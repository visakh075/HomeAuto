void PrintState(void)
{
  Serial.print("States : ");
  for(uint8_t i=0;i<4;i++)
  {
    Serial.print(RelayState(i)?'H':'L');
    #if(BLUE_EN==1)
    {
      Bluetooth.print(RelayState(i)?'H':'L');
    }
    #endif
  }
  Serial.println();
}
void RunCommand(Command cmd)
{
  switch(cmd.OP)
  {
    case OP_H:
    SetBitH(cmd.Key);
    break;
    
    case OP_L:
    SetBitL(cmd.Key);
    break;

    case OP_T:
    SetBitT(cmd.Key);
    break;

    default:
    break;
  }
}
void ValidateAndControl(void)
{
  if(IR_Command.Key!=NO_IRKEY && IR_Command.OP!=OP_N)
  {
    RunCommand(IR_Command);
  }
  #if(BLUE_EN == 1)
  else if(BT_Command.Key!=NO_BTKEY && BT_Command.OP!=OP_N)
  {
    RunCommand(BT_Command);
  }
  #endif
}