#include "shader.h"
#include "mesh.h"
#include "camera.h"
#include "head.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

                                               
glm::vec3 rgbToFloats(int red, int green, int blue);
unsigned int loadTexture(const char * path);

unsigned int window_width = 1024;                       //  initial width of window
unsigned int window_height = 600;                       //  initial height of window
glm::vec3 backgroundColor(rgbToFloats(0, 0, 0));        //  window background color

unique_ptr<Camera> cameraPtr(new Camera);               //  create camera instance and use default camera position

bool lampOrbit = false;                                 //  holds if lamp orbit is active
bool lampVisible = false;                               //  holds lamp object visibility
unsigned activeLamp = 0;
                                                        //  specify all light position
glm::vec3 lightPositionOne(-5.0f, 5.0f, 0.0f);
glm::vec3 lightPositionTwo(-5.0f, 5.0f, -6.0f);
glm::vec3 lightPositionThree(-5.0f, 5.0f, 6.0f);
glm::vec3 lightPositionFour(-3.5f, 10.0f, -0.0f);
                                                        //  specify all light colors
glm::vec3 lightColorOne(150.0f, 150.0f, 150.0f);
glm::vec3 lightColorTwo(150.0f, 150.0f, 150.0f);
glm::vec3 lightColorThree(150.0f, 150.0f, 150.0f);
glm::vec3 lightColorFour(150.0f, 150.0f, 150.0f);

const int objectCount = 96;                             //  holds number of game objects(game board and figurines)
glm::vec3 positions[objectCount + 36];                  //  positions of all game objects(includes game board border)
bool isWhite[objectCount];                              //  colors of all game objects(includes game board border)
int highlight[objectCount];                             //  highlight indiced of all game objects

int clicked = -1;                                       //  holds actual index of mouse click selection

class Chess                                             //  represents implementation of chess game logic
{
private:
    bool blackTurn = false;                             //  holds if black turns on the turn

    string board[8];                                    //  holds board indices which indicates color move highlights
    string figurines[8];                                //  holds indices of all figurines
    string temp[8];                                     //  generic array used as a temporal storage
    string linear;                                      //  holds type of figurine on concrete
    string real;                                        //  holds real type of figurine places on a linear coordinate


public:
                                   //  holds actual timestamp value

    Chess()                                             //  one and only class constructor
    {
        board[7] = "........";                          //  bwbwbwbw
        board[6] = "........";                          //  wbwbwbwb
        board[5] = "........";                          //  bwbwbwbw
        board[4] = "........";                          //  wbwbwbwb
        board[3] = "........";                          //  bwbwbwbw
        board[2] = "........";                          //  wbwbwbwb
        board[1] = "........";                          //  bwbwbwbw
        board[0] = "........";                          //  wbwbwbwb

        figurines[7] = "ph....HP";                      //  B  rp....PR  W
        figurines[6] = "og....GO";                      //  B  np....PN  W
        figurines[5] = "nf....FN";                      //  B  bp....PB  W
        figurines[4] = "me....EM";                      //  B  kp....PK  W
        figurines[3] = "ld....DL";                      //  B  qp....PQ  W
        figurines[2] = "kc....CK";                      //  B  bp....PB  W
        figurines[1] = "jb....BJ";                      //  B  np....PN  W
        figurines[0] = "ia....AI";                      //  B  rp....PR  W

        // figurines[7] = "p......P";                      //  B  rp....PR  W
        // figurines[6] = "........";                      //  B  np....PN  W
        // figurines[5] = "........";                      //  B  bp....PB  W
        // figurines[4] = "m......M";                      //  B  kp....PK  W
        // figurines[3] = "........";                      //  B  qp....PQ  W
        // figurines[2] = "........";                      //  B  bp....PB  W
        // figurines[1] = "........";                      //  B  np....PN  W
        // figurines[0] = "i......I";                      //  B  rp....PR  W

        linear = "ppppppppPPPPPPPPrnbqkbnrRNBQKBNR";
        real = "abcdefghABCDEFGHijklmnopIJKLMNOP";

        // linear = "................r...k..rR...K..R";
        // real = "abcdefghABCDEFGHijklmnopIJKLMNOP";

        
    }

    string getLinear()                                  //  linear string getter
    {
        return linear;
    }

    char toLinear(char figurine)                        //  get linear value of desired figurine
    {
        for (int i = 0; i < 32; i++)
        {
            if (real[i] == figurine)
                return linear[i];
        }

        return '.';
    }

};
int main(int argc, char ** argv)                        //  required main method implementation
{
    ios_base::sync_with_stdio(false);

    bool fullscreen = false;


    glfwInit();                                         //  initialize GLFW window and set GLFW version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    if (fullscreen)
    {
        const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());   //  get actual resolution of the screen

        if (mode)
        {
            window_width = mode->width;
            window_height = mode->height;
        }
    }

    GLFWwindow * window;

    if (fullscreen)                                     //  toggle fullscreen mode by the appropriate flag value
        window = glfwCreateWindow(window_width, window_height, "Chess", glfwGetPrimaryMonitor(), nullptr);
    else
        window = glfwCreateWindow(window_width, window_height, "Chess", nullptr, nullptr);

    if (window == nullptr)                              //  window has not been created successfully
    {
        cerr << "GLFW window has not been created successfully" << endl;
        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);                     //  set GLFW context
   
   

    glEnable(GL_DEPTH_TEST);                            //  enable depth and stencil test
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_MULTISAMPLE);                           //  multisampling is going to be used

    unique_ptr<Chess> chessPtr(new Chess);              //  create chess game logic instance
                                                        //  load all required models
    unique_ptr<Mesh> cubePtr(new Mesh( "res/models/block/positions.txt",  "res/models/block/normals.txt", "res/models/block/indices.txt", "res/models/block/uv.txt"));
    unique_ptr<Mesh> rookPtr(new Mesh( "res/models/rook/positions.txt",  "res/models/rook/normals.txt", "res/models/rook/indices.txt", "res/models/rook/uv.txt"));
    unique_ptr<Mesh> knightPtr(new Mesh( "res/models/knight/positions.txt",  "res/models/knight/normals.txt", "res/models/knight/indices.txt", "res/models/knight/uv.txt"));
    unique_ptr<Mesh> bishopPtr(new Mesh( "res/models/bishop/positions.txt",  "res/models/bishop/normals.txt", "res/models/bishop/indices.txt", "res/models/bishop/uv.txt"));
    unique_ptr<Mesh> kingPtr(new Mesh( "res/models/king/positions.txt",  "res/models/king/normals.txt", "res/models/king/indices.txt", "res/models/king/uv.txt"));
    unique_ptr<Mesh> queenPtr(new Mesh( "res/models/queen/positions.txt",  "res/models/queen/normals.txt", "res/models/queen/indices.txt", "res/models/queen/uv.txt"));
    unique_ptr<Mesh> pawnPtr(new Mesh( "res/models/pawn/positions.txt",  "res/models/pawn/normals.txt", "res/models/pawn/indices.txt", "res/models/pawn/uv.txt"));

    unique_ptr<Shader> shaderPBR(new Shader( "res/shaders/pbr.vs",  "res/shaders/pbr.fs"));

    shaderPBR->activate();                              //  setup and activate PBR shader
    shaderPBR->passInteger("albedoMap", 0);
    shaderPBR->passInteger("normalMap", 1);
    shaderPBR->passInteger("metallicMap", 2);
    shaderPBR->passInteger("roughnessMap", 3);
    shaderPBR->passInteger("aoMap", 4);

    unsigned int albedoRed = loadTexture("res/models/textures/highlight/albedoRed.png");   //  load all color textures
    unsigned int albedoGreen = loadTexture( "res/models/textures/highlight/albedoGreen.png");
    unsigned int albedoBlue = loadTexture( "res/models/textures/highlight/albedoBlue.png");
    unsigned int albedoYellow = loadTexture( "res/models/textures/highlight/albedoYellow.png");
    unsigned int albedoWhite = loadTexture("res/models/textures/highlight/albedoWhite.png");
    unsigned int albedoBlack = loadTexture("res/models/textures/highlight/albedoBlack.png");

    unsigned int normalHighlight = loadTexture( "res/models/textures/highlight/normal.png");    //  load all highlight textures
    unsigned int metallicHighlight = loadTexture( "res/models/textures/highlight/metallic.png");
    unsigned int roughnessHighlight = loadTexture( "res/models/textures/highlight/roughness.png");
    unsigned int aoHighlight = loadTexture("res/models/textures/highlight/ao.png");

    unsigned int albedoBlackFigurine = loadTexture( "res/models/textures/blackFigurine/albedo.png");    //  load all textures for black figurines
    unsigned int normalBlackFigurine = loadTexture("res/models/textures/blackFigurine/normal.png");
    unsigned int metallicBlackFigurine = loadTexture( "res/models/textures/blackFigurine/metallic.png");
    unsigned int roughnessBlackFigurine = loadTexture( "res/models/textures/blackFigurine/roughness.png");
    unsigned int aoBlackFigurine = loadTexture( "res/models/textures/blackFigurine/ao.png");

    unsigned int albedoWhiteBlock = loadTexture( "res/models/textures/whiteBlock/albedo.png");      //  load all textures for white blocks
    unsigned int normalWhiteBlock = loadTexture( "res/models/textures/whiteBlock/normal.png");
    unsigned int metallicWhiteBlock = loadTexture("res/models/textures/whiteBlock/metallic.png");
    unsigned int roughnessWhiteBlock = loadTexture( "res/models/textures/whiteBlock/roughness.png");
    unsigned int aoWhiteBlock = loadTexture( "res/models/textures/whiteBlock/ao.png");

    unsigned int albedoBlackBlock = loadTexture( "res/models/textures/blackBlock/albedo.png");      //  load all textures for black blocks
    unsigned int normalBlackBlock = loadTexture( "res/models/textures/blackBlock/normal.png");
    unsigned int metallicBlackBlock = loadTexture( "res/models/textures/blackBlock/metallic.png");
    unsigned int roughnessBlackBlock = loadTexture("res/models/textures/blackBlock/roughness.png");
    unsigned int aoBlackBlock = loadTexture( "res/models/textures/blackBlock/ao.png");

    unsigned int albedoWhiteFigurine = loadTexture( "res/models/textures/whiteFigurine/albedo.png");    //  load all textures for white figurines
    unsigned int normalWhiteFigurine = loadTexture( "res/models/textures/whiteFigurine/normal.png");
    unsigned int metallicWhiteFigurine = loadTexture( "res/models/textures/whiteFigurine/metallic.png");
    unsigned int roughnessWhiteFigurine = loadTexture("res/models/textures/whiteFigurine/roughness.png");
    unsigned int aoWhiteFigurine = loadTexture( "res/models/textures/whiteFigurine/ao.png");

    glm::mat4 projection = glm::mat4(1.0f);             //  create new projection matrix
    projection = glm::perspective(glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);   //  setup projection matrix
    shaderPBR->activate();
    shaderPBR->passMatrix("projection", projection);    //  pass projection matrix into the PBR shader

    for (int i = 0; i < 8; i++)                         //  initialize first row of game board blocks
    {
        float offset = float(i) * 0.4f;                 //  handle object offset

        positions[i] = glm::vec3(offset, 0.0f, 0.0f);
        highlight[i] = 0;                               //  nothing is highlighted by default

        if (i & 1)                                      //  set value of the color flag
            isWhite[i] = false;
        else
            isWhite[i] = true;
    }

    for (int i = 0; i < 8; i++)                         //  initialize second row of game board blocks
    {
        float offset = float(i) * 0.4f;                 //  handle object offset

        positions[8 + i] = glm::vec3(offset, 0.0f, 0.4f);
        highlight[8 + i] = 0;                           //  nothing is highlighted by default

        if (i & 1)                                      //  set value of the color flag
            isWhite[8 + i] = true;
        else
            isWhite[8 + i] = false;
    }

    for (int i = 0; i < 8; i++)                         //  initialize third row of game board blocks
    {
        float offset = float(i) * 0.4f;                 //  handle object offset

        positions[16 + i] = glm::vec3(offset, 0.0f, 0.8f);
        highlight[16 + i] = 0;                          //  nothing is highlighted by default

        if (i & 1)                                      //  set value of the color flag
            isWhite[16 + i] = false;
        else
            isWhite[16 + i] = true;
    }

    for (int i = 0; i < 8; i++)                         //  initialize fourth row of game board blocks
    {
        float offset = float(i) * 0.4f;                 //  handle object offset

        positions[24 + i] = glm::vec3(offset, 0.0f, 1.2f);
        highlight[24 + i] = 0;                          //  nothing is highlighted by default

        if (i & 1)                                      //  set value of the color flag
            isWhite[24 + i] = true;
        else
            isWhite[24 + i] = false;
    }

    for (int i = 0; i < 8; i++)                         //  initialize fifth row of game board blocks
    {
        float offset = float(i) * 0.4f;                 //  handle object offset

        positions[32 + i] = glm::vec3(offset, 0.0f, 1.6f);
        highlight[32 + i] = 0;                          //  nothing is highlighted by default

        if (i & 1)                                      //  set value of the color flag
            isWhite[32 + i] = false;
        else
            isWhite[32 + i] = true;
    }

    for (int i = 0; i < 8; i++)                         //  initialize sixth row of game board blocks
    {
        float offset = float(i) * 0.4f;                 //  handle object offset

        positions[40 + i] = glm::vec3(offset, 0.0f, 2.0f);
        highlight[40 + i] = 0;                          //  nothing is highlighted by default

        if (i & 1)                                      //  set value of the color flag
            isWhite[40 + i] = true;
        else
            isWhite[40 + i] = false;
    }

    for (int i = 0; i < 8; i++)                         //  initialize seventh row of game board blocks
    {
        float offset = float(i) * 0.4f;                 //  handle object offset

        positions[48 + i] = glm::vec3(offset, 0.0f, 2.4f);
        highlight[48 + i] = 0;                          //  nothing is highlighted by default

        if (i & 1)                                      //  set value of the color flag
            isWhite[48 + i] = false;
        else
            isWhite[48 + i] = true;
    }

    for (int i = 0; i < 8; i++)                         //  initialize eighth row of game board blocks
    {
        float offset = float(i) * 0.4f;                 //  handle object offset

        positions[56 + i] = glm::vec3(offset, 0.0f, 2.8f);
        highlight[56 + i] = 0;                          //  nothing is highlighted by default

        if (i & 1)                                      //  set value of the color flag
            isWhite[56 + i] = true;
        else
            isWhite[56 + i] = false;
    }

    for (int i = 0; i < 8; i++)                         //  initialize black pawns
    {
        float offset = float(i) * 0.4f;                 //  handle object offset

        positions[64 + i] = glm::vec3(offset, 0.23f, 0.4f);
        highlight[64 + i] = 0;                          //  nothing is highlighted by default
        isWhite[64 + i] = false;                        //  set value of the color flag
    }

    for (int i = 0; i < 8; i++)                         //  initialize white pawns
    {
        float offset = float(i) * 0.4f;                 //  handle object offset

        positions[72 + i] = glm::vec3(offset, 0.23f, 2.4f);
        highlight[72 + i] = 0;                          //  nothing is highlighted by default
        isWhite[72 + i] = true;                         //  set value of the color flag
    }

    for (int i = 0; i < 8; i++)                         //  initialize black non-pawns
    {
        float offset = float(i) * 0.4f;                 //  handle object offset

        positions[80 + i] = glm::vec3(offset, 0.23f, 0.0f);
        highlight[80 + i] = 0;                          //  nothing is highlighted by default
        isWhite[80 + i] = false;                        //  set value of the color flag
    }

    for (int i = 0; i < 8; i++)                         //  initialize white non-pawns
    {
        float offset = float(i) * 0.4f;                 //  handle object offset

        positions[88 + i] = glm::vec3(offset, 0.23f, 2.8f);
        highlight[88 + i] = 0;                          //  nothing is highlighted by default
        isWhite[88 + i] = true;                         //  set value of the color flag
    }

    for (int i = 0; i < 9; i++)                         //  initialize game board border
    {
        float offset = float(i) * 0.4f;                 //  handle object offset

        positions[96 + i] = glm::vec3(offset, -0.03f, -0.4f);
    }

    for (int i = 0; i < 9; i++)                         //  initialize game board border
    {
        float offset = float(i) * 0.4f - 0.4f;          //  handle object offset

        positions[105 + i] = glm::vec3(offset, -0.03f, 3.2f);
    }

    for (int i = 0; i < 9; i++)                         //  initialize game board border
    {
        float offset = float(i) * 0.4f;                 //  handle object offset

        positions[114 + i] = glm::vec3(3.2f, -0.03f, offset);
    }

    for (int i = 0; i < 9; i++)                         //  initialize game board border
    {
        float offset = float(i) * 0.4f - 0.4f;          //  handle object offset

        positions[123 + i] = glm::vec3(-0.4f, -0.03f, offset);
    }

    for (int i = 0; i < 132; i++)                       //  move all game objects into the center of coordinate system
    {
        positions[i].x -= 1.4f;
        positions[i].z -= 1.4f;
    }

    while (!glfwWindowShouldClose(window))              //  handle infinite render loop
    {
                             

        glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, 1.0f);    //  update background color of window
        glClearStencil(0);                              //  clear stencil buffer and set default index value
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);     //  clear all required buffers

                            

        

        glViewport(0, 0, window_width, window_height);  //  reset viewport
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);     //  clear selected buffers
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);      //  setup stencil buffer

        shaderPBR->activate();
        glm::mat4 view = glm::mat4(1.0f);
        view = cameraPtr->loadViewMatrix();             //  camera view matrix needs to be loaded
        shaderPBR->passMatrix("view", view);
        shaderPBR->passVector("camPos", cameraPtr->Position);

        for (int i = 0; i < 64; i++)                    //  render all game board blocks
        {
            glm::mat4 model = glm::mat4(1.0f);          //  create new model matrix
            model = glm::translate(model, positions[i]);
            model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

            if (highlight[i] == 1)                      //  move highlight
            {
                glActiveTexture(GL_TEXTURE0);           //  bind new set of textures
                glBindTexture(GL_TEXTURE_2D, albedoBlue);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, normalHighlight);
                glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_2D, metallicHighlight);
                glActiveTexture(GL_TEXTURE3);
                glBindTexture(GL_TEXTURE_2D, roughnessHighlight);
                glActiveTexture(GL_TEXTURE4);
                glBindTexture(GL_TEXTURE_2D, aoHighlight);
            }
            else if (highlight[i] == 2)                 //  attack highlight
            {
                glActiveTexture(GL_TEXTURE0);           //  bind new set of textures
                glBindTexture(GL_TEXTURE_2D, albedoRed);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, normalHighlight);
                glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_2D, metallicHighlight);
                glActiveTexture(GL_TEXTURE3);
                glBindTexture(GL_TEXTURE_2D, roughnessHighlight);
                glActiveTexture(GL_TEXTURE4);
                glBindTexture(GL_TEXTURE_2D, aoHighlight);
            }
            else if (highlight[i] == 3)                 //  castling highlight
            {
                glActiveTexture(GL_TEXTURE0);           //  bind new set of textures
                glBindTexture(GL_TEXTURE_2D, albedoYellow);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, normalHighlight);
                glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_2D, metallicHighlight);
                glActiveTexture(GL_TEXTURE3);
                glBindTexture(GL_TEXTURE_2D, roughnessHighlight);
                glActiveTexture(GL_TEXTURE4);
                glBindTexture(GL_TEXTURE_2D, aoHighlight);
            }
            else
            {
                if (isWhite[i] == true)                 //  current block has got white color
                {
                    glActiveTexture(GL_TEXTURE0);       //  bind new set of textures
                    glBindTexture(GL_TEXTURE_2D, albedoWhiteBlock);
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, normalWhiteBlock);
                    glActiveTexture(GL_TEXTURE2);
                    glBindTexture(GL_TEXTURE_2D, metallicWhiteBlock);
                    glActiveTexture(GL_TEXTURE3);
                    glBindTexture(GL_TEXTURE_2D, roughnessWhiteBlock);
                    glActiveTexture(GL_TEXTURE4);
                    glBindTexture(GL_TEXTURE_2D, aoWhiteBlock);
                }
                else                                    //  current block has got black color
                {
                    glActiveTexture(GL_TEXTURE0);       //  bind new set of textures
                    glBindTexture(GL_TEXTURE_2D, albedoBlackBlock);
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, normalBlackBlock);
                    glActiveTexture(GL_TEXTURE2);
                    glBindTexture(GL_TEXTURE_2D, metallicBlackBlock);
                    glActiveTexture(GL_TEXTURE3);
                    glBindTexture(GL_TEXTURE_2D, roughnessBlackBlock);
                    glActiveTexture(GL_TEXTURE4);
                    glBindTexture(GL_TEXTURE_2D, aoBlackBlock);
                }
            }

            shaderPBR->passMatrix("model", model);
            glStencilFunc(GL_ALWAYS, i + 1, -1);        //  write object into the stencil buffer
            cubePtr->render();                          //  render selected object
        }

        glActiveTexture(GL_TEXTURE0);                   //  bind new set of textures
        glBindTexture(GL_TEXTURE_2D, albedoWhiteBlock);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normalWhiteBlock);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, metallicWhiteBlock);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, roughnessWhiteBlock);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, aoWhiteBlock);

        for (int i = 64; i < 96; i++)                   //  render all figurines
        {
            glm::mat4 model = glm::mat4(1.0f);          //  create new model matrix
            model = glm::translate(model, positions[i]);    //  translate and scale object before rendering
            model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));

            if (highlight[i])
            {
                glActiveTexture(GL_TEXTURE0);           //  bind new set of textures
                glBindTexture(GL_TEXTURE_2D, albedoGreen);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, normalHighlight);
                glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_2D, metallicHighlight);
                glActiveTexture(GL_TEXTURE3);
                glBindTexture(GL_TEXTURE_2D, roughnessHighlight);
                glActiveTexture(GL_TEXTURE4);
                glBindTexture(GL_TEXTURE_2D, aoHighlight);
            }
            else
            {
                if (isWhite[i] == true)
                {
                    glActiveTexture(GL_TEXTURE0);       //  bind new set of textures
                    glBindTexture(GL_TEXTURE_2D, albedoWhiteFigurine);
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, normalWhiteFigurine);
                    glActiveTexture(GL_TEXTURE2);
                    glBindTexture(GL_TEXTURE_2D, metallicWhiteFigurine);
                    glActiveTexture(GL_TEXTURE3);
                    glBindTexture(GL_TEXTURE_2D, roughnessWhiteFigurine);
                    glActiveTexture(GL_TEXTURE4);
                    glBindTexture(GL_TEXTURE_2D, aoWhiteFigurine);
                }
                else
                {
                    glActiveTexture(GL_TEXTURE0);       //  bind new set of textures
                    glBindTexture(GL_TEXTURE_2D, albedoBlackFigurine);
                    glActiveTexture(GL_TEXTURE1);
                    glBindTexture(GL_TEXTURE_2D, normalBlackFigurine);
                    glActiveTexture(GL_TEXTURE2);
                    glBindTexture(GL_TEXTURE_2D, metallicBlackFigurine);
                    glActiveTexture(GL_TEXTURE3);
                    glBindTexture(GL_TEXTURE_2D, roughnessBlackFigurine);
                    glActiveTexture(GL_TEXTURE4);
                    glBindTexture(GL_TEXTURE_2D, aoBlackFigurine);
                }
            }

            shaderPBR->passMatrix("model", model);
            glStencilFunc(GL_ALWAYS, i + 1, -1);        //  write object into the stencil buffer

            string linear = chessPtr->getLinear();
                                                        //  check type of figure using value inside linear array
            if (linear[i - 64] == 'p' || linear[i - 64] == 'P')
                pawnPtr->render();                      //  render selected object
            else if (linear[i - 64] == 'r' || linear[i - 64] == 'R')
                rookPtr->render();                      //  render selected object
            else if (linear[i - 64] == 'n')
            {
                model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                shaderPBR->passMatrix("model", model);
                knightPtr->render();                    //  render selected object
            }
            else if (linear[i - 64] == 'N')
                knightPtr->render();                    //  render selected object
            else if (linear[i - 64] == 'b' || linear[i - 64] == 'B')
                bishopPtr->render();                    //  render selected object
            else if (linear[i - 64] == 'q' || linear[i - 64] == 'Q')
                queenPtr->render();                     //  render selected object
            else if (linear[i - 64] == 'k' || linear[i - 64] == 'K')
                kingPtr->render();                      //  render selected object
        }

        glActiveTexture(GL_TEXTURE0);                   //  bind new set of textures
        glBindTexture(GL_TEXTURE_2D, albedoBlack);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, normalHighlight);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, metallicHighlight);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, roughnessHighlight);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, aoHighlight);

        for (int i = 96; i < 132; i++)                  //  render game board border cubes
        {
            glm::mat4 model = glm::mat4(1.0f);          //  create new model matrix
            model = glm::translate(model, positions[i]);
            model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
            shaderPBR->passMatrix("model", model);
            glStencilFunc(GL_ALWAYS, i + 1, -1);        //  write object into the stencil buffer
            cubePtr->render();                          //  render selected object
        }

        shaderPBR->passVector("lightPositions[0]", lightPositionOne);   //  pass all light source positions into the PBR shader
        shaderPBR->passVector("lightColors[0]", lightColorOne);     //  pass all light source colors into the PBR shader
        shaderPBR->passVector("lightPositions[1]", lightPositionTwo);
        shaderPBR->passVector("lightColors[1]", lightColorTwo);
        shaderPBR->passVector("lightPositions[2]", lightPositionThree);
        shaderPBR->passVector("lightColors[2]", lightColorThree);
        shaderPBR->passVector("lightPositions[3]", lightPositionFour);
        shaderPBR->passVector("lightColors[3]", lightColorFour);

        if (lampVisible)                                //  check if light sources are visible
        {
            glActiveTexture(GL_TEXTURE0);               //  bind new set of textures
            glBindTexture(GL_TEXTURE_2D, albedoWhite);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, normalHighlight);
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, metallicHighlight);
            glActiveTexture(GL_TEXTURE3);
            glBindTexture(GL_TEXTURE_2D, roughnessHighlight);
            glActiveTexture(GL_TEXTURE4);
            glBindTexture(GL_TEXTURE_2D, aoHighlight);

            glm::vec3 finalPositionOne = lightPositionOne;
            glm::vec3 finalPositionTwo = lightPositionTwo;
            glm::vec3 finalPositionThree = lightPositionThree;
            glm::vec3 finalPositionFour = lightPositionFour;
            
            finalPositionOne.y += 0.2;                  //  modify position to make light source bright and visible
            finalPositionTwo.y += 0.2;
            finalPositionThree.y += 0.2;
            finalPositionFour.y += 0.2;

            {
                glm::mat4 model = glm::mat4(1.0f);      //  create new model matrix
                model = glm::translate(model, finalPositionOne);
                model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
                shaderPBR->passMatrix("model", model);
                glStencilFunc(GL_ALWAYS, 97, -1);       //  write object into the stencil buffer
                cubePtr->render();                      //  render first light source
            }

            {
                glm::mat4 model = glm::mat4(1.0f);      //  create new model matrix
                model = glm::translate(model, finalPositionTwo);
                model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
                shaderPBR->passMatrix("model", model);
                glStencilFunc(GL_ALWAYS, 98, -1);       //  write object into the stencil buffer
                cubePtr->render();                      //  render second light source
            }

            {
                glm::mat4 model = glm::mat4(1.0f);      //  create new model matrix
                model = glm::translate(model, finalPositionThree);
                model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
                shaderPBR->passMatrix("model", model);
                glStencilFunc(GL_ALWAYS, 99, -1);       //  write object into the stencil buffer
                cubePtr->render();                      //  render third light source
            }

            {
                glm::mat4 model = glm::mat4(1.0f);      //  create new model matrix
                model = glm::translate(model, finalPositionFour);
                model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
                shaderPBR->passMatrix("model", model);
                glStencilFunc(GL_ALWAYS, 100, -1);      //  write object into the stencil buffer
                cubePtr->render();                      //  render fourth light source
            }
        }

        glfwSwapBuffers(window);                        //  swap buffers and poll IO events
        glfwPollEvents();
    }

    glfwTerminate();                                    //  terminate GLFW runtime
    return 0;
}
    


glm::vec3 rgbToFloats(int red, int green, int blue)     //  convert integer RGB value to appropriate float RGB value
{
    float newRed = float(red) / 255.0;
    float newGreen = float(green) / 255.0;
    float newBlue = float(blue) / 255.0;

    return glm::vec3(newRed, newGreen, newBlue);        //  return value as a vector
}

unsigned int loadTexture(char const * path)             //  load texture and return texture ID value
{
    unsigned int textureID;
    glGenTextures(1, &textureID);                       //  generate new texture ID value

    int width, height, nrComponents;
    unsigned char * data = stbi_load(path, &width, &height, &nrComponents, 0);  //  use appropriate function to load texture date

    if (data)                                           //  check if something has been loaded
    {
        GLenum format;

        if (nrComponents == 1)                          //  detect color format of the texture
            format = GL_RED;                            //  set appropriate texture color format
        else if (nrComponents == 3)
            format = GL_RGB;                            //  set appropriate texture color format
        else if (nrComponents == 4)
            format = GL_RGBA;                           //  set appropriate texture color format

        glBindTexture(GL_TEXTURE_2D, textureID);        //  bind loaded texture with generated texture ID value
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);                //  generate appropriate mipmap texture

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   //  setup texture wrapping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);     //  setup texture filtering
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);                          //  delete previously allocated memory
    }
    else                                                //  no data has been loaded
    {
        cerr << "Texture failed to load at path: " << path << endl;
        stbi_image_free(data);                          //  delete previously allocated memory
    }

    return textureID;                                   //  return generated texture ID value
}

    
