#pragma once

const double	FRAMERATE		= 1.0 / 60.0;
const float		M2P				= 30;	// Meter to Pixel unit
const float		P2M				= 1 / M2P; // Pixel to meter unit
const float		R2D				= 180 / 3.14159;
const float		D2R				= 1 / R2D;
const int		screenWidth		= 1024;
const int		screenHeight	= 768;

//enum type{ PLAYER = 0, RECT = 1, CIRCLE = 2, TRIANGLE = 3, EDGE = 4 };

enum entityCategory {
	BOUNDARY = 0x0001,
	PLAYER = 0x0002,
	OBJECT = 0x0004,
	ENEMY = 0x0008
};