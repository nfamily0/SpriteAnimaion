#include "SpriteAnimationEditorModule.h"

#define LOCTEXT_NAMESPACE "FSpriteAnimationEditorModule"

void FSpriteAnimationEditor::StartupModule()
{
    SpriteAnimationAssetTypeActions = MakeShared<FSpriteAnimationAssetTypeActions>();
    FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(SpriteAnimationAssetTypeActions.ToSharedRef());
}

void FSpriteAnimationEditor::ShutdownModule()
{
    if (!FModuleManager::Get().IsModuleLoaded("AssetTools")) return;
    FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(SpriteAnimationAssetTypeActions.ToSharedRef());
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FSpriteAnimationEditor, SpriteAnimationEditor)