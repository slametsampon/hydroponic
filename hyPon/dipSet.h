/*
  dipSet.h - Library for Setessing
  Setes  :
    0. 000
    1. 001
    .....
    7. 111
  By : Sam March 18, 2021
*/

#ifndef dipSet_h
#define dipSet_h

#include "Arduino.h"
#include "src\digitalInput\digitalInput.h"

    class DipSet{
        public:
            DipSet(DigitalInput*, DigitalInput*, DigitalInput*);
            int getSet();
            void info();
        private:
            DigitalInput *_set0, *_set1, *_set2;
    };

#endif
