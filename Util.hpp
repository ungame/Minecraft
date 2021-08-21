#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#define GL_CLAMP_TO_EDGE 0x812F

#define PI 3.141592

#define MassLengthX 1000
#define MassLengthY 1000
#define MassLengthZ 1000

bool Mass[MassLengthX][MassLengthY][MassLengthZ];

float Size = 20.f;

GLuint loadTexture(sf::String source)
{
	sf::Image image;
	image.loadFromFile(source);
	image.flipVertically();

	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.getSize().x, image.getSize().y, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return texture;
}

void drawBackSide(GLuint backSideTexture, float size) 
{
	glBindTexture(GL_TEXTURE_2D, backSideTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, -size, -size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, -size);
	glTexCoord2f(1, 1); glVertex3f(size, size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, -size);
	glEnd();
}

void drawFrontSide(GLuint frontSideTexture, float size) 
{
	glBindTexture(GL_TEXTURE_2D, frontSideTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(size, size, size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, size);
	glEnd();
}

void drawLeftSide(GLuint leftSideTexture, float size) 
{
	glBindTexture(GL_TEXTURE_2D, leftSideTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
	glTexCoord2f(1, 0); glVertex3f(-size, -size, -size);
	glTexCoord2f(1, 1); glVertex3f(-size, size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, size);
	glEnd();
}

void drawRightSide(GLuint rightSideTexture, float size)
{
	glBindTexture(GL_TEXTURE_2D, rightSideTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(size, -size, -size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(size, size, size);
	glTexCoord2f(0, 1); glVertex3f(size, size, -size);
	glEnd();
}

void drawBottomSide(GLuint bottomSideTexture, float size)
{
	glBindTexture(GL_TEXTURE_2D, bottomSideTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, -size, size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, size);
	glTexCoord2f(1, 1); glVertex3f(size, -size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, -size, -size);
	glEnd();
}

void drawTopSide(GLuint topSideTexture, float size)
{
	glBindTexture(GL_TEXTURE_2D, topSideTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, size, -size);
	glTexCoord2f(1, 0); glVertex3f(size, size, -size);
	glTexCoord2f(1, 1); glVertex3f(size, size, size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, size);
	glEnd();
}

void drawBox(GLuint box[], float size)
{
	drawBackSide(box[0], size);
	drawFrontSide(box[1], size);
	drawLeftSide(box[2], size);
	drawRightSide(box[3], size);
	drawBottomSide(box[4], size);
	drawTopSide(box[5], size);
}

bool isOutOfBoundsX(int x) {
	return x < 0 || x >= MassLengthX;
}

bool isOutOfBoundsY(int y) {
	return y < 0 || y >= MassLengthY;
}

bool isOutOfBoundsZ(int z) {
	return z < 0 || z >= MassLengthY;
}

bool isOutOfBounds(int x, int y, int z) {
	return isOutOfBoundsX(x) || isOutOfBoundsY(y) || isOutOfBoundsX(z);
}

bool hasMass(int x, int y, int z)
{
	if (isOutOfBounds(x, y, z))
	{
		return false;
	}

	return Mass[x][y][z];
}

