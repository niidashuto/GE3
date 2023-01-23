#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Model.h"
#include "ImGuiManager.h"
#include "imgui/imgui.h"
#include <xaudio2.h>
#include <fstream>
#include <wrl.h>


#pragma comment(lib,"xaudio2.lib")

//チャンクヘッダ
struct ChunkHeader
{
    char id[4];//チャンクごとのID
    int32_t size;//チャンクサイズ
};
//RIFFヘッダチャンク
struct RiffHeader
{
    ChunkHeader chunk;//"RIFF"
    char type[4];//"WAVE"
};
//FMTチャンク
struct FormatChunk
{
    ChunkHeader chunk;//"fmt"
    WAVEFORMATEX fmt;//波形フォーマット
};
//音声データ
struct SoundData
{
    //波形フォーマット
    WAVEFORMATEX wfex;
    //バッファの先頭アドレス
    BYTE* pBuffer;
    //バッファのサイズ
    unsigned int bufferSize;
};

SoundData SoundLoadWave(const char* filename)
{
    HRESULT result;
    //ファイル入力ストリームのインスタンス
    std::ifstream file;
    //.wavファイルをバイナリモードで開く
    file.open(filename, std::ios_base::binary);
    //ファイルオープン失敗を検出する
    assert(file.is_open());

    //RIFFヘッダー読み込み
    RiffHeader riff;
    file.read((char*)&riff, sizeof(riff));
    //ファイルがRIFFかチェック
    if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
        assert(0);
    }
    //タイプがWAVEかチェック
    if (strncmp(riff.type, "WAVE", 4) != 0) {
        assert(0);
    }
    //Formatチャンクの読み込み
    FormatChunk format = {};
    //チャンクヘッダーの確認
    file.read((char*)&format, sizeof(ChunkHeader));
    if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
        assert(0);
    }
    //チャンク本体の読み込み
    assert(format.chunk.size <= sizeof(format.fmt));
    file.read((char*)&format.fmt, format.chunk.size);

    //Dataチャンクの読み込み
    ChunkHeader data;
    file.read((char*)&data, sizeof(data));
    //JUNKチャンクを検出した場合
    if (strncmp(data.id, "JUNK", 4) == 0) {
        //読み取り位置をJUNKチャンクの終わりまで進める
        file.seekg(data.size, std::ios_base::cur);
        //再読み込み
        file.read((char*)&data, sizeof(data));
    }
    if (strncmp(data.id, "data", 4) != 0) {
        assert(0);
    }

    //Dataチャンクのデータ部(波形データ)の読み込み
    char* pBuffer = new char[data.size];
    file.read(pBuffer, data.size);

    //Waveファイルを閉じる
    file.close();

    //returnするための音声データ
    SoundData soundData = {};

    soundData.wfex = format.fmt;
    soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
    soundData.bufferSize = data.size;

    return soundData;

}
//音声データ解放
void SoundUnLoad(SoundData* soundData)
{
    //バッファのメモリを解放
    delete[] soundData->pBuffer;

    soundData->pBuffer = 0;
    soundData->bufferSize = 0;
    soundData->wfex = {};
}
//音声再生
void SoundPlayWave(IXAudio2* xAudio2, const SoundData& soundData)
{
    HRESULT result;

    //波形フォーマットを元にSourceVoiceの生成
    IXAudio2SourceVoice* pSourceVoice = nullptr;
    result = xAudio2->CreateSourceVoice(&pSourceVoice, &soundData.wfex);
    assert(SUCCEEDED(result));

    //再生する波形データの設定
    XAUDIO2_BUFFER buf{};
    buf.pAudioData = soundData.pBuffer;
    buf.AudioBytes = soundData.bufferSize;
    buf.Flags = XAUDIO2_END_OF_STREAM;

    //波形データの再生
    result = pSourceVoice->SubmitSourceBuffer(&buf);
    result = pSourceVoice->Start();
}

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

    Microsoft::WRL::ComPtr<IXAudio2> xAudio2;
    IXAudio2MasteringVoice* masterVoice;
    //XAudioエンジンのインスタンスを生成
    HRESULT result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
    //マスターボイスを生成
    result = xAudio2->CreateMasteringVoice(&masterVoice);
    //音声読み込み
    SoundData soundData1 = SoundLoadWave("Resources/fanfare.wav");
    //音声再生
    SoundPlayWave(xAudio2.Get(), soundData1);
    
#pragma endregion 基盤システムの初期化

#pragma region 最初のシーンを初期化

    ImGuiManager* imGui = nullptr;
    imGui = new ImGuiManager();
    imGui->Initialize(winApp,dxCommon);

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

        imGui->Begin();
        
        ImGui::ShowDemoWindow();

        imGui->End();
        

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

        imGui->Draw();
#pragma endregion 最初のシーンの描画

        //描画後処理
        dxCommon->PostDraw();

    }
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
    xAudio2.Reset();
    SoundUnLoad(&soundData1);
    
    //WindowsAPIの終了処理
    winApp->Finalize();
    //WindowsAPI解放
    delete winApp;
#pragma endregion 基盤システムの終了

    return 0;
}