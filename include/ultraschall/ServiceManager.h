#ifndef __ULTRASCHALL_FRAMEWORK_SERVICE_MANAGER_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_SERVICE_MANAGER_H_INCL__

#include <map>
#include <mutex>
#include <string>

#include <ultraschall/IService.h>
#include <ultraschall/ServiceStatus.h>

namespace ultraschall
{
namespace framework
{

class ServiceManager
{
  public:
    virtual ~ServiceManager();

    static ServiceManager& Instance();

    ServiceStatus AcquireService(const std::string& id, IServiceCallback* pCallback, IService*& pService);

    ServiceStatus ReleaseService(const std::string& id);

  private:
    typedef std::map<std::string, IService*> ServiceDictionary;
    ServiceDictionary                        services_;
    std::recursive_mutex                     servicesLock_;
};
} // namespace framework
} // namespace ultraschall

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_SERVICE_MANAGER_H_INCL__
