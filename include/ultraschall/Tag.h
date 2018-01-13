#ifndef __ULTRASCHALL_FRAMEWORK_TAG_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_TAG_H_INCL__

#include <string>

namespace ultraschall { namespace framework {

class Tag
{
public:
  static const double INVALID_TIMESTAMP;

  Tag();

  Tag(const double timestamp, const std::string& name);

  Tag(const double timestamp, const std::string& name, const std::string& image, const std::string& url);

  virtual ~Tag();

  inline double Timestamp() const;

  inline void Timestamp(const double timestamp);

  inline const std::string& Name() const;

  inline void Name(const std::string& name);

  inline const std::string& Image() const;

  inline void Image(const std::string& image);

  inline const std::string& Url() const;

  inline void Url(const std::string& url);

private:
  double timestamp_;
  std::string name_;
  std::string image_;
  std::string url_;
};

inline double Tag::Timestamp() const
{
  return timestamp_;
}

inline void Tag::Timestamp(const double timestamp)
{
  timestamp_ = timestamp;
}

inline const std::string& Tag::Name() const
{
  return name_;
}

inline void Tag::Name(const std::string& name)
{
  name_ = name;
}

inline const std::string& Tag::Image() const
{
  return image_;
}

inline void Tag::Image(const std::string& image)
{
  image_ = image;
}

inline const std::string& Tag::Url() const
{
  return url_;
}

inline void Tag::Url(const std::string& url)
{
  url_ = url;
}

}}

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_TAG_H_INCL__
