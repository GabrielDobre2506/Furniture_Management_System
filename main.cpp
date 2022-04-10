/*
	Nume: Dobre
	Prenume: Bogdan-Gabriel
	Tema: Gestiunea unui lant de magazine de mobilier
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;
#define _CRT_SECURE_NO_WARNINGS

//clasa mobilier
class Mobilier {
private:
	string numeMobilier;
	double pretCumparare;
	double pretVanzare;
	static int id;

public:
	//constructors
	Mobilier() {
		numeMobilier = (char*)malloc(sizeof(string));
		numeMobilier = "Gol";
		pretCumparare = 0;
		pretVanzare = 0;
		//id++;
	}
	Mobilier(string numeMobilier, double pretCumparare, double pretVanzare) {
		//id++;
		numeMobilier = (char*)malloc(numeMobilier.length() * sizeof(string));
		this->numeMobilier = numeMobilier;
		this->pretCumparare = pretCumparare;
		this->pretVanzare = pretVanzare;
	}
	Mobilier(const Mobilier& old_mag)
	{
		numeMobilier = (char*)malloc(old_mag.numeMobilier.length() * sizeof(string));
		numeMobilier = old_mag.numeMobilier;
		pretCumparare = old_mag.pretCumparare;
		pretVanzare = old_mag.pretVanzare;
	}

	//setters and getters
	void setNumeMobilier(string numeMobilier) {
		this->numeMobilier = numeMobilier;
	}
	string getNumeMobilier() {
		return this->numeMobilier;
	}

	void setPretCumparare(double pretCumparare) {
		this->pretCumparare = pretCumparare;
	}
	double getPretCumparare() {
		return this->pretCumparare;
	}

	void setPretVanzare(double pretCVanzare) {
		this->pretVanzare = pretCVanzare;
	}
	double getPretVanzare() {
		return this->pretVanzare;
	}


	int getId() {
		//return id;
	}

	//operations
	double getProfit() {
		return pretVanzare - pretCumparare;
	}

	//overloading
	Mobilier operator=(const Mobilier& b) {
		this->numeMobilier = b.numeMobilier;
		this->pretCumparare = b.pretCumparare;
		this->pretVanzare = b.pretVanzare;
		return *this;
	}

	friend istream& operator>>(istream& input, Mobilier& D) {
		cout << "Introduceti numele mobilierului: ";
		input >> D.numeMobilier;

		cout << "Introduceti pretul de cumparare: ";
		input >> D.pretCumparare;

		cout << "Introduceti pretul de vanzare: ";
		input >> D.pretVanzare;

		return input;
	}
	Mobilier operator+(const Mobilier& b) {
		Mobilier p;
		p.numeMobilier = this->numeMobilier + b.numeMobilier;
		p.pretCumparare = this->pretCumparare + b.pretCumparare;
		p.pretVanzare = this->pretVanzare + b.pretVanzare;
		return p;
	}
	//destructors
	~Mobilier() {

	}
};


class Magazin {//cerinta 1 - clasa abstracta
private:
	double profit;
	double cheltuieli;
public:
	//constructors
	Magazin() {
		profit = 0;
		cheltuieli = 0;
	}
	Magazin(const double profit, const double cheltuieli) {
		if (profit >= 0) {
			this->profit = profit;
		}
		else {
			cout << "Profitul nu poate fi negativ";
		}
		if (cheltuieli >= 0) {
			this->cheltuieli = cheltuieli;
		}
		else {
			cout << "Cheltuielile nu pot fi negative";
		}
	}
	Magazin(const Magazin& old_mag)
	{
		profit = old_mag.profit;
		cheltuieli = old_mag.cheltuieli;
	}

	//setters and getters
	void setProfit(const double profit) {
		if (profit >= 0) {
			this->profit = profit;
		}
		else {
			cout << "Profitul nu poate fi negativ";
		}
	}
	double getProfit() {
		return profit;
	}

	void setCheltuieli(const double cheltuieli) {
		if (cheltuieli >= 0) {
			this->cheltuieli = cheltuieli;
		}
		else {
			cout << "Cheltuielile nu pot fi negative";
		}
	}
	double getCheltuieli() {
		return cheltuieli;
	}

	//pure virtual functions
	virtual void calcProfit() = 0;
	virtual void calcCheltuieli() = 0;

	//destructors
	~Magazin() {
		profit = 0;
		cheltuieli = 0;
	}

};

class MagazinCluj : public Magazin {
private:
	string numeMagazin;
	vector<Mobilier*> inventar;
public:
	//constructors
	MagazinCluj() {
		this->numeMagazin = (char*)malloc(sizeof(char*));
	}
	MagazinCluj(string numeMagazin_2) {
		this->numeMagazin = (char*)malloc(numeMagazin_2.size() * sizeof(char*));
		if (this->numeMagazin.size() <= numeMagazin_2.size()) {
			this->numeMagazin = numeMagazin_2;
		}
		else {
			cout << "Nume magazin prea mare";
		}
	}
	MagazinCluj(MagazinCluj& old_mag)
	{
		this->numeMagazin = (char*)malloc(sizeof(string));
		setProfit(old_mag.getProfit());
		setCheltuieli(old_mag.getCheltuieli());
		this->numeMagazin = old_mag.numeMagazin;
	}

	//setters and getters
	void setNumeMagazin(string numeMagazin) {
		this->numeMagazin = numeMagazin;
	}
	string getNumeMagazin() {
		return this->numeMagazin;
	}
	void displayInventar() {
		for (int i = 0; i < this->inventar.size(); i++) {
			cout << "\t" << "Nume mobilier: " <<inventar[i]->getNumeMobilier() << endl << "\tPret cumparare: " << inventar[i]->getPretCumparare() << endl << "\tPret vanzare: " << inventar[i]->getPretVanzare() << endl;
		}
	}

	void genRap() {
		ofstream f;
		f.open("Raport.txt");
		if (!f) {
			cout << "Imposibil de creat fisier";
		}
		for (int i = 0; i < inventar.size(); i++) {
			f << "\t" << "Nume mobilier: " << inventar[i]->getNumeMobilier() << endl << "\tPret cumparare: " << inventar[i]->getPretCumparare() << endl << "\tPret vanzare: " << inventar[i]->getPretVanzare() << endl;
		}
	}

	//operations
	void addMobilier(Mobilier& newmobilier) {
		this->inventar.push_back(&newmobilier);
	}

	//abstract functions
	virtual void calcProfit() {
		double profit = 0;
		for (int i = 0; i < this->inventar.size(); i++) {
			profit = inventar[i]->getPretVanzare() - inventar[i]->getPretCumparare();
		}
		setProfit(profit);
	}
	virtual void calcCheltuieli() {
		double cheltuieli = 0;
		for (int i = 0; i < this->inventar.size(); i++) {
			cheltuieli = inventar[i]->getPretCumparare();
		}
		setCheltuieli(cheltuieli);
	}

	//destructors
	~MagazinCluj() {
		this->numeMagazin.clear();
	}
};







//functii pentru meniu
class Icons {
public:
	void printMenu() {
		std::cout << "Meniu" << std::endl;
	}
};



class Meniu {
private:
	int optiune, iesire;
	MagazinCluj clujMag[50];
	int clujMag_size;
	Icons icons;

public:
	Meniu() {
		optiune = 0;
		iesire = 1;
		clujMag_size = 0;
	}

	void view(int optiune) {
		if (optiune == 0) {
			std::cout << "1. Afiseaza magazine" << std::endl;
			std::cout << "2. Afiseaza profit magazine" << std::endl;
			std::cout << "3. Adauga magazin" << std::endl;
			std::cout << "4. Adauga mobilier" << std::endl;
			std::cout << "5. Salveaza fisier" << std::endl;
			std::cout << "6. Genereaza raport" << std::endl;
			std::cout << "7. Iesire" << std::endl;
		}
		if (optiune == 1) {
			cout << "Magazine Cluj:" << endl;
			for (int i = 0; i < clujMag_size; i++) {
				cout << "\tNume magazin: " << clujMag[i].getNumeMagazin() << endl;
				cout << "Obiecte de mobilier: " << "\t\n";
				clujMag[i].displayInventar();

			}
			cout << endl << "Pentru a va intoarce apasati tasta 0 " << endl;
		}
		if (optiune == 2) {
			for (int i = 0; i < clujMag_size; i++) {
				clujMag[i].calcProfit();
				cout << "Nume magazin: " << clujMag[i].getNumeMagazin() << endl;
				cout << "Profit: " << clujMag[i].getProfit() << endl;
			}
			cout << "Pentru a va intoarce apasati tasta 0 " << endl;
		}
		if (optiune == 3) {
			cout << "Introduceti nume Magazin: ";
			string numeMag = new char[100];
			cout << numeMag;
			cin >> numeMag;
			clujMag[clujMag_size++].setNumeMagazin(numeMag);
			cout << "Pentru a va intoarce apasati tasta 0 " << endl;
		}
		if (optiune == 4) {
			int optiune = 0;
			cout << "Selectati magazinul pentru care doriti sa adaugati mobilierul" << endl;
			for (int i = 0; i < clujMag_size; i++) {
				cout << i + 1 << ". " << clujMag[i].getNumeMagazin() << endl;
			}
			cout << "Introduceti magazinul: ";
			cin >> optiune;
			while (optiune > clujMag_size) {
				cout << "Optiune invalida, incercati din nou";
				cin >> optiune;
			}
			Mobilier flow;
			cin >> flow;
			clujMag[optiune - 1].addMobilier(flow);
			cout << endl << "Pentru a va intoarce apasati tasta 0 " << endl;
		}
		if (optiune == 5) {
			ofstream ofdata;
			ofdata.open("appData.txt");
			if (!ofdata) {
				cout << "Fisier imposibil de deschis";
			}
			for (int i = 0; i < clujMag_size; i++) {
				ofdata << "\tNume magazin: " << clujMag[i].getNumeMagazin() << endl;
			}
			cout << "Fisier creat cu succes!" << endl;
			cout << "Pentru a va intoarce apasati tasta 0 " << endl;
		}
		if (optiune == 6) {
			for (int i = 0; i < clujMag_size; i++) {
				clujMag[i].genRap();
			}
			cout << "Pentru a va intoarce apasati tasta 0 " << endl;
		}
	}

	void stateMachine() {

		while (iesire) {
			system("cls");
			icons.printMenu();
			view(optiune);

			cout << "Selectati o optiune: ";
			cin >> optiune;

			//state machine start
			switch (optiune)
			{
			case 0:
				optiune = 0;

				break;
			case 1:
				optiune = 1;
				break;

			case 2:
				optiune = 2;
				break;
			case 3:
				optiune = 3;
				break;
			case 4:
				optiune = 4;
				break;
			case 5:
				optiune = 5;
				break;
			case 6:
				optiune = 6;
				break;
			case 7:
				iesire = 0;
				break;
			default:
				cout << "Optiune invalida";
				break;
			}
		}
	}


};

template<class T>//cerinta 3 - ierarhie
class Object {
private:
protected:
public:
	Object() {}
	virtual void displayLoginMenu(){}//cerinta 2 - metode virtuale
	virtual void check(string pa, string us){}
	~Object(){}
};

template <typename T>
class User:public Object<T> {
private:
	string name, password;
	Meniu menu;
protected:
public:
	User(){	
	}
	User(string name,string password) {
		this->name = name;
		this->password = password;
	}
	string get_name() {
		return this->name;
	}
	string get_password() {
		return this->password;
	}
	void setPass(string pass) {
		this->password = pass;
	}
	void setUserName(string userName) {
		this->name = userName;
	}
	void displayLoginMenu() {
		std::cout << "Login" << std::endl;
	}
	void check(string pa, string us) {
		if (us == this->name) {
			if (pa == this->password) {
				menu.stateMachine();
			}
			else {
				cout << "Incorrect password" << endl;
			}
		}
	}
};


int main() {	
	string us;
	cout << "Adaugati un user\nUsername: ";
	cin >> us;
	string pass;
	cout << "Adaugati parola: ";
	cin >> pass;
	vector<Object<string>*> users;//cerinta 4 - vector de pointeri
	users.push_back(new User<string>(us, pass));
	system("cls");
	users.back()->displayLoginMenu();
	cout << "\nIntroduceti username: ";
	string userName;
	cin >> userName;
	cout << "Introduceti parola: ";
	string password;
	cin >> password;
	users.back()->check(password, userName);
	
}

