//jumping animation to a triangle
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

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

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(640, 480, "Jumping Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    float positions[6] = {
        -0.1f, -0.1f,
         0.0f,  0.1f,
         0.1f, -0.1f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    ShaderProgramsSource source = ParseShader("/Users/ritikanankar/Render/res/shaders/jump.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    glUseProgram(shader);

    float xaxis = 0.0f; //initialise x axis 
    float yaxis = 0.0f;//initialise y axis
    float xmove = 0.002f; //horizontal speed
    float ymove = 0.006f; //vertical jumping speed
    bool jumping = false; //trisngle is not jumping initially 

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        xaxis = xaxis + xmove;
		//gives linear motion left to right
        if (xaxis > 1.0f) //when triangle is moved at extreme right side 
            xaxis = -1.0f; // bring it back to extreme left side 

		// gives jumping animation 
		// if the triangle is not jumping 
        if (!jumping) {
            yaxis = yaxis + ymove; //moves triangle up
            if (yaxis >= 0.3f) // triangle moves upward at a height given i.e 0.3
                jumping = true;
        } else {
            yaxis = yaxis - ymove; //else the triangle moves downwards 
            if (yaxis <= 0.0f) // triangle returns to ground , set jumping as false
                jumping = false;
        }

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(xaxis, yaxis, 0.0f));

        unsigned int transformLoc = glGetUniformLocation(shader, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}