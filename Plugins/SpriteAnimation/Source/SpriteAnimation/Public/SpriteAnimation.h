// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpriteAnimation.generated.h"

/**
 * 
 */
UCLASS()
class SPRITEANIMATION_API USpriteAnimation : public UObject
{
	GENERATED_BODY()
public:
	USpriteAnimation();

	UPROPERTY(EditAnywhere ,Category="SpriteAnimation")
	UTexture2D* SpriteTextureSource;

	UPROPERTY(VisibleDefaultsOnly, Category="SpriteAnimation")
	TArray<UTexture2D*> spriteArray;

	UPROPERTY(EditAnywhere, Category = "SpriteAnimation")
	int32 tileX;

	UPROPERTY(EditAnywhere, Category = "SpriteAnimation")
	int32 tileY;

	UFUNCTION(CallInEditor, Category = "SpriteAnimation")
	void SplitTexture();

	UFUNCTION(Category = "SpriteAnimation")
	TArray<UTexture2D*>& GetSpriteArray() { return spriteArray; }

	UFUNCTION(Category = "SpriteAnimation")
	UTexture2D* GetSpriteTextureSource() const { return SpriteTextureSource; } 

	UFUNCTION(Category = "SpriteAnimation")
	int32 GetTileX() const { return tileX; };

	UFUNCTION(Category = "SpriteAnimation")
	int32 GetTileY() const { return tileY; };

};
