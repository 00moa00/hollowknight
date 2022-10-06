#include "PreCompile.h"
#include "ScreamPromptLevel.h"
#include "SpellScreamInfo.h"

ScreamPromptLevel::ScreamPromptLevel() 
{
}

ScreamPromptLevel::~ScreamPromptLevel() 
{
}

void ScreamPromptLevel::Start()
{
	CreateActor<SpellScreamInfo>();

}

void ScreamPromptLevel::Update(float _DeltaTime)
{
}

void ScreamPromptLevel::End()
{
}

void ScreamPromptLevel::LevelStartEvent()
{
}

void ScreamPromptLevel::LevelEndEvent()
{
}
