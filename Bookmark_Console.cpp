//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("ICON_FORM.cpp", IconForm);
USEFORM("BC_INTF.cpp", Form1);
USEFORM("REG_FORM.cpp", RegForm);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();

		Application->Title="Bookmark Console";
		CreateMutex(NULL,False,"Bookmark Console");
		if(GetLastError()==ERROR_ALREADY_EXISTS){
			MessageBox(Application->Handle,"The Tool is running!","Warning",MB_OK|MB_ICONWARNING);
			return 0;
		}

		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TIconForm), &IconForm);
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TRegForm), &RegForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
