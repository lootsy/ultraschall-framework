#include <Tag.h>

namespace ultraschall { namespace framework {

const double Tag::INVALID_TIMESTAMP = -1;

Tag::Tag() : timestamp_(INVALID_TIMESTAMP)
{
}

Tag::Tag(const double timestamp, const std::string& name) :
  timestamp_(timestamp), name_(name)
{
}

Tag::Tag(const double timestamp, const std::string& name, const std::string& image, const std::string& url) :
  timestamp_(timestamp), name_(name), image_(image), url_(url)
{
}

Tag::~Tag()
{
  timestamp_ = INVALID_TIMESTAMP;
  name_.clear();
  image_.clear();
  url_.clear();
}

}}

