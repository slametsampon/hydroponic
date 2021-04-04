/*
Setting :
week = Dip-switch setting
Konsentarsi nutrisi = (week * 1023)/7 => 1023 : 10 bits, 7 : 3 bits
S0  S1  S2  Week    Konsentarsi nutrisi (simulasi)
0   0   0   0           0
1   0   0   1           146
0   1   0   2           292
1   1   0   3           438
0   0   1   4           584
1   0   1   5           730
0   1   1   6           876
1   1   1   7           1023
*/


#include    "src\digitalInput\digitalInput.h"
#include    "src\digitalOutput\DigitalOutput.h"
#include    "src\sequenceTimer\sequenceTimer.h"
#include    "dipSet.h"


#define PIN_SENSOR A0 // pin sensor conductivity

const int PIN_SET0          = 10; 
const int PIN_SET1          = 11; 
const int PIN_SET2          = 12; 

const int PIN_RELAY         = 9; 

int prevNutritionVal, prevNutritionSet;

//Variables declaration
SequenceTimer SequenceMain("Sequence");

//Variables declaration for FPSys
DigitalInput        set0(PIN_SET0);//use pin PIN_SET0 for setting
DigitalInput        set1(PIN_SET1);//use pin PIN_SET1 for setting
DigitalInput        set2(PIN_SET2);//use pin PIN_SET2 for setting
DigitalOutput       rlPump(PIN_RELAY);//relay for Dosing Pump
DigitalOutput       lifeLed(LED_BUILTIN);
//AnalogInput         conductSensor(PIN_SENSOR);

DipSet  setting(&set0, &set1, &set2);

//function declaration
void initPbLed();

void setup() {

    Serial.begin(9600);
    delay(500);

    initPbLed();
    wellcome();
}

// the loop function runs over and over again forever
void loop() {
    boolean isException = false;
    lifeLed.blink(500);//in milli second

    int nutritionVal = analogRead(PIN_SENSOR);
    int setVal = setting.getSet();

    //conversion, 1023 = 10 bits ADC, 7 = 3 bits DIP setting
    //DIP set is week number ( 0 -7)
    int nutritionSet = setVal * 1023/7;

    //Controller logic
    if (nutritionVal <= nutritionSet)rlPump.on();
    else rlPump.off();

    //get exception
    if(prevNutritionSet != nutritionSet)isException = true;
    else if(prevNutritionVal != nutritionVal)isException = true;

    //report by exception
    if(isException){
        //isException = false;
        prevNutritionSet = nutritionSet;
        prevNutritionVal = nutritionVal;

        Serial.print("Week : ");
        Serial.println(setVal);

        Serial.print("nutritionSet : ");
        Serial.println(nutritionSet);

        Serial.print("nutritionVal : ");
        Serial.println(nutritionVal);
    }

}

void initPbLed(){
    Serial.println("hyPon : initPbLed()");

    //initialization switch
    rlPump.init(FORWARD_DO);

    set0.init(REVERSE_DI);
    set1.init(REVERSE_DI);
    set2.init(REVERSE_DI);

    //initialization LEDs
    lifeLed.init("lifeLed");
}

void wellcome(){
    Serial.print("");
    Serial.println("Hydroponic System Ver.01");
    Serial.println("By Salman Alfarisi");
    Serial.print("");
}