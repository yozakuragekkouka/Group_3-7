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

//ƒŠƒUƒ‹ƒg‰æ–ÊŠÖ˜A
struct ResultInfo
{
	int BlackHandle;
	int scoae;
};