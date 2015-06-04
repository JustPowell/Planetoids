#include "../Headers/Vector3d.h"

template <typename T>
Vector3d<T>::Vector3d(int width, int height, int depth)
{
	this->width = width;
	this->height = height;
	this->depth = depth;
	this->vec.resize(width*height*depth);
}

template <typename T>
Vector3d<T>::~Vector3d()
{
}

template <typename T>
void Vector3d<T>::setDims(int width, int height, int depth)
{
	this->width = width;
	this->height = height;
	this->depth = depth;
	this->vec.resize(width*height*depth);
}

template <typename T>
T Vector3d<T>::at(int x, int y, int z)
{
	return this->vec[x + width * (y + height * z)];
}

template <typename T>
void Vector3d<T>::put(T obj, int x, int y, int z)
{
	this->vec[x + width * (y + height * z)] = obj;
}

template <typename T>
int Vector3d<T>::getDimSize(int dimension)
{
	switch (dimension)
	{
	case 0:
		return this->width;
	case 1:
		return this->height;
	case 2:
		return this->depth;
	}
}