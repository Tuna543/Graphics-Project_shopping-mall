#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "cube.h"



void swinging(Shader& lightingShader, Cube& cube_transparent)
{

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    
    //bar
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 8, -49.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 0.3f, 4.0f));
    model = translateMatrix * scaleMatrix;
    cube_transparent.drawCubeWithTexture(lightingShader, model);

    //front sides
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-15+2.063, 0.5, -49.5));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 7.97f, 0.3f));
    model = translateMatrix * rotateZMatrix * scaleMatrix;
    cube_transparent.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-15 + 2.063, 0.5, -45.8));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 7.97f, 0.3f));
    model = translateMatrix * rotateZMatrix * scaleMatrix;
    cube_transparent.drawCubeWithTexture(lightingShader, model);

    //backside
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-15 - 2.063, 0.5, -49.5));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 7.97f, 0.3f));
    model = translateMatrix * rotateZMatrix * scaleMatrix;
    cube_transparent.drawCubeWithTexture(lightingShader, model);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-15 - 2.063, 0.5, -45.8));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 7.97f, 0.3f));
    model = translateMatrix * rotateZMatrix * scaleMatrix;
    cube_transparent.drawCubeWithTexture(lightingShader, model);
}


void swing_it(Shader& lightingShader, glm::mat4 alTogether, Cube& cube_transparent,Cube& cube_cushion)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    // rotation part 
    //inner rope
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 8, -48.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -5.5f, 0.1f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube_transparent.drawCubeWithTexture(lightingShader, model);
    //time += 0.1;
    //outer rope
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 8, -46.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, -5.5f, 0.1f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube_transparent.drawCubeWithTexture(lightingShader, model);
    //time += 0.1;

    //seat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-16, 2.25, -48.75));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.5f, 2.5f));
    model = alTogether * translateMatrix * scaleMatrix;
    cube_cushion.drawCubeWithTexture(lightingShader, model);

}