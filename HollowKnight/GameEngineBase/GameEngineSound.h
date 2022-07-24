#pragma once
#include "GameEngineNameObject.h"
#include "ThirdParty/inc/fmod.hpp"
#include "GameEngineFile.h"
#include <map>

class GameEngineSoundHollowKnight;
// 설명 :
class GameEngineSound : public GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineSound();
	~GameEngineSound();

	// delete Function
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

protected:
	bool Load(const std::string& _Path);


private:
	FMOD::Sound* Sound;

	///////////////////////////////////////// 매니지먼트 사운드 기능
public:
	// 그냥 사운드 재생1회 절대로 멈추거나 이런건 못합니다.
	static GameEngineSoundHollowKnight SoundPlayControl(const std::string& _Name, unsigned int LoopCount = 0);

	static void SoundPlayOneShot(const std::string& _Name, int LoopCount = 0);
	static void Update();

/// <summary>
/// ///////////////////////////////////// 리소스 매니지먼트
/// </summary>
public:
	static GameEngineSound* FindRessource(const std::string& _Name);
	static GameEngineSound* LoadRessource(const GameEngineFile& _Path);
	static GameEngineSound* LoadRessource(const std::string& _Path);
	static GameEngineSound* LoadRessource(const std::string& _Path, const std::string& _Name);

	static void AllResourcesDestroy();

private:
	static std::map<std::string, GameEngineSound*> AllRes;

};

// 사운드 재생을 제어할수 있는 기능들을 넣을겁니다.
class GameEngineSound;
class GameEngineSoundHollowKnight 
{
	friend GameEngineSound;

public:
	void Stop();
	void PlaySpeed(float _Speed);
	void Volume(float _Value);

	GameEngineSoundHollowKnight(const GameEngineSoundHollowKnight& _Other);

private:
	GameEngineSound* Sound_;
	FMOD::Channel* ControlHandle_;


	GameEngineSoundHollowKnight(GameEngineSound* Sound, FMOD::Channel* ControlHandle);

public:
	GameEngineSoundHollowKnight();
	~GameEngineSoundHollowKnight();
};