#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <vector>
#include "mathLib3D.h"
#include "particle3D.h"
#include "particleShape.h"

class particleSystem{
    public:
    Point3D origin;
    bool isExplosive;
    bool trail;
    bool property;
    std::vector<particleSystem> subSystems;
    std::vector<particle3D> particleList;
    
    particleSystem(Point3D origin, std::vector<particle3D> particleList, bool isExplosive, bool trail, bool property);
    void addRandParticles(int amount, int age, Vec3D initialDirection);
    particle3D getRandParticle(int age, Vec3D initialDirection);
    void updateParticleMovements(Vec3D updateDirection, float platformX, float platformZ, bool friction);
    void display();
    void removeEOLParticles();
};

#endif