#pragma once

#include "../Header/Angel.h"

class Collider {
private:	
	float DistanceX;
	float DistanceY;
public:
	vec4 rightTop;
	vec4 leftButtom;

	int hp;
	bool isDestroy = false;
	bool isHurt = false;

	void Init(float x, float y, vec4 position=0);//��lCollider
	void SetCollider(vec4 position);//�]��Collider
};

class Collision {
private:
public:
	GLboolean CheckCollider(Collider one, Collider two);
};