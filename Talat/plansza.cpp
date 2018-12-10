#include"plansza.h"
#include <iostream>
#include <string>

using namespace std;

plansza::plansza(){}
plansza::plansza(string _gorny, string _dolny,int _nr) :gorny(_gorny),dolny(_dolny),nr(_nr) 
{
	// tworzenie dynamicznej mapy
	mapa = new string*[5];
	for (int i = 0; i < 5; i++)
	{
		mapa[i] = new string[5];
		for (int j = 0; j < 5; j++)
		{
			mapa[i][j] = '0';
		}
	}
}
plansza::~plansza()
{
	// usuniecie dynamicznej mapy
	for (int i = 0; i < 5; i++)
	{
		delete[] mapa[i];
	}
	delete [] mapa;
}

char plansza::get_gorny()
{
	return gorny[0];
}
char plansza::get_dolny()
{
	return dolny[0];
}
int plansza::get_nr()
{
	return nr;
}

void plansza::rysuj_1()
{
	cout << endl;
	cout <<"  ";
	for (int k = 0; k<5; k++)
	{
		cout << "   " ;
		cout << gorny;
		cout << k + 1 << " ";
	}
	cout << endl;

	//gorna sciana planszy
	cout << "   ";
	cout << "#";
	for (int k = 0; k<5; k++)
	{
		cout << "######";
	}
	
	//kolejne wiersze planszy
	for (int i = 0; i<5; i++)
	{
		cout << endl;
		cout << "   ";
		cout << "#";
		for (int k = 0; k<5; k++)
		{
			cout << "     #";
		}

		cout << endl;
		cout <<" "<< i+1<<" #";
		for (int j = 0; j<5; j++)
		{
			if (mapa[i][j] != "0")
			{

				cout << " "<< mapa[i][j];    //jest tu jakis pionek.
			}
			else
			{
				cout << "    ";
			}

			cout << " #";
		}

		cout << endl;
		cout << "   #";
		for (int k = 0; k<5; k++)
		{
			cout << "     #";
		}

		cout <<  endl;
		cout << "   ";
		for (int k = 0; k<5; k++)
		{
			cout << "######";
		}
		cout << "#";
	}
	
	cout << endl;
	cout << "  ";
	for (int k = 0; k<5; k++)
	{
		cout << "   ";
		cout << dolny;
		cout << k + 1 << " ";
	}
	cout << endl;
	
}
void plansza::rysuj_2(plansza &p2)
{
	cout << endl;
	cout << "  ";
	// oznaczenie pól gornych w planszy 1
	for (int k = 0; k<5; k++)
	{
		cout << "   ";
		cout << gorny;
		cout << k + 1 << " ";
	}

	cout << "           ";
	// oznaczenie pól gornych w planszy 2
	for (int k = 0; k<5; k++)
	{
		cout << "   ";
		cout << p2.gorny;
		cout << k + 1 << " ";
	}

	cout << endl;
	cout << "   ";
	//gorna sciana planszy 1
	cout << "#";
	for (int k = 0; k<5; k++)
	{
		cout << "######";
	}

	cout << "          ";
	//gorna sciana planszy 2
	cout << "#";
	for (int k = 0; k<5; k++)
	{
		cout << "######";
	}

	//kolejne wiersze planszy 1 i 2
	for (int i = 0; i<5; i++)
	{
		cout << endl;
		//plansza 1
		cout << "   ";
		cout << "#";
		for (int k = 0; k<5; k++)
		{
			cout << "     #";
		}

		//plansza 2
		cout << "          ";
		cout << "#";
		for (int k = 0; k<5; k++)
		{
			cout << "     #";
		}

		cout << endl;
		//plansza 1
		cout << " " << i + 1 << " #";
		for (int j = 0; j<5; j++)
		{
			if (mapa[i][j] != "0")
			{

				cout << " " << mapa[i][j];    //jest tu jakis pionek.
			}
			else
			{
				cout << "    ";
			}

			cout << " #";
		}

		//plansza 2
		cout << "       ";
		cout << " " << i + 1 << " #";
		for (int j = 0; j<5; j++)
		{
			if (p2.mapa[i][j] != "0")
			{

				cout << " " << p2.mapa[i][j];    //jest tu jakis pionek.
			}
			else
			{
				cout << "    ";
			}

			cout << " #";
		}


		cout << endl;
		//plansza 1
		cout << "   #";
		for (int k = 0; k<5; k++)
		{
			cout << "     #";
		}

		//plansza 2
		cout << "       ";
		cout << "   #";
		for (int k = 0; k<5; k++)
		{
			cout << "     #";
		}

		cout << endl;
		//dolna sciana planszy 1
		cout << "   ";
		for (int k = 0; k<5; k++)
		{
			cout << "######";
		}
		cout << "#";

		//dolna sciana planszy 2
		cout << "       ";
		cout << "   ";
		for (int k = 0; k<5; k++)
		{
			cout << "######";
		}
		cout << "#";
	}

	cout << endl;
	// oznaczenie pól dolnych w planszy 1
	cout << "  ";
	for (int k = 0; k<5; k++)
	{
		cout << "   ";
		cout << dolny;
		cout << k + 1 << " ";
	}

	cout << "           ";
	// oznaczenie pól dolnych w planszy 2
	for (int k = 0; k<5; k++)
	{
		cout << "   ";
		cout << p2.dolny;
		cout << k + 1 << " ";
	}
	cout << endl;

}

pionek::pionek() {}
pionek::pionek(string _kolor, string _wysokosc,string _nazwa) :kolor(_kolor), wysokosc(_wysokosc),nazwa(_nazwa) {}
pionek::~pionek(){}

string pionek:: get_nazwa()
{
	return nazwa;
}
string pionek:: get_kolor()
{
	return kolor;
}
string pionek:: get_wysokosc()
{
	return wysokosc;
}

trojkat::trojkat() {}
trojkat::trojkat(string _kolor, string _wysokosc,string _nazwa):pionek(_kolor,_wysokosc,_nazwa) {}
trojkat::~trojkat() {}
string trojkat::ozn_p() 
{
	string ozn=kolor+wysokosc+"T";
	return ozn;
}

kwadrat::kwadrat() {}
kwadrat::kwadrat(string _kolor, string _wysokosc,string _nazwa):pionek(_kolor, _wysokosc, _nazwa) {}
kwadrat::~kwadrat() {}
string kwadrat::ozn_p() 
{
	string ozn = kolor + wysokosc + "K";
	return ozn;
}


szesciokat::szesciokat() {}
szesciokat::szesciokat(string _kolor,string _wysokosc,string _nazwa):pionek(_kolor, _wysokosc, _nazwa) {}
szesciokat::~szesciokat() {}
string szesciokat::ozn_p() 
{
	string ozn = kolor + wysokosc + "S";
	return ozn;
}