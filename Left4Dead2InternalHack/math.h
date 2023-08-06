#pragma once
#define PI 3.14159265359

typedef struct vector3_t {
	float x, y, z;

	float abs()
	{
		return sqrt((*this) * (*this));
	}

	vector3_t unit()
	{
		return vector3_t{
			this->x / this->abs(),
			this->y / this->abs(),
			this->z / this->abs()
		};
	}

	vector3_t operator+(const vector3_t& other)
	{
		return vector3_t{
			this->x + other.x,
			this->y + other.y,
			this->z + other.z,
		};
	}

	vector3_t operator-(const vector3_t& other)
	{
		return vector3_t{
			this->x - other.x,
			this->y - other.y,
			this->z - other.z
		};
	}

	float operator*(const vector3_t& other)
	{
		return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
	}

	vector3_t operator^(const vector3_t& other)
	{
		return vector3_t{
			this->y * other.z - this->z * other.y,
			this->z * other.x - this->x * other.z,
			this->x * other.y - this->y * other.x
		};
	}
} Vector3, * PVector3;

typedef struct matrix3x4_t {
	float pad_x[3], x;
	float pad_y[3], y;
	float pad_z[3], z;
}Matrix3x4, * PMatrix3x4;

typedef struct matrix4x4_t {
	float arr[4][4];
}Matrix4x4, PMatrix4x4;
