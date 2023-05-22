#include "writingtask.h"

void thrxmlFctn(int ctrl,std::string pathXML,const std::string filename){
    if(ctrl!=2){ 
        //std::this_thread::sleep_for(std::chrono::seconds(30));
        //std::lock_guard<std::mutex> lock(fileMutex);
        jsonTOxml(pathXML,filename);
    }
}

void thrcsvFctn(int ctrl,std::string pathCSV,const std::string filename){
    if(ctrl!=1){ 
        //std::this_thread::sleep_for(std::chrono::seconds(30));
        //std::lock_guard<std::mutex> lock(fileMutex);
        jsonTOcsv(pathCSV,filename);
    }
}

void ConvJSONtoOhtersFormat(const std::string &filename,
                            unsigned int ctrl,
                            std::string pathXML,
                            std::string pathCSV)
{
    std::thread thrXML(&thrxmlFctn,ctrl,pathXML,filename);
    std::thread thrCSV(&thrcsvFctn,ctrl,pathCSV,filename);

    thrXML.join();
    thrCSV.join();
}

void jsonTOxml(std::string pathXML,const std::string filename){

    FILE* jsonfile = fopen(filename.c_str(),"r");
    FILE* xmlfile = fopen(pathXML.c_str(),"w");

    char readline[1024];
    char delimiter[1024]="\0";
    char id[1024]="\0";
    char zone[1024]="\0";
    char active[1024]="\0";
    char value[1024]="\0";
    int index=999;

    fprintf(xmlfile,"%s","<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    
    while (true) {
        if(fgets(readline, 1024, jsonfile) == NULL) break;

        if( sscanf(readline,"%s",delimiter)==1){
        if( strcmp(delimiter,"[")==0) 
            fprintf(xmlfile,"%s","<root>\n");
        if( strcmp(delimiter,"]")==0) 
            fprintf(xmlfile,"%s","</root>");
        if( strcmp(delimiter,"{")==0 || strcmp(delimiter,",{")==0)
            fprintf(xmlfile,"%s","\t<element>\n");
        if( strcmp(delimiter,"}")==0 || strcmp(delimiter,"},")==0)
            fprintf(xmlfile,"%s","\t</element>\n");
        }

        if(sscanf(readline," \"index\": %d",&index)==1)
            fprintf(xmlfile,"\t\t<index>%d</index>\n",index);

        if(sscanf(readline," \"id\": \"%[^\",\"]",id)==1)
            fprintf(xmlfile,"\t\t<id>%s</id>\n",id);

        if(sscanf(readline," \"zone\": \"%[^\",\"]",zone)==1)
            fprintf(xmlfile,"\t\t<zone>%s</zone>\n",zone);
        
        if(sscanf(readline," \"value\": \"%[^\",\"]",value)==1)
            fprintf(xmlfile,"\t\t<value>%s</value>\n",value);
        
        if(sscanf(readline," \"isActive\": %[^,\"]",active)==1)
            fprintf(xmlfile,"\t\t<isActive>%s</isActive>\n",active);

    }
    fclose(xmlfile);
    fclose(jsonfile);
}

void jsonTOcsv(std::string pathCSV,const std::string filename){

    FILE* jsonfile = fopen(filename.c_str(),"r");
    FILE* csvfile = fopen(pathCSV.c_str(),"w");
    
    char readline[1024];
    char delimiter[1024]="\0";
    char id[1024]="\0";
    char zone[1024]="\0";
    char active[1024]="\0";
    char value[1024]="\0";
    int index=999;

    fprintf(csvfile,"%s","index,id,isActive,zone,value");

    while (true) {
        if(fgets(readline, 1024, jsonfile) == NULL) break;

        sscanf(readline," \"index\": %d",&index);
        sscanf(readline," \"id\": \"%[^\",\"]",id);
        sscanf(readline," \"zone\": \"%[^\",\"]",zone);
        sscanf(readline," \"value\": \"%[^\",\"]",value);
        sscanf(readline," \"isActive\": %[^,\"]",active);
        
        if( sscanf(readline,"%s",delimiter)==1){
            if( strcmp(delimiter,"},")==0 || strcmp(delimiter,"}")==0)
                fprintf(csvfile,"\n%d,%s,%s,%s,%s",
                        index, id, active, zone, value);
        }
    }
    fclose(csvfile);
    fclose(jsonfile);
}