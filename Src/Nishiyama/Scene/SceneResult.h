#pragma once
#include "Scene.h"

class SceneResult : public SceneBase
{
private:

public:
	void Init();

	void Step();

	void Draw();

	void Fin();
};

//���U���g��ʊ֘A
struct ResultInfo
{
	int BlackHandle;
	int scoae;
};