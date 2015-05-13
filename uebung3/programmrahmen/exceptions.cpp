#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cfloat>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <ctime>


// transforms a string to a date. Throws a logic_error if year is *not* between 2005 and 2015
std::tm stringToTime(std::string date)
{
    std::tm t;
    std::istringstream ss(date);
    //ss >> std::get_time(&t, "%d.%m.%Y");

    strptime(date.c_str(), "%d.%m.%Y", &t);
    
    if(t.tm_year < 105 || t.tm_year > 115)
    {
            std::cout << 1900+t.tm_year << std::endl;
        throw std::logic_error("Year should be between 2005 and 2015");
    }
    
    return t;
}

struct FormatException
{
    int m_actLine;
    std::string m_actFields;
};

void parseLine(std::string line, int lineNum)
{
    const std::string fieldNames[3] = { "Date", "Temperature", "Rainfall" };
    
    // todo 3.2b: parse a given line, check dates by calling stringToTime, check temperature/rainfall by calling std::stof. 
    //Catch all exceptions thrown by these methods. If there have been any exceptions, aggregate all necessary information 
    //into an instance of FormatException and throw that instance.

   std::string parsed;
    int count = 0;
    std::istringstream linestream;
        linestream.str(line);


    while(std::getline(linestream, parsed, ';'))
    {
    	//std::cout << "enterd " << parsed << std::endl;
        count++;
    
	           	try{	           		
		           		if(count == 1)
			           		{
			                stringToTime(parsed);
			           		}
		            	else
			            	{
			                float casted = std::stof(parsed, 0);
			                }	
	           	}catch(std::exception e){	        
	                struct FormatException exc;
	                exc.m_actLine = lineNum;
	                exc.m_actFields = line;
	                throw exc;
	            } 

    }
    
}

// todo 3.2c..
void writeOutFormatException(const FormatException & e)
{
	std::ofstream logfile;
	logfile.open("../../data/logfile.txt");
	int line = e.m_actLine;
	std::string line_content = e.m_actFields;

	logfile << "Line: " << line << " ; content: " << line_content;

    // todo 3.2d: export information (i.e., line number + invalid data fields) about exception to a logfile.
    // todo 3.2d: catch ios_base::failure
}

void checkData(std::string path)
{

	int validLines = 0;
    int invalidLines = 0;
    int line_Nr = 0;
    std::ifstream file;
    std::string line, parsed;
    try{
   		 	
    		file.open(path);
    

		    while(std::getline(file, line))
			    {
				    	try{
				        file.exceptions ( std::ifstream::failbit | std::ifstream::badbit);

				        parseLine(line, line_Nr);
				        validLines++;

				        line_Nr++;
				    }catch(std::logic_error e){
				    	invalidLines++;
				        std::cerr << e.what() << "A logic_error occured";
					    }catch(FormatException &e)
					    {
					    	invalidLines++;
					    	writeOutFormatException(e);
					    }
			    }
	}catch(std::exception e)
	{
		std::cerr << e.what() << "Fehler in der Grossen Schleife";
	}
    

    
    // todo 3.2a: open file + read each line + call parseLine function (catch ifstream::failure)
    // todo 3.2c: read each line + call parseLine function (catch FormatException) + count valid + invalid lines
    
    std::cout << "valid lines: " << validLines << " - invalid lines: " << invalidLines << std::endl;
}

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        std::cout << "Invalid number of arguments - USAGE: exceptions [DATASET]" << std::endl;
        return -1;
    }
    
    checkData(argv[1]);

	return 0;
}
