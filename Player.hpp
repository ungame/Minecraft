#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Util.hpp"

using namespace sf;

float angleX, angleY;

class Player
{

public:
	float x, y, z;
	float dx, dy, dz;
	float w, h, d; // largura, altura, profundidade
	bool onGround;
	float speed;

	Player(float x0, float y0, float z0)
	{
		x = x0, y = y0, z = z0;
		dx = 0, dy = 0, dz = 0;
		w = 5;
		h = 20;
		d = 5;
		speed = 5;
		onGround = false;
	}

	void update(float time)
	{
		if (!onGround) dy -= 1.5 * time;
		onGround = 0;

		x += dx * time;
		collision(dx, 0, 0);

		y += dy * time;
		collision(0, dy, 0);

		z += dz * time;
		collision(0, 0, dz);

		dx = dz = 0;
	}

	void collision(float Dx, float Dy, float Dz)
	{
		for (int X = (x - w) / Size; X < (x + w) / Size; X++)
		{
			for (int Y = (y - h) / Size; Y < (y + h) / Size; Y++)
			{
				for (int Z = (z - d) / Size; Z < (z + d) / Size; Z++)
				{
					if (hasMass(X, Y, Z))
					{
						if (Dx > 0) x = X * Size - w;
						if (Dx < 0) x = X * Size + Size + w;
						if (Dy > 0) y = Y * Size - h;
						if (Dy < 0)
						{
							y = Y * Size + Size + h;
							onGround = true;
							dy = 0;
						}
						if (Dz > 0) z = Z * Size - d;
						if (Dz < 0) z = Z * Size + Size + d;
					}
				}
			}
		}
	}

	void keyboard()
	{
		if (Keyboard::isKeyPressed(Keyboard::F))
		{
			onGround = true;
		}

		if (Keyboard::isKeyPressed(Keyboard::G))
		{
			y += 2;
		}

		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			if (onGround)
			{
				onGround = false;
				dy = 12;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			dx = -sin(angleX / 180 * PI) * speed;
			dz = -cos(angleX / 180 * PI) * speed;
		}

		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			dx = sin(angleX / 180 * PI) * speed;
			dz = cos(angleX / 180 * PI) * speed;
		}

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			dx = sin((angleX + 90) / 180 * PI) * speed;
			dz = cos((angleX + 90) / 180 * PI) * speed;
		}

		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			dx = sin((angleX - 90) / 180 * PI) * speed;
			dz = cos((angleX - 90) / 180 * PI) * speed;
		}
	}
};