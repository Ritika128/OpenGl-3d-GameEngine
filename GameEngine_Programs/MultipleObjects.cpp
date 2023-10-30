
#include <GLFW/glfw3.h>

// Vertex data for the red and blue rectangles
GLfloat vertices[] = {
    // Red Rectangle
    0.0f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.5f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f,

    // Blue Rectangle
    -0.5f, -0.5f, 0.0f,
    0.0f, -0.5f, 0.0f,
    0.0f, 0.0f, 0.0f,
    -0.5f, 0.0f, 0.0f,
};

// Color data for the red and blue rectangles
GLfloat colors[] = {
    // Red Rectangle
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,

    // Blue Rectangle
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
};

// Vertex shader source code
const char* vertexShaderSource = R"(
    #version 330 core
    in vec3 position;
    in vec3 color;
    out vec3 fragColor;
    void main() {
        gl_Position = vec4(position, 1.0);
        fragColor = color;
    }
)";

// Fragment shader source code
const char* fragmentShaderSource = R"(
    #version 330 core
    in vec3 fragColor;
    out vec4 color;
    void main() {
        color = vec4(fragColor, 1.0);
    }
)";

int main() {
    if (!glfwInit()) {
        return -1;
    }

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Rectangles", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    

    GLuint vertexArray, vertexBuffer, colorBuffer, shaderProgram;
    glGenVertexArrays(1, &vertexArray);
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &colorBuffer);

    glBindVertexArray(vertexArray);

    // Vertex Buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // Color Buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    // Compile and link shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(vertexArray);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4); // Red Rectangle
        glDrawArrays(GL_TRIANGLE_FAN, 4, 4); // Blue Rectangle
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &colorBuffer);
    glDeleteVertexArrays(1, &vertexArray);

    glfwTerminate();

    return 0;
}
