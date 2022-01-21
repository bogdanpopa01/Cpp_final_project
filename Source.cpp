#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// cerinta 6 - exceptiile custom

class ExceptieStunSpider : public exception
{
public:
	const char* what() const throw()
	{
		return "Durata Stun Invalida!\n";
	}
};

class ExceptieHpSpider : public exception
{
public:
	const char* what() const throw()
	{
		return "Hp invalid!\n";
	}
};

// cerinta 1 - interfata

class InterfataMonster
{
public:
	virtual string experientaNecesara() = 0;
};

// cerinta 1 - clasa de baza

class Monster : public InterfataMonster
{
	// cerinta 2
	char* nume;
	double hp;
	float* dmgAbilitati;
	int nrAbilitati;

public:

	// cerinta 3 - constructor cu toti parametrii in clasa de baza
	Monster(const char* nume, double hp, int nrAbilitati, float* dmgAbilitati)
	{
		if (nume == nullptr)
			throw new exception("Nume invalid!\n");
		else
		{
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		if (hp <= 0)
			throw new exception("Hp invalid!\n");
		else
			this->hp = hp;

		if (nrAbilitati <= 0 && dmgAbilitati == nullptr)
			throw new exception("nrAbilitati invalid sau dmgAbilitati invalid!\n");
		else
		{
			this->nrAbilitati = nrAbilitati;
			this->dmgAbilitati = new float[nrAbilitati];
			for (int i = 0; i < nrAbilitati; i++)
				this->dmgAbilitati[i] = dmgAbilitati[i];
		}
	}

	// cerinta 3 - constructor default pentru clasa de baza
	Monster()
	{
		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
		this->hp = 2000.5;
		this->nrAbilitati = 2;
		this->dmgAbilitati = new float[nrAbilitati];
		for (int i = 0; i < nrAbilitati; i++)
			this->dmgAbilitati[i] = 1000 + i;
	}

	//  cerinta 3 - constructorul fara char* pentru clasa de baza
	Monster(double hp, int nrAbilitati, float* dmgAbilitati)
	{
		this->nume = new char[strlen("AnonimNou") + 1];
		strcpy_s(this->nume, strlen("AnonimNou") + 1, "AnonimNou");
		if (hp <= 0)
			throw new exception("Hp invalid!\n");
		else
			this->hp = hp;

		if (nrAbilitati <= 0 && dmgAbilitati == nullptr)
			throw new exception("nrAbilitati invalid sau dmgAbilitati invalid!\n");
		else
		{
			this->nrAbilitati = nrAbilitati;
			this->dmgAbilitati = new float[nrAbilitati];
			for (int i = 0; i < nrAbilitati; i++)
				this->dmgAbilitati[i] = dmgAbilitati[i];
		}
	}

	// cerinta 3 - destructor
	~Monster()
	{
		if (this->nume != nullptr)
			delete[] this->nume;
		if (this->dmgAbilitati != nullptr)
			delete[] this->dmgAbilitati;
	}

	// cerinta 3 - constructorul de copiere
	Monster(const Monster& src)
	{
		this->nume = new char[strlen(src.nume) + 1];
		strcpy_s(this->nume, strlen(src.nume) + 1, src.nume);
		this->hp = src.hp;
		this->nrAbilitati = src.nrAbilitati;
		this->dmgAbilitati = new float[this->nrAbilitati];
		for (int i = 0; i < this->nrAbilitati; i++)
			this->dmgAbilitati[i] = src.dmgAbilitati[i];
	}

	// cerinta 3 - operatorul egal
	Monster& operator=(const Monster& src)
	{
		if (this != &src)
		{
			if (this->nume != nullptr)
				delete[] this->nume;
			this->nume = new char[strlen(src.nume) + 1];
			strcpy_s(this->nume, strlen(src.nume) + 1, src.nume);
			this->hp = src.hp;
			this->nrAbilitati = src.nrAbilitati;
			if (this->dmgAbilitati != nullptr)
				delete[] this->dmgAbilitati;
			this->dmgAbilitati = new float[this->nrAbilitati];
			for (int i = 0; i < this->nrAbilitati; i++)
				this->dmgAbilitati[i] = src.dmgAbilitati[i];
		}
		else
			throw new exception("Eroare la asignare!\n");
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Monster& m)
	{
		out << "Monster: " << m.nume << " | Hp: " << m.hp << " | Dmg. abilitati: ";
		for (int i = 0; i < m.nrAbilitati; i++)
			out << m.dmgAbilitati[i] << "  ";
		out << '\n';
		return out;
	}

	string experientaNecesara()
	{
		return "Monster-ul dropeaza 300 exp.\n";
	}

	friend istream& operator>>(istream& in, Monster& src)
	{
		char aux[100];
		cout << "Nume: ";
		in >> aux;
		if (src.nume != nullptr)
			delete[] src.nume;
		src.nume = new char[strlen(aux) + 1];
		strcpy_s(src.nume, strlen(aux) + 1, aux);
		cout << "Hp: ";
		in >> src.hp;
		cout << "Numar abilitati: ";
		in >> src.nrAbilitati;
		if (src.dmgAbilitati != nullptr)
			delete[] src.dmgAbilitati;
		src.dmgAbilitati = new float[src.nrAbilitati];
		for (int i = 0; i < src.nrAbilitati; i++)
		{
			cout << "Abilitatea " << i + 1 << " = ";
			in >> src.dmgAbilitati[i];
		}
		return in;
	}

	bool operator==(const Monster& src)
	{
		if (this == &src)
			return true;

		bool normalFields = strcmp(this->nume, src.nume) == 0 &&
			this->nrAbilitati == src.nrAbilitati &&
			this->hp == src.hp;

		if (normalFields == true)
		{
			for (int i = 0; i < nrAbilitati; i++)
				if (this->dmgAbilitati[i] != src.dmgAbilitati[i])
					return false;
			return true;
		}
		else
			return false;
	}

	bool operator<=(const Monster& src)
	{
		if (this == &src)
			return true;

		bool normalFields = strcmp(this->nume, src.nume) <= 0 &&
			this->nrAbilitati <= src.nrAbilitati &&
			this->hp <= src.hp;

		if (normalFields == true)
		{
			for (int i = 0; i < src.nrAbilitati; i++)
				if (this->dmgAbilitati > src.dmgAbilitati)
					return false;
			return true;
		}
		else
			return false;
	}

	float operator[](int index)
	{
		return dmgAbilitati[index];
	}

	void setMonsterHp(double hp)
	{
		this->hp = hp;
	}

	const char* getNumeMonster()
	{
		char* aux = new char[strlen(this->nume) + 1];
		strcpy_s(aux, strlen(this->nume) + 1, this->nume);
		return aux;
	}

	double getHpMonster()
	{
		return this->hp;
	}

	int getNrAbilitatiMonster()
	{
		return this->nrAbilitati;
	}

	float getDmgAbilitatiMonster(int index)
	{
		float* aux = new float[this->nrAbilitati];
		for (int i = 0; i < this->nrAbilitati; i++)
			aux[i] = this->dmgAbilitati[i];
		return aux[index];
	}

	void setMonsterName(const char* nume)
	{
		this->nume = new char[strlen(nume) + 1];
		strcpy_s(this->nume, strlen(nume) + 1, nume);
	}

	// cerinta 7 - functie necesara pentru a scrie in fisier
	void scriereFisierBinar(ofstream& fisBinarOut)
	{
		int dim = strlen(nume) + 1;
		fisBinarOut.write((char*)&dim, sizeof(dim));
		fisBinarOut.write(this->nume, dim);

		fisBinarOut.write((char*)&this->hp, sizeof(this->hp));
		fisBinarOut.write((char*)&this->nrAbilitati, sizeof(this->nrAbilitati));

		for (int i = 0; i < this->nrAbilitati; i++)
			fisBinarOut.write((char*)(&this->dmgAbilitati[i]), sizeof(this->dmgAbilitati[i]));
	}

	// cerinta 7 - functie necesara pentru a citi din fisier
	void citireFisierBinar(ifstream& fisBinarIn)
	{
		int dim = 0;
		char aux[100];
		fisBinarIn.read((char*)&dim, sizeof(dim));

		fisBinarIn.read(aux, dim);
		if (nume != nullptr)
			delete[] nume;

		this->nume = new char[dim];
		strcpy_s(this->nume, dim, aux);

		fisBinarIn.read((char*)&this->hp, sizeof(this->hp));
		fisBinarIn.read((char*)&this->nrAbilitati, sizeof(this->nrAbilitati));

		this->dmgAbilitati = new float[this->nrAbilitati];
		for (int i = 0; i < this->nrAbilitati; i++)
			fisBinarIn.read((char*)(&this->dmgAbilitati[i]), sizeof(this->dmgAbilitati[i]));
		
	}

};

// cerinta 1 - primul copil

class giantSpider : public Monster, public InterfataMonster
{
	int durataStun;
public:

	// constructorul default pentru primul copil
	giantSpider() : Monster()
	{
		this->durataStun = 3;
	}

	// constructorul cu toti parametrii pentru primul copil
	giantSpider(const char* nume, double hp, int nrAbilitati, float* dmgAbilitati, int durataStun)
		:Monster(nume, hp, nrAbilitati, dmgAbilitati)
	{
		if (durataStun <= 0)
			throw new exception("Numar introdus invalid!\n");
		else
			this->durataStun = durataStun;
	}

	string experientaNecesara()
	{
		return "GiantSpider-ul dropeaza 500 exp.\n";
	}

	// cerinta 4 - supraincarcarea tuturor operatorilor cunoscuti
	giantSpider& operator=(const giantSpider& src)
	{
		if (this != &src)
		{
			Monster::operator=(src);
			this->durataStun = src.durataStun;
		}
		else
			throw new exception("Eroare la asignare!\n");
		return *this;
	}

	friend ostream& operator<<(ostream& out, const giantSpider& src)
	{
		out << (Monster&)src;
		out << "\tDurata stun: " << src.durataStun << " secunde.\n";
		return out;
	}

	friend istream& operator>>(istream& in, giantSpider& src)
	{
		in >> (Monster&)src;
		cout << "Durata stun: ";
		in >> src.durataStun;
		return in;
	}

	// operatorul ++ de pre-incrementare
	giantSpider& operator++()
	{
		durataStun++;
		return *this;
	}

	// operatorul ++ de post-incrementare
	giantSpider operator++(int)
	{
		giantSpider aux(*this);
		durataStun++;
		return aux;
	}

	// operatorul + intre un obiect si un int
	int operator+(int x)
	{
		return durataStun + x;
	}

	// operatorul + intre un int si un obiect
	friend int operator+(int x, giantSpider& src);

	// operatorul +=
	void operator+=(int x)
	{
		durataStun += x;
	}

	// operatorul !
	bool operator!()
	{
		/* return !ceva; */
	}

	// operatorul ==
	bool operator==(const giantSpider& src)
	{
		if (this == &src)
			return true;
		return this->durataStun == src.durataStun &&
			Monster::operator==(src);
	}

	// operatorul <=
	bool operator<=(const giantSpider& src)
	{
		if (this == &src)
			return true;
		return this->durataStun <= src.durataStun &&
			Monster::operator<=(src);
	}

	// operatorul functie
	void operator()(int val)
	{
		this->durataStun += val;
	}

	// operatorul index
	float operator[](int index)
	{
		return Monster::operator[](index);
	}

	// operatorul cast
	operator float()
	{
		return durataStun;
	}

	// cerinta 6 - settarii folositi pentru a da trigger la exceptiile custom
	void setDurataStunSpider(int durata)
	{
		if (durata <= 0)
			throw ExceptieStunSpider();
		else
			this->durataStun = durata;
	}

	void setHpSpider(double spiderHp)
	{
		if (spiderHp <= 0)
			throw ExceptieHpSpider();
		else
			Monster::setMonsterHp(spiderHp);
	}

};

int operator+(int x, giantSpider& src)
{
	return x + src.durataStun;
}

// cerinta 1 - al doilea copil

class Zombie : public Monster, public InterfataMonster
{
	int nrInfectariCauzate;
public:

	Zombie() :Monster()
	{
		this->nrInfectariCauzate = 50;
	}

	Zombie(const char* nume, double hp, int nrAbilitati, float* dmgAbilitati, int nrInfectariCauzate)
		:Monster(nume, hp, nrAbilitati, dmgAbilitati)
	{
		if (nrInfectariCauzate <= 0)
			throw new exception("Numar introdus invalid!\n");
		else
			this->nrInfectariCauzate = nrInfectariCauzate;
	}

	string experientaNecesara()
	{
		return "Zombie-ul dropeaza 700 exp.\n";
	}

	friend ostream& operator<<(ostream& out, const Zombie& src)
	{
		out << (Monster&)src;
		out << "\tNumar infectari: " << src.nrInfectariCauzate << '\n';
		return out;
	}

};


// cerinta 1 - al treilea copil, clasa abstracta
class Skeleton : public Monster, public InterfataMonster
{
	int nrOase = 1;
public:

	Skeleton() :Monster()
	{
		this->nrOase = 66;
	}

	Skeleton(const char* nume, double hp, int nrAbilitati, float* dmgAbilitati, int nrOase)
		:Monster(nume, hp, nrAbilitati, dmgAbilitati)
	{
		if (nrOase <= 0)
			throw exception("Numar oase invalid!\n");
		else
			this->nrOase = nrOase;
	}

	string experientaNecesara()
	{
		return "Skeleton-ul dropeaza 1600 exp.\n";
	}

	friend ostream& operator<<(ostream& out, const Skeleton& src)
	{
		out << (Monster&)src;
		out << "\tNumar oase: " << src.nrOase << '\n';
		return out;
	}

	// functia virtuala pura pentru clasa abstracta
	virtual string nrItemeRare() = 0;
};

// cerinta 1 - primul nepot
class FireSkeleton :public Skeleton, public InterfataMonster
{
	int nrSageti = 100;
public:

	FireSkeleton() :Skeleton()
	{
		this->nrSageti = 888;
	}

	FireSkeleton(const char* nume, double hp, int nrAbilitati, float* dmgAbilitati, int nrOase, int nrSageti)
		:Skeleton(nume, hp, nrAbilitati, dmgAbilitati, nrOase)
	{
		if (nrSageti <= 0)
			throw exception("Numar de sageti invalid!\n");
		else
			this->nrSageti = nrSageti;
	}

	string experientaNecesara()
	{
		return "FireSkeleton-ul dropeaza 8000 exp.\n";
	}

	friend ostream& operator<<(ostream& out, const FireSkeleton& src)
	{
		out << (Skeleton&)src;
		out << "\tNumar sageti: " << src.nrSageti << '\n';
		return out;
	}

	// implementarea functiei impusa de clasa abstracta
	string nrItemeRare()
	{
		return "FireSkeleton-ul dropeaza 2 iteme rare.\n";
	}

};

// cerinta 1 - al doile nepot

class WaterSkeleton : public Skeleton, public InterfataMonster
{
	int nrSabii = 2;
public:

	WaterSkeleton() :Skeleton()
	{
		this->nrSabii = 4;
	}

	WaterSkeleton(const char* nume, double hp, int nrAbilitati, float* dmgAbilitati, int nrOase, int nrSabii)
		:Skeleton(nume, hp, nrAbilitati, dmgAbilitati, nrOase)
	{
		if (nrSabii <= 0)
			throw exception("Numar sabii invalid!\n");
		else
			this->nrSabii = nrSabii;
	}

	string experientaNecesara()
	{
		return "WaterSkeleton-ul dropeaza 18000 exp.\n";
	}

	friend ostream& operator<<(ostream& out, const WaterSkeleton& src)
	{
		out << (Skeleton&)src;
		out << "\tNumar sabii: " << src.nrSabii << '\n';
		return out;
	}

	// implementarea functiei impusa de clasa abstracta
	string nrItemeRare()
	{
		return "WaterSkeleton-ul dropeaza 3 iteme rare.\n";
	}
};

// cerinta 5 - compunere
class CompunereDeMonsters
{
	string denumire;
	int nrMonsters;
	Monster* monsters;

public:

	CompunereDeMonsters()
	{
		this->denumire = "Denumire SRL";
		this->nrMonsters = 0;
		this->monsters = nullptr;
	}

	CompunereDeMonsters(string denumire, int nrMonsters, Monster* monsters)
	{
		this->denumire = denumire;
		this->nrMonsters = nrMonsters;
		this->monsters = new Monster[nrMonsters];
		for (int i = 0; i < nrMonsters; i++)
			this->monsters[i] = monsters[i];
	}

	CompunereDeMonsters(const CompunereDeMonsters& src)
	{
		this->denumire = src.denumire;
		this->nrMonsters = src.nrMonsters;
		this->monsters = new Monster[src.nrMonsters];
		for (int i = 0; i < src.nrMonsters; i++)
			this->monsters[i] = src.monsters[i];
	}

	CompunereDeMonsters& operator=(const CompunereDeMonsters& src)
	{
		if (this != &src)
		{
			this->denumire = src.denumire;
			this->nrMonsters = src.nrMonsters;
			if (this->monsters != nullptr)
				delete[] this->monsters;
			this->monsters = new Monster[src.nrMonsters];
			for (int i = 0; i < src.nrMonsters; i++)
				this->monsters[i] = src.monsters[i];
		}
		else
			throw new exception("Eroare la asignare!\n");
		return *this;
	}

	~CompunereDeMonsters()
	{
		if (this->monsters != nullptr)
			delete[] this->monsters;
	}

	void adaugaMonster(Monster m)
	{
		Monster* aux = new Monster[nrMonsters + 1];
		for (int i = 0; i < nrMonsters; i++)
			aux[i] = monsters[i];
		aux[nrMonsters++] = m;
		delete[] this->monsters;
		monsters = aux;
	}

	void stergereMonster(Monster m)
	{
		int ct = 0;
		for (int i = 0; i < nrMonsters; i++)
			if (monsters[i] == m)
				ct++;
		if (ct > 0)
		{
			for (int i = 0; i < nrMonsters; i++)
				if (monsters[i] == m)
				{
					for (int j = i; j < nrMonsters - 1; j++)
						monsters[j] = monsters[j + 1];
					nrMonsters--;
				}
			Monster* aux = new Monster[nrMonsters];
			for (int i = 0; i < nrMonsters; i++)
				aux[i] = monsters[i];
			delete[] this->monsters;
			monsters = aux;
		}
	}

	friend ostream& operator<<(ostream& out, const CompunereDeMonsters& src)
	{
		out << "Denumire: " << src.denumire << '\n';
		out << "Numar de monstrii: " << src.nrMonsters << '\n';
		for (int i = 0; i < src.nrMonsters; i++)
			out << src.monsters[i] << '\n';
		out << '\n';
		return out;
	}

	// cerinta 7

	friend ofstream& operator<<(ofstream& op, const CompunereDeMonsters& c)
	{
		int dim = c.denumire.size() + 1;
		op.write((char*)&dim, sizeof(dim));
		op.write(c.denumire.c_str(), dim);
		op.write((char*)&c.nrMonsters, sizeof(c.nrMonsters));
		for (int i = 0; i < c.nrMonsters; i++)
			c.monsters[i].scriereFisierBinar(op);
		return op;
	}

	friend ifstream& operator>>(ifstream& opp, CompunereDeMonsters& c)
	{
		int dim = 0;
		opp.read((char*)&dim, sizeof(dim));
		char aux[100];
		opp.read(aux, dim);
		c.denumire = aux;
		opp.read((char*)&c.nrMonsters, sizeof(c.nrMonsters));
		c.monsters = new Monster[c.nrMonsters];
		for (int i = 0; i < c.nrMonsters; i++)
		{
			Monster a;
			a.citireFisierBinar(opp);
			c.monsters[i] = a;
		}
		return opp;
	}

};

// cerinta 8
class CompunereDeMonstersSTL
{
	string denumire;
	int nrMonsters;
	vector<Monster> monsters;

public:

	CompunereDeMonstersSTL(){}

	CompunereDeMonstersSTL(string denumire,int nrMonsters,vector<Monster> monsters)
	{

		if (denumire.empty())
			throw exception("Denumire invalida!\n");
		else
			this->denumire = denumire;

		if (nrMonsters <= 0)
			throw exception("Numar invalid!\n");
		else
			this->nrMonsters = nrMonsters;

		for (int i = 0; i < nrMonsters; i++)
			this->monsters.push_back(monsters[i]);
	}	

	CompunereDeMonstersSTL(const CompunereDeMonstersSTL& src)
	{
		this->denumire = src.denumire;
		this->nrMonsters = src.nrMonsters;
		for(int i=0;i<src.nrMonsters;i++)
			this->monsters.push_back(src.monsters.at(i));
	}

	CompunereDeMonstersSTL& operator=(const CompunereDeMonstersSTL& src)
	{
		if (this != &src)
		{
			this->denumire = src.denumire;
			this->nrMonsters = src.nrMonsters;
			for (int i = 0; i < src.nrMonsters; i++)
				this->monsters.push_back(src.monsters.at(i));
		}
		else
			throw exception("Eroare la asignare!\n");
		return *this;
	}

	~CompunereDeMonstersSTL() {}

	friend ostream& operator<<(ostream& out, const CompunereDeMonstersSTL& src)
	{
		out << "Denumire: " << src.denumire << '\n';
		out << "Numar de monstrii: " << src.nrMonsters << '\n';
		for (int i = 0; i < src.nrMonsters; i++)
			out << src.monsters[i] << '\n';
		out << '\n';

		return out;
	}

	void adaugaMonster(Monster m)
	{
		this->nrMonsters += 1;
		this->monsters.push_back(m);
	}

	void stergereMonster(Monster m)
	{
		int ct , j =0;
		do {
			ct = 0;
			for (int i = 0; i < nrMonsters; i++)
				if (monsters[i] == m)
				{
					ct++;
					j = i;
				}
			if (ct > 0)
			{
				this->monsters.erase(monsters.begin() + j);
				this->nrMonsters -= 1;
			}
		} while (ct>0);
	}

	friend ofstream& operator<<(ofstream& op, CompunereDeMonstersSTL& c)
	{
		int dim = c.denumire.size() + 1;
		op.write((char*)&dim, sizeof(dim));
		op.write(c.denumire.c_str(), dim);
		op.write((char*)&c.nrMonsters, sizeof(c.nrMonsters));
		for (int i = 0; i < c.nrMonsters; i++)
			c.monsters[i].scriereFisierBinar(op);
		return op;
	}

	friend ifstream& operator>>(ifstream& opp, CompunereDeMonstersSTL& c)
	{
		int dim = 0;
		opp.read((char*)&dim, sizeof(dim));
		char aux[100];
		opp.read(aux, dim);
		c.denumire = aux;
		opp.read((char*)&c.nrMonsters, sizeof(c.nrMonsters));
		for (int i = 0; i < c.nrMonsters; i++)
		{
			Monster a;
			a.citireFisierBinar(opp);
			c.monsters[i] = a;
		}
		return opp;
	}
	
};



int main()
{
	// cerinta 3
	cout << "Cerinta 3:\n\n";
	float vector_pt_monster[] = { 44,444.44 };
	Monster m1, m2("Monsterutul", 2500,2, vector_pt_monster),m3=m2,m4;
	m4 = m3;
	Monster m5(2500, 2, vector_pt_monster);
	cout << m1 << m2 << m3 << m4 << m5;

	cout << "\n\n";

	float v1[] = { 125,234.22,8643.3 };
	giantSpider g1, g2("Ana", 1000, 3, v1, 3), g3(g2), g4;
	g4 = g3;
	cout << g1 << g2 << g3 << g4;

	cout << "\n\n";

	float v2[] = { 9999.1 };
	Zombie z1, z2("Marcel", 1500, 1, v2, 90), z3(z2), z4;
	z4 = z3;
	cout << z1 << z2 << z3 << z4;

	// cerinta 4
	cout << "\nCerinta 4:\n\n";
	cout << "Operatorii = si << au fost demonstrati la cerinta anterioara.\n\n";
	cout << "Operatorul >>: \n";
	giantSpider test1;
	cin >> test1;
	cout << "\n";
	cout << test1;

	cout << "\nOperatorii de pre si post incrementare: \n\n";
	cout << test1++ << ++test1;

	cout << "\nOperatorii + intre un obiect si un int SI intre un int si un obiect: \n\n";
	cout << test1 + 900 <<"\n" << 1000 + test1<<"\n";

	cout << "\nOperatorul +=: \n\n";
	test1 += 10000;
	cout << test1;

	cout << "\nOperatorii <= si == : \n\n";

	float e1[] = { 1,2 };
	giantSpider egal1("AAA", 200, 2, e1, 2);
	float e2[] = { 1,2 };
	giantSpider egal2("AAA", 200, 2, e2, 2);

	float e3[] = { 1,2,3 };
	giantSpider nu_egal("BBB", 200, 3, e3, 2);

	cout << egal1 << egal2 << '\n';
	cout << "Sunt egali?\n";

	if (egal1 == egal2)
		cout << "da" << '\n'; // raspunsul corect
	else
		cout << "nu" << '\n';

	cout << "\n\n";

	cout << nu_egal << egal1;
	cout << "\nEste primul obect prezentat mai mic decat al 2-lea obiect prezentat?\n";
	if (nu_egal <= egal1)
		cout << "da" << '\n';
	else
		cout << "nu" << '\n'; // raspunsul corect

	cout << "\nOperatorii functie () si index[] : \n";
	cout << "Operatorul functie adauga 6900 secunde la durataStun pentru ultimul obiect afisat pe ecran.\n";
	cout << "Operatorul index afiseaza dmg-ul primei abilitati( index[1] ) al ultimului obiect afisat pe ecran.\n\n";
	egal1(6900);
	cout << egal1;
	cout << "dmg: " << egal1[1];

	cout << "\n\nOperatorul cast: \n";
	float durataStun = egal1; // op cast implicit
	cout << "Durata stun: " << durataStun << ' ' << (float)egal1 << '\n'; // op cast explicit

	// cerinta 5
	cout << "\n\nCerinta 5:\n\n";

	float cv1[] = { 23 };
	Monster c1("Unu", 100, 1, cv1);
	float cv2[] = { 24,55 };
	float cv3[] = { 432.3112,55 };
	Monster c2("Doi", 200, 2, cv2);
	Monster c3("Trei", 300, 2, cv3);

	cout << "Pana in adaugare: \n\n";
	CompunereDeMonsters compunere("NumeMonstersSRL", 2, new Monster[]{ c1,c2 });
	cout << compunere;

	compunere.adaugaMonster(c3);
	cout << "Dupa adaugare:\n\n";
	cout << compunere;

	compunere.stergereMonster(c2);
	cout << "Dupa stergere:\n\n";
	cout << compunere;

	// cerinta 6
	cout << "Cerinta 6:\n";
	cout << "Exceptii:\n\n";

	try
	{
		egal1.setDurataStunSpider(-2);
	}
	catch (ExceptieStunSpider e)
	{
		cout << e.what();
	}

	try
	{
		egal1.setHpSpider(0);
	}
	catch (ExceptieHpSpider e)
	{
		cout << e.what();
	}

	// cerinta 7
	cout << "\n\nCerinta 7:\n";

	ofstream fisBinarOut("test.bin", ios::out | ios::binary | ios::app);
	if (fisBinarOut.is_open())
	{
		fisBinarOut << compunere;
		fisBinarOut.close();
	}
	else
		cout << "Fisierul nu poate fi deschis pentru scriere!\n";

	ifstream fisBinarIn("test.bin", ios::in | ios::binary);
	if (fisBinarIn.is_open())
	{
		fisBinarIn >> compunere;
		cout << compunere;
		fisBinarIn.close();
	}
	else
		cout << "Fisierul nu poate fi deschis pentru citire!\n";

	// cerinta 8
	cout << "\nCerinta 8:\n\n";

	float mv1v[] = { 5,6,7 };
	Monster mv1("Unul", 9595,3, mv1v);
	float mv2v[] = { 51,66,72 };
	Monster mv2("Doiul", 19595, 3, mv2v);

	vector<Monster> vector_stl;
	vector_stl.push_back(mv1);
	vector_stl.push_back(mv2);

	CompunereDeMonstersSTL compunere_stl("Compunere De Monstrii STL", 2, vector_stl);
	cout << "Pana in adaugare: \n\n";
	cout << compunere_stl<<'\n';

	float mv3v[] = { 511,66,72 };
	Monster mv3("Trei", 19595, 3, mv3v);

	compunere_stl.adaugaMonster(mv1);
	cout << "Dupa adaugare1:\n\n";
	cout << compunere_stl << '\n';

	compunere_stl.adaugaMonster(mv3);
	cout << "Dupa adaugare2:\n\n";
	cout << compunere_stl << '\n';

	compunere_stl.stergereMonster(mv1);
	cout << "Dupa stergere:\n\n";
	cout << compunere_stl << '\n';

	cout << "Test pentru citirea si scrierea din fisier binar pentru clasa cu STL:\n\n";

	ofstream fisBinarOut2("nou.bin", ios::out | ios::binary | ios::app);
	if (fisBinarOut2.is_open())
	{
		fisBinarOut2 << compunere_stl;
		fisBinarOut2.close();
	}
	else
		cout << "Fisierul nu poate fi deschis pentru scriere!\n";

	ifstream fisBinarIn2("nou.bin", ios::in | ios::binary);
	if (fisBinarIn2.is_open())
	{
		fisBinarIn2 >> compunere_stl;
		cout << compunere_stl;
		fisBinarIn2.close();
	}
	else
		cout << "Fisierul nu poate fi deschis pentru citire!\n";

	// cerinta 9 - early si late binding
	cout << "\nCerinta 9:\n\n";

	cout << "Early-binding:\n\n";

	float mp1v[] = { 534,433,33 };
	Monster mp1("Unu", 3000, 2, mp1v);
	cout << mp1;
	cout << mp1.experientaNecesara() << '\n';

	float mp2v[] = { 4324 };
	giantSpider mp2("Doi", 5324, 1, mp2v, 2);
	cout << mp2;
	cout << mp2.experientaNecesara() << '\n';

	float mp3v[] = { 432 };
	Zombie mp3("Trei", 5433, 1, mp3v, 534);
	cout << mp3;
	cout << mp3.experientaNecesara() << '\n';

	float mp4v[] = { 422 };
	FireSkeleton mp4("Patru", 5555, 1, mp4v, 32, 55);
	cout << mp4;
	cout << mp4.experientaNecesara()<<'\n';

	float mp5v[] = { 2 };
	WaterSkeleton mp5("Cinci", 321, 1, mp5v, 35, 16);
	cout << mp5;
	cout << mp5.experientaNecesara();

	cout << "\nLate-binding:\n\n";

	Monster* poli = &mp1;
	cout << *poli;
	cout << poli->experientaNecesara() << '\n';

	poli = &mp2;
	cout << *poli;
	cout << poli->experientaNecesara() << '\n';

	poli = &mp3;
	cout << *poli;
	cout << poli->experientaNecesara() << '\n';

	poli = &mp4;
	cout << *poli;
	cout << poli->experientaNecesara() << '\n';

	poli = &mp5;
	cout << *poli;
	cout << poli->experientaNecesara() << '\n';

	// cerinta 10
	cout << "\nCerinta 10:\n\n";

	float mogu1[] = { 1,2,3 };
	FireSkeleton c10("Mogu", 4500, 3, mogu1, 22, 90);


	float mogu2[] = { 718,22,43 };
	WaterSkeleton c11("Mogusan", 14500, 3, mogu2, 322, 190);

	float mogu3[] = { 1718,122,143 };
	FireSkeleton skeletonAjutator("Basic", 1567, 2, mogu3, 114, 144);

	Skeleton* sp = &skeletonAjutator;

	Skeleton** vectorSkeletoni = new Skeleton * [3]{ &c10,&c11,&skeletonAjutator };
	for (int i = 0; i < 3; i++)
	{
		cout << vectorSkeletoni[i]->nrItemeRare();
		cout << vectorSkeletoni[i]->experientaNecesara();
	}

}