#pragma once

#include <windows.h>

class SerialPort
{
public:
  ~SerialPort();

  // Open serial communication at given port.
  bool open(LPCTSTR port, DWORD baudRate);

  // Close opened communication port.
  void close();

  // Check if port handle is valid.
  bool isValid();

  // Read from input stream buffer.
  DWORD read(LPVOID data, DWORD length);

  // Write to output buffer.
  DWORD write(LPVOID data, DWORD length);

private:
  HANDLE _handle;
};
