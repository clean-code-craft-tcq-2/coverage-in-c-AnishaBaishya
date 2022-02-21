#include "typewise-alert.h"
#include <stdio.h>

TempConfig TemperatureConfiguration[NUMBEROF_COOLING_TYPES]={
  {PASSIVECOOLING_LOWERLIMIT,PASSIVECOOLING_UPPERLIMIT},
  {HI_ACTIVECOOLING_LOWERLIMIT,HI_ACTIVECOOLING_UPPERLIMIT},
  {MED_ACTIVECOOLING_LOWERLIMIT,MED_ACTIVECOOLING_UPPERLIMIT}
};

void (*AlertTarget_fp[NUMBEROF_ALERT_TARGETS])(BreachType)={sendToController,sendToEmail};

const char* breachAlertMessage[] = {"Hi, the temperature is Normal","Hi, the temperature is too low", "Hi, the temperature is too high"};

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

BreachType  checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = inferBreach(
    batteryChar.coolingType, temperatureInC
  );
  AlertTarget_fp[alertTarget](breachType);
  return breachType;
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  printf("To: %s\n", recepient);
  printf("%s\n",breachAlertMessage[breachType]);
}
