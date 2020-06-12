//---------------------------------------------------------------------------
#include <vcl.h>
#include <registry.hpp>
#pragma hdrstop
#include "REG_FORM.h"
#include "BC_INTF.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRegForm *RegForm;
//---------------------------------------------------------------------------
__fastcall TRegForm::TRegForm(TComponent* Owner)
	: TForm(Owner)
{
	val_ary=NULL;
}
//---------------------------------------------------------------------------
void __fastcall TRegForm::FormShow(TObject *Sender)
{
	if(EditUserName->Text!=""){
		EditUserName->Text="";
	}
	if(EditSN->Text!=""){
        EditSN->Text="";
    }
}
//---------------------------------------------------------------------------
void __fastcall TRegForm::BtnCancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TRegForm::BtnOKClick(TObject *Sender)
{
	if(!letters.IsEmpty()){
		letters="";
	}
	if(4<=EditUserName->Text.Length()&&EditUserName->Text.Length()<=16){
		AnsiString username=EditUserName->Text;
		expand_value(username.c_str());
		convert_to_letter(value_array,len);
		char *ulstr;
		transform_letter(letters.c_str(),&ulstr);
		sn=ulstr;
		delete []ulstr;
		if(sn==(AnsiString)(EditSN->Text)){
			write_reg();
			Form1->set_registered(true);
			Form1->set_user_name(((AnsiString)(EditUserName->Text)).c_str());
			MessageBox(Handle,"Thanks! Registration has succeeded!","Success",MB_OK);
			Close();
        }else{
			MessageBox(Handle,"The sn is wrong!","Failure",MB_OK);
        }
	}else{
		MessageBox(Handle,"The length of string should be between 4 and 16.","",MB_OK);
	}
}
//---------------------------------------------------------------------------
void __fastcall TRegForm::number_to_capital_letter(long number,char *letter)
{
    if(!number){
        *letter='Z';
    }else{
        if(1<=number&&number<=25){
            *letter=(char)(number+64);
        }
    }
}

void __fastcall TRegForm::number_to_column_name(long number,dbl_end_str *des)
{
    if(!number)return;
    char c;
    long remainder,quotient;
    do{
        quotient=number/26;
        remainder=number%26;
        if(!remainder){
            quotient--;
        }
        number_to_capital_letter(remainder,&c);
        apptodes(c,des);
        number=quotient;
    }while(quotient);
}

void __fastcall TRegForm::expand_value(const char *str)
{
	len=str_len(str);
	int num=len;
	value_array=new long[len];
	int i=29;
	int j=99;
	int k=0;
	char c;
	while(c=str[k]){
    	if(i==19){
			i=29;
		}
		if(!j){
			j=99;
		}
		value_array[--num]=(c*i+j);
		i--;
		j--;
		k++;
    }
}

void __fastcall TRegForm::convert_to_letter(long *v_ary,int ary_len)
{
    int i=0;
    dbl_end_str des;
	initdes(&des,12,back);
	char *temp_p;
	while(i<ary_len){
        number_to_column_name(v_ary[i],&des);
		destoch(&des,&temp_p,front);
		letters+=temp_p;
		reinitdes(&des,12,back);
		delete []temp_p;
        i++;
    }
}

inline bool __fastcall TRegForm::odd_or_not(int num)
{
    if(num%2){
        return true;
    }else{
        return false;
    }
}

void __fastcall TRegForm::transform_letter(const char *src,char **dst)
{
    char *temp_str;
    temp_str=*dst=new char[strlen(src)+1];
    char c;
    int i=0;
    while(c=*(src+i)){
        if(!odd_or_not(i)){
            *(temp_str+i)=c-32;
        }else{
            *(temp_str+i)=c;
        }
        i++;
    }
    *(temp_str+i)='\0';
}
//---------------------------------------------------------------------------
void __fastcall TRegForm::form_composed_string()
{
	TDateTime date_time=date_time.CurrentDateTime();
	unsigned short year,month,day,hour,minute,second,millisecond;
	char *str_year,*str_month,*str_day,*str_hour,*str_minute,*str_second;
	date_time.DecodeDate(&year,&month,&day);
	date_time.DecodeTime(&hour,&minute,&second,&millisecond);
	num_to_str(year,&str_year);
	num_to_str(month,&str_month);
	num_to_str(day,&str_day);
	num_to_str(hour,&str_hour);
	num_to_str(minute,&str_minute);
	num_to_str(second,&str_second);
	AnsiString name=EditUserName->Text;
	ary_len=1+str_len(str_minute)+str_len(str_hour)+str_len(str_day)+str_len(str_month)+str_len(str_year)+str_len(name.c_str())+6;
	second_len=str_len(str_second);

	if(!composed_str.IsEmpty()){
    	composed_str="";
	}
	composed_str=str_second;
	composed_str+=(char_to_str('t'),little_str);
	composed_str+=str_minute;
	composed_str+=(char_to_str('r'),little_str);
	composed_str+=str_hour;
	composed_str+=(char_to_str((char)31),little_str);
	composed_str+=name.c_str();
	composed_str+=(char_to_str((char)30),little_str);
	composed_str+=str_year;
	composed_str+=(char_to_str('u'),little_str);
	composed_str+=str_month;
	composed_str+=(char_to_str('e'),little_str);
	composed_str+=str_day;

	delete []str_year;
	delete []str_month;
	delete []str_day;
	delete []str_hour;
	delete []str_minute;
	delete []str_second;

	if(val_ary){
        delete []val_ary;
    }
	val_ary=new int[ary_len];
	val_ary[ary_len-1]=second;
}

inline void __fastcall TRegForm::char_to_str(char c)
{
	little_str[0]=c;
	little_str[1]='\0';
}

inline void __fastcall TRegForm::result_of_mod(const char c,int *result)
{
	*result=c%10;
}

void __fastcall TRegForm::str_to_num(const char *str,int *num)
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

void __fastcall TRegForm::num_to_str(int num,char **str)
{
    dbl_end_str des;
    initdes(&des,12,back);
    inttodes(num,&des);
	destoch(&des,str,front);
	destroyinternal(&des);
}

void __fastcall TRegForm::fill_value_array()
{
	const char *temp_str=composed_str.c_str();
	if(odd_or_not(second_len)){
		val_ary[0]=static_cast<int>(temp_str[second_len])-(val_ary[ary_len-1]%10);
    }else{
		val_ary[0]=static_cast<int>(temp_str[second_len])+(val_ary[ary_len-1]%10);
    }
	int str_i=second_len+1;
	int int_i=1;
	int n;
	for(;str_i<composed_str.Length();int_i++,str_i++){
		result_of_mod(temp_str[str_i-1],&n);
		val_ary[int_i]=encrypt_num(str_i,temp_str[str_i],n);
	}
}

int __fastcall TRegForm::encrypt_num(int i,const char c,int result_mod)
{
	if(odd_or_not(i)){
		return static_cast<int>(c)-result_mod;
    }else{
        return static_cast<int>(c)+result_mod;
    }
}

void __fastcall TRegForm::form_encrypted_string()
{
	if(!encrypted_string.IsEmpty()){
        encrypted_string="";
    }
	int i=0;
	char *little_str;
	while(i<ary_len-1){
		num_to_str(val_ary[i],&little_str);
		encrypted_string+=little_str;
		encrypted_string+="-";
		delete []little_str;
		i++;
	}
	num_to_str(val_ary[i],&little_str);
	encrypted_string+=little_str;
	delete []little_str;
	delete []val_ary;
}

void __fastcall TRegForm::write_reg()
{
	form_composed_string();
	fill_value_array();
	form_encrypted_string();

	TRegistry *reg=new TRegistry;
	reg->RootKey=HKEY_CURRENT_USER;
	try{
		reg->OpenKey("\\Software\\Bookmark Console",true);
		reg->WriteString("registered",encrypted_string.c_str());
	}
	__finally{
		reg->CloseKey();
		delete reg;
    }
}
void __fastcall TRegForm::BtnBuyClick(TObject *Sender)
{
	ShellExecute(Handle,"Open","http://www.winmyth.com/buy.html",NULL,NULL,SW_SHOW);
}
//---------------------------------------------------------------------------

