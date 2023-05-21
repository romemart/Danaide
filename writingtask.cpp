#include "writingtask.h"

void thrxmlFctn(int ctrl,std::string pathXML,const std::string &jsonString){
    if(ctrl!=2){ 
        std::this_thread::sleep_for(std::chrono::seconds(30));
        format fxml(pathXML,"",1);
        fxml.opening();
        rapidjson::Document document;

        document.Parse(jsonString.c_str());
        for (rapidjson::Value::ConstValueIterator it = document.Begin(); it != document.End(); ++it) {
            fxml.procesing(it);
        }

        fxml.closing();
    }
}

void thrcsvFctn(int ctrl,std::string pathCSV,const std::string &jsonString){
    if(ctrl!=1){ 
        //std::this_thread::sleep_for(std::chrono::seconds(30));
        format fxml("",pathCSV,2);
        fxml.opening();
        rapidjson::Document document;

        document.Parse(jsonString.c_str());
        for (rapidjson::Value::ConstValueIterator it = document.Begin(); it != document.End(); ++it) {
            fxml.procesing(it);
        }

        fxml.closing();
    }
}

void ConvJSONtoOhtersFormat(const std::string& jsonString,
                            unsigned int ctrl,
                            std::string pathXML,
                            std::string pathCSV)
{
    std::thread thrXML(&thrxmlFctn,ctrl,pathXML,jsonString);
    std::thread thrCSV(&thrcsvFctn,ctrl,pathCSV,jsonString);

    thrXML.join();
    thrCSV.join();
}

void ConvJSONtoOhtersFormat_ant(const std::string& jsonString,
                            unsigned int ctrl,
                            std::string pathXML,
                            std::string pathCSV,...){
    
    format files(pathXML,pathCSV,ctrl);
    files.opening();

    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    if (!document.IsArray()) {
        std::cerr << "Invalid JSON format. Expected array of objects." << std::endl;
        return;
    }

    for (rapidjson::Value::ConstValueIterator it = document.Begin(); it != document.End(); ++it) {
        if (!it->IsObject()) {
            std::cerr << "Invalid JSON format. Expected object." << std::endl;
            continue;
        }
        files.procesing(it);
    }   
    files.closing();
} 