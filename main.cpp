#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#pragma comment (lib, "glu32.lib")
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <time.h>

#include "Util.hpp"
#include "Player.hpp"

using namespace sf;

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define MOUSE_SENSIBILITY 4

void initOpenGL() 
{
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 1.0f, 2000.0f);
	glEnable(GL_TEXTURE_2D);
}

Image createTerrain()
{
	Image heightmap;
	heightmap.loadFromFile("resources/terrain/heightmap.png");

	for (int x = 0; x < 256; x++)
	{
		for (int z = 0; z < 256; z++)
		{
			int c = heightmap.getPixel(x, z).r / 15;
			
			for (int y = 0; y < c; y++)
			{
				if (y > c - 3)
				{
					Mass[x][y][z] = true;
				}
			}
		}
	}

	return heightmap;
}

void loadSkyBox(GLuint skybox[6])
{
	skybox[0] = loadTexture("resources/sky/front.bmp");
	skybox[1] = loadTexture("resources/sky/back.bmp");
	skybox[2] = loadTexture("resources/sky/left.bmp");
	skybox[3] = loadTexture("resources/sky/right.bmp");
	skybox[4] = loadTexture("resources/sky/bottom.bmp");
	skybox[5] = loadTexture("resources/sky/top.bmp");
}

void loadBox(GLuint box[6])
{
	box[0] = loadTexture("resources/box/side.jpg");
	box[1] = loadTexture("resources/box/side.jpg");
	box[2] = loadTexture("resources/box/side.jpg");
	box[3] = loadTexture("resources/box/side.jpg");
	box[4] = loadTexture("resources/box/bottom.jpg");
	box[5] = loadTexture("resources/box/top.jpg");
}

int main()
{
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Minecraft", sf::Style::Default, sf::ContextSettings(24));

	initOpenGL();

	ShowCursor(FALSE);
	
	Texture cursorTex;
	cursorTex.loadFromFile("resources/cursor.png");
	
	Sprite cursor(cursorTex);
	cursor.setOrigin(8, 8);
	cursor.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	Image terrain = createTerrain();

	GLuint skybox[6];
	loadSkyBox(skybox);

	GLuint box[6];
	loadBox(box);

	Clock clock;
	bool mLeft = 0, mRight = 0;
	Player player(100, 200, 100);

	Texture introTex;
	introTex.loadFromFile("resources/intro.png");
	Sprite intro(introTex);

	sf::Font font1;
	font1.loadFromFile("resources/fonts/sansation.ttf");

	sf::Font font2;
	font2.loadFromFile("resources/fonts/prstartk.ttf");

	sf::Text text1;
	text1.setFont(font1);
	text1.setString("(Pressione Enter)");
	text1.setCharacterSize(20);
	text1.setPosition(540, 370);
	text1.setFillColor(sf::Color::White);

	sf::Text text2;
	text2.setFont(font2);
	text2.setString("Minecraft C++");
	text2.setCharacterSize(40);
	text2.setPosition(270, 320);
	text2.setFillColor(sf::Color::White);

	Music music;
	music.openFromFile("resources/sounds/ambient-wave.ogg");
	music.play();

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		time = time / 50;
		if (time > 3) time = 3;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))
				window.close();

			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Enter))
			{
				intro.setPosition(-1000, -1000);
				text1.setPosition(-1000, -1000);
				text2.setPosition(-1000, -1000);
				music.stop();
			}

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Mouse::Right) mRight = 1;
				if (event.key.code == Mouse::Left) mLeft = 1;
			}
		}

		glClear(GL_DEPTH_BUFFER_BIT);

		player.keyboard();
		player.update(time);

		// mouse
		POINT mouseXY;
		GetCursorPos(&mouseXY);
		int xt = window.getPosition().x + (WINDOW_WIDTH / 2);
		int yt = window.getPosition().y + (WINDOW_HEIGHT / 2);

		angleX += (xt - mouseXY.x) / MOUSE_SENSIBILITY;
		angleY += (yt - mouseXY.y) / MOUSE_SENSIBILITY;

		if (angleY < -89.0) { angleY = -89.0; }
		if (angleY > 89.0) { angleY = 89.0; }

		SetCursorPos(xt, yt);

		if (mRight || mLeft)
		{
			float x = player.x;
			float y = player.y + player.h / 2;
			float z = player.z;

			int X, Y, Z, oldX = 0, oldY = 0, oldZ = 0;
			int dist = 0;

			while (dist < 100)
			{
				dist++;

				x += -sin(angleX / 180 * PI); X = x / Size;
				y += tan(angleY / 180 * PI); Y = y / Size;
				z += -cos(angleX / 180 * PI); Z = z / Size;

				if (hasMass(X, Y, Z))
				{
					if (mLeft)
					{
						Mass[X][Y][Z] = false;
						break;
					}
					else
					{
						Mass[oldX][oldY][oldZ] = true;
						break;
					}
				}
				oldX = X;
				oldY = Y;
				oldZ = Z;
			}
		}

		mLeft = mRight = 0;

		// apply some transformations
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		GLdouble centerX = (GLdouble)player.x - sin(angleX / 180 * PI);
		GLdouble centerY = (GLdouble)player.y + tan(angleY / 180 * PI);
		GLdouble centerZ = (GLdouble)player.z - cos(angleX / 180 * PI);
		gluLookAt(player.x, player.y, player.z, centerX, centerY, centerZ, 0, 1, 0);

		int R = 30;

		int X = player.x / Size;
		int Y = player.y / Size;
		int Z = player.z / Size;

		// draw a cube
		for (int x = X - R; x < X + R; x++)
		{
			for (int y = 0; y < 25; y++)
			{
				for (int z = Z - R; z < Z + R; z++)
				{
					if (!hasMass(x, y, z))
					{
						continue;
					}

					glTranslatef(Size * x + Size / 2, Size * y + Size / 2, Size * z + Size / 2);
					drawBox(box, Size / 2);
					glTranslatef(-Size * x - Size / 2, -Size * y - Size / 2, -Size * z - Size / 2);
				}
			}
		}

		glTranslatef(player.x, player.y, player.z);
		drawBox(skybox, 1000);
		glTranslatef(-player.x, -player.y, -player.z);

		window.pushGLStates();

		window.draw(cursor);
		window.draw(intro);
		window.draw(text1);
		window.draw(text2);

		window.popGLStates();

		window.display();

	}

    return EXIT_SUCCESS;
}