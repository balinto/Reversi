/* Keszitette:        */
/* Erdohegyi Balint   */
/*					  */
/* Program: Reversi   */

#include <iostream>
#include <conio.h>
#include <exception>
#include <stdexcept>
#include "Reversi.h"

using namespace std;

int main()
{
	try		/* try blokk kezdete a kivetelek elkapasahoz */
	{
	cout << endl;
	cout << " XXX  XXXX X   X XXXX XXX   XXX X " << endl;
	cout << " X  X X    X   X X    X  X X    X " << endl;
	cout << " XXX  XXXX  X X  XXXX XXX   XX  X " << endl;
	cout << " X  X X     X X  X    X  X    X X " << endl;
	cout << " X  X XXXX   X   XXXX X  X XXX  X " << endl << endl;

	cout << "           1 - Uj jatek            " << endl;
	cout << "           2 - Betoltes            " << endl;
	cout << "           X - Kilepes             " << endl << endl << " ";

	char valasz=0, sor=0, oszlop=0;
	int vege=0, joLepes, menuparancs;

	Reversi jatek;		/* a jatek objektum letrehozasa */

	valasz=_getch();	/* menu valasztasra a valasz beolvasasa */
	if(valasz=='x' || valasz=='X')		/* ha X, lepjen ki */
		return 0;
	if(valasz=='2')		/* ha 2, akkor toltse be az elmentett allast */
		if(!jatek.betolt())
		{
			cout << endl;								/* ha nem sikerult, akkor hibauzenet */
			cout << " Hiba a betolteskor!" << endl;
			cout << " Nem letezik vagy hibas elmentett allas!" << endl;
			_getch();
		}

	jatek.rajzol();		/* jatek tabla es a menu kirajzolasa */
	
	while(1)			/* a fo ciklus, ami addig megy, amig ki nem lepnek */
	{
	do					/* ez a ciklus addig megy, amig nincs vege a jateknak (vagy ki nem lepnek) */
	{
		if(jatek.lephet())	/* hogy, ha a soron levo jatekos tud lepni */
		{
			do				/* akkor amig nem lep egy jot, megy a ciklus */
			{
				joLepes=1;				/* alapbol jo */
				menuparancs=0;			/* alapbol sima lepes */
				fflush(stdin);
				oszlop=getchar();		/* az elso karakter az oszlop szama */
				if(oszlop!='\n')		/* ha nem csupan entert ut a jatekos */
					sor=getchar();		/* akkor a masodik karater lesz a sor szama */
				else menuparancs=1;		/* ez azert van, hogy a vegen ne irja ki, hogy rossz lepes */
				if(oszlop=='x' || oszlop=='X')	/* x-et olvas be elso karaterkent, lepjen ki */
				{
					cout << endl << "                                    "<<endl;
					return 0;
				}
				if(oszlop=='1')				/* uj jatek */
				{
					jatek.torol();			/* eloszor torlni a korongokat */
					jatek.alaphelyzet();	/* utana alaphelyzetbe allitja */
					cout << endl << "                                    "<<endl;
					menuparancs=1;			/* ez azert van, hogy a vegen ne irja ki, hogy rossz lepes */
				}
				if(oszlop=='2')	/* betoltes */
				{
					if(!jatek.betolt())		/* ha nem sikerult, hiba */
					{
						cout << endl;
						cout << " Hiba a betolteskor!                    " << endl;
						cout << " Nem letezik vagy hibas elmentett allas!" << endl;
					}
					else cout << endl << " Mentett allas betoltve!            " << endl;	/* ha sikerult, uzenet */
					menuparancs=1;
				}
				if(oszlop=='3')				/* mentes */
				{
					if(jatek.ment())
					{
						cout << endl << " Jatek allasa sikeresen elmentve!   " << endl;
					}
					else
					{
						cout << endl << " Nem sikerult elmenteni!            " << endl;
					}
					menuparancs=1;
				}

				if((oszlop-=96) < 0)	/* a betuvel megadott oszlop azonosito atalakitasa szamma */
					oszlop+=32;			/* nagy es kis betu eseten is jo legyen */
				sor-=48;				/* mivel karaterkent olvasta be, ezt is at kell alakitani */
				cout << endl;
				if(!jatek.lepesJo(sor,oszlop))		/* ha nem jo a lepes */
				{
					joLepes=0;				/* hogy bent maradjon a ciklusban */
					if(!menuparancs)		/* ha nem csak menu parancs volt, es emiatt nem jo a lepes */
					{
						cout<<" Oda nem tehetsz!                   "<<endl;		/* uzenet */
						jatek.rajzol(1);		/* tabla ujrarajzolasa, ugy, hogy az uzenet megmarad */
					}
					else if(menuparancs)		/* ha menu paranc volt */
							jatek.rajzol(1);	/* akkor is ujrarajzolas, uzenet meghagyasaval */
					else jatek.rajzol();		/* egyebkent meg ujrarajzolaskor toroljon minden egyebet */
				}
			}
			while(!joLepes);

			jatek.lep(sor,oszlop);		/* ha jo volt a lepes, akkor tegye le a korongot es forgasson */
			jatek.jatekosValtas();		/* kovetkezo jatekos jon */
			jatek.rajzol();				/* rajzolja ki ujra a a modositott tablat */
		}
		else		/* ha nem tudott lepni sehova se a jatekos */
		{
			jatek.jatekosValtas();		/* masik jatekos jon */
			if(!jatek.lephet())			/* ha o sem tud lepni */
				vege=1;					/* akkor vege a jateknak */
			else
			{
				cout<<" Nem tudsz lepni, masik jatekos jon!"<<endl;		/* egyebkent meg irja ki a helyzetet */
				cout<<" Nyomj ENTERT!"<<endl;
				_getch();
				jatek.rajzol();		/* es rajzolja ujra, ha elolvasta, es megnyomott egy billentyut */
			}
		}	
	}
	while(!vege);
 
	cout << "            Vege!" << endl;			/* ha vege van, ija ki a vegeredmenyt */
	if(jatek.szamol()==1)
		cout << "        A Feher nyert!" << endl;
	if(jatek.szamol()==2)
		cout << "        A Fekete nyert!" << endl;
	if(jatek.szamol()==0)
		cout << "          Dontetlen!" << endl;
	cout << endl;
	cout << "    Akarsz ujat jatszani?  I / N" << endl;		/* kerdes, hogy ujra akar e jatszani */
	valasz=_getch();
	if(valasz=='n' || valasz=='N' || valasz=='x' || valasz=='X' )	/* ha nem, akko kilep */
		return 0;
	vege=0;
	jatek.torol();			/* ha igen, akkor torolje a tablat, es tegye alaphelyzetbe, es rajzoljon */
	jatek.alaphelyzet();
	jatek.rajzol();
	}

	}
	catch(range_error& err)				/* indexelesi hibak elkapasa */
	{
		cerr << err.what() << endl;;
	}
	catch(bad_alloc& err)				/* memoria foglalasi hobak elkapasa */
	{
		cerr << err.what() << endl;;
	}
	catch(char* err)					/* egyeb sajat szoveges kivetelek elkapasa */
	{
		cerr << err << endl;
	}
	catch(...)							/* minden egyebnek */
	{
		cerr << " Ismeretlen hiba!" << endl;
	}

	return 0;
}