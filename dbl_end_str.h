#ifndef DBL_END_STR_H
#define DBL_END_STR_H

#include <iostream>
using namespace std;

enum head{front,back};
struct dbl_end_str{
    char *base;
    int currlen,maxlen;
	head h;
    union {
		char *front;
        char *back;
    };
};

void fill0(char* p,int len);
int str_len(const char *str);
bool initdes(dbl_end_str *des,int len,head h=front);
bool reinitdes(dbl_end_str *des,int len,head h=front);
void cleandes(dbl_end_str *des,head h=front);
void chtodes(const char *str,int len,dbl_end_str *des);
bool destoch(dbl_end_str *des,char **str,head h);
bool findelem(dbl_end_str *des,int index,head h,char *result);
void inttodes(int num,dbl_end_str *des);
void traversal(dbl_end_str *des,head h);
void getends(dbl_end_str *des,char* *f,char* *b);
void destroyinternal(dbl_end_str *des);
bool truncate_c(dbl_end_str *des,head h,char c,int num,dbl_end_str *former,dbl_end_str *latter);
void apptodes(char c,dbl_end_str *des);

#endif
