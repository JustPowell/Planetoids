#pragma once
#include "common.h"

template <typename T>
class Vector3d
{
public:
	Vector3d();
	Vector3d(int width, int height, int depth);
	~Vector3d();

	void setDims(int width, int height, int depth);

	T at(int x, int y, int z);

	void put(T obj, int x, int y, int z);

	int getDimSize(int dimension);

private:
	int width, height, depth;

	vector<T> vec;
};

