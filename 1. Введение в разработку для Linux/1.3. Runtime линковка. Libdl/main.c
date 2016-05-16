#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <dlfcn.h>

void (*hello_message)(const char *);

bool init_library()
{
    void *hdl = dlopen("./libHello.so", RTLD_LAZY);
    if(NULL == hdl)
        return false;

    hello_message = (void(*)(const char *))dlsym(hdl, "hello_message");
    if(NULL == hello_message)
        return false;

    return true;
}

int main()
{
    if(init_library())
        hello_message("Vasya");
    else
        printf("Library was not loaded\n");
    return 0;
}