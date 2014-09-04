/* Keszitette:        */
/* Erdohegyi Balint   */
/*					  */
/* Program: Reversi   */

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <windows.h>
#include "Reversi.h"

using namespace std;

Reversi::Reversi()
{
	alaphelyzet();
}

Reversi::~Reversi()
{
	torol();
}

void Reversi::alaphelyzet()
{
	jatekos=1;						/* kezdo jatekos a feher */
		for(int i=0;i<10;++i)
			for(int j=0;j<10;++j)
				tabla[i][j]=NULL;	/* a 10x10-es tabla osszes mezojenek pointeret nullara allitjuk */

	tabla[4][4]=new korong(1);		/* majd a kezdo korongokat feltesszuk */
	tabla[5][5]=new korong(1);
	tabla[4][5]=new korong(2);
	tabla[5][4]=new korong(2);
}

void Reversi::torol()
{
	for(int i=0;i<10;++i)
		for(int j=0;j<10;++j)
			delete tabla[i][j];		/*  az osszes mezot torli */
}

void Reversi::rajzol(int uzenet) const
{
	int vege=1;			/* alapbol feltesszuk hogy vege a jateknak */

	CONSOLE_SCREEN_BUFFER_INFO sbinf;	/* ebbe a strukturaba lesz lekerdezve a kurzor pozicioja tobbek kozott */
	COORD pos;			/* koordinata struktura a kurzor poziciojanak beallitasahoz */
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);	/* hozzaferes a std output kezelesehez */
	
	pos.X=40;								/* menu kirajzolasa (40,1) koordinatatol kezdve */
	pos.Y=1;
	SetConsoleCursorPosition(hStdOut,pos);
	cout << "[1] Uj jatek";
	pos.Y=2;
	SetConsoleCursorPosition(hStdOut,pos);
	cout << "[2] Betoltes";
	pos.Y=3;
	SetConsoleCursorPosition(hStdOut,pos);
	cout << "[3] Mentes";
	pos.Y=5;
	SetConsoleCursorPosition(hStdOut,pos);
	cout << "[X] Kilepes";

	pos.X=0;								/* kurzort a legelejere visszaallitja */
	pos.Y=0;
	SetConsoleCursorPosition(hStdOut,pos);

	cout << "     A  B  C  D  E  F  G  H      " << endl;		/* a jatekmezo kirajzolasa */
	for(int i=1;i<9;++i)
	{
		cout << "    +--+--+--+--+--+--+--+--+           " << endl;
		cout << "  " << i <<  " |";
		for(int j=1;j<9;++j)
		{
			if(tabla[i][j]==NULL)	/* ha nullpointer van, ott ures a mezo */
			{
				cout << "  ";
				vege=0;				/* ha mar van egy ures mezo, akkor meg nincs vege */
			}
			if(tabla[i][j]!=NULL && tabla[i][j]->szin==1)	/* ha nem nullpoinet, akkor a megfelelo szin kirajzolja */
				cout << (char)178 << (char)178;
			if(tabla[i][j]!=NULL && tabla[i][j]->szin==2)
				cout << (char)176 << (char)176;
			cout << "|";
		}
		cout << " " << i << "    " << endl;
	}
	cout << "    +--+--+--+--+--+--+--+--+  " << endl;
	cout << "     A  B  C  D  E  F  G  H" << endl << endl;

	GetConsoleScreenBufferInfo(hStdOut, &sbinf);	/* kurzor poziciojanak lekerdezese tobbek kozott */
	pos=sbinf.dwCursorPosition;						/* kurzor poziciojanak elmentese */
	cout << "                                             " << endl;;	/* tabla alatti elso sor torlese */
	if(!uzenet)
	{
		for(int i=0; i<3; ++i)
			cout << "                                             " << endl;	/* osszes maradek sor torlese */

		
	}

	SetConsoleCursorPosition(hStdOut,pos);		/* kurzor visszaallitasa a tabla ala kozvetlen */
	if(!vege)

	{
		jatekos==1 ? cout << " Feher: " : cout << " Fekete: ";	/* a soron leve jatekos kijelzese */
	}
}

void Reversi::jatekosValtas()
{
	jatekos = jatekos==1 ? 2 : 1;	/* jatekos valtasa */
}

bool Reversi::lepesJo(int s, int o) const	/* a lepes ellenorzese */
{
	int ellenfel = jatekos==1 ? 2 : 1;	/* ellenfel szamanak beallitasa */

	if(s<1 || o<1 || s>8 || o>8)	/* nem letezik ilyen mezo a tablan */
		return false;

	if(tabla[s][o]!=NULL)	/* van már ott korong */
		return false;

	/* van-e szomszedos ellenfel korong */
	int sz=0;
	for(int i=-1; i<=1; ++i)	/* a szomszedait megnezi */
	{
		for(int j=-1; j<=1; ++j)
		{
			if(tabla[s+i][o+j]!=NULL && tabla[s+i][o+j]->szin==ellenfel)
				sz=1;			/* ha a szomszedos korong ellenfele, akkor jo */
		}
	}
	if(sz==0)					/* nem volt szomszédos ellenfel korong */
		return false;
	

	/* lehet-e forditani  */
	int s2=s, o2=o, jo=0;
	for(int i=-1; i<=1; ++i)	/* megnezi a szomszedait */
	{
		for(int j=-1; j<=1; ++j)
		{
			if(tabla[s+i][o+j]!=NULL && tabla[s+i][o+j]->szin==ellenfel)	/* ha az egyik ellenfele */
			{
				while(tabla[s2+i][o2+j]!=NULL && tabla[s2+i][o2+j]->szin==ellenfel)
				{
					s2+=i;		/* es annak ugyanilyen iranyu szomszedja is ellenfele */
					o2+=j;		/* es igy sorban vegignezi */
				}
				if(tabla[s2+i][o2+j]!=NULL && tabla[s2+i][o2+j]->szin==jatekos)
					jo=1;		/* majd a vegen egy sajat korong van, akkor jo */
				s2=s, o2=o;
			}
		}
	}
	if(jo==0)
		return false;

	return true;
}

void Reversi::lep(int s, int o)
{
	if(s<1 || o<1 || s>8 || o>8)			/* ha nem megfelelo indexeket vett at */
		throw("Tabla indexelesi hiba!");	/* akkor dobjon egy kivetelt */
	tabla[s][o]=new korong(jatekos);		/* uj korong letrehozasa a soron leve jatekos szinevel */
	fordit(s,o);							/* majd automatikusan forgassa at a megfelelo korongokat */
}

void Reversi::fordit(int s, int o) const
{
	int ellenfel = jatekos==1 ? 2 : 1;

	/* megkeresi azokat a sorokat, ahol lehet forgatni */
	int s2=s, o2=o;
	for(int i=-1; i<=1; ++i)		/* megnezi a szomszedait */
	{
		for(int j=-1; j<=1; ++j)
		{
			if(tabla[s+i][o+j]!=NULL && tabla[s+i][o+j]->szin==ellenfel)	/* ha az egyik ellenfele */
			{
				while(tabla[s2+i][o2+j]!=NULL && tabla[s2+i][o2+j]->szin==ellenfel)
				{
					s2+=i;						/* es annak ugyanilyen iranyu szomszedja is ellenfele */
					o2+=j;						/* es igy sorban vegignezi */
				}
				if(tabla[s2+i][o2+j]!=NULL && tabla[s2+i][o2+j]->szin==jatekos)
				{
					s2=s, o2=o;					/* majd a vegen egy sajat korong van, akkor jo */
					while(tabla[s2+i][o2+j]!=NULL && tabla[s2+i][o2+j]->szin==ellenfel)
					{
						s2+=i;					/* ekkor ujra menjen vegig a soron, es kozben forgasson */
						o2+=j;
						tabla[s2][o2]->atfordit();
					}
				}
				s2=s, o2=o;
			}
		}
	}
}

bool Reversi::lephet() const
{
	for(int i=1;i<9;++i)
		for(int j=1;j<9;++j)
			if(lepesJo(i,j))	/* a tabla osszes mezojenel kiprobalja, hogy tudna-e lepni */
				return true;
	return false;
}

int Reversi::szamol() const
{
	int feher=0, fekete=0;
	for(int i=1;i<9;++i)
		for(int j=1;j<9;++j)	/* a tablan vegighaladva, osszeszamolja, melyik szinbol mennyi van */
		{
			if(tabla[i][j]!=NULL && tabla[i][j]->szin==1)
				++feher;
			if(tabla[i][j]!=NULL && tabla[i][j]->szin==2)
				++fekete;
		}
	if(feher>fekete)		/* ha feher nyert, akkor 1-el ter vissza */
		return 1;
	if(fekete>feher)		/* ha fekete nyert, akkor 2-vel ter vissza */
		return 2;
	if(feher==fekete)		/* ha dontetlen, akkor 0-val ter vissza */
		return 0;

	return -1;
}

bool Reversi::ment() const
{
	ofstream file ("savegame.dat", ios::out | ios::trunc);	/* irasra megnyit vagy letrehoz egy filet, mindig felulirja */
	if (file.is_open())		/* ha sikerult megnyitni */
	{
		for(int i=1;i<9;++i)
			for(int j=1;j<9;++j)
			{
				if(tabla[i][j]==NULL)		/* kimenti a mezoket sorban: 0, ha ures, 1, ha feher, 2, ha fekete */
					file << 0;
				if(tabla[i][j]!=NULL)
					file << tabla[i][j]->szin;
			}
		file << jatekos;			/* majd a vegere az aktualis jatekost */
	}
	else return false;

	file.close();	/* file bezarasa */
	return true;
}

bool Reversi::betolt()
{
	long begin,end;
	char x;
	int y;
	ifstream file ("savegame.dat");		/* file megnyitasa olvasasra */
	if (file.is_open())					/* ha sikerult megnyitni a filet */
	{
		begin = file.tellg();
		file.seekg (0, ios::end);
		end = file.tellg();
		if((end-begin)<65)			/* ha a file merete, kisebb, mint a 8x8-as tabla + 1 a jatekosnak, akkor hibas */
			 return false;

		file.seekg (0, ios::beg);	/* visszatekeres */
		for(int i=1;i<9;++i)
			for(int j=1;j<9;++j)
			{
				file >> x;		/* egy karakter beolvasasa */
				y=x-48;			/* atalakitas int-nek megfelelo szamnak */
				if(y==0)
					tabla[i][j]=NULL;			/* beiras a tablaba szinnek megfeleloen */
				else
					tabla[i][j]=new korong(y);
			}
		file >> x;
		y=x-48;
		jatekos=y;		/* a jatekos kiolvasasa */
	}
	else return false;

	file.close();	/* bezaras */

	return true;
}