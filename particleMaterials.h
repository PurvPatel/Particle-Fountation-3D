#ifndef PARTICLE_MATERIALS_H
#define PARTICLE_MATERIALS_H

#include "material.h"

//brass
float brassAmb[] = { 0.329412f, 0.223529f, 0.027451f, 1.0f };
float brassDif[] = { 0.780392f, 0.568627f, 0.113725f, 1.0f };
float brassSpc[] = { 0.992157f, 0.941176f, 0.807843f, 1.0f };
float brassShi[] = { 27.8974f };

Material const brass(brassAmb, brassDif, brassSpc, brassShi);

//red plastic
float redPlasticAmb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
float redPlasticDif[] = { 0.5f, 0.0f, 0.0f, 1.0f };
float redPlasticSpc[] = { 0.7f, 0.6f, 0.6f, 1.0f };
float redPlasticShi[] = { 32.0f };

Material const redPlastic(redPlasticAmb, redPlasticDif, redPlasticSpc, redPlasticShi);

//White rubber
float whiteRubberAmb[] = { 0.05f, 0.05f, 0.05f, 1.0f };
float whiteRubberDif[] = { 0.5f, 0.5f, 0.5f, 1.0f };
float whiteRubberSpc[] = { 0.7f, 0.7f, 0.7f, 1.0f };
float whiteRubberShi[] = { 10.0f };

Material const whiteRubber(whiteRubberAmb, whiteRubberDif, whiteRubberSpc, whiteRubberShi);

std::vector<Material> const particleMaterials = {brass, redPlastic, whiteRubber};

#endif