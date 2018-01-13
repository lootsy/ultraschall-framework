#ifndef __ULTRASCHALL_FRAMEWORK_IACTIVATION_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_IACTIVATION_H_INCL__

#include <ServiceStatus.>
#include <StringDictionary.h>

namespace ultraschall { namespace framework {

class IActivation
{
public:
  virtual ~IActivation()
  {
  }

  virtual ServiceStatus Start(const StringDictionary& args) = 0;
};

}}

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_IACTIVATION_H_INCL__

