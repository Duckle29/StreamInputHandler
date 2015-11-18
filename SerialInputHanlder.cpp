/*
  CoreScanner.h -
  Library for scanning the switches of a 6 switch,
  6 LED PCB for WASDkeyboards, keysampler.

  Created by Mikkel DBJ, 2015-10-23
  This file and the header file, are lsicenced under MIT license
*/

#include <SerialInputHandler.h>

SerialInputHandler::SerialInputHandler(Stream* printer)
{
  _printer = printer;
}

// readSerialBytes(char startChar, char stopChar, &pBuf, [length], [timeout])
// Arguments in [] are optional
//
// startChar : A character thats used to signal the start of a data packet
// stopChar  : A character thats used to signal the end of a data packet
// &pBuf     : The address to an array of any datatype, though bytes makes most sense.
//             (The function stuffs each byte, as they come, into this array byte per byte)
// length    : The length of the expected package. Something like sizeof(pBuf)/sizeof(pBuf[0]) should work to automate this
// timeout   : Time you want to wait for receiving the data. If this is exceeded, return false. (~5ms/byte @ 9600 baud)

bool SerialInputHandler::readSerialBytes(void* pBuf, uint16_t len, char startChar, char endChar, uint16_t timeout)
{
  _printer->print("test");
  if(timeout == -1)
  {
    timeout = len*10; // Timeout defaults to 10mS per byte, which is a little high.
  }
  _packet = false; // Used to determine if we are reading a packet, or not.
  _tempByte; // Used to store a byte of data in before we store it in the user passed buffer

  // We treat the pBuf as if it was a uint8_t so that we can increment it.
  // this is done so the user doesn't have to worry about casting.
  _currentByte = reinterpret_cast<uint8_t*>(pBuf);
  _bytesRead = 0; // The number of bytes that we have read

  _startedReading = millis(); // The time we started reading. Used for detecting timeout condition
  while(millis()-_startedReading < timeout && _bytesRead < len) // Keep looping until we have read the requested bytes, or untill we have timed out.
  {
    while(!_printer->available() && millis()-_startedReading < timeout){} // Wait for a byte to arrive. Stop waiting if we have waited for too long.
    if(_printer->available())
    {
      _tempByte = _printer->read();

      // If we have reached end of packet, don't save any more
      if(_tempByte == endChar || _bytesRead >= len)
      {
        _packet = false;
      }

      // Just scan through the garbage untill we get our package start byte
      if(_tempByte == startChar)
      {
        _packet = true; // Set it to true
        continue;
      }

      // If we are in between the start and end byte.
      if(_packet)
      {
        *_currentByte = _tempByte;
        _currentByte++;
        _bytesRead++;
      }
    }
  }

  if(millis()-_startedReading >= timeout && _bytesRead < len)
  {
    return false;
  }
  return true;
}
