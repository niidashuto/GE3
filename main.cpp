﻿#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include"Object3d.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

#pragma region 基盤システムの初期化

    WinApp* winApp = nullptr;
    //WindowsAPIの初期化
    winApp = new WinApp();
    winApp->Initialize();

    DirectXCommon* dxCommon = nullptr;
    //DirectXの初期化
    dxCommon = new DirectXCommon();
    dxCommon->Initialize(winApp);
    
    Input* input = nullptr;
    //入力の初期化
    input = new Input();
    input->Initialize(winApp);

    SpriteCommon* spriteCommon = nullptr;
    //スプライト共通部の初期化
    spriteCommon = new SpriteCommon();
    spriteCommon->Initialize(dxCommon);
    spriteCommon->LoadTexture(0, "texture.png");
    spriteCommon->LoadTexture(1, "reimu.png");

    Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
    
#pragma endregion 基盤システムの初期化

#pragma region 最初のシーンを初期化
    Sprite* sprite = nullptr;
    sprite = new Sprite();
    sprite->SetTextureIndex(0);
    sprite->Initialize(spriteCommon,0);
    Object3d* object3d = Object3d::Create();
#pragma endregion 最初のシーンを初期化
    
    // ゲームループ
    while (true) {

#pragma region 基盤システムの更新
       
        //Windowsのメッセージ処理
        if (winApp->ProcessMessage()) {
            //ゲームループを抜ける
            break;
        }

        input->Update();
#pragma endregion 基盤システムの更新

#pragma region 最初のシーンの更新
        
        sprite->Update();
        object3d->Update();

#pragma endregion 最初のシーンの更新

        //描画前処理
        dxCommon->PreDraw();

#pragma region 最初のシーンの描画
        spriteCommon->PreDraw();
        sprite->Draw();
        spriteCommon->PostDraw();
        Object3d::PreDraw(dxCommon->GetCommandList());
        object3d->Draw();
        Object3d::PostDraw();

#pragma endregion 最初のシーンの描画

        //描画後処理
        dxCommon->PostDraw();

    }
#pragma region 最初のシーンの終了
    delete sprite;
#pragma endregion 最初のシーンの終了

#pragma region 基盤システムの終了
    //スプライト共通部解放
    delete spriteCommon;
    //入力解放
    delete input;
    //DirectX解放
    delete dxCommon;

    delete object3d;
    //WindowsAPIの終了処理
    winApp->Finalize();
    //WindowsAPI解放
    delete winApp;
#pragma endregion 基盤システムの終了

    return 0;
}
