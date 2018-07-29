#include <ultraschall/ServiceFactory.h>

#include "Common.h"

namespace ultraschall
{
namespace framework
{

ServiceFactory::~ServiceFactory()
{
    std::lock_guard<std::recursive_mutex> lock(functionsLock_);

    functions_.clear();
}

ServiceFactory& ServiceFactory::Instance()
{
    static ServiceFactory instance;
    return instance;
}

ServiceStatus ServiceFactory::RegisterService(const std::string& id, CREATE_SERVICE_FUNCTION pFunction)
{
    PRECONDITION_RETURN(id.empty() == false, SERVICE_INVALID_PARAMETER);
    PRECONDITION_RETURN(pFunction != 0, SERVICE_INVALID_PARAMETER);

    std::lock_guard<std::recursive_mutex> lock(functionsLock_);

    ServiceStatus status = SERVICE_FAILURE;

    const FunctionDictionary::const_iterator functionIterator = functions_.find(id);
    if (functionIterator == functions_.end())
    {
        status = ((functions_.insert(std::pair<std::string, CREATE_SERVICE_FUNCTION>(id, pFunction)).second == true)
                      ? SERVICE_SUCCESS
                      : SERVICE_FAILURE);
    }
    else
    {
        status = SERVICE_ALREADY_REGISTERED;
    }

    return status;
}

void ServiceFactory::UnregisterService(const std::string& id)
{
    PRECONDITION(id.empty() == false);

    std::lock_guard<std::recursive_mutex> lock(functionsLock_);

    const FunctionDictionary::const_iterator functionIterator = functions_.find(id);
    if (functionIterator == functions_.end())
    {
        functions_.erase(functionIterator);
    }
}

ServiceStatus
ServiceFactory::CreateService(const std::string& id, IServiceCallback* pServiceCallback, IService*& pService) const
{
    PRECONDITION_RETURN(id.empty() == false, SERVICE_INVALID_PARAMETER);
    PRECONDITION_RETURN(pServiceCallback != 0, SERVICE_INVALID_PARAMETER);
    PRECONDITION_RETURN(pService == 0, SERVICE_INVALID_PARAMETER);

    std::lock_guard<std::recursive_mutex> lock(functionsLock_);

    ServiceStatus status = SERVICE_FAILURE;

    pService = 0;

    const FunctionDictionary::const_iterator functionIterator = functions_.find(id);
    if (functionIterator != functions_.end())
    {
        pService = (functionIterator->second)(pServiceCallback);
        if (pService != 0)
        {
            status = SERVICE_SUCCESS;
        }
    }

    return status;
}
} // namespace framework
} // namespace ultraschall
