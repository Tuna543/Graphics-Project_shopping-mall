#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "texture.h"
#include "cube.h"

void sofa(Shader& lightingShader, Cube& frame, Cube& seat)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    float x = -17.0;
    float y = 10.5;
    float z = -47.0;

    float n = 0.0;

    for (int i = 0; i < 2; i++) {
        //backside
        //upper side
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x, 0.0 + y, 0.0 + 0.45 + z + n));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.98f, 3.8f, 0.4f));
        model = translateMatrix * scaleMatrix;
        frame.drawCubeWithTexture(lightingShader, model);
        //nicher wood base
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + 0.3 + x, 0.3 + y, 0.0 + 0.41 + z +n));

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.0 - 0.6f, 1.35f, 3.2f));
        model = translateMatrix * scaleMatrix;
        frame.drawCubeWithTexture(lightingShader, model);

        //handle
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x, 0.0 + y, 0.0 + 0.5 + z + n));

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 2.45f, 3.4f));
        model = translateMatrix * scaleMatrix;
        frame.drawCubeWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 - 0.1 + x, 0.3 + y, 0.0 + 0.5 + z + n));

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 2.1f, 3.3f));
        model = translateMatrix * scaleMatrix;
        seat.drawCubeWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + 5.5 + x, 0.0 + y, 0.0 + 0.5 + z + n));

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 2.45f, 3.4f));
        model = translateMatrix * scaleMatrix;
        frame.drawCubeWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + 5.5 - 0.1 + x, 0.3 + y, 0.0 + 0.5 + z + n));

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 2.1f, 3.3f));
        model = translateMatrix * scaleMatrix;
        seat.drawCubeWithTexture(lightingShader, model);

        //foam
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + 0.05 + x, 1.7 + y, 0.0 + 0.4 + z + n));

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.9f, 2.0f, 0.5f));
        model = translateMatrix * scaleMatrix;
        seat.drawCubeWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x, 0.7 + y, 0.0 + 0.47 + z + n));

        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.9, 1.0f, 3.33f));
        model = translateMatrix * scaleMatrix;
        seat.drawCubeWithTexture(lightingShader, model);

        n += 12;
    }


    //ulta side er sofa
    n = 0.0;
    float ulta_side = 4.7;

    for (int i = 0; i < 2; i++) {
        //backside
        //upper side
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x, 0.0 + y, 0.0 + 0.45 + z + n + ulta_side*2));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.98f, 3.8f, 0.4f));
        model = translateMatrix * scaleMatrix;
        frame.drawCubeWithTexture(lightingShader, model);
        //nicher wood base
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + 0.3 + x, 0.3 + y, 0.0 + 0.5 + z + n + ulta_side * 2+0.4));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.0 - 0.6f, 1.35f, -3.2f));
        model = translateMatrix * scaleMatrix;
        frame.drawCubeWithTexture(lightingShader, model);

        //handle
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x, 0.0 + y, 0.0 + 0.53 + z + n + ulta_side * 2 + 0.45));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 2.45f, -3.4f));
        model = translateMatrix * scaleMatrix;
        frame.drawCubeWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 - 0.1 + x, 0.3 + y, 0.0 + 0.53 + z + n + ulta_side * 2 + 0.4));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 2.1f, -3.3f));
        model = translateMatrix * scaleMatrix;
        seat.drawCubeWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + 5.5 + x, 0.0 + y, 0.0 + 0.53 + z + n + ulta_side * 2 + 0.45));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 2.45f, -3.4f));
        model = translateMatrix * scaleMatrix;
        frame.drawCubeWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + 5.5 - 0.1 + x, 0.3 + y, 0.0 + 0.53 + z + n + ulta_side * 2 + 0.4));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 2.1f, -3.3f));
        model = translateMatrix * scaleMatrix;
        seat.drawCubeWithTexture(lightingShader, model);

        //foam
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + 0.05 + x, 1.7 + y, 0.0 + 0.4 + z + n + ulta_side*2));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.9f, 2.0f, 0.5f));
        model = translateMatrix * scaleMatrix;
        seat.drawCubeWithTexture(lightingShader, model);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x, 0.7 + y, 0.0 + 0.48 + z + n + ulta_side * 2 + 0.4));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.9, 1.0f, -3.2f));
        model = translateMatrix * scaleMatrix;
        seat.drawCubeWithTexture(lightingShader, model);

        n += 12;
    }


    //chairs with circular tables
    x = -8.5;
    float leg_y = 10.5;
    float bosha_y = 11.8;
    float back_frame_y = bosha_y + .25;
    z = -48.5;
    n = 0.0;
    

    //chair legs
    for (int k = 0; k < 2; k++) {
        n = 0.0;
        for (int i = 0; i < 6; i++) {
            //left side inner most
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x + n, 0.0 + leg_y, 0.0 + z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25, 1.3, .25));
            model = translateMatrix * scaleMatrix;
            frame.drawCubeWithTexture(lightingShader, model);

            //right side inner most
            translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0 + x + n, 0.0 + leg_y, 0.0 + z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(-.25, 1.3, .25));
            model = translateMatrix * scaleMatrix;
            frame.drawCubeWithTexture(lightingShader, model);

            //left side outer most
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x + n, 0.0 + leg_y, 0.0 + 2.0 + z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25, 1.3, -.25));
            model = translateMatrix * scaleMatrix;
            frame.drawCubeWithTexture(lightingShader, model);

            //right side outer most
            translateMatrix = glm::translate(identityMatrix, glm::vec3(2.0 + x + n, 0.0 + leg_y, 0.0 + 2.0 + z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(-.25, 1.3, -.25));
            model = translateMatrix * scaleMatrix;
            frame.drawCubeWithTexture(lightingShader, model);


            //chair boshar foam
            //frame
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x + n, 0.0 + bosha_y, 0.0 + z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(2, .25, 2));
            model = translateMatrix * scaleMatrix;
            frame.drawCubeWithTexture(lightingShader, model);

            //seat
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.1 + x + n, 0.05 + bosha_y, 0.1 + z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.8, .25, 1.8));
            model = translateMatrix * scaleMatrix;
            seat.drawCubeWithTexture(lightingShader, model);


            //chair pivhoner frame, helan dewar
            //frame
            if (i % 2 == 0) {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x + n, 0.0 + back_frame_y, 0.0 + z));
            }
            else {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0 + x + n + 2 - .25, 0.0 + back_frame_y, 0.0 + z));
            }
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25, 2.2, 2));
            model = translateMatrix * scaleMatrix;
            frame.drawCubeWithTexture(lightingShader, model);

            //seat
            if (i % 2 == 0) {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.05 + x + n, 0.1 + back_frame_y, 0.1 + z));
            }
            else {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.05 + x + n + 2 - .25, 0.1 + back_frame_y, 0.1 + z));
            }
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.35, 2, 1.8));
            model = translateMatrix * scaleMatrix;
            seat.drawCubeWithTexture(lightingShader, model);


            n += 5.0;
        }
        z = -41.5;
    }
    
}


#pragma once

#pragma once
