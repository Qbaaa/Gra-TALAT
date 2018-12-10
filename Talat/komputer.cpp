#include"komputer.h"
#include<ctime>
#include <Windows.h>


komputer::komputer() {}

komputer::komputer(string _imie,string _kolor,int _punkty):uzytkownik(_imie,_kolor,_punkty) {}

komputer::~komputer() {}

string komputer::ruch(plansza *arg, plansza *arg2,int yg,int yd) // zwraca "0" ruch odbyl sie na puste pole, zwraca usun(nazwa zbitego pionka) w ruch zbilismy jakiegos pionka
{
	int px, py; //  wspolrzedne pionka, ktorym sie ruszam
	int rx, ry; //  wspolrzedne gdzie postawic pionka 
	int wybor, spr;
	string usun = "0";

	srand(time(NULL));
	system("cls");
	cout << "Ruch: " << imie <<endl;
	cout << "Poczekaj teraz ruch " << imie << endl;
	Sleep(1000);
	
	while (true)
	{
		wybor = (rand() % 3) + 1;
		
		if (wybor == arg->get_nr()) // wybranie jednej z mozliwych plansz
		{
			px = rand() % 5 + 1;
			px--;

			py = rand() % 5 + 1;
			py--;

			if (arg->mapa[py][px] == "0") // sprawdzenie czy w danym miejscu nie ma pionka
				continue;
			else if (arg->mapa[py][px][0] != kolor[0]) // sprawdzenie czy ruszamy sie swoim pionkiem
				continue;
			else // ruch wlasnym pionkiem
			{
				rx = rand() % 5 + 1;
				rx--;
			
				ry = rand() % 5 + 1;
				ry--;
				
				spr = pop_ruchu(px, py, rx, ry, yg); // sprawdzenie ,ktory ruch zostal wykonany
				if (spr == 2)
				{

					if (arg->mapa[ry][rx] == "0") // sprawdzenie czy w danym miejscu nie ma pionka
						continue;
					else // w danym miejscu jest pionek
					{
						spr = spr_bicia(arg->mapa[py][px], arg->mapa[ry][rx]); // sprawdzenie ,czy bicie jest mozliwe
						if (spr == 0) // bicie jest niemozliwe
							continue;
						else // bicie jest poprawne
						{
							usun = arg->mapa[ry][rx];
							arg->mapa[ry][rx] = arg->mapa[py][px];
							arg->mapa[py][px] = "0";
							punkty += 5;
							return usun;
						}
					}
				}
				else if (spr == 1) // ruch do przodu
				{
					if (arg->mapa[ry][rx] == "0") // sprawdzenie czy w danym miejscu nie ma pionka
					{
						arg->mapa[ry][rx] = arg->mapa[py][px];
						arg->mapa[py][px] = "0";
						punkty += d_punktow(yg, ry);
						break;
					}
					else // w danym miejscu jest pionek
					{
						spr = spr_bicia(arg->mapa[py][px], arg->mapa[ry][rx]); // sprawdzenie ,czy bicie jest mozliwe
						if (spr == 0) // bicie jest niemozliwe
							continue;
						else // bicie jest poprawne
						{
							usun = arg->mapa[ry][rx];
							arg->mapa[ry][rx] = arg->mapa[py][px];
							arg->mapa[py][px] = "0";
							punkty += 5;
							punkty += d_punktow(yg, ry);
							return usun;
						}
					}
				}
				else  // ruch byl niepoprawny
					continue;
			}
		}
		else if (wybor == arg2->get_nr()) // wybranie drugiej z mozliwych plansz
		{
			
			px = rand() % 5 + 1;
			px--;
			
			py = rand() % 5 + 1;
			py--;
			
			if (arg2->mapa[py][px] == "0") // sprawdzenie czy w danym miejscu nie ma pionka
				continue;
			else if (arg2->mapa[py][px][0] != kolor[0]) // sprawdzenie czy ruszamy sie swoim pionkiem
				continue;
			else // ruch wlasnym pionkiem
			{
				rx = rand() % 5 + 1;
				rx--;
		
				ry = rand() % 5 + 1;
				ry--;
				spr = pop_ruchu(px, py, rx, ry, yd); // sprawdzenie ,ktory ruch zostal wykonany
				if (spr == 2) // ruch w bok
				{

					if (arg2->mapa[ry][rx] == "0") // sprawdzenie czy w danym miejscu nie ma pionka
						continue;
					else // w danym miejscu jest pionek
					{
						spr = spr_bicia(arg2->mapa[py][px], arg2->mapa[ry][rx]); // sprawdzenie ,czy bicie jest mozliwe
						if (spr == 0) // bicie jest niemozliwe
							continue;
						else // bicie jest poprawne
						{
							usun = arg2->mapa[ry][rx];
							arg2->mapa[ry][rx] = arg2->mapa[py][px];
							arg2->mapa[py][px] = "0";
							punkty += 5;
							return usun;
						}
					}
				}
				else if (spr == 1) // ruch do przodu
				{
					if (arg2->mapa[ry][rx] == "0") // sprawdzenie czy w danym miejscu nie ma pionka
					{
						arg2->mapa[ry][rx] = arg2->mapa[py][px];
						arg2->mapa[py][px] = "0";
						punkty += d_punktow(yd, ry);
						break;
					}
					else // w danym miejscu jest pionek
					{
						spr = spr_bicia(arg2->mapa[py][px], arg2->mapa[ry][rx]); // sprawdzenie ,czy bicie jest mozliwe
						if (spr == 0) // bicie jest niemozliwe
							continue;
						else // bicie jest poprawne
						{
							usun = arg2->mapa[ry][rx];
							arg2->mapa[ry][rx] = arg2->mapa[py][px];
							arg2->mapa[py][px] = "0";
							punkty += 5;
							punkty += d_punktow(yd, ry);
							return usun;
						}
					}
				}
				else // ruch byl niepoprawny
					continue;
			}
		}
	}

	return usun;
}

void komputer::ustaw(plansza *arg, plansza *arg2,pionek *p,int yd,int yg) 
{
	int x;
	int wybor;
	srand(time(NULL));
	system("cls");
	cout << "Ruch: " << imie << endl;
	cout << "Poczekaj teraz ustawia pionki:" << imie << endl;
	Sleep(1000);
	
	
	while (true)
	{
		wybor=(rand()%3)+1;

		if (wybor == arg->get_nr()) // wybranie jednej z mozliwych plansz
		{
			
			x= (rand() % 5);
			if (arg->mapa[yd][x] == "0") // sprawdzenie czy w danym miejscu jest pionek(nie ma pionka)
			{
				arg->mapa[yd][x] = p->ozn_p();  // ustawienie pionka na danym miejscu
				break;
			}
		}
		else if (wybor == arg2->get_nr()) // wybranie drugiej z mozliwych plansz
		{
			x = (rand() % 5);
			if (arg2->mapa[yg][x] == "0") // sprawdzenie czy w danym miejscu jest pionek(nie ma pionka)
			{
				arg2->mapa[yg][x] = p->ozn_p(); // ustawienie pionka na danym miejscu
				break;
			}	
		}
	}
}
