#include "typewise-alert.h"
#include <stdio.h>

const struct TempConfig TemperatureConfiguration[NUMBEROF_COOLING_TYPES]={
  {PASSIVECOOLING_LOWERLIMIT,PASSIVECOOLING_UPPERLIMIT},
  {HI_ACTIVECOOLING_LOWERLIMIT,HI_ACTIVECOOLING_UPPERLIMIT},
  {MED_ACTIVECOOLING_LOWERLIMIT,MED_ACTIVECOOLING_UPPERLIMIT}
};

BreachType inferBreach(CoolingType TypeOfCooling, double TempValue) {
  BreachType returnbreachtype = NORMAL;
  if(TempValue < TemperatureConfiguration[TypeOfCooling].LowerLimit) {
    returnbreachtype= TOO_LOW;
  }
  if(TempValue > TemperatureConfiguration[TypeOfCooling].UpperLimit) {
    returnbreachtype = TOO_HIGH;
  }
  return returnbreachtype;
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = inferBreach(
    batteryChar.coolingType, temperatureInC
  );
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
}
