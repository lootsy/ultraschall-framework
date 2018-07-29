#include <stdlib.h>

#include <ultraschall/CredentialStore.h>

#include "Common.h"

ServiceStatus ULTRASCHALL_API UltraschallAllocPassword(void** ppPassword, const size_t PasswordLength)
{
  PRECONDITION_RETURN(ppPassword != NULL, SERVICE_INVALID_PARAMETER);
  PRECONDITION_RETURN(*ppPassword == NULL, SERVICE_INVALID_PARAMETER);
  PRECONDITION_RETURN(PasswordLength > 0, SERVICE_INVALID_PARAMETER);

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
  PRECONDITION(ppPassword != NULL);
  PRECONDITION(*ppPassword != NULL);
  PRECONDITION(PasswordLength > 0);

  memset(*ppPassword, 0, PasswordLength);
  free(*ppPassword);
  *ppPassword = NULL;
}
