//render 2 static shapes (triangle and rectangle) in one window
#include <GLFW/glfw3.h>
#include <iostream>
#include<fstream>
#include<string>
#include<sstream>
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
    window = glfwCreateWindow(740, 580, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    float trianglePositions[] = {
        -0.5f, -0.5f,
         0.0f, 0.5f,
         0.5f, -0.5f
    };

    float rectPositions[] = {
         -0.7f, -0.7f,  //0
		 -0.7f, 0.7f,  //1
		 0.7f,  0.7f,  //2
		 0.7f,  -0.7f  //3
         };

    //bind VBO for triangle and rectangle
    unsigned int triangleBuffer, rectBuffer;
    glGenBuffers(1, &triangleBuffer); // This function is generating a buffer and giving us back an id
    glBindBuffer(GL_ARRAY_BUFFER, triangleBuffer); // This function is used to select(bind) a buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), trianglePositions, GL_STATIC_DRAW); // This function is used to provide data to the buffer

    glGenBuffers(1, &rectBuffer); // This function is generating a buffer and giving us back an id
    glBindBuffer(GL_ARRAY_BUFFER, rectBuffer); // This function is used to select(bind) a buffer
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), rectPositions, GL_STATIC_DRAW); // This function is used to provide data to the buffer

    //enable and configure vertex attribute for triangle
    glEnableVertexAttribArray(0);
    //triangle at location 0
    glBindBuffer(GL_ARRAY_BUFFER, triangleBuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT,GL_FALSE, 2 * sizeof(float),0);

    //enable and configure vertex attribute for rect
    glEnableVertexAttribArray(1);
    // rectanfle at location 1 (different from triangle)
    glBindBuffer(GL_ARRAY_BUFFER, rectBuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT,GL_FALSE, 2 * sizeof(float),0);

    ShaderProgramsSource source = ParseShader("/Users/ritikanankar/Render/res/shaders/two.shader");
    unsigned int shader = CreateShader(source.VertexSource,source.FragmentSource);
    glUseProgram(shader);
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        //Render here
        //glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //set the clear color to black
        glClear(GL_COLOR_BUFFER_BIT);
        
        glBindBuffer(GL_ARRAY_BUFFER, triangleBuffer);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        glDrawArrays(GL_TRIANGLES,0,3);

        glBindBuffer(GL_ARRAY_BUFFER, rectBuffer);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        glDrawArrays(GL_QUADS,0,4);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
