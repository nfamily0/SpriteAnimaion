#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "SpriteAnimaionAssetTypeActions.h"

class FSpriteAnimationEditor: public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
private:
    TSharedPtr<FSpriteAnimationAssetTypeActions> SpriteAnimationAssetTypeActions;
};
