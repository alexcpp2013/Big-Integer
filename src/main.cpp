#include "alg.h"


using namespace std;

void shownum( const BigInt &b );

int main()
{

	string ans = "";
	string str = "";
	cout << endl << "������ ��ࢮ� �᫮: " << endl << endl;
	cin >> str;
	BigInt bigA(str);
	shownum( bigA );
	cout << endl << "������ ��஥ �᫮: " << endl << endl;
	cin >> str;
	BigInt bigB( str );
	shownum( bigB );
	cout << endl << endl;

	for( ; ; )
	{
		cout << endl <<" >> ";
		cin >> ans;
		if( ans == "+" )
		{
			BigInt bigC = bigA + bigB;
			shownum( bigC );
		}
		if( ans == "-" )
				{
					BigInt bigC = bigA - bigB;
					shownum( bigC );
		}
		if( ans == "*" )
				{
					BigInt bigC = bigA * bigB;
					shownum( bigC );
		}
		if( ans == "/" )
				{
					BigInt bigC = bigA / bigB;
					shownum( bigC );
		}
		if( ans == "exit" )
		{
			break;
		}
	}

	return 0;

}

void shownum( const BigInt &b )
{
    cout << endl << "��᫮ � ����� " << b.getbase() << " =   ";
    	b.display( );
 	cout << endl << "����筮� �᫮ =   ";
 		b.displaydec();
}

