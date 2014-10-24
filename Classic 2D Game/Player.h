#pragma once

#include <Box2D/Box2D.h>
#include "RGBpixmap.h"
#include "Constant.h"
#include "ContactListener.h"

enum Direction{ LEFT = 0, RIGHT = 1 };
enum Status{ STOP = 0, MOVE = 1, JUMP = 2, CLIMB=3, PUSH};
class Player
{
public:
	Player(int centerX, int centerY, b2World* world)
	{
		X = centerX;
		Y = centerY;
		Width = 94;
		Height = 162;
		
		//94*162
		stop[0].loadTexture("Image/Character/stop1.png");
		walk[0].loadTexture("Image/Character/walk1.png");
		stop[1].loadTexture("Image/Character/stop2.png");
		walk[1].loadTexture("Image/Character/walk2.png");
		stop[2].loadTexture("Image/Character/stop3.png");
		walk[2].loadTexture("Image/Character/walk3.png");
		stop[3].loadTexture("Image/Character/stop4.png");
		walk[3].loadTexture("Image/Character/walk4.png");
		stop[4].loadTexture("Image/Character/stop5.png");
		walk[4].loadTexture("Image/Character/walk5.png");
		stop[5].loadTexture("Image/Character/stop6.png");
		walk[5].loadTexture("Image/Character/walk6.png");
		fly.loadTexture("Image/Character/fly.png");
		climb.loadTexture("Image/Character/LeftTouch.png");
		push.loadTexture("Image/Character/push.png");
		//down.loadTexture("Image/Character/crouch.png");


		b2BodyDef bodydef;
		bodydef.position.Set(X*P2M, Y*P2M);
		bodydef.fixedRotation = true;
		bodydef.type = b2_dynamicBody;
		bodydef.gravityScale = 3;
		//
		body = world->CreateBody(&bodydef);
		body->SetUserData(this); /*  typeid */
		//b2PolygonShape shape;
	//	shape.SetAsBox((Width-40)*P2M*SCALING / 2, (Height-20)*P2M*SCALING / 2);
		//shape.SetAsBox((Width - 80)*P2M*SCALING / 2, (Height - 60)*P2M*SCALING / 2);

		//center body shape
		b2CircleShape circle;
		circle.m_p.Set(0, 0);
		circle.m_radius = (Width - 40)*P2M/2;
		
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circle;
		fixtureDef.density = 1.00084f;
		fixtureDef.friction = 0.2f;
		/*fixtureDef.filter.categoryBits = entityCategory::PLAYER;
		fixtureDef.filter.maskBits =  BOUNDRY|entityCategory::OBJECT | entityCategory::ENEMY ;*/
		body->CreateFixture(&fixtureDef);

		circle.m_p.Set(0, -54 * P2M);
		circle.m_radius = 16 * P2M;
		fixtureDef.shape = &circle;
		fixtureDef.friction = 1.0f;
		body->CreateFixture(&fixtureDef);

		//circle.m_p.Set(0, 54 * P2M);
		//circle.m_radius = 6 * P2M;
		//fixtureDef.shape = &circle;
		//body->CreateFixture(&fixtureDef);
	
		b2PolygonShape shape;
		//add foot sensor fixture
		shape.SetAsBox(20 * P2M, 2 * P2M, b2Vec2(0, -((Height - 20) / 2)*P2M), 0);
		fixtureDef.isSensor = true;
		fixtureDef.shape = &shape;
		body->CreateFixture(&fixtureDef)->SetUserData((void*)1);

		//add left hand sensor
		shape.SetAsBox(0.3, 0.7, b2Vec2(-((Width - 40)/ 2)*P2M, 0), 0);
		fixtureDef.isSensor = true;
		body->CreateFixture(&fixtureDef)->SetUserData((void*)2);

		//add right hand sensor
		shape.SetAsBox(0.3, 0.7, b2Vec2(((Width - 40) / 2)*P2M, 0), 0);
		fixtureDef.isSensor = true;
		body->CreateFixture(&fixtureDef)->SetUserData((void*)3);

		//add head sensor
		shape.SetAsBox(0.3, 0.3, b2Vec2(0, ((Height - 20) / 2)*P2M), 0);
		fixtureDef.isSensor = true;
		body->CreateFixture(&fixtureDef)->SetUserData((void*)4);
		
	}

	~Player()
	{
		//delete[]Pic;
	}

	void move(Direction dir)
	{
		dirState = dir;
		if (!jumping)
			PicStat = MOVE;

		b2Vec2 vel = body->GetLinearVelocity();
		float desiredVel = 0;
		desiredVel = dir == RIGHT ? 15 : -15;
		float velChange = desiredVel - vel.x;
		float impulse = body->GetMass() * velChange; //disregard time factor
		body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter(), true);
	}


	void jump()
	{	
		if (jumping)
			return;
		jumping = true;
		PicStat = JUMP;
		PicCount = 0;
		body->ApplyLinearImpulse(b2Vec2(0, body->GetMass() * 27 *SCALING), body->GetWorldCenter(), true);
	}

	b2Vec2 getPosition(void)
	{
		return b2Vec2(X, Y);
	}

	void toPosition(int cx, int cy)
	{
		body->SetTransform(P2M*(b2Vec2(cx, cy)), 0);
		Update();
	}

	b2Vec2 getVeloctity()
	{
		return body->GetLinearVelocity();
	}

	void Update()
	{
		b2Vec2 position = body->GetWorldCenter();
		X = position.x * M2P;
		Y = position.y * M2P;
		
		if (ContactListener::PlayerOnGround())
		{
			if (jumping)
				PicCount = 0;
			jumping = false;
			if (body->GetLinearVelocity().x == 0)
				PicStat = STOP;
			else
				PicStat = MOVE;
		}
		else
		{
			jumping = true;
			PicStat = JUMP;
		}

		if ((ContactListener::PlayerTouchLeft() || ContactListener::PlayerTouchRight()))
		{
			jumping = false;
			PicCount = 0;
			PicStat = CLIMB;
		}

		if (ContactListener::PlayerOnGround() && (ContactListener::PlayerTouchLeft() || ContactListener::PlayerTouchRight()))
		{
			jumping = false;
			PicCount = 0;
			PicStat = PUSH;
		}

		//count+1 per 1/60 sec
		Timer++;
		if (Timer >= 8)
		{
			PicCount++;
			//idle++;
			Timer = 0;
			if ((PicStat == STOP || PicStat == MOVE) && PicCount > 5)
				PicCount = 0;
		}
		
	}

	void Render()
	{
		RGBApixmap *temp;
		if (PicStat == STOP)
			temp = &stop[PicCount];
		else if (PicStat == MOVE)
			temp = &walk[PicCount];
		else if (PicStat == CLIMB)
			temp = &climb;
		else if (PicStat == PUSH)
			temp = &push;
		else
			temp = &fly;

		if (dirState == RIGHT)
			temp->blendTex(X + Width*SCALING / 2, Y - Height*SCALING / 2, -SCALING, SCALING);
		else
			temp->blendTex(X - Width*SCALING / 2, Y - Height*SCALING / 2, SCALING, SCALING);
	}

private:
	b2Body*			body;
	int				X;
	int				Y;
	int				Width;
	int				Height;
	bool			jumping = false;
	bool			runing = false;
	Status			PicStat = STOP;
	Direction		dirState = LEFT;
	int				Timer = 0;
	//int				idle = 0;
	int				PicCount = 0;
	RGBApixmap		stop[6];
	RGBApixmap		walk[6];
	RGBApixmap		fly;
	RGBApixmap		climb;
	RGBApixmap		push;
	const double    SCALING = 1;

	
};

