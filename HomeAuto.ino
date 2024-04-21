// version 4.3.1
#include <IRremote.hpp>
#include "Common.h"
#include "Buttons.h"

#define IR_RECEIVE_PIN 11

#if(BLUE_EN == 1)
// RX in arduino 2
// TX on arduino 3
#define BT_RX 2
#define BT_TX 3
#include<SoftwareSerial.h>
SoftwareSerial Bluetooth(BT_RX, BT_TX); // RX,TXd
#endif

#if(HILTEST == 1)
#define GNDPIN 7
#define VCCPIN 6
#undef IR_RECEIVE_PIN
#define IR_RECEIVE_PIN 5
#endif

uint16_t States;
uint16_t LastStates;

String readString;
IRRawDataType Last;
IRRawDataType Current;

uint8_t IR_Key,BT_Key;
uint8_t BT_DataLen;
Operation BT_Cmd,IR_Cmd;

Command IR_Command;
#if(BLUE_EN ==1)
Command BT_Command;
#endif

// DEFINED FUNCTIONS


void setup() {
  Serial.begin(9600);
  States=0;
  LastStates=0;
  
  #if (BLUE_EN == 1)
  Bluetooth.begin(9600);
  BT_Command={NO_BTKEY,OP_N};
  #endif
  IR_Command={NO_IRKEY,OP_N};

  IrReceiver.begin(IR_RECEIVE_PIN);

  #if(HILTEST == 1)
  pinMode(GNDPIN,OUTPUT);
  digitalWrite(GNDPIN,LOW);
  pinMode(VCCPIN,OUTPUT);
  digitalWrite(VCCPIN,HIGH);
  pinMode(IR_RECEIVE_PIN,INPUT);
  #endif

  // Set Relays to OUTPUT Mode
  for(uint8_t RelayNumber=0;RelayNumber<NUM_OUTPUTS;RelayNumber++)
  {
    if(RELAYS[RelayNumber]!=NORELAY)
    {
      pinMode(RELAYS[RelayNumber],OUTPUT);
    }
  }
}

void loop() {
  delay(200);
  
  // Bluetooth has lowerpriority
  #if(BLUE_EN==1)
  BluetoothData();
  BluetoothControl();
  #endif

  Remote();
  RemoteControl();

  ValidateAndControl();
  
  if(LastStates!=States)
  {
    PrintState();
    LastStates=States;
    SetRelays();
  }
  
}
