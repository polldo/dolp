#include "ArduinoBLE.h"
#include "Multiplayer.h"
#include "dolp.h"

BLEService syncService("19B10000-E8F2-537E-4F6C-D104768A1214"); 
BLECharacteristic hostCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify, 1);
BLECharacteristic clientCharacteristic("19B10002-E8F2-537E-4F6C-D104768A1214", BLEWrite, 1);

bool sync = false;
uint8_t clientState;

void syncReceived(BLEDevice client, BLECharacteristic characteristic)
{
  characteristic.readValue(&clientState, 1);
  sync = true;
}

void hostBegin() 
{
  //BLE.debug(Serial);
  BLE.begin();
  BLE.setLocalName("PongHost");
  syncService.addCharacteristic(hostCharacteristic);
  syncService.addCharacteristic(clientCharacteristic);
  BLE.addService(syncService);

  clientCharacteristic.setEventHandler(BLEWritten, syncReceived);

  BLE.advertise();

  while (!BLE.connected()) {
    BLE.poll();
  }
}

uint8_t hostSync()
//uint8_t hostSync(uint8_t* hostState, uint8_t length, uint8_t* clientState)
{
  BLE.poll();
  while (!sync) {
    BLE.poll();
  }
  sync = false;
  uint8_t value = joystick.held(ButtonA);
  hostCharacteristic.writeValue(&value, 1);
  return clientState;
}
