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
            regExp = "^[\"][A-Za-z]+[( |\\-)A-Za-z]+[\"]$";		// name
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
            regExp = "^[\"].+[\\/].+[\"]$";		// database timezone
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
		int begin = 0;
		int end = 0;
		int column = 0;
		std::regex comma;
		comma = "[^ ][,][^ ]";
		std::string p_line = line;
		line = "," + line + ",a";
    	std::string name_timezone;
		for(std::string::size_type i = 0; i < line.size(); ++i) {
			bool tmp2;
			if(i == 0) tmp2 = std::regex_match(line.substr(i , 2), comma);
			else if(i == line.size() - 1) tmp2 = std::regex_match(line.substr(i-1 , 2), comma);
			else tmp2 = std::regex_match(line.substr(i-1 , 3), comma);
    		if(tmp2) {
    			begin = end + 1;
    			end = i;
    			std::string tmp = line.substr(begin, end - begin);
    			//std::cout << tmp << std::endl;
    			column++;
    			bool tmp3 = isValueCorrect(tmp, column);
    			if(isValueCorrect(tmp, column)) {
    				if(column == 2) name_timezone = tmp + " - ";
    				if(column == 12) {
    					name_timezone += tmp;
    					std::cout << name_timezone << std::endl;
    					name_timezone = "";
    				}
    			} else {
    				if(column == 6) logfile << p_line << " ERROR in ICAO: " << tmp << std::endl;
    				if(column == 9) logfile << p_line << " ERROR in Altitude: " << tmp << std::endl;
    				if(column == 10) logfile << p_line << " ERROR in DST: " << tmp << std::endl;
    			}
    		}
		}
		// ToDo: Exercise 2.2a - Split line and write result to std::cout
		// ToDo: Exercise 2.2b - Check each part of line with isValueCorrect and log if values are not supported. Use and extend isValueCorrect function for this.	
	}
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
