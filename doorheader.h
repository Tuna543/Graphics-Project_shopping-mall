#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "cube.h"



void door_bar(Shader& lightingShader,  Cube& cube)
{

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    float x = 0.0, y = 0.0;
    x = 0.0;
    for (int i = 0; i < 4; i++) {

        //bar
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75 + x, .5 + y, 0 - .25));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 10.0f, 0.25f));
        model = translateMatrix * scaleMatrix;
        cube.drawCubeWithTexture(lightingShader, model);
        x += 5;
    }
    x += 10;
    for (int i = 6; i < 10; i++) {

        //bar
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75 + x, .5 + y, 0 - .25));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 10.0f, 0.25f));
        model = translateMatrix * scaleMatrix;
        cube.drawCubeWithTexture(lightingShader, model);
        x += 5;
    }
    x = 0.0;
    y += 10;
    for (int i = 0; i < 10; i++) {

        //bar
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75 + x, .5 + y, 0 - .25));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 10.0f, 0.25f));
        model = translateMatrix * scaleMatrix;
        cube.drawCubeWithTexture(lightingShader, model);
        x += 5;
    }

    //inner doors
    x = 0.0;
    y = 0.0;
    float z = 0.0;
    for (int j = 0; j < 2; j++) {
        x = 0.0;
        for (int i = 0; i < 8; i++) {
            if (i == 3) {
                i++;
                x += 4;
                continue;
            }
            //bar
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-9.0 + x, .5 + y, -40+z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 9.5f, 0.25f));
            model = translateMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);
            x += 4;
        }
        y += 10;
        z += 10;
    }
    
    //left side shops
    //for first floor
    z = 0.0;
    for (int i = 0; i < 4; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(19, .5, -40 + z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 9.5f, 0.25f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        cube.drawCubeWithTexture(lightingShader, model);
        z += 10;
    }
    //for second floor
    z = 0.0;
    for (int i = 0; i < 3; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(19, 10.5, -30 + z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 9.5f, 0.25f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        cube.drawCubeWithTexture(lightingShader, model);
        z += 10;
    }

    //for right side=================sealed
    z = 0.0;
    y = 0.0;
        z = 0.0;
        for (int i = 0; i < 5; i++) {
            
            //bar
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-9.0, .5 + y, -40 + z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 9.5f, 0.25f));
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model = translateMatrix * rotateYMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);
            z += 4;
        }

    //second floor
        y += 10.0;
        z = 0.0;
        for (int i = 0; i < 3; i++) {

            //bar
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-9.0, .5 + y, -30 + z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 9.5f, 0.25f));
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model = translateMatrix * rotateYMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);
            z += 4;
        }

}

void open_door(Shader& lightingShader, Cube& cube_transparent, float r)
{

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;


    translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75 + 20, .5 , 0 - .25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 10.0f, 0.25f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    cube_transparent.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75 + 30, .5, 0 - .25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-5.0f, 10.0f, 0.25f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-r), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    cube_transparent.drawCubeWithTexture(lightingShader, model);

    float y = 0, z = 0.0;
    //restaurants and kids
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < 8; i++) {
            
            //bar
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-9.0+12 , .5 + y, -40 + z));
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r/2), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 9.5f, 0.25f));
            model = translateMatrix * rotateYMatrix * scaleMatrix;
            cube_transparent.drawCubeWithTexture(lightingShader, model);
            
        }
        y += 10;
        z += 10;
    }



    //for shops first floor
    z = 0.0;
    for (int i = 0; i < 4; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(19.25, .5, -35-(r/25) + z ));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 9.5f, 0.25f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        cube_transparent.drawCubeWithTexture(lightingShader, model);
        z += 10;
    }

    //for second floor
    z = 0.0;
    for (int i = 0; i < 3; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(19.25, 10.5, -25 - (r / 25) + z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 9.5f, 0.25f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        cube_transparent.drawCubeWithTexture(lightingShader, model);
        z += 10;
    }
}

void open_shops(Shader& lightingShader, Cube& cube_transparent, float r)
{

}