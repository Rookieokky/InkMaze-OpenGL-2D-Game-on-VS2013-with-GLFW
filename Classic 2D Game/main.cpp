
#include <glew.h>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"glew32.lib")


#include <glfw3.h>
#pragma comment(lib,"glfw3.lib")

#include <Box2D/Box2D.h>
#pragma comment(lib,"Box2D.lib")

#include <iostream>
#include <Windows.h>
#include "RGBpixmap.h"
#include "Player.h"
#include "Camera.h"
#include "Constant.h"
#include "Obstacle.h"
#include "Font.h"
#pragma comment(lib,"freetype253_D.lib")
#pragma comment(lib,"ftgl_D.lib")
#include "ContactListener.h"
using namespace std;
/*	Screen Property*/
GLFWwindow*			window;
Camera*				camera;
RGBApixmap			cursor;
double				startTime;
double				pTime; //Time passed per frame
Text				text("arial.ttf", 150);

/* Game Property */
b2World*			world;
bool				DEBUG = false;
bool				isFinished = false;
Player*				player;
RGBApixmap			Background;
RGBApixmap			Foreground;
RGBApixmap			cusor[6];
RGBApixmap			complete;
bool				KeyPressed[3] = { false };
int					cusorCounter = 0;
int					cusorTimer = 0;
double				old_time;
double				finishTime;


void obstacleSetup()
{
	Obstacle(world, 180, 180 + 6000, 4472 - 320, 4472 - 335 + 155);
	Obstacle(world, 5760, 5780 + 180, 4472 - 4302, 4472 - 4302 + 4017);
	Obstacle(world, 170, 170 + 5645, 4472 - 4342, 4472 - 4342 + 137);
	Obstacle(world, 157, 157 + 203, 4472 - 4390, 4472 - 4390 + 3474);
	Obstacle(world, 157, 157 + 203, 4472 - 603, 4472 - 603 + 313);
	Obstacle(world, 5710, 5710 + 72, 4472 - 3010, 4472 - 3010 + 2424);
	Obstacle(world, 0, 157, 4472 - 4390 + 3474, 4472 - 603);


	Obstacle(world, 4690, 4690 + 1065, 4472 - 610, 4472 - 610 + 30);
	Obstacle(world, 3468, 3468 + 922, 4472 - 604, 4472 - 604 + 20);
	//Obstacle(world, 2574, 2574 + 764, 4472 - 660, 4472 - 660 + 30);
	Obstacle(world, 2602, 2602 + 648, 4472 - 668, 4472 - 668 + 16);
	Obstacle(world, 0, 233, 4472 - 617, 4472 - 617 + 19);

	Obstacle(world, 296, 296 + 2112, 4472 - 618, 4472 - 618 + 26);
	Obstacle(world, 4188, 4188 + 26, 4472 - 1814, 4472 - 1814 + 1208);

	//Obstacle(world, 4216, 4216 + 288, 4472 - 930, 4472 - 930 + 50);
	Obstacle(world, 4216, 4494, 4472 - 930, 4472 - 930 + 50);
	Obstacle(world, 4704, 4704 + 668, 4472 - 908, 4472 - 908 + 20);
	Obstacle(world, 4444, 4444 + 50, 4472 - 1516, 4472 - 1516 + 584);
	Obstacle(world, 4692, 4692 + 28, 4472 - 1796, 4472 - 1796 + 908);
	Obstacle(world, 4206, 4206 + 948, 4472 - 1824, 4472 - 1824 + 16);
	Obstacle(world, 5368, 5368 + 28, 4472 - 2112, 4472 - 2112 + 1220);
	Obstacle(world, 5104, 5104 + 260, 4472 - 1236, 4472 - 1236 + 42);
	Obstacle(world, 4718, 4718 + 470, 4472 - 1578, 4472 - 1578 + 22);

	Obstacle(world, 2572, 2572 + 1370, 4472 - 922, 4472 - 922 + 35);
	Obstacle(world, 940, 940 + 1183, 4472 - 908, 4472 - 908 + 15);
	Obstacle(world, 0, 675, 4472 - 920, 4472 - 920 + 27);
	Obstacle(world, 2418, 2418 + 1192, 4472 - 1226, 4472 - 1226 + 26);
	//Obstacle(world, 960, 960 + 886, 4472 - 1208, 4472 - 1208 + 20);
	Obstacle(world, 960, 1820 + 21, 4472 - 1208, 4472 - 1208 + 20);
	//Obstacle(world, 954, 954 + 610, 4472 - 1511, 4472 - 1511 + 16);
	Obstacle(world, 954, 1522 + 38, 4472 - 1511, 4472 - 1511 + 16);
	
	Obstacle(world, 2106, 2106 + 1790, 4472 - 1817, 4472 - 1817 + 18);
	Obstacle(world, 2109, 2109 + 151, 4472 - 1566, 4472 - 1566 + 18);
	Obstacle(world, 644, 644 + 654, 4472 - 1816, 4472 - 1816 + 22);
	Obstacle(world, 274, 274 + 402, 4472 - 2136, 4472 - 2136 + 38);
	Obstacle(world, 1526, 1526 + 1890, 4472 - 2128, 4472 - 2128 + 26);
	Obstacle(world, 4162, 4162 + 358, 4472 - 2132, 4472 - 2132 + 38);
	Obstacle(world, 4776, 4776 + 618, 4472 - 2124, 4472 - 2124 + 28);

	Obstacle(world, 652, 652 + 2150, 4472 - 2376, 4472 - 2376 + 16);
	Obstacle(world, 3432, 3432 + 360, 4472 - 2332, 4472 - 2332 + 36);
	Obstacle(world, 3924, 3924 + 302, 4472 - 2428, 4472 - 2428 + 30);
	Obstacle(world, 4474, 4474 + 334, 4472 - 2426, 4472 - 2426 + 28);
	Obstacle(world, 5036, 5036 + 334, 4472 - 2426, 4472 - 2426 + 28);
	Obstacle(world, 3006, 3006 + 332, 4472 - 2726, 4472 - 2726 + 16);
	Obstacle(world, 3590, 3590 + 922, 4472 - 2728, 4472 - 2728 + 13);
	Obstacle(world, 4790, 4790 + 598, 4472 - 2728, 4472 - 2728 + 16);
	Obstacle(world, 2976, 2976 + 950, 4472 - 3040, 4472 - 3040 + 20);
	Obstacle(world, 3898, 3898 + 910, 4472 - 3310, 4472 - 3310 + 24);
	Obstacle(world, 5078, 5078 + 700, 4472 - 3022, 4472 - 3022 + 16);

	Obstacle(world, 929, 929 + 35, 4472 - 907, 4472 - 907 + 286);
	Obstacle(world, 2082, 2082 + 41, 4472 - 1069, 4472 - 1069 + 167);
	Obstacle(world, 4960, 4960 + 21, 4472 - 1330, 4472 - 1330 + 422);
	Obstacle(world, 1820, 1820 + 21, 4472 - 1902, 4472 - 1902 + 996);
	Obstacle(world, 620, 620 + 53, 4472 - 1582, 4472 - 1582 + 673);
	Obstacle(world, 951, 951 + 44, 4472 - 1507, 4472 - 1507 + 318);
	Obstacle(world, 2091, 2091 + 37, 4472 - 1811, 4472 - 1811 + 490);
	Obstacle(world, 2410, 2410 + 24, 4472 - 1811, 4472 - 1811 + 615);
	Obstacle(world, 3908, 3908 + 38, 4472 - 3475, 4472 - 3475 + 2586);
	Obstacle(world, 4771, 4771 + 33, 4472 - 2775, 4472 - 2775 + 675);
	Obstacle(world, 5031, 5031 + 65, 4472 - 3020, 4472 - 3020 + 622);
	Obstacle(world, 4735, 4735 + 74, 4472 - 3307, 4472 - 3307 + 300);
	Obstacle(world, 628, 628 + 50, 4472 - 2130, 4472 - 2130 + 336);
	Obstacle(world, 1522, 1522 + 38, 4472 - 2127, 4472 - 2127 + 633);
	Obstacle(world, 2962, 2962 + 64, 4472 - 3038, 4472 - 3038 + 916);
	Obstacle(world, 4155, 4155 + 72, 4472 - 2424, 4472 - 2424 + 328);

	Obstacle(world, 302, 302 + 334, 4472 - 4240, 4472 - 4240 + 1642);
	Obstacle(world, 628, 628 + 274, 4472 - 4238, 4472 - 4238 + 1508);
	Obstacle(world, 896, 896 + 310, 4472 - 4234, 4472 - 4234 + 1330);
	Obstacle(world, 1208, 1208 + 286, 4472 - 4224, 4472 - 4224 + 1182);
	Obstacle(world, 1490, 1490 + 266, 4472 - 4208, 4472 - 4208 + 1022);
	Obstacle(world, 1744, 1744 + 280, 4472 - 4212, 4472 - 4212 + 880);

	//Obstacle(world, );
}

void Init()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //background color(1.0, 1.0, 1.0): white color

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, screenWidth, screenHeight);
	gluPerspective(75, 4.0 / 3.0, 0.01, 10000.0);

	//	glOrtho(0.0, (GLfloat)screenWidth, 0.0, (GLfloat)screenHeight, -1.0, 1.0);
	//	glViewport(0, 0, screenWidth, screenHeight);
	//	glMatrixMode(GL_MODELVIEW);
	//	glLoadIdentity();


	//gluOrtho2D(0.0, (GLfloat)screenWidth, 0.0, (GLfloat)screenHeight);
	//glOrtho(0.0, (GLfloat)screenWidth, 0.0, (GLfloat)screenHeight, -1.0, 1.0);
	//glViewport(0, 0, screenWidth, screenHeight);
	//gluPerspective(75, 4.0 / 3.0, 0.01, 10000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	world = new b2World(b2Vec2(0.0f, -9.8f));
	world->SetContactListener(new ContactListener());


	Background.loadTexture("Image/background.png");
	Foreground.loadTexture("Image/foreground.png");
	cusor[0].loadTexture("Image/cusor1.png");
	cusor[1].loadTexture("Image/cusor2.png");
	cusor[2].loadTexture("Image/cusor3.png");
	cusor[3].loadTexture("Image/cusor4.png");
	cusor[4].loadTexture("Image/cusor5.png");
	cusor[5].loadTexture("Image/cusor6.png");
	complete.loadTexture("Image/Complete.png");

	player = new Player(5600, 3957, world);
	obstacleSetup();

	camera = new Camera(5600, 3957+30, 500,
						5600, 3957+30, 0,
						0, 1, 0);
	camera->Update();

}

void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			case GLFW_KEY_LEFT:
				KeyPressed[LEFT] = true;
				break;

			case GLFW_KEY_RIGHT:
				KeyPressed[RIGHT] = true;
				break;

			case GLFW_KEY_R:
				//retry
				player->toPosition(5600, 3957);
				player->move(LEFT);
				camera->toPosition(player->getPosition() + b2Vec2(0, 30));
				startTime = glfwGetTime();
				isFinished = false;
				glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
				break;

			case GLFW_KEY_F12:
				DEBUG = DEBUG ? false : true;
				//isFinished = true;
				//finishTime = glfwGetTime();
				//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
				break;

			case GLFW_KEY_ESCAPE:
				exit(0);
				break;

			case GLFW_KEY_X:

			case GLFW_KEY_SPACE:
				player->jump();
				break;

			default:
				break;

		}

	}

	else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
			case GLFW_KEY_LEFT:
				KeyPressed[LEFT] = false;
				break;

			case GLFW_KEY_RIGHT:
				KeyPressed[RIGHT] = false;
				break;


			default:
				break;
		}
	}
}

void KeyHandler(void)
{
	if (KeyPressed[LEFT])
		player->move(LEFT);

	else if (KeyPressed[RIGHT])
		player->move(RIGHT);
}

//void ResizeCallback(GLFWwindow* window, int width, int height)
//{
//	/* Save the new width and height */
//	screenWidth = width;
//	screenHeight = height;
//
//	/* Reset the viewport... */
//	glViewport(0, 0, screenWidth, screenHeight);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//
//	glOrtho(0.0, (GLfloat)screenWidth, 0.0, (GLfloat)screenHeight, -1.0, 1.0);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
		{

		}
	}
}

void Render(void)
{


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/* Background */

	Background.blendTex(0, 0);

	if (DEBUG)
	{
		b2Body* bodyList = world->GetBodyList();
		//bodyList = bodyList->GetNext();
		while (bodyList)
		{
			b2Fixture* fixtureList = bodyList->GetFixtureList();
			while (fixtureList)
			{
				//fixtureList->GetShape() == 
				b2Shape::Type shapeType = fixtureList->GetType();
				int nVertex = 0;
				if (shapeType == b2Shape::e_polygon)
				{
					nVertex = ((b2PolygonShape*)fixtureList->GetShape())->GetVertexCount();
					b2Vec2 points[4];
					for (int i = 0; i < nVertex; i++)
						points[i] = ((b2PolygonShape*)fixtureList->GetShape())->GetVertex(i);
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glColor4ub(255, 255, 0, 128);
					glPushMatrix();
					glTranslated(bodyList->GetWorldCenter().x*M2P, bodyList->GetWorldCenter().y*M2P, 0);
					glRotatef(bodyList->GetAngle()*R2D, 0, 0, 1);
					glBegin(GL_QUADS);
					for (int i = 0; i < nVertex; i++)
						glVertex2f(points[i].x*M2P, points[i].y*M2P);
					glEnd();
					glPopMatrix();
					glDisable(GL_BLEND);
				}
				else if (shapeType == b2Shape::e_circle)
				{
					float radius = ((b2CircleShape*)fixtureList->GetShape())->m_radius;
					float x = ((b2CircleShape*)fixtureList->GetShape())->m_p.x;
					float y = ((b2CircleShape*)fixtureList->GetShape())->m_p.y;
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glColor4ub(255, 0, 0, 255);
					glPushMatrix();
					glTranslated((bodyList->GetWorldCenter().x + x)*M2P, (bodyList->GetWorldCenter().y + y)*M2P, 0);
					glRotatef(bodyList->GetAngle()*R2D, 0, 0, 1);
					glBegin(GL_LINE_LOOP);
					glVertex2f(0, 0);
					for (float a = 0; a <= 360 * D2R; a += 10 * D2R)
						glVertex2f(cosf(a)*radius*M2P, sinf(a)*radius*M2P);
					glEnd();
					glPopMatrix();
					glDisable(GL_BLEND);
				}


				fixtureList = fixtureList->GetNext();
			}
			bodyList = bodyList->GetNext();
		}
	}

	if (!isFinished)
	{
		/* Image Loaded */
		player->Render();
		Foreground.blendTex(0, 0);

		/* Cusor */
		double cx, cy;
		glfwGetCursorPos(window, &cx, &cy);
		cy = screenHeight - cy;
		cusor[cusorCounter].blendTex(cx + camera->GetPosition2().x + 200 - 100, cy + camera->GetPosition2().y - 600 - 100, 0.5, 0.5);
	}
	else
	{
		complete.blendTex(camera->GetPosition2().x - 1024/2, camera->GetPosition2().y - 768/2);
		char message[30];
		sprintf_s(message, "%.1f", finishTime - startTime);
		text.Render(message, camera->GetPosition2().x - 400 + 150, camera->GetPosition2().y - 300 + 120);
	}

}

void Update(void)
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	/* Camera move */
	//camera->toPosition(player->getPosition() + b2Vec2(0, 30));

	b2Vec2 cameraPos = camera->GetPosition2();
	b2Vec2 playerPos = player->getPosition();
	b2Vec2 playerVel = M2P*player->getVeloctity();
	float passedTime = glfwGetTime() - old_time;
	if (abs(playerVel.x) < 0.1)	playerVel.x = 0;
	if (abs(playerVel.y) < 0.1)	playerVel.y = 0;

	//cout << cameraPos.x << ", " << cameraPos.y << endl;
	//cout << playerPos.x << ", " << playerPos.y << endl;
	//cout << playerVel.x << ", " << playerVel.y << endl;

	if (cameraPos.x - playerPos.x > 200 && playerVel.x < 0)
		camera->moveHorizeon(passedTime*playerVel.x);
	else if (playerPos.x - cameraPos.x > 200 && playerVel.x > 0)
		camera->moveHorizeon(passedTime*playerVel.x);

	if (cameraPos.y - playerPos.y > 150 && playerVel.y < 0)
		camera->moveVertical(passedTime*playerVel.y);
	else if (playerPos.y - cameraPos.y > 150 && playerVel.y > 0)
		camera->moveVertical(passedTime*playerVel.y);

	/* Update */
	KeyHandler();
	player->Update();
	camera->Update();

	if (++cusorTimer >= 8)
	{
		cusorCounter = (cusorCounter + 1) % 6;
		cusorTimer = 0;
	}

	/* Game over */
	b2Vec2 Pos = player->getPosition();
	if ( !isFinished && Pos.x >= 40 && Pos.x <= 40 + 164 && Pos.y >= 4472 - 902 && Pos.y <= 4472 - 902 + 290)
	{
		isFinished = true;
		finishTime = glfwGetTime();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}

	/* Teleport Setup */
	if (Pos.x == 1022 && Pos.y == 3040)
	{
		player->toPosition(4327, 3500);
		camera->toPosition(b2Vec2(4327, 3500) + b2Vec2(0, 30));
	}
	else if (Pos.x == 3053 && Pos.y == 1515)
	{
		player->toPosition(2461, 2736);
		camera->toPosition(b2Vec2(2461, 2736) + b2Vec2(0, 30));
		player->move(RIGHT);
	}
	else if (Pos.x == 5340 && Pos.y == 3341)
	{
		player->toPosition(3973, 1249);
		camera->toPosition(b2Vec2(3973, 1249) + b2Vec2(0, 30));
	}
	else if (Pos.x == 5123 && Pos.y == 1529)
	{
		player->toPosition(991, 3642);
		camera->toPosition(b2Vec2(991, 3642) + b2Vec2(0, 30));
		player->move(RIGHT);
	}
}

int main(int argc, char* argv[])
{
	FreeConsole();
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(screenWidth, screenHeight, "Ink Maze", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 100, 100);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	Init();
	/*glfwSetWindowSizeCallback(window, ResizeCallback);*/
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetKeyCallback(window, KeyboardCallback);
	old_time = glfwGetTime();
	startTime = old_time;

	while (!glfwWindowShouldClose(window))
	{

		if ((glfwGetTime() - old_time) < FRAMERATE)
		{
			/* Computing */

			continue;
		}

		/* Render here */
		/* Display frame rate: 60fps */
		world->Step(FRAMERATE, 8, 3);
		//
		double cx, cy;
		//glfwGetCursorPos(window, &cx, &cy);
		//cout << cx << ", " << cy << endl;

		Update();
		Render();
		old_time = glfwGetTime();


		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}

