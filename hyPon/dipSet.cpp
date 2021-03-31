/*
  dipSet.h - Library for Setting
  Setes  :
    0. 000
    1. 001
    .....
    7. 111
  By : Sam March 18, 2021
*/

/* Dependencies */
#include "dipSet.h"

DipSet::DipSet(DigitalInput *set0, DigitalInput *set1, DigitalInput *set2): _set0(set0), _set1(set1), _set2(set2){}

int DipSet::getSet(){
    int set0, set1, set2;
    if (_set0->isStatus()) set0 = 1;
    if (_set1->isStatus()) set1 = 2;
    if (_set2->isStatus()) set2 = 4;

    //1023 is ADC 10 bits
    return ((set0 + set1 + set2)*1023/8);
}

void DipSet::info(){
    Serial.println("DipSet::info()");
    String str;
    str = String("_set0 \n");//with new line
    str = String(str + _set0->info());
    Serial.println(str);

    str = String("_set1 \n");//with new line
    str = String(str + _set1->info());
    Serial.println(str);
    
    str = String("_set2 \n");//with new line
    str = String(str + _set2->info());
    Serial.println(str);
    
    Serial.print("Setess : ");
    Serial.println(this->getSet());
}
