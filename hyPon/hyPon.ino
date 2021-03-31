#include    "src\digitalInput\digitalInput.h"
#include    "src\digitalOutput\DigitalOutput.h"
#include    "dipSet.h"


#define PIN_SENSOR A0 // pin sensor conductivity

const int PIN_SET0          = 10; 
const int PIN_SET1          = 11; 
const int PIN_SET2          = 12; 

const int PIN_RELAY         = 9; 

//Variables declaration

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

    String str;
    str = String("lifeLed \n");//with new line
    str = String(str + lifeLed.info());
    Serial.println(str);
    
}

// the loop function runs over and over again forever
void loop() {
    lifeLed.blink(500);//in milli second

    int nutritionVal = analogRead(PIN_SENSOR);
    int setVal = setting.getSet();

    if (nutritionVal <= setVal)rlPump.on();

    //if (set1.isStatus())rlPump.on();
    else rlPump.off();

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
