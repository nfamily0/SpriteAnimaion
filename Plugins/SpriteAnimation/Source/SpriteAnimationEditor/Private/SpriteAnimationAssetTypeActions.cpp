#include "SpriteAnimaionAssetTypeActions.h"
#include "SpriteAnimation.h"

UClass* FSpriteAnimationAssetTypeActions::GetSupportedClass() const
{
	return USpriteAnimation::StaticClass();
}

FText FSpriteAnimationAssetTypeActions::GetName() const
{
	return INVTEXT("Sprite Animation");
}

FColor FSpriteAnimationAssetTypeActions::GetTypeColor() const
{
	return FColor::Cyan;
}

uint32 FSpriteAnimationAssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}