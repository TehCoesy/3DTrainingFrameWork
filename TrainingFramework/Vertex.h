#pragma once
#include "Math.h"

struct Vertex 
{
	Vertex() {
		pos = Vector3(0.0f, 0.0f, 0.0f);
		normal = Vector3(0.0f, 0.0f, 0.0f);
		binormal = Vector3(0.0f, 0.0f, 0.0f);
		tangent = Vector3(0.0f, 0.0f, 0.0f);
		uv = Vector2(0.0f, 0.0f);
	}

	Vertex(const Vertex& vCopy) {
		pos.x = vCopy.pos.x;	pos.y = vCopy.pos.y; pos.z = vCopy.pos.z;
		normal.x = vCopy.normal.x;	normal.y = vCopy.normal.y; normal.z = vCopy.normal.z;
		binormal.x = vCopy.binormal.x;	binormal.y = vCopy.binormal.y;	binormal.z = vCopy.binormal.z;
		tangent.x = vCopy.tangent.x;	tangent.y = vCopy.tangent.y; tangent.z = vCopy.tangent.z;
		uv.x = vCopy.uv.x;	uv.y = vCopy.uv.y;
	}

	Vector3 pos;
	Vector3 normal;
	Vector3 binormal;
	Vector3 tangent;
	Vector2 uv;
};