#include "MyGame.h"
#include "Quaternion.h"

void MyGame::Initialize()
{
#pragma region ��ՃV�X�e���̏�����


    SNFramework::Initialize();

    spriteCommon->LoadTexture(0, "texture.png");
    spriteCommon->LoadTexture(1, "reimu.png");

    Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);

    //�����ǂݍ���
    audio->SoundLoadWave("Resources/fanfare.wav");
    //�����Đ�
    //audio->SoundPlayWave("Resources/fanfare.wav");

#pragma endregion ��ՃV�X�e���̏�����

#pragma region �ŏ��̃V�[����������

    
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
    
    //3D�I�u�W�F�N�g��3D���f�����Ђ��t��
    object3d_1->SetModel(model_1);
    object3d_2->SetModel(model_2);
    object3d_3->SetModel(model_2);
    //3D�I�u�W�F�N�g�̈ʒu���w��
    object3d_2->SetPosition({ -5,0,-5 });
    object3d_3->SetPosition({ +5,0,+5 });
    //3D�I�u�W�F�N�g�̃X�P�[�����w��
    object3d_1->SetPosition({ 0,-50,0 });
    object3d_1->SetScale({ 10.0f,10.0f,10.0f });
    object3d_2->SetScale({ 10.0f,10.0f,10.0f });
    object3d_3->SetScale({ 10.0f,10.0f,10.0f });
#pragma endregion �ŏ��̃V�[����������
}

void MyGame::Finalize()
{
#pragma region �ŏ��̃V�[���̏I��
    delete sprite;
    imGui->Finalize();
    delete imGui;

#pragma endregion �ŏ��̃V�[���̏I��

#pragma region ��ՃV�X�e���̏I��
    //�X�v���C�g���ʕ����
    delete spriteCommon;
    //���͉��
    delete input;
    //DirectX���
    delete dxCommon;

    delete object3d_1;
    delete object3d_2;
    delete object3d_3;

    delete model_1;
    delete model_2;

    
    SNFramework::Finalize();
    delete audio;
    //WindowsAPI���
    delete winApp;
#pragma endregion ��ՃV�X�e���̏I��
}

void MyGame::Update()
{
#pragma region ��ՃV�X�e���̍X�V
    SNFramework::Update();
#pragma endregion ��ՃV�X�e���̍X�V

#pragma region �ŏ��̃V�[���̍X�V

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


#pragma endregion �ŏ��̃V�[���̍X�V
}

void MyGame::Draw()
{
    //�`��O����
    dxCommon->PreDraw();

#pragma region �ŏ��̃V�[���̕`��
    spriteCommon->PreDraw();
    sprite->Draw();
    spriteCommon->PostDraw();
    Object3d::PreDraw(dxCommon->GetCommandList());
    object3d_1->Draw();
    object3d_2->Draw();
    object3d_3->Draw();
    Object3d::PostDraw();

    imGui->Draw();
#pragma endregion �ŏ��̃V�[���̕`��

    //�`��㏈��
    dxCommon->PostDraw();
}
