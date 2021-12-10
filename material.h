#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>

class Material {
    public:

    float *ambient;
    float *diffuse;
    float *specular;
    float *shininess;

    Material(float *ambient, float *diffuse, float *specular, float *shininess);
};

#endif