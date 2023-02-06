#include "Quaternion.h"
#include <cmath>

float Norm(const Quaternion& q)
{
	Vector3 i = q.GetImaginary();
	return sqrt(i.dot(i) + q.w * q.w);
}

Quaternion Normalize(const Quaternion& q)
{
	Quaternion ans = q;
	ans /= Norm(q);
	return ans;
}

Quaternion Inverse(const Quaternion& q)
{
	Quaternion ans = Conjugate(q);
	ans /= Norm(q) * Norm(q);
	return ans;
}

void Quaternion::operator*=(const Quaternion& q)
{
	Vector3 iq1 = this->GetImaginary();
	Vector3 iq2 = q.GetImaginary();

	Quaternion ans =
	{
		this->w* q.w - iq1.dot(iq2),
		iq1.cross(iq2) + q.w * iq1 + this->w * iq2
	};
	*this = ans;
}

Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
{
	Quaternion ans = q1;
	ans *= q2;
	return ans;
}

Quaternion Identity() { return Quaternion(1, 0, 0, 0); }

Quaternion Conjugate(const Quaternion& q) { return Quaternion(q.w, -q.GetImaginary()); }
