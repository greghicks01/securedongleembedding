object Form1: TForm1
  Left = 201
  Top = 110
  Width = 270
  Height = 284
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Shape1: TShape
    Left = 112
    Top = 200
    Width = 25
    Height = 25
    Brush.Color = clSilver
    Shape = stCircle
  end
  object Button1: TButton
    Left = 8
    Top = 192
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Memo1: TMemo
    Left = 8
    Top = 8
    Width = 233
    Height = 177
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
  end
  object Timer1: TTimer
    Interval = 500
    OnTimer = Timer1Timer
    Left = 16
    Top = 16
  end
end
