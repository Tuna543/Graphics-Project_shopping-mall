#pragma once
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "staircube.h"
#include "escalatorrail.h"

void escalator_moves(Shader& lightingShader, Staircube& cube1, Esc& escc, float y, float z, float down_y, float down_z)
{

    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, scaleMatrixY;

    
    //midpoints of stairs; left side staircases
    float j = 0.0;
    float k = 0.0;
    float y1 = y + j;
    float z1 = z - k;
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3, 1, 1));
    scaleMatrixY = glm::scale(identityMatrix, glm::vec3(-3, 1, 1));
    translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5, 9.5, -21));
    model = translateMatrix * scaleMatrix;
    cube1.drawStaircubeWithTexture(lightingShader, model);
    
    translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5, -0.4, -11));
    model = translateMatrix * scaleMatrix;
    cube1.drawStaircubeWithTexture(lightingShader, model);
    


    translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5, 9.5, -21));
    model = translateMatrix * scaleMatrixY;
    cube1.drawStaircubeWithTexture(lightingShader, model);
    
    translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5, -0.4, -11));
    model = translateMatrix * scaleMatrixY;
    cube1.drawStaircubeWithTexture(lightingShader, model);


    for (int i = 0; i < 11; i++) {
        
        if (y+j <= 0.5) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5, y, z-k-1));
            model = translateMatrix * scaleMatrix;
            cube1.drawStaircubeWithTexture(lightingShader, model);
            
        }
        
        if (y + j >= 9.5) {
            //if (z - k <= -11) {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5, y, z - k-1));
                model = translateMatrix * scaleMatrix;
                cube1.drawStaircubeWithTexture(lightingShader, model);
                
            /* }
            else {
                y = -.5;
                z = -10.0;
            }*/
        }
        else {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(5.5, y+j, z-k-1));
            model = translateMatrix * scaleMatrix;
            cube1.drawStaircubeWithTexture(lightingShader, model);
            
        }
        j += 1;
        k += 1;
    }

    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-3, 1, 1));

    y = y * -1;
    z = z * -1;
    for (int i = 0; i < 11; i++) {

        if (y + j <= -0.5) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5, y-12, z - k-10));
            model = translateMatrix * scaleMatrix;
            cube1.drawStaircubeWithTexture(lightingShader, model);
        }

        if (y + j <= 9.5) {
            //if (z - k <= -11) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5, y-12, z - k-10));
            model = translateMatrix * scaleMatrix;
            cube1.drawStaircubeWithTexture(lightingShader, model);
            /* }
            else {
                y = -.5;
                z = -10.0;
            }*/
        }
        else {
            //cout << "yes\n";
            translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5, y + j-12, z - k-10));
            model = translateMatrix * scaleMatrix;
            cube1.drawStaircubeWithTexture(lightingShader, model);
        }
        j += 1;
        k += 1;
    }
    
    /*
    j = 10;;
    k = -10;
    //down wards
    for (int i = 0; i < 11; i++) {

        if (down_y + j <= 0.5) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5, down_y, down_z + k));
            model = translateMatrix * scaleMatrix;
            cube1.drawStaircubeWithTexture(lightingShader, model);
        }

        if (down_y + j >= 9.5) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5, down_y, down_z + k));
            model = translateMatrix * scaleMatrix;
            cube1.drawStaircubeWithTexture(lightingShader, model);
            
        }
        else {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5, down_y + j, down_z + k));
            model = translateMatrix * scaleMatrix;
            cube1.drawStaircubeWithTexture(lightingShader, model);
        }
        j -= 1;
        k += 1;
    }
    */
    /*
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

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-16.75, 25.5 + j, -13.5 + k));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        cube1.drawStaircubeWithTexture(lightingShader, model);

        j += .5;
        k += .5;
    }
    */
}


#pragma once

#pragma once
