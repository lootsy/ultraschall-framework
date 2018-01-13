#ifndef __ULTRASCHALL_FRAMEWORK_COMMON_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_COMMON_H_INCL__

namespace ultraschall { namespace framework {

#define Precondition(a) { if(!(a)) { return; }}
#define PreconditionReturn(a, b) { if(!(a)) { return (b); }}

template<typename T> void SafeDelete(T*& ptr)
{
  delete ptr;
  ptr = nullptr;
}

template<typename T> void SafeDeleteArray(T*& ptr)
{
  delete [] ptr;
  ptr = nullptr;
}

template<typename T> void SafeRelease(T*& ptr)
{
  if(ptr != nullptr)
  {
    ptr->Release();
    ptr = nullptr;
  }
}

}}

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_COMMON_H_INCL__
