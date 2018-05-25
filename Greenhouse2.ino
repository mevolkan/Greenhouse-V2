// best means to temporarily store and transmit data over serial
// Eprom can store it
// automatic mode

#include "DHT.h"



//set pins for sensors
const int TempSensor= A0; //assign pin A0 to LM35 
const int MoistureSensor=A3;
const int LightSensor = A2;//assign analogue pin2 to Photoresistor
#define DHTPIN 2     // DT22 connected to digital pin 2

//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

//set pins for actuators
const int pump= 1;
const int lamp= 2;
const int Humidity_Fan= 3;
const int Temp_Fan= 4;
const int vanes= 5;


//set points variables
float SetTemp;
float SetLight;
float SetMoisture;
float SetHumidity;

//sensor values
float DryTempC;
float DryTempF;
float RelTempC;//centigrade
float RelTempF;//Farenheit
float HeatIC; // heat index Centigrade
float HeatIF; //heat index Farenheit
float Light;
float Moisture;
float Humidity;


//raw voltages
float TempVoltageIn;
float LightVoltageIn;
float DHTVoltageIn;
float MoistureVoltageIn;

//lights
#define StateLight 22 // set digital pin 22 to System Status light
int SystemState=0;
//arrays for data storage



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  dht.begin();

//  //prompt user for set points
//  Serial.println("Enter Temperature set point");
//  while (Serial.available()==0){} //check if user has input values
//    SetTemp=Serial.parseFloat(); // read user input and assign to value
//
//  Serial.println("Enter Light set point");
//  while (Serial.available()==0){}
//    SetLight=Serial.parseFloat();
//
//  Serial.println("Enter Light set point");
//  while (Serial.available()==0){}
//    SetLight=Serial.parseFloat();
//  
//  Serial.println("Enter Moisture set point");
//  while (Serial.available()==0){}
//    SetMoisture=Serial.parseFloat();
//
//  Serial.println("Enter Humidity set point");
//  while (Serial.available()==0){}
//    SetHumidity=Serial.parseFloat();

    //If user does not input data, run with recent values

    //set last input values to current set points
  
  Serial.println("The set points are");

//Check for current device states and print them to serial



//set status light to on
digitalWrite(StateLight,HIGH);

//store readings to array

//compute values from readings

//store values to array

}

void loop(){
  //call the environment functions
  void TempRead();
  void MoistureRead();
void LightRead();
  void SendDataPayload();
  delay(2000 );

  Serial.println("The set points are");
//Print values to serial

  Serial.println("The voltages are");
  Serial.println("The readings are"); 
  
}

//read value from sensors

//pick value from LM35 then compute
void TempRead(){
  pinMode(TempSensor,INPUT);
  TempVoltageIn= analogRead(TempSensor);
  DryTempC=(TempVoltageIn/1024.0)*5000;
  DryTempF=(TempVoltageIn*9)/5+32;

}

void MoistureRead(){
 float MoistureVoltageIn = analogRead(MoistureSensor) ;
 Moisture= constrain(Moisture, 485, 1023);
 Moisture= map(Moisture, 485, 1023, 10, 0);

}

void HumidityRead(){
  delay(2000);
  float DHTVoltageIn= digitalRead(DHTPIN);
  float Humidity=dht.readHumidity();
  float RelTempC=dht.readTemperature();
  float RelTempF=dht.readTemperature(true);
  
// Check if any reads failed and exit early (to try again).
  if (isnan(Humidity) || isnan(RelTempC) || isnan(RelTempF)){
    Serial.println("Failed to read from DHT Sensor");
    return;
  }
  // Compute heat index in Fahrenheit (the default)
  float HeatIF = dht.computeHeatIndex(RelTempF, Humidity);
// Compute heat index in Celsius (isFahreheit = false)
  float HeatIC= dht.computeHeatIndex(RelTempC, Humidity, false);

}

void LightRead(){
   LightVoltageIn = analogRead(LightSensor);
  float Light = LightVoltageIn;

}

//print computed data to serial
//
void PrintData(){
  Serial.print("Temperature in C");Serial.println(DryTempC);// temp from LM35
  Serial.print("Temperature in F");Serial.println(DryTempF);
  Serial.print("Humidity");Serial.println(Humidity);
  Serial.print("Relative Temperature In C");Serial.println(RelTempC);//temp from DHT22
  Serial.print("Relative Temperature In F");Serial.println(RelTempF);
  Serial.print("Relative Heat Index in C");Serial.println(HeatIC);//from DHT22
  Serial.print("Relative Heat Index in F");Serial.println(HeatIF);
  Serial.print("Light");Serial.println(Light);

}

//print sensor voltage data to serial
//
void PrintVoltage(){
  Serial.print("DHT22");Serial.println();// temp from LM35
  Serial.print("LM35");Serial.println(TempVoltageIn);
  Serial.print("Photoresistor");Serial.println(LightVoltageIn);
  
}
//check states of the actuators then print states and switch on indicators
void CheckIndicators(){
SystemState = digitalRead(SystemState);
Serial.print("System state"); Serial.println(SystemState);

 }
void SendDataPayload(){
int  NData=9;
String PayLoad;
PayLoad =String();
PayLoad= NData+' '+DryTempC+' '+DryTempF+' '+RelTempC+' '+RelTempF+' '+HeatIC+' '+HeatIF+' '+Light+' '+Humidity+' '+Moisture+'/n';
Serial.println(PayLoad);
}
