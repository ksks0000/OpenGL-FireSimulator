#pragma once

struct Vector2f
{
	float x, y;
};

struct Vector3f
{
	float x, y, z;
	Vector3f(float X = 0.0f, float Y = 0.0f, float Z = 0.0f) : x(X), y(Y), z(Z) {}

	Vector3f operator*(const Vector3f& vec3f) const
	{
		return Vector3f(x * vec3f.x, y * vec3f.y, z * vec3f.z);
	}

	Vector3f operator*(float scalar) const
	{
		return Vector3f(x * scalar, y * scalar, z * scalar);
	}

	Vector3f operator+(const Vector3f& vec3f) const
	{
		return Vector3f(x + vec3f.x, y + vec3f.y, z + vec3f.z);
	}

	Vector3f& operator=(const Vector3f& vec3f)
	{
		x = vec3f.x;
		y = vec3f.y;
		z = vec3f.z;
		return *this;
	}
};

struct Vector4f
{
	float x, y, z, w;
	Vector4f(float X = 0.0f, float Y = 0.0f, float Z = 0.0f, float W = 0.0f) : x(X), y(Y), z(Z), w(W) {}

	Vector4f operator*(const Vector4f& vec4f) const
	{
		return Vector4f(x * vec4f.x, y * vec4f.y, z * vec4f.z, w * vec4f.w);
	}

	Vector4f operator*(float scalar) const
	{
		return Vector4f(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	Vector4f operator+(const Vector4f& vec4f) const
	{
		return Vector4f(x + vec4f.x, y + vec4f.y, z + vec4f.z, w + vec4f.w);
	}

	Vector4f& operator=(const Vector4f& vec4f)
	{
		x = vec4f.x;
		y = vec4f.y;
		z = vec4f.z;
		w = vec4f.w;
		return *this;
	}
};

struct FlipbookTexParams
{
	char* filePath;
	int frameCount, nRows, nColumns;

	FlipbookTexParams(char* path = "", int frameCount = 1, int nRows = 1, int nColumns = 1) 
		: filePath(path), frameCount(frameCount), nRows(nRows), nColumns(nColumns) {}
};

// za particle sa ili bez teksture
static bool G_TEX_FLAG = false;
// izbor particleSystem ili animatedTextures
static bool G_ANIMATED_TEX_FLAG = true;

class Utility
{
public:
	static float GetRandomFloat();
	static float FloatLinearInterpolation(float a, float b, float f);
	static Vector3f VectorLinearInterpolation(Vector3f& a, Vector3f& b, float f);
	static Vector4f VectorLinearInterpolation(Vector4f& a, Vector4f& b, float f);
	static float CalculateDistance(Vector3f& a, Vector3f& b);
};

