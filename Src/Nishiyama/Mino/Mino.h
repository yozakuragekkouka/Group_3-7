#pragma once
#include <random>
#include "DxLib.h"
#include "MinoData.h"

class Mino
{
private:
	bool field[FIELD_SIZE_W][FIELD_SIZE_H];
	MINO_TYPE field_Mino[FIELD_SIZE_W][FIELD_SIZE_H];
	MINO_TYPE newMino[NEXT_MINO_NUM];

	MINO_TYPE currentMino;
	MINO_ANGLE currentAngle;
	int currentPosX;
	int currentPosY;

	int stopCount;
	int currentSpeed;

	std::random_device randomer;

public:
	void Init();
	void Step();
	void Fin();

	void MinoReset();
	bool MinoHit(int minoPosX, int minoPosY, MINO_ANGLE minoAngle);
};