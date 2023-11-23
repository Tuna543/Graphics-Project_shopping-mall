#pragma once
//
//  cube.h
//  test
//
//  Created by Nazirul Hasan on 4/10/23.
//

#ifndef staircube_h
#define staircube_h

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

using namespace std;

class Staircube {
public:

    // materialistic property
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    // texture property
    float TXmin = 0.0f;
    float TXmax = 1.0f;
    float TYmin = 0.0f;
    float TYmax = 1.0f;
    unsigned int diffuseMap;
    unsigned int specularMap;

    // common property
    float shininess;

    // constructors
    Staircube()
    {
        setUpStaircubeVertexDataAndConfigureVertexAttribute();
    }

    Staircube(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float shiny)
    {
        this->ambient = amb;
        this->diffuse = diff;
        this->specular = spec;
        this->shininess = shiny;

        setUpStaircubeVertexDataAndConfigureVertexAttribute();
    }

    Staircube(unsigned int dMap, unsigned int sMap, float shiny, float textureXmin, float textureYmin, float textureXmax, float textureYmax)
    {
        this->diffuseMap = dMap;
        this->specularMap = sMap;
        this->shininess = shiny;
        this->TXmin = textureXmin;
        this->TYmin = textureYmin;
        this->TXmax = textureXmax;
        this->TYmax = textureYmax;

        setUpStaircubeVertexDataAndConfigureVertexAttribute();
    }

    // destructor
    ~Staircube()
    {
        glDeleteVertexArrays(1, &StaircubeVAO);
        glDeleteVertexArrays(1, &lightStaircubeVAO);
        glDeleteVertexArrays(1, &lightTexStaircubeVAO);
        glDeleteBuffers(1, &StaircubeVBO);
        glDeleteBuffers(1, &StaircubeEBO);
    }

    void drawStaircubeWithTexture(Shader& lightingShaderWithTexture, glm::mat4 model = glm::mat4(1.0f))
    {
        lightingShaderWithTexture.use();

        lightingShaderWithTexture.setInt("material.diffuse", 0);
        lightingShaderWithTexture.setInt("material.specular", 1);
        lightingShaderWithTexture.setFloat("material.shininess", this->shininess);

        //a fragment shader can use multiple texture at a time, 0 and 1 is used to indicate fragment shader needs to work with both of the texture together
        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);  //0 means diffuse texture
        glBindTexture(GL_TEXTURE_2D, this->diffuseMap); //0 is bound to diffuseMap
        // bind specular map    
        glActiveTexture(GL_TEXTURE1); //1 means specular texture 
        glBindTexture(GL_TEXTURE_2D, this->specularMap); //1 is bound to specularMap

        lightingShaderWithTexture.setMat4("model", model);

        glBindVertexArray(lightTexStaircubeVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    void drawCubeWithMaterialisticProperty(Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f))
    {
        lightingShader.use();

        lightingShader.setVec3("material.ambient", this->ambient);
        lightingShader.setVec3("material.diffuse", this->diffuse);
        lightingShader.setVec3("material.specular", this->specular);
        lightingShader.setFloat("material.shininess", this->shininess);

        lightingShader.setMat4("model", model);

        glBindVertexArray(lightStaircubeVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    void drawCube(Shader& shader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
    {
        shader.use();

        shader.setVec3("color", glm::vec3(r, g, b));
        shader.setMat4("model", model);

        glBindVertexArray(StaircubeVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    void setMaterialisticProperty(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float shiny)
    {
        this->ambient = amb;
        this->diffuse = diff;
        this->specular = spec;
        this->shininess = shiny;
    }

    void setTextureProperty(unsigned int dMap, unsigned int sMap, float shiny)
    {
        this->diffuseMap = dMap;
        this->specularMap = sMap;
        this->shininess = shiny;
    }

private:
    unsigned int StaircubeVAO;
    unsigned int lightStaircubeVAO;
    unsigned int lightTexStaircubeVAO;
    unsigned int StaircubeVBO;
    unsigned int StaircubeEBO;

    void setUpStaircubeVertexDataAndConfigureVertexAttribute()
    {
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------

        float Staircube_vertices[] = {
            // positions      // normals         // texture
            
            //right side +ve x
            //1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax, TYmin,//eta baad
            1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax, TYmax,
            1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin, TYmin,
            1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin, TYmax,

            //+ve z axis
            0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin, TYmin,//same as before
            1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax, TYmin,
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax, TYmax,
            0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin, TYmax,

            //left side -ve x axis
            0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax, TYmin,//left side
            0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax, TYmax,
            0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin, TYmax,
            //0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin, TYmin,//eta baad

            // +y axis
            1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax, TYmin,//same as before
            1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax, TYmax,
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin, TYmax,
            0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin, TYmin,

            //right side +ve x
            //slub er right part ta
            //index: 14-17
            1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax, TYmax, //helano toler uporer point ta
            1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin, TYmin, //helano toler nicher point ta
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax, TYmin, //helano toler uporer point tar nicher point ta
            1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin, TYmax, //helano toler nicher point tar nicher point ta

            //left side -ve x
            //slub er left part ta
            //index: 18-21
            0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmax, TYmax, //helano toler uporer point ta
            0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmin, TYmin, //helano toler nicher point ta
            0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmax, TYmin, //helano toler uporer point tar nicher point ta
            0.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmin, TYmax, //helano toler nicher point tar nicher point ta

            // index : 22-25
            //helano tol
            //right side
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax, TYmin, //helano toler uporer point tar nicher point ta
            1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin, TYmax, //helano toler nicher point tar nicher point ta
            //left side
            0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmax, TYmax, //helano toler uporer point tar nicher point ta
            0.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmin, TYmin, //helano toler nicher point tar nicher point ta
            
        };
        unsigned int Staircube_indices[] = {
            0,2,1,

            3,4,5,
            3,5,6,

            7,8,9,

            12,13,10,
            12,10,11,

            //right side helano slub
            14,15,17,
            17,16,14,

            //left side helano slube
            18,19,21,
            21,20,18,

            //full helano tol
            22,23,25,
            25,22,24

            /*
            0, 3, 2,
            2, 1, 0,

            4, 5, 7,
            7, 6, 4,

            8, 9, 10,
            10, 11, 8,

            12, 13, 14,
            14, 15, 12,

            16, 17, 18,
            18, 19, 16,

            20, 21, 22,
            22, 23, 20
            */
        };

        glGenVertexArrays(1, &StaircubeVAO);
        glGenVertexArrays(1, &lightStaircubeVAO);
        glGenVertexArrays(1, &lightTexStaircubeVAO); //for texture
        glGenBuffers(1, &StaircubeVBO);
        glGenBuffers(1, &StaircubeEBO);


        glBindVertexArray(lightTexStaircubeVAO);

        glBindBuffer(GL_ARRAY_BUFFER, StaircubeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Staircube_vertices), Staircube_vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, StaircubeEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Staircube_indices), Staircube_indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // vertex normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
        glEnableVertexAttribArray(1);

        // texture coordinate attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
        glEnableVertexAttribArray(2);


        glBindVertexArray(lightStaircubeVAO);

        glBindBuffer(GL_ARRAY_BUFFER, StaircubeVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, StaircubeEBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
        glEnableVertexAttribArray(1);


        glBindVertexArray(StaircubeVAO);

        glBindBuffer(GL_ARRAY_BUFFER, StaircubeVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, StaircubeEBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

};


#endif /* cube_h */
