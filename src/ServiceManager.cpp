#include "Common.h"
#include <ServiceFactory.h>
#include <ServiceManager.h>

namespace ultraschall
{
namespace framework
{

ServiceManager::~ServiceManager()
{
  std::lock_guard<std::recursive_mutex> lock(servicesLock_);
}

ServiceManager& ServiceManager::Instance()
{
  static ServiceManager self;
  return self;
}

ServiceStatus ServiceManager::AcquireService(const std::string& id, IServiceCallback* pCallback, IService*& pService)
{
  PreconditionReturn(id.empty() == false, SERVICE_INVALID_PARAMETER);

  std::lock_guard<std::recursive_mutex> lock(servicesLock_);

  ServiceStatus status = SERVICE_FAILURE;

  pService = 0;

  const ServiceDictionary::iterator serviceIterator = services_.find(id);
  if (serviceIterator == services_.end())
  {
    ServiceFactory& serviceFactory = ServiceFactory::Instance();
    status                         = serviceFactory.CreateService(id, pCallback, pService);
    if (SERVICE_SUCCEEDED(status))
    {
      status = ((services_.insert(std::pair<std::string, IService*>(id, pService)).second == true) ? SERVICE_SUCCESS
                                                                                                   : SERVICE_FAILURE);
    }
  }
  else
  {
    pService = serviceIterator->second;
    if (pService != 0)
    {
      pService->AddRef();

      status = SERVICE_SUCCESS;
    }
  }

  return status;
}

ServiceStatus ServiceManager::ReleaseService(const std::string& id)
{
  PreconditionReturn(id.empty() == false, SERVICE_INVALID_PARAMETER);

  std::lock_guard<std::recursive_mutex> lock(servicesLock_);

  ServiceStatus status = SERVICE_NOT_FOUND;

  const ServiceDictionary::iterator serviceIterator = services_.find(id);
  if (serviceIterator != services_.end())
  {
    IService* pService = serviceIterator->second;
    if (pService != 0)
    {
      if (pService->Release() == 0)
      {
        services_.erase(serviceIterator);
      }

      status = SERVICE_SUCCESS;
    }
    else
    {
      status = SERVICE_FAILURE;
      //FIXME: raise fatal error
    }
  }

  return status;
}
}
}
