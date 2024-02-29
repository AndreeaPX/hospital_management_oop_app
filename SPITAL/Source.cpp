#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <string>

using namespace std;

enum GEN { MASCULIN = 1, FEMININ = 2, NEUTRU = 0 };

//6 EXCEPTII CUSTOM
class ExceptieCustomAngajat :public exception
{
public:
	const char* what3() const throw()
	{
		return " Valoarea salariului trebuie sa fie >0 si <=999999";
	}

	const char* what1() const throw()
	{
		return " valoarea data vechimii trebuie sa fie >=0 si <67 ";
	}

	const char* what2() const throw()
	{
		return " valoarea prenumelui trebuie sa nu fie goala";
	}
};

//1 CLASA PARINTE
class Angajat
{
private:  //1 a) membrii sunt in zona private
	const int cod = 0;
	char* nume;  //2 membru char*
	string prenume;
	float salariu;
	int nr;
	float* modificare; //modificari procentuale salariu ---2 
	static int an;
	GEN gen;
	bool areExperienta;

public:

	//9
	virtual float OferirePrima()
	{
		return salariu = salariu + 50;
	}

	// 3-----CONSTRUCTOR DEFAULT ANGAJAT
	Angajat() :cod(0)
	{
		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
		this->gen = NEUTRU;
		this->nr = 0;
		this->modificare = nullptr;
		this->salariu = 0;
		this->areExperienta = false;
	}

	//3----CONSTRUCTOR CU TOTI PARAMETRII ANGAJAT
	Angajat(int cod, const char* nume, string prenume, float salariu, int nr, float* modificare, GEN gen,bool areExperienta) :cod(cod)
	{
		if (nume != nullptr)
		{
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else
			throw new exception("Numele Angajatului este invalid");

		if (prenume.empty())
			throw new exception("Prenume angajat invalid");
		else
			this->prenume = prenume;

		if (salariu <= 0)
			throw new exception("Salariul angajatului este invalid");
		else
			this->salariu = salariu;

		if (nr <= 0)
			throw new exception("nr invalid");
		else
			this->nr = nr;

		if (modificare == nullptr)
			throw new exception("nr sau vector invalid");
		else
		{
			this->modificare = new float[nr];
			for (int i = 0; i < nr; i++)
				this->modificare[i] = modificare[i];
		}

		if (gen != 0 && gen != 1 && gen != 2)
			throw new exception("Gen invalid");
		else
			this->gen = gen;
		if (areExperienta != 1 && areExperienta != 0)
			throw new exception(" indicator invalid");
		else
			this->areExperienta = areExperienta;
	}

	//3----CONSTRUCTOR CU PARAMETRII ANGAJAT-NUME
	Angajat(int cod, string prenume, float salariu, int nr, float* modificare, GEN gen,bool areExperienta) :cod(cod)
	{
		this->nume = new char[strlen("Anonim") + 1];
		strcpy(this->nume, "Anonim");

		if (prenume.empty())
			throw new exception("Prenume angajat invalid");
		else
			this->prenume = prenume;

		if (salariu <= 0)
			throw new exception("Salariul angajatului este invalid");
		else
			this->salariu = salariu;

		if (nr <= 0)
			throw new exception("nr invalid");
		else
			this->nr = nr;

		if (modificare == nullptr)
			throw new exception("nr sau vector invalid");
		else
		{
			this->modificare = new float[nr];
			for (int i = 0; i < nr; i++)
				this->modificare[i] = modificare[i];
		}

		if (gen != 0 && gen != 1 && gen != 2)
			throw new exception("Gen invalid");
		else
			this->gen = gen;

		if (areExperienta != 1 && areExperienta != 0)
			throw new exception(" indicator invalid");
		else
			this->areExperienta = areExperienta;
	}


	//3-----COPY CONSTRUCTOR
	Angajat(const Angajat& s) :cod(s.cod)
	{
		this->nume = new char[strlen(s.nume) + 1];
		strcpy(this->nume, s.nume);
		this->prenume = s.prenume;
		this->salariu = s.salariu;
		this->nr = s.nr;
		this->modificare = new float[s.nr];
		for (int i = 0; i < s.nr; i++)
			this->modificare[i] = s.modificare[i];
		this->gen = s.gen;
		this->areExperienta = s.areExperienta;
	}


	//3----OPERATOR =
	Angajat& operator=(const Angajat& s)
	{
		if (this != &s) {
			if (this->nume != nullptr) {
				delete[] this->nume;
			}

			if (this->modificare != nullptr) {
				delete[] this->modificare;
			}

			this->nume = new char[strlen(s.nume) + 1];
			strcpy_s(this->nume, strlen(s.nume) + 1, s.nume);

			this->prenume = s.prenume;
			this->salariu = s.salariu;
			this->nr = s.nr;
			if (nr > 0)
			{
				this->modificare = new float[nr];
				for (int i = 0; i < nr; i++) {
					this->modificare[i] = s.modificare[i];
				}
			}
			this->gen = s.gen;
			this->areExperienta = s.areExperienta;
		}

		return *this;
	}

	//3----DESTRUCTOR ANGAJAT
	~Angajat()
	{
		if (this->nume != nullptr)
			delete[] this->nume;
		if (this->modificare != nullptr)
			delete[] this->modificare;
	}

	//4----OPERATORI

	//OPERATOR <<
	friend ostream& operator<<(ostream& out, const Angajat& a)
	{
		out << a.cod << " " << "  NUME: " << a.nume << "  PRENUME: " << a.prenume << "  GEN: " << a.gen << "  SALARIU: " << a.salariu <<"  ARE EXPERIENTA? "<<(a.areExperienta==true ? "DA" : "NU")<<"  NR MODIFICARI SALARIU: " << a.nr << "  MODIFICARI: " << endl;
		for (int i = 0; i < a.nr; i++)
		{
			out << a.modificare[i] << " ";
		}
		out << endl;
		return out;
	}

	//OPERATOR>>
	friend istream& operator>>(istream& in, Angajat& a)
	{
		char aux[100];
		cout << "NUME ANGAJAT:"; in >> aux;
		if (a.nume != nullptr)
			delete[] a.nume;
		a.nume = new char[strlen(aux) + 1];
		strcpy(a.nume, aux);
		cout << "PRENUME ANGAJAT:";
		in >> a.prenume;
		cout << "SALARIU ANGAJAT:";
		in >> a.salariu;
		cout << "NR MODIFICARI SALARIU:";
		in >> a.nr;
		if (a.modificare != nullptr)
			delete[] a.modificare;
		if (a.nr > 0)
		{
			a.modificare = new float[a.nr];
			for (int i = 0; i < a.nr; i++)
			{
				cout << "Modificare:";
				in >> a.modificare[i];
			}
		}
		int auxGen;
		cout << "GEN: 0 NEUTRU/ 1 MASCULIN/ 2 FEMININ : ";  in >> auxGen;
		switch (auxGen)
		{
		case 1:
			a.gen = MASCULIN;
			break;
		case 2:
			a.gen = FEMININ;
			break;
		case 0:
			a.gen = NEUTRU;
			break;
		}

		cout << "ARE EXPERIENTA? 0/1 = NU/DA : ";
		in >> a.areExperienta;
		return in;
	}


	//OPERATORUL DE PREINCREMENTARE ++ob
	const Angajat& operator++()
	{
		++salariu;
		return *this;
	}

	//OPERATOR DE POSTINCREMENTARE ob++
	const Angajat operator++(int)
	{
		Angajat aux(*this);
		salariu++;
		return aux;
	}

	//OPERATORUL DE POSTDECREMENTARE
	const Angajat operator--(int)
	{
		Angajat aux(*this);
		salariu--;
		return aux;
	}

	//OPERATORUL DE PREDECREMENTARE
	const Angajat& operator--()
	{
		--salariu;
		return *this;
	}

	//OPERATOR PLUS---OP BINARI

	//ob+x
	float operator+(float x)
	{
		return salariu + x;
	}

	//ob+ob
	Angajat operator+(Angajat& a)
	{
		Angajat aux(*this);
		aux.salariu = aux.salariu + a.salariu;
		return aux;
	}

	//x+ob
	friend float operator+(float x, Angajat& a)
	{
		return x + a.salariu;
	}

	//OPERATOR >

	//ob>x
	bool operator>(float x)
	{
		if (salariu > x)
			return true;
		else
			return false;
	}

	//ob>ob
	bool operator>(Angajat& a)
	{
		Angajat aux(*this);
		if (aux.salariu > a.salariu)
			return true;
		else
			return false;
	}
	//x>ob
	friend bool operator>(float x, Angajat& a)
	{
		if (x>a.salariu )
			return true;
		else
			return false;
	}

	//OPERATOR -=
	float operator-=(float x)
	{
		for (int i = 0; i < nr; i++)
		{
			if (x <= modificare[i])
				modificare[i] -= x;
		}
		for (int i = 0; i < nr; i++)
			return modificare[i];
	}

	//OPERATOR CAST
	operator string()
	{
		return prenume;
	}


	//OPERATOR !
	bool operator!()
	{
		return !areExperienta;
	}

	//OPERATOR INDEX
	float& operator[](int poz)
	{
		if (poz >= 0 && poz < nr)
		{
			return modificare[poz];
		}
		else
			throw new exception("pozitie invalida");
	}

	//OPERATOR FINCTIE
	void operator()(float x)
	{
		if (x <= 0.5 && x > 0)
		{
			for (int i = 0; i < nr; i++)
			{
				if (modificare[i] > 1 && (modificare[i] + x < 2))
					modificare[i] += x;
			}
		}
		else
			throw new exception(" valoare invalida");
	}

	//OPERATOR ==
	bool operator==(Angajat& s) {
		if (this == &s) {
			return true;
		}

		bool normalFields = strcmp(this->nume, s.nume) == 0 &&
			this->prenume == s.prenume &&
			this->salariu == s.salariu &&
			this->gen == s.gen &&
			this->nr == s.nr;

		if (normalFields == true) {
			for (int i = 0; i < nr; i++) {
				if (this->modificare[i] != s.modificare[i]) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}

	//GETTERI
	const char* getGenInChar()
	{
		switch (gen)
		{
		case MASCULIN:
			return "M";
			break;
		case FEMININ:
			return "F";
			break;
		case NEUTRU:
			return "NN";
			break;
		default:
			break;
		}
	}

	const char* getnume()
	{
		return nume;
	}

	string getprenume()
	{
		return prenume;
	}

	float getSalariul()
	{
		return salariu;
	}

	int getNr()
	{
		return nr;
	}

	float* getModificare()
	{
		float* aux = new float[nr];
		for (int i = 0; i < nr; i++)
		{
			aux[i] = modificare[i];
		}
		return aux;
	}

	int const getCod()
	{
		return cod;
	}

	int static GetAn()
	{
		return an;
	}

	bool getAreExperienta()
	{
		return areExperienta;
	}

	//6 SETTERI PENTRU EXCEPTIILE CUSTOM
	void setSalariu(double salariu)
	{
		if (salariu <= 0. || salariu >= 999999.)
			throw ExceptieCustomAngajat();
		else
		{
			this->salariu = salariu;
		}
	}

	void setPrenume(string prenume)
	{
		if (prenume.empty())
			throw ExceptieCustomAngajat();
		else
			this->prenume = prenume;
	}

	//7 op>> si << pentru angajati- fisier binar
	friend ofstream& operator<<(ofstream& ost, Angajat& s)
	{
		ost.write((char*)&s.cod, sizeof(int));

		int dim = strlen(s.nume) + 1; 
		ost.write((char*)&dim, sizeof(dim));
		ost.write(s.nume, dim);

		dim = s.prenume.size()+1;
		ost.write((char*)&dim, sizeof(dim));
		ost.write(s.prenume.c_str(), dim);
		
		ost.write((char*)&s.salariu, sizeof(float));
		ost.write((char*)&s.nr, sizeof(int));
		for (int i = 0; i < s.nr; i++)
			ost.write((char*)&s.modificare[i], sizeof(float));
		ost.write((char*)&s.gen, sizeof(GEN));
		ost.write((char*)&s.areExperienta, sizeof(bool));
		return ost;
	}

	friend ifstream& operator>>(ifstream& ist, Angajat& s)
	{
		ist.read((char*)&s.cod, sizeof(int));
		char aux[100];
		int dim = 0;
		ist.read((char*)&dim, sizeof(int));
	
		ist.read(aux, dim);
		s.nume = new char[dim];
		strcpy_s(s.nume, dim, aux);

		dim = 0;
		ist.read((char*)&dim, sizeof(dim));
		//ist.ignore();
		ist.read(aux, dim);
		s.prenume = aux;

		ist.read((char*)&s.salariu, sizeof(float));
		ist.read((char*)&s.nr, sizeof(int));
		if (s.nr > 0)
		{
			s.modificare= new float[s.nr];
			for (int i = 0; i < s.nr; i++)
				ist.read((char*)&s.modificare[i], sizeof(float));
		}
		ist.read((char*)&s.gen, sizeof(GEN));
		ist.read((char*)&s.areExperienta, sizeof(bool));
		//ist.ignore();
		return ist;
	}
};

//1 CLASA DERIVATA
class Doctor : private Angajat  //1.b)--mostenire privata
{
private:  //1 a) membrii sunt in zona private
	string specializare;
	bool areStetoscop;
public:

	//9
	float OferirePrima()
	{
		if (areStetoscop != 0)
			return (getSalariul() + 500);
	}

	//3-----CONSTRUCTOR DEFAULT DOCTOR
	Doctor() :Angajat()
	{
		this->areStetoscop = 0;
	}

	//3------CONSTRUCTOR CU TOTI PARAMETRII DOCTOR
	Doctor(int cod, const char* nume, string prenume, float salariu, int nr, float* modificare, GEN gen,bool areExperienta, string specializare, bool areStetoscop)
		: Angajat(cod, nume, prenume, salariu, nr, modificare, gen,areExperienta)
	{
		if (specializare.empty())
			throw new exception("specializarea este invalida");
		else
			this->specializare = specializare;
		if (areStetoscop != 0 && areStetoscop != 1)
			throw new exception("Conditia este invalida");
		else
			this->areStetoscop = areStetoscop;
	}

	//3------COPY CONSTRUCTOR DOCTOR
	Doctor(const Doctor& d):Angajat(d)
	{
		this->specializare = d.specializare;
		this->areStetoscop = d.areStetoscop;
	}

	//3------OPERATOR= DOCTOR
	Doctor& operator=(const Doctor& d)
	{
		if (this != &d)
		{
			Angajat::operator=(d);
			this->specializare = d.specializare;
			this->areStetoscop = d.areStetoscop;
		}
		return *this;
	}

	//3------DESTRUCTOR DOCTOR
	~Doctor() {}

	friend ostream& operator<<(ostream& out, Doctor& a)
	{
		out << a.getCod() << " " << "  NUME: " << a.getnume() << "  PRENUME: " << a.getprenume() << "  GEN: " << a.getGenInChar() << "  SALARIU: " << a.getSalariul() << "  ARE EXPERIENTA?  " <<(a.getAreExperienta()==true ? "DA" : "NU") <<"  NR MODIFICARI SALARIU: " << a.getNr() << "  MODIFICARI: " << endl;
		for (int i = 0; i < a.getNr(); i++)
		{
			out << a.getModificare()[i] << " ";
		}
		out << "  SPECIALIZARE: " << a.specializare << "  Are Stetoscop? " << (a.areStetoscop == 1 ? "DA" : "NU") << endl << endl;
		return out;
	}

};

//1 CLASA DERIVATA
class Asistent :private Angajat //1.b)--mostenire privata
{
private:  //1 a) membrii sunt in zona private
	string sectie;
	int vechime;
public:

	//9
	float OferirePrima()
	{
		if (vechime > 1)
			return getSalariul() + 200;
	}

	//3----CONSTRUCTOR DEFAULT Asistent
	Asistent() :Angajat() {}

	//3-----CONSTRUCTOR CU TOTI PARAMETRII ASISTENT
	Asistent(int cod, const char* nume, string prenume, float salariu, int nr, float* modificare, GEN gen,bool areExperienta, string sectie, int vechime)
		: Angajat(cod, nume, prenume, salariu, nr, modificare, gen,areExperienta)
	{
		if (sectie.empty())
			throw new exception("sectia este invalida");
		else
			this->sectie = sectie;
		if (vechime < 0)
			throw new exception("Elementul vechime este invalida");
		else
			this->vechime = vechime;
	}

	//3-----COPY CONSTRUCTOR ASISTENT
	Asistent(const Asistent& a):Angajat(a)
	{
		this->sectie = a.sectie;
		this->vechime = a.vechime;
	}

	//3----OPERATOR = ASISTENT
	Asistent& operator=(const Asistent& a) 
	{
		if (this != &a)
		{
			Angajat::operator=(a);
			this->sectie = a.sectie;
			this->vechime = a.vechime;
		}
		return *this;
	}

	//3----DESTRUCTOR DOCTOR
	~Asistent() {}

	friend ostream& operator<<(ostream& out, Asistent& a)
	{
		out << a.getCod() << " " << "  NUME: " << a.getnume() << "  PRENUME: " << a.getprenume() << "  GEN: " << a.getGenInChar() << "  SALARIU: " << a.getSalariul() << "  ARE EXPERIENTA?  " << (a.getAreExperienta() == true ? "DA" : "NU")<<"  NR MODIFICARI SALARIU: " << a.getNr() << "  MODIFICARI: " << endl;
		for (int i = 0; i < a.getNr(); i++)
		{
			out << a.getModificare()[i] << " ";
		}
		out << "  SECTIE: " << a.sectie << "  VECHIME: " << a.vechime << endl << endl;
		return out;
	}

	//6-----LEGAT DE CUSOM EXCEPTIONS
	void setVechime(int vechime)
	{
		if (vechime < 0 || vechime>68)
			throw ExceptieCustomAngajat();
		else
			this->vechime = vechime;

	}
};

//1 INTERFATA
class Iinfirmier
{
	virtual void adaugaBacsis() = 0;
	virtual void retrageBacsis() = 0;
};

//CLASA DERIVATA
class Infirmier : private Angajat //1.b)--mostenire privata
{
private:   //1 a) membrii sunt in zona private
	int nrPacientiInGrija;
	double* bacsis;  //2
public:
	//9
	float OferirePrima()
	{
		if (nrPacientiInGrija > 5)
			return getSalariul() + 100;
	}

	//3---CONSTRUCTOR DEFAULT INFIRMIER
	Infirmier() :Angajat()
	{
		this->nrPacientiInGrija = 0;
		this->bacsis = nullptr;
	}

	//3--CONSTRUCTOR CU TOTI PARAMETRII INFIRMIER
	Infirmier(int cod, const char* nume, string prenume, float salariu, int nr, float* modificare, GEN gen,bool areExperienta, int nrPacientiInGrija, double* bacsis)
		: Angajat(cod, nume, prenume, salariu, nr, modificare, gen,areExperienta)
	{
		if (nrPacientiInGrija <= 0)
			throw new exception("element invalid");
		else
			this->nrPacientiInGrija = nrPacientiInGrija;

		if (bacsis != nullptr)
		{
			this->bacsis = new double[nrPacientiInGrija];
			for (int i = 0; i < nrPacientiInGrija; i++)
				this->bacsis[i] = bacsis[i];
		}
	}

	//3----COPY CONSTRUCTOR INDIRMIER

	Infirmier(const Infirmier& s) :Angajat(s)
	{
		this->nrPacientiInGrija = s.nrPacientiInGrija;
		this->bacsis = new double[s.nrPacientiInGrija];
		for (int j = 0; j < s.nrPacientiInGrija; j++)
		{
			this->bacsis[j] = s.bacsis[j];
		}
	}

	//3---OPERATORUL = INFIEMIER
	Infirmier& operator=(Infirmier& s)
	{
		if (this != &s)
		{
			Angajat::operator=(s);
			if (this->bacsis != nullptr)
				delete[] this->bacsis;
			this->nrPacientiInGrija = s.nrPacientiInGrija;
			this->bacsis = new double[s.nrPacientiInGrija];
			for (int j = 0; j < s.nrPacientiInGrija; j++)
				this->bacsis[j] = s.bacsis[j];
		}
		return *this;
	}

	//3---DESTRUCTOR INFIRMIER
	~Infirmier()
	{
		if (this->bacsis != nullptr)
			delete[] this->bacsis;
	}

	friend ostream& operator<<(ostream& out, Infirmier& a)
	{
		out << a.getCod() << " " << "  NUME: " << a.getnume() << "  PRENUME: " << a.getprenume() << "  GEN: " << a.getGenInChar() << "  SALARIU: " << a.getSalariul() << "  ARE EXPERIENTA?  " << (a.getAreExperienta() == true ? "DA" : "NU")<< "  NR MODIFICARI  " << a.getNr() << " MODIFICARI: ";
		for (int j = 0; j < a.getNr(); j++)
		{
			out << a.getModificare()[j] << " ";
		}
		out << endl;
		out << "  NR PACIENTI IN GRIJA: " << a.nrPacientiInGrija << "  BACSIS: ";
		for (int i = 0; i < a.nrPacientiInGrija; i++)
		{
			out << a.bacsis[i] << " ";
		}
		out << endl;
		return out;
	}

	//IMPLEMENTARE INTERFATA

	void adaugaBacsis(double bani)
	{
		double* aux = new double[nrPacientiInGrija+1];
		for (int i = 0; i < nrPacientiInGrija; i++)
			aux[i] = bacsis[i];
		aux[nrPacientiInGrija++] = bani;
		delete[] bacsis;
		bacsis = aux;
	}

	void retrageBacsis(double bani)
	{
		int k = 0;
		for (int i = 0; i < nrPacientiInGrija; i++) {
			if (bani == bacsis[i]) {
				k++;
			}
		}
		if (k >0) {
			int j = 0;
			double* aux = new double[nrPacientiInGrija - k];
			for (int i = 0; i < nrPacientiInGrija; i++) {
				if (bani != bacsis[i]) {
					aux[j++] = bacsis[i];
				}
			}
			nrPacientiInGrija -= k;
			delete[] bacsis;
			bacsis = aux;
		}
	}
};

//1 CLASA ABSTRACTA
class Pacient {
private:   //1 a) membrii sunt in zona private
	int id;
	string numePacient;
	float valoare_reteta;
public:

	//ABSTRACTIZARE
	virtual float CompensareReteta() = 0;

	//9
	virtual float AdaugareElementeReteta(float val)
	{
		this->valoare_reteta += val;
		return valoare_reteta;
	}

	//10
	virtual float StergereElementeReteta(float valoare)
	{
		if (valoare <= valoare_reteta)
			return valoare_reteta - valoare;
		else
			cout << " NU SE POATE SCADEA ATAT DE MULT" << endl;
	}

	//3----CONSTRUCTOR DEFAULT PACIENT 
	Pacient()
	{
		this->id = 0;
		this->valoare_reteta = 0.0;
	}

	//3----CONSTRUCTOR CU TOTI PARAMETRII 
	Pacient(int id, string numePacient, float valoare_reteta) :id(id)
	{
		if (numePacient.empty())
			throw new exception("Nume pacient invalid");
		else
			this->numePacient = numePacient;
		if (valoare_reteta < 0)
			throw new exception("Valoarea retetei este invalida");
		else
			this->valoare_reteta = valoare_reteta;
	}

	//3-----COPY CONSTR PACIENT
	Pacient(const Pacient& p)
	{
		this->id = p.id;
		this->numePacient = p.numePacient;
		this->valoare_reteta = p.valoare_reteta;
	}

	//3-----OPERATOR=
	Pacient& operator=(const Pacient& p)
	{
		if (this != &p)
		{
			this->id = p.id;
			this->numePacient = p.numePacient;
			this->valoare_reteta = p.valoare_reteta;
		}
		return *this;
	}

	//3-----DESTRUCTOR PACIENT
	~Pacient() {}



	int getID()
	{
		return id;
	}

	string getnumepacient()
	{
		return numePacient;
	}

	float getValoareReteta()
	{
		return valoare_reteta;
	}

	friend ostream& operator<< (ostream& out, Pacient& p)
	{
		out << "ID PACIENT:" << p.id << "  NUME PACIENT: " << p.numePacient << " VALOARE RETETA:  " << p.valoare_reteta << endl;
		return out;
	}

};

class Copil : public Pacient
{
public:
	//3-----CONSTRUCTOR DEFAULT
	Copil() :Pacient() {}

	//3----CONSTRUCTOR CU TOTI PARAMETRII
	Copil(int id, string numePacient, float valoare_reteta) :Pacient(id, numePacient, valoare_reteta) {}

	//3----COPY CONSTR
	Copil(const Copil& c):Pacient(c){}

	//3---OP=
	Copil& operator=(const Copil& c)
	{
		if (this != &c)
		{
			Pacient::operator=(c);
		}
		return *this;
	}

	//3----DESTRUCTOR
	~Copil(){}

	//9
	float CompensareReteta()
	{
		return getValoareReteta() * 0.5;
	}

	float AdaugareElementeReteta(float val)
	{
		return getValoareReteta() + val;
	}

	//10
	float StergereElementeReteta(float valoare)
	{
		if (valoare <= getValoareReteta())
			return getValoareReteta() - valoare;
		else
			cout << " NU SE POATE SCADEA ATAT DE MULT"<<endl;
	}
};

class Adult : public Pacient
{
private:  //1 a) membrii sunt in zona private
	float taxa;
public:
	
	//3---CONSTR DEFAULT
	Adult() :Pacient()
	{
		this->taxa = 0.0;
	}

	//3---CONSTR CU TOTI PARAMETRII
	Adult(int id, string numePacient, float valoare_reteta, float taxa) : Pacient(id, numePacient, valoare_reteta)
	{
		if (taxa < 0)
			throw new exception("Taxa este invalida");
		else
			this->taxa = taxa;
	}

	//3---COPY CONST 
	Adult(const Adult& ad):Pacient(ad)
	{
		this->taxa = ad.taxa;
	}
	//3---OPERATOR=
	Adult& operator=(const Adult& ad)
	{
		if (this != &ad)
		{
			Pacient::operator=(ad);
			this->taxa = ad.taxa;
		}
		return *this;
	}

	//3---DESTRUCTOR
	friend ostream& operator<<(ostream& out, Adult& ad)
	{
		out << (Pacient&)ad;
		out << " TAXA " << ad.taxa << endl;
		return out;
	}

	//9
	float CompensareReteta()
	{
		if (taxa > 600)
			return getValoareReteta() * 0.6;
		else
			return getValoareReteta() * 0.3;
	}

	float AdaugareElementeReteta(float val)
	{
		return getValoareReteta() + val + 100;
	}

	//10
	float StergereElementeReteta(float valoare)
	{
		if (valoare <= getValoareReteta())
			return getValoareReteta() - valoare;
		else
			cout << " NU SE POATE SCADEA ATAT DE MULT" << endl;
	}
};

//5 COMPUNERE
class Spital {
private:   //1 a) membrii sunt in zona private
	string numeSpital;
	int nrAngajati;
	Angajat* angajati;
public:

	//CONSTR DEFAULT
	Spital() {}

	//CONSTR CU TOTI PARAMETRII
	Spital(string numeSpital, int nrAngajati, Angajat* angajati)
	{
		if (numeSpital.empty())
			throw new exception("Nume spital invalid");
		else
			this->numeSpital = numeSpital;
		if (nrAngajati <= 0)
			throw new exception("Nr invalid");
		else
			this->nrAngajati = nrAngajati;

		if (angajati == nullptr)
			throw new exception("vectorul este invalid");
		else
		{
			this->angajati = new Angajat[nrAngajati];
			for (int i = 0; i < nrAngajati; i++)
				this->angajati[i]=angajati[i];
		}

	}

	//DESTRUCTOR
	~Spital() {
		if (this->angajati != nullptr)
			delete[] this->angajati;
	}

	//CONSTR COPY
	Spital(const Spital& s)
	{
		this->numeSpital = s.numeSpital;
		this->nrAngajati = s.nrAngajati;
		this->angajati = new Angajat[s.nrAngajati];
		for (int i = 0; i < s.nrAngajati; i++)
			this->angajati[i] = s.angajati[i];
	}

	//OP =
	Spital& operator=(const Spital& s)
	{
		if (this != &s)
		{
			if (angajati != nullptr)
				delete[] this->angajati;

			this->numeSpital = s.numeSpital;
			this->nrAngajati = s.nrAngajati;
			this->angajati = new Angajat [s.nrAngajati];
			for (int i = 0; i < s.nrAngajati; i++)
				this->angajati[i] = s.angajati[i];
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, const Spital& sp)
	{
		out << " NUME SPITAL: " << sp.numeSpital << " NR angajati: " << sp.nrAngajati << " ANGAJATI: " << endl;
		for (int i = 0; i < sp.nrAngajati; i++)
			out << sp.angajati[i] << " ";
		out << endl;
		return out;
	}

	//op << fisier binar

	friend ofstream& operator<<(ofstream& op, const Spital& c)
	{
		int dim = c.numeSpital.size() + 1;
		op.write((char*)&dim, sizeof(dim));
		op.write(c.numeSpital.c_str(), dim);
		op.write((char*)&c.nrAngajati, sizeof(c.nrAngajati));
		for (int i = 0; i < c.nrAngajati; i++)
		{
			op << c.angajati[i];
		}
		return op;
	}

	//op >> fisier binar

	friend ifstream& operator>>(ifstream& opp, Spital& c)
	{
		int dim = 0;
		opp.read((char*)&dim, sizeof(dim));
		char aux[100];
		opp.read(aux, dim);
		c.numeSpital = aux;
		opp.read((char*)&c.nrAngajati, sizeof(c.nrAngajati));
		c.angajati = new Angajat[c.nrAngajati];
		for (int i = 0; i < c.nrAngajati; i++)
		{
			Angajat a;
			opp >> a;
			c.angajati[i] = Angajat(a);
		}
		return opp;
	}
};

//8 CLASA COMPUNERE STL
class SpitalSTL
{
private:   //1 a) membrii sunt in zona private
	string numeSpital;
	int nrAngajati;
    vector<Angajat>angajati;
public:
	
	SpitalSTL()
	{
		this->nrAngajati = 0;
	}

	SpitalSTL(string numeSpital, int nrAngajati, vector<Angajat>angajati)
	{
		if (numeSpital.empty())
			throw new exception("Nume spital invalid");
		else
			this->numeSpital = numeSpital;
		if (nrAngajati <= 0)
			throw new exception("Nr invalid");
		else
			this->nrAngajati = nrAngajati;

		if (angajati.size() != 0)
		{
			for (int i = 0; i < nrAngajati; i++)
				this->angajati.push_back(angajati[i]);
		}
		else
			throw new exception("vector invalid");
	}

	SpitalSTL(const SpitalSTL& s)
	{
		this->numeSpital = s.numeSpital;
		this->nrAngajati = s.nrAngajati;
		for (int i = 0; i < s.nrAngajati; i++)
			this->angajati.push_back(s.angajati[i]);
	}

	SpitalSTL& operator=(const SpitalSTL& s)
	{
		if (this != &s)
		{

			this->numeSpital = s.numeSpital;
			this->nrAngajati = s.nrAngajati;
			for (int i = 0; i < s.nrAngajati; i++)
				this->angajati.push_back(s.angajati[i]);
		}

		return *this;
	}

	~SpitalSTL()
	{}

	friend ostream& operator<<(ostream& out, const SpitalSTL& sp)
	{
		out << " NUME SPITAL: " << sp.numeSpital << " NR angajati: " << sp.nrAngajati << " ANGAJATI: " << endl;
		for (int i = 0; i < sp.nrAngajati; i++)
			out << sp.angajati[i] << " ";
		out << endl;
		return out;
	}

	//op << f b

	friend ofstream& operator<<(ofstream& op, const SpitalSTL& c)
	{
		int dim = c.numeSpital.size() + 1;
		op.write((char*)&dim, sizeof(dim));
		op.write(c.numeSpital.c_str(), dim);
		op.write((char*)&c.nrAngajati, sizeof(c.nrAngajati));
		for (Angajat a : c.angajati)
		{
			op << a;
		}
		return op;
	}

	//op >> fisier binar

	friend ifstream& operator>>(ifstream& opp, SpitalSTL& c)
	{
		while (!c.angajati.empty())
			c.angajati.pop_back();
		int dim = 0;
		opp.read((char*)&dim, sizeof(dim));
		char aux[100];
		opp.read(aux, dim);
		c.numeSpital = aux;
		opp.read((char*)&c.nrAngajati, sizeof(c.nrAngajati));
	   	Angajat a;
		for (int i = 0; i < c.nrAngajati; i++)
		{
			opp >> a;
			c.angajati.push_back(a);
		}

		return opp;
	}

};

int Angajat::an = 2022;

int main()
{
	float o[] = { 0.2,1.3 };
	float v[] = { 1.02,1.05,1.03 };
	float q[] = { 1.02,0.03 };
	Angajat a8, a1, a2(100, "Andrei", 1253, 2, o, NEUTRU, 0), a3(101, "Pana", "Andreea", 2590, 2, o, FEMININ, 1), a4(a2), a5(102, "Necula", "Cristina", 5987, 3, v, FEMININ, 1), a6, a7(103, "Paraschiv", "Alexandru", 4578, 3, v, MASCULIN, 0);
	Angajat a9(104, "Paun", "Silviu", 2541.5, 2, q, MASCULIN, 1), a10(105,"Adamescu","Simon",5471.66,2,o,MASCULIN,0);

	//3
	cout << "CONSTRUCTOR DEFAULT ANGAJAT" << endl;
	cout << a1 << endl;
	cout << "CONSTRUCTOR CU TOTI PARAMETRII ANGAJAT" << endl;
	cout << a3 << endl;
	cout << "CONSTRUCTOR (FARA CHAR) ANGAJAT" << endl;
	cout << a2 << endl;
	cout << "COPY CONSTRUCTOR ANGAJAT" << endl;
	cout << a4 << endl;
	cout << "OPERATORUL = ANGAJAT" << endl;
	a10=a9;
	cout <<a10<<a9 << endl;
	cout << "GETTERI ANGAJAT" << endl;
	cout << a5.getCod() << " " << a5.getnume() << " " << a5.getprenume() << " " << a5.getSalariul() << " " << a5.getGenInChar() << endl << endl;
	cout << "SETTERI ANGAJAT" << endl;
	 a1.setPrenume("Alexandru");
	 a1.setSalariu(125.3);
	 cout << a1 << endl << endl;

	//4
	cout << "-----OPERATORI ANGAJAT-----" << endl << endl;
	cout << "OPERATOR PRE-INCREMENTARE" << endl;
	++a3;
	cout << a3 << endl;
	cout << "OPERATOR POST-INCREMENTARE" << endl;
	a5++;
	cout << a5 << endl;
	cout << "OPERATOR PRE-DECREMENTARE" << endl;
	cout << --a3 << endl;
	cout << "OPERATOR POST-DECREMENTARE" << endl;
	a5--;
	cout << a5 << endl;
	cout << "CITIRE ANGAJAT (OPERATOR >>)" << endl;
	cin >> a6; cout << a6 << endl << endl;
	cout << "OPERATOR +" << endl;
	cout << 800 + a3 << endl;
	cout << a5 + 45.5 << endl;
	cout << a3 + a5 << endl << endl;
	cout << "OPERATOR >" << endl;
	cout << (1000 > a3) << endl;
	cout << (a3 > 1000) << endl;
	cout << (a5 > a3) << endl << endl;
	cout << "OPERATOR -=" << endl;
	a3 -= 0.1;
	cout << a3 << endl << endl;
	cout << "OPERATOR !" << endl;
	cout << !a5 << endl << endl;
	cout << "OPERATOR CAST IMPLICIT+EXPLICIT" << endl;
	//op cast explicit
	cout << " (string)a5 " << (string)a5 << endl;
	//op cast implicit;
	string prenume = a5;
	cout << prenume << endl << endl;
	cout << "OPERATOR INDEX" << endl;
	cout << a5[2] << endl << endl;
	cout << "OPERATOR FUNCTIE" << endl;
	a2(0.2);
	cout << a2 << endl << endl;
	cout << "OPERATOR ==" << endl;
	a8 = a7;
	cout << (a8 == a7) << endl<<endl;
	
	//6 
	cout << "EXCEPTII CUSTOM ANGAJAT" << endl;
	try {
		a7.setSalariu(0);
	}
	catch (ExceptieCustomAngajat e1)
	{
		cout << e1.what3() << endl;
	}

	try {
		a7.setPrenume("");
	}
	catch (ExceptieCustomAngajat e2)
	{
		cout << e2.what2() << endl<<endl<<endl;
	}

	Doctor d1, d2(200, "Pascale", "Adrian", 999999,3,v, MASCULIN,1, "NeuroChirurg", 0), d3(d2), d4, d5(201, "Papura", "Vlad", 999999,3,v, MASCULIN,1, "Chirurg Bariatric", 1);
	
	//3
	cout << "CONSTRUCTOR DEFAULT DOCTOR" << endl;
	cout << d1 << endl;
	cout << "CONSTRUCTOR CU TOTI PARAMETRII DOCTOR" << endl;
	cout << d2 << endl;
	cout << "COPY CONSTRUCTOR DOCTOR" << endl;
	cout << d3 << endl;
	cout << "OPERATORUL = DOCTOR" << endl;
	d2 = d4 = d5;
	cout << d2 << d4 << d5 << endl<<endl<<endl;

	Asistent as1, as2(300, "Alexandrescu", "Mihaela", 5962, 2, o, FEMININ,0, "Analize sange", 2), as3(as2), as4(301, "Anastasia", "Cristina", 4587, 2, o, FEMININ,1, "Neurologie", 3);

		//3
	cout << "CONSTRUCTOR DEFAULT ASISTENT" << endl;
	cout << as1 << endl;
	cout << "CONSTRUCTOR CU TOTI PARAMETRII ASISTENT" << endl;
	cout << as2 << endl;
	cout << "COPY CONSTRUCTOR ASISTENT" << endl;
	cout << as3 << endl;
	cout << "OPERATORUL = ASISTENT" << endl;
	as2 = as4;
	cout << as2<<as4 << endl<<endl;

	//6
	cout << "EXCEPTII CUSTOM ASISTENT" << endl;

	try {
		as2.setVechime(-1);
	}
	catch (ExceptieCustomAngajat e3)
	{
		cout << e3.what1() << endl<<endl<<endl;
	}

	double r[] = {987,32 };
	double rr[] = { 50,78,60,30,30,10,20 };

	Infirmier i1, i2(400, "Popescu","Ionut",4567,2,o,MASCULIN,1,7,rr), i3(i2), i4(401,"Vladimir","Tudose",4587,3,v,MASCULIN,1,2,r);
		
		//3
	cout << "CONSTRUCTOR DEFAULT INFIRMIER" << endl;
	cout << i1 << endl;
	cout << "CONSTRUCTOR CU TOTI PARAMETRII INFIRMIER" << endl;
	cout << i2 << endl;
	cout << "COPY CONSTRUCTOR INFIRMIER" << endl;
	cout << i3 << endl;
	cout << "OPERATORUL = INFIRMIER" << endl;
	i3 = i2;
	cout <<i2<<i3 << endl<<endl;

	cout << "----INTERFATA IMPLEMENTATA-----"<<endl;
	i2.adaugaBacsis(500);
	cout << i2 << endl;
	i2.retrageBacsis(30);
	cout << i2 << endl<<endl;


	Copil c0,c1(600, "Buscan Alin", 50), c2(601, "Neata Florian", 60),c3(c2);

		//3
	cout << "CONSTRUCTOR DEFAULT COPIL" << endl;
	cout << c0 << endl;
	cout << "CONSTRUCTOR CU TOTI PARAMETRII COPIL" << endl;
	cout << c1 << endl;
	cout << "COPY CONSTRUCTOR COPIL" << endl;
	cout << c3 << endl;
	cout << "OPERATORUL = COPIL" << endl;
	c3=c2;
	cout <<c3<<c2 << endl;

	Adult ad1(700, "Alexandru Marian", 200, 260), ad2(701, "Galeteanu Andrei", 600, 500), ad3(ad1),ad0;

		//3
	cout << "CONSTRUCTOR DEFAULT ADULT" << endl;
	cout << ad0 << endl;
	cout << "CONSTRUCTOR CU TOTI PARAMETRII ADULT" << endl;
	cout << ad1 << endl;
	cout << "COPY CONSTRUCTOR ADULT" << endl;
	cout << ad3 << endl;
	cout << "OPERATORUL = ADULT" << endl;
	ad0=ad3;
	cout << ad0<<ad3 << endl;

	Pacient* p1 = &c1, * p2 = &c2, * p3 = &ad1, * p4 = &ad2,* p6(p3);

		//3
	cout << "CONSTRUCTOR CU TOTI PARAMETRII PARINTE" << endl;
	cout << *p2 << endl;
	cout << "COPY CONSTRUCTOR PARINTE" << endl;
	cout << *p6 << endl;
	cout << "OPERATORUL = PARINTE" << endl;
	p6=p1;
	cout << *p6<<*p1 << endl;


	//5 CLASA COMPUNERE SPITAL
		Angajat g[] = { a3,a5 };
		Angajat h[] = { a4,a7 };
		Angajat l[] = { a3,a2,a7 };
		Spital s0,s1("Fundeni", 3, l), s2("Militar", 2, h),s3(s1), s4("Floreasca",2,g);
	
		//3
	cout << "CONSTRUCTOR DEFAULT SPITAL" << endl;
	cout << s0 << endl;
	cout << "CONSTRUCTOR CU TOTI PARAMETRII SPITAL" << endl;
	cout << s1 << endl;
	cout << "COPY CONSTRUCTOR SPITAL" << endl;
	cout << s3 << endl;
	cout << "OPERATORUL = SPITAL" << endl;
	s3=s4;
	cout << s3<<s4 << endl;

		//7
	  ofstream fisBinarOut("Spitale.bin", ios::out | ios::binary | ios::app);
	   if (fisBinarOut.is_open()) {
		   fisBinarOut << s1;
		   fisBinarOut << s2;

		   fisBinarOut.close();
	   }
	   else {
		   cout << "Fisierul nu poate fi deschis pentru scriere.\n";
	   }

	    Spital vv4,vv5;
	   ifstream fisBinarIn("Spitale.bin", ios::in | ios::binary);
	   if (fisBinarIn.is_open()) {
		   fisBinarIn >> vv4;
		  fisBinarIn >> vv5;
		   cout << "FISISER BINAR \n  " << vv4<<endl<<vv5;
		   fisBinarIn.close();
	   }
	   else {
		   cout << "Fisierul  nu poate fi deschis pentru citire.\n";
	   }

	   //8
       // CLASA STL----vector
		cout << "---------STL-----------"<<endl;

		vector<Angajat> vectorDeAngajati;
		vectorDeAngajati.push_back(a3);
		vectorDeAngajati.push_back(a5);
		vectorDeAngajati.push_back(a7);

		vector<Angajat> vectorang;
		vectorang.push_back(a5);
		vectorang.push_back(a2);

		//8
		SpitalSTL ss0,ss1("Carol Davila", 3, vectorDeAngajati), ss2("Universitar", 2, vectorang),ss3(ss2),ss4("Victor Babes",2,vectorang);
		cout << "CONSTRUCTOR DEFAULT SPITAL STL" << endl;
		cout << ss0 << endl;
		cout << "CONSTRUCTOR CU TOTI PARAMETRII SPITAL STL" << endl;
		cout << ss1 << endl;
		cout << "COPY CONSTRUCTOR SPITAL STL" << endl;
		cout << ss3 << endl;
		cout << "OPERATORUL = SPITAL STL" << endl;
		ss3 = ss4;
		cout << s3 << s4 << endl;

	  ofstream fisBinarOutt("SpitalSTL.bin", ios::out | ios::binary | ios::app);
	  if (fisBinarOutt.is_open()) {
		  fisBinarOutt << ss1;

		  fisBinarOutt.close();
	  }
	  else {
		  cout << "Fisierul nu poate fi deschis pentru scriere.\n";
	  }

	  SpitalSTL sss;
	  ifstream fisBinarInn("SpitalSTL.bin", ios::in | ios::binary);
	  if (fisBinarInn.is_open()) {
		  fisBinarInn >> sss;
		  cout << "FISIER BINAR STL:  \n " << sss;
		  fisBinarInn.close();
	  }
	  else {
		  cout << "Fisierul nu poate fi deschis pentru citire.\n";
	  }	
 
	   //9 Early binding
		cout << "-----EARLY BINDING-----"<<endl;
		cout<<ad1.AdaugareElementeReteta(50)<<endl;
		cout << ad1.CompensareReteta() << endl;

		cout<<ad2.AdaugareElementeReteta(69)<<endl;
		cout << ad2.CompensareReteta() << endl;

		cout<<c1.AdaugareElementeReteta(90)<<endl;
		cout << c1.CompensareReteta() << endl;

		cout<<c2.AdaugareElementeReteta(55)<<endl;
		cout << c2.CompensareReteta() << endl;


		//Late Binding
		cout << "------LATE BINDING-------" << endl;
		Pacient* p = &ad1;
		cout << p->AdaugareElementeReteta(50) << endl;
		cout << p->CompensareReteta() << endl;

		p = &ad2;
		cout<<p->AdaugareElementeReteta(69)<<endl;
		cout << p->CompensareReteta() << endl;

		p = &c1;
		cout << p->AdaugareElementeReteta(90) << endl;
		cout << p->CompensareReteta() << endl;

		p = &c2;
		cout<<p->AdaugareElementeReteta(55)<<endl;
		cout << p->CompensareReteta() << endl;


		//10 POLIMORFISM PE CLASA ABSTRACTA
		cout << "\nlista STL PENTRU POLIMORFISM\n";
		list<Pacient*> listaPacienti;
		listaPacienti.push_back(p1);
		listaPacienti.push_back(p2);
		listaPacienti.push_back(p3);
		listaPacienti.push_back(p4);
			for (Pacient *pacient : listaPacienti)
			{
				cout << pacient->StergereElementeReteta(3)<<endl;
			}
}