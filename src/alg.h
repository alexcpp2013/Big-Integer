// alg.h
#ifndef ALG_H
#define ALG_H

#include <iostream>
#include <string>
#include <vector>

class BigInt
{

    private:
        static int base;
        std::vector <short> big;
    public:
    	BigInt()
    	{
			;
		}
        BigInt( std::string );
        BigInt( const BigInt& cpy ) : big( cpy.big )
		{
			;
		}
        ~BigInt( );
        void display( ) const;
        void displaydec( ) const;
        const BigInt& operator= ( const BigInt& );
        bool operator>= ( const BigInt& ) const;
        const BigInt operator+ ( const BigInt& ) const;
        const BigInt operator- ( const BigInt& ) const;
        const BigInt operator* ( const BigInt& ) const;
        const BigInt operator/ ( const BigInt& ) const;
        const BigInt operator* (const unsigned long) const;
        const BigInt operator/ (const unsigned long) const;
        static int getbase()
        {
			return base;
		}

};

#endif
