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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "particleSystem.h"
#include "particleMaterials.h"

//speeds
float speeds[5] = {0.1, 0.2, 0.3, 0.4, 0.5};

//sizes
float sizes[5] = {0.6, 0.7, 0.8, 0.9, 1.0};

particleSystem::particleSystem(Point3D origin, std::vector<particle3D> particleList, bool isExplosive, bool trail, bool property)
{
    this->origin = origin;
    this->particleList = particleList;
    this->isExplosive = isExplosive;
    this->subSystems = std::vector<particleSystem>();
    this->trail = trail;
    this->property = property;
}

void particleSystem::addRandParticles(int amount, int age, Vec3D initialDirection){
    bool randomDir = false;

    // if no initial direction vector is given, assign random direction (this generates the fountain)
    if(initialDirection.mX == 0 && initialDirection.mY == 0 && initialDirection.mZ == 0){
        randomDir = true;
    }

    for(int i = 0; i < amount; i++){
        if (randomDir)
            this->particleList.push_back(this->getRandParticle(age, Vec3D(((float) rand() / (RAND_MAX))*2 - 1, ((float) rand() / (RAND_MAX)) * 2 + 3, ((float) rand() / (RAND_MAX)) * 2 - 1)));
        else
            this->particleList.push_back(this->getRandParticle(age, initialDirection.normalize()));
    }
}

particle3D particleSystem::getRandParticle(int age, Vec3D initialDirection){
    Point3D position(this->origin.mX, this->origin.mY, this->origin.mZ);

    // assign random direction
    float dirX = ((float) rand() / (RAND_MAX)) * initialDirection.mX;
    float dirY = ((float) rand() / (RAND_MAX)) * initialDirection.mY;
    float dirZ = ((float) rand() / (RAND_MAX)) * initialDirection.mZ;
    Vec3D direction(dirX, dirY, dirZ);

    float speed = speeds[rand() % 5];

    // assign rotation per frame and a rotation angle
    float angle = 8;
    float rotX = ((float) rand()) / RAND_MAX;
    float rotY = ((float) rand()) / RAND_MAX;
    float rotZ = ((float) rand()) / RAND_MAX;
    std::vector<float> rot = {angle, rotX, rotY, rotZ};

    std::vector<float> colour = {float(rand()) / RAND_MAX, float(rand()) / RAND_MAX, float(rand()) / RAND_MAX, 1.0f};

    int materialType = rand() % particleMaterials.size();

    float size = sizes[rand() % 5];

    Shape shape =  static_cast<Shape> (rand() % 3);

    // assign properties
    bool gravity = rand() % 2 == 0;
    bool bounciness = rand() % 2 == 0;

    return particle3D(position, direction, colour, rot, size, speed, materialType, age, shape, gravity, bounciness);

}

void particleSystem::updateParticleMovements(Vec3D updateDirection, float platformX, float platformZ, bool friction){
    for(auto &particle : this->particleList){
        //apply no vertical force if particle does not have gravity property and particle properties are turned on
        if(!(particle.gravity || !this->property)){
            Vec3D temp(updateDirection.mX, 0, updateDirection.mZ);
            particle.direction = particle.direction.add(temp);
        }
        else
            particle.direction = particle.direction.add(updateDirection);
        particle.position.mX += particle.direction.multiply(particle.speed).mX;
        particle.position.mZ += particle.direction.multiply(particle.speed).mZ;

        //apply properties if particle properties are on
        if(particle.gravity || !this->property){
            float yVal = particle.position.mY + particle.direction.multiply(particle.speed).mY;
            if (yVal <= 0 && -platformX <= particle.position.mX && particle.position.mX <= platformX && -platformZ <= particle.position.mZ && particle.position.mZ <= platformZ){
                particle.direction.mY = - particle.direction.mY;
                if (particle.bounciness && this->property)
                    particle.speed += particle.speed * 0.15;
                if (friction)
                    particle.speed -= particle.speed * 0.1;
                
            }
            particle.position.mY += particle.direction.multiply(particle.speed).mY;
        }
        
        //decrement particle age
        particle.age -= 1;

        //add past particle movements if trail is set
        if(trail){
            //sample every 2 ticks and keep track of max 30 past positions
            if (particle.age % 2 == 0){
                particle.addPosition();
                if(particle.pastPositions.size() >= 30){
                    particle.pastPositions.erase(particle.pastPositions.begin());
                }
            }
        }else{
            //make room for newer history
            particle.pastPositions.clear();
        }

        //update rotation values
        particle.rot[0] = (particle.rot[0] + 8) >= 360 ? particle.rot[0] - 352 : particle.rot[0] + 8;
    }
    for(auto &subSystem : this->subSystems){
        subSystem.trail = this->trail;
        subSystem.updateParticleMovements(updateDirection, platformX, platformZ, friction);
    }
}


void particleSystem::display(){
    for(auto &particle : this->particleList){
        //draw particle
		glPushMatrix();
			glColor4fv(particle.colour.data());

			glTranslatef(particle.position.mX, particle.position.mY, particle.position.mZ);
            glRotatef(particle.rot[0], particle.rot[1], particle.rot[2], particle.rot[3]);

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, particleMaterials[particle.materialType].ambient);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, particleMaterials[particle.materialType].diffuse);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, particleMaterials[particle.materialType].specular);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, particleMaterials[particle.materialType].shininess);

			if (particle.shape == Teapot)
				glutSolidTeapot(particle.size);
			else if (particle.shape == Cube)
				glutSolidCube(particle.size);
			else if (particle.shape == Sphere)
				glutSolidSphere(particle.size, 10, 10);
		glPopMatrix();

        glPushMatrix();
        
        //draw trail if particle trails are on
        if(trail && particle.pastPositions.size() > 0){
            glBegin(GL_LINE_STRIP);
            glColor4fv(particle.colour.data());
                for(auto &pastPostion : particle.pastPositions){
                    glVertex4f(pastPostion.mX, pastPostion.mY, pastPostion.mZ, 1.0f);
                }
            glEnd();
        }

        glPopMatrix();
        
	}

    this->removeEOLParticles();

    for(auto &subSystem : this->subSystems)
    {
        subSystem.display();
        subSystem.removeEOLParticles();
    }
}

void particleSystem::removeEOLParticles(){
    int n = this->particleList.size() - 1;

    for (int i = n; i >= 0; i--){
        if(this->particleList[i].age <= 0 || this->particleList[i].position.mY <= -50){
            if(this->isExplosive){
                this->subSystems.push_back(particleSystem(this->particleList[i].position, std::vector<particle3D>(), false, this->trail, false));
                this->subSystems.back().addRandParticles(5, 180, Vec3D(0, 0, 0));
            }
            this->particleList.erase(this->particleList.begin() + i);
            
        }
            
    }
}