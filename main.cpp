//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//

#define _CRT_SECURE_NO_DEPRECATE


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "walls.h"
#include "floornstairs.h"
#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "directionalLight.h"
#include "SpotLight.h"
#include "cube.h"
#include "cubeobject.h"
#include "staircube.h"
#include "swings.h"
#include "stairs.h"
#include "lift.h"
#include "stb_image.h"
#include "texture.h"
//#include "sphere.h"
#include "tool.h"
#include "rack.h"
#include "counter.h"
#include "escalatorrail.h"
#include "cylinder.h"
#include "roads.h"
#include "doorheader.h"
#include "escalator.h"
#include "kidz_zone.h"
#include "sofa.h"
#include "triangle.h"
#include "table.h"
//#include "Sphere2.h"
#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);


//curves
void scsToWcs(float sx, float sy, float wcsv[3]);
long long nCr(int n, int r);
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L);
unsigned int hollowBezier(GLfloat ctrlpoints[], int L);
void drawCurve(Shader ourShader, glm::mat4 moveMatrix, unsigned int VAO, vector<int> indices, glm::vec4 color, float rotateAngleTest_Y)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model, rotateYMatrix;

    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngleTest_Y), glm::vec3(0.0f, 1.0f, 0.0f));

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;

    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("material.ambient", color);
    ourShader.setVec4("material.diffuse", color);
    ourShader.setVec4("material.specular", color);
    ourShader.setFloat("material.shininess", 32.0f);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}



// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;

// model, view & projection matrix
glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);
// viewport
GLint viewport[4];

/////////////////////////////////////////////////////////////
float wcsClkDn[3], wcsClkUp[3];
vector <float> cntrlPoints;
vector <float> coordinates;
vector <float> normals;
vector <int> indices;
vector <float> vertices;

bool isOn = true;
bool isFan = false;

void updateSpotlight(const Shader& shader, const glm::vec3& direction)
{
    shader.setVec3("spotlight.direction", direction);

}

void readControlPointsFromFile(const char* filename, std::vector<float>& controlPoints) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        float x, y, z;
        if (!(iss >> x >> y >> z)) {
            std::cout << "Error reading control points from file." << std::endl;
            return;
        }
        cntrlPoints.push_back(x);
        cntrlPoints.push_back(y);
        cntrlPoints.push_back(z);
        cout << x << " " << y << " " << z<<"\n";
    }

    file.close();
}
class point
{
public:
    point()
    {
        x = 0;
        y = 0;
    }
    int x;
    int y;
} clkpt[2];
int mouseButtonFlag = 0;
FILE* fp;
const double pi = 3.14159265389;
const int nt = 40;
const int ntheta = 20;
bool showControlPoints = true;
bool loadBezierCurvePoints = false;
bool showHollowBezier = false;
bool lineMode = false;
unsigned int bezierVAO;


// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

// camera
Camera camera(glm::vec3(0.0f, 12.5f, 7.2f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);

// lights
// positions of the point lights
glm::vec3 pointLightPositions[] = {
     glm::vec3(-6.5f + 3.5f,  3.50f,  -6.5 + 10.25f),
     //glm::vec3(1.5f,  4.5f,  -6.5 + 0.25f),
     glm::vec3(3.5f,  3.5f,   -6.5 + 10.25f),
     //glm::vec3(-1.5f,  4.5f,  -6.5 + 0.25f),
};
PointLight pointlight1(

    //pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    -6.0f, 3.0f, 10.0f,
    1.0f, 1.0f, 1.0f,        // specular
    1.0f, 1.0f, 1.0f,        // specular
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.14f,  //k_l
    0.07f, //k_q
    1       // light number
);

PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.05f, 0.05f, 0.05f,     // ambient
    0.8f, 0.8f, 0.8f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.14f,  //k_l
    0.07f, //k_q
    2      // light number
);

DirLight dirLight(
    0.0f, 1.0f, 0.3f,
    1.0f, 1.0f, 1.0f,        // specular
    1.0f, 1.0f, 1.0f,        // specular
    1.0f, 1.0f, 1.0f        // specular
);
SpotLight spotLight1(
    0.0f, 20.0f, -45.0f,
    0.0f, -1.0f, 0.0f,
    0.9686f, 0.9686f, 0.0f,
    1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,
    0.09f,
    0.032f,
    12.5f,
    15.0f,
    1 //lightnumber
);

SpotLight spotLight2(
    25.0f, 10.0f, -45.0f,
    0.0f, -1.0f, 0.0f,
    0.9686f, 0.9686f, 0.0f,
    1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,
    0.09f,
    0.032f,
    12.5f,
    15.0f,
    2 //lightnumber 2
);



// light settings
bool dirLightOn = true;
bool pointLightOn = true;
bool spotLightOn = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;
bool nightmode = false;

//for door
bool door = false;
//for swing
bool swing = false;
//for lift
bool liftdoor1 = false;
bool liftdoor2 = false;
bool liftdoor3 = false;
bool escalator = true;
bool kids_cylinder = false;
bool washroom_dorja = false;
bool washroom_kol = false;
// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");
    
    //black and whites
    string diffuseMapPath = "dark_wood.jpg"; //loading image path for diffuse.
    string specularMapPath = "tooL_cushion.png"; //loading image path for specular.
    
                                                                //wrapping           //mapping 
    unsigned int specMap_black = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap_white = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    
    //for road
    diffuseMapPath = "road.jpg"; //loading image path for diffuse.
    //wrapping           //mapping 
    unsigned int diffMap_road = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    

    //for footpath
    diffuseMapPath = "footpath.jpeg"; //loading image path for diffuse.
    //wrapping           //mapping 
    unsigned int diffMap_footpath = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_road = Cube(diffMap_road, specMap_black, 52.0f, 0.0f, 0.0f, 50.0f, 1.0f);
    Cube cube_footpath = Cube(diffMap_footpath, specMap_black, 32.0f, 0.0f, 0.0f, 50.0f, 4.0f);
    
    //floor; 
    diffuseMapPath = "tile.png"; //loading image path for diffuse.
    //wrapping           //mapping 
    unsigned int diffMap_tiles = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_floor_tiles = Cube(diffMap_tiles, specMap_white, 52.0f, 0.0f, 0.0f, 5.0f, 6.0f);
    Esc esc = Esc(diffMap_tiles, specMap_white, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    
    //stairs;
    diffuseMapPath = "stair_tiles_image.png"; //loading image path for diffuse.
    //wrapping           //mapping 
    unsigned int diffMap_tiles_stairs = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Staircube cube_stair_tiles = Staircube(diffMap_tiles_stairs, specMap_white, 52.0f, 0.0f, 0.0f, 3.0f, 1.0f);
    //escalator
    diffuseMapPath = "escalator.jpg"; //loading image path for diffuse.
    //wrapping           //mapping 
    unsigned int diffMap_tiles_escalator = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Staircube cube_escalator = Staircube(diffMap_tiles_escalator, specMap_white, 52.0f, 0.0f, 0.0f, 3.0f, 1.0f);

    //

    //cushions
    //tool
    Cylinder cylinder_cushion = Cylinder(specMap_white, specMap_black, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);//base cushion
    //chair
    Cube cube_cushion = Cube(specMap_white, specMap_white, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    
    
    //stair_railing
    diffuseMapPath = "railing.jpg"; //loading image path for diffuse.
    //wrapping           //mapping 
    unsigned int diffMap_stair_railing = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cylinder cylinder_silver = Cylinder(diffMap_stair_railing, specMap_white, 82.0f, 0.0f, 0.0f, 1.0f, 1.0f);//base cushion
    
    
    
    //transparent
    diffuseMapPath = "glass_3.png"; //loading image path for diffuse.
    unsigned int diffMap_glass = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_glass = Cube(diffMap_glass, diffMap_glass, 82.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    
    //wood
    
    diffuseMapPath = "wood.jpeg"; //loading image path for diffuse.
    unsigned int diffMap_wood = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_wood = Cube(diffMap_wood, specMap_black, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cylinder cylinder_dark = Cylinder(diffMap_wood, specMap_black, 82.0f, 0.0f, 0.0f, 1.0f, 1.0f);//base cushion
    
    //woods counter
    diffuseMapPath = "counter.jpg"; //loading image path for diffuse.
    unsigned int diffMap_wood_counter = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_counter_wood = Cube(diffMap_wood_counter, specMap_black, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    //deep_color_wood
    Cube cube_deep_color_wood = Cube(specMap_black, specMap_black, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    Cylinder cylinder_dark_wood = Cylinder(specMap_black, specMap_black, 82.0f, 0.0f, 0.0f, 1.0f, 1.0f);//base cushion
    Triangle triangle_dark_wood = Triangle(specMap_black, specMap_black, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    
    
    //kidz_wall
    
    //tom and jerry
    diffuseMapPath = "tom_jerry.png"; //loading image path for diffuse.
    unsigned int diffMap_tom_jerry = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_tom_jerry = Cube(diffMap_tom_jerry, specMap_black, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    
    //scooby doo
    
    diffuseMapPath = "scooby.jpeg"; //loading image path for diffuse.
    unsigned int diffMap_ben_ten = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_deep_ben_ten = Cube(diffMap_ben_ten, specMap_black, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    
    
    //doremon
    diffuseMapPath = "doremon_image.png"; //loading image path for diffuse.
    unsigned int diffMap_doremon = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_doremon = Cube(diffMap_doremon, specMap_black, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    

    //Restaurant interior
    diffuseMapPath = "restaurant_interior.jpg"; //loading image path for diffuse.
    unsigned int diffMap_rest_wall = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_rest_wall = Cube(diffMap_rest_wall, specMap_black, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "rest1.jpg"; //loading image path for diffuse.
    unsigned int diffMap_rest1 = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_rest1 = Cube(diffMap_rest1, specMap_black, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "rest2.jpg"; //loading image path for diffuse.
    unsigned int diffMap_rest2 = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_rest2 = Cube(diffMap_rest2, specMap_black, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "rest3.jpg"; //loading image path for diffuse.
    unsigned int diffMap_rest3 = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_rest3 = Cube(diffMap_rest3, specMap_black, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "rest4.jpg"; //loading image path for diffuse.
    unsigned int diffMap_rest4 = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_rest4 = Cube(diffMap_rest4, specMap_black, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "rest5.jpg"; //loading image path for diffuse.
    unsigned int diffMap_rest5 = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube_rest5 = Cube(diffMap_rest5, specMap_black, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    

    //shop inside items
    diffuseMapPath = "red_shoe.png"; //loading image path for diffuse.
    unsigned int diffMap_shoe = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cubeobject cube_shoe = Cubeobject(diffMap_shoe, diffMap_shoe, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "fabric_print.png"; //loading image path for diffuse.
    unsigned int diffMap_fabric = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cubeobject cube_fabric = Cubeobject(diffMap_fabric, diffMap_fabric, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "shampoo_stack.png"; //loading image path for diffuse.
    unsigned int diffMap_shampoo = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cubeobject cube_shampoo = Cubeobject(diffMap_shampoo, diffMap_shampoo, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    diffuseMapPath = "perfume2.png"; //loading image path for diffuse.
    unsigned int diffMap_watch = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cubeobject cube_watch = Cubeobject(diffMap_watch, diffMap_watch, 52.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    //dynamic objects
    //door
    float r = 0;
    float time = 0.0f;
    float amplitude = 30.0f;
    float frequency = 0.1f;
    //float y = 0, z = 0;
    float escalator_y = -0.5, escalator_z = -10;
    float escalator_y_down = 9.5, escalator_z_down = -11;
    float cylinder_ghurano_r = 0.0f;
    float washroom_dorja_r = 0.0;
    float washroom_kol_r = 0.0;


    //For lighting shader
    //offwhite
    glm::vec3 ambientColor(0.949f, 0.945f, 0.93f);
    glm::vec3 diffuseColor(1.0f, 1.0f, 1.0f);
    glm::vec3 specularColor(1.0f, 1.0f, 1.0f);
    float shininessValue = 52.0f;
    Cube cube = Cube(ambientColor, diffuseColor, specularColor, shininessValue);

    //red
    glm::vec3 ambientColor_red(0.803f, 0.152f, 0.152f);
    glm::vec3 diffuseColor_red(1.0f, 1.0f, 1.0f);
    glm::vec3 specularColor_red(1.0f, 1.0f, 1.0f);
    Cube cube_red_lego = Cube(ambientColor_red, diffuseColor_red, specularColor_red, shininessValue);
    Cylinder cylinder_red = Cylinder(ambientColor_red, diffuseColor_red, specularColor_red, shininessValue);
    Sphere red_ball= Sphere(1,36,18,ambientColor_red, diffuseColor_red, specularColor_red, shininessValue);

    //_green
    //glm::vec3 ambientColor_green(0.37f, 0.47f, 0.117f);
    glm::vec3 ambientColor_green(0.188f, 0.58f, 0.0f);
    glm::vec3 diffuseColor_green(1.0f, 1.0f, 1.0f);
    glm::vec3 specularColor_green(1.0f, 1.0f, 1.0f);
    Cube cube_green_lego = Cube(ambientColor_green, diffuseColor_green, specularColor_green, shininessValue);
    Cylinder cylinder_green = Cylinder(ambientColor_green, diffuseColor_green, specularColor_green, shininessValue);
    Sphere green_ball = Sphere(1, 36, 18, ambientColor_green, diffuseColor_green, specularColor_green, shininessValue);
    //Triangle triangle_house = Triangle(ambientColor_green, diffuseColor_green, specularColor_green, shininessValue);

    //_blue
    glm::vec3 ambientColor_blue(0.1294f, 0.639f, 0.79f);
    glm::vec3 diffuseColor_blue(1.0f, 1.0f, 1.0f);
    glm::vec3 specularColor_blue(1.0f, 1.0f, 1.0f);
    Cube cube_blue = Cube(ambientColor_blue, diffuseColor_blue, specularColor_blue, shininessValue);

    //paste color
    glm::vec3 ambientColor_paste(0.18f, 0.8f, 0.76f);
    glm::vec3 diffuseColor_paste(1.0f, 1.0f, 1.0f);
    glm::vec3 specularColor_paste(1.0f, 1.0f, 1.0f);
    Cube cube_paste = Cube(ambientColor_paste, diffuseColor_paste, specularColor_paste, shininessValue);

    //yellow
    glm::vec3 ambientColor_yellow(0.9647f, 0.788f, 0.0117f);
    glm::vec3 diffuseColor_yellow(1.0f, 1.0f, 1.0f);
    glm::vec3 specularColor_yellow(1.0f, 1.0f, 1.0f);
    Cube cube_yellow_lego = Cube(ambientColor_yellow, diffuseColor_yellow, specularColor_yellow, shininessValue);
    Triangle triangle_house = Triangle(ambientColor_yellow, diffuseColor_yellow, specularColor_yellow, shininessValue);
    Cylinder cylinder_yellow = Cylinder(ambientColor_yellow, diffuseColor_yellow, specularColor_yellow, shininessValue);
    Sphere yellow_ball = Sphere(1, 36, 18, ambientColor_yellow, diffuseColor_yellow, specularColor_yellow, shininessValue);

    //_dark_ash_color
    glm::vec3 ambientColor_dark_ash_color(0.43f, 0.37f, 0.31f);
    glm::vec3 diffuseColor_dark_ash_color(1.0f, 1.0f, 1.0f);
    glm::vec3 specularColor_dark_ash_color(1.0f, 1.0f, 1.0f);
    Cube cube_dark_ash = Cube(ambientColor_dark_ash_color, diffuseColor_dark_ash_color, specularColor_dark_ash_color, shininessValue);
    Cylinder cylinder_darkash = Cylinder(ambientColor_dark_ash_color, diffuseColor_dark_ash_color, specularColor_dark_ash_color, shininessValue);

    //light_ash_color
    glm::vec3 ambientColor_light_ash_color(0.756f, 0.76f, 0.756f);
    glm::vec3 diffuseColor_light_ash_color(1.0f, 1.0f, 1.0f);
    glm::vec3 specularColor_light_ash_color(1.0f, 1.0f, 1.0f);
    Cylinder cylinder_lightash = Cylinder(ambientColor_light_ash_color, diffuseColor_light_ash_color, specularColor_light_ash_color, shininessValue);
    Cube cube_light_ash = Cube(ambientColor_light_ash_color, diffuseColor_dark_ash_color, specularColor_dark_ash_color, shininessValue);

    //brown color
    glm::vec3 ambientColor_brown(0.56f, 0.2f, 0.05f);
    glm::vec3 diffuseColor_brown(1.0f, 1.0f, 1.0f);
    glm::vec3 specularColor_brown(1.0f, 1.0f, 1.0f);
    Cube cube_brown = Cube(ambientColor_brown, diffuseColor_brown, specularColor_brown, shininessValue);
    Cylinder cylinder_brown = Cylinder(ambientColor_brown, diffuseColor_brown, specularColor_brown, shininessValue);

    
    //curves
    const char* controlPointsFile = "E:/Texture Mapping Student Version/basin_points.txt";
    const char* vasePointsFile = "E:/Texture Mapping Student Version/basin_points.txt";
    // Read control points from file
    readControlPointsFromFile(controlPointsFile, cntrlPoints);

    loadBezierCurvePoints = true;
    showHollowBezier = true;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        if (nightmode) {
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        }
        else {
            glClearColor(0.94f, 0.94f, 0.8f, 1.0f);
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShaderWithTexture.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShaderWithTexture.setMat4("view", view);

        // Modelling Transformation
        
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, model_door;
        

        lightingShaderWithTexture.use();
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        dirLight.setUpDirLight(lightingShaderWithTexture);
        spotLight1.setUpSpotLight(lightingShaderWithTexture);
        spotLight2.setUpSpotLight(lightingShaderWithTexture);

        
     

        
        
   
        //interior plan
        stair(lightingShaderWithTexture, cylinder_silver, cube_stair_tiles);
        roads(lightingShaderWithTexture, cube_road, cube_footpath);
        tools(lightingShaderWithTexture, cylinder_cushion, cylinder_dark);
        showcaserack(lightingShaderWithTexture, cube_wood, cube_shoe, cube_fabric, cube_shampoo, cube_watch);
        counter_draw(lightingShaderWithTexture, cube_counter_wood, cube_rest_wall);
        swinging(lightingShaderWithTexture, cube_wood);
        door_bar(lightingShaderWithTexture, cube_glass);
        kidz_wall(lightingShaderWithTexture, cube_tom_jerry, cube_deep_ben_ten, cube_doremon);
        sofa(lightingShaderWithTexture, cube_wood, cube_cushion);
        circular_table(lightingShaderWithTexture, cylinder_dark_wood,triangle_dark_wood);
        restaurant_interior(lightingShaderWithTexture, cube_rest_wall, cube_rest1, cube_rest2, cube_rest3, cube_rest4, cube_rest5);
        floor_stairs(lightingShaderWithTexture, cube_floor_tiles);
        tables_four_leg(lightingShaderWithTexture, cube_deep_color_wood);



        //dynamic objects

        //escalator railing
        float esc_x = 1.4, esc_z = -12.0;
        float esc_scale = 13.542;
        for (int i = 0; i < 4; i++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(esc_x, 0.5, esc_z));
            rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1, esc_scale, 2.0));
            model = translateMatrix * rotateXMatrix * scaleMatrix;
            cube_glass.drawCubeWithTexture(lightingShaderWithTexture, model);
            esc_x += 3.1;
            if (i == 1) {
                esc_x = 5.5 - .1;
                //esc_z = -11;
                //esc_scale = 14.142;
            }
        }
        
        //escalator
        if (escalator) {
            escalator_y += 0.005;
            escalator_z -= 0.005;
            escalator_y_down -= 0.005;
            escalator_z_down += 0.005;
            if (escalator_y >= 0.5) {
                escalator_y = -0.5;
            }
            if (escalator_z <= -11) {
                escalator_z = -10.0;
            }
            if (escalator_y_down <= 8.5) {
                escalator_y_down = 9.5;
            }
            if (escalator_z_down >= -10) {
                escalator_z_down = -11.0;
            }
            escalator_moves(lightingShaderWithTexture, cube_escalator,esc, escalator_y, escalator_z,escalator_y_down, escalator_z_down);

            //cout << escalator << "\n";
        }

        translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5-3, 0.5, -23.25));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.5+3, 2.5, 4.5));
        model = translateMatrix * scaleMatrix;
        cube_wood.drawCubeWithTexture(lightingShaderWithTexture, model);
            
        
        //swing
        if (swing) {
            //pivot point
            glm::vec3 seatPivotPoint(-14.95, 8.0, -47.5);
            float angle = amplitude * sin(frequency * time);
            rotateZMatrix = glm::rotate(identityMatrix, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
            glm::mat4 model_swing = glm::translate(identityMatrix, glm::vec3(-14.95, 8.0, -47.5)) * rotateZMatrix * glm::translate(identityMatrix, glm::vec3(14.95, -8.0, 47.5));
            swing_it(lightingShaderWithTexture, model_swing, cube_wood, cube_cushion);
            time += .25;

        }

        else {
            rotateZMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            glm::mat4 model_swing = glm::translate(identityMatrix, glm::vec3(-14.95, 8.0, -47.5)) * rotateZMatrix * glm::translate(identityMatrix, glm::vec3(14.95, -8.0, 47.5));
            swing_it(lightingShaderWithTexture, model_swing, cube_wood, cube_cushion);
        }
        
        //door
        if (door) {

            r += 0.5;
            if (r > 90.0f) {
                r = 90.0f;
            }
            open_door(lightingShaderWithTexture, cube_glass, r);

        }
        else if (!door) {

            r -= 0.5;
            if (r < 0.0f) {
                r = 0.0f;
            }
            open_door(lightingShaderWithTexture, cube_glass, r);

        }
        

        if (washroom_dorja) {

            washroom_dorja_r -= 0.5;
            if (washroom_dorja_r < -90.0f) {
                washroom_dorja_r = -90.0f;
            }
            //washroom_doors
            float x_axis = 15.5;
            for (int i = 0; i < 2; i++) {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(x_axis, 10.5, -33.875));
                rotateYMatrix = glm::rotate(identityMatrix, glm::radians(washroom_dorja_r), glm::vec3(0.0f, 1.0f, 0.0f));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(3 - .5, 7.0, .25));
                model = translateMatrix * rotateYMatrix * scaleMatrix;
                cube_deep_color_wood.drawCubeWithTexture(lightingShaderWithTexture, model);
                x_axis = 27.25;

            }
        }
        else if (!washroom_dorja) {

            washroom_dorja_r += 0.5;
            if (washroom_dorja_r > 0.0f) {
                washroom_dorja_r = 0.0f;
            }
            //washroom_doors
            float x_axis = 15.5;
            for (int i = 0; i < 2; i++) {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(x_axis, 10.5, -33.875));
                rotateYMatrix = glm::rotate(identityMatrix, glm::radians(washroom_dorja_r), glm::vec3(0.0f, 1.0f, 0.0f));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(3 - .5, 7.0, .25));
                model = translateMatrix * rotateYMatrix * scaleMatrix;
                cube_deep_color_wood.drawCubeWithTexture(lightingShaderWithTexture, model);
                x_axis = 27.25;

            }
        }
        
        /*
        //third floor lift door
        if (liftdoor3) {
            //dorja off ase; eta dile khulbe
            float j = 0.0;

            if (j <= 1.5) {
                j += .125;
            }
            open_lift_door(lightingShaderWithTexture, model, cube_stainless, 20.5, -6, j);//right side door
            open_lift_door(lightingShaderWithTexture, model, cube_stainless, 20.5, -1.625, -j);//left side door
            take_lift_to_floors(lightingShaderWithTexture, model, cube_steel_with_khaj_kata, 20.5, -j);//left side door

        }
        else if (!liftdoor3) {
            float j = 0.0;


            if (j >= -1.5) {
                j -= .125;
            }
            open_lift_door(lightingShaderWithTexture, model, cube_stainless, 20.5, -4.5, j);//right side door
            open_lift_door(lightingShaderWithTexture, model, cube_stainless, 20.5, -3.125, -j);//left side door

        }
        
        
        */
        
        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // Create the glm::vec3 objects for ambient, diffuse, and specular, and a float for shininess.
    
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        lightingShader.use();

        pointlight1.setUpPointLight(lightingShader);
        pointlight3.setUpPointLight(lightingShader);
        dirLight.setUpDirLight(lightingShader);
        spotLight1.setUpSpotLight(lightingShader);
        spotLight2.setUpSpotLight(lightingShader);

        
        walls(lightingShader, cube);
        kidz_house(lightingShader, cube_red_lego, cube_green_lego,cube_yellow_lego, triangle_house);
        kidz_slide(lightingShader, cube_red_lego, cube_green_lego, cube_brown);
        kidz_circle(lightingShader, red_ball, green_ball, yellow_ball);
        liftwalls(lightingShader, cube);

        /*dynamic objects*/

        //lift
        //Ground floor lift door

        if (liftdoor1) {
            //dorja off ase, eta dile khule jabe
            float j = 0.0;

            if (j <= 1.5) {
                j += .125;
            }
            open_lift_door(lightingShader, cube_dark_ash, 0.5, -6, j);//right side door
            open_lift_door(lightingShader, cube_dark_ash, 0.5, -1.625, -j);//left side door
            //printf("lift opened");
            take_lift_to_floors(lightingShader, cube_light_ash, 0.5, -j);//left side door

        }
        else if (!liftdoor1) {
            float j = 0.0;

            if (j >= -1.5) {
                j -= .125;
            }
            open_lift_door(lightingShader, cube_dark_ash, 0.5, -4.5, j);//right side door
            open_lift_door(lightingShader, cube_dark_ash, 0.5, -3.125, -j);//left side door
            //printf("closed");

        }

        //second floor lift door
        if (liftdoor2) {
            //dorja off ase; eta dile khulbe
            float j = 0.0;

            if (j <= 1.5) {
                j += .125;
            }
            open_lift_door(lightingShader, cube_dark_ash, 10.5, -6, j);//right side door
            open_lift_door(lightingShader, cube_dark_ash, 10.5, -1.625, -j);//left side door
            take_lift_to_floors(lightingShader, cube_light_ash, 10.5, -j);//left side door

        }
        else if (!liftdoor2) {
            float j = 0.0;

            if (j >= -1.5) {
                j -= .125;
            }
            open_lift_door(lightingShader, cube_dark_ash, 10.5, -4.5, j);//right side door
            open_lift_door(lightingShader, cube_dark_ash, 10.5, -3.125, -j);//left side door

        }

        if (kids_cylinder) {

            cylinder_ghurano_r += 0.5;
            
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(cylinder_ghurano_r), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::translate(identityMatrix, glm::vec3(0.0, 1, -45)) * rotateYMatrix * glm::translate(identityMatrix, glm::vec3(0.0, -1, 45));
            kidz_cylinder(lightingShader, model, cylinder_green ,cylinder_yellow, cylinder_red , cylinder_brown, cube_blue, cube_paste);

        }
        else {
            rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::translate(identityMatrix, glm::vec3(0.0, 1, -45)) * rotateYMatrix * glm::translate(identityMatrix, glm::vec3(0.0, -1, 45));
            kidz_cylinder(lightingShader, model, cylinder_green, cylinder_yellow, cylinder_red, cylinder_brown, cube_blue, cube_paste);

        }

        //curve
        glm::mat4 model3,model_basin1, model_basin2, model_basin1_pipe, model_basin2_pipe;
        if (loadBezierCurvePoints)
        {
            bezierVAO = hollowBezier(cntrlPoints.data(), ((unsigned int)cntrlPoints.size() / 3) - 1);
            loadBezierCurvePoints = false;
            showHollowBezier = true;
            showControlPoints = false;
        }
        if (showHollowBezier)
        {
            //cout << "true" << "\n";
            //chader boro light ta
            translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0, 12.5, -25.0));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0, 5.0, 4.0));
            model3 = translateMatrix * scaleMatrix;

            lightingShader.use();
            
            lightingShader.setMat4("model", model3);
            lightingShader.setVec3("material.ambient", glm::vec3(0.89f, 0.87f, 0.83f));
            lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 0.0f));
            lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
            lightingShader.setFloat("material.shininess", 32.0f);

            
            glBindVertexArray(bezierVAO);
            glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
            glBindVertexArray(0);

            //basin1
            translateMatrix = glm::translate(identityMatrix, glm::vec3(24.5, 10.5, -31.5));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.7, 1.3, 1.5));
            model_basin1 = translateMatrix * scaleMatrix;
            lightingShader.setMat4("model", model_basin1);
            lightingShader.setVec3("material.ambient", glm::vec3(0.945f, 0.835f, 0.74f));
            lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 0.0f));
            lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
            lightingShader.setFloat("material.shininess", 32.0f);
            
            glBindVertexArray(bezierVAO);
            glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
            glBindVertexArray(0);


            //basin2
            translateMatrix = glm::translate(identityMatrix, glm::vec3(20.5, 10.5, -31.5));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.7, 1.3, 1.5));
            model_basin2 = translateMatrix * scaleMatrix;
            lightingShader.setMat4("model", model_basin2);
            lightingShader.setVec3("material.ambient", glm::vec3(0.945f, 0.835f, 0.74f));
            lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 0.0f));
            lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
            lightingShader.setFloat("material.shininess", 32.0f);

            glBindVertexArray(bezierVAO);
            glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
            glBindVertexArray(0);
/*
            //spot light on restaurant
            translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0, 20.5, -45));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1.3, 1.5));
            model_basin2 = translateMatrix * scaleMatrix;
            lightingShader.setMat4("model", model_basin2);
            lightingShader.setVec3("material.ambient", glm::vec3(0.792f, 0.67f, 0.584f));
            lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 0.0f));
            lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
            lightingShader.setFloat("material.shininess", 32.0f);

            glBindVertexArray(bezierVAO);
            glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
            glBindVertexArray(0);
*/

        }
        
        float x_axis = 20.5;
        //basin pipes
        for (int i = 0; i < 2; i++) {
            //inner side basin pipe
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x_axis, 11.2, -31.5));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.25, .75, .25));
            model_basin1_pipe = translateMatrix * scaleMatrix;
            cylinder_lightash.drawCylinderWithMaterialisticProperty(lightingShader, model_basin1_pipe);
            x_axis = 24.5;
        }
        
        x_axis = 20.5;
        //basin kol lomba part
        for (int i = 0; i < 2; i++) {
            //inner side basin pipe
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x_axis, 12.75, -30.5));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05, 0.25, .05));
            model_basin2_pipe = translateMatrix * scaleMatrix;
            cylinder_darkash.drawCylinderWithMaterialisticProperty(lightingShader, model_basin2_pipe);
            x_axis = 24.5;
        }

        //kol handle
        //eta ghurbe
        x_axis = 20.45;
        
        if (washroom_kol) {
            washroom_kol_r -= 0.5;
            //kol open korbe pani porbe
            if (washroom_kol_r < -90.0f) {
                washroom_kol_r = -90.0f;
            }
            for (int i = 0; i < 2; i++) {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(x_axis, 12.95, -30.5));
                rotateYMatrix = glm::rotate(identityMatrix, glm::radians(washroom_kol_r), glm::vec3(0.0f, 1.0f, 0.0f));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05 * 2, 0.05, -.15));
                model_basin2_pipe = translateMatrix * rotateYMatrix * scaleMatrix;
                cube_dark_ash.drawCubeWithMaterialisticProperty(lightingShader, model_basin2_pipe);
                //pani portese
                translateMatrix = glm::translate(identityMatrix, glm::vec3(x_axis, 12.75, -31.0));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05 * 2, 0.0083*washroom_kol_r, .1));
                model_basin2_pipe = translateMatrix * scaleMatrix;
                cube_blue.drawCubeWithMaterialisticProperty(lightingShader, model_basin2_pipe);

                x_axis = 24.45;
            }
        }
        else if (!washroom_kol) {
            //kol off hobe, pani pora off hobe
            washroom_kol_r += 0.5;
            if (washroom_kol_r > 0.0f) {
                washroom_kol_r = 0.0f;
            }
            for (int i = 0; i < 2; i++) {
                translateMatrix = glm::translate(identityMatrix, glm::vec3(x_axis, 12.95, -30.5));
                rotateYMatrix = glm::rotate(identityMatrix, glm::radians(washroom_kol_r), glm::vec3(0.0f, 1.0f, 0.0f));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05 * 2, 0.05, -.15));
                model_basin2_pipe = translateMatrix * rotateYMatrix * scaleMatrix;
                cube_dark_ash.drawCubeWithMaterialisticProperty(lightingShader, model_basin2_pipe);
                //pani pora off hoye jabe
                translateMatrix = glm::translate(identityMatrix, glm::vec3(x_axis, 12.75, -31.0));
                scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05 * 2, 0.0083 * washroom_kol_r, .1));
                model_basin2_pipe = translateMatrix * scaleMatrix;
                cube_blue.drawCubeWithMaterialisticProperty(lightingShader, model_basin2_pipe);

                x_axis = 24.45;
            }
        }
        //kol pani porar jayga
        x_axis = 20.45;
        for (int i = 0; i < 2; i++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x_axis, 12.75, -30.5));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(.05 * 2, 0.05, -.5));
            model_basin1_pipe = translateMatrix * scaleMatrix;
            cube_dark_ash.drawCubeWithMaterialisticProperty(lightingShader, model_basin1_pipe);
            x_axis = 24.45;
        }

        // we now draw as many light bulbs as we have point lights.
        /*
        for (unsigned int i = 0; i < 2; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            cube.drawCube(ourShader, model, 0.8f, 0.8f, 0.8f);
        }
        */
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_RIGHT, deltaTime);
    }
    
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        pointlight1.turnOn();
        pointlight3.turnOn();
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        pointlight1.turnOff();
        pointlight3.turnOff();

    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        pointlight1.turnDiffuseOn();
        pointlight3.turnDiffuseOn();
        spotLight1.turnDiffuseOn();
        spotLight2.turnDiffuseOn();
        dirLight.turnDiffuseOn();

    }
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {

        pointlight1.turnOff();
        pointlight3.turnOff();
        dirLight.turnOff();
        spotLight1.turnOff();
        spotLight2.turnOff();

    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        dirLight.turnOn();

    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        dirLight.turnOff();
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        spotLight1.turnOn();
        spotLight2.turnOn();


    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        spotLight1.turnOff();
        spotLight2.turnOff();

    }
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
    {
        pointlight1.turnAmbientOn();
        pointlight3.turnAmbientOn();
        spotLight1.turnAmbientOn();
        spotLight2.turnAmbientOn();
        dirLight.turnAmbientOn();
    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        pointlight1.turnSpecularOn();
        pointlight3.turnSpecularOn();
        spotLight1.turnSpecularOn();
        spotLight2.turnSpecularOn();
        dirLight.turnSpecularOn();
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        if (door) {
            door = false;
        }
        else
        {
            door = true;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        if (swing) {
            swing = false;
        }
        else
        {
            swing = true;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        if (washroom_kol) {
            washroom_kol = false;
        }
        else
        {
            washroom_kol = true;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        if (washroom_dorja) {
            washroom_dorja = false;
        }
        else
        {
            washroom_dorja = true;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        if (kids_cylinder) {
            kids_cylinder = false;
        }
        else
        {
            kids_cylinder = true;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        if (liftdoor1) {
            liftdoor1 = false;
        }
        else
        {
            liftdoor1 = true;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
        if (liftdoor2) {
            liftdoor2 = false;
        }
        else
        {
            liftdoor2 = true;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        if (nightmode) {
            nightmode = false;
        }
        else
        {
            nightmode = true;
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true); //loading texture
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0); //call by referencing width, height, and then channels
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data); //0->bitp level. if incresead the resolution will drop
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS); //texturemapping and wrapping , along S axis
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT); //for T axis
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin); //minification mode filter
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    //binding with texture id.

    return textureID;
}









// This function converts the screen coordinates to world coordinates
// ---------------------------------------------------------------------------------------------
void scsToWcs(float sx, float sy, float wcsv[3])
{

    glm::vec4 winCoordinateVector; //vector to hold screen x,y,z coordinates
    glm::vec4 worldCoordinateVector; //vector to hold world x,y,z coordinates

    glGetIntegerv(GL_VIEWPORT, viewport); //get the viewport info

    // setup screen coordinates values
    winCoordinateVector.x = sx;
    winCoordinateVector.y = (float)viewport[3] - (float)sy; // reversed since y-coordinates go from bottom to top
    winCoordinateVector.z = 0.0f;
    winCoordinateVector.w = 1.0f;

    // prepare viewport matrix
    float v_l = viewport[0], v_b = viewport[1], v_r = viewport[2], v_t = viewport[3];
    glm::mat4 viewportMat = glm::mat4(1.0f);
    viewportMat[0].x = (v_r - v_l) / 2.0f;  viewportMat[1].x = 0.0f; viewportMat[2].x = 0.0f;  viewportMat[3].x = (v_r + v_l) / 2.0f;
    viewportMat[0].y = 0.0f; viewportMat[1].y = (v_t - v_b) / 2.0f;  viewportMat[2].y = 0.0f;  viewportMat[3].y = (v_t + v_b) / 2.0f;
    viewportMat[0].z = 0.0f; viewportMat[1].z = 0.0f; viewportMat[2].z = 0.5f;  viewportMat[3].z = 0.5f;
    viewportMat[0].w = 0.0f; viewportMat[1].w = 0.0f; viewportMat[2].w = 0.0f;  viewportMat[3].w = 1.0f;

    //get the world coordinates from the screen coordinates
    worldCoordinateVector = glm::inverse(viewportMat * projection * view * model) * winCoordinateVector;
    wcsv[0] = worldCoordinateVector.x / worldCoordinateVector.w;
    wcsv[1] = worldCoordinateVector.y / worldCoordinateVector.w;
    wcsv[2] = worldCoordinateVector.z / worldCoordinateVector.w;
}

// glfw: whenever mouse button is pressed, this callback is called
// -------------------------------------------------------



long long nCr(int n, int r)
{
    if (r > n / 2)
        r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for (i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//polynomial interpretation for N points
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L)
{
    double y = 0;
    double x = 0;
    t = t > 1.0 ? 1.0 : t;
    for (int i = 0; i < L + 1; i++)
    {
        long long ncr = nCr(L, i);
        double oneMinusTpow = pow(1 - t, double(L - i));
        double tPow = pow(t, double(i));
        double coef = oneMinusTpow * tPow * ncr;
        x += coef * ctrlpoints[i * 3];
        y += coef * ctrlpoints[(i * 3) + 1];

    }
    xy[0] = float(x);
    xy[1] = float(y);
}

unsigned int hollowBezier(GLfloat ctrlpoints[], int L)
{
    int i, j;
    float x, y, z, r;                //current coordinates
    float theta;
    float nx, ny, nz, lengthInv;    // vertex normal


    const float dtheta = 2 * pi / ntheta;        //angular step size

    float t = 0;
    float dt = 1.0 / nt;
    float xy[2];

    for (i = 0; i <= nt; ++i)              //step through y
    {
        BezierCurve(t, xy, ctrlpoints, L);
        r = xy[0];
        y = xy[1];
        theta = 0;
        t += dt;
        lengthInv = 1.0 / r;

        for (j = 0; j <= ntheta; ++j)
        {
            double cosa = cos(theta);
            double sina = sin(theta);
            z = r * cosa;
            x = r * sina;

            coordinates.push_back(x);
            coordinates.push_back(y);
            coordinates.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            // center point of the circle (0,y,0)
            nx = (x - 0) * lengthInv;
            ny = (y - y) * lengthInv;
            nz = (z - 0) * lengthInv;

            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            theta += dtheta;
        }
    }

    // generate index list of triangles
    // k1--k1+1
    // |  / |
    // | /  |
    // k2--k2+1

    int k1, k2;
    for (int i = 0; i < nt; ++i)
    {
        k1 = i * (ntheta + 1);     // beginning of current stack
        k2 = k1 + ntheta + 1;      // beginning of next stack

        for (int j = 0; j < ntheta; ++j, ++k1, ++k2)
        {
            // k1 => k2 => k1+1
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);

            // k1+1 => k2 => k2+1
            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k2 + 1);
        }
    }

    size_t count = coordinates.size();
    for (int i = 0; i < count; i += 3)
    {
        vertices.push_back(coordinates[i]);
        vertices.push_back(coordinates[i + 1]);
        vertices.push_back(coordinates[i + 2]);

        vertices.push_back(normals[i]);
        vertices.push_back(normals[i + 1]);
        vertices.push_back(normals[i + 2]);
    }

    unsigned int bezierVAO;
    glGenVertexArrays(1, &bezierVAO);
    glBindVertexArray(bezierVAO);

    // create VBO to copy vertex data to VBO
    unsigned int bezierVBO;
    glGenBuffers(1, &bezierVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bezierVBO);           // for vertex data
    glBufferData(GL_ARRAY_BUFFER,                   // target
        (unsigned int)vertices.size() * sizeof(float), // data size, # of bytes
        vertices.data(),   // ptr to vertex data
        GL_STATIC_DRAW);                   // usage

    // create EBO to copy index data
    unsigned int bezierEBO;
    glGenBuffers(1, &bezierEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bezierEBO);   // for index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
        (unsigned int)indices.size() * sizeof(unsigned int),             // data size, # of bytes
        indices.data(),               // ptr to index data
        GL_STATIC_DRAW);                   // usage

    // activate attrib arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // set attrib arrays with stride and offset
    int stride = 24;     // should be 24 bytes
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3));

    // unbind VAO, VBO and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return bezierVAO;
}
