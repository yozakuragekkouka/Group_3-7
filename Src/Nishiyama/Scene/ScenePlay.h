#pragma once
#include "Scene.h"
#include "../Mino/Mino.h"

class ScenePlay : public SceneBase
{
private:
	Mino mino;

public:
	void Init();
	void Step();
	void Draw();
	void Fin();
};