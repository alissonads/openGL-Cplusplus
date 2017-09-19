#ifndef	__WINDOW_H__
#define __WINDOW_H__

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <RTmath.h>

class RT_Keyboard;
class Scene;

class Window
{
private:
	GLFWwindow *window;
	Scene *scene;
	char *title;
	int width;
	int height;

	static void GetErrorCallback(int error, const char *description);

public:
	Window(Scene *_scene,
		   char *_title = "--- teste ---", 
		   const int _width = 800, 
		   const int height = 600);
	~Window();

	int GetWidth() const;
	int GetHeight() const;

	void init();
	void loop();
	void show();

	static void key_callback(GLFWwindow *_window, const int key, const int scancode, const int action, const int mode);
};

#endif //__WINDOW_H__
