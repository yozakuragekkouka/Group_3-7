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
	int TitleRogoHndl;            //タイトルロゴ
	int TitleRogox;               //タイトルロゴX座標
	int TitleRogoy;               //タイトルロゴY座標
	int alphaNum;                 //タイトルロゴ透明度
	bool PlaySceneFlag;           //PLAYSCENEに行くためのフラグ
	int PlaySceneStopcount;       //PLAYSCENEに行くまでの秒数
	int Titlecount;               //アクションする秒数(演出)
};

//タイトル構造体
struct PlayRogoInfo
{
	int PlayrogoHndl;             //PLAYROGO
	int Playrogo2Hndl;            //PLAYROGO2
	int PlayrogoOffHndl;          //PLAYROGO OFF
	int Playrogocount;            //描画する秒数(Playrogo)
};

//タイトルミノ構造体
struct TitleMino
{
	int Tmino;
	int Zmino;
	int Smino;
	int Lmino;
	int Jmino;
	int Omino;
	int Imino;
	int x[7];
	int y[7];
	int alphaNum[7];
};