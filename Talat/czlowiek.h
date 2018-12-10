#pragma once
#include"uzytkownik.h"

class czlowiek:public uzytkownik
{
public:
	czlowiek();
	czlowiek(string,string,int);
	~czlowiek();

	string ruch(plansza*, plansza*,int,int);
	void ustaw(plansza*,plansza*,pionek*,int,int);
};