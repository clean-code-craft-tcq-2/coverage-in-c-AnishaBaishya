#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(PASSIVE_COOLING, -20)== TOO_LOW);
  REQUIRE(inferBreach(PASSIVE_COOLING, 45)== TOO_HIGH);
  REQUIRE(inferBreach(PASSIVE_COOLING, 30)== NORMAL);
  REQUIRE(inferBreach(HI_ACTIVE_COOLING, -20)== TOO_LOW);
  REQUIRE(inferBreach(HI_ACTIVE_COOLING, 50)== TOO_HIGH);
  REQUIRE(inferBreach(HI_ACTIVE_COOLING, 30)== NORMAL);
  REQUIRE(inferBreach(MED_ACTIVE_COOLING, -20)== TOO_LOW);
  REQUIRE(inferBreach(MED_ACTIVE_COOLING, 45)== TOO_HIGH);
  REQUIRE(inferBreach(MED_ACTIVE_COOLING, 30)== NORMAL);
}

TEST_CASE("checks the main function Alert Target CONTROLLER") {
  AlertTarget alertTarget = TO_CONTROLLER;
  CoolingType coolingtype = MED_ACTIVE_COOLING;
  BatteryCharacter batteryChar = {coolingtype, "BrandX"};
  checkAndAlert(alertTarget, batteryChar, 45);
  checkAndAlert(alertTarget, batteryChar, 30);
  checkAndAlert(alertTarget, batteryChar, -5);
}

TEST_CASE("checks the main function Alert Target EMAIL") {
  AlertTarget alertTarget = TO_EMAIL;
  CoolingType coolingtype = HI_ACTIVE_COOLING;
  BatteryCharacter batteryChar = {coolingtype, "BrandX"};
  checkAndAlert(alertTarget, batteryChar, -10);
  checkAndAlert(alertTarget, batteryChar, 30);
  checkAndAlert(alertTarget, batteryChar, 55);
}

TEST_CASE("checks the function sendToController") {
  sendToController(TOO_HIGH);
  sendToController(TOO_LOW);
  sendToController(NORMAL);
}

TEST_CASE("checks the function sendToEmail") {
  sendToEmail(TOO_HIGH);
  sendToEmail(TOO_LOW);
  sendToEmail(NORMAL);
}
