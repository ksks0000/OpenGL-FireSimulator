#include "pch.h"
#include "Utility.h"


float Utility::GetRandomFloat()
{
	return (float)rand() / (float)RAND_MAX;
}

float Utility::FloatLinearInterpolation(float a, float b, float f)
{
	return (float)(a * (1.0 - f)) + (b * f);
}

Vector3f Utility::VectorLinearInterpolation(Vector3f& a, Vector3f& b, float f)
{
	return (Vector3f)(a * (1.0 - f)) + (b * f);
}

Vector4f Utility::VectorLinearInterpolation(Vector4f& a, Vector4f& b, float f)
{
	return (Vector4f)(a * (1.0 - f)) + (b * f);
}

float Utility::CalculateDistance(Vector3f& a, Vector3f& b)
{
	return (float)sqrt((a.x-b.x)*(a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}
