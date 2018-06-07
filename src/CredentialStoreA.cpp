#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <stdlib.h>

#include "ultraschall/CredentialStore.h"

#include "Common.h"

extern void UltraschallPrintSecErrorW(LPCWSTR Description, const long Status);

void UltraschallFreeUnicodeString(LPWSTR* ppUnicodeString, const size_t UnicodeStringLength)
{
  Precondition(ppUnicodeString != 0);
  Precondition(*ppUnicodeString != 0);
  Precondition(UnicodeStringLength > 0);

  memset((void*)*ppUnicodeString, 0, UnicodeStringLength);
  free((void*)*ppUnicodeString);
  *ppUnicodeString = 0;
}

int32_t UltraschallAnsiStringToUnicodeString(LPCSTR       AnsiString,
                                             const size_t AnsiStringLength,
                                             LPWSTR*      pUnicodeString,
                                             size_t*      pUnicodeStringLength)
{
  PreconditionReturn(AnsiString != 0, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(AnsiStringLength > 0, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(pUnicodeString != 0, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(pUnicodeStringLength != 0, SERVICE_INVALID_PARAMETER);

  ServiceStatus Status = SERVICE_FAILURE;

  int UnicodeStringLength = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, AnsiString, (int)AnsiStringLength, 0, 0);
  if (UnicodeStringLength > 0)
  {
    LPWSTR UnicodeString = (LPWSTR)calloc(UnicodeStringLength + 1, sizeof(WCHAR));
    if (UnicodeString != 0)
    {
      int ConvertedChars = MultiByteToWideChar(
          CP_ACP, MB_ERR_INVALID_CHARS, AnsiString, (int)AnsiStringLength, UnicodeString, UnicodeStringLength);
      if (ConvertedChars > 0)
      {
        *pUnicodeString       = UnicodeString;
        *pUnicodeStringLength = UnicodeStringLength;

        Status = SERVICE_SUCCESS;
      }
      else
      {
        UltraschallFreeUnicodeString(&UnicodeString, UnicodeStringLength);

        Status = SERVICE_FAILURE;
      }
    }
    else
    {
      Status = SERVICE_OUT_OF_MEMORY;
    }
  }

  return Status;
}

void UltraschallPrintSecErrorA(LPCSTR Description, const long Status)
{
  Precondition(Description != 0);

  const size_t DescriptionLength = strlen(Description);
  if (DescriptionLength > 0)
  {
    LPWSTR        UnicodeString       = 0;
    size_t        UnicodeStringLength = 0;
    ServiceStatus Status =
        UltraschallAnsiStringToUnicodeString(Description, DescriptionLength, &UnicodeString, &UnicodeStringLength);
    if (SERVICE_SUCCEEDED(Status))
    {
      UltraschallPrintSecErrorW(UnicodeString, Status);

      UltraschallFreeUnicodeString(&UnicodeString, UnicodeStringLength);
    }
  }
}

ServiceStatus ULTRASCHALL_API UltraschallCreateCredentialsA(LPCSTR       ServiceName,
                                                            const size_t ServiceNameLength,
                                                            LPCSTR       LoginName,
                                                            const size_t LoginNameLength,
                                                            const void*  pPassword,
                                                            const size_t PasswordLength)
{
  PreconditionReturn(ServiceName != 0, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(ServiceNameLength > 0, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(LoginName != 0, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(LoginNameLength > 0, SERVICE_INVALID_PARAMETER);

  LPWSTR        ServiceNameBuffer       = 0;
  size_t        ServiceNameBufferLength = 0;
  ServiceStatus Status                  = UltraschallAnsiStringToUnicodeString(
      ServiceName, ServiceNameLength, &ServiceNameBuffer, &ServiceNameBufferLength);
  if (SERVICE_SUCCEEDED(Status))
  {
    LPWSTR LoginNameBuffer       = 0;
    size_t LoginNameBufferLength = 0;
    Status = UltraschallAnsiStringToUnicodeString(LoginName, LoginNameLength, &LoginNameBuffer, &LoginNameBufferLength);
    if (SERVICE_SUCCEEDED(Status))
    {
      Status = UltraschallCreateCredentialsW(
          ServiceNameBuffer, ServiceNameBufferLength, LoginNameBuffer, LoginNameBufferLength, pPassword, PasswordLength);

      UltraschallFreeUnicodeString(&LoginNameBuffer, LoginNameBufferLength);
    }

    UltraschallFreeUnicodeString(&ServiceNameBuffer, ServiceNameBufferLength);
  }

  return Status;
}

ServiceStatus ULTRASCHALL_API UltraschallReadCredentialsA(LPCSTR       ServiceName,
                                                          const size_t ServiceNameLength,
                                                          LPCSTR       LoginName,
                                                          const size_t LoginNameLength,
                                                          void**       ppPassword,
                                                          size_t*      pPasswordLength)
{
  PreconditionReturn(ServiceName != NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(ServiceNameLength > 0, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(LoginName != NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(LoginNameLength > 0, SERVICE_INVALID_PARAMETER);

  LPWSTR        ServiceNameBuffer       = 0;
  size_t        ServiceNameBufferLength = 0;
  ServiceStatus Status                  = UltraschallAnsiStringToUnicodeString(
      ServiceName, ServiceNameLength, &ServiceNameBuffer, &ServiceNameBufferLength);
  if (SERVICE_SUCCEEDED(Status))
  {
    LPWSTR LoginNameBuffer       = 0;
    size_t LoginNameBufferLength = 0;
    Status = UltraschallAnsiStringToUnicodeString(LoginName, LoginNameLength, &LoginNameBuffer, &LoginNameBufferLength);
    if (SERVICE_SUCCEEDED(Status))
    {
      Status = UltraschallReadCredentialsW(ServiceNameBuffer,
                                           ServiceNameBufferLength,
                                           LoginNameBuffer,
                                           LoginNameBufferLength,
                                           ppPassword,
                                           pPasswordLength);

      UltraschallFreeUnicodeString(&LoginNameBuffer, LoginNameBufferLength);
    }

    UltraschallFreeUnicodeString(&ServiceNameBuffer, ServiceNameBufferLength);
  }

  return Status;
}

ServiceStatus ULTRASCHALL_API UltraschallUpdateCredentialsA(LPCSTR       ServiceName,
                                                            const size_t ServiceNameLength,
                                                            LPCSTR       LoginName,
                                                            const size_t LoginNameLength,
                                                            const void*  pPassword,
                                                            const size_t PasswordLength)
{
  PreconditionReturn(ServiceName != NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(ServiceNameLength > 0, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(LoginName != NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(LoginNameLength > 0, SERVICE_INVALID_PARAMETER);

  LPWSTR        ServiceNameBuffer       = 0;
  size_t        ServiceNameBufferLength = 0;
  ServiceStatus Status                  = UltraschallAnsiStringToUnicodeString(
      ServiceName, ServiceNameLength, &ServiceNameBuffer, &ServiceNameBufferLength);
  if (SERVICE_SUCCEEDED(Status))
  {
    LPWSTR LoginNameBuffer       = 0;
    size_t LoginNameBufferLength = 0;
    Status = UltraschallAnsiStringToUnicodeString(LoginName, LoginNameLength, &LoginNameBuffer, &LoginNameBufferLength);
    if (SERVICE_SUCCEEDED(Status))
    {
      Status = UltraschallUpdateCredentialsW(
          ServiceNameBuffer, ServiceNameBufferLength, LoginNameBuffer, LoginNameBufferLength, pPassword, PasswordLength);

      UltraschallFreeUnicodeString(&LoginNameBuffer, LoginNameBufferLength);
    }

    UltraschallFreeUnicodeString(&ServiceNameBuffer, ServiceNameBufferLength);
  }

  return Status;
}

ServiceStatus ULTRASCHALL_API UltraschallDeleteCredentialsA(LPCSTR       ServiceName,
                                                            const size_t ServiceNameLength,
                                                            LPCSTR       LoginName,
                                                            const size_t LoginNameLength)
{
  PreconditionReturn(ServiceName != NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(ServiceNameLength > 0, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(LoginName != NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(LoginNameLength > 0, SERVICE_INVALID_PARAMETER);

  LPWSTR        ServiceNameBuffer       = 0;
  size_t        ServiceNameBufferLength = 0;
  ServiceStatus Status                  = UltraschallAnsiStringToUnicodeString(
      ServiceName, ServiceNameLength, &ServiceNameBuffer, &ServiceNameBufferLength);
  if (SERVICE_SUCCEEDED(Status))
  {
    LPWSTR LoginNameBuffer       = 0;
    size_t LoginNameBufferLength = 0;
    Status = UltraschallAnsiStringToUnicodeString(LoginName, LoginNameLength, &LoginNameBuffer, &LoginNameBufferLength);
    if (SERVICE_SUCCEEDED(Status))
    {
      Status = UltraschallDeleteCredentialsW(
          ServiceNameBuffer, ServiceNameBufferLength, LoginNameBuffer, LoginNameBufferLength);

      UltraschallFreeUnicodeString(&LoginNameBuffer, LoginNameBufferLength);
    }

    UltraschallFreeUnicodeString(&ServiceNameBuffer, ServiceNameBufferLength);
  }

  return Status;
}
