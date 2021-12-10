#ifndef LIGHT_CONSTANTS_H
#define LIGHT_CONSTANTS_H

#include "light.h"

float light0Pos[4] = {100,100,100, 1};
float light0Amb[4] = {0,0,0,1};
float light0Dif[4] = {1,1,1,1};
float light0Spc[4] = {1,1,1,1};

Light const light0(GL_LIGHT0, light0Pos, light0Amb, light0Dif, light0Spc);

float light1Pos[4] = {0,100,100, 1};
float light1Amb[4] = {0,0,0,1};
float light1Dif[4] = {1,1,1,1};
float light1Spc[4] = {1,1,1,1};

Light const light1(GL_LIGHT1, light1Pos, light1Amb, light1Dif, light1Spc);

#endif