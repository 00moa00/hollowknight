#pragma once
#include "Knight.h"
#include "Monster.h"

enum class OBJECTORDER
{
	Background,
	Background_Object,
	Terrain,
	Knight,
	FrontObject,
	Monster,
};

enum class RENDERORDER
{
	Background,
	Background_Object,
	Terrain,
	Knight,
	FrontObject,
	Monster,
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

