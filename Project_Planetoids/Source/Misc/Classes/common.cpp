#include "../Headers/common.h"

/*GLfloat distance(Vertex *ver1, Vertex *ver2)
{
	GLfloat dist;
	vector3f v1 = ver1->getLocation();
	vector3f v2 = ver2->getLocation();

	dist = sqrt(pow((get<0>(v1) - get<0>(v2)), 2) + pow((get<1>(v1) - get<1>(v2)), 2) + pow((get<2>(v1) - get<2>(v2)), 2));

	return dist;
}*/

int Simplex::fastFloor(double x)
{
	int xi = (int)x;
	return x < xi ? xi - 1 : xi;
}

double Simplex::sdot(glm::vec3 g, double x, double y, double z)
{
	return g.x*x + g.y*y + g.z*z;
}

double Simplex::noise(double xin, double yin, double zin)
{
	double n0, n1, n2, n3;
	double s = (xin + yin + zin)*f3;

	int i = fastFloor(xin + s);
	int j = fastFloor(yin + s);
	int k = fastFloor(zin + s);

	double t = (i + j + k)*g3;
	double X0 = i - t;
	double Y0 = j - t;
	double Z0 = k - t;
	double x0 = xin - X0;
	double y0 = yin - Y0;
	double z0 = zin - Z0;

	int i1, j1, k1;
	int i2, j2, k2;

	if (x0 >= y0)
	{
		if (y0 >= z0)
		{
			i1 = 1;
			j1 = 0;
			k1 = 0;
			i2 = 1;
			j2 = 1;
			k2 = 0;
		}
		else if (x0 >= z0)
		{
			i1 = 1;
			j1 = 0;
			k1 = 0;
			i2 = 1;
			j2 = 0;
			k2 = 1;
		}
		else
		{
			i1 = 0;
			j1 = 0;
			k1 = 1;
			i2 = 1;
			j2 = 0;
			k2 = 1;
		}
	}
	else
	{
		if (y0 < z0)
		{
			i1 = 0;
			j1 = 0;
			k1 = 1;
			i2 = 0;
			j2 = 1;
			k2 = 1;
		}
		else if (x0 < z0)
		{
			i1 = 0;
			j1 = 1;
			k1 = 0;
			i2 = 0;
			j2 = 1;
			k2 = 1;
		}
		else
		{
			i1 = 0;
			j1 = 1;
			k1 = 0;
			i2 = 1;
			j2 = 1;
			k2 = 0;
		}
	}

	double x1 = x0 - i1 + g3;
	double y1 = y0 - j1 + g3;
	double z1 = z0 - k1 + g3;
	double x2 = x0 - i2 + 2.0*g3;
	double y2 = y0 - j2 + 2.0*g3;
	double z2 = z0 - k2 + 2.0*g3;
	double x3 = x0 - 1.0 + 3.0*g3;
	double y3 = y0 - 1.0 + 3.0*g3;
	double z3 = z0 - 1.0 + 3.0*g3;

	int ii = i & 255;
	int jj = j & 255;
	int kk = k & 255;
	int gi0 = permMod12[ii + perm[jj + perm[kk]]];
	int gi1 = permMod12[ii + i1 + perm[jj + j1 + perm[kk + k1]]];
	int gi2 = permMod12[ii + i2 + perm[jj + j2 + perm[kk + k2]]];
	int gi3 = permMod12[ii + 1 + perm[jj + 1 + perm[kk + 1]]];

	double t0 = 0.6 - x0*x0 - y0*y0 - z0*z0;
	if (t0 < 0)
		n0 = 0.0;
	else
	{
		t0 *= t0;
		n0 = t0 * t0 * sdot(grad3[gi0], x0, y0, z0);
	}

	double t1 = 0.6 - x1*x1 - y1*y1 - z1*z1;
	if (t1 < 0)
		n1 = 0.0;
	else
	{
		t1 *= t1;
		n1 = t1 * t1 * sdot(grad3[gi1], x1, y1, z1);
	}

	double t2 = 0.6 - x2*x2 - y2*y2 - z2*z2;
	if (t2 < 0)
		n2 = 0.0;
	else
	{
		t2 *= t2;
		n2 = t2 * t2 * sdot(grad3[gi2], x2, y2, z2);
	}

	double t3 = 0.6 - x3*x3 - y3*y3 - z3*z3;
	if (t3 < 0)
		n3= 0.0;
	else
	{
		t3 *= t3;
		n3= t3 * t3 * sdot(grad3[gi3], x3, y3, z3);
	}

	double blah = 32.0 * (n0 + n1 + n2 + n3);
	//cout << blah << " ";
	return blah;
}