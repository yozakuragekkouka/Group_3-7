#pragma once
#include "Scene.h"
#include "../Mino/Mino.h"
#include "../Shapes/Shapes.h"

constexpr char PLAY_SCENE_BG_PATH[128] = "Data/PlayScene/青背景.jpg";
constexpr char PLAY_SCENE_GAMEOVER_BG_PATH[128] = "Data/Result/薄黒背景.png";
constexpr char PLAY_SCENE_GAMEOVER_TEXT_PATH[128] = "Data/Result/ゲームオーバーフォント.png";

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