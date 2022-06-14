//---------------------------------------------------------------------------
/*
 *                     Copyright © 2007
 *                  Gregory Security Utilities
 *
 *                 Software Project Engineer
 *                 Mr Gregory Hicks BIT CQU
 *
 *  $Revision: 1.3 $
 *
 *  $Log: testkey.cpp $
 *  Revision 1.3  2007/08/22 03:34:43  Administrator
 *  updated to remove redundant code
 *
 *  Revision 1.2  2007/08/21 03:39:32  Administrator
 *  test program
 *
 *  Revision 1.1  2007/07/09 08:59:09  Administrator
 *  Initial revision
 *
 *
 *
*///---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "testkey.h"
#include "math.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define ValidateCode1 0X488B // Codes used as part of active algorithm to
#define ValidateCode2 0XFEE2 // check for installation of proper device
#define ValidateCode3 0XEF90
#define ClientIDCode1 0XD882
#define ClientIDCode2 0X5E01
#define ReadCode1     0X1772 // Codes used to authorize read operations
#define ReadCode2     0XC4E6
#define ReadCode3     0XBCF8
#define WriteCode1    0X30A0 // Codes used to authorize write operations
#define WriteCode2    0X3C89
#define WriteCode3    0X0A2B


//---------------------------------------------------------------------------
void Reverse ( AnsiString & r )
{
        AnsiString t = r ;
        int start = 1 , stop = t.Length() ;

        while ( stop < start )
        {
                char   c    = t [ start ] ;
                t [ start ] = t [ stop  ] ;
                t [ stop  ] = c           ;
        }
        r = t ;
}
//---------------------------------------------------------------------------

const unsigned HexToInt ( const AnsiString tr )
{
        const AnsiString hexDig = "0123456789ABCDEF" ;

        AnsiString h = UpperCase ( tr ) ;

        Reverse ( h ) ;

        unsigned t = 0 ;

        for ( int i = 0 ; i < h.Length() ; i ++ )
        {
                t += ( hexDig . Pos ( h [ i + 1 ] ) - 1 ) << ( 4 * i ) ;
        }
        return t ;
}
//---------------------------------------------------------------------------

TForm1 *Form1;
//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{ 
}
//---------------------------------------------------------------------------

__fastcall TForm1::~TForm1()
{
        //TODO: Add your source code here
        delete USBKey ;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        Timer1->Enabled = false ;

        USBKey = new TUSBKeyWrite ( ValidateCode1,ValidateCode2,ValidateCode3,ClientIDCode1,ClientIDCode2,ReadCode1,ReadCode2,ReadCode3,WriteCode1,WriteCode2,WriteCode3,true );
        USBKey->OK   = KeyFound    ;
        USBKey->Fail = KeyNotFound ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::KeyFound ( TObject * Sender )
{
        //TODO: Add your source code here
        Shape1->Brush->Color = clLime ;
} 
//---------------------------------------------------------------------------

void __fastcall TForm1::KeyNotFound(TObject * Sender )
{
        //TODO: Add your source code here
        Shape1->Brush->Color = clRed ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject * Sender )
{
        USBKey->CheckKey  ;
}
//---------------------------------------------------------------------------

