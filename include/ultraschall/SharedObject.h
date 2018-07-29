#ifndef __ULTRASCHALL_FRAMEWORK_SHARED_OBJECT_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_SHARED_OBJECT_H_INCL__

#include <atomic>

namespace ultraschall
{
namespace framework
{

class SharedObject
{
  public:
    virtual uint32_t AddRef() const
    {
        return ++refCount_;
    }

    virtual uint32_t Release() const
    {
        const uint32_t refCount = --refCount_;
        if (refCount == 0)
        {
            delete this;
        }

        return refCount;
    }

  protected:
    SharedObject() : refCount_(1) {}

    virtual ~SharedObject() {}

  private:
    mutable std::atomic<uint32_t> refCount_ = 1;
};

} // namespace framework
} // namespace ultraschall

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_SHARED_OBJECT_H_INCL__
