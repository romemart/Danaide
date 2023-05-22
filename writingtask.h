#ifndef WRITING_H
#define WRITING_H

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>

//std::mutex fileMutex;

void jsonTOxml(std::string pathXML,const std::string filename);
void jsonTOcsv(std::string pathCSV,const std::string filename);

void thrxmlFctn(int ctrl,std::string pathXML,const std::string filename);
void thrcsvFctn(int ctrl,std::string pathCSV,const std::string filename);

void ConvJSONtoOhtersFormat(const std::string& jsonString,
                            unsigned int ctrl,
                            std::string pathXML,
                            std::string pathCSV);


#endif