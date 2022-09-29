// Fill out your copyright notice in the Description page of Project Settings.


#include "MaterialExpressionSpriteAnimation.h"
#include "MaterialCompiler.h"


UMaterialExpressionSpriteAnimation::UMaterialExpressionSpriteAnimation(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}


#if WITH_EDITOR
int32 UMaterialExpressionSpriteAnimation::Compile(FMaterialCompiler* Compiler, int32 OutputIndex)
{
	if (!spriteAnimation)
	{
		return Compiler->Errorf(TEXT("no sprite Animation Asset"));
	}

	if (!spriteAnimation->GetSpriteTextureSource())
	{
		return Compiler->Errorf(TEXT("no sprite Animation Texture Source"));
	}

	//Asset으로 부터 texture 가져오기
	//Asset으로 부터 Asset 설정값 가져오기
	const int32 texSizeX = resultTexture->Source.GetSizeX();
	const int32 texSizeY = resultTexture->Source.GetSizeY();

	const int32 divX = texSizeX / spriteAnimation->GetTileX();
	const int32 divY = texSizeY / spriteAnimation->GetTileY();

	//텍스쳐를 tile size로 자르고 시간의 흐름의 따라 index를 변화한다. index를 순환하게 하여 순환 animation 구현 
	//speed = isSpeed? speed : 1.0f
	//time = Floor(Time * speed);
	//length = (texSizeX / tileSizeX) * (texSizeY / tileSizY)
	//index = time % length
	int32 speedArg = Speed.GetTracedInput().Expression ? Speed.Compile(Compiler) : Compiler->Constant(1.0f);
	int32 time = Compiler->Floor(Compiler->Mul(Compiler->GameTime(false, 0.0f), speedArg) );
	int32 length = Compiler->Constant(divX * divY);
	int32 index = Compiler->Fmod(time, length);

	// index 변화에 따른 좌표 수정을 위한 계산
	// quot = Floor (time / (texSizeX / tileSizeX))
	// remainder = time % (texSizeX / tileSizeX)
	int32 quotient = Compiler->Floor(Compiler->Div(index, Compiler->Constant(divX)));
	int32 remainder = Compiler->Fmod(index, Compiler->Constant(divX));



	//index의 위치에 맞게 텍스쳐 좌표 수정
	//arg1 = vector2( rem * 1 / (texSizeX / tileSizeX) , quotient * 1 / (texSizeY / tileSizY) )
	//tex coord += arg1; 
	int32 Arg1 = Compiler->AppendVector(Compiler->Mul(remainder, Compiler->Constant(1.0f / divX)), Compiler->Mul(quotient, Compiler->Constant(1.0f / divY)));
	int32 tcoord = Compiler->Div(Compiler->TextureCoordinate(0, false, false), Compiler->Constant2(divX, divY));
	tcoord = Compiler->Add(tcoord, Arg1) ;

	int32 TextureCodeIndex = Compiler->Texture(resultTexture, SAMPLERTYPE_Color);

	return Compiler->TextureSample(
		TextureCodeIndex,
		tcoord,
		SAMPLERTYPE_Color
	);

	}

	void UMaterialExpressionSpriteAnimation::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
	{
		resultTexture = nullptr;

		if (spriteAnimation)
		{
			resultTexture = Cast<UTexture>(spriteAnimation->GetSpriteTextureSource());
		}


		Super::PostEditChangeProperty(PropertyChangedEvent);
	}

	void UMaterialExpressionSpriteAnimation::GetCaption(TArray<FString>& OutCaptions) const
	{
		OutCaptions.Add(TEXT("Sprite Animation"));
	}

	UObject* UMaterialExpressionSpriteAnimation::GetReferencedTexture() const
	{
		return resultTexture;
	}
#endif
