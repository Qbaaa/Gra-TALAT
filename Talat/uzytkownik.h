#pragma once
#include"plansza.h"
#include <iostream>
#include <cstring>

using namespace std;

class uzytkownik
{
protected:
	string imie; // imie gracza
	string kolor; // kolor gracza
	int punkty; // zdobyte punkty

public:
	uzytkownik();
	uzytkownik(string,string,int);
	~uzytkownik();

	int get_punkty();
	string get_imie();
	char get_kolor();
	
	virtual string ruch(plansza*, plansza*,int,int) = 0;  // ruch gracza
	virtual void ustaw(plansza*,plansza*,pionek*,int ,int) = 0; // ustawienie pionka

	int pop_ruchu(int, int, int, int, int); // sprawdzenie poprawnosci ruchu
	int spr_bicia(string, string); // sprawdzenie czy pionem moze byc zbity przez drugiego pionka
	int d_punktow(int, int);  // dodanie punktow za dojscie do miejsca startowego przeciwnika
	
};


