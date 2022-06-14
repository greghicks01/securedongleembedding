//---------------------------------------------------------------------------
/*
 *                     Copyright © 2007
 *                     Mr Gregory Hicks
 *
 *                 Software Project Engineer
 *                 Mr Gregory Hicks BIT CQU
 *
 *  $Revision: 1.1 $
 *
 *  $Log: keydll.h $
 *  Revision 1.1  2007/08/21 03:30:04  Administrator
 *  Initial revision
 *
 *
 *
*/


#ifndef keydllH
#define keydllH

#include "shfold.h"
#include <vcl.h>

class TUSBKeyDLL : public TComponent
{
        typedef TComponent Inherited ;
        
private:
        
        // DLL Functions signatures
        typedef unsigned ( __stdcall * TKFUNC ) ( int , int , int , int ) ;
        typedef unsigned ( __stdcall * TKEYBD ) ( int ) ;

        TKFUNC  KFUNC ;
        TKEYBD  KEYBD ;

        static const AnsiString
                     DLLName    , // name of DLL
                     keypp      , // PPMON debugger detector
                     keydrv     , // SYS driver
                     keyinf     , // INF file

                     // relative paths
                     keyDrvRel  , // Driver
                     keyInfRel  , // inf
                     keyinst    , // locally held copies
                     
                     // DLL Functions
                     DllF_KFunc ,
                     DllF_Kbd   ;


        bool         DriverIsDirty ,
                     DriversFound  ;

        TNotifyEvent FDLLLoaded    ,
                     FDLLnotLoaded ;

        TShFolder * ShFolder ;

        HINSTANCE   hDLL ;

        AnsiString  F_DLL   ,
                    F_PPMON ,
                    F_INF   ,
                    F_SYS   ;

        void     __fastcall DetectDrivers   ( ) ;
        bool     __fastcall DriverCopy      ( AnsiString , AnsiString ) ;

        int FReturnValue1, FReturnValue2 ;
public:
        virtual  __fastcall  TUSBKeyDLL  ( ) ;
                 __fastcall ~TUSBKeyDLL  ( ) ;

protected:
        void __fastcall KTASK ( int , int , int , int ) ;
        virtual void __fastcall DetectKey() = 0 ;

__published:
        __property int RV1       = { read = FReturnValue1 } ;
        __property int RV2       = { read = FReturnValue2 } ;

        __property TNotifyEvent OK   = { read = FDLLLoaded    , write = FDLLLoaded    } ;
        __property TNotifyEvent Fail = { read = FDLLnotLoaded , write = FDLLnotLoaded } ;
} ;

//---------------------------------------------------------------------------

#endif


