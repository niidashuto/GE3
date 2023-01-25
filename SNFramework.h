#pragma once


class SNFramework
{
public://�����o�֐�
	//������
	virtual void Initialize();

	//�I��
	virtual void Finalize();

	//���t���[���X�V
	virtual void Update();

	//�`��
	virtual void Draw() = 0;

	//�I���`�F�b�N
	virtual bool IsEndRequest() { return endRequest_; }

	virtual ~SNFramework() = default;

	//���s
	void Run();
private:
	bool endRequest_ = false;
};

