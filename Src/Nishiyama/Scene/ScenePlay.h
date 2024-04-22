#pragma once
#include "Scene.h"
#include "../Mino/Mino.h"
#include "../Shapes/Shapes.h"

constexpr char PLAY_SCENE_BG_PATH[128] = "Data/PlayScene/�w�i.jpg";
constexpr char PLAY_SCENE_GAMEOVER_BG_PATH[128] = "Data/Result/�����w�i.png";
constexpr char PLAY_SCENE_GAMEOVER_TEXT_PATH[128] = "Data/Result/�Q�[���I�[�o�[�t�H���g.png";

class ScenePlay : public SceneBase
{
private:
	Mino mino;
	Rect_Data BG_Image;
	Rect_Data GO_BG_Image;
	Rect_Data GO_TEXT_Image;

	int gameOverCount;

public:
	void Init();
	void Step();
	void Draw();
	void Fin();
};