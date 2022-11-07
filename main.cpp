#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"

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
    
#pragma endregion 基盤システムの初期化

#pragma region 最初のシーンを初期化
    
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
#pragma endregion 最初のシーンの更新

        //描画前処理
        dxCommon->PreDraw();

#pragma region 最初のシーンの描画
#pragma endregion 最初のシーンの描画

        //描画後処理
        dxCommon->PostDraw();

    }
#pragma region 最初のシーンの終了
#pragma endregion 最初のシーンの終了

#pragma region 基盤システムの終了
    //入力解放
    delete input;
    //DirectX解放
    delete dxCommon;
    //WindowsAPIの終了処理
    winApp->Finalize();
    //WindowsAPI解放
    delete winApp;
#pragma endregion 基盤システムの終了

    return 0;
}
