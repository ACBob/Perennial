//-- Perennial File
//--- Purpose: Define entry points

//Includes
#include <stdio.h>
//#include <thread>
#include "rendersystem.h"
#include "p_main.h"

// p_main
//- Returns INT
//- Entry Point
int PerennialMain()
{

	//Should we hard-code version number?
	printf("Perennial (V0.0)\n");
    InitRenderSystem(); //Init sets stuff
    //std::thread RenderThread(RenderSystem); //Run the render loop
    
    //RenderThread.join();

    RenderSystem();

    return 0;
}
