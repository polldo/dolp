#include "ArduinoBLE.h"
#include "Multiplayer.h"
#include "dolp.h"

BLECharacteristic hostCharacteristic;
BLECharacteristic clientCharacteristic;

auto hostUuid = "19B10001-E8F2-537E-4F6C-D104768A1214";
auto clientUuid = "19B10002-E8F2-537E-4F6C-D104768A1214";

bool clientConnect(BLEDevice peripheral)
{
  if (!peripheral.connect()) {
    return false;
  }
  if (!peripheral.discoverAttributes()) {
    peripheral.disconnect();
    return false;
  }

  hostCharacteristic = peripheral.characteristic("19B10001-E8F2-537E-4F6C-D104768A1214");
  clientCharacteristic = peripheral.characteristic("19B10002-E8F2-537E-4F6C-D104768A1214");
  if (!hostCharacteristic || !clientCharacteristic) {
    peripheral.disconnect();
    return false;
  }

  if (!hostCharacteristic.subscribe()) {
    peripheral.disconnect();
    return false;
  }

  return true;
}

void clientBegin() 
{
  BLE.begin();
  BLE.scanForName("PongHost");
  while (!BLE.connected()) {
    auto dev = BLE.available();
    if (dev) {
      BLE.stopScan();
      if (!clientConnect(dev)) {
        BLE.scanForName("PongHost");
      }
    }
  }
}

uint8_t clientSync()
{
  BLE.poll();
  uint8_t value = joystick.held(ButtonA);
  clientCharacteristic.writeValue(&value, 1);
  while (!hostCharacteristic.valueUpdated()) ;
  uint8_t hostState;
  hostCharacteristic.readValue(&hostState, 1);
  return  hostState;
}
