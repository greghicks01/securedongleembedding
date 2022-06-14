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
 *  $Log: testkey.h $
 *  Revision 1.3  2007/08/22 03:34:06  Administrator
 *  updated test methods to include write back to key
 *
 *  Revision 1.2  2007/08/21 03:30:04  Administrator
 *  Test program
 *
 *  Revision 1.1  2007/07/09 08:59:05  Administrator
 *  Initial revision
 *
 *
 *
*///---------------------------------------------------------------------------

#ifndef testkeyH
#define testkeyH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "keywrite.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTimer  * Timer1  ;
        TButton * Button1 ;
        TShape  * Shape1  ;
        TMemo *Memo1;

        void __fastcall Timer1Timer  ( TObject *Sender ) ;
        void __fastcall Button1Click ( TObject *Sender ) ;

private:   	// User declarations

        void    __fastcall KeyFound(TObject *);
        virtual __fastcall ~TForm1();
        void    __fastcall KeyNotFound(TObject *);
        void    __fastcall KeyRead(TObject *);
        void    __fastcall KeyWrite(TObject *);
        void    __fastcall KeyNotRead(TObject *);
        void    __fastcall KeyNotWrite(TObject *);
        void    __fastcall DLLLoaded(TObject *);
        void    __fastcall DLLNotLoaded(TObject *);

public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        TUSBKeyWrite * USBKey ;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
