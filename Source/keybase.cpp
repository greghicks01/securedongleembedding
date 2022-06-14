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
 *  $Log: keybase.cpp $
 *  Revision 1.3  2007/08/22 03:34:43  Administrator
 *  updated to remove redundant code
 *
 *  Revision 1.2  2007/08/21 03:39:32  Administrator
 *  base key functions before driving the DLL
 *
 *
 *
*/
//---------------------------------------------------------------------------
#pragma hdrstop

#include "keybase.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
// Demo Dongle Security Constants
/*const int
        TUSBKeyBase :: VC1  = 0X488B ,
        TUSBKeyBase :: VC2  = 0XFEE2 ,
        TUSBKeyBase :: VC3  = 0XEF90 ,
        TUSBKeyBase :: CID1 = 0XD882 ,
        TUSBKeyBase :: CID2 = 0X5E01 ,
        TUSBKeyBase :: RC3  = 0XBCF8 ;   */

//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/



__fastcall TUSBKeyBase::TUSBKeyBase( int vc1 , int vc2 , int vc3 , int cid1 , int cid2 , int rc3 ) : Inherited ( ) ,
VC1 ( vc1 ), VC2 ( vc2 ), VC3 ( vc3 ), CID1 ( cid1 ), CID2 ( cid2 ), RC3 ( rc3 )
{
        //TODO: Add your source code here
        FKeyCheck     = false ;
}
//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/


__fastcall TUSBKeyBase::~TUSBKeyBase()
{
        //TODO: Add your source code here
        FArg1 = -1 ;
        KeyFunction ( ) ;
}
//---------------------------------------------------------------------------

/*
 * Purpose : 
 * Accepts : 
 * Returns :
*/

int __fastcall TUSBKeyBase::RotateLeft16 ( int rotateMe , int byMe )
{
        //TODO: Add your source code here
        int LocalTarget, HighBit;


        LocalTarget = rotateMe;

        for ( int i = 0 ; i < byMe ; i++)
        {
                HighBit = LocalTarget & 0x8000 ;
                LocalTarget = ( LocalTarget << 1 ) + ( HighBit >> 15 ) ;
        }

        return ( LocalTarget & 0xFFFF ) ;
}

//---------------------------------------------------------------------------

/*
 * Purpose :
 * Accepts :
 * Returns :
*/

void __fastcall TUSBKeyBase::DetectKey(  )
{
        //TODO: Add your source code here
        FKeyCheck = false ;
        int tries = 5 ;
        while ( ! FKeyCheck && tries-- > 0 )
                USBCheck ( ) ;

        if ( FKeyCheck )
        {
                if ( FKeyFound )
                        FKeyFound ( this ) ;
        }
        else
        {
                if ( FKeyNotFound )
                        FKeyNotFound (this ) ;
        }
}
//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/


void __fastcall TUSBKeyBase::USBCheck()
{
        //TODO: Add your source code here
        Sleep ( 500 ) ;
        KTASK ( 1 , VC1 , VC2 , VC3 ) ;
        KTASK ( RC3 ^ RV2 ^ RotateLeft16 ( RV1 , RV2 & 0x7 ) ,
                RotateLeft16 ( RV2 , RV1 & 0xF ) ,
                RV1 ^ RV2 ,
                0
              ) ;

        if (  RV1 == CID1 && RV2 == CID2 )
                FKeyCheck = true ;
        else
                FKeyCheck = false ;

}

//---------------------------------------------------------------------------

/*
 * Purpose : 
 * Accepts : 
 * Returns :
*/

void __fastcall TUSBKeyBase::KeyFunction ( )
{
        //TODO: Add your source code here
        if ( FArg1 == 6 )
        {
                FArg4 = 4 ;
        }
        else
        if ( FArg1 == 10 )
        {
                FArg2 = 2 ;
                FArg4 = 4 ;
        }
        else
        if ( FArg1 == 4 || FArg1 == 7 || FArg1 == 11 )
        {
                FArg3 = 3 ;
                FArg4 = 4 ;
        }
        else
        if ( FArg1 == -1 || FArg1 ==  3 || FArg1 ==  8 ||
             FArg1 ==  9 || FArg1 == 12 || FArg1 == 13 ||
             FArg1 == 14 || FArg1 == 18 || FArg1 == 19 ||
             FArg1 == 20 || FArg1 == 32                   )
        {
                FArg2 = 2 ;
                FArg3 = 3 ;
                FArg4 = 4 ;
        }

        KTASK ( FArg1 , FArg2 , FArg3 , FArg4 ) ;
}
//---------------------------------------------------------------------------

/*
 * Purpose : 
 * Accepts : 
 * Returns :
*/

int __fastcall TUSBKeyBase::Int16Rnd ( )
{
        //TODO: Add your source code here
        return  rand ( ) % 0xFFFF ;
}
//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/


int __fastcall TUSBKeyBase::HexToInt(AnsiString value)
{
        //TODO: Add your source code here
        // Length to be 4 or 8...
        StringRev ( value ) ;

        AnsiString v = "0123456789ABCDEF" ;

        int answer = 0 ;

        for ( int i = 0 ; i < value.Length() ; i++ )
        {
                answer += (int) pow ( 16 , i ) * ( v.Pos ( value [ i + 1 ] ) - 1 ) ;
        }
        return answer ;
} 
//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/


void __fastcall TUSBKeyBase::StringRev(AnsiString & v)
{
        //TODO: Add your source code here
        for ( int i = 1 , j = v.Length() ; i < j ; i++ , j-- )
        {
                char t  = v [ i ] ;
                v [ i ] = v [ j ] ;
                v [ j ] = t       ;
        }
} 
//---------------------------------------------------------------------------
