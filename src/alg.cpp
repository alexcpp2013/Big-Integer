#include "alg.h"
#include <iomanip>

using namespace std;

int BigInt :: base = 7777;

BigInt::BigInt( string str )
{
    vector < short > num;
    int i;
 	for (i = str.length() - 3; i >= 0; i -= 3)
 	{
		num.push_back( atoi( &str[ i ] ) );
 	    str[i] = '\n';
    }
 	switch( i )
 	{
        case -3: break;
		case -2: num.push_back( atoi( &str[ i+2 ] ) ); break;
		case -1: num.push_back( atoi( &str[ i+1 ] ) ); break;
    }
    while ( !num.empty( ) )
    {
    	int r = 0, temp;
        for ( i = num.size( ) - 1; i >= 0; --i)
        {
            temp = r * 1000 + num[ i  ];
            num[ i ] = temp / base;
            r = temp - num[ i ] * base;
        }
        big.push_back(r);
        i = num.size() - 1;
        while ( (i>=0) && (num[i] == 0) )
        {
			num.pop_back( );
			--i;
		}
    }
}

BigInt::~BigInt()
{
    big.clear();
}

void BigInt :: display( ) const
{
    for( int i = big.size( ) - 1; i >= 0; --i )
        cout << setw(4) << setfill('0') << big[ i ] << ' ';
    cout << endl;
}

void BigInt::displaydec() const
{
    vector < short > in_dec;
    const int BASEDEC = 1000;
	int temp, carry = 0;

	 in_dec.push_back( 0 );
	 for(int i = big.size( ) - 1; i >= 0; --i )
	 {
        int j;
        for (j = 0; j < in_dec.size( ); ++j )
        {
            temp = in_dec[ j ] * base + carry;
            carry = temp / BASEDEC;
            in_dec[ j ] = temp - carry * BASEDEC;
        }
        while ( carry )
        {
            in_dec.push_back( carry % BASEDEC );
            carry /= BASEDEC;
        }
        temp = in_dec[ 0 ] + big[ i ];
        carry = temp / BASEDEC;
        in_dec[ 0 ] = temp - carry * BASEDEC;
        j = 1;
        while ( carry && ( j != in_dec.size( ) ) )
        {
            temp = in_dec[ j ] + carry;
            carry = temp / BASEDEC;
				in_dec[ j++ ] = temp - carry * BASEDEC;
        }
        while ( carry )
        {
            in_dec.push_back( carry );
            carry /= BASEDEC;
        }
    }
    cout << in_dec[ in_dec.size( ) - 1 ] << ' ';
    for( int i = in_dec.size( ) - 2; i >= 0; --i )
        cout << setw(3) << setfill( '0' ) << in_dec[ i ] << ' ';
    cout << endl;
}

const BigInt& BigInt :: operator= ( const BigInt& b )
{
    if ( this == &b ) return *this;
    if ( !big.empty( ) ) big.clear( );
    big = b.big;
}

bool BigInt :: operator>= ( const BigInt& b) const
{
    if ( big.size() > b.big.size( ) )
        return true;
    else if ( big.size( ) < b.big.size( ) )
	     return false;
    else
	     for( int i = big.size( ); i > 0; --i )
	     {
            if ( big[ i - 1 ] < b.big[ i - 1 ] )
                return false;
			else
				if( big[ i - 1 ] > b.big[ i - 1 ] )
			       return true;
        }
    return true;
}

const BigInt BigInt :: operator+ ( const BigInt& b ) const
{
    BigInt res;
    short temp, carry = 0, size1 = big.size( ), size2 = b.big.size( ), i;
    if (big.size( ) < b.big.size( ) ) return (b + *this);
	for ( i= 0; i < size2; ++i )
	{
		temp = big[ i ] + b.big[ i ] + carry;
	    if (temp >= base)
	    {
	        res.big.push_back( temp - base );
	        carry = 1;
        }
        else
        {
        	res.big.push_back( temp );
            carry = 0;
        }
    }
    for ( ; i < size1; ++i )
    {
        temp = big[ i ] + carry;
        if ( temp >= base )
        {
	         res.big.push_back( temp - base );
	         carry = 1;
        }
        else
        {
            res.big.push_back( temp );
            carry = 0;
        }
    }
    if ( carry ) res.big.push_back( 1 );
    return res;
}

const BigInt BigInt :: operator- ( const BigInt& b ) const
{
    BigInt res;
    short temp, carry = 0, i;
    if ( b >= *this)
	{
		res.big.push_back( 0 );
		return res;
	}
    for ( i=0; i < b.big.size( ); ++i )
    {
        temp = big[ i ] - b.big[ i ] + carry;
        if ( temp < 0)
        {
            res.big.push_back( temp + base );
            carry = -1;
        }
        else
        {
            res.big.push_back( temp );
            carry = 0;
        }
    }
    for ( ; i < big.size( ); ++i )
    {
        temp = big[ i ] + carry;
        if ( temp < 0)
        {
            res.big.push_back( temp + base );
            carry = -1;
        }
        else
        {
            res.big.push_back( temp );
            carry = 0;
        }
    }
    while ( res.big.back( ) == 0 )
    	res.big.pop_back( );
    return res;
}

const BigInt BigInt :: operator* ( const unsigned long num ) const
{
    BigInt res;
    unsigned long temp, carry = 0;
    for ( int i = 0; i < big.size( ); ++i )
    {
        temp = big[ i ] * num + carry;
        carry = temp / base;
        res.big.push_back( temp - carry * base );
    }
    while ( carry )
    {
        res.big.push_back( carry );
        carry /= base;
    }
    return res;
}

const BigInt BigInt :: operator* ( const BigInt& b ) const
{
    BigInt res;
    short i,j;
	int carry, temp;
    res.big.resize( big.size() + b.big.size( ) );
	for ( i = 0; i < big.size( ); ++i )
	{
    	carry = 0;
        for ( j = 0; j < b.big.size( ); ++j )
        {
            temp = big[ i ] * b.big[ j ] + res.big[ i+j ] + carry;
            carry = temp / base;
            res.big[ i + j]  = temp - carry * base;
        }
        res.big[ i + j ] = carry;
    }
    while ( res.big.back( ) == 0 )
    	res.big.pop_back( );
    return res;
}

const BigInt BigInt::operator/ (const unsigned long num) const
{
    BigInt Q;
    int r = 0, temp;
    int i;
    Q.big.resize( big.size( ) );
    for ( i = big.size( ) - 1; i >= 0; --i )
    {
        temp = r * base + big[ i ];
        Q.big[ i ] = temp / num;
        r = temp - Q.big[ i ] * num;
    }
    i = big.size( ) - 1;
    while ( ( i > 0 ) && ( Q.big[ i ] == 0 ) )
    {
		Q.big.pop_back( );
		--i;
	}
    return Q;
}

const BigInt BigInt::operator/ ( const BigInt& b ) const
{
    BigInt U( *this ), B( b ), Q;
    if ( !( U >= B ) )
    {
		Q.big.push_back( 0 );
		return Q;
	}
    if ( B.big.size( ) == 1)
    {
		Q = U / B.big[ 0 ];
		return Q;
	}
    int n = B.big.size( ), m = U.big.size( ) - B.big.size( );
    int scale, borrow, carry;
    int qGuess, r;
    int uJ, vJ, i;
    int temp, temp1, temp2;
    Q.big.resize( m + 1 );
    scale = base / ( B.big[ n - 1 ] + 1 );
    if ( scale > 1 )
    {
        U = U * scale;
        B = B * scale;
    }
	if ( U.big.size( ) == this -> big.size( ) )
		U.big.push_back(0);
    for ( vJ = m, uJ = n + vJ; vJ >= 0; --vJ, --uJ)
    {
		qGuess = ( U.big[ uJ ] * base + U.big[ uJ - 1 ] ) / B.big[ n - 1 ];
        r = ( U.big[ uJ ] * base + U.big[ uJ - 1 ] ) % B.big[ n - 1 ];
        while ( r < base )
        {
		      temp2 = B.big[ n - 2 ] * qGuess;
		      temp1 = r * base + U.big[ uJ - 2 ];
		      if ( ( temp2 > temp1 ) || ( qGuess == base ) )
		      {
				    --qGuess;
				    r += B.big[ n - 1 ];
            }
            else
            	break;
        }
        carry = 0; borrow = 0;
        for ( i = 0; i < n; ++i )
        {
            temp1 = B.big[ i ] * qGuess + carry;
            carry = temp1 / base;
            temp1 -= carry * base;
            temp2 = U.big[ vJ + i ] - temp1 + borrow;
            if (temp2 < 0)
            {
				U.big[ vJ + i ] = temp2 + base;
				borrow = -1;
			}
			else
			{
                U.big[ vJ + i ] = temp2;
                borrow = 0;
			}
        }
        temp2 = U.big[ vJ + i ] - carry + borrow;
        if ( temp2 < 0 )
        {
            U.big[ vJ + i ] = temp2 + base;
			borrow = -1;
        }
        else
        {
            U.big[ vJ + i] = temp2;
            borrow = 0;
		}
		if ( borrow == 0 )
			Q.big[ vJ ] = qGuess;
		else
		{
			Q.big[ vJ ] = qGuess - 1;
			carry = 0;
			for ( i = 0; i < n; ++i )
			{
            	temp = U.big[ vJ + i ] + B.big[ i ] + carry;
            	if (temp >= base)
            	{
            		U.big[ vJ + i ] = temp - base;
                	carry = 1;
				}
				else
				{
					U.big[ vJ + i ] = temp;
					carry = 0;
				}
			}
			U.big[ vJ + i] = U.big[ vJ + i ] + carry - base;
			}
    	i = U.big.size( ) - 1;
    	while ( ( i > 0 ) && ( U.big[ i ] == 0 ) )
    	{
			U.big.pop_back( );
			--i;
		}
    }
    if ( Q.big[ m ] == 0 )
    	Q.big.pop_back( );
    return Q;
}
