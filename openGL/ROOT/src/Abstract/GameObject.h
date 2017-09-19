#ifndef	 __GAME_OBJECT_H__
#define	 __GAME_OBJECT_H__

class RT_Camera;
class RT_Light;

class GameObject
{
public:
	virtual ~GameObject() {}
	virtual void Init() = 0;
	virtual void Update(float secs) = 0;
	virtual void Draw(const RT_Camera *camera, 
					  const RT_Light *light) = 0;
};

#endif //__GAME_OBJECT_H__
