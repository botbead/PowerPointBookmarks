//---------------------------------------------------------------------------

#ifndef REG_FORMH
#define REG_FORMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "dbl_end_str.h"
//---------------------------------------------------------------------------
class TRegForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TEdit *EditUserName;
	TEdit *EditSN;
	TButton *BtnOK;
	TButton *BtnCancel;
	TButton *BtnBuy;
	void __fastcall BtnCancelClick(TObject *Sender);
	void __fastcall BtnOKClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnBuyClick(TObject *Sender);
private:	// User declarations
	long *value_array;
	int len;
	AnsiString letters;
	AnsiString sn;

	char little_str[2];
	int *val_ary;
	int ary_len;
	int second_len;
	AnsiString composed_str;
	AnsiString encrypted_string;
public:		// User declarations
	__fastcall TRegForm(TComponent* Owner);
	void __fastcall number_to_capital_letter(long,char *);
	void __fastcall number_to_column_name(long,dbl_end_str *);
	void __fastcall expand_value(const char *);
	void __fastcall convert_to_letter(long *,int);
	bool __fastcall odd_or_not(int);
	void __fastcall transform_letter(const char *,char **);

	void __fastcall form_composed_string();
	void __fastcall char_to_str(char);
	void __fastcall result_of_mod(const char ,int *);
	void __fastcall str_to_num(const char *,int *);
	void __fastcall num_to_str(int,char* *);
	void __fastcall fill_value_array();
	int __fastcall encrypt_num(int,const char,int);
	void __fastcall form_encrypted_string();
	void __fastcall write_reg();
};
//---------------------------------------------------------------------------
extern PACKAGE TRegForm *RegForm;
//---------------------------------------------------------------------------
#endif
