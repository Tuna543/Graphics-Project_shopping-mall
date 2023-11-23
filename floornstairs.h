#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "cube.h"
#include "staircube.h"

void floor_stairs(Shader& lightingShader, Cube& cube)
{

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    
    //Ground floor;      start=-.5       finish = 0.5=>floor top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, -.5, -50));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(49.75, 1, 50));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //second floor;      start=10.5       finish = 11=>floor top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.75, 10, -50));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(46.75, .5, 29.0));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //second floor;      start=10.5       finish = 11=>floor top
    //left side
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.75, 10, -21));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(11.75, .5, 21.0));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);
    //right side
    translateMatrix = glm::translate(identityMatrix, glm::vec3(15, 10, -21));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(15, .5, 21.0));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);



    //third floor;      start=20.5       finish = 21=>floor top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.75, 20, -50));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(46.75, .5, 49.75));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //stairs
    //stair mid floor
    float j = 0;
    for (int i = 0; i < 2; i = i + 1) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, 5.0 + j, -17.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(3, .5, 3));
        model = translateMatrix * scaleMatrix;
        cube.drawCubeWithTexture(lightingShader, model);
        j += 10;
    }
    //stairfloor connected with floor
    j = 0;
    float samner_choto_part = 3;
    for (int i = 0; i < 2; i = i + 1) {
        //samner choto part
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, 10 + j, -9));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(3, .5, samner_choto_part));
        model = translateMatrix * scaleMatrix;
        cube.drawCubeWithTexture(lightingShader, model);

        //pichoner lomba part
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, 10 + j, -50));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(3, .5, 33));
        model = translateMatrix * scaleMatrix;
        cube.drawCubeWithTexture(lightingShader, model);

        samner_choto_part = 9;
        j += 10;
    }

    /*
    //slub under stair
    
    j = 0.0;
    k = 0.0;
    float rotateAngle_X = 45.0;
    for (int i = 0; i < 3; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, 5.25 + j, -14.1));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, .25, 6.9));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        model = translateMatrix * rotateXMatrix * scaleMatrix;
        cube.drawCubeWithTexture(lightingShader, model);


        j += 10;
    }
    */
}


#pragma once
