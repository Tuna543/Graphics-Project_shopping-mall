#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "cube.h"
#include "cubeobject.h"
#include "staircube.h"

void showcaserack(Shader& lightingShader, Cube& cube, Cubeobject& shoe, Cubeobject& fabric, Cubeobject& shampoo, Cubeobject& watch)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    float n = 0.0, o = 0.0;

    //2nd floor er single rack ta
    //first rack starts here
    float x = 19.5, y = 10.5 + n, z = -9.5 + o;
    //for scaling back
    float back_x = 10.0, back_y = 8.0, back_z = 0.25;
    //for scaling two sides
    float border_x = 0.25, border_y = 8.0, border_z = 1.2;
    //for scaling rack size
    float rack_x = 10.0, rack_y = 0.25, rack_z = 1.2;
    float lowest_rack_y_position = .75 + 10;

    //pichoner base
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 0.0, y + 0.0, z - 0.25));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(back_x, back_y, back_z));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);


    //left border
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 0.0, y + 0.0, z + 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(border_x, border_y, border_z));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //right border
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 10.0, y + 0.0, z + 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(border_x, border_y, border_z));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //lowest rack
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position, z + 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //2nd lowest rack
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position + 1.5, z + 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //middle rack
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position + 1.5 * 2, z + 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //upper rack
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position + 1.5 * 3, z + 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //higest rack
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position + 1.5 * 4, z + 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);

    //topmost rack
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position + 1.5 * 5, z + 0.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
    model = translateMatrix * scaleMatrix;
    cube.drawCubeWithTexture(lightingShader, model);


    for (int i = 0; i < 2; i++) {
        if (i == 1) {
            o = 10.0;
        }
        else {
            o = 0.0;
        }
        for (int j = 0; j < 4; j++) {
            
            if (i == 1) {
                ++j;
            }
            //first rack starts here
            float x = 19.5, y = 0.5+n, z = -39.5+o;
            //for scaling back
            float back_x = 10.0, back_y = 8.0, back_z = 0.25;
            //for scaling two sides
            float border_x = 0.25, border_y = 8.0, border_z = 1.2;
            //for scaling rack size
            float rack_x = 10.0, rack_y = 0.25, rack_z = 1.2;
            float lowest_rack_y_position = .75+n;

            //pichoner base
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 0.0, y + 0.0, z - 0.25));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(back_x, back_y, back_z));
            model = translateMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);


            //left border
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 0.0, y + 0.0, z + 0.0));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(border_x, border_y, border_z));
            model = translateMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);

            //right border
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 10.0, y + 0.0, z + 0.0));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(border_x, border_y, border_z));
            model = translateMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);

            //lowest rack
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position, z + 0.0));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
            model = translateMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);

            //2nd lowest rack
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position + 1.5, z + 0.0));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
            model = translateMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);

            //middle rack
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position + 1.5 * 2, z + 0.0));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
            model = translateMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);

            //upper rack
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position + 1.5 * 3, z + 0.0));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
            model = translateMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);

            //higest rack
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position + 1.5 * 4, z + 0.0));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
            model = translateMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);

            //topmost rack
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position + 1.5 * 5, z + 0.0));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
            model = translateMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);

            //first rack ends here

            o += 10;
        }
        n += 10;
    }
    /*
    //z aligned rack
    //second rack
    n = 0.0, o = 0.0;
    /*
    for (int i = 0; i < 2; i++) {
        if (i == 0) {
            o = 10.0;
        }
        else {
            o = 0.0;
        }
        
        for (int j = 0; j < 4; j++) {
            if (i == 0) {
                j++;
            }
            float x = 29.5, y = 0.5 + n, z = -48.3 + o;
            //for scaling back
            float back_x = .25, back_y = 8.0, back_z = 8;
            //for scaling two sides
            float border_x = -1.2, border_y = 8.0, border_z = .25;
            //for scaling rack size
            float rack_x = -1.2, rack_y = 0.25, rack_z = 8;
            float lowest_rack_y_position = .75 + n;

            //pichoner base
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, y, z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(back_x, back_y, back_z));
            model = translateMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);

            //left border dorkar nai

            //right border
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, y + 0.0, z + back_z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(border_x, border_y, border_z));
            model = translateMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);

            //lowest rack
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position, z + 0.0));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
            model = translateMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);

            //2nd lowest rack
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position + 1.5, z + 0.0));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
            model = translateMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);

            //middle rack
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position + 1.5 * 2, z + 0.0));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
            model = translateMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);

            //upper rack
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position + 1.5 * 3, z + 0.0));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
            model = translateMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);

            //higest rack
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position + 1.5 * 4, z + 0.0));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
            model = translateMatrix * scaleMatrix;
            cube.drawCubeWithTexture(lightingShader, model);

            //second rack ends here
            
            o += 10;
        }
        n += 10;
    }
    */
    //placing items on rack
    y = 1.0;
    x = 20;
    float shoe_z = -39.5 - 0.25;
    float fabric_z = -29.5 - 0.25;
    float shampoo_z = -19.5 - 0.25;
    float watch_z = -9.5 - 0.25;

    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 5; j++) {
                if (k==0) {
                    //placing shoes
                    translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 1.5 * i, y - .05 + 1.5 * j, shoe_z));
                    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1.2, 1.2));
                    model = translateMatrix * scaleMatrix;
                    shoe.drawcubeobjectWithTexture(lightingShader, model);
                }
                //placing fabrics
                translateMatrix = glm::translate(identityMatrix, glm::vec3(x - 0.45 + 1.6 * i, y + 1.5 * j, fabric_z));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.2, 1.25, 1.2));
                model = translateMatrix * scaleMatrix;
                fabric.drawcubeobjectWithTexture(lightingShader, model);

                //placing shampoos
                translateMatrix = glm::translate(identityMatrix, glm::vec3(x - 0.25 + 1.6 * i, y - .45 + 1.5 * j, shampoo_z));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1.7, 1.2));
                model = translateMatrix * scaleMatrix;
                shampoo.drawcubeobjectWithTexture(lightingShader, model);

                //placing perfumes
                translateMatrix = glm::translate(identityMatrix, glm::vec3(x - 0.25 + 1.6 * i, y - .07 + 1.5 * j, watch_z));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, 1.2));
                model = translateMatrix * scaleMatrix;
                watch.drawcubeobjectWithTexture(lightingShader, model);
            }
        }
        y += 10;
    }
    
    
    
    
    
    
    /*
    o = 0.0;
    //gold er dokan
    for (int j = 0; j < 2; j++) {
        //first rack starts here
        float x = -19.5, y = 0.5, z = -32.5 + o;
        //for scaling back
        float back_x = 10.0, back_y = 8.0, back_z = 0.25;
        //for scaling two sides
        float border_x = 0.25, border_y = 8.0, border_z = 1.2;
        //for scaling rack size
        float rack_x = 9.95, rack_y = 0.25, rack_z = 1.2;
        float lowest_rack_y_position = .75 + 0;

        if (j == 1) {
            border_z = -1.2;
            rack_z = -1.2;
        }
        //pichoner base
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 0.0, y + 0.0, z - 0.25));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(back_x, back_y, back_z));
        model = translateMatrix * scaleMatrix;
        cube.drawCubeWithTexture(lightingShader, model);


        //left border
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 0.0, y + 0.0, z + 0.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(border_x, border_y, border_z));
        model = translateMatrix * scaleMatrix;
        cube.drawCubeWithTexture(lightingShader, model);

        //right border
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 10.0, y + 0.0, z + 0.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(-border_x, border_y, border_z));
        model = translateMatrix * scaleMatrix;
        cube.drawCubeWithTexture(lightingShader, model);
        
        //2nd lowest rack
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position + 1.5, z + 0.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
        model = translateMatrix * scaleMatrix;
        cube.drawCubeWithTexture(lightingShader, model);
        
        //upper rack
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position + 1.5 * 3, z + 0.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
        model = translateMatrix * scaleMatrix;
        cube.drawCubeWithTexture(lightingShader, model);
        
        //topmost rack
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x, lowest_rack_y_position + 1.5 * 5, z + 0.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(rack_x, rack_y, rack_z));
        model = translateMatrix * scaleMatrix;
        cube.drawCubeWithTexture(lightingShader, model);

        //first rack ends here

        o += 14.5;
    }
    
    //placing golds on rack
    y = 2.45;
    x = -19;
    float neck1_z = -32.5 - 0.25;
    float neck2_z = -17 - 0.75;
    float neck3_z = -19.5 - 0.25;
    float neck4_z = -9.5 - 0.25;

    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 2; j++) {
                
                    translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 1.5 * i, y + 3 * j, neck1_z));
                    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1.0, 1.2));
                    model = translateMatrix * scaleMatrix;
                    cube_neck2.drawcubeobjectWithTexture(lightingShader, model);
          
                translateMatrix = glm::translate(identityMatrix, glm::vec3(x+1.5 + 1.5 * i, y + 3 * j, neck2_z));
                rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 2.5, 1.2));
                model = translateMatrix * rotateYMatrix* scaleMatrix;
                cube_neck3.drawcubeobjectWithTexture(lightingShader, model);
                
            }
        }
        y += 10;
    }
    */
    //washroom wooden doors

    float x_axis = 15.25;
    float y_axis = 10.5;
    float z_axis = -34.25;
    float x_scale = .25;
    float y_scale = 7.0;
    float z_scale = .5;

    //door bars 
    //sides
    for (int i = 0; i < 4; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x_axis, y_axis, z_axis));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(x_scale, y_scale, z_scale));
        model = translateMatrix * scaleMatrix;
        cube.drawCubeWithTexture(lightingShader, model);

        x_axis += 3 - .25; 

        if (i == 1) {
            x_axis = 27;
        }
    }
    x_axis = 15.25;
    //upper part
    for (int i = 0; i < 2; i++) {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x_axis, y_axis+y_scale, z_axis));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(3, .25, z_scale));
        model = translateMatrix * scaleMatrix;
        cube.drawCubeWithTexture(lightingShader, model);
        x_axis = 27;
        
    }
    
    
}
#pragma once
