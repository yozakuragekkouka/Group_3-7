#pragma once
#include "Scene.h"

//シーン情報
class SceneTitle : public SceneBase
{
private:

public:
	void Init();

	void Step();

	void Draw();

	void Fin();
};

//タイトル構造体
struct TitleInfo
{
	int TitleHndl;                //タイトル画面
	bool PlaySceneFlag;           //PLAYSCENEに行くためのフラグ
	int PlaySceneStopcount;       //PLAYSCENEに行くまでの秒数
};

//タイトル構造体
struct PlayRogoInfo
{
	int PlayrogoHndl;             //PLAYROGO
	int Playrogo2Hndl;            //PLAYROGO2
	int PlayrogoOffHndl;          //PLAYROGO OFF
	int Playrogocount;            //描画する秒数(Playrogo)
};