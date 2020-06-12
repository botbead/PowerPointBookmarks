#include <iostream>
#include <fstream>
using namespace std;
#include "item_info.h"
#include "dbl_end_str.h"

unsigned int item_num=0;

const unsigned short org_img_x=30;
const unsigned short org_img_y=81;

const unsigned short img_width=395;//395;
//the img_height influence y-coordinate in form_node()
const unsigned short img_height=70;//80;


const char *path_ary[3];
char *strs[3];


//the spacing between items
const unsigned short item_interval=4;

const Gdiplus::Size img_size(395,80);

link_node *link_head,*temp_head,*one_node;

extern void form_path(const char *,int,char **);


void form_node(link_node* *node)
{
	*node=new link_node;
	(*node)->item=new item_info;
	item_info *temp=(*node)->item;
	temp->state=0;

	temp->img_location.X=org_img_x;
	temp->img_location.Y=org_img_y+(item_num++)*(img_height+item_interval);

	int num;
	for(num=0;num<3;num++){
        temp->contents[num]=strs[num];
	}
	(*node)->next=NULL;
}

void append_to_link()
{
	form_node(&one_node);
	temp_head=temp_head->next=one_node;
}

void init_link()
{
	link_head=new link_node;
	link_head->item=NULL;
	link_head->next=NULL;
	temp_head=link_head;
}

void read_from_file(const char *file_path,char* *strs,void (*function)())
{
    dbl_end_str des[3];
    int i;
    for(i=0;i<3;i++){
        initdes(&(des[i]),50,back);
    }
    ifstream file_i;
    file_i.open(file_path,ios::in);
    i=0;
    char c,n;
    int j;
        while(file_i.get(c),n=file_i.peek(),!file_i.eof()){
            switch(i){
                case 0:apptodes(c,&(des[i]));break;
                case 1:apptodes(c,&(des[i]));break;
                case 2:apptodes(c,&(des[i]));break;
            }
            if(n==31){
                file_i.ignore(1,31);
                destoch(&des[i],&(strs[i]),back);
                i++;
            }else if(n==30){
                file_i.ignore(1,30);
                destoch(&des[i],&(strs[i]),back);
                i=0;
                function();
                for(j=0;j<3;j++){
                    cleandes(&des[j],back);
                }
            }
        }
    for(i=0;i<3;i++){
        destroyinternal(&(des[i]));
    }
    file_i.close();
}

void form_item_rgn()
{
	temp_head=link_head;
	while(temp_head->next){
		temp_head->next->item->img_rgn=new Gdiplus::Region(Gdiplus::Rect(temp_head->next->item->img_location.X+((395-377)/2),temp_head->next->item->img_location.Y+((80-64)/2),377,64));
		temp_head=temp_head->next;
    }
}

void delete_item()
{
	temp_head=link_head->next;
	while(temp_head){
		one_node=temp_head->next;
		delete temp_head->item->img_rgn;
		delete temp_head->item;
		delete temp_head;
		temp_head=one_node;
	}
	delete link_head;
	link_head=NULL;
}

void get_img_path()
{
	char *temp_path;

	for(int i=0;i<3;i++){
		form_path("item",i,&temp_path);
		path_ary[i]=temp_path;
	}
}
