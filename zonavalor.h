#ifndef ZONAVALOR_H
#define ZONAVALOR_H

class zonavalor{
    float value;
    int count;
    public:
    zonavalor();
    zonavalor(float value,int count);
    zonavalor operator +=(const zonavalor &obj);
    float getValue();
    int getCount();
};

#endif