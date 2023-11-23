#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "cube.h"
#include "cylinder.h"
#include "triangle.h"
#include "cubeobject.h"

/*
void tables_one_leg(Shader& lightingShader, Cube& frame)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    float x = -10.0;
    float y = 0.5;
    float z = -40.0;

    //table top most surface
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x - 0.15, 2.25 + y, 0.0 + z - 0.15));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.8, 0.2, 2.3));
    model = translateMatrix * scaleMatrix;
    frame.drawCubeWithTexture(lightingShader, model);
    //table top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x, 1.75 + y, 0.0 + z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.5, 0.5, 2));
    model = translateMatrix * scaleMatrix;
    frame.drawCubeWithTexture(lightingShader, model);
    //leg
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x, 0.25+ y, 0.9 + z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.5, 1.5, .2));
    model = translateMatrix * scaleMatrix;
    frame.drawCubeWithTexture(lightingShader, model);

    //base for legside
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x, 0.0 + y, 0.7 + z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.5, .25, .6));
    model = translateMatrix * scaleMatrix;
    frame.drawCubeWithTexture(lightingShader, model);

}
*/
void tables_four_leg(Shader& lightingShader, Cube& frame)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    float x = -17.0;
    float y = 10.5;
    float z = -42.5;

    float p = 0.0;

    for (int k = 0; k < 2; k++) {

        //table top most surface
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x - 0.15, 2.0 + y, 0.0 + z - 0.15 +p));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.8, 0.25, 2.3));
        model = translateMatrix * scaleMatrix;
        frame.drawCubeWithTexture(lightingShader, model);
        //table top
        /*
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x, 1.75 + y, 0.0 + z + p));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.5, 0.5, 2));
        model = translateMatrix * scaleMatrix;
        base.drawCubeWithTexture(lightingShader, model);
        */
        //leg
        float m = 0.0, n = 0.0;
        float angle = 90 - 53.13f, scale_z = .25;
        for(int i=0; i<2; i++){
            m = 0.0;
            if (i == 1) {
                angle = angle * -1;
                scale_z = scale_z * -1;
            }
            for (int j = 0; j < 2; j++) {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0-.15+.4+x+m, 0.1 + y,  0.0 - .15 + .4 + z + p+n));
                rotateXMatrix = glm::rotate(identityMatrix, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25, 2.5, scale_z));
                model = translateMatrix * rotateXMatrix * scaleMatrix;
                frame.drawCubeWithTexture(lightingShader, model);

                m += 5;
            }
            n += 1.5;
        }

        p += 12;
    }

}

void circular_table(Shader& lightingShader, Cylinder& cylinder, Triangle& triangle)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    float x = -5.0;
    float y = 10.5;
    float z = -47.5;

    float p = 0.0;

    for (int j = 0; j < 2; j++) {
        p = 0.0;
        for (int k = 0; k < 3; k++) {

            //table top
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x + p, 2.0 + y, 0.0 + z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0, 0.25, 2.0));
            model = translateMatrix * scaleMatrix;
            cylinder.drawCylinderWithTexture(lightingShader, model);

            //leg
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x + p, 0.0 + y, 0.0 + z - .125));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0, 2.0, .25));
            model = translateMatrix * scaleMatrix;
            triangle.drawTriangleWithTexture(lightingShader, model);

            //leg
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x + p, 0.0 + y, 0.0 + z));
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0, 2.0, .125));
            model = translateMatrix * rotateYMatrix * scaleMatrix;
            triangle.drawTriangleWithTexture(lightingShader, model);

            //leg
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x + p, 0.0 + y, 0.0 + z));
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(3.0, 2.0, -.125));
            model = translateMatrix * rotateYMatrix * scaleMatrix;
            triangle.drawTriangleWithTexture(lightingShader, model);

            p += 10;
        }
        z = -40.5;
    }


}
#pragma once

void restaurant_interior(Shader& lightingShader, Cube& cube_wall, Cube& cube1, Cube& cube2, Cube& cube3, Cube& cube4, Cube& cube5)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    float x = -19.75;
    float y = 10.5;
    float z = -50;

    //backside wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x, y, z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(49.75, 10, .25));
    model = translateMatrix * scaleMatrix;
    cube_wall.drawCubeWithTexture(lightingShader, model);

    //wall left side
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x, y, z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25, 10, 32));
    model = translateMatrix * scaleMatrix;
    cube_wall.drawCubeWithTexture(lightingShader, model);

    //wall right side
    translateMatrix = glm::translate(identityMatrix, glm::vec3(30.24, y, z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-.25, 10, 20));
    model = translateMatrix * scaleMatrix;
    cube_wall.drawCubeWithTexture(lightingShader, model);

    //wall inside washroom
    translateMatrix = glm::translate(identityMatrix, glm::vec3(15.0, 10.5, -30));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(15, 10, -.25));
    model = translateMatrix * scaleMatrix;
    cube_wall.drawCubeWithTexture(lightingShader, model);

    //wall front washroom
    translateMatrix = glm::translate(identityMatrix, glm::vec3(18.25, 10.5, -34.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(8.75, 10, .25));
    model = translateMatrix * scaleMatrix;
    cube_wall.drawCubeWithTexture(lightingShader, model);

    //wall front washroom==========upper
    translateMatrix = glm::translate(identityMatrix, glm::vec3(15.0, 20.5, -34.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(15.0, -2.75, .25));
    model = translateMatrix * scaleMatrix;
    cube_wall.drawCubeWithTexture(lightingShader, model);


    //washroom side wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(15.0, 10.5, -30.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25, 10, -4));
    model = translateMatrix * scaleMatrix;
    cube_wall.drawCubeWithTexture(lightingShader, model);

    //washroom middle wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(22.5, 10.5, -30.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25, 10, -4));
    model = translateMatrix * scaleMatrix;
    cube_wall.drawCubeWithTexture(lightingShader, model);

    //wall left side=========picture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25 + x, 5.0+y, 10.0+z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1, 4, 2.73));
    model = translateMatrix * scaleMatrix;
    cube1.drawCubeWithTexture(lightingShader, model);

    //wall left side=========picture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.25 + x, 5.0 + y, 25.0 + z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1, 4, 2.3));
    model = translateMatrix * scaleMatrix;
    cube2.drawCubeWithTexture(lightingShader, model);

    //backside wall============picture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(10.0 + x, 5.0+y, z+.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.3, 4, .1));
    model = translateMatrix * scaleMatrix;
    cube3.drawCubeWithTexture(lightingShader, model);

    
    //backside wall============picture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(20.0 + x, 3.0 + y, z + .25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(3, 6, .1));
    model = translateMatrix * scaleMatrix;
    cube5.drawCubeWithTexture(lightingShader, model);

    //backside wall============picture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(30.0 + x, 5.0 + y, z + .25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.7, 4, .1));
    model = translateMatrix * scaleMatrix;
    cube4.drawCubeWithTexture(lightingShader, model);





    //restuarants counter and racks
}


