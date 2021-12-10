#ifndef LIGHT_H
#define LIGHT_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

class Light {
    public:

    GLenum LIGHT_NUM;
    float *position;
    float *ambient;
    float *diffuse;
    float *specular;

    Light(GLenum LIGHT_NUM, float *postion, float *ambient, float *diffuse, float *specular);
};

#endif