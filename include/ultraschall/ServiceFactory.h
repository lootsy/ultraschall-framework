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

    template <class ServiceType> static bool RegisterService();

    template <class ServiceType> static void UnregisterService();

    template <class ServiceType> static IService* CreateService(IServiceCallback* pServiceCallback);

    static ServiceFactory& Instance();

    typedef IService* (*CREATE_SERVICE_FUNCTION)(IServiceCallback* pCallback);

    ServiceStatus ServiceFactory::RegisterService(const std::string& id, CREATE_SERVICE_FUNCTION pFunction);

    void UnregisterService(const std::string& id);

    ServiceStatus CreateService(const std::string& id, IServiceCallback* pServiceCallback, IService*& pService) const;

  private:
    typedef std::map<std::string, CREATE_SERVICE_FUNCTION> FunctionDictionary;
    FunctionDictionary                                     functions_;
    mutable std::recursive_mutex                           functionsLock_;
};

template <class T> bool ServiceFactory::RegisterService()
{
    PRECONDITION_RETURN(ServiceType::ServiceName().empty() == false, false);

    ServiceFactory& serviceFactory = ServiceFactory::Instance();
    return SERVICE_SUCCEEDED(serviceFactory.RegisterService(T::ServicewName(), T::CreateService));
}

template <class T> void ServiceFactory::UnregisterService()
{
    PRECONDITION(ServiceType::ServiceName().empty() == false);

    ServiceFactory& serviceFactory = ServiceFactory::Instance();
    serviceFactory.UnregisterService(T::ServicewName());
}

template <class ServiceType> IService* ServiceFactory::CreateService(IServiceCallback* pServiceCallback)
{
    PRECONDITION_RETURN(pServiceCallback != 0, 0);
    PRECONDITION_RETURN(ServiceType::ServiceName().empty() == false, 0);

    const ServiceFactory& serviceFactory = ServiceFactory::Instance();
    IService*             pService       = 0;
    const ServiceStatus   status = serviceFactory.CreateService(ServiceType::ServiceName(), pServiceCallback, pService);
    if (SERVICE_FAILED(status))
    {
        pService = 0;
    }

    return pService;
}

} // namespace framework
} // namespace ultraschall

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_SERVICE_FACTORY_H_INCL__
