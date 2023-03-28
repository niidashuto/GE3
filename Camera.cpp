#include "Camera.h"

Camera::Camera()
{
	//������
	viewProjection_.Initialize();

	//�s��v�Z
	viewProjection_.Update();

	//����
	matViewProjection_ = viewProjection_.matView_ * viewProjection_.matProjection_;
}

Camera::~Camera()
{
}

void Camera::Update()
{
	//�_�[�e�B�t���O���L���Ȃ�
	if (viewDirty_ || projectionDirty_)
	{
		//�Čv�Z���K�v�Ȃ�
		if (viewDirty_)
		{
			//�r���[�s��v�Z
			viewProjection_.UpdateView();
			viewDirty_ = false;
		}
		//�Čv�Z���K�v�Ȃ�
		if (projectionDirty_)
		{
			//�v���W�F�N�V�����s��v�Z
			viewProjection_.UpdateProjection();
			projectionDirty_ = false;
		}
		//����
		matViewProjection_ = viewProjection_.matView_ * viewProjection_.matProjection_;
	}

	//�]��
	viewProjection_.Trans();
}

void Camera::CameraMoveVector(const XMFLOAT3& move)
{
	XMFLOAT3 eye_moved = GetEye();
	XMFLOAT3 target_moved = GetTarget();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	target_moved.x += move.x;
	target_moved.y += move.y;
	target_moved.z += move.z;

	SetEye(eye_moved);
	SetTarget(target_moved);
}
void Camera::CameraMoveEyeVector(const XMFLOAT3& move)
{
	XMFLOAT3 eye_moved = GetEye();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	SetEye(eye_moved);
}

void Camera::SetEye(const XMFLOAT3& eye)
{
	viewProjection_.eye_ = eye;

	//�ύX������true
	viewDirty_ = true;
}

void Camera::SetTarget(const XMFLOAT3& target)
{
	viewProjection_.target_ = target;

	//�ύX������true
	viewDirty_ = true;
}

void Camera::SetUp(const XMFLOAT3& up)
{
	viewProjection_.up_ = up;

	//�ύX������true
	viewDirty_ = true;
}