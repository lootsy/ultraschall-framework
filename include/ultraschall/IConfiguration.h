#ifndef __ULTRASCHALL_FRAMEWORK_ICONFIGURATION_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_ICONFIGURATION_H_INCL__

#include <ServiceStatus.h>
#include <StringDictionary.h>

namespace ultraschall { namespace framework {

class IConfiugration
{
public:
  virtual ~IConfiguration()
  {
  }

  virtual ServiceStatus Configure(const StringDictionary& args) = 0;
};

}}

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_ICONFIGURATION_H_INCL__
