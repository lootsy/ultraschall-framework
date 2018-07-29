#ifndef __ULTRASCHALL_FRAMEWORK_ISERVICE_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_ISERVICE_H_INCL__

#include <ultraschall/IServiceCallback.h>

namespace ultraschall
{
namespace framework
{

class IService : public SharedObject
{
  protected:
    virtual ~IService() {}
};

} // namespace framework
} // namespace ultraschall

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_ISERVICE_H_INCL__
