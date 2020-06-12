#include "dbl_end_str.h"

//init dbl_end_str
bool initdes(dbl_end_str *des,int len,head h)
{
    if(des->base=new char[des->maxlen=len+2]){
        des->h=h;
        des->currlen=0;
        fill0(des->base,des->maxlen);
        if(h==front){
            des->front=des->base+1;
        }else{
            des->back=des->base+(des->maxlen-2);
        }
        return true;
    }else{
        return false;
    }
}

//string-->dbl_end_str
//write substring of len length in des
void chtodes(const char *str,int len,dbl_end_str *des)
{
    if(len<1)return;
    int ultimlen,actlen=str_len(str);
    if(len>=actlen)ultimlen=actlen;
    else ultimlen=len;
    if(ultimlen<=(des->maxlen-2))cleandes(des);
    else reinitdes(des,ultimlen+2);
    char * temp;
    getends(des,&temp,NULL);
    for(int i=0;i<ultimlen;i++)temp[i]=str[i];
    des->currlen=ultimlen;
}

//length of string
int str_len(const char *str)
{
	int i=0;
	for(;*(str+i);i++);
	return i;
}

//dbl_end_str-->string
bool destoch(dbl_end_str *des,char **str,head h)
{
    char *latter,*f,*b;
    getends(des,&f,&b);
    int len=des->currlen;
    if(latter=*str=new char[des->currlen+1]){
        latter[len]='\0';
        if(h==front){
            for(int i=0;i<len;i++){
                latter[i]=f[i];
            }
        }else{
            for(int i=0;i<len;i++){
                latter[i]=*(b-i);
            }
        }
        return true;
    }
    return false;
}

void fill0(char* p,int len)
{
    if(!p)return;
    for(int i=0;i<len;i++){
        p[i]='\0';
    }
}

void cleandes(dbl_end_str *des,head h)
{
    des->h=h;
    des->currlen=0;
    fill0(des->base,des->maxlen);
    if(h==front){
        des->front=des->base+1;
    }else{
        des->back=des->base+(des->maxlen-2);
    }
}

//find element on the indexed location in positive/inverted order
bool findelem(dbl_end_str *des,int index,head h,char *result)
{
    if(index>=des->currlen)return false;
    char *f,*b;
    getends(des,&f,&b);
    if(h==front){
        *result=f[index];
        return true;
    }else{
        *result=*(b-index);
        return true;
    }
}

void inttodes(int num,dbl_end_str *des)
{
    cleandes(des,back);
    bool posi_or_neg=true;
    if(num<0){
        num-=num+num;
        posi_or_neg=false;
    }
    int r;//remainder
    char *b=des->back;
    do{
        r=num%10;
        *b--=(r+48);
        num/=10;
    }while(num);
    if(posi_or_neg){
        des->currlen=des->back-b;
        des->front=b+1;
    }else{
        *b='-';
        des->currlen=des->back-b+1;
        des->front=b;
    }
    //h keep pace with the pointer in union
    des->h=front;
}

void traversal(dbl_end_str *des,head h)
{
    char a;
    int i=0;
    for(;findelem(des,i,h,&a);i++){

        //do something instead of cout << a;
        cout<<a;
    }
}

//for internal use
void getends(dbl_end_str *des,char* *f,char* *b)
{
    if(!f&&!b)return;
    char *temp_f,*temp_b;
    if(!(des->currlen)){
        temp_f=des->base+1;
        temp_b=des->base+(des->maxlen-2);
    }else{
        if(des->h==front){
            temp_f=des->front;
            temp_b=(temp_f+des->currlen)-1;
        }else{
            temp_b=des->back;
            temp_f=(temp_b-des->currlen)+1;
        }
    }
    if(f&&!b)*f=temp_f;
    else if(!f&&b)*b=temp_b;
    else{
        *f=temp_f;
        *b=temp_b;
    }
}

void destroyinternal(dbl_end_str *des)
{
    delete [](des->base);
}

//for internal use
bool reinitdes(dbl_end_str *des,int len,head h)
{
    delete [](des->base);
    if(des->base=new char[des->maxlen=len+2]){
        des->h=h;
        des->currlen=0;
        fill0(des->base,des->maxlen);
        if(h==front){
            des->front=des->base+1;
        }else{
            des->back=des->base+(des->maxlen-2);
        }
        return true;
    }else{
        return false;
    }
}

bool truncate_c(dbl_end_str *des,head h,char c,int num,dbl_end_str *former,dbl_end_str *latter)
{
    if(!des||!(des->currlen)||(!former&&!latter)||(num<1))return false;
    char type,r;
    if(former&&!latter)type='1';
    else if(!former&&latter)type='2';
    else type='3';
    int i,n=des->currlen;
    for(i=0;i<n;i++){
        if(findelem(des,i,h,&r)&&(r==c)&&!(--num))break;
    }
    if(i==n||num)return false;
    else{
        char *f,*l;
        int len_f,len_l;
        getends(des,&f,NULL);
        if(h==front){
            len_f=i;
            len_l=n-(i+1);
            l=f+(i+1);
        }else{
            len_f=n-(i+1);
            len_l=i;
            l=f+(n-(i+1))+1;
        }
        switch(type){
            case '1':
            chtodes(f,len_f,former);
            break;
            case '2':
            chtodes(l,len_l,latter);
            break;
            case '3':
            chtodes(f,len_f,former);
            chtodes(l,len_l,latter);
            break;
        }
        return true;
    }
}

void apptodes(char c,dbl_end_str *des)
{
    int currlen,maxlen;
    currlen=des->currlen;
    maxlen=des->maxlen;
    if(currlen>=maxlen-2){
        char *tempstr=new char[currlen];
        destoch(des,&tempstr,des->h);
        if(reinitdes(des,(maxlen*=2),des->h)){
            des->maxlen=maxlen;
        }
        chtodes(tempstr,currlen,des);
        delete []tempstr;
    }
    char *f,*b;
    getends(des,&f,&b);
    if(des->h==front){
        f[des->currlen]=c;
    }else{
        *(b-des->currlen)=c;
    }
    (des->currlen)++;
}
