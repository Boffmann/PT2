#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cfloat>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <ctime>

std::ofstream logfile;
// transforms a string to a date. Throws a logic_error if year is *not* between 2005 and 2015
std::tm stringToTime(std::string date)
{
#if 0
    std::tm t;
    std::istringstream ss(date);
    strptime(date.c_str(), "%d.%m.%Y", &t);
    if(t.tm_year < 105 || t.tm_year > 115)
        throw std::logic_error("Year should be between 2005 and 2015");
    return t;
#endif

    std::tm t;
#if defined(__GNUC__) && (__GNUC__ < 5)
    strptime(date.c_str(), "%d.%m.%Y", &t);
#else
    std::istringstream ss(date);
    ss >> std::get_time(&t, "%d.%m.%Y");
#endif
    
    if(t.tm_year < 105 || t.tm_year > 115)
        throw std::logic_error("Year should be between 2005 and 2015");
    
    return t;
}

struct FormatException
{
    int m_actLine;
    std::string m_actFields;
};

void inaline(std::string parsed, int count) {
    if(count == 1) {
        stringToTime(parsed);
    } else {
        float casted = std::stof(parsed);
    }
}

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
    while(std::getline(linestream, parsed, ';')) {
    	count++;
        try {
            inaline(parsed, count); // catches one more wrong date. idk why
            //if(count == 1) stringToTime(parsed);
            //else float casted = std::stof(parsed);   
        } catch (std::out_of_range e) {    
            struct FormatException exc;
            exc.m_actLine = lineNum;
            if(count == 2) exc.m_actFields = fieldNames[1];
            else if(count == 3) exc.m_actFields = fieldNames[2];
            throw exc;
        } catch(std::logic_error e) {  
            try {
                while(std::getline(linestream, parsed, ';')) {
                    count++;
                    inaline(parsed, count);  
                }
            } catch (std::out_of_range e) {    
                struct FormatException exc;
                exc.m_actLine = lineNum;
                if(count == 2) exc.m_actFields = fieldNames[0] + "," + fieldNames[1];
                else if(count == 3) exc.m_actFields = fieldNames[0] + "," + fieldNames[2];
            throw exc;
        }
            struct FormatException exc;
            exc.m_actLine = lineNum;
            exc.m_actFields = fieldNames[0];
            throw exc;  
        }
    }
}

// todo 3.2c..
void writeOutFormatException(const FormatException & e)
{
	try {
        int line = e.m_actLine;
        std::string line_content = e.m_actFields;
        logfile << "line: " << line << ";invalid data field(s): " << line_content << std::endl;
    } catch (std::ios_base::failure e) {
        std::cerr << e.what();
    }
    
    // todo 3.2d: export information (i.e., line number + invalid data fields) about exception to a logfile.
    // todo 3.2d: catch ios_base::failure
}

void checkData(std::string path) {

    int validLines = 0;
    int invalidLines = 0;
    int line_Nr = 1;
    std::ifstream file;
    std::string line, parsed;
    logfile.open("exceptions.log");
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(path);

        while (std::getline(file, line)){
            try {
                
                // skip first line which names the columns
                if(line_Nr > 1) {
                    parseLine(line, line_Nr);
                    validLines++;
                }

            } catch(FormatException &e) {
                invalidLines++;
                writeOutFormatException(e);
            }
            line_Nr++;
        }
        file.close();
    } catch (std::ifstream::failure e) {
        std::cerr << "Fehler beim oeffnen, lesen oder schliessen der Datei (" << e.what() << ")" << std::endl;
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
