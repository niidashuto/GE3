#include "GamePlayScene.h"
#include "SpriteCommon.h"
#include "Object3d.h"
#include "ParticleManager.h"
#include "DirectXCommon.h"
#include "Audio.h"

void GamePlayScene::Initialize()
{
    ////spriteCommon->LoadTexture(0, "texture.png");
    ////spriteCommon->LoadTexture(1, "reimu.png");

    //SpriteCommon::GetInstance()->LoadTexture(1, "white1x1.png");

    //SpriteCommon::GetInstance()->LoadTexture(0, "background.png");

    //ParticleManager::StaticInitialize(DirectXCommon::GetInstance()->GetDevice());

    ////音声読み込み
    //Audio::GetInstance()->SoundLoadWave("Resources/fanfare.wav");
    ////音声再生
    ////audio->SoundPlayWave("Resources/fanfare.wav");
}

void GamePlayScene::Finalize()
{
}

void GamePlayScene::Update()
{
}

void GamePlayScene::Draw()
{
}
