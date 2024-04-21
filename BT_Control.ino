#if(BLUE_EN == 1)
void BluetoothData()
{
  
  while (Bluetooth.available()) {
    delay(10);

    char c = Bluetooth.read();
    if (c == ';' || c=='\n') {
      // find line breaks
      Bluetooth.flush();
      break;
    } 
    readString += c;
  } 

  // all commands should be 2 character in length
  // eg H1 L1 T1
  // or this is a complex command
  BT_DataLen = readString.length();
  //Simple Command
  if (BT_DataLen == 2) {
    Serial.print("BT > ");
    Serial.println(readString);
  }
  // Complex Command
  else if(BT_DataLen > 0)
  {
    Serial.print("BT Complex > ");
    Serial.println(readString);
  }

}
void BluetoothControl()
{
  BT_Key=(uint8_t)readString[1]-'0';
  char tmpBT_Cmd=readString[0];

  // Validation
  if(BT_Key>9)
  {
    // only have 10 keys from 0-9
    BT_Key=NO_BTKEY;
  }

  BT_Command.Key=BT_Key;
  switch (tmpBT_Cmd)
  {
    case 'H':
      BT_Command.OP=OP_H;
      break;

    case 'L':
      BT_Command.OP=OP_L;
      break;

    case 'T':
      BT_Command.OP=OP_T;
      break;

    default:
      BT_Command.OP=OP_N;
  }
  readString="";
}
#endif
