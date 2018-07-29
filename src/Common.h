#ifndef __ULTRASCHALL_FRAMEWORK_COMMON_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_COMMON_H_INCL__

#define PRECONDITION(a)                                                                                                \
  {                                                                                                                    \
    if (!(a))                                                                                                          \
    {                                                                                                                  \
      return;                                                                                                          \
    }                                                                                                                  \
  }
#define PRECONDITION_RETURN(a, b)                                                                                       \
  {                                                                                                                    \
    if (!(a))                                                                                                          \
    {                                                                                                                  \
      return (b);                                                                                                      \
    }                                                                                                                  \
  }

namespace ultraschall
{
namespace framework
{

template <typename T> void SafeDelete(T*& ptr)
{
  delete ptr;
  ptr = 0;
}

template <typename T> void SafeDeleteArray(T*& ptr)
{
  delete[] ptr;
  ptr = 0;
}

template <typename T> void SafeRelease(T*& ptr)
{
  if (ptr != 0)
  {
    ptr->Release();
    ptr = 0;
  }
}

} // namespace framework
} // namespace ultraschall

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_COMMON_H_INCL__
