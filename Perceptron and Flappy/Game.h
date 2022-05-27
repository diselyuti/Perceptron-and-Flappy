#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>

using namespace std;
using namespace sf;


class GameObject {
public:
	float gravitation = 0.005;
	float xSpeed = 0.000005;
	float dx , dy;
	float currentFrame;
	int height;
	Sprite _sprite;
	FloatRect _rect;

	GameObject(Sprite &sprite, FloatRect rect)
	{
		dx = 0;
		dy = 0;
		currentFrame = 0;
		_sprite = sprite; 
		_rect = rect;
	}

	void update(float time) {
		dy += gravitation * time;
		_rect.left += dx * time;
		_rect.top += dy * time;
		_sprite.setPosition(_rect.left, _rect.top);
	}
};

