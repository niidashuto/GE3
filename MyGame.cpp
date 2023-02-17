#include "MyGame.h"
#include "Quaternion.h"

void MyGame::Initialize()
{
#pragma region 基盤システムの初期化


    SNFramework::Initialize();

    spriteCommon->LoadTexture(0, "texture.png");
    spriteCommon->LoadTexture(1, "reimu.png");

    Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);

    //音声読み込み
    audio->SoundLoadWave("Resources/fanfare.wav");
    //音声再生
    //audio->SoundPlayWave("Resources/fanfare.wav");

#pragma endregion 基盤システムの初期化

#pragma region 最初のシーンを初期化

    
    imGui = new ImGuiManager();
    imGui->Initialize(winApp, dxCommon);

    
    sprite = new Sprite();
    sprite->SetTextureIndex(0);
    sprite->Initialize(spriteCommon, 0);

    model_1 = Model::LoadFromOBJ("ground");
    model_2 = Model::LoadFromOBJ("triangle_mat");

    object3d_1 = Object3d::Create();
    object3d_2 = Object3d::Create();
    object3d_3 = Object3d::Create();
    
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
}

void MyGame::Finalize()
{
#pragma region 最初のシーンの終了
    delete sprite;
    imGui->Finalize();
    delete imGui;

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

    
    SNFramework::Finalize();
    delete audio;
    //WindowsAPI解放
    delete winApp;
#pragma endregion 基盤システムの終了
}

void MyGame::Update()
{
#pragma region 基盤システムの更新
    SNFramework::Update();
#pragma endregion 基盤システムの更新

#pragma region 最初のシーンの更新

    Quaternion rotation0 = MakeAxisAngle({ 0.71f,0.71f,0.0f }, 0.3f);
    Quaternion rotation1 = { -rotation0.x,-rotation0.y,-rotation0.z,-rotation0.w };

    Quaternion interpolate0 = Slerp(rotation0, rotation1, 0.0f);
    Quaternion interpolate1 = Slerp(rotation0, rotation1, 0.3f);
    Quaternion interpolate2 = Slerp(rotation0, rotation1, 0.5f);
    Quaternion interpolate3 = Slerp(rotation0, rotation1, 0.7f);
    Quaternion interpolate4 = Slerp(rotation0, rotation1, 1.0f);


    sprite->Update();

    object3d_1->Update();
    object3d_2->Update();
    object3d_3->Update();

    imGui->Begin();

    //ImGui::ShowDemoWindow();
    ImGui::Text("%.2f,%.2f,%.2f,%.2f", interpolate0.x, interpolate0.y, interpolate0.z, interpolate0.w);
    ImGui::Text("%.2f,%.2f,%.2f,%.2f", interpolate1.x, interpolate1.y, interpolate1.z, interpolate1.w);
    ImGui::Text("%.2f,%.2f,%.2f,%.2f", interpolate2.x, interpolate2.y, interpolate2.z, interpolate2.w);
   

    imGui->End();


#pragma endregion 最初のシーンの更新
}

void MyGame::Draw()
{
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

    imGui->Draw();
#pragma endregion 最初のシーンの描画

    //描画後処理
    dxCommon->PostDraw();
}
