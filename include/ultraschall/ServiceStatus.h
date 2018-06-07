#ifndef __ULTRASCHALL_FRAMEWORK_SERVICE_STATUS_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_SERVICE_STATUS_H_INCL__

#include <stdint.h>

typedef uint32_t ServiceStatus;

const ServiceStatus SERVICE_SUCCESS            = 0x00000000;
const ServiceStatus SERVICE_FAILURE            = 0x80000000;
const ServiceStatus SERVICE_INVALID_PARAMETER  = 0x80000001;
const ServiceStatus SERVICE_ALREADY_REGISTERED = 0x80000002;
const ServiceStatus SERVICE_NOT_FOUND          = 0x80000003;
const ServiceStatus SERVICE_NOT_IMPLEMENTED    = 0x80000004;
const ServiceStatus SERVICE_ALREADY_EXISTS     = 0x80000005;
const ServiceStatus SERVICE_OUT_OF_MEMORY      = 0x80000006;

#define SERVICE_SUCCEEDED(a) (a < 0x80000000)
#define SERVICE_FAILED(a) (SERVICE_SUCCEEDED((a)) == false)

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_SERVICE_STATUS_H_INCL__
