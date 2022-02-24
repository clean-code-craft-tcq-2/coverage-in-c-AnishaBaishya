#include "typewise-alert.h"
#include <stdio.h>

void (*AlertTarget_fp[NUMBEROF_ALERT_TARGETS])(BreachType)={sendToController,sendToEmail};

const char* breachAlertMessage[] = {"Hi, the temperature is Normal","Hi, the temperature is too low", "Hi, the temperature is too high"};

TempConfig setLimitsAccordingToCoolingType(double lowLimit, double highLimit)
{
	TempConfig TempLimit;
	TempLimit.lowerLimitforCoolingType = lowLimit;
	TempLimit.higherLimitforCoolingType = highLimit;
	return TempLimit;
}

TempConfig CoolingTypePassive()
{
	return setLimitsAccordingToCoolingType(PASSIVECOOLING_LOWERLIMIT,PASSIVECOOLING_UPPERLIMIT);
}

TempConfig CoolingTypeHi_Active()
{
	return setLimitsAccordingToCoolingType(HI_ACTIVECOOLING_LOWERLIMIT,HI_ACTIVECOOLING_UPPERLIMIT);
}

TempConfig CoolingTypeMed_Active()
{
	return setLimitsAccordingToCoolingType(MED_ACTIVECOOLING_LOWERLIMIT,MED_ACTIVECOOLING_UPPERLIMIT);
}

BreachType inferBreach(TempConfig TempConfigCoolingType, double TempValue) {
  BreachType returnbreachtype = NORMAL;
  if(TempValue < TempConfigCoolingType.LowerLimit) {
    returnbreachtype= TOO_LOW;
  }
  if(TempValue > TempConfigCoolingType.UpperLimit) {
    returnbreachtype = TOO_HIGH;
  }
  return returnbreachtype;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  TempConfig TempConfigCoolingType;
  TempConfigCoolingType = ClassifyCoolingType();
  return inferBreach(TempConfigCoolingType,temperatureInC);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  AlertTarget_fp[alertTarget](breachType);
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
