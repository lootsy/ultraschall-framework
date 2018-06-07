#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wincred.h>

#include <ultraschall/CredentialStore.h>

#include "Common.h"

void UltraschallPrintSecErrorW(LPCWSTR Description, const long Status)
{
  Precondition(Description != 0);

  LPWSTR MessageBuffer     = 0;
  size_t MessageBufferSize = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                                            0,
                                            Status,
                                            MAKELCID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
                                            (LPWSTR)&MessageBuffer,
                                            0,
                                            0);
  if (MessageBufferSize > 0)
  {
    //std::wcout << Description << L", rc = " << Status << L", " << MessageBuffer << std::endl;
  }

  if (MessageBuffer != 0)
  {
    LocalFree(MessageBuffer);
    MessageBuffer = 0;
  }

  MessageBufferSize = 0;
}

ServiceStatus ULTRASCHALL_API UltraschallCreateCredentialsW(LPCWSTR      ServiceName,
                                                            const size_t ServiceNameLength,
                                                            LPCWSTR      LoginName,
                                                            const size_t LoginNameLength,
                                                            const void*  pPassword,
                                                            const size_t PasswordLength)
{
  PreconditionReturn(ServiceName != NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(ServiceNameLength > 0, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(LoginName != NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(LoginNameLength > 0, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(pPassword != NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(PasswordLength > 0, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(PasswordLength <= CRED_MAX_CREDENTIAL_BLOB_SIZE, SERVICE_INVALID_PARAMETER);

  ServiceStatus Status = SERVICE_FAILURE;

  PCREDENTIALW pCredential = { 0 };
  if (CredReadW(ServiceName, CRED_TYPE_GENERIC, 0, &pCredential) == FALSE)
  {
    CREDENTIALW Credential        = { 0 };
    Credential.Type               = CRED_TYPE_GENERIC;
    Credential.TargetName         = (LPWSTR)ServiceName;
    Credential.Comment            = L"Created by StudioLink credential store";
    Credential.CredentialBlobSize = (DWORD)PasswordLength;
    Credential.CredentialBlob     = (LPBYTE)pPassword;
    Credential.Persist            = CRED_PERSIST_LOCAL_MACHINE;
    Credential.UserName           = (LPWSTR)LoginName;

    if (CredWriteW(&Credential, 0) != FALSE)
    {
      Status = SERVICE_SUCCESS;
    }
    else
    {
      UltraschallPrintSecErrorW(L"CredWrite failed", GetLastError());

      Status = SERVICE_FAILURE;
    }
  }
  else
  {
    CredFree(pCredential);
    pCredential = 0;
    UltraschallPrintSecErrorW(L"CredWrite failed", ERROR_ALREADY_EXISTS);
    Status = SERVICE_ALREADY_EXISTS;
  }

  return Status;
}

ServiceStatus ULTRASCHALL_API UltraschallReadCredentialsW(LPCWSTR      ServiceName,
                                                          const size_t ServiceNameLength,
                                                          LPCWSTR      LoginName,
                                                          const size_t LoginNameLength,
                                                          void**       ppPassword,
                                                          size_t*      pPasswordLength)
{
  PreconditionReturn(ServiceName != NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(ServiceNameLength > 0, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(LoginName != NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(LoginNameLength > 0, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(ppPassword != NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(pPasswordLength != NULL, SERVICE_INVALID_PARAMETER);

  ServiceStatus Status = SERVICE_FAILURE;

  *ppPassword      = 0;
  *pPasswordLength = 0;

  PCREDENTIALW pCredential = { 0 };
  if (CredReadW(ServiceName, CRED_TYPE_GENERIC, 0, &pCredential) != FALSE)
  {
    Status = UltraschallAllocPassword(ppPassword, pCredential->CredentialBlobSize);
    if (SERVICE_SUCCESS == Status)
    {
      memmove(*ppPassword, pCredential->CredentialBlob, pCredential->CredentialBlobSize);
      *pPasswordLength = pCredential->CredentialBlobSize;
      Status           = SERVICE_SUCCESS;
    }

    CredFree(pCredential);
    pCredential = 0;
    Status      = SERVICE_SUCCESS;
  }
  else
  {
    const long StatusCode = GetLastError();
    UltraschallPrintSecErrorW(L"CredRead failed", StatusCode);

    if (ERROR_NOT_FOUND == StatusCode)
    {
      Status = SERVICE_NOT_FOUND;
    }
    else
    {
      Status = SERVICE_FAILURE;
    }
  }

  return Status;
}

ServiceStatus ULTRASCHALL_API UltraschallUpdateCredentialsW(LPCWSTR      ServiceName,
                                                            const size_t ServiceNameLength,
                                                            LPCWSTR      LoginName,
                                                            const size_t LoginNameLength,
                                                            const void*  pPassword,
                                                            const size_t PasswordLength)
{
  PreconditionReturn(ServiceName != NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(ServiceNameLength > 0, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(LoginName != NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(LoginNameLength > 0, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(pPassword != NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(PasswordLength > 0, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(PasswordLength <= CRED_MAX_CREDENTIAL_BLOB_SIZE, SERVICE_INVALID_PARAMETER);

  ServiceStatus Status = SERVICE_FAILURE;

  PCREDENTIALW pCredential = { 0 };
  if (CredReadW(ServiceName, CRED_TYPE_GENERIC, 0, &pCredential) != FALSE)
  {
    CredFree(pCredential);
    pCredential = 0;

    CREDENTIALW Credential        = { 0 };
    Credential.Type               = CRED_TYPE_GENERIC;
    Credential.TargetName         = (LPWSTR)ServiceName;
    Credential.Comment            = L"Created by StudioLink credential store";
    Credential.CredentialBlobSize = (DWORD)PasswordLength;
    Credential.CredentialBlob     = (LPBYTE)pPassword;
    Credential.Persist            = CRED_PERSIST_LOCAL_MACHINE;
    Credential.UserName           = (LPWSTR)LoginName;

    if (CredWriteW(&Credential, 0) != FALSE)
    {
      Status = SERVICE_SUCCESS;
    }
    else
    {
      UltraschallPrintSecErrorW(L"CredWrite failed", GetLastError());

      Status = SERVICE_FAILURE;
    }
  }
  else
  {
    UltraschallPrintSecErrorW(L"CredWrite failed", ERROR_NOT_FOUND);
    Status = SERVICE_NOT_FOUND;
  }

  return Status;
}

ServiceStatus ULTRASCHALL_API UltraschallDeleteCredentialsW(LPCWSTR      ServiceName,
                                                            const size_t ServiceNameLength,
                                                            LPCWSTR      LoginName,
                                                            const size_t LoginNameLength)
{
  PreconditionReturn(ServiceName != NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(ServiceNameLength > 0, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(LoginName != NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(LoginNameLength > 0, SERVICE_INVALID_PARAMETER);

  ServiceStatus Status = SERVICE_FAILURE;

  if (CredDeleteW(ServiceName, CRED_TYPE_GENERIC, 0) != FALSE)
  {
    Status = SERVICE_SUCCESS;
  }
  else
  {
    const long StatusCode = GetLastError();
    UltraschallPrintSecErrorW(L"CredDelete failed", StatusCode);

    if (ERROR_NOT_FOUND == StatusCode)
    {
      Status = SERVICE_NOT_FOUND;
    }
    else
    {
      Status = SERVICE_FAILURE;
    }
  }

  return Status;
}
