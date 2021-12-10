#include "material.h"

Material::Material(float *ambient, float *diffuse, float *specular, float *shininess){
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->shininess = shininess;
}