#pragma once

// Created with ReClass.NET 1.2 by KN4CK3R
#define ENTITY_LIST_SIZE 4096

class Entity
{
public:
	char pad_0000[16]; //0x0000
	char* szInfected; //0x0010
	char pad_0014[68]; //0x0014
	int32_t iEntityNumber; //0x0058
	char pad_005C[4]; //0x005C
	char* szModelName; //0x0060
	char pad_0064[36]; //0x0064
	Vector3 vec3Velocity; //0x0088
	Vector3 vec3Position; //0x0094
	Vector3 vec3Position2; //0x00A0
	char pad_00AC[12]; //0x00AC
	Vector3 vec3ViewAngles; //0x00B8
	Vector3 vec3ViewAngles2; //0x00C4
	char pad_00D0[20]; //0x00D0
	int32_t iTeam; //0x00E4
	char pad_00E8[4]; //0x00E8
	int32_t iHealth; //0x00EC
	int32_t iFlags; //0x00F0
	Vector3 vec3OriginOffset; //0x00F4
	Vector3 vec3JumpVelocity; //0x0100
	char pad_010C[24]; //0x010C
	Vector3 vec3Origin; //0x0124
	char pad_0130[20]; //0x0130
	int32_t iAlive; //0x0144
	char pad_0148[1400]; //0x0148
	class BoneMatrix* pBoneMatrix; //0x06C0
	char pad_06C4[664]; //0x06C4
}; //Size: 0x095C

class EntityListNode
{
public:
	class Entity** ppEntityPrev; //0x0000
	class Entity** ppEntityNext; //0x0004
	class Entity* pEntity; //0x0008
	int32_t iID; //0x000C
}; //Size: 0x0010

class EntityList
{
public:
	char pad_0000[12]; //0x0000
	class EntityListNode arr[ENTITY_LIST_SIZE]; //0x000C
	char pad_FFFC[13348]; //0xFFFC
}; //Size: 0x13420

class BoneMatrix
{
public:
	Matrix3x4 arr[19]; //0x0000
}; //Size: 0x0390