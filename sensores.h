#ifndef SENSORES_H
#define SENSORES_H

#include <string>

class sensores{
    int index;
    std::string id;
    bool isActive;
    std::string zone;
    std::string value;
    public:
    sensores(int index, std::string id,bool isActive, std::string zone,std::string value);
    ~sensores();
    float getValuef();
    std::string getValue();
    std::string getId();
    std::string getZona();
    bool getIsActive();
};

#endif