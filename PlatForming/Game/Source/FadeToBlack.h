#ifndef __FADETOBLACK_H__
#define __FADETOBLACK_H__

#include "Module.h"
#include "Animation.h"


class FadeToBlack : public Module
{
public:
	FadeToBlack(bool enabled);

	virtual ~FadeToBlack();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

public:
	
};

#endif