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
 *  $Log: keyread.h $
 *  Revision 1.2  2007/08/21 03:30:04  Administrator
 *  base key lok class
 *
 *
 *
*/
//---------------------------------------------------------------------------

#ifndef keyreadH
#define keyreadH

#include "keybase.h"

class TKeyDate : public TObject
{
        typedef TObject Inherited ;

        private:
                static const int BaseYear ;
                int Fyear  ,
                    Fmonth ,
                    Fday   ;

                int Fbinarydate ;
                void __fastcall date2bin(); 
                void __fastcall bin2date(int);
                TDateTime __fastcall GetDate();
                TKeyDate * __fastcall operator=(TKeyDate *);

        public:
                __fastcall TKeyDate  ( TKeyDate * ) ;
                __fastcall TKeyDate  ( int = 0 , int = 0 , int = 0 ) ;
                __fastcall ~TKeyDate ( ) ;
                
        __published:
                __property int BinaryDate = { read = Fbinarydate , write = bin2date } ;
                __property int Year  = { read = Fyear  } ;
                __property int Month = { read = Fmonth } ;
                __property int Day   = { read = Fday   } ;
                __property TDateTime Date  = { read=GetDate };
};
//---------------------------------------------------------------------------

class TUSBKeyRead : public TUSBKeyBase
{
private:
        typedef TUSBKeyBase Inherited ;

        bool         FReadAuth     ;

        TNotifyEvent FKeyRead      ,
                     FKeyNotRead   ;

        int __fastcall GetSerial ( ) ;
        int __fastcall GetDays   ( ) ;

public:
        virtual __fastcall  TUSBKeyRead ( int vc1 , int vc2 , int vc3 , int cid1 , int cid2 , int rc1 , int rc2 , int rc3 ) ;
                __fastcall ~TUSBKeyRead ( ) ;

protected:
        /*static*/ const int
                     RC1  ,
                     RC2  ;

        TKeyDate * tmpDate ;

        TKeyDate * __fastcall GetExpireDate ( ) ;
        int        __fastcall Getlocation   ( ) ;

        virtual void __fastcall DetectKey   ( ) ;

__published:

        __property int CheckKey  = { read = DetectKey    } ;

        __property TNotifyEvent OK   = { read = FKeyFound     , write = FKeyFound    } ;
        __property TNotifyEvent Fail = { read = FKeyNotFound  , write = FKeyNotFound } ;

        __property int SERIAL    = { read = GetSerial } ;  //3  r1
        __property TKeyDate *   ExpireDate    = { read = GetExpireDate } ;
        __property int Days  = { read=GetDays };
        //__property int GETMXUSR  = { read  = } ; 	//12 r1 
        //__property int NETWKCNT  = { read  = } ; 	//20 r1 r2
        //__property int ABSMAXUSR = { read  = } ; 	//32 r1
} ;

//---------------------------------------------------------------------------

#endif

