#pragma once

#define PASSIVECOOLING_LOWERLIMIT     0
#define PASSIVECOOLING_UPPERLIMIT     35
#define HI_ACTIVECOOLING_LOWERLIMIT   0
#define HI_ACTIVECOOLING_UPPERLIMIT   45
#define MED_ACTIVECOOLING_LOWERLIMIT  0
#define MED_ACTIVECOOLING_UPPERLIMIT  40

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(TempConfig TempConfigCoolingType, double TempValue);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL,
  NUMBEROF_ALERT_TARGETS
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

typedef struct{
  int LowerLimit;
  int UpperLimit;
}TempConfig;

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);

typedef TempConfig (*ClassifyCoolingType)();

TempConfig PASSIVE_COOLING();
TempConfig HI_ACTIVE_COOLING();
TempConfig MED_ACTIVE_COOLING();
