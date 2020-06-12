#ifndef IMG_INFO_H
#define IMG_INFO_H

#include "dbl_end_str.h"
#include <Graphics.hpp>
#include <gdiPlus.h>
using namespace Gdiplus;

const int files_count=9;

struct img_info
{
	unsigned short int state;//value:0,1,2
	Gdiplus::Point location;
	Gdiplus::Size size;
	Gdiplus::Region *rgn;
	const char *path_ary[3];
};

void form_path(const char *,int,char **);
void form_region();

void init_files();
void release_files();

#endif
