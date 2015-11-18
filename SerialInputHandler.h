#ifndef SERIALINPUTHANDLER_H
#define SERIALINPUTHANDLER_H

#if (ARDUINO < 100)
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

class SerialInputHandler
{
  public:
    SerialInputHandler(Stream* printer);

    /*
    readSerialBytes(&pBuf, uint16_t length, char [startChar], char [stopChar], uint16_t [timeout])
    Arguments in [] are optional

    &pBuf     : The address to an array of any datatype, though bytes makes most sense.
               (The function stuffs each byte, as they come, into this array byte per byte)
    length    : The length of the expected package.
    startChar : A character thats used to signal the start of a data packet. Defaults to ASCII <STX>
    endChar   : A character thats used to signal the end of a data packet. Defailts to ASCII <ETX>

    timeout   : Time you want to wait for receiving the data. If this is exceeded, return false. (~5ms/byte @ 9600 baud)
    */
    bool readSerialBytes(void* pBuf,  uint16_t len, char startChar = 0x02, char endChar = 0x03, uint16_t timeout = -1);

  private:
    Stream* _printer;
    bool _packet;
    uint8_t _tempByte;
    uint8_t* _currentByte;
    uint16_t _bytesRead;
    uint32_t _startedReading;
};

#endif
