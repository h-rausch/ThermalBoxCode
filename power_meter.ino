double voltageValue = 0;
double currentAmpValue = 0;
double currentValue = 0;
bool currentPos = true;

const int numReadings = 16;

int voltageCounts[numReadings];
int currentCounts[numReadings];
long voltageAverage = 0;
long currentAverage = 0;
int readIndex = 0;
int Vtotal = 0;
int Itotal = 0;
//int average = 0;


void setup() {
  Serial.begin(9600);
}

void loop() {

  if(readIndex < numReadings)
  {
    voltageCounts[readIndex] = analogRead(A7);
    currentCounts[readIndex] = analogRead(A6);
    readIndex++;
  }
  else
  {
    readIndex = 0;
    voltageAverage = 0;
    currentAverage = 0;
    for (int i = 0 ; i < numReadings ; i++)
    {
      voltageAverage += voltageCounts[i];
      currentAverage += currentCounts[i];
    }
    voltageAverage = voltageAverage/numReadings;
    currentAverage =  currentAverage/numReadings;
    voltageValue = ((voltageAverage + 1.6)/11.428);
    if (currentAverage > 513)
    {
      currentPos = false;
      currentValue = (((currentAverage - 513) * 20)/513);
    }
    else
    {
      currentPos = true;
      currentValue = ((513 - currentAverage ) *20);
      currentValue = currentValue/513;
    }
    Serial.print("V = ");
    Serial.print(voltageAverage);
    Serial.print("  I = ");
    //if (!currentPos){Serial.print("-");}
    Serial.println(currentAverage);

  }

  delay(10);
}
