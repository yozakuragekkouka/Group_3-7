#include "DxLib.h"
#include "../../Common.h"
#include "Scene.h"
//2309405 宇賀塚暖紀

#include "SceneTitle.h"
#include "../Input/Input.h"

#define TITLE_PATH "Data/Title/タイトル.png"
//プレイロゴ
#define PLAY_ROGO_PATH "Data/Title/PLAY1.png"
#define PLAY_ROGO2_PATH "Data/Title/PLAY2.png"
#define PLAY_ROGO_OFF_PATH "Data/Title/PLAY OFF.png"
//テトリミノ
#define TITLE_T_MINO_PATH "Data/Block/Tミノ(上 120,80).png"
#define TITLE_Z_MINO_PATH "Data/Block/Zミノ(120,80).png"
#define TITLE_S_MINO_PATH "Data/Block/Sミノ(120,80).png"
#define TITLE_L_MINO_PATH "Data/Block/Lミノ(120,80).png"
#define TITLE_J_MINO_PATH "Data/Block/Jミノ(120,80).png"
#define TITLE_O_MINO_PATH "Data/Block/Oミノ(80).png"
#define TITLE_I_MINO_PATH "Data/Block/Iミノ(40,160).png"


TitleInfo titleInfo;
PlayRogoInfo playrogoInfo;
TitleMino titlemino;

//タイトル初期化
void SceneTitle::Init()
{
	//タイトル処理関連
	titleInfo.TitleHndl= LoadGraph(TITLE_PATH);         //タイトル画面初期化
	titleInfo.PlaySceneFlag = false;                   //PLAYSCENEに行くためのフラグ
	titleInfo.PlaySceneStopcount = 0;                //PLAYSCENEに行くまでの秒数
	titleInfo.Titlecount = 0;                        //アクションする秒数(演出)
	//プレイロゴ関連
	playrogoInfo.PlayrogoHndl = LoadGraph(PLAY_ROGO_PATH);          //PLAYROGO初期化
	playrogoInfo.Playrogo2Hndl = LoadGraph(PLAY_ROGO2_PATH);         //PLAYROGO2初期化
	playrogoInfo.PlayrogoOffHndl= LoadGraph(PLAY_ROGO_OFF_PATH);     //PLAYROGO OFF初期化
	playrogoInfo.Playrogocount = 0;                                  //描画する秒数(Playrogo)
	//テトリミノ(描画用)関連
	titlemino.Tmino= LoadGraph(TITLE_T_MINO_PATH);          //Tミノ初期化
	titlemino.Zmino = LoadGraph(TITLE_Z_MINO_PATH);          //Zミノ初期化
	titlemino.Smino = LoadGraph(TITLE_S_MINO_PATH);          //Sミノ初期化
	titlemino.Lmino = LoadGraph(TITLE_L_MINO_PATH);          //Lミノ初期化
	titlemino.Jmino = LoadGraph(TITLE_J_MINO_PATH);          //Jミノ初期化
	titlemino.Omino = LoadGraph(TITLE_O_MINO_PATH);          //Oミノ初期化
	titlemino.Imino = LoadGraph(TITLE_I_MINO_PATH);          //Iミノ初期化
	titlemino.x[7] = { 0 };    //ミノX座標初期化
	titlemino.y[7] = { 0 };    //ミノY座標初期化
	//ミノX座標
	titlemino.x[0] = 0;
	titlemino.x[1] = 50;
	titlemino.x[2] = 100;
	titlemino.x[3] = 150;
	titlemino.x[4] = 200;
	titlemino.x[5] = 250;
	titlemino.x[6] = 300;
	//ミノY座標
	titlemino.y[0] = 0;
	titlemino.y[1] = 50;
	titlemino.y[2] = 100;
	titlemino.y[3] = 150;
	titlemino.y[4] = 200;
	titlemino.y[5] = 250;
	titlemino.y[6] = 300;

	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_TITLE;
}

//タイトル通常処理
void SceneTitle::Step()
{
	if (Input::PressAnyKey())
	{
		titleInfo.PlaySceneFlag = true;    //フラグを立てる
	}

	if (titleInfo.PlaySceneFlag == true)
	{
		titleInfo.PlaySceneStopcount++;   //カウントを増やす
		if (titleInfo.PlaySceneStopcount <= 10) {
			playrogoInfo.Playrogocount = 0;    //カウントを戻す
		}
		if (titleInfo.PlaySceneStopcount >= 100) {
			titleInfo.PlaySceneFlag = true;
			SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_TITLE;
		}
	}
}

//タイトル描画処理
void SceneTitle::Draw()
{
	//タイトル描画
	DrawGraph(0, 0, titleInfo.TitleHndl, true);
	//PLAYROGO描画
	if (playrogoInfo.Playrogocount <= 49) {
		DrawGraph(500, 550, playrogoInfo.PlayrogoHndl, true);    //一つ目を描画
	}
	if (playrogoInfo.Playrogocount >= 50) {
		DrawGraph(500, 550, playrogoInfo.Playrogo2Hndl, true);    //二つ目を描画
	}
	if (titleInfo.PlaySceneStopcount >= 1&& titleInfo.PlaySceneStopcount <= 10) {
		DrawGraph(500, 550, playrogoInfo.PlayrogoOffHndl, true);   //クリック処理描画
	}
	if (playrogoInfo.Playrogocount >= 100) {
		playrogoInfo.Playrogocount = 0;    //カウントを戻す
	}
	if (titleInfo.PlaySceneFlag == false) {
		playrogoInfo.Playrogocount++;   //カウントを増やす
	}
}

//タイトル後処理
void SceneTitle::Fin()
{
	playrogoInfo.Playrogocount = 0;
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_PLAY;
}