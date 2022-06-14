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
 *  $Log: keyread.cpp $
 *  Revision 1.3  2007/08/22 03:34:43  Administrator
 *  updated to remove redundant code
 *
 *  Revision 1.2  2007/08/21 03:39:32  Administrator
 *  read fucnction wrapper
 *
 *
 *
*/
//---------------------------------------------------------------------------
#pragma hdrstop

#include "keyread.h"
//#include <cstdlib>
//using namespace std ;
//---------------------------------------------------------------------------

#pragma package(smart_init)


//---------------------------------------------------------------------------

const int TKeyDate::BaseYear = 1990 ;

//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/


__fastcall TKeyDate::TKeyDate ( TKeyDate * d )
{
        //TODO: Add your source code here
        Fbinarydate = d->Fbinarydate ;
        bin2date(Fbinarydate);
} 
//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/


__fastcall TKeyDate::TKeyDate( int y , int m , int d ):Fyear ( y ) , Fmonth ( m ) , Fday ( d )
{
        //TODO: Add your source code here
        date2bin ( ) ;
}
//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/


__fastcall TKeyDate::~TKeyDate()
{
        //TODO: Add your source code here
}
//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/


TKeyDate * __fastcall TKeyDate::operator=(TKeyDate * lhs )
{
        //TODO: Add your source code here

        Fyear = lhs->Year ;
        Fmonth = lhs->Month ;
        Fday = lhs->Day ;
        return this ;

}
//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/


void __fastcall TKeyDate::date2bin()
{
        //TODO: Add your source code here
        int y = 512 *  ( Fyear==0?0 : Fyear - BaseYear ) ,
            m = 32 * Fmonth ;
        Fbinarydate = static_cast < int > ( y + m + Fday ) ;
}
//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/


void __fastcall TKeyDate::bin2date(int b)
{
        //TODO: Add your source code here
        Fbinarydate = b ;
        Fday   =     Fbinarydate        & 0x1F ;
        Fmonth =   ( Fbinarydate >> 5 ) & 0x0F ;
        Fyear  = ( ( Fbinarydate >> 9 ) & 0x7F ) + BaseYear ;
}
//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/


TDateTime __fastcall TKeyDate::GetDate()
{
        //TODO: Add your source code here
        if ( Fbinarydate != 0 )
                return EncodeDate ( Fyear , Fmonth , Fday ) ;
        else
                return EncodeDate ( 0 , 1 , 1 ) ;
}
//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/


// Demo Dongle Security Constants
/*const int
        TUSBKeyRead :: RC1  = 0X1772 ,
        TUSBKeyRead :: RC2  = 0XC4E6 ;  */
//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/

__fastcall TUSBKeyRead::TUSBKeyRead( int vc1 , int vc2 , int vc3 , int cid1 , int cid2 , int rc1 , int rc2 , int rc3  ) :
           Inherited (  vc1 ,  vc2 ,  vc3 ,  cid1 ,  cid2 ,  rc3  ) , RC1 ( rc1 ) , RC2 ( rc2 )
{
        //TODO: Add your source code here
        FReadAuth = false ;
        tmpDate   = new TKeyDate ;
}
//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/

__fastcall TUSBKeyRead::~TUSBKeyRead()
{
        delete tmpDate ;
}

//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/

void __fastcall TUSBKeyRead::DetectKey ( )
{
        //TODO: Add your source code here

        Inherited::CheckKey ;

        //try read auth
        KTASK ( 2 , RC1 , RC2 , RC3 ) ;

        // test by two serial reads and compare
        int add = abs ( int16rnd % 56 ) ;
        KTASK ( 4 , add , int16rnd , int16rnd ) ;

        int a = RV1 ;

        KTASK ( 4 , add , int16rnd , int16rnd ) ;

        FReadAuth = ( RV1 == a ) ? true : false ;

        if ( FReadAuth )
        {
                if ( FKeyRead )
                        FKeyRead ( this ) ;
        }
        else
                if ( FKeyNotRead )
                        FKeyNotRead ( this ) ;
}
//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/

int __fastcall TUSBKeyRead::GetSerial()
{
        //TODO: Add your source code here
        //SERIAL     	3  r1
        FArg1 = 3;
        KeyFunction ( ) ;
        return RV1 ;
}
//---------------------------------------------------------------------------
/*
 * Purpose:
 * Accepts:
 * Returns:
*/

TKeyDate * __fastcall TUSBKeyRead::GetExpireDate()
{
        //TODO: Add your source code here
        //GETXDATE  = { read  = GetExpireDate } ; 	//8  r1
        FArg1 = 8 ;
        KeyFunction () ;
        tmpDate->BinaryDate = RV1 ;
        return tmpDate ;
}

/*
 * Purpose:
 * Accepts:
 * Returns:
*/

int __fastcall TUSBKeyRead::GetDays()
{
        //TODO: Add your source code here
        int diff =-1;
        TDate t ;

        TKeyDate * exp = GetExpireDate() ;

        if ( exp->BinaryDate != 0 && FReadAuth)
        {
                // difference between today and expire
                if ( TryEncodeDate(exp->Year , exp->Month , exp->Day , t ) )
                {
                        diff = t - Date() ;
                }
                return diff ;
        }
        else
                return -1 ;
}
