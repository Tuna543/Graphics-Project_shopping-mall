#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "cube.h"
#include "triangle.h"
#include "cylinder.h"
#include "sphere.h"

void kidz_wall(Shader& lightingShader, Cube& tom, Cube& ben, Cube& doremon)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //left side wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-19.75, 0.5, -45));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25, 9.5, 17));
    model = translateMatrix * scaleMatrix;
    tom.drawCubeWithTexture(lightingShader, model);

    //right side wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(30, 0.5, -50));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-0.25, 9.5, 10));
    model = translateMatrix * scaleMatrix;
    doremon.drawCubeWithTexture(lightingShader, model);

    //back side wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0, 0.5, -50));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(8, 9.5, 0.25));
    model = translateMatrix * scaleMatrix;
    ben.drawCubeWithTexture(lightingShader, model);
}

void kidz_house(Shader& lightingShader, Cube& red, Cube& green, Cube& yellow, Triangle& triangle)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //left sides of tiner chaal
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.5, 6.5, -38));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 0.25f, 4.0f));
    model = translateMatrix * rotateXMatrix * scaleMatrix;
    red.drawCubeWithMaterialisticProperty(lightingShader, model);
    
    //right sides of tiner chaal
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-18.5, 6.5, -37.75));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 0.25f, -4.25f));
    model = translateMatrix * rotateXMatrix * scaleMatrix;
    red.drawCubeWithMaterialisticProperty(lightingShader, model);

    //majher triangle   >>  front ta
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-14, 4.5, -38));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 2.0f, .25f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    triangle.drawTriangleWithMaterialisticProperty(lightingShader, model);

    //majher triangle   >>  back ta
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-18, 4.5, -38));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 2.0f, .25f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    triangle.drawTriangleWithMaterialisticProperty(lightingShader, model);


    //back side of ghor
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-18, 0.5, -40));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25f, 4.0f, 4.0f));
    model = translateMatrix * scaleMatrix;
    green.drawCubeWithMaterialisticProperty(lightingShader, model);

    //left side of ghor
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-18, 0.5, -36));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 4.0f, -.25f));
    model = translateMatrix * scaleMatrix;
    green.drawCubeWithMaterialisticProperty(lightingShader, model);

    //right side of ghor
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-18, 0.5, -40));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 4.0f, .25f));
    model = translateMatrix * scaleMatrix;
    green.drawCubeWithMaterialisticProperty(lightingShader, model);

    //front side of ghor
    //left part
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-14, 0.5, -36));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 4.0f, -1.0f));
    model = translateMatrix * scaleMatrix;
    yellow.drawCubeWithMaterialisticProperty(lightingShader, model);

    //right part
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-14, 0.5, -40));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25f, 4.0f, 1.0f));
    model = translateMatrix * scaleMatrix;
    yellow.drawCubeWithMaterialisticProperty(lightingShader, model);

    //upper wall
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-14, 4.5, -40));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25f, -1.0f, 4.0f));
    model = translateMatrix * scaleMatrix;
    yellow.drawCubeWithMaterialisticProperty(lightingShader, model);



    //baka slide
    translateMatrix = glm::translate(identityMatrix, glm::vec3(25.25, .5, -45 + 3.7));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.25f, 5.23f, -.2f));
    model = translateMatrix * rotateXMatrix * scaleMatrix;
    yellow.drawCubeWithMaterialisticProperty(lightingShader, model);

}

void kidz_cylinder(Shader& lightingShader, glm::mat4 model_swing, Cylinder& cylinder_green, Cylinder& cylinder_yellow, Cylinder& cylinder_red, Cylinder& cylinder_brown, Cube& cube_cushion, Cube& paste)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //round table
    //nicher base
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 1.5, -25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 1.0f, .2f));
    model = translateMatrix * scaleMatrix;
    cylinder_brown.drawCylinderWithMaterialisticProperty(lightingShader, model);
    //table plate
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-15, 2.7, -25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, .2f, 2.50f));
    model = translateMatrix * scaleMatrix;
    cylinder_brown.drawCylinderWithMaterialisticProperty(lightingShader, model);

    float x_table = -15-2.5;
    float z_table = -25.5;

   for (int j = 0; j < 2; j++) {
            //nicher base
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x_table, 1.0, z_table));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 0.5f, .2f));
        model = translateMatrix * scaleMatrix;
        cylinder_brown.drawCylinderWithMaterialisticProperty(lightingShader, model);
            //table plate
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x_table, 1.7, z_table));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, .2f, 1.0f));
        model = translateMatrix * scaleMatrix;
        cylinder_red.drawCylinderWithMaterialisticProperty(lightingShader, model);
        x_table += 5;
        
    }

    x_table = -15;
    z_table = -25 - 2.5;
    for (int j = 0; j < 2; j++) {
        //nicher base
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x_table, 1.0, z_table));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.2f, 0.5f, .2f));
        model = translateMatrix * scaleMatrix;
        cylinder_brown.drawCylinderWithMaterialisticProperty(lightingShader, model);
        //table plate
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x_table, 1.7, z_table));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, .2f, 1.0f));
        model = translateMatrix * scaleMatrix;
        cylinder_red.drawCylinderWithMaterialisticProperty(lightingShader, model);
        z_table += 5;

    }

    //majher khamba
    //yellow color majher ta
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 4.5, -45));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5f, 1.5f, .5f));
    model = model_swing * translateMatrix * scaleMatrix;
    cylinder_yellow.drawCylinderWithMaterialisticProperty(lightingShader, model);
    //red color majher ta
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 7.25, -45));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5f, 1.25f, .5f));
    model = model_swing * translateMatrix * scaleMatrix;
    cylinder_red.drawCylinderWithMaterialisticProperty(lightingShader, model);
    //green color majher ta
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 1.75, -45));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.5f, 1.25f, .5f));
    model = model_swing * translateMatrix * scaleMatrix;
    cylinder_green.drawCylinderWithMaterialisticProperty(lightingShader, model);



    //nicher base
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, .75, -45));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, .25f, 4.0f));
    model = model_swing * translateMatrix * scaleMatrix;
    cylinder_brown.drawCylinderWithMaterialisticProperty(lightingShader, model);


    //4 seat er niche 4ta lathi
    //left
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.0 + 1.25f, 1.75, -45));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.125f, .75f, .125f));
    model = model_swing * translateMatrix * scaleMatrix;
    cylinder_brown.drawCylinderWithMaterialisticProperty(lightingShader, model);
    //right
    translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0 - 1.25f, 1.75, -45));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.125f, .75f, .125f));
    model = model_swing * translateMatrix * scaleMatrix;
    cylinder_brown.drawCylinderWithMaterialisticProperty(lightingShader, model);
    //back
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.75, -49+1.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.125f, .75f, .125f));
    model = model_swing * translateMatrix * scaleMatrix;
    cylinder_brown.drawCylinderWithMaterialisticProperty(lightingShader, model);
    //front
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.75, -41 - 1.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.125f, .75f, .125f));
    model = model_swing * translateMatrix * scaleMatrix;
    cylinder_brown.drawCylinderWithMaterialisticProperty(lightingShader, model);


    //4 seats
    //left seat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.0+2.5f, 2.5, -45+1.0));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-2.5f, 0.5f, 2.0f));
    model =  model_swing *  translateMatrix * rotateYMatrix * scaleMatrix;
    paste.drawCubeWithMaterialisticProperty(lightingShader, model);
    //left seat helan
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.0 + 2.5f, 3.0, -45 + 1.0));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-2.5f, 2.0f, .5f));
    model = model_swing * translateMatrix * rotateYMatrix * scaleMatrix;
    paste.drawCubeWithMaterialisticProperty(lightingShader, model);
    //left seat right side
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.0f+2.5f, 3.0, -45 + 1.0));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-.25f, .75f, 2.0f));
    model = model_swing * translateMatrix * rotateYMatrix * scaleMatrix;
    cube_cushion.drawCubeWithMaterialisticProperty(lightingShader, model);
    
    //left seat left side
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-4.0+2.5f, 3.0, -45 + 1.0-2.5));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25f, .75f, 2.0f));
    model = model_swing * translateMatrix * rotateYMatrix * scaleMatrix;
    cube_cushion.drawCubeWithMaterialisticProperty(lightingShader, model);
    


    //right seat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0-2.5, 2.5, -45+1));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 0.5f, 2.0f));
    model =  model_swing *  translateMatrix * rotateYMatrix * scaleMatrix;
    paste.drawCubeWithMaterialisticProperty(lightingShader, model);
    //right seat helan
    translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0 - 2.5, 3.0, -45 + 1));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 2.0f, .5f));
    model = model_swing * translateMatrix * rotateYMatrix * scaleMatrix;
    paste.drawCubeWithMaterialisticProperty(lightingShader, model);
    //right seat left part
    translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0 - 2.5, 3.0, -45 + 1));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25f, .75f, 2.0f));
    model = model_swing * translateMatrix * rotateYMatrix * scaleMatrix;
    cube_cushion.drawCubeWithMaterialisticProperty(lightingShader, model);
    //right seat right part
    translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0 -2.5, 3.0, -45 + 1-2.5));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-.25f, .75f, 2.0f));
    model = model_swing * translateMatrix * rotateYMatrix * scaleMatrix;
    cube_cushion.drawCubeWithMaterialisticProperty(lightingShader, model);


    //back seat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.25, 2.5, -49));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 0.5f, 2.0f));
    model =  model_swing *  translateMatrix * scaleMatrix;
    paste.drawCubeWithMaterialisticProperty(lightingShader, model);
    //back seat helan
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.25, 3.0, -49+2));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 2.0f, -.5f));
    model = model_swing * translateMatrix * scaleMatrix;
    paste.drawCubeWithMaterialisticProperty(lightingShader, model);
    //back seat left side
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.25, 3.0, -49 + 2));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25f, 0.75f, -2.0f));
    model = model_swing * translateMatrix * scaleMatrix;
    cube_cushion.drawCubeWithMaterialisticProperty(lightingShader, model);
    //back seat right side
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.25+2.5, 3.0, -49 + 2));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-.25f, 0.75f, -2.0f));
    model = model_swing * translateMatrix * scaleMatrix;
    cube_cushion.drawCubeWithMaterialisticProperty(lightingShader, model);


    //front seat
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.25, 2.5, -41));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 0.5f, -2.0f));
    model =  model_swing *  translateMatrix * scaleMatrix;
    paste.drawCubeWithMaterialisticProperty(lightingShader, model);
    //front seat helan
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.25, 3.0, -41-2));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, 2.0f, .5f));
    model = model_swing * translateMatrix * scaleMatrix;
    paste.drawCubeWithMaterialisticProperty(lightingShader, model);
    //front seat left side
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.25, 3.0, -41 - 2));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25f, 0.75f, 2.0f));
    model = model_swing * translateMatrix * scaleMatrix;
    cube_cushion.drawCubeWithMaterialisticProperty(lightingShader, model);
    //front seat right side
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.25+2.5, 3.0, -41 - 2));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-.25f, .75f, 2.0f));
    model = model_swing * translateMatrix * scaleMatrix;
    cube_cushion.drawCubeWithMaterialisticProperty(lightingShader, model);

}

void kidz_slide(Shader& lightingShader, Cube& red, Cube& green, Cube& wood)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    //front sides of nicher cube
    translateMatrix = glm::translate(identityMatrix, glm::vec3(20, .5, -45));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(10.0f, 1.5f, 0.25f));
    model = translateMatrix * scaleMatrix;
    green.drawCubeWithMaterialisticProperty(lightingShader, model);

    //left sides of nicher cube
    translateMatrix = glm::translate(identityMatrix, glm::vec3(20, .5, -45));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 1.5f, .25f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    red.drawCubeWithMaterialisticProperty(lightingShader, model);
    
    float j = 0.0;
    for (int i = 0; i < 2; i++) {
        //sides of ladder
        translateMatrix = glm::translate(identityMatrix, glm::vec3(25+j, .5, -46));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25f, 3.5f, .25f));
        model = translateMatrix * scaleMatrix;
        wood.drawCubeWithMaterialisticProperty(lightingShader, model);
        j += 2.5;
    }
    
    j = 0.0;
    for (int i = 0; i < 6; i++) {
        //steps of ladder
        translateMatrix = glm::translate(identityMatrix, glm::vec3(25, .6 + j, -46));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5f, .2f, .25f));
        model = translateMatrix * scaleMatrix;
        wood.drawCubeWithMaterialisticProperty(lightingShader, model);
        j += 0.56;
    }

    //upper side before slide
    translateMatrix = glm::translate(identityMatrix, glm::vec3(25, 4, -46));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.75f, .2f, 1.0f));
    model = translateMatrix * scaleMatrix;
    wood.drawCubeWithMaterialisticProperty(lightingShader, model);

    //baka slide=========left side
    translateMatrix = glm::translate(identityMatrix, glm::vec3(25.0, .5, -45+3.7-.2));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25f, 5.23f, .4f));
    model = translateMatrix * rotateXMatrix * scaleMatrix;
    wood.drawCubeWithMaterialisticProperty(lightingShader, model);

    //baka slide========right side
    translateMatrix = glm::translate(identityMatrix, glm::vec3(27.5, .5, -45 + 3.7-.2));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25f, 5.23f, .4f));
    model = translateMatrix * rotateXMatrix * scaleMatrix;
    wood.drawCubeWithMaterialisticProperty(lightingShader, model);

}

//kids circles
void kidz_circle(Shader& lightingShader, Sphere& red, Sphere& green, Sphere& yellow)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    float scale_x = .5;
    float scale_y = .5;
    float scale_z = .5;

    //green balls

    for (int i = 0; i < 3; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(22+(scale_y+2.5)*i, 1.0, -40-scale_y));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_x, scale_y, scale_z));
        model = translateMatrix * scaleMatrix;
        green.drawSphere(lightingShader, model);
    }
    for (int i = 0; i < 3; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(23+(scale_y + 1.5) * i, 1.0, -44 + scale_y));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_x, scale_y, scale_z));
        model = translateMatrix * scaleMatrix;
        red.drawSphere(lightingShader, model);
    }
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(21+(scale_y + 7.0) * i, 1.0, -44 + (scale_y + 1.2) * j));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_x, scale_y, scale_z));
            model = translateMatrix * scaleMatrix;
            yellow.drawSphere(lightingShader, model);
        }
    }
}
