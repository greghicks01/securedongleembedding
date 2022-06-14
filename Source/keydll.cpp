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
 *  $Log: keydll.cpp $
 *  Revision 1.2  2007/08/22 03:34:43  Administrator
 *  updated to remove redundant code
 *
 *  Revision 1.1  2007/08/21 03:39:32  Administrator
 *  Initial revision
 *
 *
 *
*/
//---------------------------------------------------------------------------
#pragma hdrstop

#include "keydll.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

// Dongle path and file constants
const AnsiString pathDelim = "\\" ;

const AnsiString
        TUSBKeyDLL :: DLLName    = "KL2DLL32.DLL" , // %SYS%
        TUSBKeyDLL :: keypp      = "PPMON.EXE"    , // %SYS%
        TUSBKeyDLL :: keydrv     = "USBKEY.SYS"   , // %SYS%/drivers
        TUSBKeyDLL :: keyinf     = "USBKEY.INF"   , // %win%/inf
        TUSBKeyDLL :: keyDrvRel  = "drivers"      ,
        TUSBKeyDLL :: keyInfRel  = "inf"          ,
        TUSBKeyDLL :: keyinst    = "keyinst"      ,

        TUSBKeyDLL :: DllF_KFunc = "KFUNC"        ,
        TUSBKeyDLL :: DllF_Kbd   = "KEYBD"        ;


//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/

__fastcall TUSBKeyDLL::TUSBKeyDLL() : Inherited ( NULL )
{
        //TODO: Add your source code here
        DriverIsDirty = false ;

        ShFolder = new TShFolder ;

        F_DLL    /*f1*/  = ShFolder->System  + pathDelim + DLLName ;
        F_PPMON  /*f2*/  = ShFolder->System  + pathDelim + keypp ;
        F_INF    /*f3*/  = ShFolder->System  + pathDelim + keyDrvRel + pathDelim + keydrv ;
        F_SYS    /*f4*/  = ShFolder->Windows + pathDelim + keyInfRel + pathDelim + keyinf ;

        DetectDrivers ( ) ;

}
//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/


__fastcall TUSBKeyDLL::~TUSBKeyDLL()
{
        //TODO: Add your source code here

        FreeLibrary ( hDLL ) ;
        delete ShFolder  ;
}
//---------------------------------------------------------------------------

/*
 * Purpose : Generic copy
 * Accepts : fully qualified paths to original and copy
 * Returns :
*/
void __fastcall TUSBKeyDLL::DetectDrivers()
{
        //TODO: Add your source code here

        if ( FileExists ( F_DLL ) && FileExists ( F_PPMON ) &&
             FileExists ( F_INF ) && FileExists ( F_SYS )    )
        {
                hDLL = LoadLibrary ( DLLName.c_str() ) ;

                if ( hDLL != NULL )
                {
                        KFUNC = ( TKFUNC ) GetProcAddress ( hDLL , DllF_KFunc.c_str ( ) ) ;
                        KEYBD = ( TKEYBD ) GetProcAddress ( hDLL , DllF_Kbd.c_str ( )   ) ;
                }
                if ( FDLLLoaded )
                        FDLLLoaded ( this ) ;
        }
        else
        if ( FDLLnotLoaded )
                FDLLnotLoaded ( this ) ;
}
//---------------------------------------------------------------------------

/*
 * Purpose : Generic copy
 * Accepts : fully qualified paths to original and copy
 * Returns :
*/

void __fastcall TUSBKeyDLL::KTASK ( int arg1 , int arg2 , int arg3 , int arg4 )
{
        //TODO: Add your source code here
        if ( KFUNC )
        {
                unsigned RV = KFUNC ( arg1 , arg2 , arg3 , arg4 ) ;
                //int ec = GetLastError() ;
                FReturnValue1 = ( RV & 0XFFFF ) ;
                FReturnValue2 = (  RV  >> 16  ) ;
        }
} 

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

/*
/*
 * Purpose:
 * Accepts:
 * Returns:


void __fastcall TUSBKey::InstallDrivers()
{
        //TODO: Add your source code here
        AnsiString FromDir = ExtractFilePath ( Application->ExeName ) +  keyinst + pathDelim;

        DriverCopy ( FromDir + F_DLL    , ShFolder->System  + pathDelim + F_DLL   ) ;
        DriverCopy ( FromDir + F_PPMON  , ShFolder->System  + pathDelim + F_PPMON ) ;
        DriverCopy ( FromDir + F_INF    , ShFolder->Windows + keyInfRel + pathDelim + F_INF  ) ;
        DriverCopy ( FromDir + F_SYS    , ShFolder->System  + keyDrvRel + pathDelim + F_SYS ) ;

        DriverIsDirty = true ;
} */

//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:


bool __fastcall TUSBKey::DriverCopy(AnsiString from , AnsiString to )
{
        //DONE: Add your source code here
        return CopyFile ( from.c_str() , to.c_str() , TRUE ) ;
} */
//---------------------------------------------------------------------------

/*
 * Purpose : Generic copy
 * Accepts : fully qualified paths to original and copy
 * Returns :
*/
/*
void __fastcall TUSBKeyBase::RemoveDrivers()
{
        //TODO: Add your source code here
        if ( DriverIsDirty )
        {
                // unload the driver
                DeleteFile ( ShFolder->System  + pathDelim + F_DLL   ) ;
                DeleteFile ( ShFolder->System  + pathDelim + F_PPMON ) ;
                DeleteFile ( ShFolder->Windows + keyInfRel + pathDelim + F_INF ) ;
                DeleteFile ( ShFolder->System  + keyDrvRel + pathDelim + F_SYS ) ;
        }
} */

