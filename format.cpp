#include "format.h"

void format::openXML(){
    xmlfile = fopen(nameXML.c_str(),"w");
    fprintf(xmlfile,"%s","<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(xmlfile,"%s","<root>\n");
}
void format::openCSV(){
    csvfile = fopen(nameCSV.c_str(),"w");
    fprintf(csvfile,"%s\n","index,id,isActive,zone,value");
}    

void format::writingXML(rapidjson::Value::ConstValueIterator it){
    fprintf(xmlfile,"%s","\t<element>\n");
    fprintf(xmlfile,"\t\t<index>%d</index>\n",(*it)["index"].GetInt());
    fprintf(xmlfile,"\t\t<id>%s</id>\n",(*it)["id"].GetString());
    fprintf(xmlfile,"\t\t<isActive>%s</isActive>\n",((*it)["isActive"].GetBool() ? "true" : "false"));
    fprintf(xmlfile,"\t\t<value>%s</value>\n",(*it)["value"].GetString());
    fprintf(xmlfile,"\t\t<zone>%s</zone>\n",(*it)["zone"].GetString());
    fprintf(xmlfile,"%s","\t</element>\n");
}
void format::writingCSV(rapidjson::Value::ConstValueIterator it){
    fprintf(csvfile,"%d,%s,%s,%s,%s\n",
        (*it)["index"].GetInt(),
        (*it)["id"].GetString(),
        ((*it)["isActive"].GetBool() ? "true" : "false"),
        (*it)["zone"].GetString(),
        (*it)["value"].GetString()
    );
}    

void format::closeXML(){
    fprintf(xmlfile,"%s","</root>");
    fclose(xmlfile); 
}
void format::closeCSV(){
    fclose(csvfile); 
} 

format::format(){}
format::format(std::string xml,std::string csv,int ctrl):nameXML(xml),nameCSV(csv),ctrl(ctrl){}
format::~format(){}

void format::opening(){
    switch (ctrl)
    {
        case 1: openXML(); break;
        case 2: openCSV(); break;
        default:
            openXML();
            openCSV();
        break;
    }  
}
void format::procesing(rapidjson::Value::ConstValueIterator it){
    switch (ctrl)
    {
        case 1: writingXML(it); break;
        case 2: writingCSV(it); break;
        default:
            writingXML(it);
            writingCSV(it);
        break;
    }        
}
void format::closing(){
    switch (ctrl)
    {
        case 1: closeXML(); break;
        case 2: closeCSV(); break;
        default:
            closeXML();
            closeCSV();
        break;
    }   
}