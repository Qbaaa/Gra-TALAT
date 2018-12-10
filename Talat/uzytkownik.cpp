#include"uzytkownik.h"
#include <cstring>

using namespace std;

uzytkownik::uzytkownik() {}

uzytkownik::uzytkownik(string _imie,string _kolor,int _punkty):imie(_imie),kolor(_kolor),punkty(_punkty) {}

uzytkownik::~uzytkownik(){}

int uzytkownik::get_punkty() 
{
	return punkty;
}

string uzytkownik::get_imie()
{
	return imie;
}

char uzytkownik::get_kolor()
{
	return kolor[0];
}

int uzytkownik::pop_ruchu(int xp, int yp, int xr, int yr, int spr) // zwraca 0 ruch niepoprawny, zwraca 1 ruch poprawny(porusza sie do przodu),zwraca 2 ruch poprawny(porusza sie w bok)
{
	if (spr == 0)  // gorna czesc planszy
	{
		if ((xp - 1 <= xr && xr <= xp + 1) && (yp + 1 == yr))
			return 1;
		else if ((xp - 1 <= xr && xr <= xp + 1) && (yp == yr))
		{
			if (xp == xr && yp == yr)
				return 0;
			else
				return 2;
		}

	}
	else if (spr == 4) //dolna czesc planszy
	{
		if ((xp - 1 <= xr && xr <= xp + 1) && (yp - 1 == yr))
			return 1;
		else if ((xp - 1 <= xr && xr <= xp + 1) && (yp == yr))
		{
			if (xp == xr && yp == yr)
				return 0;
			else
				return 2;
		}
	}
	return 0;
}

int uzytkownik::spr_bicia(string p_bi, string p_bro)  // zwraca 1 jesli bicie jest mozliwe pionka przez pionka, zwraca 0 jesli bicie jest niemozliwe 
{
	if (p_bi == "BMT")
		if (p_bro == "SDS" || p_bro == "CDS")
			return 1;

	if (p_bi == "SMT")
		if (p_bro == "BDS" || p_bro == "CDS")
			return 1;

	if (p_bi == "CMT")
		if (p_bro == "BDS" || p_bro == "SDS")
			return 1;

	if (p_bi == "BST")
		if (p_bro == "SMT" || p_bro == "SMK" || p_bro == "SMS" || p_bro == "CMT" || p_bro == "CMK" || p_bro == "CMS")
			return 1;

	if (p_bi == "SST")
		if (p_bro == "BMT" || p_bro == "BMK" || p_bro == "BMS" || p_bro == "CMT" || p_bro == "CMK" || p_bro == "CMS")
			return 1;

	if (p_bi == "CST")
		if (p_bro == "SMT" || p_bro == "SMK" || p_bro == "SMS" || p_bro == "BMT" || p_bro == "BMK" || p_bro == "BMS")
			return 1;

	if (p_bi == "BDT")
		if (p_bro == "SST" || p_bro == "SSK" || p_bro == "SSS" || p_bro == "CST" || p_bro == "CSK" || p_bro == "CSS")
			return 1;

	if (p_bi == "SDT")
		if (p_bro == "BST" || p_bro == "BSK" || p_bro == "BSS" || p_bro == "CST" || p_bro == "CSK" || p_bro == "CSS")
			return 1;

	if (p_bi == "CDT")
		if (p_bro == "SST" || p_bro == "SSK" || p_bro == "SSS" || p_bro == "BST" || p_bro == "BSK" || p_bro == "BSS")
			return 1;

	if (p_bi == "BMK")
		if (p_bro == "SMT" || p_bro == "CMT")
			return 1;

	if (p_bi == "SMK")
		if (p_bro == "BMT" || p_bro == "CMT")
			return 1;

	if (p_bi == "CMK")
		if (p_bro == "SMT" || p_bro == "BMT")
			return 1;

	if (p_bi == "BSK")
		if (p_bro == "SST" || p_bro == "CST" ||
			p_bro == "SMT" || p_bro == "SMK" || p_bro == "SMS" || p_bro == "CMT" || p_bro == "CMK" || p_bro == "CMS")
			return 1;

	if (p_bi == "SSK")
		if (p_bro == "BST" || p_bro == "CST" ||
			p_bro == "BMT" || p_bro == "BMK" || p_bro == "BMS" || p_bro == "CMT" || p_bro == "CMK" || p_bro == "CMS")
			return 1;

	if (p_bi == "CSK")
		if (p_bro == "SST" || p_bro == "BST" ||
			p_bro == "SMT" || p_bro == "SMK" || p_bro == "SMS" || p_bro == "BMT" || p_bro == "BMK" || p_bro == "BMS")
			return 1;

	if (p_bi == "BDK")
		if (p_bro == "SDT" || p_bro == "CDT" ||
			p_bro == "SST" || p_bro == "SSK" || p_bro == "SSS" || p_bro == "CST" || p_bro == "CSK" || p_bro == "CSS")
			return 1;

	if (p_bi == "SDK")
		if (p_bro == "BDT" || p_bro == "CDT" ||
			p_bro == "BST" || p_bro == "BSK" || p_bro == "BSS" || p_bro == "CST" || p_bro == "CSK" || p_bro == "CSS")
			return 1;

	if (p_bi == "CDK")
		if (p_bro == "BDT" || p_bro == "SDT" ||
			p_bro == "SST" || p_bro == "SSK" || p_bro == "SSS" || p_bro == "BST" || p_bro == "BSK" || p_bro == "BSS")
			return 1;

	if (p_bi == "BMS")
		if (p_bro == "SMK" || p_bro == "CMK" || p_bro == "SMT" || p_bro == "CMT")
			return 1;

	if (p_bi == "SMS")
		if (p_bro == "BMK" || p_bro == "CMK" || p_bro == "BMT" || p_bro == "CMT")
			return 1;

	if (p_bi == "CMS")
		if (p_bro == "SMK" || p_bro == "BMK" || p_bro == "SMT" || p_bro == "BMT")
			return 1;

	if (p_bi == "BSS")
		if (p_bro == "SSK" || p_bro == "CSK" || p_bro == "SST" || p_bro == "CST" ||
			p_bro == "SMT" || p_bro == "SMK" || p_bro == "SMS" || p_bro == "CMT" || p_bro == "CMK" || p_bro == "CMS")
			return 1;

	if (p_bi == "SSS")
		if (p_bro == "BSK" || p_bro == "CSK" || p_bro == "BST" || p_bro == "CST" ||
			p_bro == "BMT" || p_bro == "BMK" || p_bro == "BMS" || p_bro == "CMT" || p_bro == "CMK" || p_bro == "CMS")
			return 1;

	if (p_bi == "CSS")
		if (p_bro == "BSK" || p_bro == "SSK" || p_bro == "BST" || p_bro == "SST" ||
			p_bro == "BMT" || p_bro == "BMK" || p_bro == "BMS" || p_bro == "SMT" || p_bro == "SMK" || p_bro == "SMS")
			return 1;

	if (p_bi == "BDS")
		if (p_bro == "SDK" || p_bro == "SDT" || p_bro == "CDK" || p_bro == "CDT" ||
			p_bro == "SST" || p_bro == "SSK" || p_bro == "SSS" || p_bro == "CST" || p_bro == "CSK" || p_bro == "CSS")
			return 1;

	if (p_bi == "SDS")
		if (p_bro == "BDK" || p_bro == "BDT" || p_bro == "CDK" || p_bro == "CDT" ||
			p_bro == "BST" || p_bro == "BSK" || p_bro == "BSS" || p_bro == "CST" || p_bro == "CSK" || p_bro == "CSS")
			return 1;

	if (p_bi == "CDS")
		if (p_bro == "SDK" || p_bro == "SDT" || p_bro == "BDK" || p_bro == "BDT" ||
			p_bro == "SST" || p_bro == "SSK" || p_bro == "SSS" || p_bro == "BST" || p_bro == "BSK" || p_bro == "BSS")
			return 1;

	return 0;
}

int uzytkownik::d_punktow(int yp, int yr)  // zwraca 3 jesli pionek dodarl do miejsca startowego przeciwnika, zwraca 0 jesli nie dotarl
{
	if (yp == 0)  // sprawdzenie czy pionek zaczynal gre z gornej czesci planszy
	{
		if (yr == 4)	// sprawdzenie czy pionek dodarl do miejsca startowego przeciwnika
			return 3;
	}
	else if (yp == 4) // sprawdzenie czy pionek zaczynal gre z dolnej czesci planszy
	{
		if (yr == 0) // sprawdzenie czy pionek dodarl do miejsca startowego przeciwnika
			return 3;
	}
	return 0;
}