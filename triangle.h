#pragma once
//
//  triangle.h
//  test
//
//  Created by Nazirul Hasan on 4/10/23.
//

#ifndef triangle_h
#define triangle_h

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

using namespace std;

class Triangle {
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
    Triangle()
    {
        setUpTriangleVertexDataAndConfigureVertexAttribute();
    }

    Triangle(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float shiny)
    {
        this->ambient = amb;
        this->diffuse = diff;
        this->specular = spec;
        this->shininess = shiny;

        setUpTriangleVertexDataAndConfigureVertexAttribute();
    }

    Triangle(unsigned int dMap, unsigned int sMap, float shiny, float textureXmin, float textureYmin, float textureXmax, float textureYmax)
    {
        this->diffuseMap = dMap;
        this->specularMap = sMap;
        this->shininess = shiny;
        this->TXmin = textureXmin;
        this->TYmin = textureYmin;
        this->TXmax = textureXmax;
        this->TYmax = textureYmax;

        setUpTriangleVertexDataAndConfigureVertexAttribute();
    }

    // destructor
    ~Triangle()
    {
        glDeleteVertexArrays(1, &triangleVAO);
        glDeleteVertexArrays(1, &lightTriangleVAO);
        glDeleteVertexArrays(1, &lightTexTriangleVAO);
        glDeleteBuffers(1, &triangleVBO);
        glDeleteBuffers(1, &triangleEBO);
    }

    void drawTriangleWithTexture(Shader& lightingShaderWithTexture, glm::mat4 model = glm::mat4(1.0f))
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

        glBindVertexArray(lightTexTriangleVAO);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
    }

    void drawTriangleWithMaterialisticProperty(Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f))
    {
        lightingShader.use();

        lightingShader.setVec3("material.ambient", this->ambient);
        lightingShader.setVec3("material.diffuse", this->diffuse);
        lightingShader.setVec3("material.specular", this->specular);
        lightingShader.setFloat("material.shininess", this->shininess);

        lightingShader.setMat4("model", model);

        glBindVertexArray(lightTriangleVAO);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
    }

    void drawCube(Shader& shader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
    {
        shader.use();

        shader.setVec3("color", glm::vec3(r, g, b));
        shader.setMat4("model", model);

        glBindVertexArray(triangleVAO);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
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
    unsigned int triangleVAO;
    unsigned int lightTriangleVAO;
    unsigned int lightTexTriangleVAO;
    unsigned int triangleVBO;
    unsigned int triangleEBO;

    void setUpTriangleVertexDataAndConfigureVertexAttribute()
    {
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------

        float triangle_vertices[] = {
            // positions      // normals         // texture
            //back triangle surface
            -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin, TYmin,//0
            0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax, TYmin,//1
            0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax, TYmax,//2
            
            //front triangle surface
             -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin, TYmin,//3
            0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax, TYmin,//4
            0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax, TYmax,//5

            //nicher tol normal= -y axis
            -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin, TYmin,//0  //6
            0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax, TYmin,//1   //7
             -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin, TYmax,//3  //8
            0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax, TYmax,//4    //9

            //left side helano tol
            -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, TXmin, TYmin,//0  10
            0.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f, TXmax, TYmax,//2   11
            -0.5f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, TXmin, TYmax,//3   12
            0.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, TXmax, TYmin,//5    13

            //right side helano tol
            0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, TXmax, TYmin,//1    14
            0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, TXmax, TYmax,//2   15
            0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, TXmin, TYmin,//4    16
            0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, TXmin, TYmax//5    17

        };
        unsigned int triangle_indices[] = {
            //back triangle
            0, 2, 1,

            //front triangle
            3,4,5,

            //nicher tol
            6,7,9,
            9,8,6,

            //left side helano tol
            10,12,13,
            5,2,0,

            //right side helano tol
            14,15,17,
            17,16,14
        };

        glGenVertexArrays(1, &triangleVAO);
        glGenVertexArrays(1, &lightTriangleVAO);
        glGenVertexArrays(1, &lightTexTriangleVAO); //for texture
        glGenBuffers(1, &triangleVBO);
        glGenBuffers(1, &triangleEBO);


        glBindVertexArray(lightTexTriangleVAO);

        glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(triangle_indices), triangle_indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // vertex normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
        glEnableVertexAttribArray(1);

        // texture coordinate attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
        glEnableVertexAttribArray(2);


        glBindVertexArray(lightTriangleVAO);

        glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
        glEnableVertexAttribArray(1);


        glBindVertexArray(triangleVAO);

        glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

};


#endif /* cube_h */
