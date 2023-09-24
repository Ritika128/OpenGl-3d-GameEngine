// rotating a cube with different color for each face

#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
 
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
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id,length, &length ,message);
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
    glfwSwapInterval(1);

    float positions [] = {
		    -0.5f, -0.5f, 0.5f,
         0.5f, -0.5f, 0.5f,
         0.5f,  0.5f, 0.5f,
        -0.5f,  0.5f, 0.5f,
        
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f
         };
    //index buffer
    unsigned int indices[] = {
		    0, 1, 2, // Front
        2, 3, 0,

        1, 2, 6, // Right
        6, 5, 1,

        4, 5, 6, // Back
        6, 7, 4,
        
        3, 2, 6, // Top
        6, 7, 3,

        0, 3, 7, // Left
        7, 4, 0,

        4, 5, 1, // Bottom
        1, 0, 4,
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);                                                    
    glBindBuffer(GL_ARRAY_BUFFER, buffer);                                       
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW); 

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 0 ,0);

    //index buffer objecta
    unsigned int ibo;
    glGenBuffers(1, &ibo);                                                    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);                                       
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

    ShaderProgramsSource source = ParseShader("res/shaders/animation.shader");
    unsigned int shader = CreateShader(source.VertexSource,source.FragmentSource);
    glUseProgram(shader);
       
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
       
        glDrawElements(GL_TRIANGLES, 6*6, GL_UNSIGNED_INT, nullptr);

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f)); 
              
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
