#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include"Object3d.h"
#include"Model.h"
#include "ImGuiManager.h"
#include "imgui/imgui.h"

int scene = 0;

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
    spriteCommon->LoadTexture(0, "title.png");
    spriteCommon->LoadTexture(1, "gameover.png");

    Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);

    
    
#pragma endregion 基盤システムの初期化

#pragma region 最初のシーンを初期化

    ImGuiManager* imGui = nullptr;
    imGui = new ImGuiManager();
    imGui->Initialize(winApp,dxCommon);

    Sprite* sprite = nullptr;
    sprite = new Sprite();
    sprite->SetTextureIndex(0);
    sprite->Initialize(spriteCommon,0);

    Sprite* sprite2 = nullptr;
    sprite2 = new Sprite();
    sprite2->SetTextureIndex(0);
    sprite2->Initialize(spriteCommon, 1);
    //OBJからモデルデータを読み込む
    Model* model_1 = Model::LoadFromOBJ("ground");
    Model* model_2 = Model::LoadFromOBJ("box");
    Model* model_3 = Model::LoadFromOBJ("enemy");
    Model* model_4 = Model::LoadFromOBJ("skydome");
    //3Dオブジェクト生成
    Object3d* object3d_1 = Object3d::Create();
    Object3d* object3d_2 = Object3d::Create();
    Object3d* object3d_3 = Object3d::Create();
    Object3d* object3d_4 = Object3d::Create();
    //3Dオブジェクトと3Dモデルをひも付け
    object3d_1->SetModel(model_1);
    object3d_2->SetModel(model_2);
    object3d_3->SetModel(model_3);
    object3d_4->SetModel(model_4);
    //3Dオブジェクトの位置を指定
    object3d_2->SetPosition({ -5,0,-10 });
    object3d_3->SetPosition({ +5,0,+50 });
    //3Dオブジェクトのスケールを指定
    object3d_1->SetPosition({ 0,-20,0 });
    object3d_1->SetScale({ 10.0f,10.0f,10.0f });
    object3d_2->SetScale({ 3.0f,3.0f,3.0f });
    object3d_3->SetScale({ 3.0f,3.0f,3.0f });
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

        XMFLOAT3 playerPositon;

        XMFLOAT3 positon;

        if (scene == 0)
        {
            sprite->Update();
        }

        if (scene == 2)
        {
            sprite2->Update();
        }

        if (scene == 1)
        {
            //敵の移動
            {
                positon = object3d_3->GetPosition();
                //positon.x = 0;
                //positon.y = 0;
                positon.z -= 0.2f;
                object3d_3->SetPosition(positon);
                object3d_3->SetPosition(positon);
            }

            //プレイヤー操作
            {
                playerPositon = object3d_2->GetPosition();
                if (input->Pushkey(DIK_W)) { playerPositon.y += 0.2f; object3d_2->SetPosition(playerPositon); }
                else if (input->Pushkey(DIK_S)) { playerPositon.y -= 0.2f; object3d_2->SetPosition(playerPositon); }

                if (input->Pushkey(DIK_A)) { playerPositon.x -= 0.2f; object3d_2->SetPosition(playerPositon); }
                else if (input->Pushkey(DIK_D)) { playerPositon.x += 0.2f; object3d_2->SetPosition(playerPositon); }
            }
        }
        
        

        if (scene == 1)
        {
            object3d_1->Update();
            object3d_2->Update();
            object3d_3->Update();
            object3d_4->Update();

            imGui->Begin();
            //ImGui::ShowDemoWindow();


            imGui->End();
        }

        switch (scene)
        {
        case 0:
            
            if (input->TriggerKey(DIK_SPACE))
            {
                object3d_2->SetPosition({ -5,0,-10 });
                object3d_3->SetPosition({ +5,0,+50 });
                scene += 1;
            }
            break;
        case 1:
            if (playerPositon.x-positon.x<=-1.0f&&playerPositon.x>=-2.0f||playerPositon.x-positon.x>=-1.0f&&playerPositon.x<=11.0f)
            {
                if (playerPositon.y - positon.y <= -1.0f && playerPositon.y >= -2.0f || playerPositon.y - positon.y >= -1.0f && playerPositon.y <= 6.0f)
                {
                    if (playerPositon.z-positon.z<=1.0f&&positon.z<=-0.1f)
                    {
                        scene += 1;
                    }
                }
            }
            if (input->TriggerKey(DIK_SPACE))
            {
                scene += 1;
            }

            break;
        case 2:
            if (input->TriggerKey(DIK_SPACE))
            {
                scene = 0;
            }
            break;
        }
        

#pragma endregion 最初のシーンの更新



        //描画前処理
        dxCommon->PreDraw();

#pragma region 最初のシーンの描画
        spriteCommon->PreDraw();
        if (scene == 0)
        {
            sprite->Draw();
        }
        if (scene == 2)
        {
            sprite2->Draw();
        }
        spriteCommon->PostDraw();
        Object3d::PreDraw(dxCommon->GetCommandList());
        if (scene == 1)
        {
            object3d_1->Draw();
            object3d_2->Draw();
            object3d_3->Draw();
            object3d_4->Draw();
        }
        Object3d::PostDraw();

        //imGui->Draw();
#pragma endregion 最初のシーンの描画

        //描画後処理
        dxCommon->PostDraw();

    }
#pragma region 最初のシーンの終了
    delete sprite;
    delete sprite2;
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
    delete object3d_4;

    delete model_1;
    delete model_2;
    delete model_3;
    delete model_4;
    
    //WindowsAPIの終了処理
    winApp->Finalize();
    //WindowsAPI解放
    delete winApp;
#pragma endregion 基盤システムの終了

    return 0;
}