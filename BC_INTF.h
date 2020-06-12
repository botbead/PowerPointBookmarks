//---------------------------------------------------------------------------

#ifndef BC_INTFH
#define BC_INTFH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "img_info.h"
#include "item_info.h"

#include <math.h>
#include <Graphics.hpp>
#include <gdiPlus.h>
#include "PowerPoint_TLB.h"
using namespace Gdiplus;

const int size_big_btn=45;
const int size_small_btn=37;
//---------------------------------------------------------------------------
struct node{
	int value;
	node *next;
};

class TForm1 : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDblClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);

private:	// User declarations
	Gdiplus::GdiplusStartupInput gdi_plus_startup_input;
	ULONG_PTR gdi_plus_token;

	BLENDFUNCTION blend;

	AnsiString top_dir;

	bool MouseLButtonDown;
	TPoint original_pos,current_pos,mouse_down_pos;
	Gdiplus::Region *rgn_for_move;

	char little_str[2];
	int second_len;
	node *reg_link_head;
	AnsiString decrypted_string;
	bool registered;
	AnsiString user_name;

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	__fastcall ~TForm1();

	void __fastcall check_file();
	void __fastcall get_top_dir();
	void __fastcall set_blend();
	void __fastcall draw_images();
	bool __fastcall move_state_machine(int,Gdiplus::Point &,Gdiplus::Graphics &);
	bool __fastcall item_move_state_machine(link_node *,Gdiplus::Point &,Gdiplus::Graphics &);
	void __fastcall draw_text(Gdiplus::Graphics *,item_info *);
	void __fastcall modify_scrollbar_height();
	void __fastcall form_rgn_for_move();

	void __fastcall init_handlers();

	void __fastcall close_form();
	void __fastcall mini_form();
	void __fastcall move_item_up();
	void __fastcall move_item_down();
	void __fastcall add_a_item();
	void __fastcall delete_a_item();
	void __fastcall display_info();
	void __fastcall move_scrollbar();

	void __fastcall write_into_file(const char *,bool);
	void __fastcall fill_contents(const char *,char **);
	void __fastcall replace_bcr();
	void __fastcall str_to_num(const char *,int *);
	void __fastcall num_to_str(int,char* *);
	void __fastcall move_window();

	void __fastcall parse_reg_info();
	void __fastcall form_link_list(const char *);
	void __fastcall clean_str(char *,int);
	void __fastcall decrypt();
	void __fastcall decrypt_num(int,int &,int);
	void __fastcall extract_keys(const char *,char* *,char* *);
	void __fastcall char_to_str(char);
	bool __fastcall odd_or_not(int);
	bool __fastcall compare_string(const char *,const char *);

	void __fastcall set_registered(bool);
	void __fastcall set_user_name(const char *);

	void __fastcall get_little_letters(const char *,char* *);
	void __fastcall crop_string(const char *,char* *,int,int,int,const char *);
	void __fastcall handle_path(const char *,char* *);
	void __fastcall handle_name(const char *,char* *);

	MESSAGE void __fastcall on_window_restore(TMessage &);
	BEGIN_MESSAGE_MAP
		MESSAGE_HANDLER(WM_SYSCOMMAND,TMessage,on_window_restore);
	END_MESSAGE_MAP(TForm);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
static void __fastcall (TForm1::*handlers[8])();
#endif
