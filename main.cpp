#include <iostream>
#include "jsontask.h"
#include "writingtask.h"
#include "sensores.h"
#include "zonavalor.h"


int main(int argc, char const *argv[])
{
    std::vector<sensores>sen;
    std::map<std::string,zonavalor> zv;
    std::map<std::string,int> zc;

    std::string filename = "sensores.json";

    std::string jsonString = ReadJSONFile(filename);

    if (!jsonString.empty()) {
        ParseJSONArray(jsonString,sen);
        std::cout << "Opening the input JSON file successfully.\n";
        WriteJSONfile("fileJSON.json",zv,zc,sen);
        std::cout << "The file \"fileJSON.json\" was created successfully.\n";
    }
    else{   
        std::cout << "The input JSON file is empty or does not exist.\n";
        return -1;
    }
    std::cout<<"\n\n";
    std::cout << "To change the format to JSON input file type:\n";
    std::cout << "1 - To output in XML format\n";
    std::cout << "2 - To output in CSV format\n";
    std::cout << "ANY To output both of them formats\n";
    std::cout << "\nType: ";
   
    unsigned int number;
    std::cin >> number;
    
    std::string pathXML;
    std::string pathCSV;

    std::cout << "\n";

    if(number !=2 ){
        std::cout << "Choose the path for the file \"fileXML.xml\"\n";
        std::cout << "Example: ./folderxml/ or ./ or ../\n";
        std::cout << "\nType: ";
        std::cin >> pathXML;
        pathXML+="fileXML.xml";
        std::cout << "Find the file in:" << pathXML << "\n\n";
    }

    if(number !=1 ){
        std::cout << "Choose the path for the file \"fileCSV.csv\"\n";
        std::cout << "Example: ./foldercsv/ or ./ or ../\n";
        std::cout << "\nType: ";
        std::cin >> pathCSV;
        pathCSV+="fileCSV.csv";
        std::cout << "Find the file in:" << pathCSV << "\n\n";
    }

    ConvJSONtoOhtersFormat(filename,number,pathXML,pathCSV);
    return 0;
}