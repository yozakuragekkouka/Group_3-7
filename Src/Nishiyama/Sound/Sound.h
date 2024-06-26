#pragma once
#include "../../Common.h"

//BGMíÞñ^
enum BGM_KIND
{
	BGM_NONE = -1,
	BGM_A,
	BGM_PLAY,

	BGM_NUM
};

//SEíÞñ^
enum SE_KIND
{
	SE_NONE = -1,
	SE_A,
	SE_FirstRogo,
	SE_Rogo,
	SE_MIGRATIONMINO,
	SE_REVOLUTION_MINO,
	SE_ESTABLISHMENT_MINO,
	SE_ENTER_MINO,

	SE_NUM
};

//BGMf[^NX
class BGM_Data
{
private:
	int BGMHandle;
	int VolumePal;

public:
	BGM_Data();
	~BGM_Data();

	void SetVol(int Volume) { VolumePal = Volume; };

	void BGMInit(BGM_KIND kind);

	void FinBGM();
};

//SEf[^NX
class SE_Data
{
private:
	int SEHandle;
	
public:
	SE_Data();
	~SE_Data();

	void LoadSE(SE_KIND kind);

	void SetVolume(int VolumePal) { ChangeVolumeSoundMem(VolumePal, SEHandle); }

	void PlaySE();

	void FinSE();
};

class SoundEffect
{
private:
	static SE_Data SE[SE_NUM];

public:
	static void Init();
	static void Play(SE_KIND kind);
	static void Fin();
};
