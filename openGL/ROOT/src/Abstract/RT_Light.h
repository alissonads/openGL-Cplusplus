#ifndef	 __RT_LIGHT_H__
#define	 __RT_LIGHT_H__

class RT_Shader;

class RT_Light
{
public:
	virtual void Apply(RT_Shader &shader) const = 0;
};

#endif //__RT_LIGHT_H__
