#include <stdlib.h>

#include <ultraschall/CredentialStore.h>

#include "Common.h"

ServiceStatus ULTRASCHALL_API UltraschallAllocPassword(void** ppPassword, const size_t PasswordLength)
{
  PreconditionReturn(ppPassword != NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(*ppPassword == NULL, SERVICE_INVALID_PARAMETER);
  PreconditionReturn(PasswordLength > 0, SERVICE_INVALID_PARAMETER);

  ServiceStatus Status = SERVICE_FAILURE;

  *ppPassword = calloc(PasswordLength, sizeof(char));
  if (*ppPassword != NULL)
  {
    Status = SERVICE_SUCCESS;
  }
  else
  {
    Status = SERVICE_OUT_OF_MEMORY;
  }

  return Status;
}

void ULTRASCHALL_API UltraschallDeletePassword(void** ppPassword, const size_t PasswordLength)
{
  Precondition(ppPassword != NULL);
  Precondition(*ppPassword != NULL);
  Precondition(PasswordLength > 0);

  memset(*ppPassword, 0, PasswordLength);
  free(*ppPassword);
  *ppPassword = NULL;
}
