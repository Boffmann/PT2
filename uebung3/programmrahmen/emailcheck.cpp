#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>

#define ENTRIES 7

std::wstring dataset[ENTRIES][4] = { { L"max.muestermann@bmw.de", L"Max", L"Mustermann", L"SAP" },
    { L"juergen.doellner@hpi.de", L"Jürgen", L"Döllner", L"HPI" },
    { L"soeren.discher@hpi.de", L"Sören", L"Discher", L"HPI" } ,
    { L"daniel.maeller@hpi.de", L"Daniel", L"Mäller", L"HPI" },
    { L"paul.deissler@hertha.de", L"Sebastian", L"Deißler", L"herTha" },
	{ L"mueller.marga@sap.com", L"Marga", L"Müller", L"SAP" },
    { L"h.boss@service.bayer.com", L"Hugo", L"Boss", L"Bayer" }};

//Replaces [from] with [to] in [str]
void ReplaceAll(std::wstring& str, const std::wstring& from, const std::wstring& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::wstring::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
}

//ToDo 3.1a - implement use std::transform()
void caseConvert(std::wstring& str) {
    
	/*for(int i = 0; i<str.length();i++)
	{
		if(str[i] > 64 && str[i] < 91)
			str[i] += 32;
	}*/

	std::transform(str.begin(), str.end(), str.begin(), ::tolower);

}

//ToDo 3.1b - implement replacement for ä, ö, ü, ß with ae,oe,ue,ss
//			- use ReplaceAll. wstrings are declared the same way as normal strings but with an "L" in front
void replace(std::wstring& str) {

	ReplaceAll(str, L"ä", L"ae");
	ReplaceAll(str, L"ö", L"oe");
	ReplaceAll(str, L"ü", L"ue");
	ReplaceAll(str, L"ß", L"ss");

}

//ToDo 3.1c - check if email is correct
bool emailCheck(std::wstring mail, std::wstring firstname, std::wstring name, std::wstring company)
{
	std::string e_mail(mail.begin(), mail.end());
	std::string s_firstname(firstname.begin(), firstname.end());
	std::string s_name(name.begin(), name.end());
	std::string s_company(company.begin(), company.end());


	std::string in_mail_vorname = e_mail.substr(0, e_mail.find("."));
	std::string in_mail_nachname = e_mail.substr(e_mail.find(".")+1, e_mail.find("@")-(e_mail.find(".")+1));
	//std::string after_AT = e_mail.substr(e_mail.find("@")+1, e_mail.length() - (e_mail.find("@")+1));
	std::string in_mail_firma = e_mail.substr(e_mail.find("@")+1, e_mail.find(".")-(e_mail.find("@")+1));

	std::cout << in_mail_vorname << "__" << in_mail_nachname << "__" << in_mail_firma << std::endl;

	/*if((strncmp(s_firstname, in_mail_vorname, in_mail_vorname.length()) <= 0 || strncmp(s_firstname, in_mail_nachname, in_mail_nachname.length()) <= 0) 
		&& (strncmp(s_name, in_mail_nachname, in_mail_nachname.length()) <= 0 || strncmp(s_name, in_mail_vorname, in_mail_vorname.length()) <= 0) 
		&& (strncmp(s_company, in_mail_firma, in_mail_firma.length()) <= 0))*/

		if((s_firstname.compare(in_mail_vorname) <= 0 || s_firstname.compare(in_mail_nachname) <= 0) 
		&& (s_name.compare(in_mail_nachname) <= 0 || s_name.compare(in_mail_vorname) <= 0) 
		//&& (strncmp(s_company, in_mail_firma, in_mail_firma.length()) <= 0)
		)
		return true;
	else 
    return false;
}

int main(int argc, char * argv[])
{
    for (int i = 0; i < ENTRIES; i++)
    {
        for (int j = 1; j < 4; j++)
        {
            replace(dataset[i][j]);
            caseConvert(dataset[i][j]);
        }
        
        std::cout << emailCheck(dataset[i][0], dataset[i][1], dataset[i][2], dataset[i][3]) << std::endl;
    }
    
    return 0;
    
}