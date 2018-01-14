#ifndef __ULTRASCHALL_FRAMEWORK_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_H_INCL__

#ifdef _MSC_VER
  #ifdef _DLL
    #define ULTRASCHALL_API __declspec(dllexport)
  #else
    #define ULTRASCHALL_API __declspec(dllimport)
  #endif // #ifdef _DLL
#else
  #ifdef __GNUC__
    #ifdef __DYNAMIC__
      #define ULTRASCHALL_API __attribute__((visibility("default")))
    #else
      #define ULTRASCHALL_API
    #endif // #ifdef __DYNAMIC__
  #endif // #ifdef __GNUC__
#endif // #ifdef _MSC_VER

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_H_INCL__
