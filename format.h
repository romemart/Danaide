#ifndef FORMAT_H
#define FORMAT_H

#include <string>
#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"

class format{
    std::string nameXML;
    std::string nameCSV;
    FILE* xmlfile;
    FILE* csvfile;
    int ctrl;
    
    void openXML();
    void openCSV();    

    void writingXML(rapidjson::Value::ConstValueIterator it);
    void writingCSV(rapidjson::Value::ConstValueIterator it);    

    void closeXML();
    void closeCSV();

    public:
    format();
    format(std::string xml,std::string csv,int ctrl);
    ~format();

    void opening();
    void procesing(rapidjson::Value::ConstValueIterator it);
    void closing();
};

#endif