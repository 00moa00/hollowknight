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
	UI,

	TileMap,

	FrontObject,

	Terrain,

	Monster,

	Knight_Shadow_Slash,

	Knight_Shadow,

	Knight_Slash,

	Geo,

	Small_Light,

	Light,

	Dount_Light,

	Side_Dark,
	Knight,



	Background_Object ,

	Background = 200,


};