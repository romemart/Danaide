#include "sensores.h"

sensores::sensores(int index, std::string id,bool isActive, 
                    std::string zone,std::string value):
                    index(index),id(id),isActive(isActive),zone(zone),value(value){}

sensores::~sensores(){}

float sensores::getValuef(){
        return std::stof(value);
}

std::string sensores::getValue(){
    return value;
}
std::string sensores::getId(){
    return id;
}
std::string sensores::getZona(){
    return zone;
}
bool sensores::getIsActive(){
    return isActive;
}