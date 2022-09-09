#include "PreCompile.h"

#include "ShopItem.h"

ShopItem::ShopItem() 
{
}

ShopItem::~ShopItem() 
{
}

void ShopItem::Start()
{
}

void ShopItem::Update(float _DeltaTime)
{
}

void ShopItem::CreateShopItem(SHOP_ITEM _Item)
{
	switch (_Item)
	{
	case SHOP_ITEM::Crosslaod_Map:


		ItemRenderer_ = CreateComponent<GameEngineUIRenderer>();
		ItemRenderer_->SetTexture("Area_map.png");
		ItemRenderer_->GetTransform().SetLocalScale(ItemRenderer_->GetCurTexture()->GetScale()*0.6f);

		GeoRenderer_ = CreateComponent<GameEngineUIRenderer>();
		GeoRenderer_->SetTexture("Item_Geo.png");
		GeoRenderer_->GetTransform().SetLocalScale({35,35});

		PriceRenderer_ = GetLevel()->CreateActor<ContentsFontRenderer>();
		PriceRenderer_->CreateFontRenderer("200", 
			28, 
			{ 0,0 }, 
			false,
			false, 
			4);

		ItemRenderer_->GetTransform().SetLocalPosition({ -55,0,0 });
		GeoRenderer_->GetTransform().SetLocalPosition({ 25,0,0 });
		PriceRenderer_->GetTransform().SetLocalPosition({50,0});
		PriceRenderer_->SetScreenMove();
		PriceRenderer_->GetFontRenderer()->SetTopAndBotSort(TopAndBotSort::VCENTER);
		//PriceRenderer_->GetFontRenderer()->SetLeftAndRightSort(LeftAndRightSort::CENTER);
		ShopItemState_.ItemName_ = "잊혀진 교차로";
		ShopItemState_.ItemInfo_ = "흙의 마을 바로 아래에 있는 지역인 잊혀진 교차로의 지도. 코니퍼가 한 번 나를 거기 아래로 끌고간 적이 있어요. 그곳은 공허하고 외로운 장소였지만 여전히 인상적이었어요.";

		break;
	case SHOP_ITEM::Wayward_Compass:


		ItemRenderer_ = CreateComponent<GameEngineUIRenderer>();
		ItemRenderer_->SetTexture("Charm_0.png");
		ItemRenderer_->GetTransform().SetLocalScale(ItemRenderer_->GetCurTexture()->GetScale() * 0.5f);

		GeoRenderer_ = CreateComponent<GameEngineUIRenderer>();
		GeoRenderer_->SetTexture("Item_Geo.png");
		GeoRenderer_->GetTransform().SetLocalScale({ 35,35 });

		PriceRenderer_ = GetLevel()->CreateActor<ContentsFontRenderer>();
		PriceRenderer_->CreateFontRenderer("200",
			28,
			{ 0,0 },
			false,
			false, 4);
		ItemRenderer_->GetTransform().SetLocalPosition({ -55,0,0 });
		GeoRenderer_->GetTransform().SetLocalPosition({ 25,0,0 });
		PriceRenderer_->GetTransform().SetLocalPosition({ 50,0 });
		PriceRenderer_->SetScreenMove();
		PriceRenderer_->GetFontRenderer()->SetTopAndBotSort(TopAndBotSort::VCENTER);

		ShopItemState_.ItemName_ = "변덕스런 나침반";
		ShopItemState_.ItemInfo_ = "적극 추천해요! 우리 아래의 폐허의 미로에서 길을 찾는데 어려움을 느낀다면 이 부적을 써 보세요.";


		break;
	case SHOP_ITEM::Mark_of_Pride:

		ItemRenderer_ = CreateComponent<GameEngineUIRenderer>();
		ItemRenderer_->SetTexture("Area_map.png");
		ItemRenderer_->GetTransform().SetLocalScale(ItemRenderer_->GetCurTexture()->GetScale() * 0.6f);

		GeoRenderer_ = CreateComponent<GameEngineUIRenderer>();
		GeoRenderer_->SetTexture("Item_Geo.png");
		GeoRenderer_->GetTransform().SetLocalScale({ 35,35 });

		PriceRenderer_ = GetLevel()->CreateActor<ContentsFontRenderer>();
		PriceRenderer_->CreateFontRenderer("200",
			28,
			{ 0,0 },
			false,
			false, 4);

		ItemRenderer_->GetTransform().SetLocalPosition({ -55,0,0 });
		GeoRenderer_->GetTransform().SetLocalPosition({ 25,0,0 });
		PriceRenderer_->GetTransform().SetLocalPosition({ 50,0 });
		PriceRenderer_->SetScreenMove();
		PriceRenderer_->GetFontRenderer()->SetTopAndBotSort(TopAndBotSort::VCENTER);

		ShopItemState_.ItemName_ = "잊혀진 교차로";
		ShopItemState_.ItemInfo_ = "흙의 마을 바로 아래에 있는 지역인 잊혀진 교차로의 지도. 코니퍼가 한 번 나를 거기 아래로 끌고간 적이 있어요. 그곳은 공허하고 외로운 장소였지만 여전히 인상적이었어요.";

		break;
	case SHOP_ITEM::Dreamshield:

		ItemRenderer_ = CreateComponent<GameEngineUIRenderer>();
		ItemRenderer_->SetTexture("Charm_38.png");
		ItemRenderer_->GetTransform().SetLocalScale(ItemRenderer_->GetCurTexture()->GetScale() * 0.5f);

		GeoRenderer_ = CreateComponent<GameEngineUIRenderer>();
		GeoRenderer_->SetTexture("Item_Geo.png");
		GeoRenderer_->GetTransform().SetLocalScale({ 35,35 });

		PriceRenderer_ = GetLevel()->CreateActor<ContentsFontRenderer>();
		PriceRenderer_->CreateFontRenderer("240",
			28,
			{ 0,0 },
			false,
			false, 4);

		ItemRenderer_->GetTransform().SetLocalPosition({ -55,0,0 });
		GeoRenderer_->GetTransform().SetLocalPosition({ 25,0,0 });
		PriceRenderer_->GetTransform().SetLocalPosition({ 50,0 });
		PriceRenderer_->SetScreenMove();
		PriceRenderer_->GetFontRenderer()->SetTopAndBotSort(TopAndBotSort::VCENTER);

		ShopItemState_.ItemName_ = "몽환 방패";
		ShopItemState_.ItemInfo_ = "꿈을 형상화할 수 있는 부족이 사용하던 방어용 부적이래요.";

		break;

	case SHOP_ITEM::MaskPiece:

		ItemRenderer_ = CreateComponent<GameEngineUIRenderer>();
		ItemRenderer_->SetTexture("Heart_Piece_01.png");

		ItemRenderer_->GetTransform().SetLocalScale(ItemRenderer_->GetCurTexture()->GetScale() * 0.6f);

		GeoRenderer_ = CreateComponent<GameEngineUIRenderer>();
		GeoRenderer_->SetTexture("Item_Geo.png");
		GeoRenderer_->GetTransform().SetLocalScale({ 35,35 });

		PriceRenderer_ = GetLevel()->CreateActor<ContentsFontRenderer>();
		PriceRenderer_->CreateFontRenderer("300",
			28,
			{ 0,0 },
			false,
			false, 4);

		ItemRenderer_->GetTransform().SetLocalPosition({ -55,0,0 });
		GeoRenderer_->GetTransform().SetLocalPosition({ 25,0,0 });
		PriceRenderer_->GetTransform().SetLocalPosition({ 50,0 });
		PriceRenderer_->SetScreenMove();
		PriceRenderer_->GetFontRenderer()->SetTopAndBotSort(TopAndBotSort::VCENTER);

		ShopItemState_.ItemName_ = "가면 조각";
		ShopItemState_.ItemInfo_ = "이 낡은 물건이요? 그냥 어떤 것의 파편이에요. 그래도 어쩌면 당신에게 유용할지도요?";

		break;
	default:
		break;
	}

	PriceRenderer_->SetParent(this);
}

void ShopItem::SetFontRendererMove()
{
	PriceRenderer_->GetTransform().SetWorldPosition({ PriceRenderer_->GetTransform().GetWorldPosition().x, this->GetTransform().GetWorldPosition().y });
	PriceRenderer_->SetScreenMove();

}

