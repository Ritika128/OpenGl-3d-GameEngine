
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
 //multiple return type
 struct ShaderProgramsSource
 {
    std::string VertexSource;
    std::string FragmentSource;
 };

static ShaderProgramsSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);
    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos )
        {
            if(line.find("vertex")!= std::string::npos)
                type = ShaderType::VERTEX;
            //set node to vertex
            else if(line.find("fragment")!= std::string::npos)
                type = ShaderType::FRAGMENT;
            //set node to fragment 
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    return
    {
        ss[0].str(), ss[1].str() 
    };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //error handling code, iv integer the specifies it wants a vector
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS,&result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
        char* message = (char*)alloca(length* sizeof(char));
        glGetShaderInfoLog(id,length,&length,message);
        std::cout<< "Failed to compile " << 
        (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
        << std::endl;
        std::cout<< message<< std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

//creating shader
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    //to link vs and fs together
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    //to delete when we get the results
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    float positions[6] = {
        -0.5f, -0.5f,
         0.0f, 0.5f,
         0.5f, -0.5f
         };

    unsigned int buffer;
    glGenBuffers(1, &buffer);                                                    // This function is generating a buffer and giving us back an id
    glBindBuffer(GL_ARRAY_BUFFER, buffer);                                       // This function is used to select(bind) a buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); // This function is used to provide data to the buffer

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT,GL_FALSE, sizeof(float) * 2,0);

    ShaderProgramsSource source = ParseShader("res/shaders/Linear.shader");
    std::cout << "VERTEX" << endl;
    std::cout << source.VertexSource << endl;
    std::cout << "FRAGMENT" << endl;
    std::cout << source.FragmentSource << endl;
    unsigned int shader = CreateShader(source.VertexSource,source.FragmentSource);
    glUseProgram(shader);
    float x_axis = 0.0f;
    float move= 0.01f; //speed of movement
   

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //set the clear color to black
        glClear(GL_COLOR_BUFFER_BIT);


        glDrawArrays(GL_TRIANGLES,0,3);
        x_axis=x_axis+move;
        if (x_axis>1.5f)
        {
            x_axis=-1.5f;
        }
        

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans,glm::vec3(x_axis, 0.0f, 0.0f));
        //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f)); 
        
        
        unsigned int transformLoc = glGetUniformLocation(shader, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));



        



        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}