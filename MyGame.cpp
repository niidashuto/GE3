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
