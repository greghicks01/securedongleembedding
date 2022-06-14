//---------------------------------------------------------------------------
/*
 *                     Copyright © 2007
 *                     Mr Gregory Hicks
 *
 *                 Software Project Engineer
 *                 Mr Gregory Hicks BIT CQU
 *
 *  $Revision: 1.2 $
 *
 *  $Log: keybase.h $
 *  Revision 1.2  2007/08/21 03:30:04  Administrator
 *  base key lok class
 *
 *
 *
*/


#ifndef keybaseH
#define keybaseH

#include "keydll.h"
#include <vcl.h>
#include <math.h>

class TUSBKeyBase : public TUSBKeyDLL
{
        typedef TUSBKeyDLL Inherited ;
        
private:
        TNotifyEvent FKeyFound     ,
                     FKeyNotFound  ;

        bool         FKeyCheck     ;

        void       __fastcall USBCheck   ( ) ;
        int inline __fastcall Int16Rnd   ( ) ;
        void       __fastcall StringRev(AnsiString & );

public:
        virtual  __fastcall  TUSBKeyBase ( int vc1 , int vc2 , int vc3 , int cid1 , int cid2 , int rc3 ) ;
                 __fastcall ~TUSBKeyBase ( ) ;
        int __fastcall HexToInt (AnsiString) ;

protected:
        /*static*/ const int
                     VC1  ,
                     VC2  ,
                     VC3  ,
                     CID1 ,
                     CID2 ,
                     RC3  ;

        int          FArg1 ,
                     FArg2 ,
                     FArg3 ,
                     FArg4 ;

        void    __fastcall KeyFunction  ( ) ;
        int     __fastcall RotateLeft16 ( int , int ) ;
        virtual void __fastcall DetectKey  ( ) ;

__published:
        __property int CheckKey  = { read = DetectKey } ;
        __property int int16rnd  = { read = Int16Rnd  } ;

        __property TNotifyEvent OK   = { read = FKeyFound     , write = FKeyFound    } ;
        __property TNotifyEvent Fail = { read = FKeyNotFound  , write = FKeyNotFound } ;
} ;
//---------------------------------------------------------------------------

#endif


