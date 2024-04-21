#include "DxLib.h"     //2309405 �F��˒g�I
#include "../../Common.h"
#include "Scene.h"
#include "SceneTitle.h"
#include "../Input/Input.h"
#include "../Sound/Sound.h"

#define TITLE_PATH "Data/Title/�^�C�g��.png"    //�w�i
#define TITLE_ROGO_PATH "Data/Title/building block.png"    //�^�C�g�����S
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

#define SCOAE_PATH "Data/Result/�Q�[���I�[�o�[�t�H���g.png"    //�X�R�A����

TitleInfo titleInfo;
PlayRogoInfo playrogoInfo;
TitleMino titlemino;

SE_KIND FirstRogoSE = SE_KIND::SE_FirstRogo;   //�^�C�g�����S�ŏ� SE
SE_KIND RogoSE = SE_KIND::SE_Rogo;             //�^�C�g�����S�o�ꎞ SE
SE_KIND ENTERSE = SE_KIND::SE_ENTER_MINO;     //����{�^��
SoundEffect SEe;

//�^�C�g��������
void SceneTitle::Init()
{
	//�^�C�g�������֘A
	titleInfo.TitleHndl= LoadGraph(TITLE_PATH);         //�^�C�g����ʏ�����
	titleInfo.TitleRogoHndl = LoadGraph(TITLE_ROGO_PATH);  //�^�C�g�����S������
	titleInfo.TitleRogox = 400;
	titleInfo.TitleRogoy = 100;
	titleInfo.alphaNum = 0;
	titleInfo.PlaySceneFlag = false;                   //PLAYSCENE�ɍs�����߂̃t���O
	titleInfo.PlaySceneStopcount = 0;                //PLAYSCENE�ɍs���܂ł̕b��
	titleInfo.Titlecount = 0;                        //�A�N�V��������b��(���o)

	titleInfo.scoae= LoadGraph(SCOAE_PATH);
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
	titlemino.alphaNum[7] = { 0 };   //�����x
	//�~�mX���W
	titlemino.x[0] = 920;
	titlemino.x[1] = 200;
	titlemino.x[2] = 350;
	titlemino.x[3] = 1150;
	titlemino.x[4] = 200;
	titlemino.x[5] = 120;
	titlemino.x[6] = 1030;
	//�~�mY���W
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

//�^�C�g���ʏ폈��
void SceneTitle::Step()
{
	titleInfo.Titlecount++;   //�J�E���g�𑝂₷

	if (Input::PressAnyKey())     //�����ꂽ��
	{
		titleInfo.PlaySceneFlag = true;    //�t���O�𗧂Ă�
	}

	if (titleInfo.PlaySceneFlag == true)   //�t���O��������
	{
		titleInfo.PlaySceneStopcount++;   //�J�E���g�𑝂₷
		if (titleInfo.PlaySceneStopcount == 1) {
			SEe.Play(ENTERSE);      //SE����
		}
		if (titleInfo.PlaySceneStopcount <= 10) {
			playrogoInfo.Playrogocount = 0;    //�J�E���g��߂�
		}
		if (titleInfo.PlaySceneStopcount >= 90) {
			SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_FIN_TITLE;  //FIN��
		}
	}
	//SE����
	if (titleInfo.Titlecount == 10) {
		SEe.Play(FirstRogoSE);          //�^�C�g�����S�ŏ� SE����
	}
	if (titleInfo.TitleRogoy == 250) {
		SEe.Play(RogoSE);               //�^�C�g�����S�o�ꎞ SE����
	}

}

//�^�C�g���`�揈��
void SceneTitle::Draw()
{
	//�^�C�g���w�i�`��
	DrawGraph(0, 0, titleInfo.TitleHndl, true);
	//�^�C�g�����S�ړ�����
	if (titleInfo.TitleRogoy <= 250) {
		titleInfo.TitleRogoy++;
	}
	//�^�C�g�����S�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, titleInfo.alphaNum);
	DrawGraph(titleInfo.TitleRogox, titleInfo.TitleRogoy, titleInfo.TitleRogoHndl, true); //�`��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	titleInfo.alphaNum++;
	titleInfo.alphaNum++;
	titleInfo.alphaNum++;   //�^�C�g�����S�����x��3���₷
	//�^�C�g���p�e�g���~�m�`��
	if (titleInfo.Titlecount >= 150) {
		for (int i = 0; i < 7; i++) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, titlemino.alphaNum[i]);
			DrawRotaGraph(titlemino.x[0], titlemino.y[0], 1, -0.1, titlemino.Tmino, true);   //T�~�m
			DrawRotaGraph(titlemino.x[1], titlemino.y[1], 1, 0.5, titlemino.Zmino, true);    //Z�~�m
			DrawRotaGraph(titlemino.x[2], titlemino.y[2], 1, 0, titlemino.Smino, true);      //S�~�m
			DrawRotaGraph(titlemino.x[3], titlemino.y[3], 1, -0.1, titlemino.Lmino, true);   //L�~�m
			DrawRotaGraph(titlemino.x[4], titlemino.y[4], 1, -0.1, titlemino.Jmino, true);   //J�~�m
			DrawRotaGraph(titlemino.x[5], titlemino.y[5], 1, 0.8, titlemino.Omino, true);    //O�~�m
			DrawRotaGraph(titlemino.x[6], titlemino.y[6], 1, 18, titlemino.Imino, true);     //I�~�m
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			titlemino.alphaNum[i]++;
			titlemino.alphaNum[i]++;
			titlemino.alphaNum[i]++;    //�����x�J�E���g��3���₷
		}
	}
	//PLAYROGO�`��
	if (playrogoInfo.Playrogocount <= 49) {
		DrawGraph(520, 550, playrogoInfo.PlayrogoHndl, true);    //��ڂ�`��
	}
	if (playrogoInfo.Playrogocount >= 50) {
		DrawGraph(520, 550, playrogoInfo.Playrogo2Hndl, true);    //��ڂ�`��
	}
	if (titleInfo.PlaySceneStopcount >= 1&& titleInfo.PlaySceneStopcount <= 10) {
		DrawGraph(520, 550, playrogoInfo.PlayrogoOffHndl, true);   //�N���b�N�����`��
	}
	if (playrogoInfo.Playrogocount >= 100) {
		playrogoInfo.Playrogocount = 0;    //�J�E���g��߂�
	}
	if (titleInfo.PlaySceneFlag == false) {
		playrogoInfo.Playrogocount++;   //�J�E���g�𑝂₷
	}

	DrawGraph(340, 90, titleInfo.scoae, true);

}

//�^�C�g���㏈��
void SceneTitle::Fin()
{
	titleInfo.alphaNum = 0;
	titlemino.alphaNum[7] = { 0 };
	titleInfo.TitleRogoy = 100;
	titleInfo.Titlecount = 0;
	titleInfo.PlaySceneFlag = false;
	playrogoInfo.Playrogocount = 0;
	//SE�j��
	SEe.Fin();


	SceneManager::g_CurrenySceneID = SCENEID::SCENE_ID_INIT_PLAY;
}