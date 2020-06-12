#include "img_info.h"

img_info img_files[files_count];
int current_y;
const int scrollbar_ceiling=79+24;
const int scrollbar_floor=426+(33-24)-1;

extern unsigned int item_num;

void init_files()
{
	int i;
	char *temp_path;
	img_info info;
	//background
	info.state=0;//normal state
	info.location.X=0;
	info.location.Y=0;
	info.size.Width=470;
	info.size.Height=520;
	info.path_ary[0]="\\resource\\bkgnd.png";
	info.path_ary[1]="";
	info.path_ary[2]="";
	img_files[0]=info;

	//close_button
	info.location.X=408;
	info.location.Y=25;
	info.size.Width=36;
	info.size.Height=22;
	for(i=0;i<3;i++){
		form_path("cb",i,&temp_path);
		info.path_ary[i]=temp_path;
	}
	img_files[1]=info;

	//mini_button
	info.location.X=370;
	info.location.Y=25;
	info.size.Width=36;
	info.size.Height=22;
	for(i=0;i<3;i++){
		form_path("mb",i,&temp_path);
		info.path_ary[i]=temp_path;
	}
	img_files[2]=info;

	//add_button
	info.location.X=365;
	info.location.Y=467;
	info.size.Width=80;
	info.size.Height=28;
	for(i=0;i<3;i++){
		form_path("ab",i,&temp_path);
		info.path_ary[i]=temp_path;
	}
	img_files[3]=info;

	//delete_button
	info.location.X=285;
	info.location.Y=467;
	info.size.Width=80;
	info.size.Height=28;
	for(i=0;i<3;i++){
		form_path("db",i,&temp_path);
		info.path_ary[i]=temp_path;
	}
	img_files[4]=info;

	//i_button
	info.location.X=28;
	info.location.Y=467;
	info.size.Width=34;
	info.size.Height=28;
	for(i=0;i<3;i++){
		form_path("ib",i,&temp_path);
		info.path_ary[i]=temp_path;
	}
	img_files[5]=info;

	//up_button
	info.location.X=419;
	info.location.Y=79;
	info.size.Width=27;
	info.size.Height=33;
	for(i=0;i<3;i++){
		form_path("ub",i,&temp_path);
		info.path_ary[i]=temp_path;
	}
	img_files[6]=info;

	//down_button
	info.location.X=419;
	info.location.Y=426;
	info.size.Width=27;
	info.size.Height=33;
	for(i=0;i<3;i++){
		form_path("nb",i,&temp_path);
		info.path_ary[i]=temp_path;
	}
	img_files[7]=info;

	//scrollo_bar
	info.location.X=428;
	info.location.Y=103;
	//18*332
	info.size.Width=18;
	if(item_num<=5){
        info.size.Height=332;
	}else{
		info.size.Height=((332/(double)item_num))*5;//332;
	}
	for(i=0;i<3;i++){
		form_path("sb",i,&temp_path);
		info.path_ary[i]=temp_path;
	}
	img_files[8]=info;
}

void form_region()
{
	for(int i=0;i<files_count-3;i++){
		img_files[i].rgn=new Gdiplus::Region(Gdiplus::Rect(img_files[i].location,img_files[i].size));
	}
	img_files[6].rgn=new Gdiplus::Region(Gdiplus::Rect(428,79,18,24));
	img_files[7].rgn=new Gdiplus::Region(Gdiplus::Rect(428,435,18,24));
	img_files[8].rgn=new Gdiplus::Region(Gdiplus::Rect(img_files[8].location,img_files[8].size));
}

void release_files()
{
	for(int i=0;i<files_count;i++){
		delete img_files[i].rgn;
    }
}

void form_path(const char *basic_file,int file_order,char **final_str)
{
    dbl_end_str fore_part;
    initdes(&fore_part,102);
    chtodes("\\resource\\",str_len("\\resource\\"),&fore_part);
    dbl_end_str mid_part;
    initdes(&mid_part,102);
    chtodes(basic_file,str_len(basic_file),&mid_part);
    dbl_end_str order;
    initdes(&order,3);
    inttodes(file_order,&order);
    char *ch_order;
    destoch(&order,&ch_order,front);
    apptodes(ch_order[0],&mid_part);
    dbl_end_str back_part;
    initdes(&back_part,6);
    chtodes(".png",str_len(".png"),&back_part);

    char r;
    int i;
    for(i=0;findelem(&mid_part,i,front,&r);i++){
        apptodes(r,&fore_part);
    }
    for(i=0;findelem(&back_part,i,front,&r);i++){
        apptodes(r,&fore_part);
    }
    destoch(&fore_part,final_str,front);

    destroyinternal(&fore_part);
    destroyinternal(&mid_part);
    destroyinternal(&back_part);
}
