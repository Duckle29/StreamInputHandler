#include "SerialInputHandler.h"

SerialInputHandler inputter(&Serial);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{

  /*
  readSerialBytes(char startChar, char stopChar, &pBuf, length, timeout)
  startChar : A character thats used to signal the start of a data packet
  stopChar  : A character thats used to signal the end of a data packet
  &pBuf     : The address to an array of any datatype, though bytes makes most sense.
             (The function stuffs each byte, as they come, into this array byte per byte)
  length    : The length of the expected package. Something like sizeof(pBuf)/sizeof(pBuf[0]) should work to automate this
  timeout   : Time you want to wait for receiving the data. If this is exceeded, return false. (~5ms/byte @ 9600 baud)
  */

  char myBuf[10];
  // If we successfully read all the 10 bytes that we want (or if we specify another length that'll fit in our buffer)
  if(Serial.available())
  {
    if(inputter.readSerialBytes(&myBuf[0], sizeof(myBuf)/sizeof(myBuf[0]), '!', '$'))
    {
      for(int i=0; i<10; i++)
      {
        Serial.print(myBuf[i], DEC);
        Serial.print(" : ");
      }
      Serial.println();
    }
    else
    {
      Serial.println("Timed Out");
    }
  }
}
