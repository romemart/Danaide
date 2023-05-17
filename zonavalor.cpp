#include "zonavalor.h"

zonavalor::zonavalor():value(0.0),count(0){}

zonavalor::zonavalor(float value,int count):value(value),count(count){}

zonavalor zonavalor::operator +=(const zonavalor &obj){
    this->value = this->value + obj.value;
    this->count = this->count + obj.count;
    return *this;
}

float zonavalor::getValue(){
    return value;
}

int zonavalor::getCount(){
    return count;
}