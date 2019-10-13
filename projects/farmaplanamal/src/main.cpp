#include <iostream>
#include "unistd.h"
#include "dlfcn.h"

int main()
{
    void* handle = dlopen("./bin/engine.so", RTLD_LAZY);
    typedef int(*engine_game_loop)();

    engine_game_loop GameLoop = (engine_game_loop)dlsym(handle, "perennial::GameLoop");

    if(GameLoop)
        GameLoop();
    else
    {
        printf("Can't find GameLoop symbol.\n");
        return -1;
    }
    
    

}