#include <stdio.h>
#include <stdlib.h>


#include <GLFW/glfw3.h>

int main()
{
    printf("Hello, YouTube!\n");

    if(!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    GLFWwindow *window = glfwCreateWindow(420, 420, "dnqr.", NULL, NULL);
    if(!window) {
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    
    glViewport(0, 0, 420, 420);

    // shaders
    const char* vShaderCode =
    "#version 410 core\n"
    "layout (location = 0) in vec2 vertex_position;\n"
    "void main() {\n"
    "    gl_Position = vec4(vertex_position, 0.0, 1.0);\n"
    "}\0";
    const char* fShaderCode =
    "#version 410 core\n"
    "out vec4 frag_color;\n"
    "void main(){\n"
    "    frag_color = vec4(0.1412, 0.1608, 0.1843, 1.0);\n"
    "}\0";

    unsigned int vShader, fShader;
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShaderCode, NULL);
    glCompileShader(vShader);
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fShaderCode, NULL);
    glCompileShader(fShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
    glLinkProgram(shaderProgram);

    // vertices & indices
    float vertices[] = {
        -0.5, -0.5,
        -0.5, 0.5,
        0.5, 0.5,
        0.5, -0.5
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(0);


    // loop
    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.9451, 0.9451, 0.9451, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}