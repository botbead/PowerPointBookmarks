object IconForm: TIconForm
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'Powerpoint Bookmark Console'
  ClientHeight = 303
  ClientWidth = 427
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PPMenu: TPopupMenu
    Left = 200
    Top = 136
    object MItem_show: TMenuItem
      Caption = 'Show'
      OnClick = MItem_showClick
    end
    object MItem_home: TMenuItem
      Caption = 'Home Page'
      OnClick = MItem_homeClick
    end
    object MItem_close: TMenuItem
      Caption = 'Close'
      OnClick = MItem_closeClick
    end
  end
end
