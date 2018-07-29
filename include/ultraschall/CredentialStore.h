#ifndef __ULTRASCHALL_CREDENTIAL_STORE_H_INCL__
#define __ULTRASCHALL_CREDENTIAL_STORE_H_INCL__

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <ultraschall/Framework.h>
#include <ultraschall/ServiceStatus.h>

#ifndef __cplusplus__
extern "C"
{
#endif // #ifndef __cplusplus__

    ServiceStatus ULTRASCHALL_API UltraschallCreateCredentialsW(LPCWSTR      ServiceName,
                                                                const size_t ServiceNameLength,
                                                                LPCWSTR      LoginName,
                                                                const size_t LoginNameLength,
                                                                const void*  pPassword,
                                                                const size_t PasswordLength);

    ServiceStatus ULTRASCHALL_API UltraschallCreateCredentialsA(LPCSTR       ServiceName,
                                                                const size_t ServiceNameLength,
                                                                LPCSTR       LoginName,
                                                                const size_t LoginNameLength,
                                                                const void*  pPassword,
                                                                const size_t PasswordLength);

    ServiceStatus ULTRASCHALL_API UltraschallReadCredentialsW(LPCWSTR      ServiceName,
                                                              const size_t ServiceNameLength,
                                                              LPCWSTR      LoginName,
                                                              const size_t LoginNameLength,
                                                              void**       ppPassword,
                                                              size_t*      pPasswordLength);

    ServiceStatus ULTRASCHALL_API UltraschallReadCredentialsA(LPCSTR       ServiceName,
                                                              const size_t ServiceNameLength,
                                                              LPCSTR       LoginName,
                                                              const size_t LoginNameLength,
                                                              void**       ppPassword,
                                                              size_t*      pPasswordLength);

    ServiceStatus ULTRASCHALL_API UltraschallUpdateCredentialsW(LPCWSTR      ServiceName,
                                                                const size_t ServiceNameLength,
                                                                LPCWSTR      LoginName,
                                                                const size_t LoginNameLength,
                                                                const void*  pPassword,
                                                                const size_t PasswordLength);

    ServiceStatus ULTRASCHALL_API UltraschallUpdateCredentialsA(LPCSTR       ServiceName,
                                                                const size_t ServiceNameLength,
                                                                LPCSTR       LoginName,
                                                                const size_t LoginNameLength,
                                                                const void*  pPassword,
                                                                const size_t PasswordLength);

    ServiceStatus ULTRASCHALL_API UltraschallDeleteCredentialsW(LPCWSTR      ServiceName,
                                                                const size_t ServiceNameLength,
                                                                LPCWSTR      LoginName,
                                                                const size_t LoginNameLength);

    ServiceStatus ULTRASCHALL_API UltraschallDeleteCredentialsA(LPCSTR       ServiceName,
                                                                const size_t ServiceNameLength,
                                                                LPCSTR       LoginName,
                                                                const size_t LoginNameLength);

#ifdef UNICODE
#define UltraschallCreateCredentials UltraschallCreateCredentialsW
#define UltraschallReadCredentials UltraschallReadCredentialsW
#define UltraschallUpdateCredentials UltraschallUpdateCredentialsW
#define UltraschallDeleteCredentials UltraschallDeleteCredentialsW
#else
#define UltraschallCreateCredentials UltraschallCreateCredentialsA
#define UltraschallReadCredentials UltraschallReadCredentialsA
#define UltraschallUpdateCredentials UltraschallUpdateCredentialsA
#define UltraschallDeleteCredentials UltraschallDeleteCredentialsA
#endif // #ifdef UNICODE

    ServiceStatus ULTRASCHALL_API UltraschallAllocPassword(void** ppPassword, const size_t PasswordLength);

    void ULTRASCHALL_API UltraschallDeletePassword(void** ppPassword, const size_t PasswordLength);

#ifndef __cplusplus__
}
#endif // #ifndef __cplusplus__

#endif // #ifndef __ULTRASCHALL_CREDENTIAL_STORE_H_INCL__,
