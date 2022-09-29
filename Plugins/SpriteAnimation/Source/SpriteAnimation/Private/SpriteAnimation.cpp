// Fill out your copyright notice in the Description page of Project Settings.


#include "SpriteAnimation.h"

USpriteAnimation::USpriteAnimation()
	:tileX(32), tileY(32)
{
	
}


void USpriteAnimation::SplitTexture()
{

	if(SpriteTextureSource == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("SpriteTextureSource is null"));
		return;
	}

	const int32 texSizeX = SpriteTextureSource->PlatformData->Mips[0].SizeX;
	const int32 texSizeY = SpriteTextureSource->PlatformData->Mips[0].SizeY;

	if(tileX == 0 || tileY == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("zero division tileX : %f, tileY : %f"), tileX, tileY);
		return;
	}

	if(texSizeX == 0 || texSizeY == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SpriteTextureSource sizeX : %f, sizeY : %f"), texSizeX, texSizeY);
		return;
	}

	const int32 divX = texSizeX / tileX;
	const int32 divY = texSizeY / tileY;

	const int32 tileNumber = divX * divY;

	spriteArray.Reserve(tileNumber);
	for(int i = 0; i < tileNumber; ++i)
	{
		UTexture2D* sprite = UTexture2D::CreateTransient(tileX, tileY, PF_R8G8B8A8);
		spriteArray.Add(sprite);
	}

	const TextureCompressionSettings OldCompressionSettings = SpriteTextureSource->CompressionSettings;
	const TextureMipGenSettings OldMipGenSettings = SpriteTextureSource->MipGenSettings;
	const bool OldSRGB = SpriteTextureSource->SRGB;

	SpriteTextureSource->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
	SpriteTextureSource->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
	SpriteTextureSource->SRGB = false;
	SpriteTextureSource->UpdateResource();

	const FColor* textureColorArray = static_cast<FColor*>(SpriteTextureSource->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

	uint8* spriteData = new uint8[tileX * tileY * 4];

	//원본 Texture를 조각 내어서 2차원 배열 tileset에 저장
	for (int32 i = 0; i < tileNumber; ++i)
	{
		for (int32 y = 0; y < tileY; ++y)
		{
			for (int32 x = 0; x < tileX * 4; x += 4)
			{
				const int32 startIndex = (i % divX) * tileX + (i / divX) * texSizeX * tileY;
				const FColor color = textureColorArray[startIndex + x / 4 + y * texSizeX];

				spriteData[x + y * tileX * 4 + 0] = color.R;
				spriteData[x + y * tileX * 4 + 1] = color.G;
				spriteData[x + y * tileX * 4 + 2] = color.B;
				spriteData[x + y * tileX * 4 + 3] = 255;

			}
		}

		void* spriteColorArray = spriteArray[i]->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);

		FMemory::Memcpy(spriteColorArray, spriteData, sizeof(uint8) * tileX * tileY * 4);

		spriteArray[i]->PlatformData->Mips[0].BulkData.Unlock();
		spriteArray[i]->UpdateResource();
	}

	delete spriteData;

	SpriteTextureSource->PlatformData->Mips[0].BulkData.Unlock();
	SpriteTextureSource->CompressionSettings = OldCompressionSettings;
	SpriteTextureSource->MipGenSettings = OldMipGenSettings;
	SpriteTextureSource->SRGB = OldSRGB;
	SpriteTextureSource->UpdateResource();
}
