// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialExpression.h"
#include "SpriteAnimation.h"
#include "MaterialExpressionSpriteAnimation.generated.h"

/**
 * 
 */
UCLASS()
class SPRITEANIMATION_API UMaterialExpressionSpriteAnimation : public UMaterialExpression
{
	GENERATED_UCLASS_BODY()

		//Indirect Texture�� �������� �޾ƿ��� ������
	UPROPERTY(EditAnywhere, Category = MaterialExpressionSpriteAnimation)
	USpriteAnimation* spriteAnimation;

	//Indirect Texture�� ������� �����ϴ� ������
	UPROPERTY(VisibleDefaultsOnly, Category = MaterialExpressionSpriteAnimation)
	UTexture* resultTexture;

	UPROPERTY(meta = (RequiredInput = "false", ToolTip = "Vector2 speed scale, if specified"))
	FExpressionInput Speed;


#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

#if WITH_EDITOR
	virtual int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;
	virtual void GetCaption(TArray<FString>& OutCaptions) const override;
#endif
	virtual UObject* GetReferencedTexture() const override;
	virtual bool CanReferenceTexture() const override { return true; }
private:

};
