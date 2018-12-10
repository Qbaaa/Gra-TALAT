#pragma once
#include"uzytkownik.h"

class komputer :public uzytkownik
{
public:
	komputer();
	komputer(string,string,int);
	~komputer();

	string ruch(plansza*, plansza*,int,int);
	void ustaw(plansza*, plansza*,pionek*,int,int);

};

