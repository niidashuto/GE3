#include "SNFramework.h"

void SNFramework::Initialize()
{
}

void SNFramework::Finalize()
{
}

void SNFramework::Update()
{
}

void SNFramework::Run()
{
	//�Q�[���̏�����
	Initialize();

	while (true)//�Q�[�����[�v
	{
		//���t���[���X�V
		Update();
		//�I�����N�G�X�g�������甲����
		if (IsEndRequest())
		{
			break;
		}
		//�`��
		Draw();
	}
	//�Q�[���̏I��
	Finalize();
}
