//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ICON_FORM.h"
#include "BC_INTF.h"
#include "img_info.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TIconForm *IconForm;
extern img_info img_files[files_count];
//---------------------------------------------------------------------------
__fastcall TIconForm::TIconForm(TComponent* Owner)
	: TForm(Owner)
{
	icon_bc=new TIcon();
	icon_bc->Handle=LoadIcon(HInstance,"ICON_BC");
	TNotifyIconDataA icon_data;
	icon_data.cbSize=sizeof(icon_data);
	icon_data.hWnd=Handle;
	icon_data.uID=777;
	icon_data.hIcon=icon_bc->Handle;
	icon_data.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP;
	icon_data.uCallbackMessage=ICON_MESSAGE;
	strcpy(icon_data.szTip,"Powerpoint Bookmark Console");
	Shell_NotifyIcon(NIM_ADD,&icon_data);
	SetWindowLong(Handle,GWL_EXSTYLE,WS_EX_APPWINDOW);
}
//---------------------------------------------------------------------------
__fastcall TIconForm::~TIconForm()
{
	TNotifyIconDataA icon_data;
	icon_data.cbSize=sizeof(icon_data);
	icon_data.hWnd=Handle;
	icon_data.uID=777;
	Shell_NotifyIcon(NIM_DELETE,&icon_data);
	delete icon_bc;
}

void __fastcall TIconForm::IconClick(TMessage& msg)
{
	TPoint point;
	if(msg.LParam==WM_LBUTTONDBLCLK){
    	this->Show();
		Form1->Show();
	}
	if(msg.LParam==WM_RBUTTONDOWN){
		GetCursorPos(&point);
		PPMenu->Popup(point.x,point.y);
    }
}
void __fastcall TIconForm::FormShow(TObject *Sender)
{
	Width=0;
	Form1->Show();
}
//---------------------------------------------------------------------------
void __fastcall TIconForm::on_window_restore(TMessage &msg)
{
	if(msg.WParam==SC_RESTORE){
		img_files[2].state=0;
		Form1->draw_images();
	}
	DefaultHandler(&msg);
}
void __fastcall TIconForm::MItem_closeClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TIconForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action=caFree;
}
//---------------------------------------------------------------------------

void __fastcall TIconForm::MItem_showClick(TObject *Sender)
{
	this->Show();
	Form1->Show();
}
//---------------------------------------------------------------------------

void __fastcall TIconForm::MItem_homeClick(TObject *Sender)
{
	ShellExecute(Handle,"Open","http://www.winmyth.com",NULL,NULL,SW_SHOW);
}
//---------------------------------------------------------------------------

