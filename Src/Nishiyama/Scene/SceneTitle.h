#pragma once
#include "Scene.h"

//�V�[�����
class SceneTitle : public SceneBase
{
private:

public:
	void Init();

	void Step();

	void Draw();

	void Fin();
};

//�^�C�g���\����
struct TitleInfo
{
	int TitleHndl;                //�^�C�g�����
	bool PlaySceneFlag;           //PLAYSCENE�ɍs�����߂̃t���O
	int PlaySceneStopcount;       //PLAYSCENE�ɍs���܂ł̕b��
	int Titlecount;               //�A�N�V��������b��(���o)
};

//�^�C�g���\����
struct PlayRogoInfo
{
	int PlayrogoHndl;             //PLAYROGO
	int Playrogo2Hndl;            //PLAYROGO2
	int PlayrogoOffHndl;          //PLAYROGO OFF
	int Playrogocount;            //�`�悷��b��(Playrogo)
};

//�^�C�g���~�m�\����
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
};