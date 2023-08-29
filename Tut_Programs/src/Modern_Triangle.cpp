#include <GLFW/glfw3.h>
#include <iostream>
static unsigned int CompileShader(unsigned int type,const std::string& source)
{
    unsigned int id= glCreateShader(type);
    const char* src= source.c_str(); //can also be written as &source[0]
    glShaderSource(id ,1 ,&src ,nullptr); //specifies the source of our shader
    glCompileShader(id);

    //Code for error handling:
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);//i specifies integer and v specifes that it wasnts a vector
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length*sizeof(char));//alloca is function that dynamically allocates stack memory
        glGetShaderInfoLog(id, length, &length, message);
        std::cout<<"Failed to compile " << 
        (type== GL_VERTEX_SHADER ? "vertex ": "fragment") <<"shader!"<<std::endl;
        std::cout<<message<<std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program= glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);//To delete the intermediates as they have already been linked to the program
    
    return program;
}
int main(void)
{
    GLFWwindow *window;

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
    glBindBuffer(GL_ARRAY_BUFFER, buffer);                                       // THis function is used to select(bind) a buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); // This function is used to provide data to the buffer

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,0);

    std::string vertexShader = 
        "#version 330 core\n" //Used to define the version of the shader
        "\n"
        "layout(location = 0)in vec4 position;\n" //index of attribute
        "\n"
        "void main()\n"
        "{\n"
        "gl_Position=position;\n"
        "}\n";

    std::string fragmentShader = 
        "#version 330 core\n" //Used to define the version of the shader
        "\n"
        "layout(location = 0)out vec4 color;\n" //index of attribute
        "\n"
        "void main()\n"
        "{\n"
        "color=vec4(1.0,0.0,0.0,1.0);\n"//0 is black and 1 is white (RGBA)
        "}\n";
         
    unsigned int shader = CreateShader(vertexShader,fragmentShader);
    glBindBuffer(GL_ARRAY_BUFFER,0);
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

    glfwTerminate();
    return 0;
}