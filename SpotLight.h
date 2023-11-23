
#ifndef spotLight_h
#define spotLight_h

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"

class SpotLight { //spot light class
public:
    //the attributes of light
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    float kc;
    float kl;
    float kq;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    int lightnumber;

    //constructor
    SpotLight(float posX, float posY, float posZ, float dirX, float dirY, float dirZ, float ambR, float ambG, float ambB, float diffR, float diffG, float diffB, float specR, float specG, float specB, float constant, float linear, float quadratic, float CO, float OCO, int num) {

        position = glm::vec3(posX, posY, posZ);
        direction = glm::vec3(dirX, dirY, dirZ);
        ambient = glm::vec3(ambR, ambG, ambB);
        diffuse = glm::vec3(diffR, diffG, diffB);
        specular = glm::vec3(specR, specG, specB);
        kc = constant;
        kl = linear;
        kq = quadratic;
        cutOff = CO;
        outerCutOff = OCO;
        lightnumber = num;
    }
    //input is a shader, ekhan theke set up hochhe fragment shader e
    void setUpSpotLight(Shader& lightingShaderWithTexture)
    {
        lightingShaderWithTexture.use();

        //setting up all the properties for each light
        if (lightnumber == 1) {
            lightingShaderWithTexture.setVec3("spotLights[0].position", position);
            lightingShaderWithTexture.setVec3("spotLights[0].direction", direction);
            lightingShaderWithTexture.setVec3("spotLights[0].ambient", ambient * ambientOn);
            lightingShaderWithTexture.setVec3("spotLights[0].diffuse", diffuse * diffuseOn);
            lightingShaderWithTexture.setVec3("spotLights[0].specular", specular * specularOn);
            lightingShaderWithTexture.setFloat("spotLights[0].kc", kc);
            lightingShaderWithTexture.setFloat("spotLights[0].kl", kl);
            lightingShaderWithTexture.setFloat("spotLights[0].kq", kq);
            lightingShaderWithTexture.setFloat("spotLights[0].cutOff", glm::cos(glm::radians(cutOff)));
            lightingShaderWithTexture.setFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(outerCutOff)));

        }

        if (lightnumber == 2) {
            lightingShaderWithTexture.setVec3("spotLights[1].position", position);
            lightingShaderWithTexture.setVec3("spotLights[1].direction", direction);
            lightingShaderWithTexture.setVec3("spotLights[1].ambient", ambient * ambientOn);
            lightingShaderWithTexture.setVec3("spotLights[1].diffuse", diffuse * diffuseOn);
            lightingShaderWithTexture.setVec3("spotLights[1].specular", specular * specularOn);
            lightingShaderWithTexture.setFloat("spotLights[1].kc", kc);
            lightingShaderWithTexture.setFloat("spotLights[1].kl", kl);
            lightingShaderWithTexture.setFloat("spotLights[1].kq", kq);
            lightingShaderWithTexture.setFloat("spotLights[1].cutOff", glm::cos(glm::radians(cutOff)));
            lightingShaderWithTexture.setFloat("spotLights[1].outerCutOff", glm::cos(glm::radians(outerCutOff)));

        }
        
    }
    void turnOff() //light off
    {
        ambientOn = 0.0;
        diffuseOn = 0.0;
        specularOn = 0.0;
    }
    void turnOn()
    {
        ambientOn = 1.0;
        diffuseOn = 1.0;
        specularOn = 1.0;
    }
    void turnAmbientOn()
    {
        ambientOn = 1.0;
    }
    void turnAmbientOff()
    {
        ambientOn = 0.0;
    }
    void turnDiffuseOn()
    {
        diffuseOn = 1.0;
    }
    void turnDiffuseOff()
    {
        diffuseOn = 0.0;
    }
    void turnSpecularOn()
    {
        specularOn = 1.0;
    }
    void turnSpecularOff()
    {
        specularOn = 0.0;
    }
private: //for light on-off
    float ambientOn = 1.0;
    float diffuseOn = 1.0;
    float specularOn = 1.0;
};

#endif /* spotLight_h */

#pragma once

