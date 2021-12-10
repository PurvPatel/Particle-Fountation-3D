#ifndef PARTICLE_3D_H
#define PARTICLE_3D_H

#include <vector>
#include "mathLib3D.h"
#include "material.h"
#include "particleShape.h"

class particle3D{
    public:
    Point3D position;
    Vec3D direction;
    std::vector<float> colour;
    std::vector<float> rot;
    std::vector<Point3D> pastPositions;
    float size;
    float speed;
    int materialType;
    int age;
    Shape shape;
    bool gravity;
    bool bounciness;
    bool transparent;
    
    particle3D(Point3D position, Vec3D direction, std::vector<float> colour, std::vector<float> rot, float size, float speed, int materialType, int age, Shape shape, bool gravity, bool bounciness);
    void addPosition();
};

#endif