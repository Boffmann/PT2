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
		double convert(double value);
		void print();

};

Amount::Amount() : brutto{0}, mwst{0.19}, bezeichnung{""}, currency{EUR}
{
	netto = brutto / (1.0 + mwst);
}

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
	netto = brutto / (1.0 + mwst);
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

double Amount::convert(double value)
{
	if(currency == EUR) {
		return value *= EUR_TO_USD;
	} else 
		return value *= USD_TO_EUR;
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
	Amount a1(42);
	a1.print();
	a1.convert();
	a1.print();
	a1.changeBrutto(50.27);
	a1.print();
	a1.convert();
	a1.print();
	
	std::cout << std::endl;
	
	Amount a2(9001, 0.8, USD);
	a2.print();
	a2.convert();
	a2.print();
	a2.changeBrutto(42);
	a2.print();
	a2.convert();
	a2.print();

	std::cout << std::endl;
	
	Amount a3(1337, "Skills");
	a3.print();
	a3.convert();
	a3.print();
	a3.changeBrutto(42);
	a3.print();
	a3.convert();
	a3.print();

	std::cout << std::endl;
	
	Amount a4(911, 0.10, "JETFUELCANTMELTSTEELBEAMS", USD);
	a4.print();
	a4.convert();
	a4.print();
	a4.changeBrutto(1337);
	a4.print();
	a4.convert();
	a4.print();
}

int main() {
	test();
    return 0;
}