#ifndef __ULTRASCHALL_FRAMEWORK_IACTIVATION_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_IACTIVATION_H_INCL__

#include <ultraschall/ServiceStatus.h>
#include <ultraschall/StringDictionary.h>

namespace ultraschall
{
namespace framework
{

class IActivation
{
  public:
    virtual ~IActivation() {}

    virtual ServiceStatus Start(const StringDictionary& args) = 0;
};

} // namespace framework
} // namespace ultraschall

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_IACTIVATION_H_INCL__
