#pragma once
enum class BlendMode
{
	Alpha,
	Overlay,
	Lighten,
	Multply,
	Add,
	Addition,
	Darken,
	MAX
};

enum class UPDATE_ORDER
{
	NORMAL,
	CAMERA
};


enum class COLLISION_ORDER
{
	Background,
	Background_Object,
	Terrain,
	NPC,
	Potal,
	//Elderbug,
	Knight,
	Prompt,
	Object,
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
	UI_Pointer,

	UI_Border,

	UI,
	
	UI_BackBoard,

	TileMap,

	FrontObject,

	Terrain,

	Effect,
	Knight_Shadow_Slash,



	Knight_Shadow,

	Knight_Slash,

	Geo,

	Knight,
	Monster,

	NPC,

	Object,

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
	Inventory,
	Map,
};

// 페이지 인덱스 : 현재 페이지를 0으로 세팅한다.
// 만약 내가 +1 이었다가 0으로 된다면 오른쪽으로 이동된다.
// 만약 내가 -1 이었다가 0으로 된다면 왼족으로 이동된다.
enum class CURRENT_PAGE_INDEX
{
	MIN = -2,
	SincePage = -1,
	CurrentPage = 0,
	NextPage = 1,
	MAX = 2
};

enum class CHAR_PAGE_ACTOR
{
	RightArrow = 50,
	LeftArrow = 51,
};

enum class MAP_PAGE_ACTOR
{
	RightArrow = 50,
	LeftArrow = 51,
};

enum class MONSTER_BOOK_PAGE_ACTOR
{
	RightArrow = 1,
	LeftArrow,
};

enum class MAP_LIST
{
	MAP_MIN = -1,
	DIRTMOUTH,
	CORSSROAD,
	MAP_MAX
};

enum class ITEM_LIST
{
	NONE = -2,
	SPELL_MIN = -1,
	Heart_Piece = 0,
	Soul_Piece,
	Dream_Nail,
	Nail,
	Spell_core,
	Spell_Fireball,
	Spell_Scream,
	Item_Geo,
	SPELL_MAX = 8,

	NORMAL_MIN = 9,

	Tram_Pass = 10,
	Lumafly_Lantern,
	Mapand_Quill,
	Collectors_Map,
	Hunters_Journal,
	Hunters_Mark,
	Delicate_Flower,
	Godtuner,
	Mask_Shard,
	Vessel_Fragment,
	Salubras_Blessing,
	Pale_Ore,

	NORMAL_MAX,


	Map_and_Quill,
	Rancid_Egg,
	Shade_Cloak,
	Witches_eye,
	Storeroom_key,
	Quill_combined,
	Monarch_Wings,
	Mender_key, 
	Acid_armour,
	Crystal_heart, 
	Rancid_egg,
	Area_map, 
	Treasure_map, 
	Mantis_Cloak,

	SELL_MIN = 39,
	Wanderers_Journal = 40,
	hallownest_seal,
	Kings_idol,
	arcane_egg,
	SELL_MAX = 44,
};


enum class ITEM_TYPE
{
	Spell_Item,
	Normal_Item,
	Sell_Item
};

enum class SHOP_ITEM
{
	Crosslaod_Map,
	Rancid_Egg,


	MaskPiece,		// 가면조각
	Wayward_Compass, //나침반
	Mark_of_Pride,	//사마귀
	Dreamshield,	//몽환방패
};

enum class SlideItemIndex
{
	Min = -1,
	First,
	Second,
	Third,
	Fourth,
	Fifth,
	Sixth
};

enum class NPC_TYPE
{
	Normal,
	Shop
};

enum class CHARM_SLOT
{
	None = -1 ,
	Wayward_Compass, // 슬롯 1, 변덕스런납침반, 지도가 열릴 때마다 착용자에게 위치를 속삭여 방랑자가 자신의 현재 위치를 정확히 파악할 수 있게 합니다. 흙의 마을, 이셀다가 220지오에 판매
	Gathering_Swarm, //슬롯 1, 수집벌레무리, 무리가 착용자를 따라다니며, 놓친 지오를 가져옵니다. 아무리 사소한 것이라도 남기는 것을 견디지 못하는 이들에게 유용합니다. 흙의 마을, 슬라이가 300지오에 판매
	Stalwart_Shell, // 슬롯 2, 튼튼한 껍데기, 주술자들이 주위 세계로부터 더 많은 영혼을 끌어내기 위해 사용합니다. 대못으로 적을 공격할 때 얻는 영혼의 양을 증가시킵니다. 잊혀진 교차로 - 선조의 흙더미
	Soul_Catcher, // / 슬롯 2, 영혼 포식자, 아직 살아있는 생명체로부터 영혼을 끌어내는 데 사용되던 잊혀진 주술사의 유물. 대못으로 적을 공격할 때 얻는 영혼의 양을 크게 증가시킵니다. 안식의 땅
	Shaman_Stone, // 슬롯 3, 주술사의 돌, 주술사의 과거 세대 지식을 담고 있다고 합니다. 주문의 힘을 증가시켜 적에게 더 많은 피해를 가합니다. 잊혀진 교차로, 살루브라가 220지오에 판매
	Soul_Eater, // / 슬롯 4, 영혼 포식자, 아직 살아있는 생명체로부터 영혼을 끌어내는 데 사용되던 잊혀진 주술사의 유물. 대못으로 적을 공격할 때 얻는 영혼의 양을 크게 증가시킵니다. 안식의 땅
	Dashmaster, // 슬롯 4, '대시마스터'라고만 알려진 괴상한 곤충의 모습을 하고 있습니다.착용자는 더 자주 대시를 할뿐만 아니라 아래로도 대시를 할 수 있습니다.최대한 빨리 주변을 돌아다니고 싶어하는 이들에게 이상적입니다.버섯 황무지
	Thorns_of_Agony, // 슬롯 2,  고통의 가시 덩굴, 착용자의 고통을 감지하면 주변을 채찍질 합니다. 피해를 받으면 주변의 적들에게 피해를 입히는 가시가 많은 덩굴이 자라납니다. 녹색 거리
	Fury_of_the_Fallen, // 슬롯 2, 전사자의 분노, 죽을 이들에 대한 분노와 영웅심을 상징합니다. 죽음에 가까워졌을 때 착용자의 힘이 증가합니다. 왕의 길
	Fragile_Heart, // 슬롯 2, 허술한 심장. 착용자의 체력을 증가시켜 더 많은 피해를 견딜 수 있게 합니다. 이 부적은 약해서 착용자가 죽으면 깨집니다. 버섯 황무지, 다리를 먹는 자가 350지오에 판매
	Fragile_Greed, // 슬롯 2, 착용자가 적을 물리치면 더 많은 지오를 가져다줍니다. 이 부적은 약해서 착용자가 죽으면 깨집니, 버섯 황무지, 다리를 먹는 자가 250지오에 판매.
	Fragile_Strength, // 슬롯 3, 착용자를 강하게 하고, 대못으로 적에게 입히는 손상을 증가시킵니다. 이 부적은 약해서 착용자가 죽으면 깨집니다. 버섯 황무지, 다리를 먹는 자가 600지오에 판매
	Spell_Twister, // 슬롯 2, 주문 회오리, 주문을 부리는 데 필요한 영혼 비용을 줄입니다. 눈물의 도시 - 영혼 성소
	Steady_Body, // 슬롯 1, 대못으로 적을 공격할 때 착용자가 뒤로 몸이 밀리지 않게 합니다. 안정적인 상태로 계속 공격을 할 수 있게 합니다. 잊혀진 교차로, 살루브라가 120지오에 판매
	Heavy_Blow, // 슬롯2, 죽은 전사의 대못으로 만들어졌습니다. 착용자의 대못의 힘을 증가시켜 적이 공격을 받았을 때 더 멀리 밀려나게 합니다. 흙의 마을, 상점 열쇠를 되찾아주면 슬라이가 350지오에 판매
	Quick_Slash, // 슬롯3, 함께 용해된 불완전하고 버려진 대못으로부터 태어났습니다. 대못은 여전히 휘둘러지기를 갈망합니다. 착용자는 대못으로 훨씬 더 빠르게 벨 수 있습니다.왕국의 끝자락
	Longnail, // 슬롯2, 착용자의 대못 범위를 증가시켜 멀리서 적을 공격할 수 있게 합니다. 잊혀진 교차로, 살루브라가 300지오에 판매
	Mark_of_Pride, // 슬롯3, 사마귀 부족이 자신들이 존경하는 이에게 줍니다. 착용자의 대못 범위를 크게 증가시켜 멀리서 적을 공격할 수 있게 합니다. 버섯 황무지 - 사마귀 마을 - 사마귀 군주들 처치[6]
	Baldur_Shell, // 슬롯 2, 영혼을 집중하면서 딱딱한 껍데기로 착용자를 보호합니다. 껍데기는 무적이 아니며 너무 많은 손상을 흡수하면 산산이 부서집니다.
	Flukenest, // 슬롯3, 흡충 어미의 내장에서 태어난 살아있는 부적. 복수의 영령 주문을 변덕스러운 아기 흡충 무리로 바꿉니다.
	Defenders_Crest, // 슬롯1 , 신성둥지의 왕이 가장 충성스러운 기사에게 수여한 독특한 부적. 긁히고 더러워졌지만 여전히 사랑받습니다. 착용자가 영웅적 냄새를 방출하게 합니다.
	Glowing_Womb, // 슬롯 2 , 착용자의 영혼을 빼내 유충을 탄생시키는 데 사용합니다. 유충은 먹거나 살려는 의지가 없으며, 부모를 보호하기 위해 자신을 희생합니다., 잊혀진 교차로
	Quick_Focus, // 슬롯3 , 수정 렌즈를 포함하고 있는 부적. 영혼 집중의 속도를 증가시켜 착용자가 피해를 더 빨리 치유할 수 있게 합니다.잊혀진 교차로, 살루브라가 800지오에 판매
	Deep_Focus, // 슬롯4 , 오랜 기간에 걸쳐 수정 안에 자연적으로 형성된 부적. 주변 공기로부터 영혼을 끌어냅니다. 착용자는 더 느린 속도로 영혼을 집중하지만, 치유 효과는 두 배가 됩니다. 수정 봉우리
	Lifeblood_Heart, // 슬롯2, 귀중한 생명혈을 스며 나오게 하는 살아있는 핵을 담고 있습니다. 휴식을 할 때 착용자는 경미한 손상으로부터 보호하는 생명혈로 코팅됩니다. 잊혀진 교차로, 살루브라가 250지오에 판매
	Lifeblood_Core, // 슬롯3, 귀중한 생명혈을 흘리는 살아있는 핵을 담고 있습니다. 휴식을 할 때 착용자는 많은 손상으로부터 보호하는 생명혈로 코팅됩니다. 고대의 분지 - 심연
	Jonis_Blessing, // 슬롯4, 친절한 이교도인 조니의 축복. 생체 유체를 파란 생명혈로 변화시킵니다. 착용자는 더 건강한 껍데기를 가지고 더 많은 손상을 견딜 수 있지만, 영혼을 집중하여 스스로를 치유할 수는 없습니다. 	울부짖는 벼랑
	Grubsong, // 슬롯 1, 해방된 애벌레의 감사를 담고 있습니다. 피해를 입을 때 영혼을 얻습니다. 잊혀진 교차로, 10 애벌레 구출 보상 
	Grubberflys_Elegy, // 슬롯3, 애벌나비의 애가, 삶의 다음 단계로 넘어선 애벌레의 감사를 담고 있습니다. 무기에 신성한 힘을 가득 채웁니다. 착용자의 체력이 가득할 때 대못으로부터 하얀 뜨거운 에너지를 발사합니다.잊혀진 교차로, 모든 애벌레 구출 보상
	Hiveblood, // 슬롯 4, 벌집의 꿀이 굳어 형성된 귀중한 황금색 덩어리. 시간이 지남에 따라 착용자의 상처를 치유하여 영혼을 집중하지 않고 체력을 되찾을 수 있게 합니다. 벌집 - 벌집 기사 처치
	Spore_Shroom, // 슬롯1, 	살아있는 곰팡이 물질로 구성되어 있습니다.영혼에 노출되면 포자를 뿌립니다.영혼을 집중할 때 지속적으로 적에게 피해를 입히는 포자를 방출합니다. , 버섯 황무지
	Sharp_Shadow, // 슬롯2, 그림자를 치명적인 무기로 바꾸는 금지된 주문을 담고 있습니다. 그림자 대시를 사용할 때 착용자의 몸이 날카로워지고 적에게 피해를 입힙니다.깊은 둥지
	Shape_of_Unn, // 슬롯2, 착용자 내에서 우운의 형상을 드러냅니다. 영혼을 집중하는 동안 착용자는 새로운 형태를 취하며, 적을 피하기 위해 자유롭게 움직일 수 있습니다.
	Nailmasters_Glory, // 슬롯1, 대못사부의 열정, 기술, 후회가 담겨 있습니다. 착용자의 대못 기술 숙달도를 증가시켜 자신의 힘을 더 빨리 집중하고 기술을 더 빨리 발휘할 수 있게 합니다.
	Dream_Wielder, // 슬롯1, 몽환의 대못을 휘두르고 정수를 수집하는 이들을 위해 만들어진 부적. 착용자가 몽환의 대못을 더 빨리 충전하고 적을 공격할 때 더 많은 영혼을 수집할 수 있게 합니다., 안식의 땅, 안식의 땅, 정수 500을 모은 후 예언자에게서
	Kingsoul, // 슬롯 5, 천천히 영혼을 회복한다. 출생지로 들어가는 길을 열 수 있게 된다. 여왕의 정원, 배신자 군주 처치 후 백의 여사로부터 반쪽, 백색 궁전 마지막 지점에서 반쪽
	//Void_Heart, // 슬롯  '그림자'에게 피해를 받지 않게 된다. 이 부적은 착용을 해제할 수 없다. 심연 - 출생지
	Sprintmaster, // 슬롯 1 , 질주마스터라고만 알려진 이상한 곤충의 모습을 하고 있는 부적. 착용자의 이동속도를 증가시켜서 위협을 피하거나 경쟁자를 추월할 수 있게 도와줍니다. 흙의 마을, 슬라이가 400지오에 판매
	Weaversong, // 슬롯 2, 자신의 고향으로 돌아간 엮는 이들의 작별 노래를 담고있는 비단으로 짜여진 부적. 외로운 착용자에게 친구와 수호자가 되어줄 존재를 소환합니다. 깊은 둥지 - 엮는 이의 소굴
	Dreamshield, // 슬롯 3, 꿈을 형상화할 수 있는 부족이 사용하던 방어용 부적. 착용자를 따라다니며 지켜주는 방패를 생성합니다. 안식의 땅
	Grimmchild, // 슬롯 2, 그림 극단의 의식에 참여한 이들이 지니는 부적. 착용자는 그림의 동족들을 찾아내서 불꽃을 수집해야 합니다. 수집하지 못한 불꽃이 착용자의 지도에 표시됩니다.
	//Carefree_Melody // 슬롯 3, 새로운 우정을 기념하는 상징. 착용자를 피해로부터 지켜줄 수 있는 보호의 노래를 담고 있습니다., 흙의 마을

};