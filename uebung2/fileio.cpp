#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>


bool isValueCorrect(const std::string &teststring, const int &column)
{
	std::regex regExp;
	
	switch (column)
	{
		//regExp for column 1
        case 1:
            regExp = "^[0-9]+$";	// id
            break;
        case 2:
            regExp = "^(.*?)$";		// name
            break;
        case 3:
            regExp = "^(.*?)$";		// city
            break;
        case 4:
            regExp = "^(.*?)$";		//country
            break;
        case 5:
            regExp = "^(.*?)$";		// iata iata_faa 	^([\"]|)([A-Z0-9]{1,4}|)([\"]|)$
            break;
        case 6:
            regExp = "^([\"]|)([A-Z]{4}|[\\\\][N]|)([\"]|)$";	//icao (blank is \N and nothing)
            break;
        case 7:
            regExp = "^(.*?)$";		// latitude		^(([-]|)[0-9]+[.][0-9]{1,6})$
            break;
        case 8:
            regExp = "^(.*?)$";		// longitude	^(([-]|)[0-9]+[.][0-9]{1,6})$
            break;
        case 9:
            regExp = "^([1-2][0-8][0-9]{1,3}$|^[2][9][0][0][0]$|^[0-9]{1,4})$";	// altitude
            break;
        case 10:
            regExp = "^([-][1][0-2]|[-][0-9]|[-][349][.][5]|[0-9]|([34569]|[1][01])[.][5]|[1][0-4]|([58]|[1][2])[.][7][5])$";		// utc offset timezone
            break;
        case 11:
            regExp = "^([\"]|)[EASOZNU]([\"]|)$";	// dst
            break;
        case 12:
            regExp = "(^.*?$)";		// database timezone
            break;    

		//Todo implement cases for other columns

		default:
			regExp = ".*";
			break;
	}
	return std::regex_match(teststring, regExp);
}

void readTokensAndLines(char* path)
{
	std::ifstream file(path);
	std::string parsed, line;
	std::string id, name, city, country, iata_faa, icao, latitude, longitude, altitude, utc_offset_timezone, dst, database_timezone;
	std::ofstream logfile;
	logfile.open("fileio.log");
	while (std::getline(file, line)) {
		std::istringstream linestream;
		linestream.str(line);
		int tmp = 0;
		int column = 0;

		//airport with id 5562 has city with , in its name which makes it appear in the logfile for all values

		column++;
		id = line.substr(tmp,line.find_first_of(',', tmp));
		tmp += id.length() + 1;
		
		column++;
		name = line.substr(tmp,line.find_first_of(",", tmp) - tmp);
		tmp += name.length() + 1;
		
		column++;
		city = line.substr(tmp,line.find_first_of(",", tmp) - tmp);
		tmp += city.length() + 1;
		
		column++;
		country = line.substr(tmp,line.find_first_of(",", tmp) - tmp);
		tmp += country.length() + 1;
		
		column++;
		iata_faa = line.substr(tmp,line.find_first_of(",", tmp) - tmp);
		tmp += iata_faa.length() + 1;
		if(!isValueCorrect(iata_faa, column)){
			logfile << line << " ERROR in IATA/FAA: " << iata_faa << std::endl;
		}

		column++;
		icao = line.substr(tmp,line.find_first_of(",", tmp) - tmp);
		tmp += icao.length() + 1;
		if(!isValueCorrect(icao, column)){
			logfile << line << " ERROR in ICAO: " << icao << std::endl;
		}

		column++;
		latitude = line.substr(tmp,line.find_first_of(",", tmp) - tmp);
		tmp += latitude.length() + 1;
		
		column++;
		longitude = line.substr(tmp,line.find_first_of(",", tmp) - tmp);
		tmp += longitude.length() + 1;
		
		column++;
		altitude = line.substr(tmp,line.find_first_of(",", tmp) - tmp);
		tmp += altitude.length() + 1;
		if(!isValueCorrect(altitude, column)){
			logfile << line << " ERROR in Altitude: " << altitude << std::endl;
		}

		column++;
		utc_offset_timezone = line.substr(tmp,line.find_first_of(",", tmp) - tmp);
		tmp += utc_offset_timezone.length() + 1;
		if(!isValueCorrect(utc_offset_timezone, column)){
			logfile << line << " ERROR in UTC offset timezone: " << utc_offset_timezone << std::endl;
		}
		
		column++;
		dst = line.substr(tmp,line.find_first_of(",", tmp) - tmp);
		tmp += dst.length() + 1;
		if(!isValueCorrect(dst, column)){
			logfile << line << " ERROR in DST: " << dst << std::endl;
		}

		column++;
		database_timezone = line.substr(tmp,line.find_first_of(",", tmp) - tmp);
		
		std::cout << name << " - " << database_timezone << std::endl;
		// ToDo: Exercise 2.2a - Split line and write result to std::cout
		// ToDo: Exercise 2.2b - Check each part of line with isValueCorrect and log if values are not supported. Use and extend isValueCorrect function for this.	
	}
	//logfile.close();
}

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		std::cout << "not enough arguments - USAGE: fileio [DATASET]" << std::endl;
		return -1;	// invalid number of parameters
	}
	
	std::cout << "Given path to airports.dat: " << argv[1] << std::endl;

	// ToDO: Exercise 2.2a - Parse the stream by lines and every line by its delimiter
	//					   - Print the name of the airport and the timeZone for each airport
	readTokensAndLines(argv[1]);

	return 0;
}
