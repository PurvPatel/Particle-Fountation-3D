#ifndef WALL_MATERIALS_H
#define WALL_MATERIALS_H

#include "material.h"

//Jade
float jadeAmb[] = { 0.135f, 0.2225f, 0.1575f, 0.95f };
float jadeDif[] = { 0.54f, 0.89f, 0.63f, 0.95f };
float jadeSpc[] = { 0.316228f, 0.316228f, 0.316228f, 0.95f };
float jadeShi[] = { 12.8f };

Material const jade(jadeAmb, jadeDif, jadeSpc, jadeShi);

std::vector<Material> const wallMaterials = {jade};

#endif