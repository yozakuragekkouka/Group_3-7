#include "DxLib.h"     //2309405 宇賀塚暖紀
#include "../../Common.h"
#include "Scene.h"
#include "SceneTitle.h"
#include "../Input/Input.h"
#include "../Sound/Sound.h"

#define TITLE_PATH "Data/Title/タイトル.png"    //背景
#define TITLE_ROGO_PATH "Data/Title/building block.png"    //タイトルロゴ
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

#define SCOAE_PATH "Data/Result/ゲームオーバーフォント.png"    //スコア文字

TitleInfo titleInfo;
PlayRogoInfo playrogoInfo;
TitleMino titlemino;

SE_KIND FirstRogoSE = SE_KIND::SE_FirstRogo;   //タイトルロゴ最初 SE
SE_KIND RogoSE = SE_KIND::SE_Rogo;             //タイトルロゴ登場時 SE
SE_KIND ENTERSE = SE_KIND::SE_ENTER_MINO;     //決定ボタン
SoundEffect SEe;

//タイトル初期化
void SceneTitle::Init()
{
	//タイトル処理関連
	titleInfo.TitleHndl= LoadGraph(TITLE_PATH);         //タイトル画面初期化
	titleInfo.TitleRogoHndl = LoadGraph(TITLE_ROGO_PATH);  //タイトルロゴ初期化
	titleInfo.TitleRogox = 400;
	titleInfo.TitleRogoy = 100;
	titleInfo.alphaNum = 0;
	titleInfo.PlaySceneFlag = false;                   //PLAYSCENEに行くためのフラグ
	titleInfo.PlaySceneStopcount = 0;                //PLAYSCENEに行くまでの秒数
	titleInfo.Titlecount = 0;                        //アクションする秒数(演出)

	titleInfo.scoae= LoadGraph(SCOAE_PATH);
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
	titlemino.alphaNum[7] = { 0 };   //透明度
	//ミノX座標
	titlemino.x[0] = 920;
	titlemino.x[1] = 200;
	titlemino.x[2] = 350;
	titlemino.x[3] = 1150;
	titlemino.x[4] = 200;
	titlemino.x[5] = 120;
	titlemino.x[6] = 1030;
	//ミノY座標
	titlemino.y[0] = 50;
	titlemino.y[1] = 40;
	titlemino.y[2] = 620;
	titlemino.y[3] = 280;
	titlemino.y[4] = 370;
	titlemino.y[5] = 200;
	titlemino.y[6] = 640;

	SEe.Init();
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_TITLE;
}

//タイトル通常処理
void SceneTitle::Step()
{
	titleInfo.Titlecount++;   //カウントを増やす

	if (Input::PressAnyKey())     //押されたら
	{
		titleInfo.PlaySceneFlag = true;    //フラグを立てる
	}

	if (titleInfo.PlaySceneFlag == true)   //フラグが立った
	{
		titleInfo.PlaySceneStopcount++;   //カウントを増やす
		if (titleInfo.PlaySceneStopcount == 1) {
			SEe.Play(ENTERSE);      //SE処理
		}
		if (titleInfo.PlaySceneStopcount <= 10) {
			playrogoInfo.Playrogocount = 0;    //カウントを戻す
		}
		if (titleInfo.PlaySceneStopcount >= 90) {
			SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_TITLE;  //FINへ
		}
	}
	//SE処理
	if (titleInfo.Titlecount == 10) {
		SEe.Play(FirstRogoSE);          //タイトルロゴ最初 SE処理
	}
	if (titleInfo.TitleRogoy == 250) {
		SEe.Play(RogoSE);               //タイトルロゴ登場時 SE処理
	}

}

//タイトル描画処理
void SceneTitle::Draw()
{
	//タイトル背景描画
	DrawGraph(0, 0, titleInfo.TitleHndl, true);
	//タイトルロゴ移動処理
	if (titleInfo.TitleRogoy <= 250) {
		titleInfo.TitleRogoy++;
	}
	//タイトルロゴ描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, titleInfo.alphaNum);
	DrawGraph(titleInfo.TitleRogox, titleInfo.TitleRogoy, titleInfo.TitleRogoHndl, true); //描画
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	titleInfo.alphaNum++;
	titleInfo.alphaNum++;
	titleInfo.alphaNum++;   //タイトルロゴ透明度を3増やす
	//タイトル用テトリミノ描画
	if (titleInfo.Titlecount >= 150) {
		for (int i = 0; i < 7; i++) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, titlemino.alphaNum[i]);
			DrawRotaGraph(titlemino.x[0], titlemino.y[0], 1, -0.1, titlemino.Tmino, true);   //Tミノ
			DrawRotaGraph(titlemino.x[1], titlemino.y[1], 1, 0.5, titlemino.Zmino, true);    //Zミノ
			DrawRotaGraph(titlemino.x[2], titlemino.y[2], 1, 0, titlemino.Smino, true);      //Sミノ
			DrawRotaGraph(titlemino.x[3], titlemino.y[3], 1, -0.1, titlemino.Lmino, true);   //Lミノ
			DrawRotaGraph(titlemino.x[4], titlemino.y[4], 1, -0.1, titlemino.Jmino, true);   //Jミノ
			DrawRotaGraph(titlemino.x[5], titlemino.y[5], 1, 0.8, titlemino.Omino, true);    //Oミノ
			DrawRotaGraph(titlemino.x[6], titlemino.y[6], 1, 18, titlemino.Imino, true);     //Iミノ
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			titlemino.alphaNum[i]++;
			titlemino.alphaNum[i]++;
			titlemino.alphaNum[i]++;    //透明度カウントを3増やす
		}
	}
	//PLAYROGO描画
	if (playrogoInfo.Playrogocount <= 49) {
		DrawGraph(520, 550, playrogoInfo.PlayrogoHndl, true);    //一つ目を描画
	}
	if (playrogoInfo.Playrogocount >= 50) {
		DrawGraph(520, 550, playrogoInfo.Playrogo2Hndl, true);    //二つ目を描画
	}
	if (titleInfo.PlaySceneStopcount >= 1&& titleInfo.PlaySceneStopcount <= 10) {
		DrawGraph(520, 550, playrogoInfo.PlayrogoOffHndl, true);   //クリック処理描画
	}
	if (playrogoInfo.Playrogocount >= 100) {
		playrogoInfo.Playrogocount = 0;    //カウントを戻す
	}
	if (titleInfo.PlaySceneFlag == false) {
		playrogoInfo.Playrogocount++;   //カウントを増やす
	}

	DrawGraph(340, 90, titleInfo.scoae, true);

}

//タイトル後処理
void SceneTitle::Fin()
{
	titleInfo.alphaNum = 0;
	titlemino.alphaNum[7] = { 0 };
	titleInfo.TitleRogoy = 100;
	titleInfo.Titlecount = 0;
	titleInfo.PlaySceneFlag = false;
	playrogoInfo.Playrogocount = 0;
	//SE破棄
	SEe.Fin();


	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_PLAY;
}