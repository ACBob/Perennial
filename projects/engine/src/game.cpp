#include <stdio.h>
#include "rendersystem/opengltoucher.h"
#include "io/input.h"
#include <iostream>
#include "game.h"

namespace perennial{

	bool bGameRunning = false;

	int i_gameLoop()
	{
		if(perennial::rendering::i_init())
		{

			return -1;

		}
		
		bGameRunning = true;

		while(bGameRunning)
		{
			perennial::rendering::frame();
			if(perennial::input::b_checkClose()) //Check if we're supposed to close.
			{
				bGameRunning = false;
			}

		}
		return 0;

	}

}
