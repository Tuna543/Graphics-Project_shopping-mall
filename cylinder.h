//
//  cube.h
//  test
//
//  Created by Nazirul Hasan on 4/10/23.
//

#ifndef cylinder_h
#define cylinder_h

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

using namespace std;

class Cylinder {
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
    Cylinder()
    {
        setUpCylinderVertexDataAndConfigureVertexAttribute();
    }

    Cylinder(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float shiny)
    {
        this->ambient = amb;
        this->diffuse = diff;
        this->specular = spec;
        this->shininess = shiny;

        setUpCylinderVertexDataAndConfigureVertexAttribute();
    }

    Cylinder(unsigned int dMap, unsigned int sMap, float shiny, float textureXmin, float textureYmin, float textureXmax, float textureYmax)
    {
        this->diffuseMap = dMap;
        this->specularMap = sMap;
        this->shininess = shiny;
        this->TXmin = textureXmin;
        this->TYmin = textureYmin;
        this->TXmax = textureXmax;
        this->TYmax = textureYmax;

        setUpCylinderVertexDataAndConfigureVertexAttribute();
    }

    // destructor
    ~Cylinder()
    {
        glDeleteVertexArrays(1, &cylinderVAO);
        glDeleteVertexArrays(1, &lightCylinderVAO);
        glDeleteVertexArrays(1, &lightTexCylinderVAO);
        glDeleteBuffers(1, &cylinderVBO);
        glDeleteBuffers(1, &cylinderEBO);
    }

    void drawCylinderWithTexture(Shader& lightingShaderWithTexture, glm::mat4 model = glm::mat4(1.0f))
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

        glBindVertexArray(lightTexCylinderVAO);
        glDrawElements(GL_TRIANGLES, 120, GL_UNSIGNED_INT, 0);
    }

    void drawCylinderWithMaterialisticProperty(Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f))
    {
        lightingShader.use();

        lightingShader.setVec3("material.ambient", this->ambient);
        lightingShader.setVec3("material.diffuse", this->diffuse);
        lightingShader.setVec3("material.specular", this->specular);
        lightingShader.setFloat("material.shininess", this->shininess);

        lightingShader.setMat4("model", model);

        glBindVertexArray(lightCylinderVAO);
        glDrawElements(GL_TRIANGLES, 120, GL_UNSIGNED_INT, 0);
    }

    void drawCylinder(Shader& shader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
    {
        shader.use();

        shader.setVec3("color", glm::vec3(r, g, b));
        shader.setMat4("model", model);

        glBindVertexArray(cylinderVAO);
        glDrawElements(GL_TRIANGLES, 120, GL_UNSIGNED_INT, 0);
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
    unsigned int cylinderVAO;
    unsigned int lightCylinderVAO;
    unsigned int lightTexCylinderVAO;
    unsigned int cylinderVBO;
    unsigned int cylinderEBO;

    void setUpCylinderVertexDataAndConfigureVertexAttribute()
    {
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------

        float cylinder_vertices[] = {
            // positions      // normals         // texture
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, TXmax, TYmax, //0
            0.809017f, 1.0f, 0.587785f, 0.809017f, 1.0f, 0.587785f, TXmax, TYmin,//1
            0.309017f, 1.0f, 0.951057f, 0.309017f, 1.0f, 0.951057f, TXmax, TYmax,//2
            -0.309017f, 1.0f, 0.951057f, -0.309017f, 1.0f, 0.951057f, TXmax, TYmin,//3
            -0.809017f, 1.0f, 0.587785f, -0.809017f, 1.0f, 0.587785f, TXmax, TYmax,//4
            -1.0f, 1.0f, 1.22465e-16f, -1.0f, 1.0f, 1.22465e-16f, TXmax, TYmin,//5
            -0.809017f, 1.0f, -0.587785f, -0.809017f, 1.0f, -0.587785f, TXmax, TYmax,//6
            -0.309017f, 1.0f, -0.951057f, -0.309017f, 1.0f, -0.951057f, TXmax, TYmin,//7
            0.309017f, 1.0f, -0.951057f, 0.309017f, 1.0f, -0.951057f, TXmax, TYmax,//8
            0.809017f, 1.0f, -0.587785f, 0.809017f, 1.0f, -0.587785f, TXmax, TYmin,//9

            1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, TXmin, TYmin,//10
            0.809017f, -1.0f, 0.587785f, 0.809017f, -1.0f, 0.587785f, TXmin, TYmax,//11
            0.309017f, -1.0f, 0.951057f, 0.309017f, -1.0f, 0.951057f, TXmin, TYmin,//12
            -0.309017f, -1.0f, 0.951057f, -0.309017f, -1.0f, 0.951057f, TXmin, TYmax,//13
            -0.809017f, -1.0f, 0.587785f, -0.809017f, -1.0f, 0.587785f, TXmin, TYmin,//14
            -1.0f, -1.0f, 1.22465e-16f, -1.0f, -1.0f, 1.22465e-16f, TXmin, TYmax,//15
            -0.809017f, -1.0f, -0.587785f, -0.809017f, -1.0f, -0.587785f, TXmin, TYmin,//16
            -0.309017f, -1.0f, -0.951057f, -0.309017f, -1.0f, -0.951057f, TXmin, TYmax,//17
            0.309017f, -1.0f, -0.951057f, 0.309017f, -1.0f, -0.951057f, TXmin, TYmin,//18
            0.809017f, -1.0f, -0.587785f, 0.809017f, -1.0f, -0.587785f, TXmin, TYmax,//19

            1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, TXmax, TYmin,//20
            0.809017f, -1.0f, 0.587785f, 0.809017f, -1.0f, 0.587785f, TXmin, TYmax,//21
            0.309017f, -1.0f, 0.951057f, 0.309017f, -1.0f, 0.951057f, TXmax, TYmin,//22
            -0.309017f, -1.0f, 0.951057f, -0.309017f, -1.0f, 0.951057f, TXmin, TYmax,//23
            -0.809017f, -1.0f, 0.587785f, -0.809017f, -1.0f, 0.587785f, TXmax, TYmin,//24
            -1.0f, -1.0f, 1.22465e-16f, -1.0f, -1.0f, 1.22465e-16f, TXmin, TYmax,//25
            -0.809017f, -1.0f, -0.587785f, -0.809017f, -1.0f, -0.587785f, TXmax, TYmin,//26
            -0.309017f, -1.0f, -0.951057f, -0.309017f, -1.0f, -0.951057f, TXmin, TYmax,//27
            0.309017f, -1.0f, -0.951057f, 0.309017f, -1.0f, -0.951057f, TXmax, TYmin,//28
            0.809017f, -1.0f, -0.587785f, 0.809017f, -1.0f, -0.587785f, TXmin, TYmax,//29

            1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, TXmax, TYmin,//30
            0.809017f, 1.0f, 0.587785f, 0.809017f, 1.0f, 0.587785f, TXmin, TYmax,//31
            0.309017f, 1.0f, 0.951057f, 0.309017f, 1.0f, 0.951057f, TXmax, TYmin,//32
            -0.309017f, 1.0f, 0.951057f, -0.309017f, 1.0f, 0.951057f, TXmin, TYmax,//33
            -0.809017f, 1.0f, 0.587785f, -0.809017f, 1.0f, 0.587785f, TXmax, TYmin,//34
            -1.0f, 1.0f, 1.22465e-16f, -1.0f, 1.0f, 1.22465e-16f, TXmin, TYmax,//35
            -0.809017f, 1.0f, -0.587785f, -0.809017f, 1.0f, -0.587785f, TXmax, TYmin,//36
            -0.309017f, 1.0f, -0.951057f, -0.309017f, 1.0f, -0.951057f, TXmin, TYmax,//37
            0.309017f, 1.0f, -0.951057f, 0.309017f, 1.0f, -0.951057f, TXmax, TYmin,//38
            0.809017f, 1.0f, -0.587785f, 0.809017f, 1.0f, -0.587785f, TXmin, TYmax,//39

            0.0,-1.0,0.0, 0.0,-1.0,0.0, TXmax, TYmax,//40
            0.0,1.0,0.0, 0.0,1.0,0.0, TXmax, TYmax//41

        };
        unsigned int cylinder_indices[] = {
            0, 11, 1,
            11, 0, 10,
            1, 12, 2,
            12, 1, 11,
            2, 13, 3,
            13, 2, 12,
            3, 14, 4,
            14, 3, 13,
            4, 15, 5,
            15, 4, 14,
            5, 16, 6,
            16, 5, 15,
            6, 17, 7,
            17, 6, 16,
            7, 18, 8,
            18, 7, 17,
            8, 19, 9,
            19, 8, 18,
            9, 10, 0,
            10, 9, 19,

            40,20,21,
            40,21,22,
            40,22,23,
            40,23,24,
            40,24,25,
            40,25,26,
            40,26,27,
            40,27,28,
            40,28,29,
            40,29,20,

            41,30,31,
            41,31,32,
            41,32,33,
            41,33,34,
            41,34,35,
            41,35,36,
            41,36,37,
            41,37,38,
            41,38,39,
            41,39,30


            /*
            21,10,11,
            21,11,12,
            21,12,13,
            21,13,14,
            21,14,15,
            21,15,16,
            21,16,17,
            21,17,18,
            21,18,19,
            21,19,10*/
        };

        glGenVertexArrays(1, &cylinderVAO);
        glGenVertexArrays(1, &lightCylinderVAO);
        glGenVertexArrays(1, &lightTexCylinderVAO); //for texture
        glGenBuffers(1, &cylinderVBO);
        glGenBuffers(1, &cylinderEBO);


        glBindVertexArray(lightTexCylinderVAO);

        glBindBuffer(GL_ARRAY_BUFFER, cylinderVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cylinder_vertices), cylinder_vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cylinderEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cylinder_indices), cylinder_indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // vertex normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
        glEnableVertexAttribArray(1);

        // texture coordinate attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
        glEnableVertexAttribArray(2);


        glBindVertexArray(lightCylinderVAO);

        glBindBuffer(GL_ARRAY_BUFFER, cylinderVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cylinderEBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
        glEnableVertexAttribArray(1);


        glBindVertexArray(cylinderVAO);

        glBindBuffer(GL_ARRAY_BUFFER, cylinderVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cylinderEBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

};


#endif /* cube_h */
