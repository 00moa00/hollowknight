#pragma once
#include "Knight.h"
#include "Monster.h"

enum class OBJECTORDER
{
	Background,
	Background_Object,
	Terrain,
	Knight,
	Knight_Slash,
	Knight_Shadow,
	Monster,
	FrontObject,
	TileMap,
	UI
};

enum class RENDERORDER
{
	Background,
	Background_Object,
	Terrain,

	Knight,
	Monster,

	FrontObject,
	UI

};


// Ό³Έν :
class GlobalContentsValue
{
public:
	class Enums 
	{
	};

	class Actors 
	{
	public:
		static Monster* TestMonster;

	private:
		Actors() {		}
		~Actors() {		}
	};

private:
	GlobalContentsValue()	{	}

	~GlobalContentsValue()	{	}
};

