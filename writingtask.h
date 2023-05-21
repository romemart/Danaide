#ifndef WRITING_H
#define WRITING_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "format.h"
#include "rapidjson/document.h"

void thrxmlFctn(int ctrl,std::string pathXML,const std::string &jsonString);
void thrcsvFctn(int ctrl,std::string pathCSV,const std::string &jsonString);

void ConvJSONtoOhtersFormat(const std::string& jsonString,
                            unsigned int ctrl,
                            std::string pathXML,
                            std::string pathCSV);

void ConvJSONtoOhtersFormat_ant(const std::string& jsonString,
                            unsigned int ctrl,
                            std::string pathXML,
                            std::string pathCSV,...);

#endif