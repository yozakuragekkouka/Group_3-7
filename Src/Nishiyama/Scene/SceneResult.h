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

//リザルト画面関連
struct ResultInfo
{
	int BlackHandle;
	int scoae;
};