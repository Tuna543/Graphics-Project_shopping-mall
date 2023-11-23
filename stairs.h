#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "staircube.h"
#include "cylinder.h"

void stair(Shader& lightingShader, Cylinder& cylinder , Staircube& cube1)
{

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    
    //midpoints of stairs; left side staircases
    float j = 0.0;
    float k = 0.0;
    for (int i = 0; i < 10; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, .5 + j, -9.5 - k));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, .5, .5));
        model = translateMatrix * scaleMatrix;
        cube1.drawStaircubeWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, 10.5 + j, -9.5 - k));
        model = translateMatrix * scaleMatrix;
        cube1.drawStaircubeWithTexture(lightingShader, model);
        /*
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, 20.5 + j, -9.5 - k));
        model = translateMatrix * scaleMatrix;
        cube1.drawStaircubeWithTexture(lightingShader, model);
        */
        j += .5;
        k += .5;
    }

    //midpoints of stairs; right side staircases
    j = 0.0;
    k = 0.0;
    float rotateAngle_Y = 180.0;
    for (int i = 0; i < 10; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.75, 5.5 + j, -13.5 + k));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, .5, .5));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        cube1.drawStaircubeWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.75, 15.5 + j, -13.5 + k));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        cube1.drawStaircubeWithTexture(lightingShader, model);
        /*
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.75, 25.5 + j, -13.5 + k));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        cube1.drawStaircubeWithTexture(lightingShader, model);
        */
        j += .5;
        k += .5;
    }

    //stair_railings
    //for right stairs
    j = 0.0;
    k = 0.0;
    for (int i = 0; i < 10; i++) {
        //ground floor
        //floor side
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.85, 6.5 + j, -13.75 + k));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, .5, .05));
        model = translateMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model); 
        //stair side
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.15, 6.5 + j, -13.75 + k));
        model = translateMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);

        //2nd floor
        //floor side
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.85, 16.5 + j, -13.75 + k));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);
        //stair side
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.15, 16.5 + j, -13.75 + k));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);
/*
        //2nd floor
        //floor side
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.85, 26.5 + j, -13.75 + k));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);
        //stair side
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.15, 26.5 + j, -13.75 + k));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);
        */
        j += .5;
        k += .5;
    }


    //stair_railings
    //for left stairs
    j = 0.0;
    k = 0.0;
    for (int i = 0; i < 10; i++) {
        //ground stair side
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.35, 1.5 + j, -9.25 - k));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, .5, .05));
        model = translateMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);
        //second floor stair side
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.35, 11.5 + j, -9.25 - k));
        model = translateMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);
        /*
        //third floor stair side
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.35, 21.5 + j, -9.25 - k));
        model = translateMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);
        */
        j += .5;
        k += .5;
    }

    //stair floor railing
    float m=0.0,n=0.0;
    for (int i = 0; i < 1; i = i + 1) {
        m = 0.0;
        for (int j = 0; j < 16; j++) {
            //pichon theke samne
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.65, 11.0 + n, -17.0+m));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, .5, .05));
            model = translateMatrix * scaleMatrix;
            cylinder.drawCylinderWithTexture(lightingShader, model);
            m += .5;

        }
        n += 10;
    }

    //stair mid floor railing
    m = 0.0, n = 0.0;
    for (int i = 0; i < 2; i = i + 1) {
        m = 0.0;
        for (int j = 0; j < 6; j++) {
            //pichon theke samne
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.85, 6.0 + n, -16.75 + m));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, .5, .05));
            model = translateMatrix * scaleMatrix;
            cylinder.drawCylinderWithTexture(lightingShader, model);
            
            //from left to right
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.6+m, 6.0 + n, -16.75));
            model = translateMatrix * scaleMatrix;
            cylinder.drawCylinderWithTexture(lightingShader, model);
            
            if (i < 2) {
                //from left to right; original floor railing
                translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.6 + m, 11.0 + n, -17.25));
                model = translateMatrix * scaleMatrix;
                cylinder.drawCylinderWithTexture(lightingShader, model);

            }
            m += .5;
        }
        n += 10;
    }
    
    //stair lomba railing
    m = 0.0;
    float rotateAngle_X = -45.0;
    float rotateAngle_Z = 90.0;

    for (int i = 0; i < 2; i++) {
        //for left side stairs
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.35, 4.25 + m, -11.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, 3.5, .05));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        model = translateMatrix * rotateXMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);

        //for right side stairs
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.85, 9.25 + m, -11.5));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X*-1), glm::vec3(1.0f, 0.0f, 0.0f));
        model = translateMatrix * rotateXMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);
        //for right side stair side railing
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.15, 9.25 + m, -11.5));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X * -1), glm::vec3(1.0f, 0.0f, 0.0f));
        model = translateMatrix * rotateXMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);

        //for mid floors
        //pichon theke samne
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.85, 6.5 + m, -15.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, 1.5, .05));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z ), glm::vec3(1.0f, 0.0f, 0.0f));
        model = translateMatrix * rotateXMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);
        
        //for mid floors
        //left to right
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.25, 6.5 + m, -16.75));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z ), glm::vec3(0.0f, 0.0f, 1.0f));
        model = translateMatrix * rotateZMatrix * scaleMatrix;
        cylinder.drawCylinderWithTexture(lightingShader, model);
        
        
        //for floors
        //left to right
        if (i < 1) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.25, 11.5 + m, -17.25));
            rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
            model = translateMatrix * rotateZMatrix * scaleMatrix;
            cylinder.drawCylinderWithTexture(lightingShader, model);

            //pichon theke samne
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.65, 11.5 + m, -13.35));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, 4, .05));
            rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(1.0f, 0.0f, 0.0f));
            model = translateMatrix * rotateXMatrix * scaleMatrix;
            cylinder.drawCylinderWithTexture(lightingShader, model);

        }

        m += 10;
    }

    //slub under stair
    /*
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
    }*/
}


#pragma once

#pragma once
