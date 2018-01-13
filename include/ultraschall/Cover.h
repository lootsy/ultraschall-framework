#ifndef __ULTRASCHALL_FRAMEWORK_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_H_INCL__

#include <string>

namespace ultraschall { namespace framework {

class Cover
{
public:
  Cover();

  Cover(const std::string& image);

  virtual ~Cover();

  inline const std::string& Image() const;

  inline void Image(const std::string& image);

private:
  std::string image_;

};

const std::string& Cover::Image() const
{
  return image_;
}

void Cover::Image(const std::string& image)
{
  image_ = image;
}

}}

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_H_INCL__
