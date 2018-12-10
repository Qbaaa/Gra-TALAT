#define _CRT_SECURE_NO_WARNINGS
#include"rozgrywka.h"
#include"uzytkownik.h"
#include"czlowiek.h"
#include"komputer.h"
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

rozgrywka::rozgrywka():ruch(1), g1(0), g2(0), g3(0)
{
	zbite = new string*[3];
	for (int i = 0; i < 3; i++)
	{
		zbite[i] = new string[10];
		for (int j = 0; j < 10; j++)
			zbite[i][j] = "0";
	}
}

rozgrywka::~rozgrywka()
{
	delete gracz1;
	delete gracz2;
	delete gracz3;
	delete p1;
	delete p2;
	delete p3;
	delete bmt;
	delete bst;
	delete bdt;
	delete smt;
	delete sst;
	delete sdt;
	delete cmt;
	delete cst;
	delete cdt;
	delete bmk;
	delete bsk;
	delete bdk;
	delete smk;
	delete ssk;
	delete sdk;
	delete cmk;
	delete csk;
	delete cdk;
	delete bms;
	delete bss;
	delete bds;
	delete sms;
	delete sss;
	delete sds;
	delete cms;
	delete css;
	delete cds;

	for (int i = 0; i < 3; i++)
	{
		delete[] zbite[i];
	}
	delete[] zbite;
}

void rozgrywka::menu1()
{
	int wybor;
	cout << "========================" << endl;
	cout << "     MENU : " << endl;
	cout << "1- NOWA GRA" << endl;
	cout << "2- WCZYTAJ GRE" << endl;
	cout << "3- TABLICA WYNIKOW" << endl;
	cout << "========================" << endl;

	cout << "Twoj wybor: ";
	while (!(cin >> wybor) || wybor < 1 || wybor > 3 || getchar() != '\n')
	{
		cout << "BLAD! Podaj jeszcze raz: ";
		while (getchar() != '\n');
		cin.clear();
		cin.sync();
	}

	if (wybor == 1) // wybor iloma graczami chcemy grac
	{
		system("cls");
		menu2();
	}
	else if (wybor == 2) // wczytanie gry
	{
		if (wczytaj_save()==false)
			menu2();
		else
		{
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 10; j++)			
					usun_pionka(zbite[i][j]);  // usuniecie pionkow zbitych przez gracza

			gra();
			kto();
			p1->rysuj_2(*p2);
			p3->rysuj_1();
		}

	}
	else if (wybor == 3) // wypisanie wszystkich wynikow, zakonczonych gier
		tablica_wynikow();
}

void rozgrywka::menu2()
{
	int wybor;
	cout << "========================" << endl;
	cout << "Wybierz tryb gry: " << endl;
	cout << "1- Czlowiek vs Komputer vs Komputer" << endl;
	cout << "2- Czlowiek vs Czlowiek vs Komputer" << endl;
	cout << "========================" << endl;

	cout << "Twoj wybor: ";
	while (!(cin >> wybor) || wybor < 1 || wybor > 2 || getchar() != '\n')
	{
		cout << "BLAD! Podaj jeszcze raz: ";
		while (getchar() != '\n');
		cin.clear();
		cin.sync();
	}

	if (wybor == 1) // Czlowiek vs Komputer vs Komputer
	{
		string nazwa_Gracza1;
		bool poprawnosc = true;
		int dlugosc;

		while (poprawnosc)
		{
			cout << "Podaj nazwe gracza: ";
			getline(cin, nazwa_Gracza1);

			dlugosc = nazwa_Gracza1.length();
			for (int i = 0; i < dlugosc; i++)
				if (nazwa_Gracza1[i] == ' ')
				{
					cout << "BLAD! Podaj jeszcze raz: " << endl;
					poprawnosc = true;
					break;
				}
				else
					poprawnosc = false;
		}
	
		gracz1 = new czlowiek(nazwa_Gracza1,"Bialy",0);
		gracz2 = new komputer("Komputer1","Szary",0);
		gracz3 = new komputer("Komputer2","Czarny",0);

		stworz_p(); 
		ustawienie_pionkow();
		gra();
		kto();
		p1->rysuj_2(*p2);
		p3->rysuj_1();
	}
	else if (wybor == 2) //  Czlowiek vs Czlowiek vs Komputer
	{
		string nazwa_Gracza1, nazwa_Gracza2;
		bool poprawnosc = true;
		int dlugosc;

		while (poprawnosc)
		{
			cout << "Podaj nazwe gracza(gracz1): ";
			getline(cin, nazwa_Gracza1);

			dlugosc = nazwa_Gracza1.length();
			for (int i = 0; i < dlugosc; i++)
				if (nazwa_Gracza1[i] == ' ')
				{
					cout << "BLAD! Podaj jeszcze raz: " << endl;
					poprawnosc = true;
					break;
				}
				else
					poprawnosc = false;
		}

		poprawnosc = true;
		while (poprawnosc)
		{
			cout << "Podaj nazwe gracza(gracz2): ";
			getline(cin, nazwa_Gracza2);

			dlugosc = nazwa_Gracza2.length();
			for (int i = 0; i < dlugosc; i++)
				if (nazwa_Gracza2[i] == ' ')
				{
					cout << "BLAD! Podaj jeszcze raz: " << endl;
					poprawnosc = true;
					break;
				}
				else
					poprawnosc = false;
		}


		gracz1 = new czlowiek(nazwa_Gracza1, "Bialy", 0);
		gracz2 = new czlowiek(nazwa_Gracza2, "Szary", 0);
		gracz3 = new komputer("Komputer3", "Czarny",0);
		
		stworz_p();
		ustawienie_pionkow();
		gra();
		kto();
		p1->rysuj_2(*p2);
		p3->rysuj_1();
	}
}

void rozgrywka::stworz_p() // stworzenie planszy i pionkow
{
	p1 = new plansza("B", "S",1);
	p2 = new plansza("B", "C",2);
	p3 = new plansza("C", "S",3);

	bmt = new trojkat("B", "M", "Biala mala trojkatna wieza");
	bst = new trojkat("B", "S", "Biala srednia trojkatna wieza");
	bdt = new trojkat("B", "D", "Biala duza trojkatna wieza");
	smt = new trojkat("S", "M", "Szara mala trojkatna wieza");
	sst = new trojkat("S", "S", "Szara srednia trojkatna wieza");
	sdt = new trojkat("S", "D", "Szara duza trojkatna wieza");
	cmt = new trojkat("C", "M", "Czarna mala trojkatna wieza");
	cst = new trojkat("C", "S", "Czarna srednia trojkatna wieza");
	cdt = new trojkat("C", "D", "Czarna duza trojkatna wieza");

	bmk = new kwadrat("B", "M", "Biala mala kwadratowa wieza");
	bsk = new kwadrat("B", "S", "Biala srednia kwadratowa wieza");
	bdk = new kwadrat("B", "D", "Biala duza kwadratowa wieza");
	smk = new kwadrat("S", "M", "Szara mala kwadratowa wieza");
	ssk = new kwadrat("S", "S", "Szara srednia kwadratowa wieza");
	sdk = new kwadrat("S", "D", "Szara duza kwadratowa wieza");
	cmk = new kwadrat("C", "M", "Czarna mala kwadratowa wieza");
	csk = new kwadrat("C", "S", "Czarna srednia kwadratowa wieza");
	cdk = new kwadrat("C", "D", "Czarna duza kwadratowa wieza");

	bms = new szesciokat("B", "M","Biala mala szeciokatna wieza");
	bss = new szesciokat("B", "S","Biala srednia szeciokatna wieza");
	bds = new szesciokat("B", "D","Biala duza szeciokatna wieza");
	sms = new szesciokat("S", "M","Szara mala szeciokatna wieza");
	sss = new szesciokat("S", "S","Szara srednia szeciokatna wieza");
	sds = new szesciokat("S", "D","Szara duza szeciokatna wieza");
	cms = new szesciokat("C", "M","Czarna mala szeciokatna wieza");
	css = new szesciokat("C", "S","Czarna srednia szeciokatna wieza");
	cds = new szesciokat("C", "D","Czarna duza szeciokatna wieza");
}

void rozgrywka::ustawienie_pionkow()
{
	gracz1->ustaw(p1, p2, bmt, 0, 0);
	gracz2->ustaw(p1, p3, smt, 4, 4);
	gracz3->ustaw(p2, p3, cmt, 4, 0);

	gracz1->ustaw(p1, p2, bst, 0, 0);
	gracz2->ustaw(p1, p3, sst, 4, 4);
	gracz3->ustaw(p2, p3, cst, 4, 0);

	gracz1->ustaw(p1, p2, bdt, 0, 0);
	gracz2->ustaw(p1, p3, sdt, 4, 4);
	gracz3->ustaw(p2, p3, cdt, 4, 0);

	gracz1->ustaw(p1, p2, bmk, 0, 0);
	gracz2->ustaw(p1, p3, smk, 4, 4);
	gracz3->ustaw(p2, p3, cmk, 4, 0);

	gracz1->ustaw(p1, p2, bsk, 0, 0);
	gracz2->ustaw(p1, p3, ssk, 4, 4);
	gracz3->ustaw(p2, p3, csk, 4, 0);

	gracz1->ustaw(p1, p2, bdk, 0, 0);
	gracz2->ustaw(p1, p3, sdk, 4, 4);
	gracz3->ustaw(p2, p3, cdk, 4, 0);

	gracz1->ustaw(p1, p2, bms, 0, 0);
	gracz2->ustaw(p1, p3, sms, 4, 4);
	gracz3->ustaw(p2, p3, cms, 4, 0);

	gracz1->ustaw(p1, p2, bss, 0, 0);
	gracz2->ustaw(p1, p3, sss, 4, 4);
	gracz3->ustaw(p2, p3, css, 4, 0);

	gracz1->ustaw(p1, p2, bds, 0, 0);
	gracz2->ustaw(p1, p3, sds, 4, 4);
	gracz3->ustaw(p2, p3, cds, 4, 0);
	save();
}

void rozgrywka:: gra()
{
	string usun;

	while (true)
	{

		// sprawdzanie czy dwie plansze sa zamrozone 
		if ((ilosc_ruchow_plansza(gracz1, gracz2, p1) == 0 && ilosc_ruchow_plansza(gracz1, gracz3, p2) == 0) ||
			(ilosc_ruchow_plansza(gracz1, gracz2, p1) == 0 && ilosc_ruchow_plansza(gracz3, gracz2, p3) == 0) ||
			(ilosc_ruchow_plansza(gracz1, gracz3, p2) == 0 && ilosc_ruchow_plansza(gracz3, gracz2, p3) == 0))
			break;

		system("cls");
		if (ruch == 1) // ruch gracza 1
		{
			if (ilosc_ruchow_gracza(p1, p2, gracz1) == 0) // sprawdzenie ile ruchow moze wykonac gracz 1
			{
				ruch = 2;
				continue;
			}

			usun=gracz1->ruch(p1, p2, 0, 0); // przemieszczenie pionka

			if (usun != "0") // sprawdzenie czy przy ruchu zostal zbity pionek, jesli zostal zbity to usuwa dany pionek i zapisuje danemu graczowi jaki pionek zbil 
			{
				usun_pionka(usun);
				zbite[0][g1] = usun;
				g1++;
			}
			
			ruch = 2;
			save();
		}
		else if (ruch == 2) // ruch gracza 2
		{
			if (ilosc_ruchow_gracza(p1, p3, gracz2) == 0) // sprawdzenie ile ruchow moze wykonac gracz 1
			{
				ruch = 3;
				continue;
			}	

			usun=gracz2->ruch(p1, p3, 4, 4); // przemieszczenie pionka

			if (usun != "0") // sprawdzenie czy przy ruchu zostal zbity pionek, jesli zostal zbity to usuwa dany pionek i zapisuje danemu graczowi jaki pionek zbil 
			{
				usun_pionka(usun);
				zbite[1][g2] = usun;
				g2++;
			}

			ruch = 3;
			save();
		}
		else if (ruch == 3) // ruch gracza 3
		{
			if (ilosc_ruchow_gracza(p2, p3, gracz3) == 0) // sprawdzenie ile ruchow moze wykonac gracz 2
			{
				ruch = 1;
				continue;
			}

			usun=gracz3->ruch(p2, p3, 4, 0); // przemieszczenie pionka

			if (usun != "0") // sprawdzenie czy przy ruchu zostal zbity pionek, jesli zostal zbity to usuwa dany pionek i zapisuje danemu graczowi jaki pionek zbil 
			{
				usun_pionka(usun);
				zbite[2][g3] = usun;
				g3++;
			}
			ruch = 1;
			save();
		}
	}
}

int rozgrywka::wygrana() // zwraca, ktory gracz wygra(1- gracz 1, 2- gracz 2, 3- gracz 3)
{
	int x1, x2, x3;
	x1 = gracz1->get_punkty();
	x2 = gracz2->get_punkty();
	x3 = gracz3->get_punkty();
	
	if (x1 > x2)
	{
		if (x1 > x3)
			return 1;
		else if (x1 < x3)
			return 3;
		else if (x1 == x3)
			return remis_1_3();
	}
	else if (x1 < x2)
	{
		if (x2 > x3)
			return 2;
		else if (x2 < x3)
			return 3;
		else if (x2 == x3)
			return remis_2_3();
	}
	else if (x1 == x2 == x3)
		return remis_1_2_3();

	return remis_1_2();
}

void rozgrywka::kto()
{
	int wynik=wygrana();

	if (wynik == 1)
	{
		system("cls");
		cout << gracz1->get_imie() << " WYGRAL!!" << endl;
		dodanie_wyniku_do_tablicy(gracz1->get_imie(),gracz1->get_punkty());
	}
	else if (wynik == 2)
	{
		system("cls");
		cout << gracz2->get_imie() << " WYGRAL!!" << endl;
		dodanie_wyniku_do_tablicy(gracz2->get_imie(),gracz2->get_punkty());
	}
	else if (wynik == 3)
	{
		system("cls");
		cout << gracz3->get_imie() << " WYGRAL!!" << endl;
		dodanie_wyniku_do_tablicy(gracz3->get_imie(), gracz3->get_punkty());
	}
	else
	{
		system("cls");
		cout <<"REMIS!!" << endl;
		dodanie_wyniku_do_tablicy("REMIS",NULL);
	}
}

void rozgrywka::dodanie_wyniku_do_tablicy(string nazwa,int punkty)
{
	ofstream plik;
	plik.open("wyniki.txt", ios::app); // otwarcie pliku do pisania w trybie do³¹czania
	char data[30];
	time_t rawtime;
	tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(data, 90, "%Y.%m.%d %H:%M:%S ", timeinfo);

	plik << data << " " << nazwa <<" "<< punkty << endl;;

	plik.close();
}

void rozgrywka::tablica_wynikow()
{
	ifstream plik;
	plik.open("wyniki.txt"); // otwarcie pliku do odczytu
	string nazwa;
	int punkty;
	string data;
	string godzina;
	system("cls");
	cout << "Tablica wynikow gry:" << endl;
	if (plik.good())
	{
		while (plik >> data >> godzina >> nazwa >> punkty)
		{
			cout << data << " " << godzina << " Wygrana: " << nazwa << " Punkty: " << punkty << endl;
		}
	}
	cout << endl;
	plik.close();
}

void rozgrywka::save()
{
	string typ;
	ofstream plik;
	plik.open("save.txt", ios::out);

	if (plik.good() == false)
	{
		cout << "Blad otwarcia \"save.txt\" do zapisu" << endl;
		exit(0);
	}

	if (typeid(*gracz1) == typeid(komputer))
		typ = "komputer";
	else
		typ = "czlowiek";
	
	plik << typ << " " << gracz1->get_imie() << " " << gracz1->get_punkty() << endl;
	
	if (typeid(*gracz2) == typeid(komputer))
		typ = "komputer";
	else
		typ = "czlowiek";

	plik << typ << " " << gracz2->get_imie() << " " << gracz2->get_punkty() << endl;

	if (typeid(*gracz3) == typeid(komputer))
		typ = "komputer";
	else
		typ = "czlowiek";

	plik << typ << " " << gracz3->get_imie() << " " << gracz3->get_punkty() << endl;
	plik << ruch << endl;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			plik << p1->mapa[i][j]<<" ";
		plik << endl;
	}

	plik << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			plik << p2->mapa[i][j] << " ";
		plik << endl;
	}
	
	plik << endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			plik << p3->mapa[i][j] << " ";
		plik << endl;
	}

	plik << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 10; j++)
			plik << zbite[i][j] << " ";
		plik << endl;
	}

	plik << endl;
	plik << g1<<" " << g2<<" " << g3;

	plik.close();
}

bool rozgrywka::wczytaj_save() // zwraca false jesli nastapil jakis blad, zwraca true jesli wszystko zostalo wczytane poprawnie
{
	string imie1, imie2, imie3;
	string typ1, typ2, typ3;
	int punkty1, punkty2, punkty3;
	int _ruch;
	ifstream plik;
	plik.open("save.txt");

	system("cls");
	if (plik.good() == false)
	{
		cout << "Blad otwarcia \"save.txt\" do odczytu. Rozpoczynam NOWA GRE." << endl;
		return false;
	}

	plik >> typ1 >> imie1 >> punkty1;
	plik >> typ2 >> imie2 >> punkty2;
	plik >> typ3 >> imie3 >> punkty3;
	plik >> _ruch;

	if (plik.eof())
	{
		cout << "Brak w pliku zapisu. Rozpoczynam NOWA GER." << endl;
		return false;
	}

	if (typ1 == "czlowiek")
		gracz1 = new czlowiek(imie1,"Bialy",punkty1);
	else if (typ1 == "komputer")
		gracz1 = new komputer(imie1,"Bialy",punkty1);

	if (typ2 == "czlowiek")
		gracz2 = new czlowiek(imie2, "Szary", punkty2);
	else if (typ2 == "komputer")
		gracz2 = new komputer(imie2, "Szary", punkty2);

	if (typ3 == "czlowiek")
		gracz3 = new czlowiek(imie3, "Czarny", punkty3);
	else if (typ3 == "komputer")
		gracz3 = new komputer(imie3, "Czarny", punkty3);
	ruch = _ruch;

	stworz_p();

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			plik >> p1->mapa[i][j];

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			plik >> p2->mapa[i][j];

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			plik >> p3->mapa[i][j];

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 10; j++)
			plik >> zbite[i][j];

	plik >> g1 >> g2 >> g3;

	plik.close();

	return true;
}

void rozgrywka:: usun_pionka(string u)
{
	if (u == "BMT")
	{
		delete bmt;
		bmt = NULL;
	}
	else if (u == "BST")
	{
		delete bst;
		bst = NULL;
	}
	else if (u == "BDT")
	{
		delete bdt;
		bdt = NULL;
	}
	else if (u == "SMT")
	{
		delete smt;
		smt = NULL;
	}
	else if (u == "SST")
	{
		delete sst;
		sst = NULL;
	}
	else if (u == "SDT")
	{
		delete sdt;
		sdt = NULL;
	}
	else if (u == "CMT")
	{
		delete cmt;
		cmt = NULL;
	}
	else if (u == "CST")
	{
		delete cst;
		cst = NULL;
	}
	else if (u == "CDT")
	{
		delete cdt;
		cdt = NULL;
	}
	else if (u == "BMK")
	{
		delete bmk;
		bmk = NULL;
	}
	else if (u == "BSK")
	{
		delete bsk;
		bsk = NULL;
	}
	else if (u == "BDK")
	{
		delete bdk;
		bdk = NULL;
	}
	else if (u == "SMK")
	{
		delete smk;
		smk = NULL;
	}
	else if (u == "SSK")
	{
		delete ssk;
		ssk = NULL;
	}
	else if (u == "SDK")
	{
		delete sdk;
		sdk = NULL;
	}
	else if (u == "CMK")
	{
		delete cmk;
		cmk = NULL;
	}
	else if (u == "CSK")
	{
		delete csk;
		csk = NULL;
	}
	else if (u == "CDK")
	{
		delete cdk;
		cdk = NULL;
	}
	else if (u == "BMS")
	{
		delete bms;
		bms = NULL;
	}
	else if (u == "BSS")
	{
		delete bss;
		bss = NULL;
	}
	else if (u == "BDS")
	{
		delete bds;
		bds = NULL;
	}
	else if (u == "SMS")
	{
		delete sms;
		sms = NULL;
	}
	else if (u == "SSS")
	{
		delete sss;
		sss = NULL;
	}
	else if (u == "SDS")
	{
		delete sds;
		sds = NULL;
	}
	else if (u == "CMS")
	{
		delete cms;
		cms = NULL;
	}
	else if (u == "CSS")
	{
		delete css;
		css = NULL;
	}
	else if (u == "CDS")
	{
		delete cds;
		cds = NULL;
	}
}

int rozgrywka::remis_1_2()  // zwarca, ktory gracz wygral w przypadku remisu(1- gracz 1, 2- gracz 2)
{
	int w1 = 0, w2 = 0;

	for (int i = 0; i < 9; i++)
	{
		if (zbite[0][i] == "SDS" || zbite[0][i] == "CDS")
			w1++;

		if (zbite[1][i] == "BDS" || zbite[1][i] == "CDS")
			w2++;
	}

	if (w1 > w2)
		return 1;
	else if (w1 < w2)
		return 2;
	else
	{
		w1 = 0, w2 = 0;

		for (int i = 0; i < 9; i++)
		{
			if (zbite[0][i] == "SDK" || zbite[0][i] == "CDK")
				w1++;

			if (zbite[1][i] == "BDK" || zbite[1][i] == "CDK")
				w2++;
		}

		if (w1 > w2)
			return 1;
		else if (w1 < w2)
			return 2;
		else
		{
			w1 = 0, w2 = 0;

			for (int i = 0; i < 9; i++)
			{
				if (zbite[0][i] == "SDT" || zbite[0][i] == "CDT")
					w1++;

				if (zbite[1][i] == "BDT" || zbite[1][i] == "CDT")
					w2++;
			}

			if (w1 > w2)
				return 1;
			else if (w1 < w2)
				return 2;
			else
			{
				w1 = 0, w2 = 0;

				for (int i = 0; i < 9; i++)
				{
					if (zbite[0][i] == "SSS" || zbite[0][i] == "CSS")
						w1++;

					if (zbite[1][i] == "BSS" || zbite[1][i] == "CSS")
						w2++;
				}

				if (w1 > w2)
					return 1;
				else if (w1 < w2)
					return 2;
				else
				{
					w1 = 0, w2 = 0;

					for (int i = 0; i < 9; i++)
					{
						if (zbite[0][i] == "SSK" || zbite[0][i] == "CSK")
							w1++;

						if (zbite[1][i] == "BSK" || zbite[1][i] == "CSK")
							w2++;
					}

					if (w1 > w2)
						return 1;
					else if (w1 < w2)
						return 2;
					else
					{
						w1 = 0, w2 = 0;

						for (int i = 0; i < 9; i++)
						{
							if (zbite[0][i] == "SST" || zbite[0][i] == "CST")
								w1++;

							if (zbite[1][i] == "BST" || zbite[1][i] == "CST")
								w2++;
						}

						if (w1 > w2)
							return 1;
						else if (w1 < w2)
							return 2;
						else
						{
							w1 = 0, w2 = 0;

							for (int i = 0; i < 9; i++)
							{
								if (zbite[0][i] == "SMS" || zbite[0][i] == "CMS")
									w1++;

								if (zbite[1][i] == "BMS" || zbite[1][i] == "CMS")
									w2++;
							}

							if (w1 > w2)
								return 1;
							else if (w1 < w2)
								return 2;
							else
							{
								w1 = 0, w2 = 0;

								for (int i = 0; i < 9; i++)
								{
									if (zbite[0][i] == "SMK" || zbite[0][i] == "CMK")
										w1++;

									if (zbite[1][i] == "BMK" || zbite[1][i] == "CMK")
										w2++;
								}

								if (w1 > w2)
									return 1;
								else if (w1 < w2)
									return 2;
								else
								{
									w1 = 0, w2 = 0;

									for (int i = 0; i < 9; i++)
									{
										if (zbite[0][i] == "SMT" || zbite[0][i] == "CMT")
											w1++;

										if (zbite[1][i] == "BMT" || zbite[1][i] == "CMT")
											w2++;
									}

									if (w1 > w2)
										return 1;
									else if (w1 < w2)
										return 2;
									else
									{
										return 0;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

int rozgrywka::remis_1_3()  // zwarca, ktory gracz wygral w przypadku remisu(1- gracz 1, 3- gracz 3)
{
	int w1 = 0, w3 = 0;

	for (int i = 0; i < 9; i++)
	{
		if (zbite[0][i] == "SDS" || zbite[0][i] == "CDS")
			w1++;

		if (zbite[2][i] == "BDS" || zbite[2][i] == "SDS")
			w3++;
	}

	if (w1 > w3)
		return 1;
	else if (w1 < w3)
		return 3;
	else
	{
		w1 = 0, w3 = 0;

		for (int i = 0; i < 9; i++)
		{
			if (zbite[0][i] == "SDK" || zbite[0][i] == "CDK")
				w1++;

			if (zbite[2][i] == "BDK" || zbite[2][i] == "SDK")
				w3++;
		}

		if (w1 > w3)
			return 1;
		else if (w1 < w3)
			return 3;
		else
		{
			w1 = 0, w3 = 0;

			for (int i = 0; i < 9; i++)
			{
				if (zbite[0][i] == "SDT" || zbite[0][i] == "CDT")
					w1++;

				if (zbite[2][i] == "BDT" || zbite[2][i] == "SDT")
					w3++;
			}

			if (w1 > w3)
				return 1;
			else if (w1 < w3)
				return 3;
			else
			{
				w1 = 0, w3 = 0;

				for (int i = 0; i < 9; i++)
				{
					if (zbite[0][i] == "SSS" || zbite[0][i] == "CSS")
						w1++;

					if (zbite[2][i] == "BSS" || zbite[2][i] == "SSS")
						w3++;
				}

				if (w1 > w3)
					return 1;
				else if (w1 < w3)
					return 3;
				else
				{
					w1 = 0, w3 = 0;

					for (int i = 0; i < 9; i++)
					{
						if (zbite[0][i] == "SSK" || zbite[0][i] == "CSK")
							w1++;

						if (zbite[2][i] == "BSK" || zbite[2][i] == "SSK")
							w3++;
					}

					if (w1 > w3)
						return 1;
					else if (w1 < w3)
						return 3;
					else
					{
						w1 = 0, w3 = 0;

						for (int i = 0; i < 9; i++)
						{
							if (zbite[0][i] == "SST" || zbite[0][i] == "CST")
								w1++;

							if (zbite[2][i] == "BST" || zbite[2][i] == "SST")
								w3++;
						}

						if (w1 > w3)
							return 1;
						else if (w1 < w3)
							return 3;
						else
						{
							w1 = 0, w3 = 0;

							for (int i = 0; i < 9; i++)
							{
								if (zbite[0][i] == "SMS" || zbite[0][i] == "CMS")
									w1++;

								if (zbite[2][i] == "BMS" || zbite[2][i] == "SMS")
									w3++;
							}

							if (w1 > w3)
								return 1;
							else if (w1 < w3)
								return 3;
							else
							{
								w1 = 0, w3 = 0;

								for (int i = 0; i < 9; i++)
								{
									if (zbite[0][i] == "SMK" || zbite[0][i] == "CMK")
										w1++;

									if (zbite[2][i] == "BMK" || zbite[2][i] == "SMK")
										w3++;
								}

								if (w1 > w3)
									return 1;
								else if (w1 < w3)
									return 3;
								else
								{
									w1 = 0, w3 = 0;

									for (int i = 0; i < 9; i++)
									{
										if (zbite[0][i] == "SMT" || zbite[0][i] == "CMT")
											w1++;

										if (zbite[2][i] == "BMT" || zbite[2][i] == "SMT")
											w3++;
									}

									if (w1 > w3)
										return 1;
									else if (w1 < w3)
										return 3;
									else
									{
										return 0;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

int rozgrywka::remis_2_3() // zwarca, ktory gracz wygral w przypadku remisu(2- gracz 2, 3- gracz 3)
{
	int w2 = 0, w3 = 0;

	for (int i = 0; i < 9; i++)
	{
		if (zbite[1][i] == "BDS" || zbite[1][i] == "CDS")
			w2++;

		if (zbite[2][i] == "BDS" || zbite[2][i] == "SDS")
			w3++;
	}

	if (w2 > w3)
		return 2;
	else if (w2 < w3)
		return 3;
	else
	{
		w2 = 0, w3 = 0;

		for (int i = 0; i < 9; i++)
		{
			if (zbite[1][i] == "BDK" || zbite[1][i] == "CDK")
				w2++;

			if (zbite[2][i] == "BDK" || zbite[2][i] == "SDK")
				w3++;
		}

		if (w2 > w3)
			return 2;
		else if (w2 < w3)
			return 3;
		else
		{
			w2 = 0, w3 = 0;

			for (int i = 0; i < 9; i++)
			{
				if (zbite[1][i] == "BDT" || zbite[1][i] == "CDT")
					w2++;

				if (zbite[2][i] == "BDT" || zbite[2][i] == "SDT")
					w3++;
			}

			if (w2 > w3)
				return 2;
			else if (w2 < w3)
				return 3;
			else
			{
				w2 = 0, w3 = 0;

				for (int i = 0; i < 9; i++)
				{
					if (zbite[1][i] == "BSS" || zbite[0][i] == "CSS")
						w2++;

					if (zbite[2][i] == "BSS" || zbite[2][i] == "SSS")
						w3++;
				}

				if (w2 > w3)
					return 2;
				else if (w2 < w3)
					return 3;
				else
				{
					w2 = 0, w3 = 0;

					for (int i = 0; i < 9; i++)
					{
						if (zbite[1][i] == "BSK" || zbite[1][i] == "CSK")
							w2++;

						if (zbite[2][i] == "BSK" || zbite[2][i] == "SSK")
							w3++;
					}

					if (w2 > w3)
						return 2;
					else if (w2 < w3)
						return 3;
					else
					{
						w2 = 0, w3 = 0;

						for (int i = 0; i < 9; i++)
						{
							if (zbite[1][i] == "BST" || zbite[1][i] == "CST")
								w2++;

							if (zbite[2][i] == "BST" || zbite[2][i] == "SST")
								w3++;
						}

						if (w2 > w3)
							return 2;
						else if (w2 < w3)
							return 3;
						else
						{
							w2 = 0, w3 = 0;

							for (int i = 0; i < 9; i++)
							{
								if (zbite[1][i] == "BMS" || zbite[0][i] == "CMS")
									w2++;

								if (zbite[2][i] == "BMS" || zbite[2][i] == "SMS")
									w3++;
							}

							if (w2 > w3)
								return 2;
							else if (w2 < w3)
								return 3;
							else
							{
								w2 = 0, w3 = 0;

								for (int i = 0; i < 9; i++)
								{
									if (zbite[1][i] == "BMK" || zbite[1][i] == "CMK")
										w2++;

									if (zbite[2][i] == "BMK" || zbite[2][i] == "SMK")
										w3++;
								}

								if (w2 > w3)
									return 2;
								else if (w2 < w3)
									return 3;
								else
								{
									w2 = 0, w3 = 0;

									for (int i = 0; i < 9; i++)
									{
										if (zbite[1][i] == "BMT" || zbite[1][i] == "CMT")
											w2++;

										if (zbite[2][i] == "BMT" || zbite[2][i] == "SMT")
											w3++;
									}

									if (w2 > w3)
										return 2;
									else if (w2 < w3)
										return 3;
									else
									{
										return 0;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

int rozgrywka:: remis_1_2_3() // zwarca, ktory gracz wygral w przypadku remisu(1- gracz 1, 2- gracz 2, 3- gracz 3)
{
	int w1 = 0, w2 = 0, w3 = 0;
	
	for (int i = 0; i < 9; i++)
	{
		if (zbite[0][i] == "SDS" || zbite[0][i] == "CDS")
			w1++;

		if (zbite[1][i] == "BDS" || zbite[1][i] == "CDS")
			w2++;

		if (zbite[2][i] == "BDS" || zbite[2][i] == "SDS")
			w3++;
	}

	if (w1 > w2)
	{
		if (w1 > w3)
			return 1;
		else if (w1 < w3)
			return 3;
		else if (w1 == w3)
			return remis_1_3();
	}
	else if (w1 < w2)
	{
		if (w2 > w3)
			return 2;
		else if (w2 < w3)
			return 3;
		else if (w2 == w3)
			return remis_2_3();
	}
	else if (w1 == w2 == w3)
	{
		w1 = 0, w2 = 0, w3 = 0;

		for (int i = 0; i < 9; i++)
		{
			if (zbite[0][i] == "SDK" || zbite[0][i] == "CDK")
				w1++;

			if (zbite[1][i] == "BDK" || zbite[1][i] == "CDK")
				w2++;

			if (zbite[2][i] == "BDK" || zbite[2][i] == "SDK")
				w3++;
		}

		if (w1 > w2)
		{
			if (w1 > w3)
				return 1;
			else if (w1 < w3)
				return 3;
			else if (w1 == w3)
				return remis_1_3();
		}
		else if (w1 < w2)
		{
			if (w2 > w3)
				return 2;
			else if (w2 < w3)
				return 3;
			else if (w2 == w3)
				return remis_2_3();
		}
		else if (w1 == w2 == w3)
		{
			w1 = 0, w2 = 0, w3 = 0;

			for (int i = 0; i < 9; i++)
			{
				if (zbite[0][i] == "SDT" || zbite[0][i] == "CDT")
					w1++;

				if (zbite[1][i] == "BDK" || zbite[1][i] == "CDT")
					w2++;

				if (zbite[2][i] == "BDT" || zbite[2][i] == "SDT")
					w3++;
			}

			if (w1 > w2)
			{
				if (w1 > w3)
					return 1;
				else if (w1 < w3)
					return 3;
				else if (w1 == w3)
					return remis_1_3();
			}
			else if (w1 < w2)
			{
				if (w2 > w3)
					return 2;
				else if (w2 < w3)
					return 3;
				else if (w2 == w3)
					return remis_2_3();
			}
			else if (w1 == w2 == w3)
			{
				w1 = 0, w2 = 0, w3 = 0;

				for (int i = 0; i < 9; i++)
				{
					if (zbite[0][i] == "SSS" || zbite[0][i] == "CSS")
						w1++;

					if (zbite[1][i] == "BSS" || zbite[1][i] == "CSS")
						w2++;

					if (zbite[2][i] == "BSS" || zbite[2][i] == "SSS")
						w3++;
				}

				if (w1 > w2)
				{
					if (w1 > w3)
						return 1;
					else if (w1 < w3)
						return 3;
					else if (w1 == w3)
						return remis_1_3();
				}
				else if (w1 < w2)
				{
					if (w2 > w3)
						return 2;
					else if (w2 < w3)
						return 3;
					else if (w2 == w3)
						return remis_2_3();
				}
				else if (w1 == w2 == w3)
				{
					w1 = 0, w2 = 0, w3 = 0;

					for (int i = 0; i < 9; i++)
					{
						if (zbite[0][i] == "SSK" || zbite[0][i] == "CSK")
							w1++;

						if (zbite[1][i] == "BSK" || zbite[1][i] == "CSK")
							w2++;

						if (zbite[2][i] == "BSK" || zbite[2][i] == "SSK")
							w3++;
					}

					if (w1 > w2)
					{
						if (w1 > w3)
							return 1;
						else if (w1 < w3)
							return 3;
						else if (w1 == w3)
							return remis_1_3();
					}
					else if (w1 < w2)
					{
						if (w2 > w3)
							return 2;
						else if (w2 < w3)
							return 3;
						else if (w2 == w3)
							return remis_2_3();
					}
					else if (w1 == w2 == w3)
					{
						w1 = 0, w2 = 0, w3 = 0;

						for (int i = 0; i < 9; i++)
						{
							if (zbite[0][i] == "SST" || zbite[0][i] == "CST")
								w1++;

							if (zbite[1][i] == "BST" || zbite[1][i] == "CST")
								w2++;

							if (zbite[2][i] == "BST" || zbite[2][i] == "SST")
								w3++;
						}

						if (w1 > w2)
						{
							if (w1 > w3)
								return 1;
							else if (w1 < w3)
								return 3;
							else if (w1 == w3)
								return remis_1_3();
						}
						else if (w1 < w2)
						{
							if (w2 > w3)
								return 2;
							else if (w2 < w3)
								return 3;
							else if (w2 == w3)
								return remis_2_3();
						}
						else if (w1 == w2 == w3)
						{
							w1 = 0, w2 = 0, w3 = 0;

							for (int i = 0; i < 9; i++)
							{
								if (zbite[0][i] == "SMS" || zbite[0][i] == "CMS")
									w1++;

								if (zbite[1][i] == "BMS" || zbite[1][i] == "CMS")
									w2++;

								if (zbite[2][i] == "BMS" || zbite[2][i] == "SMS")
									w3++;
							}

							if (w1 > w2)
							{
								if (w1 > w3)
									return 1;
								else if (w1 < w3)
									return 3;
								else if (w1 == w3)
									return remis_1_3();
							}
							else if (w1 < w2)
							{
								if (w2 > w3)
									return 2;
								else if (w2 < w3)
									return 3;
								else if (w2 == w3)
									return remis_2_3();
							}
							else if (w1 == w2 == w3)
							{
								w1 = 0, w2 = 0, w3 = 0;

								for (int i = 0; i < 9; i++)
								{
									if (zbite[0][i] == "SMK" || zbite[0][i] == "CMK")
										w1++;

									if (zbite[1][i] == "BMK" || zbite[1][i] == "CMK")
										w2++;

									if (zbite[2][i] == "BMK" || zbite[2][i] == "SMK")
										w3++;
								}

								if (w1 > w2)
								{
									if (w1 > w3)
										return 1;
									else if (w1 < w3)
										return 3;
									else if (w1 == w3)
										return remis_1_3();
								}
								else if (w1 < w2)
								{
									if (w2 > w3)
										return 2;
									else if (w2 < w3)
										return 3;
									else if (w2 == w3)
										return remis_2_3();
								}
								else if (w1 == w2 == w3)
								{
									w1 = 0, w2 = 0, w3 = 0;

									for (int i = 0; i < 9; i++)
									{
										if (zbite[0][i] == "SMT" || zbite[0][i] == "CMT")
											w1++;

										if (zbite[1][i] == "BMT" || zbite[1][i] == "CMT")
											w2++;

										if (zbite[2][i] == "BMT" || zbite[2][i] == "SMT")
											w3++;
									}

									if (w1 > w2)
									{
										if (w1 > w3)
											return 1;
										else if (w1 < w3)
											return 3;
										else if (w1 == w3)
											return remis_1_3();
									}
									else if (w1 < w2)
									{
										if (w2 > w3)
											return 2;
										else if (w2 < w3)
											return 3;
										else if (w2 == w3)
											return remis_2_3();
									}
									else if (w1 == w2 == w3)
										return 0;
									else
										return remis_1_2();
								}
								else
									return remis_1_2();
							}
							else
								return remis_1_2();
						}
						else
							return remis_1_2();
					}
					else
						return remis_1_2();
				}
				else
					return remis_1_2();
			}
			else
				return remis_1_2();
		}
		else
			return remis_1_2();
	}
	else
		return remis_1_2();

		return 0;
}