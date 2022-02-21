#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(PASSIVE_COOLING, -20)== TOO_LOW);
  REQUIRE(inferBreach(PASSIVE_COOLING, 45)== TOO_HIGH);
  REQUIRE(inferBreach(HI_ACTIVE_COOLING, -20)== TOO_LOW);
  REQUIRE(inferBreach(HI_ACTIVE_COOLING, 50)== TOO_HIGH);
  REQUIRE(inferBreach(MED_ACTIVE_COOLING, -20)== TOO_LOW);
  REQUIRE(inferBreach(MED_ACTIVE_COOLING, 45)== TOO_HIGH);
}

TEST_CASE("checks the main function") {
  AlertTarget alertTarget = TO_CONTROLLER;
  CoolingType coolingtype = MED_ACTIVE_COOLING;
  BatteryCharacter batteryChar = {coolingtype, "BrandX"};
  REQUIRE(checkAndAlert(alertTarget, batteryChar, 45) == TOO_HIGH);
}
