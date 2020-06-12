#ifndef ITEM_INFO_H
#define ITEM_INFO_H

#include <Graphics.hpp>
#include <gdiPlus.h>
using namespace Gdiplus;

struct item_info
{
	unsigned short int state;
	Gdiplus::Point img_location;
	Gdiplus::Region *img_rgn;

	char *contents[3];
};

struct link_node
{
	item_info *item;
	link_node *next;
};

void init_link();
void form_node();
void append_to_link();
void read_from_file(const char *,char* *,void (*)());
void form_item_rgn();
void delete_item();
void get_img_path();
#endif
