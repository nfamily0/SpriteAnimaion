// Fill out your copyright notice in the Description page of Project Settings.


#include "SpriteAnimationFactory.h"
#include "SpriteAnimation.h"

USpriteAnimationFactory::USpriteAnimationFactory()
{
	SupportedClass = USpriteAnimation::StaticClass();
	bCreateNew = true;
}

UObject* USpriteAnimationFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<USpriteAnimation>(InParent, Class, Name, Flags, Context);
}