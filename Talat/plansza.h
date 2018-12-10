#pragma once
#include <iostream>
#include <string>

using namespace std;

class plansza
{
private:
	string gorny; // oznaczenie gornej czesci planszy
	string dolny; // oznaczenie dolnej czesci planszy
	int nr;      // numer planszy

public:
	string **mapa;

	plansza();
	plansza(string, string,int);
	~plansza();
   
	char get_gorny();
	char get_dolny();
	int get_nr();

	void rysuj_1();
	void rysuj_2(plansza &);
};

class pionek
{
protected:
	string nazwa; // pelna nazwa ponka
	string kolor; // kolor pionka
	string wysokosc; // wyskokosc pionka(maly,sredni,szesciokatny)

public:
	pionek();
	pionek(string,string,string);
	~pionek();

	string get_nazwa();
	string get_kolor();
	string get_wysokosc();

	virtual string ozn_p() = 0; // zwraca oznaczenie danego pionka
	
};

class trojkat :public pionek
{
public:
	trojkat();
	trojkat(string, string,string);
	~trojkat();

	string ozn_p();
};

class kwadrat :public pionek
{
public:
	kwadrat();
	kwadrat(string, string,string);
	~kwadrat();

	string ozn_p();
};

class szesciokat:public pionek
{
public:
	szesciokat();
	szesciokat(string, string,string);
	~szesciokat();

	string ozn_p();
};