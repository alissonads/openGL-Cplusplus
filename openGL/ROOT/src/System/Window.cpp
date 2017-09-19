#include "Window.h"
#include <exception>
#include <sstream>
#include <iostream>

#include "RT_Keyboard.h"
#include "..\Abstract\Scene.h"

Window::Window(Scene *_scene,
			   char *_title,
			   const int _width, 
	           const int _height  ) : 
	scene(_scene), title(_title),
	width(_width), height(_height)
{}

Window::~Window()
{
	if (scene)
	{
		delete scene;
		scene = nullptr;
	}

	glfwDestroyWindow(window);
	window = nullptr;
	glfwTerminate();
}

int Window::GetWidth() const
{
	return width;
}

int Window::GetHeight() const
{
	return height;
}

void Window::init()
{
	if (!glfwInit())
	{
		throw std::exception("Unable to initialize GLFW\n");
	}

	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSetErrorCallback(GetErrorCallback);

	window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (!window)
	{
		throw std::exception("Failed to create the GLFW window\n");
	}

	GLFWvidmode *vidmode = nullptr;
	vidmode = const_cast<GLFWvidmode*>(glfwGetVideoMode(glfwGetPrimaryMonitor()));
	
	glfwSetWindowPos(window, (vidmode->width - width) / 2, 
							 (vidmode->height - height) / 2);

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	glfwShowWindow(window);

	//opengl
	glewExperimental = GL_TRUE;

	GLenum glewInitError = glewInit();
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	if (glewInitError != GLEW_OK)
	{
		std::stringstream error;

		error << "Erro ao Iniciar a janela. Erro: "
		      << glewGetErrorString(glewInitError) << "\n";
		throw std::out_of_range(error.str());
	}

	glViewport(0, 0, width, height);
}

void Window::loop()
{
	scene->Init();
	double before = glfwGetTime() - 1;

	while (!glfwWindowShouldClose(window) &&
		   !RT_Keyboard::GetInstance()->
				IsPressed(GLFW_KEY_ESCAPE)   )
	{
		float time = (glfwGetTime() - before) / 60;
		before = glfwGetTime() - 1;
		
		scene->Update(time);
		scene->Draw();

		RT_Keyboard::GetInstance()->Update();
		glfwPollEvents();
		glfwSetKeyCallback(window, key_callback);
		glfwSwapBuffers(window);
	}

	scene->Deinit();
}

void Window::show()
{
	try
	{
		init();
		loop();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Window::GetErrorCallback(int error, const char * description)
{
	std::cout << "ERROR " << error << ": " 
			  << description << std::endl;
}

void Window::key_callback(GLFWwindow *_window, const int key, 
						  const int scancode, const int action, 
						  const int mode                       )
{
	RT_Keyboard::GetInstance()->Set(key, action);

	/*for (int i = 0; i < KEY_MAX; i++)
		button[i].pressed = false;

	if (p_action == GLFW_PRESS || p_action == GLFW_RELEASE)
	{
		if (p_key == GLFW_KEY_ESCAPE)
		{
			PressedButton(&button[KEY_ESC]);
		}
		else
		{
			switch (p_key)
			{
			case GLFW_KEY_Q:
				Process(&button[KEY_q], p_action);
				break;
			case GLFW_KEY_W:
				Process(&button[KEY_w], p_action);
				break;
			case GLFW_KEY_E:
				Process(&button[KEY_e], p_action);
				break;
			case GLFW_KEY_R:
				Process(&button[KEY_r], p_action);
				break;
			case GLFW_KEY_T:
				Process(&button[KEY_t], p_action);
				break;
			case GLFW_KEY_Y:
				Process(&button[KEY_y], p_action);
				break;
			case GLFW_KEY_U:
				Process(&button[KEY_u], p_action);
				break;
			case GLFW_KEY_I:
				Process(&button[KEY_i], p_action);
				break;
			case GLFW_KEY_O:
				Process(&button[KEY_o], p_action);
				break;
			case GLFW_KEY_P:
				Process(&button[KEY_p], p_action);
				break;
			case GLFW_KEY_A:
				Process(&button[KEY_a], p_action);
				break;
			case GLFW_KEY_S:
				Process(&button[KEY_s], p_action);
				break;
			case GLFW_KEY_D:
				Process(&button[KEY_d], p_action);
				break;
			case GLFW_KEY_F:
				Process(&button[KEY_f], p_action);
				break;
			case GLFW_KEY_G:
				Process(&button[KEY_g], p_action);
				break;
			case GLFW_KEY_H:
				Process(&button[KEY_h], p_action);
				break;
			case GLFW_KEY_J:
				Process(&button[KEY_j], p_action);
				break;
			case GLFW_KEY_K:
				Process(&button[KEY_k], p_action);
				break;
			case GLFW_KEY_L:
				Process(&button[KEY_l], p_action);
				break;
			case GLFW_KEY_Z:
				Process(&button[KEY_z], p_action);
				break;
			case GLFW_KEY_X:
				Process(&button[KEY_x], p_action);
				break;
			case GLFW_KEY_C:
				Process(&button[KEY_c], p_action);
				break;
			case GLFW_KEY_V:
				Process(&button[KEY_v], p_action);
				break;
			case GLFW_KEY_B:
				Process(&button[KEY_b], p_action);
				break;
			case GLFW_KEY_N:
				Process(&button[KEY_n], p_action);
				break;
			case GLFW_KEY_M:
				Process(&button[KEY_m], p_action);
				break;
			case GLFW_KEY_1:
				Process(&button[KEY_1], p_action);
				break;
			case GLFW_KEY_2:
				Process(&button[KEY_2], p_action);
				break;
			case GLFW_KEY_3:
				Process(&button[KEY_3], p_action);
				break;
			case GLFW_KEY_4:
				Process(&button[KEY_4], p_action);
				break;
			case GLFW_KEY_5:
				Process(&button[KEY_5], p_action);
				break;
			case GLFW_KEY_6:
				Process(&button[KEY_6], p_action);
				break;
			case GLFW_KEY_7:
				Process(&button[KEY_7], p_action);
				break;
			case GLFW_KEY_8:
				Process(&button[KEY_8], p_action);
				break;
			case GLFW_KEY_9:
				Process(&button[KEY_9], p_action);
				break;
			case GLFW_KEY_0:
				Process(&button[KEY_0], p_action);
				break;
			case GLFW_KEY_SPACE:
				Process(&button[KEY_SPACE], p_action);
				break;
			case GLFW_KEY_LEFT_SHIFT:
				Process(&button[KEY_SHIFT], p_action);
				break;
			case GLFW_KEY_LEFT_CONTROL:
				Process(&button[KEY_CTRL], p_action);
				break;
			case GLFW_KEY_LEFT_ALT:
				Process(&button[KEY_ALT], p_action);
				break;
			case GLFW_KEY_BACKSPACE:
				Process(&button[KEY_BACKSPACE], p_action);
				break;
			case GLFW_KEY_LEFT:
				Process(&button[KEY_LEFT], p_action);
				break;
			case GLFW_KEY_RIGHT:
				Process(&button[KEY_RIGHT], p_action);
				break;
			case GLFW_KEY_UP:
				Process(&button[KEY_UP], p_action);
				break;
			case GLFW_KEY_DOWN:
				Process(&button[KEY_DOWN], p_action);
				break;
			case GLFW_KEY_ENTER:
				Process(&button[KEY_ENTER], p_action);
				break;
			default:
				break;
			}
			if (p_key == GLFW_KEY_Q)
			{
				Process(&button[KEY_q], p_action);
			}
			if (p_key == GLFW_KEY_W)
			{
				Process(&button[KEY_w], p_action);
			}
			if (p_key == GLFW_KEY_E)
			{
				Process(&button[KEY_e], p_action);
			}
			if (p_key == GLFW_KEY_R)
			{
				Process(&button[KEY_r], p_action);
			}
			if (p_key == GLFW_KEY_T)
			{
				Process(&button[KEY_t], p_action);
			}
			if (p_key == GLFW_KEY_Y)
			{
				Process(&button[KEY_y], p_action);
			}
			if (p_key == GLFW_KEY_U)
			{
				Process(&button[KEY_u], p_action);
			}
			if (p_key == GLFW_KEY_I)
			{
				Process(&button[KEY_i], p_action);
			}
			if (p_key == GLFW_KEY_O)
			{
				Process(&button[KEY_o], p_action);
			}
			if (p_key == GLFW_KEY_P)
			{
				Process(&button[KEY_p], p_action);
			}
			if (p_key == GLFW_KEY_A)
			{
				Process(&button[KEY_a], p_action);
			}
			if (p_key == GLFW_KEY_S)
			{
				Process(&button[KEY_s], p_action);
			}
			if (p_key == GLFW_KEY_D)
			{
				Process(&button[KEY_d], p_action);
			}
			if (p_key == GLFW_KEY_W)
			{
				Process(&button[KEY_w], p_action);
			}
			if (p_key == GLFW_KEY_S)
			{
				Process(&button[KEY_s], p_action);
			}
			if (p_key == GLFW_KEY_UP)
			{
				Process(&button[KEY_UP], p_action);
			}
			if (p_key == GLFW_KEY_DOWN)
			{
				Process(&button[KEY_DOWN], p_action);
			}
		}
	}*/
}
