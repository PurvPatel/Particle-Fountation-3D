#include "particle3D.h"

particle3D::particle3D(Point3D position, Vec3D direction, std::vector<float> colour, std::vector<float> rot, float size, float speed, int materialType, int age, Shape shape, bool gravity, bool bounciness)
{
    this->position = position;
    this->direction = direction;
    this->colour = colour;
    this->rot = rot;
    this->size = size;
    this->speed = speed;
    this->age = age;
    this->materialType = materialType;
    this->shape = shape;
    this->pastPositions = std::vector<Point3D>();
    this->gravity = gravity;
    this->bounciness = bounciness;
}

void particle3D::addPosition(){
    this->pastPositions.push_back(Point3D(this->position.mX, this->position.mY, this->position.mZ));
}