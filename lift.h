#pragma once
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "cube.h"



void liftwalls(Shader& lightingShader, Cube& cube_wall)
{

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    
    //left side wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, 0.5, -6));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 20.0f, 1.5f));
    model = translateMatrix * scaleMatrix;
    cube_wall.drawCubeWithMaterialisticProperty(lightingShader, model);
    
    //right side wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, 0.5, -1.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0f, 20.0f, 1.5f));
    model = translateMatrix * scaleMatrix;
    cube_wall.drawCubeWithMaterialisticProperty(lightingShader, model);

    //upper wall of the lift
    float j = 0.0;
    for (int i = 0; i < 2; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-17.25, 10+j, -6));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, -3.0f, 6.0f));
        model = translateMatrix * scaleMatrix;
        cube_wall.drawCubeWithMaterialisticProperty(lightingShader, model);
        j += 10;
    }
}

void open_lift_door(Shader& lightingShader, Cube& cube_door,float y, float x, float j)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-17.125, y, x + j));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25, 6.5, 1.625));
    model = translateMatrix * scaleMatrix;
    cube_door.drawCubeWithMaterialisticProperty(lightingShader, model);

}

void take_lift_to_floors(Shader& lightingShader, Cube& cube_box, float y, float j)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //lift box

    //backside of lift
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, y, -4.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25, 6.5, 3));
    model = translateMatrix * scaleMatrix;
    cube_box.drawCubeWithMaterialisticProperty(lightingShader, model);

    //left side of lift
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.5, y, -1.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.375, 6.5, -.25));
    model = translateMatrix * scaleMatrix;
    cube_box.drawCubeWithMaterialisticProperty(lightingShader, model);

    //right side of lift
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.5, y, -4.45));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.375, 6.5, -.25));
    model = translateMatrix * scaleMatrix;
    cube_box.drawCubeWithMaterialisticProperty(lightingShader, model);

    //top of lift
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.5, y+6.5, -4.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.375, .25, 3));
    model = translateMatrix * scaleMatrix;
    cube_box.drawCubeWithMaterialisticProperty(lightingShader, model);

    //bottom/floor of lift
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.5, y-.24, -4.5));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.375, .25, 3));
    model = translateMatrix * scaleMatrix;
    cube_box.drawCubeWithMaterialisticProperty(lightingShader, model);

}