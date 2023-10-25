
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec2 aPos;
    void main() {
        gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    uniform vec3 color;
    void main() {
        FragColor = vec4(color, 1.0);
    }
)";

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a GLFW window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Rectangle and Circle", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    

    // Create vertex and fragment shaders
    GLuint vertexShader, fragmentShader, shaderProgram;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Define rectangle and circle vertices and attributes
    float rectangleVertices[] = {
        -0.5f, -0.5f,   // bottom-left
        0.5f, -0.5f,    // bottom-right
        0.5f, 0.5f,     // top-right
        -0.5f, 0.5f     // top-left
    };

    float circleVertices[360 * 2];
    float radius = 0.3f;
    for (int i = 0; i < 360; i++) {
        float angle = glm::radians(float(i));
        circleVertices[i * 2] = radius * cos(angle);
        circleVertices[i * 2 + 1] = radius * sin(angle);
    }

    GLuint VAO[2], VBO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    // Rectangle setup
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), rectangleVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Circle setup
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circleVertices), circleVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Render the rectangle
        glBindVertexArray(VAO[0]);
        glUniform3f(glGetUniformLocation(shaderProgram, "color"), 1.0f, 0.0f, 0.0f);
        glDrawArrays(GL_QUADS, 0, 4);

        // Render the circle
        glBindVertexArray(VAO[1]);
        glUniform3f(glGetUniformLocation(shaderProgram, "color"), 0.0f, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 360);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();

    return 0;
}
