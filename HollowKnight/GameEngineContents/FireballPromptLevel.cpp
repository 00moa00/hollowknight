#include "PreCompile.h"
#include "FireballPromptLevel.h"
#include "SpellFireballInfo.h"

FireballPromptLevel::FireballPromptLevel() 


{
}

FireballPromptLevel::~FireballPromptLevel() 
{

}

void FireballPromptLevel::Start()
{
	CreateActor<SpellFireballInfo>();

}

void FireballPromptLevel::Update(float _DeltaTime)
{

}

void FireballPromptLevel::End() 
{

}

void FireballPromptLevel::LevelStartEvent() 
{

}

void FireballPromptLevel::LevelEndEvent()
{

}

