#include <stdio.h>
#include "rendersystem/opengltoucher.h"
#include "io/input.h"
#include "game.h"

namespace perennial{

    bool GameRunning = false;

    int GameLoop()
    {
        if(perennial::rendering::Init())
        {

            return -1;

        }
        
        GameRunning = true;

        while(GameRunning)
        {

            perennial::rendering::Frame();
            perennial::input::ProcessInput();
            if(perennial::input::CheckClose()) //Check if we're supposed to close.
            {
                GameRunning = false;
            }

        }
        return 0;

    }

}