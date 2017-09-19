#ifndef	 __RT_KEYBOARD_H__
#define	 __RT_KEYBOARD_H__

#include <unordered_map>
#include <GLFW\glfw3.h>

class RT_Keyboard
{
private:
	std::unordered_map<int, bool> down;
	std::unordered_map<int, bool> pressed;
	std::unordered_map<int, bool> released;
	static RT_Keyboard *INSTANCE;

	RT_Keyboard();

public:
	~RT_Keyboard();
	static RT_Keyboard *GetInstance();
	bool IsPressed(const int key);
	bool IsDown(const int key);
	bool IsReleased(const int key);
	void Set(const int key, const int action);
	void Update();

};

#endif //__RT_KEYBOARD_H__
