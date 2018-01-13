#ifndef __ULTRASCHALL_FRAMEWORK_ISERVICE_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_ISERVICE_H_INCL__

#include <IServiceCallback.h>

namespace ultraschall { namespace framework {

class IService : public SharedObject
{
protected:
  IService(IServiceCallback* pCallback)
  {
  }

private:
  virtual ~IService()
  {
  }
};

}}

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_ISERVICE_H_INCL__
