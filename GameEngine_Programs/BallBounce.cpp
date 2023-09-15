#include "glfw_app.hpp"
#include "ball.hpp
#include <iostream>
#include <GLFW/glfw3.h>

class glfw_app 
{
public:
    glfw_app(const std::string& window_title, int window_width, int window_height);
    virtual ~glfw_app();
    
    void start();

    virtual void on_keydown(GLFWwindow* window, int key, int scancode, int action, int mods);
    virtual void on_error(int error, const char* desc);
    virtual void on_resize(GLFWwindow* window, int width, int height);
    virtual void glloop() = 0;
    
    GLFWwindow* window() const;
};
void triangle::on_keydown(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void triangle::glloop()
{
	float ratio = glfw_app::framebuffer_width() / (float)glfw_app::framebuffer_height();

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

	glBegin(GL_TRIANGLES);
	glColor3f(1.f, 0.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();
}
glfw_app::glfw_app(const std::string& window_title , int window_width , int window_height)
{
    if( !glfwInit() )
        throw std::runtime_error
    {
        "Unable to initialize glfw runtime"
    };

    _window = glfwCreateWindow(window_width , window_height , window_title.c_str() , nullptr , nullptr);

    if( !_window )
        throw std::runtime_error
    {
        "Unable to initialize glfw window"
    };

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);
}

glfw_app::~glfw_app()
{
    glfwDestroyWindow(_window);
    glfwTerminate();
}
void glfw_app::start()
{
    glfwloop();
}

void glfw_app::glfwloop()
{
    while( !glfwWindowShouldClose(_window) )
    {
	    //Here we call our custom loop body
        this->glloop(); 

        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
}
void glfw_app::on_resize(GLFWwindow* window , int width , int height)
{
    //By defualt rearranges OpenGL viewport to the current framebuffer size.

    glViewport(0 , 0 , width , height);
}
class glfw_app_manager
{
    static glfw_app* _app;
    
    static void on_keydown(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if(_app) _app->on_keydown(window,key,scancode,action,mods);
    }
    
    static void on_error(int error, const char* desc)
    {
        if(_app) _app->on_error(error,desc);
    }
    
    static void on_resize(GLFWwindow* window, int width, int height)
    {
        if(_app) _app->on_resize(window,width,height);
    }
    
public:
    static void start_app(glfw_app* app)
    {
        _app = app;
        
        glfwSetKeyCallback(app->window() , on_keydown);
        glfwSetFramebufferSizeCallback(app->window() , on_resize);
        glfwSetErrorCallback(on_error);
    }
};
template<typename T , typename... ARGS , typename = typename std::enable_if<std::is_base_of<glfw_app,T>::value>::type>
std::unique_ptr<T> make_app(ARGS&&... args)
{
    std::unique_ptr<T> app{ new T{ std::forward<ARGS>(args)...} };
    
    glfw_app_manager::start_app(app.get());
    
    return app;
}
class ball : public glfw_app
{
public:
	template<typename... ARGS>
	ball(ARGS&&... args) : glfw_app{ std::forward<ARGS>(args)... } , 
		x_ball{ 0.0f },
		y_ball{ 0.8f },
		vx_ball{ 0.0f },
		vy_ball{ 0.0f }
	{}

	virtual void on_keydown(GLFWwindow* window, int key, int scancode, int action, int mods) override;

	virtual void glloop() override;

private:
	float x_ball, y_ball;
	float vx_ball, vy_ball;
	const float gravity = 0.01;
	const float radius = 0.05f;

	void draw_ball();
};
void ball::on_keydown(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
void ball::glloop()
{
	float ratio = framebuffer_width() / (float)framebuffer_height();

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);

	//Bounce on window bottom
	if (y_ball + radious <= radious)
		vy_ball = std::abs(vy_ball);
	else
		vy_ball -= gravity; //Apply gravity

	//Update ball coordinates
	x_ball += vx_ball;
	y_ball += vy_ball;

	//Lets draw the ball!
	draw_ball();
}
void ball::draw_ball()
{
	const float full_angle = 2.0f*3.141592654f;
	float x, y;

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);

	for (std::size_t i = 0; i < 20; ++i)
	{
		x = x_ball + radious*(std::cos(i*full_angle / 20.0f));
		y = y_ball + radious*(std::sin(i*full_angle / 20.0f));

		glVertex2f(x, y);
	}

	glEnd();
}

int main()
{
    auto app = make_app<ball>("bouncing ball!" , 800 , 600);
    
    app->start();
}