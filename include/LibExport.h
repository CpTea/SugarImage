#ifndef SUGAR_LIBAPI
#define SUGAR_LIBAPI

#ifdef _MSC_VER
#ifdef LIBRARY_EXPORT
#define LIB_API __declspec(dllexport)
#else
#define LIB_API __declspec(dllimport)
#endif
#define LIB_INT
#else
#define LIB_API __attribute((visibility("default")))
#define LIB_INT __attribute((visibility("hidden")))
#endif

#endif
