// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "SpriteAnimationFactory.generated.h"

/**
 * 
 */
UCLASS()
class SPRITEANIMATIONEDITOR_API USpriteAnimationFactory : public UFactory
{
	GENERATED_BODY()

public:
	USpriteAnimationFactory();

	UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
