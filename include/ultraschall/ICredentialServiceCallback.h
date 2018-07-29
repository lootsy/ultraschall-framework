#ifndef __ULTRASCHALL_FRAMEWORK_ICREDENTIAL_SERVICE_CALLBACK_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_ICREDENTIAL_SERVICE_CALLBACK_H_INCL__

#include <string>
#include <vector>

#include <ultraschall/IService.h>
#include <ultraschall/IServiceCallback.h>

namespace ultraschall
{
namespace framework
{

class ICredentialServiceCallback : public IServiceCallback
{
  public:
    virtual void ServiceSucceeded() = 0;

    virtual void ServiceFailed() = 0;

  protected:
    virtual ~ICredentialServiceCallback() {}
};

} // namespace framework
} // namespace ultraschall

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_ICREDENTIAL_SERVICE_CALLBACK_H_INCL__
#pragma once
