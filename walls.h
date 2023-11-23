#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "cube.h"


void walls(Shader& lightingShader, Cube& cube)
{

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;


    // Create the glm::vec3 objects for ambient, diffuse, and specular, and a float for shininess.
    /*
    glm::vec3 ambientColor(1.0f, 1.0f, 1.0f);
    glm::vec3 diffuseColor(1.0f, 1.0f, 1.0f);
    glm::vec3 specularColor(1.0f, 1.0f, 1.0f);
    float shininessValue = 52.0f;

    // Create an instance of the Cube class and call its constructor.
    Cube cube=Cube(ambientColor, diffuseColor, specularColor, shininessValue);
    */

    //pichoner lomba part
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, 20.5, -50+33));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3, 2, -.5));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithMaterialisticProperty(lightingShader, model);

    //samner choto part
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, 20.5, -9));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3, 2, .25));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithMaterialisticProperty(lightingShader, model);

    //samner choto part
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75+3, 20.5, -50+33));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25, 2, .25));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithMaterialisticProperty(lightingShader, model);

    //samner choto part
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, 20.5, -50 + 33));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3, 2, 8));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithMaterialisticProperty(lightingShader, model);


    //translateMatrix = glm::translate(identityMatrix, glm::vec3(-20, -0.5, 0.0));
    //building walls
    //left side wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-20, 0.5, -50));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25, 22, 50));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithMaterialisticProperty(lightingShader, model);
    //right side wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(30, 0.5, -50));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 22, 50));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithMaterialisticProperty(lightingShader, model);
    //back side wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-20, 0.5, -50.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, 22, 0.25));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithMaterialisticProperty(lightingShader, model);
    //front wall
    //back side wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-20, 20.5, -0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(50, 2, 0.25));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithMaterialisticProperty(lightingShader, model);

    /*
    //ceiling
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-20, 30, -50.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(50.25, .5, 50.25));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithMaterialisticProperty(lightingShader, model);
    */
    /*
    //walls for stairs
    // beside stairs
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.75, 0.5, -17));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25, 30, 7.5));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithMaterialisticProperty(lightingShader, model);
    // behind stairs
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, 0.5, -17.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(10, 30, .25));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithMaterialisticProperty(lightingShader, model);
    */
    //shops walls
    float scale_y = 9.95; 
    float j = 0.0;
    for (int i = 0; i < 4; i++) {
        
        //right side shops
        translateMatrix = glm::translate(identityMatrix, glm::vec3(19, 0.5, -40 + j));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(11, scale_y, .25));
        model = translateMatrix * scaleMatrix;
        cube.drawCubeWithMaterialisticProperty(lightingShader, model);
        j += 10;
        scale_y = 19.95;
    }

    j = 0.0;
    j += 15;

    float scale_left_shop = 9.95;
    for (int i = 0; i < 1; i++) {
        //left side shops
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, 0.5, -20.25));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.75, scale_left_shop, .25));
        model = translateMatrix * scaleMatrix;
        cube.drawCubeWithMaterialisticProperty(lightingShader, model);
       // scale_left_shop = 19.95;
    }
    for (int i = 0; i < 1; i++) {
        //left side shops
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, 10.5, -18.25));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.75, scale_left_shop, .25));
        model = translateMatrix * scaleMatrix;
        cube.drawCubeWithMaterialisticProperty(lightingShader, model);
        // scale_left_shop = 19.95;
    }


    //second floor;      start=10.5       finish = 11=>floor top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.75+11.75, 10.5, -50+29.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.5, 2.5, -.25));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithMaterialisticProperty(lightingShader, model);
    //second floor;      start=10.5       finish = 11=>floor top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(8.5, 10.5, -50 + 29.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.5, 2.5, -.25));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithMaterialisticProperty(lightingShader, model);


    //second floor;      start=10.5       finish = 11=>floor top
    //left side
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.75+11.75, 10.5, -21));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25, 2.5, 21.0));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithMaterialisticProperty(lightingShader, model);
    //right side
    translateMatrix = glm::translate(identityMatrix, glm::vec3(15, 10.5, -21));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25, 2.5, 21.0));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithMaterialisticProperty(lightingShader, model);

    /*
    //walls beside lift
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, 10.5 + j, -9));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3, 0.25, 3));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithMaterialisticProperty(lightingShader, model);
    */



}



#pragma once