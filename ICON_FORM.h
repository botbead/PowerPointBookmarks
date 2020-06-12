//---------------------------------------------------------------------------

#ifndef ICON_FORMH
#define ICON_FORMH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
#define ICON_MESSAGE WM_USER+777

class TIconForm : public TForm
{
__published:	// IDE-managed Components
	TPopupMenu *PPMenu;
	TMenuItem *MItem_show;
	TMenuItem *MItem_close;
	TMenuItem *MItem_home;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall MItem_closeClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall MItem_showClick(TObject *Sender);
	void __fastcall MItem_homeClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TIconForm(TComponent* Owner);
	__fastcall ~TIconForm();
	TIcon *icon_bc;
	void virtual __fastcall IconClick(TMessage& msg);
	MESSAGE void __fastcall on_window_restore(TMessage &);
	BEGIN_MESSAGE_MAP
		MESSAGE_HANDLER(ICON_MESSAGE,TMessage,IconClick);
		MESSAGE_HANDLER(WM_SYSCOMMAND,TMessage,on_window_restore);
	END_MESSAGE_MAP(TForm);
};
//---------------------------------------------------------------------------
extern PACKAGE TIconForm *IconForm;
//---------------------------------------------------------------------------
#endif
