#include "DxLib.h"
#include "../../Common.h"
#include "Scene.h"
//2309405 �F��˒g�I

#include "SceneTitle.h"
#include "../Input/Input.h"

#define TITLE_PATH "Data/Title/�^�C�g��.png"
//�v���C���S
#define PLAY_ROGO_PATH "Data/Title/PLAY1.png"
#define PLAY_ROGO2_PATH "Data/Title/PLAY2.png"
#define PLAY_ROGO_OFF_PATH "Data/Title/PLAY OFF.png"
//�e�g���~�m
#define TITLE_T_MINO_PATH "Data/Block/T�~�m(�� 120,80).png"
#define TITLE_Z_MINO_PATH "Data/Block/Z�~�m(120,80).png"
#define TITLE_S_MINO_PATH "Data/Block/S�~�m(120,80).png"
#define TITLE_L_MINO_PATH "Data/Block/L�~�m(120,80).png"
#define TITLE_J_MINO_PATH "Data/Block/J�~�m(120,80).png"
#define TITLE_O_MINO_PATH "Data/Block/O�~�m(80).png"
#define TITLE_I_MINO_PATH "Data/Block/I�~�m(40,160).png"


TitleInfo titleInfo;
PlayRogoInfo playrogoInfo;
TitleMino titlemino;

//�^�C�g��������
void SceneTitle::Init()
{
	//�^�C�g�������֘A
	titleInfo.TitleHndl= LoadGraph(TITLE_PATH);         //�^�C�g����ʏ�����
	titleInfo.PlaySceneFlag = false;                   //PLAYSCENE�ɍs�����߂̃t���O
	titleInfo.PlaySceneStopcount = 0;                //PLAYSCENE�ɍs���܂ł̕b��
	titleInfo.Titlecount = 0;                        //�A�N�V��������b��(���o)
	//�v���C���S�֘A
	playrogoInfo.PlayrogoHndl = LoadGraph(PLAY_ROGO_PATH);          //PLAYROGO������
	playrogoInfo.Playrogo2Hndl = LoadGraph(PLAY_ROGO2_PATH);         //PLAYROGO2������
	playrogoInfo.PlayrogoOffHndl= LoadGraph(PLAY_ROGO_OFF_PATH);     //PLAYROGO OFF������
	playrogoInfo.Playrogocount = 0;                                  //�`�悷��b��(Playrogo)
	//�e�g���~�m(�`��p)�֘A
	titlemino.Tmino= LoadGraph(TITLE_T_MINO_PATH);          //T�~�m������
	titlemino.Zmino = LoadGraph(TITLE_Z_MINO_PATH);          //Z�~�m������
	titlemino.Smino = LoadGraph(TITLE_S_MINO_PATH);          //S�~�m������
	titlemino.Lmino = LoadGraph(TITLE_L_MINO_PATH);          //L�~�m������
	titlemino.Jmino = LoadGraph(TITLE_J_MINO_PATH);          //J�~�m������
	titlemino.Omino = LoadGraph(TITLE_O_MINO_PATH);          //O�~�m������
	titlemino.Imino = LoadGraph(TITLE_I_MINO_PATH);          //I�~�m������
	titlemino.x[7] = { 0 };    //�~�mX���W������
	titlemino.y[7] = { 0 };    //�~�mY���W������
	//�~�mX���W
	titlemino.x[0] = 0;
	titlemino.x[1] = 50;
	titlemino.x[2] = 100;
	titlemino.x[3] = 150;
	titlemino.x[4] = 200;
	titlemino.x[5] = 250;
	titlemino.x[6] = 300;
	//�~�mY���W
	titlemino.y[0] = 0;
	titlemino.y[1] = 50;
	titlemino.y[2] = 100;
	titlemino.y[3] = 150;
	titlemino.y[4] = 200;
	titlemino.y[5] = 250;
	titlemino.y[6] = 300;

	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_LOOP_TITLE;
}

//�^�C�g���ʏ폈��
void SceneTitle::Step()
{
	if (Input::PressAnyKey())
	{
		titleInfo.PlaySceneFlag = true;    //�t���O�𗧂Ă�
	}

	if (titleInfo.PlaySceneFlag == true)
	{
		titleInfo.PlaySceneStopcount++;   //�J�E���g�𑝂₷
		if (titleInfo.PlaySceneStopcount <= 10) {
			playrogoInfo.Playrogocount = 0;    //�J�E���g��߂�
		}
		if (titleInfo.PlaySceneStopcount >= 100) {
			titleInfo.PlaySceneFlag = true;
			SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_TITLE;
		}
	}
}

//�^�C�g���`�揈��
void SceneTitle::Draw()
{
	//�^�C�g���`��
	DrawGraph(0, 0, titleInfo.TitleHndl, true);
	//PLAYROGO�`��
	if (playrogoInfo.Playrogocount <= 49) {
		DrawGraph(500, 550, playrogoInfo.PlayrogoHndl, true);    //��ڂ�`��
	}
	if (playrogoInfo.Playrogocount >= 50) {
		DrawGraph(500, 550, playrogoInfo.Playrogo2Hndl, true);    //��ڂ�`��
	}
	if (titleInfo.PlaySceneStopcount >= 1&& titleInfo.PlaySceneStopcount <= 10) {
		DrawGraph(500, 550, playrogoInfo.PlayrogoOffHndl, true);   //�N���b�N�����`��
	}
	if (playrogoInfo.Playrogocount >= 100) {
		playrogoInfo.Playrogocount = 0;    //�J�E���g��߂�
	}
	if (titleInfo.PlaySceneFlag == false) {
		playrogoInfo.Playrogocount++;   //�J�E���g�𑝂₷
	}
}

//�^�C�g���㏈��
void SceneTitle::Fin()
{
	playrogoInfo.Playrogocount = 0;
	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_PLAY;
}