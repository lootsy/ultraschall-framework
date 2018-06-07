#ifndef __ULTRASCHALL_FRAMEWORK_SERVICE_FACTORY_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_SERVICE_FACTORY_H_INCL__

#include <map>
#include <mutex>
#include <string>

#include <ultraschall/ServiceStatus.h>
#include <ultraschall/IService.h>

namespace ultraschall
{
namespace framework
{

class ServiceFactory
{
  public:
    virtual ~ServiceFactory();

    typedef IService* (*CREATE_SERVICE_FUNCTION)(IServiceCallback* pCallback);

    static ServiceFactory& Instance();

    ServiceStatus RegisterService(const std::string& id, CREATE_SERVICE_FUNCTION pFunction);

    void UnregisterService(const std::string& id);

    ServiceStatus CreateService(const std::string& id, IServiceCallback* pServiceCallback, IService*& pService);

  private:
    typedef std::map<std::string, CREATE_SERVICE_FUNCTION> FunctionDictionary;
    FunctionDictionary                                     functions_;
    std::recursive_mutex                                   functionsLock_;
};

} // namespace framework
} // namespace ultraschall

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_SERVICE_FACTORY_H_INCL__
