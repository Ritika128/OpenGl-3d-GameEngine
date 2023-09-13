//animated color swap rectangle
//index buffers and uniforms
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
		-0.5f, -0.5f,  //0
		 0.5f, -0.5f,  //1
		 0.5f,  0.5f,  //2
		-0.5f,  0.5f   //3
         };
    //index buffer
    unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
         };

    unsigned int buffer;
    glGenBuffers(1, &buffer);                                                    
    glBindBuffer(GL_ARRAY_BUFFER, buffer);                                       
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(unsigned int), positions, GL_STATIC_DRAW); 

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT,GL_FALSE, 0 ,0);

    //index buffer objecta
    unsigned int ibo;
    glGenBuffers(1, &ibo);                                                    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);                                       
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW); 


    ShaderProgramsSource source = ParseShader("/Users/ritikanankar/Render/res/shaders/Basic2.shader");
    unsigned int shader = CreateShader(source.VertexSource,source.FragmentSource);
    glUseProgram(shader);
    
    //uniform
    int location = glGetUniformLocation(shader, "u_color");
    //ASSERT(location != -1);
    glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f);

    float r = 0.0f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        //glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //set the clear color to black
        glClear(GL_COLOR_BUFFER_BIT);
       
        glUniform4f(location, r, 0.3f, 0.8f, 1.0f);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        //logic to animate it
        if(r>1.0f)
            increment = -0.05f;
        else if (r<0.0f)
            increment = 0.05f;

        r = r + increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
