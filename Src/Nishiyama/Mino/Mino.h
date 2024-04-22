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

	int LmoveCount;
	int RmoveCount;
	int accelerationCount;

	int AddSpeedCount;

	int dropCount;
	int stopCount;
	int currentSpeed;

	int renCount;
	int doujiCount;

	std::random_device randomer;

	int BlockHandle[(int)MINO_TYPE::KIND_NUM + 1];
	int MinoHandle[(int)MINO_TYPE::KIND_NUM];
	
public:
	~Mino();

	void Init();
	void Step();
	void Fin();

	void PredictionDraw();
	void NextDraw();
	void FieldDraw();

	void MinoReset();
	void MinoStop();
	bool MinoHit(int minoPosX, int minoPosY, MINO_ANGLE minoAngle);

	bool DeleteJudge(int JudgeHeight);
	void Delete(int JudgeHeight);
};