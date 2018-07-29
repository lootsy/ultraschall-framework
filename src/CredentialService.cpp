#include <ultraschall/ICredentialServiceCallback.h>
#include "CredentialService.h"
#include "Common.h"

namespace ultraschall
{
namespace framework
{

CredentialService::~CredentialService()
{
    SafeRelease(pServiceCallback_);
}

IService* CredentialService::CreateService(IServiceCallback* pServiceCallback)
{
    PRECONDITION_RETURN(pServiceCallback != 0, 0);

    CredentialService* pService = new CredentialService();
    if (pService != 0)
    {
        pService->pServiceCallback_ = dynamic_cast<ICredentialServiceCallback*>(pServiceCallback);
        if (pService->pServiceCallback_ != 0)
        {
            pService->pServiceCallback_->AddRef();
        }
        else
        {
            SafeRelease(pService);
        }
    }

    return pService;
}

ServiceStatus CredentialService::CreateCredentials(const std::string&          service,
                                                   const std::string&          login,
                                                   const std::vector<uint8_t>& password)
{
    PRECONDITION_RETURN(service.empty() == false, SERVICE_INVALID_PARAMETER);
    PRECONDITION_RETURN(login.empty() == false, SERVICE_INVALID_PARAMETER);
    PRECONDITION_RETURN(password.empty() == false, SERVICE_INVALID_PARAMETER);

    return SERVICE_NOT_IMPLEMENTED;
}

ServiceStatus
CredentialService::ReadCredentials(const std::string& service, const std::string& login, std::vector<uint8_t>& password)
{
    PRECONDITION_RETURN(service.empty() == false, SERVICE_INVALID_PARAMETER);
    PRECONDITION_RETURN(login.empty() == false, SERVICE_INVALID_PARAMETER);

    return SERVICE_NOT_IMPLEMENTED;
}

ServiceStatus CredentialService::UpdateCredentials(const std::string&          service,
                                                   const std::string&          login,
                                                   const std::vector<uint8_t>& password)
{
    PRECONDITION_RETURN(service.empty() == false, SERVICE_INVALID_PARAMETER);
    PRECONDITION_RETURN(login.empty() == false, SERVICE_INVALID_PARAMETER);
    PRECONDITION_RETURN(password.empty() == false, SERVICE_INVALID_PARAMETER);

    return SERVICE_NOT_IMPLEMENTED;
}

ServiceStatus CredentialService::DeleteCredentials(const std::string& service, const std::string& login)
{
    PRECONDITION_RETURN(service.empty() == false, SERVICE_INVALID_PARAMETER);
    PRECONDITION_RETURN(login.empty() == false, SERVICE_INVALID_PARAMETER);

    return SERVICE_NOT_IMPLEMENTED;
}

} // namespace framework
} // namespace ultraschall
