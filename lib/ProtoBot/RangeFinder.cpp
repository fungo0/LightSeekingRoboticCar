#include "RangeFinder.h"

void RangeFinder::init(int tp, int ep)
{
  transmitPin = tp;
  echoPin = ep;
  pinMode(tp,OUTPUT);       // set TP output pin for trigger
  pinMode(ep,INPUT);        // set EP input pin for echo
}


long RangeFinder::getDistance()
{
  long pingSamples[PING_SAMPLES];
  long microseconds;

  for (int x = 0; x < PING_SAMPLES; x++)
  {
    pingSamples[x] = ping();
  }
  microseconds = filterRange(pingSamples);

#if __RANGEFINDER_H__DEBUG
  Serial.print("Filtered microseconds = ");
  Serial.println(microseconds);
#endif

  long distance_cm = calcDistance(microseconds, 1); // Calculating the distance

#if __RANGEFINDER_H__DEBUG
  Serial.print("distance CM = ");
  Serial.println(distance_cm);   // printf the distance about CM
#endif

  return distance_cm;
}

long RangeFinder::calcDistance(long time, int flag)
{
  long distance;
  if(flag)
    distance = time /29 / 2  ;     // Distance_CM  = ((Duration of high level)*(Sonic :340m/s))/2
                                   //              = ((Duration of high level)*(Sonic :0.034 cm/us))/2
                                   //              = ((Duration of high level)/(Sonic :29.4 cm/us))/2
  else
    distance = time / 74 / 2;      // INC
  return distance;
}

long RangeFinder::ping()
{
  // Serial.print("What?");
  digitalWrite(transmitPin, LOW);
  delayMicroseconds(2);
  digitalWrite(transmitPin, HIGH);               // pull the Trig pin to high level for more than 10us impulse
  delayMicroseconds(10);
  digitalWrite(transmitPin, LOW);
  long microseconds = pulseIn(echoPin,HIGH,PING_TIMEOUT);    // waits for the pin to go HIGH, and returns the length of the pulse in microseconds
  #if __RANGEFINDER_H__DEBUG
    Serial.print("RAW microseconds = ");
    Serial.println(microseconds);
  #endif

  return microseconds;                          // return microseconds
}

long RangeFinder::filterRange(long samples[])
{
  int numSamplesToAverage = PING_SAMPLES - 2;
  int highIndex, lowIndex;
  long samplesToAverage[numSamplesToAverage];
  long total;

  //find highest sample index
  highIndex = 0;
  for (int x = 0; x < PING_SAMPLES; x++)
  {
    if (samples[x] > samples[highIndex])
      highIndex = x;
  }

  //find lowest sample index
  lowIndex = 0;
  for (int x = 0; x < PING_SAMPLES; x++)
  {
    if (samples[x] < samples[lowIndex])
      lowIndex = x;
  }

  //Average results
  total = 0;
  for (int x = 0; x < PING_SAMPLES; x++)
  {
    if (x != highIndex && x != lowIndex)
    {
      total += samples[x];
    }
  }

  return total / numSamplesToAverage;
}

RangeFinder rangeFinder;
