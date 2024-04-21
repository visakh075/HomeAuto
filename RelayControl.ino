void SetHIGH(uint8_t RelayId)
{
  if(RELAYS[RelayId]!=NORELAY)
  {
    digitalWrite(RELAYS[RelayId],HIGH);
  }
}
void SetLOW(uint8_t RelayId)
{
    if(RELAYS[RelayId]!=NORELAY)
  {
    digitalWrite(RELAYS[RelayId],LOW);
  }
}
void SetRelays(void)
{
  uint8_t tmpRelay,tmpRelayState;
  for(uint8_t RelayId=0;RelayId<NUM_OUTPUTS;RelayId++)
  {

    tmpRelay=RELAYS[RelayId];
    tmpRelayState=RelayState(RelayId);
    Serial.print("R");
    Serial.print(RelayId);
    Serial.print(" ");
    Serial.print((tmpRelay!=NORELAY)?tmpRelay:9);
    Serial.print(" ");
    Serial.print(tmpRelayState);
    
    if(tmpRelayState)
    {
      SetHIGH(RelayId);
      Serial.print(" ON");
    }
    else
    {
      SetLOW(RelayId);
      Serial.print(" OFF");
    }
    Serial.println();
  }
}
