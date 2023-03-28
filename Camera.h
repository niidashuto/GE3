#pragma once
#include "ViewProjection.h"
#include <DirectXMath.h>

class Camera
{
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public://�����o�֐�
	//�R���X�g���N�^��
	Camera();
	virtual ~Camera();
	//�X�V
	virtual void Update();

	//�x�N�g���ɂ��ړ�
	void CameraMoveVector(const XMFLOAT3& move);
	//�x�N�g���ɂ�鎋�_�ړ�
	void CameraMoveEyeVector(const XMFLOAT3& move);

protected://�����o�ϐ�
	//�r���v��
	ViewProjection viewProjection_;
	//�r���v���s��
	XMMATRIX matViewProjection_;

	//�_�[�e�B�t���O��
	bool viewDirty_ = false;
	bool projectionDirty_ = false;

public://�Q�b�^�[�A�Z�b�^�[
	//�r���[�s��̎擾
	const XMMATRIX& GetView() { return viewProjection_.matView_; }
	//�v���W�F�N�V�����s��̎擾
	const XMMATRIX& GetProjection() { return viewProjection_.matProjection_; }
	//�r���v���s��̎擾
	const XMMATRIX& GetViewProjection() { return viewProjection_.matViewProjection_; }
	//�r���{�[�h�s��̎擾
	const XMMATRIX& GetBillboard() { return viewProjection_.matBillboard_; }
	//Y�����r���{�[�h�s��̎擾
	const XMMATRIX& GetBillboardY() { return viewProjection_.matBillboardY_; }

	//���_���W
	const XMFLOAT3& GetEye() { return viewProjection_.eye_; }
	void SetEye(const XMFLOAT3& eye);
	//�����_���W
	const XMFLOAT3& GetTarget() { return viewProjection_.target_; }
	void SetTarget(const XMFLOAT3& target);
	//������x�N�g�����W
	const XMFLOAT3& GetUp() { return viewProjection_.up_; }
	void SetUp(const XMFLOAT3& up);
};
