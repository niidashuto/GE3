#include "MyGame.h"
#include "Quaternion.h"
#include "FbxLoader.h"
#include "ObjectFBX.h"



void MyGame::Initialize()
{
#pragma region 基盤システムの初期化


    SNFramework::Initialize();

    //spriteCommon->LoadTexture(0, "texture.png");
    //spriteCommon->LoadTexture(1, "reimu.png");

    scene_ = new GamePlayScene();

    scene_->Initialize();

    //spriteCommon->LoadTexture(1, "white1x1.png");

    //spriteCommon->LoadTexture(0, "background.png");

    postEffect = new PostEffect();
    
    postEffect->Initialize(spriteCommon, 0);

    postEffect->SetSize({ 500,500 });
    
    
    

    Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);

    

    ParticleManager::StaticInitialize(dxCommon->GetDevice());

    //音声読み込み
    //audio->SoundLoadWave("Resources/fanfare.wav");
    //音声再生
    //audio->SoundPlayWave("Resources/fanfare.wav");


#pragma endregion 基盤システムの初期化

#pragma region 最初のシーンを初期化

    camera_ = new Camera();

    imGui = new ImGuiManager();
    imGui->Initialize(winApp, dxCommon);

    
    //sprite = new Sprite();
    //sprite->SetTextureIndex(0);
    //sprite->Initialize(spriteCommon, 1);

    sprite = new Sprite();
    sprite->SetTextureIndex(0),
    sprite->Initialize(spriteCommon, 0);

    /*sprite2 = new Sprite();
    sprite2->SetTextureIndex(0);
    sprite2->Initialize(spriteCommon, 0);*/

    //sprite2->SetPosition({ 800,0 });

    // レベルデータの読み込み
    jsonData = JsonLoader::LoadFile("TL");

    model_1 = Model::LoadFromOBJ("ground");
    model_2 = Model::LoadFromOBJ("ball");
    model_3 = Model::LoadFromOBJ("skydome");
    model_4 = Model::LoadFromOBJ("sphere");

   
    //3Dオブジェクトの位置を指定
    //object3d_2->SetPosition({ -5,0,-5 });
    //3Dオブジェクトのスケールを指定
    //object3d_1->SetPosition({ 0,-10,0 });
   

    particle1_ = Particle::LoadFromParticleTexture("particle.png");
    pm1_ = ParticleManager::Create();
    pm1_->SetParticleModel(particle1_);
    pm1_->SetCamera(camera_);

    particle2_ = Particle::LoadFromParticleTexture("particle6.png");
    pm2_ = ParticleManager::Create();
    pm2_->SetParticleModel(particle2_);
    pm2_->SetCamera(camera_);

    model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

    ObjectFBX::SetDevice(dxCommon->GetDevice());

    ObjectFBX::SetCamera(camera_);

    ObjectFBX::CreateGraphicsPipeline();

    object1 = new ObjectFBX;
    object1->Initialize();
    object1->SetModel(model1);
    object1->SetRotation({ 0,90,0 });
    camera_->SetTarget({ 0,2.5f,0 });
    camera_->SetEye({ 0,0,8.0f });
    //camera_->SetEye({ 0,0,0 });
    object1->PlayAnimation();

    
    models.insert(std::make_pair("ground", model_1));
    models.insert(std::make_pair("ball", model_2));
    models.insert(std::make_pair("skydome", model_3));
    models.insert(std::make_pair("sphere", model_4));
    

    // レベルデータからオブジェクトを生成、配置
    for (auto& objectData : jsonData->objects) {
        // ファイル名から登録済みモデルを検索
        Model* model = nullptr;
        decltype(models)::iterator it = models.find(objectData.fileName);
        if (it != models.end()) {
            model = it->second;
        }

        // モデルを指定して3Dオブジェクトを生成
        Object3d* newObject = Object3d::Create();
        newObject->SetModel(model);
        // 座標
        DirectX::XMFLOAT3 pos;
        DirectX::XMStoreFloat3(&pos, objectData.translation);
        newObject->SetPosition(pos);

        // 回転角
        DirectX::XMFLOAT3 rot;
        DirectX::XMStoreFloat3(&rot, objectData.rotation);
        newObject->SetRotation(rot);

        // 座標
        DirectX::XMFLOAT3 scale;
        DirectX::XMStoreFloat3(&scale, objectData.scaling);
        newObject->SetScale(scale);

        newObject->SetCamera(camera_);
        // 配列に登録
        objects.push_back(newObject);
    }

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
    

    delete postEffect;

    for (auto& object : objects) {
        delete object;

    }
    delete object1;

    delete model_1;
    delete model_2;
    delete model_3;
    delete model_4;
    delete model1;
    
    SNFramework::Finalize();
    
    
#pragma endregion 基盤システムの終了
}

void MyGame::Update()
{
#pragma region 基盤システムの更新
    SNFramework::Update();
#pragma endregion 基盤システムの更新

#pragma region 最初のシーンの更新

    pm1_->Active(particle1_, 100.0f, 0.2f, 0.001f, 5, { 6.0f, 0.0f });
    pm2_->Active(particle2_, 100.0f, 0.2f, 0.001f, 5, { 6.0f, 0.0f });
    {
        XMFLOAT3 cmove = camera_->GetEye();
        float moveSpeed = 1.0f;

        //キーボード入力による移動処理
        XMMATRIX matTrans = XMMatrixIdentity();
        if (input->Pushkey(DIK_LEFT)) {
           
            cmove.x -= moveSpeed;
        }
        if (input->Pushkey(DIK_RIGHT)) {
            
            cmove.x += moveSpeed;
        }
        if (input->Pushkey(DIK_UP)) {
          
            cmove.y += moveSpeed;
        }
        if (input->Pushkey(DIK_DOWN)) {
           
            cmove.y -= moveSpeed;
        }

        camera_->SetEye(cmove);
    }

    camera_->Update();
    sprite->Update();

    //sprite2->Update();

    postEffect->Update();

    /*object3d_1->Update();
    object3d_2->Update();
    object3d_3->Update();
    object3d_4->Update();*/
    for (auto& object : objects) {
        object->Update();
    }

    object1->Update();
    

    pm1_->Update();
    pm2_->Update();

    imGui->Begin();

    //ImGui::ShowDemoWindow();
    

    imGui->End();


#pragma endregion 最初のシーンの更新
}

void MyGame::Draw()
{
    postEffect->PreDraw(dxCommon->GetCommandList());
    
    
#pragma region 最初のシーンの描画
    spriteCommon->PreDraw();
    //sprite->Draw();
    //sprite2->Draw();

    //sprite->Draw();



    spriteCommon->PostDraw();
    ParticleManager::PreDraw(dxCommon->GetCommandList());
    //pm1_->Draw();
    //pm2_->Draw();
    ParticleManager::PostDraw();

    Object3d::PreDraw(dxCommon->GetCommandList());
    /* for (auto& object : objects) {
         object->Draw();
     }*/

    Object3d::PostDraw();

    ObjectFBX::PreDraw(dxCommon->GetCommandList());

    object1->Draw(dxCommon->GetCommandList());

    ObjectFBX::PostDraw();
    
    
    postEffect->PostDraw(dxCommon->GetCommandList());
   
    //描画前処理
    dxCommon->PreDraw();

    postEffect->Draw(dxCommon->GetCommandList());



    imGui->Draw();
#pragma endregion 最初のシーンの描画

    //描画後処理
    dxCommon->PostDraw();
}
