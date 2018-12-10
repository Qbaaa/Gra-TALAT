#define _CRT_SECURE_NO_WARNINGS
#include"czlowiek.h"

czlowiek::czlowiek() {}

czlowiek::czlowiek(string _imie,string _kolor,int _punkty):uzytkownik(_imie,_kolor,_punkty) {}

czlowiek::~czlowiek() {}

string czlowiek::ruch(plansza *arg, plansza *arg2,int yg,int yd)  // zwraca "0" ruch odbyl sie na puste pole, zwraca usun(nazwa zbitego pionka) w ruch zbilismy jakiegos pionka
{
	int px, py;  //  wspolrzedne pionka, ktorym sie ruszam
	int rx, ry;  //  wspolrzedne gdzie postawic pionka 
	int wybor,spr;
	string usun = "0";

	system("cls");
	while (true)
	{
		cout << "Plansza " << arg->get_nr() << " :" << "                              Plansza " << arg2->get_nr() << " :";
		arg->rysuj_2(*arg2);   // rysowanie plansz

		cout << endl;
		cout << "RUCH : " << kolor << endl;
		cout << "Z, ktorej planszych chcesz dokonac ruchu (" << arg->get_nr() << " lub " << arg2->get_nr() << ") : ";
		while (!(cin >> wybor) || (wybor != arg->get_nr() && wybor != arg2->get_nr() )|| getchar() != '\n')  // pobieranie danych, z ktorej planszy mamy sie ruszyc
		{
			cout << "BLAD! Podaj jeszcze raz: ";
			while (getchar() != '\n');
			cin.clear();
			cin.sync();
		}

		if (wybor == arg->get_nr()) // wybranie jednej z mozliwych plansz 
		{
			system("cls");
			cout << "Plansza " << arg->get_nr() << " :";
			arg->rysuj_1();  // rysowanie planszy
			cout << endl;
			cout << "RUCH : " << kolor << endl;
			cout << "Podaj wspolrzedne pionka, ktorym masz sie ruszyc : " << endl;
			cout << "x : " ;
			while (!(cin >> px) || px < 1 || px > 5 || getchar() != '\n') // pobieranie wspolrzednej x z planszy
			{
				cout << "BLAD! Podaj jeszcze raz: ";
				while (getchar() != '\n');
				cin.clear();
				cin.sync();
			}
			px--;
			cout << "y : ";
			while (!(cin >> py) || py < 1 || py > 5 || getchar() != '\n') // pobieranie wspolrzednej y z planszy
			{
				cout << "BLAD! Podaj jeszcze raz: ";
				while (getchar() != '\n');
				cin.clear();
				cin.sync();
			}
			py--;
			if (arg->mapa[py][px] == "0") // sprawdzenie czy w danym miejscu nie ma pionka
			{
				system("cls");
				cout << "W tym miejscu nie ma pionka!!!" << endl << endl;
				continue;
			}
			else if(arg->mapa[py][px][0]!=kolor[0] ) // sprawdzenie czy ruszamy sie swoim pionkiem
			{
				system("cls");
				cout << "Tym pionkiem nie mozesz sie ruszac!!!" << endl << endl;
				continue;
			}
			else // ruch wlasnym pionkiem
			{
				cout << "Podaj wspolrzedne gdzie chcesz postawic pionka : "<<endl;
				cout << "x: ";
				while (!(cin >> rx) || rx < 1 || rx > 5 || getchar() != '\n') // pobieranie wspolrzednej x (miejsca do ktorego chcemy poprowadzic pionka)
				{
					cout << "BLAD! Podaj jeszcze raz : ";
					while (getchar() != '\n');
					cin.clear();
					cin.sync();
				}
				rx--;
				cout << "y: ";
				while (!(cin >> ry) || ry < 1 || ry > 5 || getchar() != '\n') // pobieranie wspolrzednej y (miejsca do ktorego chcemy poprowadzic pionka)
				{
					cout << "BLAD! Podaj jeszcze raz: ";
					while (getchar() != '\n');
					cin.clear();
					cin.sync();
				}
				ry--;
				spr=pop_ruchu(px, py, rx, ry, yg); // sprawdzenie ,ktory ruch zostal wykonany
				
				if (spr == 2) // ruch w bok
				{
					if (arg->mapa[ry][rx] == "0") // sprawdzenie czy w danym miejscu nie ma pionka
					{
						system("cls");
						cout << "Niepoprawny ruch!!!" << endl << endl;
						continue;
					}
					else // w danym miejscu jest pionek
					{
						spr = spr_bicia(arg->mapa[py][px], arg->mapa[ry][rx]); // sprawdzenie ,czy bicie jest mozliwe
						if (spr == 0) // bicie jest niemozliwe
						{
							system("cls");
							cout << "BICIE JEST NIEMOZLIWE !!!" << endl << endl;
							continue;
						}
						else // bicie jest poprawne
						{
							usun = arg->mapa[ry][rx]; 
							arg->mapa[ry][rx] = arg->mapa[py][px];
							arg->mapa[py][px] = "0";
							punkty += 5;  // dodanie punktow za zbicie pionka
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
						{
							system("cls");
							cout << "BICIE JEST NIEMOZLIWE !!!" << endl << endl;
							continue;
						}
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
				else if(spr == 0) // ruch byl niepoprawny
				{
					system("cls");
					cout << "Niepoprawny ruch!!!" << endl<< endl;
					continue;
				}
			}
		}
		else if (wybor == arg2->get_nr()) // wybranie drugiej z mozliwych plansz
		{
			system("cls");
			cout << "Plansza " << arg2->get_nr() << " :";
			arg2->rysuj_1();
			cout << endl;
			cout << "RUCH : " << kolor << endl;
			cout << "Podaj wspolrzedne pionka, ktorym mamsz sie ruszyc : " << endl;
			cout << "x: ";
			while (!(cin >> px) || px < 1 || px > 5 || getchar() != '\n')
			{
				cout << "BLAD! Podaj jeszcze raz: ";
				while (getchar() != '\n');
				cin.clear();
				cin.sync();
			}
			px--;
			cout << "y: ";
			while (!(cin >>py) || py < 1 || py > 5 || getchar() != '\n')
			{
				cout << "BLAD! Podaj jeszcze raz: ";
				while (getchar() != '\n');
				cin.clear();
				cin.sync();
			}
			py--;

			if (arg2->mapa[py][px] == "0") // sprawdzenie czy w danym miejscu nie ma pionka
			{
				system("cls");
				cout << "W tym miejscu nie ma pionka!!!" << endl << endl;
				continue;
			}
			else if (arg2->mapa[py][px][0] != kolor[0]) // sprawdzenie czy ruszamy sie swoim pionkiem
			{
				system("cls");
				cout << "Tym pionkiem nie mozesz sie ruszac!!!" << endl << endl;
				continue;
			}
			else // ruch wlasnym pionkiem
			{
				cout << "Podaj wspolrzedne gdzie chcesz postawic pionka : " << endl;
				cout << "x: ";
				while (!(cin >> rx) || rx < 1 || rx > 5 || getchar() != '\n')
				{
					cout << "BLAD! Podaj jeszcze raz: ";
					while (getchar() != '\n');
					cin.clear();
					cin.sync();
				}
				rx--;
				cout << "y: ";
				while (!(cin >> ry) || ry < 1 || ry > 5 || getchar() != '\n')
				{
					cout << "BLAD! Podaj jeszcze raz: ";
					while (getchar() != '\n');
					cin.clear();
					cin.sync();
				}
				ry--;
				spr = pop_ruchu(px, py, rx, ry, yd); // sprawdzenie ,ktory ruch zostal wykonany
				if (spr == 2) // ruch w bok
				{

					if (arg2->mapa[ry][rx] == "0") // sprawdzenie czy w danym miejscu jest pionek (w tym miejscu nie ma pionka)
					{
						system("cls");
						cout << "Niepoprawny ruch!!!" << endl << endl;
						continue;
					}
					else // w danym miejscu jest pionek
					{
						spr = spr_bicia(arg2->mapa[py][px], arg2->mapa[ry][rx]); // sprawdzenie ,czy bicie bylo mozliwe
						if (spr == 0) // bicie bylo niemozliwe
						{
							system("cls");
							cout << "BICIE JEST NIEMOZLIWE !!!" << endl << endl;
							continue;
						}
						else // bicie bylo poprawne
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
					if (arg2->mapa[ry][rx] == "0") // sprawdzenie czy w danym miejscu jest pionek (w tym miejscu nie ma pionka)
					{
						arg2->mapa[ry][rx] = arg2->mapa[py][px];
						arg2->mapa[py][px] = "0";
						punkty += d_punktow(yd, ry);
						break;
					}
					else // w danym miejscu jest pionek
					{
						spr = spr_bicia(arg2->mapa[py][px], arg2->mapa[ry][rx]); // sprawdzenie ,czy bicie jest mozliwe
						if (spr == 0) // bicie bylo niemozliwe
						{
							cout << "BICIE JEST NIEMOZLIWE !!!" << endl << endl;
							continue;
						}
						else // bicie bylo poprawne
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
				{
					system("cls");
					cout << "Niepoprawny ruch!!!" << endl << endl;
					continue;
				}
			}
		}
	}

	return usun; // zwraca, ktory pionek zostal usuniety
}

void czlowiek::ustaw(plansza *arg, plansza *arg2,pionek*p,int yg,int yd)
{
	int x;
	int wybor;
	system("cls");
	while (true)
	{
		cout << "Plansza " << arg->get_nr() << " :"<< "                              Plansza " << arg2->get_nr() << " :";
		arg->rysuj_2(*arg2);

		cout << endl;
		cout << "Ruch : " << imie << endl;
		cout << p->get_nazwa() << endl;
		cout << "Na, ktorej planszych chcesz ustawi pionek (" << arg->get_nr() << " lub " << arg2->get_nr() << "): ";
		while (!(cin >> wybor) || wybor != arg->get_nr() && wybor != arg2->get_nr() || getchar() != '\n')
		{
			cout << "BLAD! Podaj jeszcze raz: ";
			while (getchar() != '\n');
			cin.clear();
			cin.sync();
		}

		if (wybor == arg->get_nr()) // wybranie jednej z mozliwych plansz
		{
			system("cls");
			cout << "Plansza " << arg->get_nr() << " :";
			arg->rysuj_1();
			cout << endl;
			cout << "Ruch : " << imie << endl;
			cout << p->get_nazwa() << endl;
			cout << "Na, ktoryrym polu ustawic pionek: "<<kolor[0];
			while (!(cin >> x) || x < 1 || x > 5 || getchar() != '\n')
			{
				cout << "BLAD! Podaj jeszcze raz: " << kolor[0];
				while (getchar() != '\n');
				cin.clear();
				cin.sync();
			}
			x--;

			if (arg->mapa[yg][x] == "0") // sprawdzenie czy w danym miejscu jest pionek(nie ma pionka)
			{
				arg->mapa[yg][x] = p->ozn_p();  // ustawienie pionka na danym miejscu
				break;
			}
			else // pole jest juz zajete przez pionka
			{
				system("cls");
				cout << "Pole jest juz zajete!!!" << endl<<endl;
			}
		}
		else if (wybor == arg2->get_nr()) // wybranie drugiej z mozliwych plansz
		{
			system("cls");
			cout << "Plansza " << arg2->get_nr() << " :";
			arg2->rysuj_1();
			cout << endl;
			cout << "Ruch : " << imie << endl;
			cout << p->get_nazwa() << endl;
			cout << "Na, ktoryrym polu ustawic pionek: "<< kolor[0];
			while (!(cin >> x) || x < 1 || x > 5 || getchar() != '\n')
			{
				cout << "BLAD! Podaj jeszcze raz: "<< kolor[0];
				while (getchar() != '\n');
				cin.clear();
				cin.sync();
			}
			x--;

			if (arg2->mapa[yg][x] == "0") // sprawdzenie czy w danym miejscu jest pionek(nie ma pionka)
			{
				arg2->mapa[yg][x] = p->ozn_p(); // ustawienie pionka na danym miejscu
				break;
			}
			else // pole jest juz zajete przez pionka
			{
				system("cls");
				cout << "Pole jest juz zajete!!!" << endl << endl;
			}
		}
	}
}