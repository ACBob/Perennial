#include <iostream>
#include "unistd.h"
#include "dlfcn.h"

int main()
{
    void* handle = dlopen("bin/engine.so", RTLD_NOW);
    if (handle == NULL)
    {
        printf("Error!\n");
        printf(dlerror());
        printf("\n");
        return -1;
    }
    typedef int(*engineloop)();

    engineloop GameLoop = (engineloop)dlsym(handle, "PerennialMain");

    if(GameLoop)
        GameLoop();
    else
    {
        printf("Error!\n");
        printf(dlerror());
        printf("\n");
        return -1;
    }
    
    

}
