#include <iostream>
#include "unistd.h"
#include "dlfcn.h"

int main()
{
    void* handle = dlopen("bin/engine.so", RTLD_LAZY);
    typedef int(*engineloop)();

    engineloop GameLoop = (engineloop)dlsym(handle, "PerennialMain");

    if(GameLoop)
        GameLoop();
    else
    {
        printf("Can't find PerennialMain symbol.\n");
        return -1;
    }
    
    

}
