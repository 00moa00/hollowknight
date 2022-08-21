#pragma once

enum class OBJECTORDER
{
	Background,
	Background_Object,
	Terrain,
	Knight,
	Geo,
	Knight_Slash,
	Knight_Shadow,
	Knight_Shadow_Slash,
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
	Knight_Shadow,
	FrontObject,
	UI

};

//역순으로. 숫자가 높을 수록 뒤로간다
enum class Z_ORDER
{
	UI_Border,

	UI,

	TileMap,

	FrontObject,

	Terrain,

	Monster,

	Knight_Shadow_Slash,

	Knight_Shadow,

	Knight_Slash,

	Geo,

	Knight,

	Small_Light,

	Light,

	Dount_Light,

	Side_Dark,



	Background_Object ,

	Background = 200,


};

//액터 포인터
//0은 대기 상태? 상황에 따라 바귈 수 있음.

enum class PAGE_TYPE
{
	Charm,
	MonsterBook,
	Map
};

enum class CHAR_PAGE_ACTOR
{
	RightArrow = 1,
	LeftArrow,
};


enum class MONSTER_BOOK_PAGE_ACTOR
{
	RightArrow = 1,
	LeftArrow,
};


enum class MAP_PAGE_ACTOR
{
	RightArrow = 1,
	LeftArrow,
};