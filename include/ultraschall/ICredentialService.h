#ifndef __ULTRASCHALL_FRAMEWORK_ICREDENTIAL_SERVICE_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_ICREDENTIAL_SERVICE_H_INCL__

#include <string>
#include <vector>

#include <ultraschall/IService.h>
#include <ultraschall/ServiceStatus.h>

namespace ultraschall
{
namespace framework
{

class ICredentialService : public IService
{
  public:
    virtual ServiceStatus CreateCredentials(const std::string& service, const std::string& login, const std::vector<uint8_t>& password) = 0;

    virtual ServiceStatus
    ReadCredentials(const std::string& service, const std::string& login, std::vector<uint8_t>& password) = 0;

    virtual ServiceStatus
    UpdateCredentials(const std::string& service, const std::string& login, const std::vector<uint8_t>& password) = 0;

    virtual ServiceStatus DeleteCredentials(const std::string& service, const std::string& login) = 0;

  protected:
    virtual ~ICredentialService() {}
};

} // namespace framework
} // namespace ultraschall

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_ICREDENTIAL_SERVICE_H_INCL__
