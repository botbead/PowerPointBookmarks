//---------------------------------------------------------------------------

#include <vcl.h>
#include <registry.hpp>
#pragma hdrstop
#include <iostream>
#include <fstream>
using namespace std;
#include "BC_INTF.h"
#include "REG_FORM.h"
#include "ICON_FORM.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

bool bcr_changed=false;
bool presn_opened=false;
TForm1 *Form1;
unsigned short state_lock=0;
link_node *item_state_lock=NULL;
link_node *temp_item_lock=NULL;
link_node *first_display_item=NULL;
static unsigned int remaining_item_num;
extern img_info img_files[files_count];
extern int current_y;
extern const int scrollbar_ceiling=79+24;
extern const int scrollbar_floor=426+(33-24);

extern char *strs[3];
extern link_node *link_head,*temp_head,*one_node;
extern unsigned int item_num;
extern const char *path_ary[3];

extern const unsigned short org_img_x=30;
extern const unsigned short org_img_y=81;

extern const unsigned short img_width=395;
extern const unsigned short img_height=80;
extern const unsigned short item_interval=4;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	get_top_dir();
	check_file();
	init_link();
	AnsiString bcr_path=top_dir+"\\ppt.bcr";
	read_from_file(bcr_path.c_str(),strs,append_to_link);
	first_display_item=link_head->next;
	remaining_item_num=item_num;

	init_files();

	BorderStyle = bsNone;
	GdiplusStartup(&gdi_plus_token, &gdi_plus_startup_input, NULL);

	Width=470;
	Height=520;

	set_blend();
	get_img_path();

	draw_images();
	form_region();
	form_item_rgn();
	form_rgn_for_move();

	init_handlers();

	SetWindowPos(
		Handle,
		HWND_NOTOPMOST,
		0,
		0,
		470,
		520,
		SWP_NOMOVE | SWP_NOSIZE
	);

	reg_link_head=NULL;
}
//---------------------------------------------------------------------------
__fastcall TForm1::~TForm1()
{
	GdiplusShutdown(gdi_plus_token);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::set_blend()
{
	blend.BlendOp=AC_SRC_OVER;
	blend.BlendFlags=0;
	blend.SourceConstantAlpha=255;
	blend.AlphaFormat=AC_SRC_ALPHA;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::get_top_dir()
{
	AnsiString exe_file=Application->ExeName;

	dbl_end_str exe_path;
	initdes(&exe_path,102);
	chtodes(exe_file.c_str(),100,&exe_path);
	dbl_end_str result;
	initdes(&result,100);
	truncate_c(&exe_path,back,'\\',2,&result,NULL);
	char *r;
	destoch(&result,&r,front);
	top_dir=r;

	destroyinternal(&exe_path);
	destroyinternal(&result);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::check_file()
{
	AnsiString bcr_path=top_dir+"\\ppt.bcr";
	if(!FileExists(bcr_path)){
		fstream file_io;
		file_io.open(bcr_path.c_str(),ios::out|ios::app|ios::in);
		file_io.close();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::draw_images()
{
	DWORD style_win = ::GetWindowLong(Handle, GWL_EXSTYLE);
	SetWindowLong(Handle, GWL_EXSTYLE, style_win | WS_EX_LAYERED);

	WideString bkgnd_path(top_dir);
	bkgnd_path+=img_files[0].path_ary[0];
	Gdiplus::Image bkgnd(bkgnd_path.c_bstr());

	INT w_bkgnd=bkgnd.GetWidth();
	INT h_bkgnd=bkgnd.GetHeight();

	HDC mem_dc,temp_dc;
	HBITMAP handle_bmp;
	temp_dc=GetDC(Handle);
	mem_dc=CreateCompatibleDC(temp_dc);
	handle_bmp = CreateCompatibleBitmap(temp_dc,w_bkgnd,h_bkgnd);
	SelectObject(mem_dc, handle_bmp);

	Gdiplus::Graphics graph(mem_dc);
    graph.DrawImage(&bkgnd,0,0,w_bkgnd,h_bkgnd);

	int i;
	for(i=1;i<files_count;i++){
		WideString img_path(top_dir);
		img_path+=img_files[i].path_ary[img_files[i].state];
		Gdiplus::Image img(img_path.c_bstr());
		graph.DrawImage(&img,img_files[i].location.X,img_files[i].location.Y,img_files[i].size.Width,img_files[i].size.Height);
	}

	for(i=0,temp_head=first_display_item;i<5&&temp_head;i++,temp_head=temp_head->next){
		WideString item_img_path(top_dir);
		item_img_path+=path_ary[temp_head->item->state];
		Gdiplus::Image item_img(item_img_path.c_bstr());
		Gdiplus::Graphics *img_graphis=Gdiplus::Graphics::FromImage(&item_img);
		draw_text(img_graphis,temp_head->item);
		graph.DrawImage(&item_img,temp_head->item->img_location.X,temp_head->item->img_location.Y,img_width,img_height);
		delete img_graphis;
    }

	HDC wnd_dc=GetDC(Handle);
	RECT rect;
	GetWindowRect(Handle, &rect);
	POINT org_point_win={rect.left, rect.top};
	SIZE size_win = {w_bkgnd, h_bkgnd};
	POINT org_point_bkgnd={0,0};

	UpdateLayeredWindow(
		Handle,
		wnd_dc,
		&org_point_win,
		&size_win,
		mem_dc,
		&org_point_bkgnd,
		NULL,
		&blend,
		ULW_ALPHA
	);

	DeleteDC(mem_dc);
	DeleteObject(handle_bmp);
	ReleaseDC(Handle,temp_dc);
	ReleaseDC(Handle,wnd_dc);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	HDC hdc=GetDC(Handle);
	Gdiplus::Graphics graph(hdc);
	POINT p;
	GetCursorPos(&p);
	::ScreenToClient(Handle,&p);
	Gdiplus::Point point(p.x,p.y);

	if(move_state_machine(1,point,graph)){
		draw_images();
	}else if(move_state_machine(2,point,graph)){
        draw_images();
	}else if(move_state_machine(3,point,graph)){
        draw_images();
	}else if(move_state_machine(4,point,graph)){
        draw_images();
    }else if(move_state_machine(5,point,graph)){
        draw_images();
	}else if(move_state_machine(6,point,graph)){
    	draw_images();
	}else if(move_state_machine(7,point,graph)){
		draw_images();
	}else if(img_files[8].state==2){
		if(item_num>5){
			int new_location=img_files[8].location.Y+point.Y-current_y;
			if(new_location<scrollbar_ceiling){
				img_files[8].location.Y=scrollbar_ceiling;
			}else if(new_location+img_files[8].size.Height>scrollbar_floor){
				img_files[8].location.Y=scrollbar_floor-img_files[8].size.Height;
			}else{
				img_files[8].location.Y=new_location;
			}
			(Form1->*handlers[7])();
			current_y=point.Y;
			delete img_files[8].rgn;
			img_files[8].rgn=new Gdiplus::Region(Gdiplus::Rect(img_files[8].location,img_files[8].size));
			draw_images();
		}
	}else if(move_state_machine(8,point,graph)){
		draw_images();
	}else if(MouseLButtonDown){
		current_pos.x=X;
		current_pos.y=Y;
		current_pos=ClientToScreen(current_pos);
		Form1->Left=original_pos.x+(current_pos.x-mouse_down_pos.x);
		Form1->Top=original_pos.y+(current_pos.y-mouse_down_pos.y);
	}else{
		int j;
		for(j=0,temp_head=first_display_item;j<5&&temp_head;j++,temp_head=temp_head->next){
			if(temp_head!=item_state_lock&&item_move_state_machine(temp_head,point,graph)){
				draw_images();
				return;
            }
        }
	}

	ReleaseDC(Handle,hdc);
}
//---------------------------------------------------------------------------
inline bool __fastcall TForm1::move_state_machine(int index,Gdiplus::Point &p,Gdiplus::Graphics &g)
{
	img_info &a_img_file=img_files[index];
	if(!(a_img_file.state&&a_img_file.rgn->IsVisible(p,&g))&&(a_img_file.state||a_img_file.rgn->IsVisible(p,&g))){
		a_img_file.state=!(a_img_file.state);
		return true;
	}else
    	return false;
}

inline bool __fastcall TForm1::item_move_state_machine(link_node *one_node,Gdiplus::Point &p,Gdiplus::Graphics &g)
{
	item_info *one_item=one_node->item;
	if((!one_item->state)&&one_item->img_rgn->IsVisible(p,&g)){
		one_item->state=1;
		return true;
	}else if(one_item->state==1&&(!one_item->img_rgn->IsVisible(p,&g))){
		one_item->state=0;
		return true;
	}else{
        return false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	HDC hdc=GetDC(Handle);
	Gdiplus::Graphics graph(hdc);
	Gdiplus::Point point(X,Y);

	int i;
	for(i=1;i<files_count-1;i++){
		if(img_files[i].rgn->IsVisible(point,&graph)){
			state_lock=i;
			img_files[i].state=2;
			draw_images();
			return;
        }
	}
	if(img_files[i].rgn->IsVisible(point,&graph)){
    	state_lock=i;
		current_y=Y;
		img_files[i].state=2;
		draw_images();
		return;
	}
	for(i=0,temp_head=first_display_item;i<5&&temp_head;i++,temp_head=temp_head->next){
        if(temp_head->item->img_rgn->IsVisible(point,&graph)){
			temp_item_lock=temp_head;
			return;
        }
	}
	if(rgn_for_move->IsVisible(point,&graph)&&Button==mbLeft){
		MouseLButtonDown = true;
		original_pos.x=Form1->Left;
		original_pos.y=Form1->Top;
		mouse_down_pos.x=X;
		mouse_down_pos.y=Y;
		mouse_down_pos = ClientToScreen(mouse_down_pos);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	HDC hdc=GetDC(Handle);
	Gdiplus::Graphics graph(hdc);
	Gdiplus::Point point(X,Y);

	int i;
	for(i=1;i<files_count-1;i++){
		if(i==state_lock&&img_files[i].rgn->IsVisible(point,&graph)){
			img_files[i].state=1;
			draw_images();
			(Form1->*handlers[i-1])();
			state_lock=0;
			return;
        }
	}
	if(i==state_lock&&img_files[i].rgn->IsVisible(point,&graph)){
		state_lock=0;
		img_files[i].state=1;
		draw_images();
	}else if(i==state_lock&&!img_files[i].rgn->IsVisible(point,&graph)){
		state_lock=0;
		img_files[i].state=0;
		draw_images();
    }
	for(i=0,temp_head=first_display_item;i<5&&temp_head;i++,temp_head=temp_head->next){
		if(temp_head==temp_item_lock&&temp_head->item->img_rgn->IsVisible(point,&graph)){
            if(!item_state_lock){
				temp_head->item->state=2;
				draw_images();
				item_state_lock=temp_item_lock;
			}else{
				if(temp_head!=item_state_lock){
					item_state_lock->item->state=0;
					temp_head->item->state=2;
					draw_images();
					item_state_lock=temp_item_lock;
                }
			}
			temp_item_lock=NULL;
			return;
        }
	}
	if(MouseLButtonDown){
    	MouseLButtonDown=false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::draw_text(Gdiplus::Graphics *graphics,item_info *one_item)
{
	Gdiplus::FontFamily font_family(L"Tahoma");
	Gdiplus::PointF text_locations[3]={Gdiplus::PointF(57.0f,16.5f),Gdiplus::PointF(336.0f,16.5f),Gdiplus::PointF(106.0f,40.5f)};
	const Gdiplus::SolidBrush white_brush(Gdiplus::Color(255, 255, 255, 255));
	graphics->SetTextRenderingHint(TextRenderingHintAntiAlias);
	WideString item_content;
	char *result_str;
	if(!(one_item->state)){
		for(int i=0;i<3;i++){
			switch(i){
				case 0:
				handle_name(one_item->contents[i],&result_str);
				item_content=result_str;
				delete []result_str;
				break;
				case 1:
				item_content=one_item->contents[i];
				break;
				case 2:
				char *lls;
				get_little_letters(one_item->contents[i],&lls);
				handle_path(lls,&result_str);
				delete []lls;
				item_content=result_str;
				delete []result_str;
			}
			Gdiplus::Font font(&font_family, 20, FontStyleRegular, UnitPixel);
			graphics->DrawString(item_content.c_bstr(),-1,&font,text_locations[i],&white_brush);
		}
	}else{
		for(int i=0;i<3;i++){
			switch(i){
				case 0:
				handle_name(one_item->contents[i],&result_str);
				item_content=result_str;
				delete []result_str;
				break;
				case 1:
				item_content=one_item->contents[i];
				break;
				case 2:
				char *lls;
				get_little_letters(one_item->contents[i],&lls);
				handle_path(lls,&result_str);
				delete []lls;
				item_content=result_str;
				delete []result_str;
            }
			Gdiplus::Font font(&font_family, 20, FontStyleItalic, UnitPixel);
			graphics->DrawString(item_content.c_bstr(),-1,&font,text_locations[i],&white_brush);//red_brush);
		}
    }
}

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
	release_files();
	delete_item();
	for(int i=0;i<8;i++){
        handlers[i]=0;
	}
	delete rgn_for_move;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::init_handlers()
{
	handlers[0]=&TForm1::close_form;
	handlers[1]=&TForm1::mini_form;
	handlers[2]=&TForm1::add_a_item;
	handlers[3]=&TForm1::delete_a_item;
	handlers[4]=&TForm1::display_info;
	handlers[5]=&TForm1::move_item_up;
	handlers[6]=&TForm1::move_item_down;
	handlers[7]=&TForm1::move_scrollbar;
}

//close button
void __fastcall TForm1::close_form()
{
	Close();
}

void __fastcall TForm1::mini_form()
{
	Application->Minimize();
}

void __fastcall TForm1::move_item_up()
{
	if(remaining_item_num<item_num){
		int i;
		for(i=1,temp_head=link_head->next;i+remaining_item_num<item_num;i++,temp_head=temp_head->next){
			temp_head->item->img_location.Y+=74;
		}
		first_display_item=temp_head;
		while(temp_head){
        	temp_head->item->img_location.Y+=74;
			temp_head=temp_head->next;
        }
		if((img_files[8].location.Y-=ceil(332/(double)item_num))<scrollbar_ceiling){
            img_files[8].location.Y=scrollbar_ceiling;
        }
		draw_images();
		form_item_rgn();
		delete img_files[8].rgn;
		img_files[8].rgn=new Gdiplus::Region(Gdiplus::Rect(img_files[8].location,img_files[8].size));
		remaining_item_num++;
    }
}

void __fastcall TForm1::move_item_down()
{
	if(remaining_item_num>5){
		temp_head=link_head->next;
		while(temp_head){
			temp_head->item->img_location.Y-=74;
			temp_head=temp_head->next;
		}
		first_display_item=first_display_item->next;
		if((img_files[8].location.Y+=ceil(332/(double)item_num))+img_files[8].size.Height>scrollbar_floor){
			img_files[8].location.Y=scrollbar_floor-img_files[8].size.Height;
        }
		draw_images();
		form_item_rgn();
		delete img_files[8].rgn;
		img_files[8].rgn=new Gdiplus::Region(Gdiplus::Rect(img_files[8].location,img_files[8].size));
		remaining_item_num--;
	}
}

void __fastcall TForm1::add_a_item()
{
	_ApplicationDisp disp_app;
	disp_app.BindDefault();
	Powerpoint_tlb::PowerPointPresentation *active_presn=NULL;
	disp_app.get_ActivePresentation(&active_presn);
	if(!active_presn){
		MessageBox(Handle,"No PPT Presentations have been opened!","Error",MB_OK);
		return;
    }

	Powerpoint_tlb::DocumentWindow *active_win;
	disp_app.get_ActiveWindow(&active_win);
	DocumentWindowDisp disp_docwin;
	disp_docwin.Bind(active_win);

	Powerpoint_tlb::Selection *selection;
	disp_docwin.get_Selection(&selection);
	SelectionDisp disp_selection;
	disp_selection.Bind(selection);

	Powerpoint_tlb::SlideRange *slide_range;
	disp_selection.get_SlideRange(&slide_range);
	SlideRangeDisp disp_sliderange;
	disp_sliderange.Bind(slide_range);

	int slideindex;
	disp_sliderange.get_SlideIndex(&slideindex);

	if((!registered)&&(slideindex>20)){
		MessageBox(Handle,"The trial version can not record a bookmark whose index of slide is beyond 20.","Attention",MB_OK);
		return;
	}

	Powerpoint_tlb::PowerPointPresentation *presn;
	disp_docwin.get_Presentation(&presn);
	_PresentationDisp disp_presn;
	disp_presn.Bind(presn);

	wchar_t *path,*name;
	disp_presn.get_Path(&path);
	disp_presn.get_Name(&name);

	disp_app=0;

	AnsiString path_txt=path;
	AnsiString name_txt=name;
	AnsiString index_txt=IntToStr(slideindex);

	one_node=new link_node;
	one_node->item=new item_info;
	one_node->item->state=0;

	one_node->item->img_location.X=org_img_x;
	one_node->item->img_location.Y=org_img_y;

	fill_contents(name_txt.c_str(),&(one_node->item->contents[0]));
	fill_contents(index_txt.c_str(),&(one_node->item->contents[1]));
	fill_contents(path_txt.c_str(),&(one_node->item->contents[2]));

	if(remaining_item_num<item_num){
		temp_head=link_head;
        while(temp_head->next){
			temp_head->next->item->img_location.Y+=((item_num-remaining_item_num)*74);
			temp_head=temp_head->next;
        }
    }

	one_node->next=link_head->next;
	first_display_item=link_head->next=one_node;
	remaining_item_num=++item_num;
	modify_scrollbar_height();
	temp_head=link_head->next;
	while(temp_head->next){
		temp_head->next->item->img_location.Y+=((img_height-10)+item_interval);
        temp_head=temp_head->next;
    }
	draw_images();
	form_item_rgn();
	bcr_changed=true;
}

void __fastcall TForm1::write_into_file(const char *str,bool end_of_record)
{
	ofstream file_o;
	AnsiString bcr_path=top_dir+"\\ppt.bcr";
	file_o.open(bcr_path.c_str(),ios::out|ios::app);
	int i=0;
	char c;
	while(c=str[i]){
		file_o.put(c);
		i++;
	}
	if(end_of_record){
		file_o.put(30);
    }else{
		file_o.put(31);
	}
	file_o.close();
}

void __fastcall TForm1::delete_a_item()
{
	if(!item_state_lock){
		MessageBox(Handle,"No bookmark has been selected!","Error",MB_OK);
	}else{
		temp_head=link_head;
		while(temp_head->next){
			if(temp_head->next==item_state_lock){
				one_node=temp_head->next;
				temp_head->next=one_node->next;
				delete one_node->item->img_rgn;
				delete one_node->item;
				delete one_node;
				item_state_lock=one_node=NULL;
				break;
			}
			temp_head=temp_head->next;
		}
		if(item_num>0){
            item_num--;
        }
		while(temp_head->next){
			temp_head->next->item->img_location.Y-=74;
            temp_head=temp_head->next;
		}
		int i=0;
		temp_head=link_head;
		while(temp_head->next){
			if(temp_head->next->item->img_location.Y==org_img_y){
				first_display_item=temp_head;
				i++;
				break;
            }
			i++;
            temp_head=temp_head->next;
		}
		if(!i){
			first_display_item=NULL;
			remaining_item_num=item_num;
        }else{
			if(item_num>=5&&item_num-i<4){
				temp_head=link_head;
				while(temp_head->next){
                    temp_head->next->item->img_location.Y+=74;
                    temp_head=temp_head->next;
				}
				remaining_item_num=5;
            }else{
				first_display_item=first_display_item->next;
				remaining_item_num=item_num-(i-1);
            }
		}
		if(item_num<=5){
        	img_files[8].location.Y=103;
			img_files[8].size.Height=332;
		}else{
			img_files[8].location.Y=103+(item_num-remaining_item_num)*((332/(double)item_num));
			img_files[8].size.Height=((332/(double)item_num))*5;
		}
		delete img_files[8].rgn;
		img_files[8].rgn=new Gdiplus::Region(Gdiplus::Rect(img_files[8].location,img_files[8].size));
		draw_images();
		form_item_rgn();
        bcr_changed=true;
	}
}

void __fastcall TForm1::display_info()
{
	if(registered){
		AnsiString reg_info="This Product is licensed to ";
		reg_info+=user_name;
		MessageBox(Handle,reg_info.c_str(),"Thanks",MB_OK);
	}else{
		RegForm->Show();
	}
}

void __fastcall TForm1::move_scrollbar()
{
	HDC hdc=GetDC(Handle);
	Gdiplus::Graphics graph(hdc);
	POINT p;
	GetCursorPos(&p);
	::ScreenToClient(Handle,&p);
	Gdiplus::Point point(p.x,p.y);

	if((point.Y>current_y)&&((img_files[8].location.Y-scrollbar_ceiling)>=(item_num-remaining_item_num+1)*floor(332/(double)item_num))){
		temp_head=link_head->next;
		while(temp_head){
			temp_head->item->img_location.Y-=74;
			temp_head=temp_head->next;
		}
		first_display_item=first_display_item->next;
		draw_images();
		form_item_rgn();
		remaining_item_num--;
	}
	if((point.Y<current_y)&&((img_files[8].location.Y+img_files[8].size.Height-scrollbar_ceiling)<=(item_num-remaining_item_num+(5-1))*ceil(332/(double)item_num))){
		int i;
    	for(i=1,temp_head=link_head->next;i+remaining_item_num<item_num;i++,temp_head=temp_head->next){
        	temp_head->item->img_location.Y+=74;
		}
		first_display_item=temp_head;
		while(temp_head){
			temp_head->item->img_location.Y+=74;
        	temp_head=temp_head->next;
		}
		draw_images();
		form_item_rgn();
		remaining_item_num++;
	}

	ReleaseDC(Handle,hdc);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::on_window_restore(TMessage &msg)
{
	if(msg.WParam==SC_RESTORE){
		img_files[2].state=0;
		draw_images();
	}
	DefaultHandler(&msg);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	parse_reg_info();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::fill_contents(const char *src,char **dst)
{
	(*dst)=new char[50];
	char *dst2=*dst;
	while(*dst2++=*src++);
}
//---------------------------------------------------------------------------
inline void __fastcall TForm1::modify_scrollbar_height()
{
	img_files[8].location.Y=103;
    if(item_num<=5){
		img_files[8].size.Height=332;
	}else{
		img_files[8].size.Height=((332/(double)item_num))*5;
	}
	delete img_files[8].rgn;
	img_files[8].rgn=new Gdiplus::Region(Gdiplus::Rect(img_files[8].location,img_files[8].size));
}
//---------------------------------------------------------------------------
void __fastcall TForm1::replace_bcr()
{
	if(bcr_changed){
		ofstream file_o;
		AnsiString bcr_path=top_dir+"\\ppt.bcr";
		file_o.open(bcr_path.c_str(),ios::out);
		file_o.close();
		temp_head=link_head;
		while(temp_head->next){
			write_into_file(temp_head->next->item->contents[0],false);
			write_into_file(temp_head->next->item->contents[1],false);
			write_into_file(temp_head->next->item->contents[2],true);
            temp_head=temp_head->next;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDblClick(TObject *Sender)
{
	HDC hdc=GetDC(Handle);
	Gdiplus::Graphics graph(hdc);
	POINT p;
	GetCursorPos(&p);
	::ScreenToClient(Handle,&p);
	Gdiplus::Point point(p.x,p.y);

	temp_head=link_head;
	while(temp_head->next){
		if(temp_head->next==item_state_lock&&temp_head->next->item->img_rgn->IsVisible(point,&graph)){
			WideString ppt_file_path(temp_head->next->item->contents[2]);
			ppt_file_path+="\\";
			ppt_file_path+=temp_head->next->item->contents[0];

			_ApplicationDisp disp_app;
			if(!disp_app){
				disp_app.BindDefault();
			}

			disp_app.Visible=(MsoTriState)(-1);
			disp_app.Activate();

			bool existed=false;

			PresentationsDisp disp_presns;
			Powerpoint_tlb::Presentations *presns;
			disp_app.get_Presentations(&presns);
			disp_presns.Bind(presns);

			long presn_num=0;
			disp_presns.get_Count(&presn_num);
			Powerpoint_tlb::PowerPointPresentation *open_presn;
			_PresentationDisp disp_open_presn;
			while(presn_num){
				disp_presns.Item((TVariant)presn_num,&open_presn);
				disp_open_presn.Bind(open_presn);
				wchar_t *full_name;
				disp_open_presn.get_FullName(&full_name);
				WideString open_presn_path(full_name);
				if(open_presn_path==ppt_file_path){
					existed=true;
					break;
				}
				presn_num--;
			}

            int slide_index;

			if(existed){
				Powerpoint_tlb::DocumentWindows *windows;
				DocumentWindowsDisp disp_wins;
				disp_open_presn.get_Windoz(&windows);
				disp_wins.Bind(windows);

				Powerpoint_tlb::DocumentWindow *window;
				disp_wins.Item(1,&window);
				DocumentWindowDisp disp_win;
				disp_win.Bind(window);

				disp_win.Activate();

				Powerpoint_tlb::Slides *slides;
				disp_open_presn.get_Slides(&slides);
				SlidesDisp disp_slides;
				disp_slides.Bind(slides);

				str_to_num(temp_head->next->item->contents[1],&slide_index);

				Powerpoint_tlb::PowerPointSlide *one_slide;
				disp_slides.Item((TVariant)slide_index,&one_slide);
				_SlideDisp disp_slide;
				disp_slide.Bind(one_slide);

				disp_slide.Select();
            }else{
				Powerpoint_tlb::PowerPointPresentation *presn;
				disp_presns.Open((wchar_t *)ppt_file_path,(MsoTriState)0,(MsoTriState)0,(MsoTriState)-1,&presn);
				_PresentationDisp disp_presn;
				disp_presn.Bind(presn);

				Powerpoint_tlb::Slides *slides;
				disp_presn.get_Slides(&slides);
				SlidesDisp disp_slides;
				disp_slides.Bind(slides);

				str_to_num(temp_head->next->item->contents[1],&slide_index);

				Powerpoint_tlb::PowerPointSlide *one_slide;
				disp_slides.Item((TVariant)slide_index,&one_slide);
				_SlideDisp disp_slide;
				disp_slide.Bind(one_slide);

				disp_slide.Select();
			}
			disp_app=0;
		}
		temp_head=temp_head->next;
	}
    ReleaseDC(Handle,hdc);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::str_to_num(const char *str,int *num)
{
    char c;
    bool posi_or_neg=true;
    if(*str=='-'){
        str++;
        posi_or_neg=false;
    }
    *num=0;
    while(c=*str++){
        (*num*=10)+=c-48;
    }
    if(!posi_or_neg){
        *num-=*num+*num;
    }
}

void __fastcall TForm1::num_to_str(int num,char **str)
{
    dbl_end_str des;
    initdes(&des,12,back);
    inttodes(num,&des);
	destoch(&des,str,front);
	destroyinternal(&des);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::form_rgn_for_move()
{
	int i;
	rgn_for_move=new Gdiplus::Region(Gdiplus::Rect(img_files[0].location,img_files[0].size));
	for(i=1;i<9;i++){
		rgn_for_move->Exclude(img_files[i].rgn);
	}
	Gdiplus::Region *temp_rgn=new Gdiplus::Region(Gdiplus::Rect(25,78,421,381));
	rgn_for_move->Exclude(temp_rgn);
	delete temp_rgn;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::form_link_list(const char *string)
{
	int node_num=0;
	reg_link_head=new node;
	reg_link_head->next=NULL;
	node *temp_head=reg_link_head;
	char temp_str[5];
	clean_str(temp_str,5);
	char c;
	int i=0;
	int temp_value;
	node *anode;
	while(c=*string++){
        if(c!='-'){
			temp_str[i]=c;
			i++;
		}else{
			anode=new node;
			str_to_num(temp_str,&temp_value);
			anode->value=temp_value;
			anode->next=NULL;
			temp_head=temp_head->next=anode;
			i=0;
			clean_str(temp_str,5);
			node_num++;
        }
	}
	second_len=str_len(temp_str);
	anode=new node;
	str_to_num(temp_str,&temp_value);
	anode->value=temp_value;
	anode->next=reg_link_head->next;
	reg_link_head->next=anode;
	reg_link_head->value=++node_num;
}

inline void __fastcall TForm1::clean_str(char *str,int len)
{
	while(len)
	{
    	str[--len]='\0';
	}
}

void __fastcall TForm1::decrypt_num(int order,int &value,int result_mod)
{
	if(odd_or_not(order)){
		value+=result_mod;
    }else{
		value-=result_mod;
    }
}

void __fastcall TForm1::decrypt()
{
	if(!decrypted_string.IsEmpty()){
        decrypted_string="";
	}
	char *str_of_num=NULL;
	num_to_str(reg_link_head->next->value,&str_of_num);
	decrypted_string+=str_of_num;
	int r_mod=(reg_link_head->next->value)%10;
	int i=1;
	node *temp_node=reg_link_head->next;
	reg_link_head->next=temp_node->next;
	delete []str_of_num;
	delete temp_node;
	int order=second_len;
	while(i<reg_link_head->value){
		decrypt_num(order++,reg_link_head->next->value,r_mod);
		decrypted_string+=(char_to_str(static_cast<char>(reg_link_head->next->value)),little_str);
		r_mod=(reg_link_head->next->value)%10;
		temp_node=reg_link_head->next;
		reg_link_head->next=temp_node->next;
		delete temp_node;
    	i++;
	}
	delete reg_link_head;
	reg_link_head=NULL;
}

inline void __fastcall TForm1::char_to_str(char c)
{
	little_str[0]=c;
	little_str[1]='\0';
}

void __fastcall TForm1::extract_keys(const char *str,char* *name,char* *key)
{
	char *temp_name,*temp_key;
	temp_name=*name=new char[17];
	temp_key=*key=new char[5];
	char c;
	unsigned short int flag=0;
	int i,name_i,key_i;
	i=name_i=key_i=0;
	while(c=str[i]){
		switch(flag){
			case 0:
			if(c==31){
                flag++;
            }else{
				if(!(48<=c&&c<=57)){
					temp_key[key_i++]=c;
                }
			}
			break;
			case 1:
            if(c==30){
                flag++;
            }else{
                temp_name[name_i++]=c;
			}
			break;
			case 2:
			if(!(48<=c&&c<=57)){
				temp_key[key_i++]=c;
            }
        }
    	i++;
	}
	temp_key[key_i]=temp_name[name_i]='\0';
}

inline bool __fastcall TForm1::odd_or_not(int num)
{
    if(num%2){
        return true;
    }else{
        return false;
    }
}

bool __fastcall TForm1::compare_string(const char *str1,const char *str2)
{
    int index1,index2;
    index1=index2=0;
    for(;(str1[index1]&&str2[index2])&&(str1[index1]==str2[index2]);index1++,index2++);
    if((index1==index2)&&(!str1[index1]&&!str2[index2])){
        return true;
    }else{
        return false;
    }
}

void __fastcall TForm1::parse_reg_info()
{
	TRegistry *reg=new TRegistry;
	reg->RootKey=HKEY_CURRENT_USER;
	try{
		if(!reg->OpenKey("\\Software\\Bookmark Console",false)){
        	registered=false;
		}else{
			AnsiString cryptogram=reg->ReadString("registered");
			form_link_list(cryptogram.c_str());
			decrypt();
			char *name,*key;
			extract_keys(decrypted_string.c_str(),&name,&key);
			if(compare_string(key,"true")){
				registered=true;
				user_name=name;
			}else{
            	registered=false;
			}
			delete []name;
			delete []key;
        }
	}
	__finally{
		reg->CloseKey();
		delete reg;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::set_registered(bool true_or_not)
{
	registered=true_or_not;
}

void __fastcall TForm1::set_user_name(const char *uname)
{
	user_name=uname;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::get_little_letters(const char *src,char **dst)
{
    char *temp_dst;
    temp_dst=*dst=new char [str_len(src)+1];
    char c;
    int i=0;
    while(c=src[i]){
        if(65<=c&&c<=90){
            temp_dst[i]=c+32;
        }else{
            temp_dst[i]=c;
        }
        i++;
    }
    temp_dst[i]='\0';
}

void __fastcall TForm1::crop_string(const char *src,char **dst,int total_len,int former_len,int latter_len,const char *filler)
{
    if((total_len<0||former_len<0||latter_len<0)||(total_len<former_len+latter_len+str_len(filler))){
        *dst=NULL;
        return;
    }
    int len;
    char *temp_dst;
    if((len=str_len(src))>total_len){
        int i,j;
        i=j=0;
        temp_dst=*dst=new char[total_len+1];
        while(i<former_len)
        {
            temp_dst[j]=src[i];
            i++;
            j++;
        }
        while(i<len-latter_len)i++;
        while(*filler){
            temp_dst[j++]=*filler;
            filler++;
        }
        while(i<len){
            temp_dst[j]=src[i];
            i++;
            j++;
        }
        temp_dst[j]='\0';
    }else{
        char c;
        temp_dst=*dst=new char[len+1];
        while(c=*src++){
            *temp_dst++=c;
        }
        *temp_dst='\0';
    }
}

void __fastcall TForm1::handle_name(const char *src,char* *dst)
{
    dbl_end_str des;
    initdes(&des,262,front);
    dbl_end_str front_str;
    initdes(&front_str,262,front);
    chtodes(src,str_len(src),&des);
    if(truncate_c(&des,back,'.',1,&front_str,NULL)){
        char *name_without_suffix;
        destoch(&front_str,&name_without_suffix,front);
        char *little_name;
        get_little_letters(name_without_suffix,&little_name);
        delete name_without_suffix;
        char *clipped_str;
		crop_string(little_name,&clipped_str,12,8,3,"~");
        delete little_name;
        dbl_end_str r_des;
		initdes(&r_des,16,front);
        chtodes(clipped_str,str_len(clipped_str),&r_des);
        apptodes('.',&r_des);
        apptodes('p',&r_des);
        apptodes('p',&r_des);
        apptodes('t',&r_des);
        destoch(&r_des,dst,front);
        destroyinternal(&r_des);
    }else{
        *dst=NULL;
    }
    destroyinternal(&des);
    destroyinternal(&front_str);
}

void __fastcall TForm1::handle_path(const char *src,char* *dst)
{
    char c,*temp_dst,*temp_seg1,*temp_seg2,*str_after_backslash;
    temp_dst=*dst=new char[26];
    str_after_backslash=new char[str_len(src)+1];
    int i,j,str_num_after_last_backslash,num_backslash,str_num_after_first_backslash;
    i=j=str_num_after_last_backslash=str_num_after_first_backslash=num_backslash=0;
    while(i<3){
        temp_dst[j++]=src[i];
        i++;
    }
    num_backslash++;
    int k=0;
    while(c=src[i]){
        if(c=='\\'){
            num_backslash++;
            str_num_after_first_backslash+=str_num_after_last_backslash;
            str_num_after_last_backslash=0;
        }else{
            str_num_after_last_backslash++;
        }
        str_after_backslash[k++]=c;
        i++;
    }
    if(!k){
        temp_dst[j]='\0';
        delete []str_after_backslash;
    }else if(num_backslash==1){
        str_after_backslash[k]='\0';
        crop_string(str_after_backslash,&temp_seg1,22,15,3,"~");
        i=0;
        while(c=temp_seg1[i]){
            temp_dst[j++]=c;
            i++;
        }
        temp_dst[j]='\0';
        delete []temp_seg1;
        delete []str_after_backslash;
    }else{
        str_after_backslash[k-str_num_after_last_backslash-1]='\0';
        if(str_num_after_first_backslash>=str_num_after_last_backslash){
            crop_string(str_after_backslash,&temp_seg1,14,10,3,"~");
            crop_string((src+3+(k-str_num_after_last_backslash)),&temp_seg2,7,3,3,"~");
        }else{
            crop_string(str_after_backslash,&temp_seg1,7,3,3,"~");
            crop_string((src+3+(k-str_num_after_last_backslash)),&temp_seg2,14,8,3,"~");
        }
        i=0;
        while(c=temp_seg1[i]){
            temp_dst[j++]=c;
            i++;
        }
        temp_dst[j++]='\\';
        i=0;
        while(c=temp_seg2[i]){
            temp_dst[j++]=c;
            i++;
        }
        temp_dst[j]='\0';
        delete []temp_seg1;
        delete []temp_seg2;
        delete []str_after_backslash;
    }
}
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	replace_bcr();
	IconForm->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
	img_files[1].state=0;
	img_files[2].state=0;
	draw_images();
}
//---------------------------------------------------------------------------

