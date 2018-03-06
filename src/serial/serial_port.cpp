#include "serial/serial_port.h"

SerialPort::~SerialPort()
{
  close();
}

bool SerialPort::open(LPCTSTR port, DWORD baudRate)
{
  char fileName[16] = "\\\\.\\";
  strcat(fileName, port);

  _handle = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL,
    OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

  if(!isValid())
    return false;

  DCB params = {0};
  params.DCBlength = sizeof(params);

  GetCommState(_handle, &params);
  params.BaudRate = baudRate;
  params.ByteSize = 8;
  params.StopBits = ONESTOPBIT;
  params.Parity = NOPARITY;
  params.fDtrControl = DTR_CONTROL_DISABLE;
  if(!SetCommState(_handle, &params))
    return false;

  PurgeComm(_handle, PURGE_RXCLEAR | PURGE_TXCLEAR);

  return true;
}

void SerialPort::close()
{
  if(!isValid())
    return;

  CloseHandle(_handle);
}

bool SerialPort::isValid()
{
  return _handle != INVALID_HANDLE_VALUE;
}

DWORD SerialPort::read(LPVOID data, DWORD length)
{
  if(!isValid())
    return 0;

  COMSTAT status;
  ClearCommError(_handle, NULL, &status);
  DWORD toRead = status.cbInQue > length ? length : status.cbInQue;

  DWORD bytesRead;
  ReadFile(_handle, data, toRead, &bytesRead, NULL);

  return bytesRead;
}

DWORD SerialPort::write(LPVOID data, DWORD length)
{
  if(!isValid())
    return 0;

  DWORD bytesWritten;
  WriteFile(_handle, data, length, &bytesWritten, NULL);
  FlushFileBuffers(_handle);

  return bytesWritten;
}
