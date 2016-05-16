#ifndef __HELLO__
#define __HELLO__

#ifdef __cplusplus
extern "C" void hello_message(const char *name);
#else
void hello_message(const char *name);
#endif

#endif