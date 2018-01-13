#include <Cover.h>

namespace ultraschall { namespace framework {

Cover::Cover()
{
}

Cover::Cover(const std::string& image) : image_(image)
{
}

Cover::~Cover()
{
  image_.clear();
}

}}
