#include <iostream>

class Amount {
		//ToDo 7.2
		//Implement class Amount
		double netto, brutto;
		float mehrwertsteuer;
		const float from_dollar_to_euro = 0.896205912f;
		const float from_euro_to_dollar = 1.115815f;
		enum waehrung {EUR, USD};
		waehrung currency;
		std::string bezeichnung; 
	public:
		Amount();
		Amount(double startkapital);
		Amount(double startkapital, float steuersatz);
		Amount(double startkapital, std::string);
		Amount(double startkapital, float steuersatz, std::string bezeichnung);
		bool addBrutto(double add);
		double getBalance() const;
		bool convert();
		double convert(double betrag);
		bool setSteuer(float tax);
		void print();

};

Amount::Amount() : brutto{0}, mehrwertsteuer{0.19}, bezeichnung{"void"}
{
	netto = brutto - brutto * mehrwertsteuer;
	currency = EUR;
}
Amount::Amount(double startkapital) : brutto{startkapital}, mehrwertsteuer{0.19}, bezeichnung{""}
{
	netto = brutto - brutto * mehrwertsteuer;
	currency = EUR;
}
Amount::Amount(double startkapital, float steuersatz) : brutto{startkapital}, mehrwertsteuer{steuersatz}, bezeichnung{""}
{
	netto = brutto - brutto * mehrwertsteuer;
	currency = EUR;
}
Amount::Amount(double startkapital, std::string bezeichnung) : brutto{startkapital}, mehrwertsteuer{0.19}, bezeichnung{bezeichnung}
{
	netto = brutto - brutto * mehrwertsteuer;
	currency = EUR;
}
Amount::Amount(double startkapital, float steuersatz, std::string bezeichnung) :
			   brutto{startkapital}, mehrwertsteuer{steuersatz}, bezeichnung{bezeichnung}
{
		netto = brutto - brutto * mehrwertsteuer;
		currency = EUR;
}

bool Amount::addBrutto(double add)
{
	if(brutto + add >= brutto)
	{
		brutto += add;
		netto = brutto - brutto * mehrwertsteuer;
		return true;
	}
	else return false;
}

double Amount::getBalance() const{
	return netto;
}

bool Amount::convert(){
	if(currency == EUR)
	{
		brutto *= from_euro_to_dollar;
		netto *= from_euro_to_dollar;
		currency = USD;
	}
	else{
		brutto *= from_dollar_to_euro;
		netto *= from_dollar_to_euro;
		currency = EUR;
	}
}
double Amount::convert(double betrag)
{
	if(currency == EUR)
	{
		return betrag *= from_euro_to_dollar;
	}else 
		return betrag *= from_dollar_to_euro;
}


void Amount::print(){
	std::cout << "Verfügbares Kapital: " << netto;
	if(currency == EUR) std::cout << " EUR"; else std::cout << " USD";
	std::cout <<  std::endl << "Bei einem steuersatz von: " << mehrwertsteuer << "%" << std::endl;
}

void test() {
	//ToDo 7.2
	//implement tests
	Amount a1(42);
	a1.print();
	a1.addBrutto(50.27);
	a1.print();
	a1.convert();
	a1.print();

	Amount a2(50, "Auto");

}

int main() {
	test();
    return 0;
}