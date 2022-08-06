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
	Monster,
	FrontObject,
};

enum class RENDERORDER
{
	Background,
	Background_Object,
	Terrain,

	Knight,
	Monster,

	FrontObject,

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

