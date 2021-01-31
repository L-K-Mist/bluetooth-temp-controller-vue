#include <SoftwareSerial.h>
#include "BluetoothSerial.h" // Our local Bluetooth library

#include "Heater.h"
#include "Flasher.h"
#include "TempSensor.h"
#include "MyThermistor.h"
#include "MyThermocouple.h"
#include <AsyncDelay.h>

int thermoSCK = 8;
int thermoCS = 9;
int thermoSO = 10;
MyThermocouple thermoC(thermoSCK, thermoCS, thermoSO);
TempSensor *tempSensor = &thermoC;
Flasher hotFlasher(LED_BUILTIN);
Flasher fanFlasher(12);
Heater mainHeater(tempSensor, hotFlasher, fanFlasher);

AsyncDelay delay_6s;
AsyncDelay delay_1s;

const int8_t bluetoothTxPin = 3;
const int8_t bluetoothRxPin = 4;

// onMessageReceived is a callback function.
// This is where you decide the message logic.
// Each message coming from the PWA has a maximum of three comma-separated parts.
// Note that I haven't used part 3 at all, since - for now - I only need parts one and two.
// If you don't need comma separation then you can deal only with messageParts[0] if you prefer.
void onMessageReceived(char * messageParts[3], SoftwareSerial* device){ 
  if(strcmp(messageParts[0], "Hi from web") == 0){ // In this strange world strcmp is 0 if the comparison is true.
      Serial.println("Yay web says hi!");
      device->println("Hi from arduino");
  }
  if(strcmp(messageParts[0], "echo") == 0){
      device->print("I echo back    ");
      device->println(messageParts[1]);
  }
  if(strcmp(messageParts[0], "setTemp") == 0){ 
      const double targetTemp = atof(messageParts[1]);
      device->print("Aiming for ");
      device->print(targetTemp);
      device->println("C");
      mainHeater.setTargetTemp(targetTemp);

  }
  if(strcmp(messageParts[0], "getTemp") == 0){
      Serial.println("I must fetch tempC...");
      // device->print("TempC: ");
      mainHeater.checkIsRising();
      device->print("tempC,");
      device->println(mainHeater.getTempC());
  }
  if(strcmp(messageParts[0], "getHotState") == 0){
    device->print("State: ");
    device->println(mainHeater.getHeaterState());
  }
    if(strcmp(messageParts[0], "getCoolState") == 0){
    device->print("State: ");
    device->println(mainHeater.getCoolerState());
  }
}
SoftwareSerial BluetoothDevice(bluetoothTxPin, bluetoothRxPin);
Bluetooth myBluetooth(&BluetoothDevice, onMessageReceived);

void setup() {
  delay_6s.start(6000, AsyncDelay::MILLIS);
  delay_1s.start(1000, AsyncDelay::MILLIS);
  Serial.begin(115200); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  myBluetooth.setup();
  mainHeater.setup();
  mainHeater.setMinMaxTemp(25, 100); // In this case for testing with a cup of hot water.
  mainHeater.setTargetTemp(55);
  delay(500);
}

void loop() {
  myBluetooth.loop();
  if (delay_6s.isExpired()) {
    delay_6s.repeat();
  }
  if (delay_1s.isExpired()) {
    mainHeater.loop();
    delay_1s.repeat();
  }
  delay(10);
}


