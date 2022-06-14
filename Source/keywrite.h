//---------------------------------------------------------------------------
/*
 *                     Copyright © 2007
 *                     Mr Gregory Hicks
 *
 *                 Software Project Engineer
 *                 Mr Gregory Hicks BIT CQU
 *
 *  $Revision: 1.3 $
 *
 *  $Log: keywrite.h $
 *  Revision 1.3  2007/08/22 03:34:06  Administrator
 *  updated output and input data
 *
 *  Revision 1.2  2007/08/21 03:30:04  Administrator
 *  Wrapper around wite functionality of KEYLOK product
 *
 *
 *
*/
//---------------------------------------------------------------------------

#ifndef keywriteH
#define keywriteH

#include "keyread.h"
#include <vcl.h>

class TUSBKeyWrite : public TUSBKeyRead
{
private:
        typedef TUSBKeyRead Inherited ;

        int     WC1  ,
                WC2  ,
                WC3  ;

        bool    FWriteAuth    ;

        TNotifyEvent FKeyFound     ,
                     FKeyNotFound  ;

        TNotifyEvent FCheckLease;
        int FExpireIn;
        AnsiString FUpdate;
        bool FTest;

        void       __fastcall Setmem             ( int address , int value ) ;
        int        __fastcall Getmem             ( int address ) ;
        void       __fastcall GetCheckLease      ( ) ;

        void       __fastcall SetExpireDate      ( TKeyDate * kd ) ;
        TKeyDate * __fastcall GetExpireDate      ( ) ;

        int        __fastcall GetDECMEM          ( int ) ;
        int        __fastcall GetINCMEM          ( int index        ) ;

        void       __fastcall SetExpireIn        ( int value ) ;

        AnsiString __fastcall GetRegisterRequest ( ) ;
        //void       __fastcall SetRegister        ( AnsiString value ) ;
        //AnsiString __fastcall GetRegister        ( ) ;
        AnsiString __fastcall GetUpdate          ( ) ;
        void       __fastcall SetUpdate          ( AnsiString value ) ;
        void       __fastcall SetWriteKey        ( AnsiString value ) ;
        void       __fastcall SetKeyData         ( AnsiString value ) ;
        AnsiString __fastcall GetKeyData         ( ) ;

public:
        virtual __fastcall  TUSBKeyWrite ( int vc1 , int vc2 , int vc3 , int cid1 , int cid2 , int rc1 , int rc2 , int rc3  , int wc1 , int wc2 , int wc3 , bool ) ;
                __fastcall ~TUSBKeyWrite ( ) ;


protected:
        virtual void    __fastcall DetectKey    ( ) ;

__published:

        //__property         WA	      	5
        // write autorisation
        
        __property int CheckKey  = { read=DetectKey };

        __property TNotifyEvent OK    = { read = FKeyFound     , write = FKeyFound     } ;
        __property TNotifyEvent Fail  = { read = FKeyNotFound  , write = FKeyNotFound  } ;

        __property int KEYMEM [ int address ] = { read = Getmem  , write = Setmem };  // 4 and 6
        __property int DECMEM [ int address ] = { read = GetDECMEM } ; // 7
        __property int INCMEM [ int address ] = { read = GetINCMEM } ;

        __property TKeyDate *   keyDate    = { read = GetExpireDate , write = SetExpireDate } ; //8  r1 //10

        __property int CKLEASE   = { read  = GetCheckLease } ;
        __property int ExpireIn  = { write=SetExpireIn } ;
        //__property AnsiString WriteKey  = { write = SetWriteKey };
        //__property AnsiString KeyData  = { read=GetKeyData, write=SetKeyData };	//9  r1 r2!=0=error -4 ok

        //__property int SETXDATE  = { write = } ; 	//10
        //__property int SETMXUSR  = { write = } ; 	//11
        //__property int REMUPUSR1 = { read  = } ; 	//13 r1 r2
        //__property int REMUPUSR2 = { read  = } ; 	//14 r1 r2
        //__property int REMUPUSR3 = { read  = } ; 	//15 r1 r2
        //__property int REMUPCLI1 = { read  = } ; 	//16 r1=0 OK
        //__property int REMUPCLI2 = { read  = } ;  //17 r1 r2 High Bit!=0 = error
        //__property int REMUPCLI3 = { read  = } ; 	//18 r1 r2


} ;

//---------------------------------------------------------------------------

#endif

