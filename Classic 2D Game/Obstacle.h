#pragma once
#include <Box2D/Box2D.h>
#include "Constant.h"

class Obstacle
{
public:
	Obstacle(b2World* world,int left, int right, int down, int up)
	{
		X = float(left + right) / 2.0f;
		Y = float(up + down) / 2.0f;
		width = right - left;
		height = up - down;

		b2BodyDef bodydef;
		bodydef.position.Set(X*P2M, Y*P2M);
		obstacle = world->CreateBody(&bodydef);
		obstacle->SetUserData(this);

		b2PolygonShape shape;
		shape.SetAsBox(width*P2M / 2.0, height*P2M / 2.0);
		b2FixtureDef fixturedef;
		fixturedef.shape = &shape;
		fixturedef.friction = 1.2f;
		/*fixturedef.filter.categoryBits = entityCategory::BOUNDARY;
		fixturedef.filter.maskBits = entityCategory::PLAYER | entityCategory::OBJECT | entityCategory::ENEMY;*/
		obstacle->CreateFixture(&fixturedef);
	}

	~Obstacle()
	{
	}

	b2Body* getBody()
	{
		return obstacle;
	}

	void draw()
	{
		b2Vec2 points[4];
		for (int i = 0; i < 4; i++)
			points[i] = ((b2PolygonShape*)obstacle->GetFixtureList()->GetShape())->GetVertex(i);

		glColor3ub(255,255,255);
		glPushMatrix();
		glTranslated(X, Y, 0);
		glBegin(GL_QUADS);
		for (int i = 0; i < 4; i++)
			glVertex2f(points[i].x*M2P, points[i].y*M2P);
		glEnd();
		glPopMatrix();
	}

private:
	float X;
	float Y;
	int width;
	int height;
	b2Body* obstacle;
};

