#pragma once
#include"uzytkownik.h"
#include"plansza.h"

class rozgrywka
{
private:
	int ruch; // ktory gracz wykonuje ruch
	string **zbite; // przechowuje jakie pionki zbili gracze
	int g1, g2, g3; 

public:
	plansza *p1;
	plansza *p2;
	plansza *p3;

	pionek *bmt, *bst, *bdt, *smt, *sst, *sdt, *cmt, *cst, *cdt;
	pionek *bmk, *bsk, *bdk, *smk, *ssk, *sdk, *cmk, *csk, *cdk;
	pionek *bms, *bss, *bds, *sms, *sss, *sds, *cms, *css, *cds;

	uzytkownik *gracz1;
	uzytkownik *gracz2;
	uzytkownik *gracz3;

	rozgrywka();
	~rozgrywka();

	void menu1();
	void menu2();
	void stworz_p(); // tworzenie planszy i pionkow
	void ustawienie_pionkow(); // ustawienie pionkow
	void gra(); //rozgrywka
	int wygrana(); // zwrocenie zwyciescy danej gry
	void kto();  // wypisanie zwyciescy danej rozgrywki
	void dodanie_wyniku_do_tablicy(string, int); // dodanie zwyciescy do tablicy wynikow
	void tablica_wynikow(); // wypisanie wszystkich zwyciescow zakonczonych gier
	void save(); // zapisanie gry
	bool wczytaj_save(); // wczytanie save
	void usun_pionka(string); // usuniecie pionka po biciu
	int remis_1_2(); // wylonienie zwyciezcy, gdy gracz 1 i garcz 2 maja tyle samo punktow
	int remis_1_3(); // wylonienie zwyciezcy, gdy gracz 1 i garcz 3 maja tyle samo punktow
	int remis_2_3(); // wylonienie zwyciezcy, gdy gracz 2 i garcz e maja tyle samo punktow
	int remis_1_2_3(); // wylonienie zwyciezcy, gdy gracz 1, garcz 2 i gracz 3 maja tyle samo punktow
};

template<typename T1, typename T2, typename T3>
int ilosc_ruchow_plansza(T1 *arg1,T2 *arg2,T3 *arg3) // zwraca ilosc mozliwych ruchow na planszy
{
	int ruchy = 0;
	int x, y;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (arg3->mapa[i][j][0] == arg3->get_gorny())
			{
				y = i;
				x = j - 1;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg1->spr_bicia(arg3->mapa[i][j], arg3->mapa[y][x]) == 1)
						ruchy += 1;

				x = j + 1;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg1->spr_bicia(arg3->mapa[i][j], arg3->mapa[y][x]) == 1)
						ruchy += 1;

				y = i + 1;
				x = j;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg3->mapa[y][x] == "0")
						ruchy += 1;
					else if (arg1->spr_bicia(arg3->mapa[i][j], arg3->mapa[y][x]) == 1)
						ruchy += 1;

				x = j - 1;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg3->mapa[y][x] == "0")
						ruchy += 1;
					else if (arg1->spr_bicia(arg3->mapa[i][j], arg3->mapa[y][x]) == 1)
						ruchy += 1;

				x = j + 1;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg3->mapa[y][x] == "0")
						ruchy += 1;
					else if (arg1->spr_bicia(arg3->mapa[i][j], arg3->mapa[y][x]) == 1)
						ruchy += 1;
			}


			if (arg3->mapa[i][j][0] == arg3->get_dolny())
			{
				y = i;
				x = j - 1;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg2->spr_bicia(arg3->mapa[i][j], arg3->mapa[y][x]) == 1)
						ruchy += 1;

				x = j + 1;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg2->spr_bicia(arg3->mapa[i][j], arg3->mapa[y][x]) == 1)
						ruchy += 1;

				y = i - 1;
				x = j;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg3->mapa[y][x] == "0")
						ruchy += 1;
					else if (arg2->spr_bicia(arg3->mapa[i][j], arg3->mapa[y][x]) == 1)
						ruchy += 1;

				x = j - 1;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg3->mapa[y][x] == "0")
						ruchy += 1;
					else if (arg2->spr_bicia(arg3->mapa[i][j], arg3->mapa[y][x]) == 1)
						ruchy += 1;

				x = j + 1;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg3->mapa[y][x] == "0")
						ruchy += 1;
					else if (arg2->spr_bicia(arg3->mapa[i][j], arg3->mapa[y][x]) == 1)
						ruchy += 1;
			}
		}
	}

	return ruchy;
}

template<typename T1, typename T2, typename T3>
int ilosc_ruchow_gracza(T1 *arg1, T2 *arg2, T3 *arg3) // zwraca ilosc mozliwych ruchow gracza
{
	int ruchy = 0;
	int x, y;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (arg1->mapa[i][j][0] == arg3->get_kolor())
			{
				y = i;
				x = j - 1;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg3->spr_bicia(arg1->mapa[i][j], arg1->mapa[y][x]) == 1)
						ruchy += 1;

				x = j + 1;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg3->spr_bicia(arg1->mapa[i][j], arg1->mapa[y][x]) == 1)
						ruchy += 1;


				if (arg1->get_gorny() == arg3->get_kolor())
					y = i + 1;
				else if (arg1->get_dolny() == arg3->get_kolor())
					y = i - 1;


				x = j;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg1->mapa[y][x] == "0")
						ruchy += 1;
					else if (arg3->spr_bicia(arg1->mapa[i][j], arg1->mapa[y][x]) == 1)
						ruchy += 1;

				x = j - 1;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg1->mapa[y][x] == "0")
						ruchy += 1;
					else if (arg3->spr_bicia(arg1->mapa[i][j], arg1->mapa[y][x]) == 1)
						ruchy += 1;

				x = j + 1;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg1->mapa[y][x] == "0")
						ruchy += 1;
					else if (arg3->spr_bicia(arg1->mapa[i][j], arg1->mapa[y][x]) == 1)
						ruchy += 1;
			}

			if (arg2->mapa[i][j][0] == arg3->get_kolor())
			{
				y = i;
				x = j - 1;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg3->spr_bicia(arg2->mapa[i][j], arg2->mapa[y][x]) == 1)
						ruchy += 1;

				x = j + 1;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg3->spr_bicia(arg2->mapa[i][j], arg2->mapa[y][x]) == 1)
						ruchy += 1;

				if (arg2->get_gorny() == arg3->get_kolor())
					y = i + 1;
				else if (arg2->get_dolny() == arg3->get_kolor())
					y = i - 1;
	
				x = j;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg2->mapa[y][x] == "0")
						ruchy += 1;
					else if (arg3->spr_bicia(arg2->mapa[i][j], arg2->mapa[y][x]) == 1)
						ruchy += 1;

				x = j - 1;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg2->mapa[y][x] == "0")
						ruchy += 1;
					else if (arg3->spr_bicia(arg2->mapa[i][j], arg2->mapa[y][x]) == 1)
						ruchy += 1;

				x = j + 1;
				if ((5 > x&&x > -1) && (5 > y&&y > -1))
					if (arg2->mapa[y][x] == "0")
						ruchy += 1;
					else if (arg3->spr_bicia(arg2->mapa[i][j], arg2->mapa[y][x]) == 1)
						ruchy += 1;

			}
		}
	}

	return ruchy;
}