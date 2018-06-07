#ifndef __ULTRASCHALL_FRAMEWORK_ICONFIGURATION_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_ICONFIGURATION_H_INCL__

#include <ultraschall/ServiceStatus.h>
#include <ultraschall/StringDictionary.h>

namespace ultraschall
{
namespace framework
{

class IConfiguration
{
  public:
    virtual ~IConfiguration() {}

    virtual ServiceStatus Configure(const StringDictionary& args) = 0;
};

} // namespace framework
} // namespace ultraschall

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_ICONFIGURATION_H_INCL__
