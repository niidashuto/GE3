#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include"Object3d.h"
#include"Model.h"

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
    //OBJからモデルデータを読み込む
    Model* model_1 = Model::LoadFromOBJ("ground");
    Model* model_2 = Model::LoadFromOBJ("triangle_mat");
    //3Dオブジェクト生成
    Object3d* object3d_1 = Object3d::Create();
    Object3d* object3d_2 = Object3d::Create();
    Object3d* object3d_3 = Object3d::Create();
    //3Dオブジェクトと3Dモデルをひも付け
    object3d_1->SetModel(model_1);
    object3d_2->SetModel(model_2);
    object3d_3->SetModel(model_2);
    //3Dオブジェクトの位置を指定
    object3d_2->SetPosition({ -5,0,-5 });
    object3d_3->SetPosition({ +5,0,+5 });
    //3Dオブジェクトのスケールを指定
    object3d_1->SetPosition({ 0,-50,0 });
    object3d_1->SetScale({ 10.0f,10.0f,10.0f });
    object3d_2->SetScale({ 10.0f,10.0f,10.0f });
    object3d_3->SetScale({ 10.0f,10.0f,10.0f });
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

        object3d_1->Update();
        object3d_2->Update();
        object3d_3->Update();

#pragma endregion 最初のシーンの更新

        //描画前処理
        dxCommon->PreDraw();

#pragma region 最初のシーンの描画
        spriteCommon->PreDraw();
        sprite->Draw();
        spriteCommon->PostDraw();
        Object3d::PreDraw(dxCommon->GetCommandList());
        object3d_1->Draw();
        object3d_2->Draw();
        object3d_3->Draw();
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

    delete object3d_1;
    delete object3d_2;
    delete object3d_3;

    delete model_1;
    delete model_2;
    //WindowsAPIの終了処理
    winApp->Finalize();
    //WindowsAPI解放
    delete winApp;
#pragma endregion 基盤システムの終了

    return 0;
}