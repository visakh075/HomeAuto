void Remote() {

  // set default key to NO_IRKEY
  // this has status bit 0 and connected to NORELAY (via R0)
  IR_Key=(uint8_t)NO_IRKEY;
  IR_Cmd=OP_N;
  if (IrReceiver.decode())
  {
      
      Current=IrReceiver.decodedIRData.command;

      // From remote key to Status Bit
      for(uint8_t SW=0;SW<NUM_OUTPUTS;SW++)
      {
        if(Current==Codes[SW])
        {
          IR_Key=SW;
          IR_Cmd=OP_T;
          break;
        }
      }
      IrReceiver.resume();
  }
}

void RemoteControl(void)
{
  // assume the IR_Key is set by Remote Control
  // IR_key represent the index of relay to be controlled
  // Skip 
  if(IR_Key!=NO_IRKEY)
  {
    // Change state
    // for ir key its just toggling only
    IR_Command.Key=IR_Key;
    IR_Command.OP=OP_T;
    // SetBitT(IR_Key);
  }
}
