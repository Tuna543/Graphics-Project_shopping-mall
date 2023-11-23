#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "cube.h"
#include "staircube.h"

void counter_draw(Shader& lightingShader, Cube& cube_brown, Cube& cube_black)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    float k = 0.0;
    for (int i = 0; i < 4; i++) {
        //nicher base
        translateMatrix = glm::translate(identityMatrix, glm::vec3(20, 0.5, -37+k));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(7, 1.5, 1));
        model =translateMatrix * scaleMatrix;
        cube_brown.drawCubeWithTexture(lightingShader, model);

        //uporer black part
        translateMatrix = glm::translate(identityMatrix, glm::vec3(20, 2, -37 + k));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(7, .25, 1));
        model = translateMatrix * scaleMatrix;
        cube_black.drawCubeWithTexture(lightingShader, model);

        k += 10.0;
    }


    //restaurant counter
    //samner dike jei part agay ashche
    //nicher base
    translateMatrix = glm::translate(identityMatrix, glm::vec3(25, 10.5, -48.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1.5, 10));
    model = translateMatrix * scaleMatrix;
    cube_brown.drawCubeWithTexture(lightingShader, model);

    //uporer black part
    translateMatrix = glm::translate(identityMatrix, glm::vec3(25, 12, -48.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, .25, 10));
    model = translateMatrix * scaleMatrix;
    cube_black.drawCubeWithTexture(lightingShader, model);


    //x axis er dike align jei part
    //nicher base
    translateMatrix = glm::translate(identityMatrix, glm::vec3(25, 10.5, -39.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5, 1.5, 1));
    model = translateMatrix * scaleMatrix;
    cube_brown.drawCubeWithTexture(lightingShader, model);

    //uporer black part
    translateMatrix = glm::translate(identityMatrix, glm::vec3(26, 12, -39.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4, .25, 1));
    model = translateMatrix * scaleMatrix;
    cube_black.drawCubeWithTexture(lightingShader, model);


}
