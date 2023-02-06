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

    Quaternion q1 = { 2.0f,3.0f,4.0f,1.0f };
    Quaternion q2 = { 1.0f,3.0f,5.0f,2.0f };
    Quaternion identity = Identity();
    Quaternion conj = Conjugate(q1);
    Quaternion inv = Inverse(q1);
    Quaternion normal = Normalize(q1);
    Quaternion mul1 = q1 * q2;
    Quaternion mul2 = q2 * q1;
    float norm = Norm(q1);

    sprite->Update();

    object3d_1->Update();
    object3d_2->Update();
    object3d_3->Update();

    imGui->Begin();

    //ImGui::ShowDemoWindow();
    ImGui::Text("%.2f,%.2f,%.2f,%.2f", conj.x, conj.y, conj.z, conj.w);
    ImGui::Text("%.2f,%.2f,%.2f,%.2f", inv.x, inv.y, inv.z, inv.w);
    ImGui::Text("%.2f,%.2f,%.2f,%.2f", normal.x, normal.y, normal.z, normal.w);
    ImGui::Text("%.2f,%.2f,%.2f,%.2f", mul1.x, mul1.y, mul1.z, mul1.w);
    ImGui::Text("%.2f,%.2f,%.2f,%.2f", mul2.x, mul2.y, mul2.z, mul2.w);
    ImGui::Text("%.2f", norm);

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
