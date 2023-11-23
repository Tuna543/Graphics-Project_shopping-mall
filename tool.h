#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "cylinder.h"

void tools( Shader& lightingShader, Cylinder& cylinder, Cylinder& cylinder3)
{

    float rotateAngle_Y = 0.0;


    //glm::mat4 rotateY = glm::mat4(1.0f);
    //glm::mat4 rotateZ = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    
    
    //base
    float m = 0.0,n=0.0,o=0.0;
    for (int i = 0; i < 1; i++) {
        o = 0.0;
        for (int k = 0; k < 4; k++) {
            m = 0.0;
            for (int i = 0; i < 5; i++) {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(26 - m, 1.6+n, -31 + o));//put center points
                //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y ), glm::vec3(0.0f, 1.0f, 0.0f));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.1, 0.5));
                model = translateMatrix * scaleMatrix;
                cylinder.drawCylinderWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
                m += 1.3;
            }
            o += 10;
        }
        n += 10;
    }
    
    //leg 1
    m = 0.0, n = 0.0, o = 0.0;
    for (int j = 0; j < 1; j++) {
        o = 0.0;
        for (int k = 0; k < 4; k++) {
            m = 0.0;
            for (int i = 0; i < 5; i++) {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(26 - m, 1+n, -31 + o));//put center points
                //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.09, 0.5, 0.09));
                model = translateMatrix * scaleMatrix;
                cylinder3.drawCylinderWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
                m += 1.3;
            }
            o += 10;
        }
        n += 10;
    }

    //second floor
    //base
    m = 0.0, n = 10.0, o = 0.0;
    for (int i = 0; i < 1; i++) {
        o = 0.0;
        for (int k = 0; k < 3; k++) {
            m = 0.0;
            for (int i = 0; i < 5; i++) {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(26 - m, 1.6 + n, -21 + o));//put center points
                //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y ), glm::vec3(0.0f, 1.0f, 0.0f));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5, 0.1, 0.5));
                model = translateMatrix * scaleMatrix;
                cylinder.drawCylinderWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
                m += 1.3;
            }
            o += 10;
        }
    }

    //leg 1
    m = 0.0, n = 10.0, o = 0.0;
    for (int j = 0; j < 1; j++) {
        o = 0.0;
        for (int k = 0; k < 3; k++) {
            m = 0.0;
            for (int i = 0; i < 5; i++) {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(26 - m, 1 + n, -21 + o));//put center points
                //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.09, 0.5, 0.09));
                model = translateMatrix * scaleMatrix;
                cylinder3.drawCylinderWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
                m += 1.3;
            }
            o += 10;
        }
    }

    /*
    //dolls
    float m = 0.0, n = 0.0, o = 0.0;
    for (int k = 0; k < 4; k++) {
        m = 0.0;
        for (int i = 0; i < 5; i++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(26 - m, 1, -31 + o));//put center points
            //rotateZMatrix = glm::rotate(identityMatrix, glm::radians(30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.9, 1.5, 0.9));
            model = translateMatrix * scaleMatrix;
            barbie.drawCylinderWithTexture(lightingShader, model); //this model is later sent to the vertex shader. //altogether is a matrix that is multiplied with every parts of the bed, so everything is part of Altogether. when rotated, everything is rotated AllTogether
            m += 1.3;
        }
        o += 10;
    }
    */
}
#pragma once


#pragma once
