#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;

};
static ShaderProgramSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE=-1, VERTEX=0, FRAGMENT=1
    };
    ShaderType type = ShaderType::NONE;
    std::string line;
    std::stringstream ss[2];
    while(getline(stream,line))
    {
        if(line.find("#shader")!= std::string::npos)
        {
            if(line.find("vertex")!=std::string::npos)
                type= ShaderType::VERTEX;
            else if(line.find("fragment")!= std::string::npos)
                type= ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type]<<line<<'\n';

        }
    }
    return {ss[0].str(),ss[1].str()};

}
static unsigned int CompileShader(unsigned int type,const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();//returns pointer to the address of source string
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);//specifies the source of our shader

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
static unsigned int CreateShader(const std::string& vertexShader,const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram(); //returns an unsigned integer
    unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader); //Creating a vertex shader
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);//Creating a fragment shader

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

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
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,0);

    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    unsigned int shader= CreateShader( source.VertexSource, source.FragmentSource); 
    glUseProgram(shader);
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES,0,3);

        


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}