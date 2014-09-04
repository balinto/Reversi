/* Keszitette:        */
/* Erdohegyi Balint   */
/*					  */
/* Program: Reversi   */

#ifndef REVERSI_H
#define REVERSI_H

class korong;

/* a jatekszabalyokat ismero, jatekot megvalosito osztaly  */
class Reversi
{
private:
	korong* tabla[10][10];		/* 10x10-es tabla, amibol 8x8 a valodi a kozepen, a korulotte levo mezok csak seged mezok*/
	int jatekos;				/* az eppen soron levo jatekos szama  */
public:
	Reversi();					/*  a konstruktor a tablat alaphelyzetbe allitja, a kezdo jatekos a feher lesz */
	~Reversi();					/*  a destruktor torli a tablat */
	void alaphelyzet();			/*  a tablat alaphelyzetbe allitja, a kezdo jatekos a feher */
	void torol();				/* torli az osszes korongot  */
	void rajzol(int uzenet=0) const;	/*  kirajzolja a tablat es a menut */
	void jatekosValtas();				/*  jatekost valt */
	bool lepesJo(int s, int o) const;	/* ellenorzi, hogy az adott lepes megfelelo-e, lehet-e oda lepni  */
	void lep(int s, int o);				/*  ellenorzi, hogy a jatekos tud-e egyaltalan lepni valamit */
	void fordit(int s, int o) const;	/*  atforditja a korongokat a lepesnek megfeleloen */
	bool lephet() const;		/*  ellenorzi, hogy a jatekos tud-e egyaltalan lepni valamit */
	int szamol() const;			/*  megszamolja, melyik szinbol van a tobb, 1: feher, 2: fekete, 3: ugynannyi */
	bool ment() const;			/*  elmenti az aktualis allast */
	bool betolt();				/*  betolti a kimentett allast */
};

/*  a korongok osztalya */
class korong
{
private:
	int szin;	/*  a korong tetejenek a szine, 1: feher, 2: fekete */
public:
	friend class Reversi;		/*  hogy hozzaferhessen a Reversi osztaly a korong tagvaltozojahoz */
	korong(int x){ szin=x; }	/*  korongot letrehozni a felforditott oldalanak szinevel lehet */
	void atfordit(){ szin = szin==1 ? 2 : 1; }	/*  megforditja a korongot */
};

#endif