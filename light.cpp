#include "light.h"

Light::Light(GLenum LIGHT_NUM, float *position, float *ambient, float *diffuse, float *specular){
    this->LIGHT_NUM = LIGHT_NUM;
    this->position = position;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}