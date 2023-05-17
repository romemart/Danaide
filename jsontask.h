#ifndef JSONTASK_H
#define JSONTASK_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include "sensores.h"
#include "zonavalor.h"
#include "format.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

std::string ReadJSONFile(const std::string& filename);
void ParseJSONArray(const std::string& jsonString,std::vector<sensores>&sen);
void ConvJSONtoOhtersFormat(const std::string& jsonString,
                            unsigned int ctrl,
                            std::string pathXML,
                            std::string pathCSV);
std::string getIdMayorValor(std::vector<sensores>sen);
float getValorMedio(std::vector<sensores>sen);
void CreaValorMedioZona(std::map< std::string, zonavalor > &zv, std::vector<sensores>sen);
void CreaCantSenActZona(std::map<std::string,int> &zc, std::vector<sensores>sen);
void WriteJSONfile( const std::string& filename,
                    std::map<std::string,zonavalor> &zv,
                    std::map<std::string,int> &zc,
                    std::vector<sensores>sen
 );

#endif