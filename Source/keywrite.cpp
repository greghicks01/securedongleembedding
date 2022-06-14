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
 *  $Log: keywrite.cpp $
 *  Revision 1.3  2007/08/22 03:34:43  Administrator
 *  updated to remove redundant code
 *
 *  Revision 1.2  2007/08/21 03:39:32  Administrator
 *  key write functions wrapped.
 *
 *
 *
*/
//---------------------------------------------------------------------------
#pragma hdrstop

#include "keywrite.h"
#include <cstdlib>
using namespace std ;
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
/*
* Purpose :
* Accepts :
* Returns :
*/
__fastcall TUSBKeyWrite::TUSBKeyWrite( int vc1 , int vc2 , int vc3 , int cid1 , int cid2 , int rc1 , int rc2 , int rc3  , int wc1 , int wc2 , int wc3 , bool test ) :
                         Inherited ( vc1 , vc2 , vc3 , cid1 , cid2 , rc1 , rc2 , rc3 ), FTest ( test ) , WC1 ( wc1 ) , WC2 ( wc2 ) , WC3 ( wc3 )
{
        //TODO: Add your source code here
        FWriteAuth    = false ;
}
//---------------------------------------------------------------------------
 
/*
* Purpose :
* Accepts :
* Returns :
*/
__fastcall TUSBKeyWrite::~TUSBKeyWrite()
{
        //TODO: Add your source code here
}
//---------------------------------------------------------------------------
 
/*
* Purpose :
* Accepts :
* Returns :
*/
void __fastcall TUSBKeyWrite::DetectKey ( )
{
        //TODO: Add your source code here

        Inherited::CheckKey ;

        // try write authorisation
        KTASK ( 5 , WC1 , WC2 , WC3 ) ;

        int add = abs ( int16rnd % 56 ) , //location ,
            newval = int16rnd   ,
            dat = newval        ,
            val                 ;

        // Test Write Authorisation
        // read data
        val = Getmem ( add ) ;
        // write new data
        Setmem ( add , newval ) ;
        newval = Getmem ( add ) ;
        // reset mem
        Setmem ( add , val ) ;

        FWriteAuth = ( newval == dat ) ? true : false ;

        if ( FWriteAuth )
        {
                if ( FKeyFound )
                        FKeyFound ( this ) ;
        }
        else
                if ( FKeyNotFound )
                        FKeyNotFound ( this ) ;

}
//---------------------------------------------------------------------------
 
/*
* Purpose :
* Accepts :
* Returns :
*/
void __fastcall TUSBKeyWrite::Setmem( int __index, int value )
{
        //TODO: Add your source code here
        FArg1 = 6 ;
        FArg2 = __index ;
        FArg3 = value ;

        KeyFunction ( ) ;
}
//---------------------------------------------------------------------------
 
/*
* Purpose :
* Accepts :
* Returns :
*/
int __fastcall TUSBKeyWrite::Getmem( int __index )
{
        //TODO: Add your source code here
        FArg1 = 4 ;
        FArg2 = __index ;

        KeyFunction ( ) ;
        
        return RV1 ;
} 
//---------------------------------------------------------------------------

/*
* Purpose :
* Accepts :
* Returns :
*/
void __fastcall TUSBKeyWrite::SetExpireDate( TKeyDate * date )
{
        //TODO: Add your source code here
        //GETXDATE  = { read  = GetExpireDate } ; 	//10
        FArg1 = 10 ;
        FArg3 = date->BinaryDate ;

        KeyFunction () ;
}
//---------------------------------------------------------------------------
 
/*
* Purpose :
* Accepts :
* Returns :
*/
TKeyDate * __fastcall TUSBKeyWrite::GetExpireDate( )
{
        //TODO: Add your source code here
        //GETXDATE  = { read  = GetExpireDate } ; 	//8
        FArg1 = 8 ;

        KeyFunction ( ) ;

        tmpDate->BinaryDate = RV1 ;

        return tmpDate ;
}
//---------------------------------------------------------------------------

/*
* Purpose :
* Accepts :
* Returns :
*/
void __fastcall TUSBKeyWrite::GetCheckLease()
{
        //TODO: Add your source code here
        //9  r1 r2!=0=error}
        FArg1 = 9 ;

        KeyFunction ( ) ;

        if ( RV2 == 0xFFFE || RV2 == 0xFFFD || RV2 == 0xFFFB )
        {
                if ( FKeyNotFound )
                        FKeyNotFound ( this );
        }else
                if ( FKeyFound )
                        FKeyFound ( this );

}
//---------------------------------------------------------------------------

/*
* Purpose :
* Accepts :
* Returns :
*/
int __fastcall TUSBKeyWrite::GetDECMEM(int address)
{
        //TODO: Add your source code here
        FArg1 = 7 ;
        FArg2 = address ;

        KeyFunction ( ) ;

        return RV1 ;
}
//---------------------------------------------------------------------------

/*
* Purpose :
* Accepts :
* Returns :
*/
void __fastcall TUSBKeyWrite::SetExpireIn(int value)
{
        if(FExpireIn != value) {
                FExpireIn = value;
                TDate t = Date() + FExpireIn ;
                WORD y = 0 , m = 0 , d = 0 ;
                DecodeDate ( t , y , m , d ) ;
                TKeyDate * kd = new TKeyDate ( y , m , d ) ;
                SetExpireDate ( kd ) ;
                delete kd ;
        }
} 
//---------------------------------------------------------------------------

/*
* Purpose :
* Accepts :
* Returns :
*/    /*
void __fastcall TUSBKeyWrite::SetKeyData(AnsiString a)
{
        //TODO: Add your source code here
        /* builds structure
                      Pre - Decode
            +---------------------------------------------------+
            |                   Scrambled Data                  |
            +---------------------------------------------------+
                      Post - Decode
            +------+------+------+------------------+-----+-----+
            | Date | Time |  Len |     Key Data     | MD5 | Pad |
            |  8   |  8   |   8  |        Len       |  32 |  XX |
            +------+------+------+------------------+-----+-----+
                          +------+
                          |  Len |
                          |   8  |
                          +------+
            +------+------+------+------------------+
            | Date | Time |  Len |     Key Data     |
            |  8   |  8   |   8  |        Len       |
            +------+------+------+------------------+
                                                    +-----+
                                                    | MD5 |
                                                    |  32 |
                                                    +-----+
                                 +------------------+
                                 |     Key Data     |
                                 |        Len       |
                                 +------------------+

                                Key Data
                              +----+-----+++++++++++++
                              | SN | LD  |  0 - 55   |
                              |  4 |  4  |   224     |
                              +----+-----+++++++++++++
        */  /*

        AnsiString key , A , B , C , D ;

        // blowfish key data
        for ( int x = 5 ; x < 13 ; x++ )
                key += IntToHex ( KEYMEM [ x ] , 4 ) ;

        TBlowFish * b = new TBlowFish ( key ) ;

        b->decyph = a         ;
        a         = b->decyph ;

        delete b ;

        A = a.SubString ( 17               , 8                  ) ; // length of data
        B = a.SubString ( 17               , 8 + HexToInt ( A ) ) ; // length + data
        C = a.SubString ( 17 + B.Length()  , 32                 ) ; // MD5 hash
        D = a.SubString ( 25               , HexToInt ( A )     ) ; // data

        TMD5Digest * MD5  = new TMD5Digest ;
        MD5->InString     = a.SubString ( 1 , 16 ) + B  ;
        AnsiString newMD5 = UpperCase   ( MD5->MD5Str ) ;
        delete MD5 ;

        // Tamper Test
        if ( newMD5 != C )
        {
                if ( Fail )
                        Fail ( this ) ;
                return ;
        }

        key = D.SubString( 1 , 4 ) ; // serial

        // serial match test
        if ( FTest )
        {
                return ;
        }
        if ( IntToHex ( SERIAL , 4 ) != key )
        {
                WORD y , m , d ;
                DecodeDate ( Now() , y , m , d ) ;
                TKeyDate * t = new TKeyDate ( 1990 , m , d ) ;
                keyDate      = t ;
                delete t ;

                if ( Fail )
                        Fail ( this ) ;
                return ;
        }
        ExpireDate->BinaryDate = HexToInt ( D.SubString( 5 , 4 ) ) ;
        keyDate = ExpireDate ;

        for ( int x = 0 ; x < 56 ; x++ )
                KEYMEM [ x ] = HexToInt ( D.SubString( 9 + 4 * x , 4 ) ) ;
}   */
//---------------------------------------------------------------------------  
/*
* Purpose :
* Accepts :
* Returns :
*/  /*
AnsiString __fastcall TUSBKeyWrite::GetKeyData()
{
        //TODO: Add your source code here

        /* builds structure
                      Key Data
            +----+-----+++++++++++++
            | SN | LD  |  0 - 55   |
            |  4 |  4  |   224     |
            +----+-----+++++++++++++
                      Pre - Encode
                              +------------------+
                              |     Key Data     |
                              +------------------+ 
                          +---+
                          |Len|
                          | 8 |
                          +---+
            +------+------+
            | Date | Time |
            |  8   |  8   |
            +------+------+
            +------+------+------+------------------+
            | Date | Time |  Len |     Key Data     |
            |  8   |  8   |   8  |       Len        |
            +------+------+------+------------------+
                                                    +-----+
                                                    | MD5 |
                                                    | 32  |
                                                    +-----+
            +------+------+------+------------------+-----+
            | Date | Time |  Len |     Key Data     | MD5 |
            |  8   |  8   |   8  |       Len        | 32  |
            +------+------+------+------------------+-----+
                      Post - Encode
            +----------------------------------------------+
            |                Scrambled Data                |
            +----------------------------------------------+

        */  /*

        // Read of Serial, Date and 0 to 55
        AnsiString a = IntToHex ( SERIAL , 4 ) ;
        a += IntToHex ( ExpireDate->BinaryDate , 4 ) ;
        for ( int x = 0 ; x < 56 ; x++ )
                  a += IntToHex ( KEYMEM [ x ] , 4 ) ;

        // prefix key data with length
        a = IntToHex ( a.Length() , 8 ) + a ;

        // prefix unique part of signature
        unsigned short y = 0 , m = 0 , d = 0 , hour = 0 , min = 0 , sec = 0 , msec = 0;

        DecodeDate ( Date() , y    , m   , d )           ;
        DecodeTime ( Time() , hour , min , sec ,  msec ) ;
        int dt1 = msec + ( sec << 10 ) + ( min << 16 ) + ( hour << 22 ) + ( d << 26 ) ,
            dt2 = m + y << 4;
        a = IntToHex ( dt1 , 8 ) + IntToHex ( dt2 , 8 ) + a ;

        // hash signature include length
        TMD5Digest * MD5 = new TMD5Digest ;
        MD5->InString = a ;

        // suffix hash
        a +=  MD5->MD5Str ;

        delete MD5 ;

        AnsiString key ;

        for ( int x = 5 ; x < 13 ; x++ )
                key += IntToHex ( KEYMEM [ x ] , 4 ) ;

        TBlowFish * b = new TBlowFish ( key ) ;

        b->cypher = a ;
        
        // a may be longer than our handed in data
        a = b->cypher ;

        delete b ;

        return a ;
}     */
//---------------------------------------------------------------------------

/*
* Purpose :
* Accepts :
* Returns :
*/
int __fastcall TUSBKeyWrite::GetINCMEM ( int index )
{
        //TODO: Add your source code here
        KEYMEM [ index ] = KEYMEM [ index ] + 1 ;

        return KEYMEM [ index ] ;
}
