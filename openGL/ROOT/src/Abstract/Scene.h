#ifndef	 __SCENE_H__
#define	 __SCENE_H__

class Scene
{
public:
	virtual ~Scene() {}
	virtual void Init() = 0;
	virtual void Update(float secs) = 0;
	virtual void Draw() = 0;
	virtual void Deinit() = 0;
};

#endif //__SCENE_H__
