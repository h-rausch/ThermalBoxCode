#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
#define TEMPERATURE_PRECISION 9 // Lower resolution

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

int numberOfDevices; // Number of temperature devices found

DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address

double voltageValue = 0;
double currentAmpValue = 0;
double currentValue = 0;

const int numReadings = 16;

int voltageCounts[numReadings];
int currentAmpCounts[numReadings];
int currentCounts[numReadings];
long voltageSum = 0;
long currentAmpSum = 0;
long currentSum = 0;
int voltageAverage = 0;
int currentAmpAverage = 0;
int currentAverage = 0;

int readIndex = 0;


void setup() {
  Serial.begin(9600);
  sensors.begin();
  numberOfDevices = sensors.getDeviceCount();
}

void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  if(tempC == DEVICE_DISCONNECTED_C) 
  {
    //Serial.println("Error: Could not read temperature data");
    return;
  }
  Serial.print(tempC);
}

void loop() {
  sensors.requestTemperatures();
  
  voltageSum -= voltageCounts[readIndex];
  currentAmpSum -= currentAmpCounts[readIndex];
  currentSum -= currentCounts[readIndex];
  voltageCounts[readIndex] = analogRead(A7);
  currentAmpCounts[readIndex] = analogRead(A6);
  currentCounts[readIndex] = analogRead(A5);
  voltageSum += voltageCounts[readIndex];
  currentAmpSum += currentAmpCounts[readIndex];
  currentSum += currentCounts[readIndex];
  voltageAverage = voltageSum/numReadings;
  currentAmpAverage = (currentAmpSum/numReadings)-513;
  currentAverage = (currentSum/numReadings)-513;
  voltageValue = voltageAverage * 1;
  currentAmpValue = currentAmpAverage * 1;
  currentValue = currentAverage * 1;
  
  readIndex = ((readIndex + 1) % numReadings);

  //Serial.print("V = ");
  Serial.print(voltageAverage);
  Serial.print(',');
  //Serial.print("  Iamp = ");
  Serial.print(currentAmpAverage);
  Serial.print(',');
  //Serial.print("  I = ");
  Serial.print(currentAverage);
  //Serial.print(',');

  for(int i=0;i<numberOfDevices; i++)
  {
    if(sensors.getAddress(tempDeviceAddress, i))
    {
      Serial.print(',');
      printTemperature(tempDeviceAddress); // Use a simple function to print out the data
    } 
  
  }

  Serial.print('\n');

   delay(100);
}
