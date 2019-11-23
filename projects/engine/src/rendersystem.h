//-- Perennial File
//--- Purpose: Rendering system header

#include "GLFW/glfw3.h"

#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

extern GLFWwindow* GameWindow;

void ResizeEvent();

int InitRenderSystem();
int RenderSystem();


#endif
