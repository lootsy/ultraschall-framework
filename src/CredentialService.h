#ifndef __ULTRASCHALL_FRAMEWORK_CREDENTIAL_SERVICE_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_CREDENTIAL_SERVICE_H_INCL__

#include <ultraschall/ICredentialService.h>

namespace ultraschall
{
namespace framework
{

class ICredentialServiceCallback;

class CredentialService : public ICredentialService
{
  public:
    static IService* CreateService(IServiceCallback* pServiceCallback);

    virtual ServiceStatus
    CreateCredentials(const std::string& service, const std::string& login, const std::vector<uint8_t>& password);

    virtual ServiceStatus
    ReadCredentials(const std::string& service, const std::string& login, std::vector<uint8_t>& password);

    virtual ServiceStatus
    UpdateCredentials(const std::string& service, const std::string& login, const std::vector<uint8_t>& password);

    virtual ServiceStatus DeleteCredentials(const std::string& service, const std::string& login);

  protected:
    virtual ~CredentialService();

  private:
    ICredentialServiceCallback* pServiceCallback_;
};

} // namespace framework
} // namespace ultraschall

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_CREDENTIAL_SERVICE_H_INCL__
