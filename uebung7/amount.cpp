#include <iostream>
#include <math.h>

enum waehrung {
	EUR,
	USD
};

class Amount {
		//ToDo 7.2
		//Implement class Amount
		double netto, brutto;
		float mwst;
		const float USD_TO_EUR = 0.896205912f;
		const float EUR_TO_USD = 1.115815f;
		waehrung currency;
		std::string bezeichnung; 
	public:
		Amount();
		Amount(waehrung curr);
		Amount(double preis);
		Amount(double preis, waehrung curr);
		Amount(double preis, float steuersatz);
		Amount(double preis, float steuersatz, waehrung curr);
		Amount(double preis, std::string);
		Amount(double preis, std::string, waehrung curr);
		Amount(double preis, float steuersatz, std::string bezeichnung);
		Amount(double preis, float steuersatz, std::string bezeichnung, waehrung curr);

		void changeBrutto(double add);
		double getNetto() const;
		double getBrutto() const;
		void convert();
		void print();

};

Amount::Amount(waehrung curr) : brutto{0}, mwst{0.19}, bezeichnung{""}
{
	netto = brutto / (1.0 + mwst);
	currency = curr;
}

Amount::Amount(double preis) : netto{preis}, mwst{0.19}, bezeichnung{""}, currency{EUR}
{
	brutto = netto * (1.0 + mwst);
}

Amount::Amount(double preis, waehrung curr) : netto{preis}, mwst{0.19}, bezeichnung{""}
{
	brutto = netto * (1.0 + mwst);
	currency = curr;
}

Amount::Amount(double preis, float steuersatz) : netto{preis}, mwst{steuersatz}, bezeichnung{""}, currency{EUR}
{
	brutto = netto * (1.0 + mwst);
}

Amount::Amount(double preis, float steuersatz, waehrung curr) : netto{preis}, mwst{steuersatz}, bezeichnung{""}
{
	brutto = netto * (1.0 + mwst);
	currency = curr;
}

Amount::Amount(double preis, std::string bezeichnung) : netto{preis}, mwst{0.19}, bezeichnung{bezeichnung}, currency{EUR}
{
	brutto = netto * (1.0 + mwst);
}

Amount::Amount(double preis, std::string bezeichnung, waehrung curr) : netto{preis}, mwst{0.19}, bezeichnung{bezeichnung}
{
	brutto = netto * (1.0 + mwst);
	currency = curr;
}

Amount::Amount(double preis, float steuersatz, std::string bezeichnung) :
			   netto{preis}, mwst{steuersatz}, bezeichnung{bezeichnung}
{
	brutto = netto * (1.0 + mwst);
	currency = EUR;
}

Amount::Amount(double preis, float steuersatz, std::string bezeichnung, waehrung curr) :
			   netto{preis}, mwst{steuersatz}, bezeichnung{bezeichnung}
{
	brutto = netto * (1.0 + mwst);
	currency = curr;
}

void Amount::changeBrutto(double add)
{
	brutto += add;
	if(brutto > 0) {
		netto = brutto / (1.0 + mwst);
	} else {
		brutto = 0;
		netto = 0;
	}
}

double Amount::getNetto() const{
	return netto;
}

double Amount::getBrutto() const{
	return brutto;
}

void Amount::convert(){
	double fac = 1.0;
	if(currency == EUR) {
		fac = EUR_TO_USD;
		currency = USD;
	} else {
		fac = USD_TO_EUR;
		currency = EUR;
	}
	brutto *= fac;
	netto *= fac;	
}

void Amount::print(){
	std::string cur = currency == EUR ? "EUR" : "USD";
	if(bezeichnung.size() >= 1)
		std::cout << bezeichnung << " hat ";
	std::cout << "Nettopreis: " << round(netto * 100)/100 << " " << cur << ", Bruttopreis: " << round(brutto * 100)/100 << " " << cur << std::endl;
	std::cout << "Bei einem Mehrwertsteuersatz von: " << 100.0 * mwst << "%" << std::endl;
}

void test() {
	//ToDo 7.2
	//implement tests
	
	Amount a1(USD);
	a1.print();
	a1.convert();
	a1.print();

	std::cout << std::endl;

	Amount a2(53.54);
	a2.print();
	a2.changeBrutto(-2.5);
	a2.print();
	a2.convert();
	a2.print();

	std::cout << std::endl;
	
	Amount a3(82.42, USD);
	a3.print();
	a3.changeBrutto(91.4);
	a3.print();

	std::cout << std::endl;
	
	Amount a4(71.23, 0.19);
	a4.print();
	a4.convert();
	a4.print();

	std::cout << std::endl;
	
	Amount a5(32.1, 0.42, USD);
	a5.print();
	a5.convert();
	a5.print();
	a5.changeBrutto(12.0);
	a5.print();
	a5.convert();
	a5.print();

	std::cout << std::endl;

	Amount a6(13.37, "Skills");
	a6.print();

	std::cout << std::endl;
	
	Amount a7(9.11, "Cord", USD);
	a7.print();

	std::cout << std::endl;
	
	Amount a8(12.34, 0.07, "Italian BMT");
	a8.print();

	std::cout << std::endl;
	
	Amount a9(43.21, 0.12, "Chicken Teriyaki", USD);
	a9.print();

}

int main() {
	test();
    return 0;
}