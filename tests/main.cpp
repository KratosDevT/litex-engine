#include "litex/core.h"
#include <cmath>
#include <iostream>
#include <string>

static int g_testsFailed = 0;
static int g_testsPassed = 0;

void printTab() { std::cout << "    "; }
void printNewLine() { std::cout << "\n"; }

void print(const litex::Vector3& v)
{
	std::cout << "[" << v.x << ", " << v.y << ", " << v.z << "]";
}

void printVec(const std::string& label, const litex::Vector3& v)
{
	printTab();
	std::cout << "Vector3 " << label << " ";
	print(v);
	printNewLine();
}

void check(bool condition, const std::string& label)
{
	printTab();
	if (condition)
	{
		std::cout << "[PASS] " << label << "\n";
		++g_testsPassed;
	}
	else
	{
		std::cout << "[FAIL] " << label << "\n";
		++g_testsFailed;
	}
}

bool nearlyEqual(litex::real a, litex::real b, litex::real eps = 1e-5f)
{
	return std::abs(a - b) < eps;
}

void test_defaultConstructor()
{
	std::cout << "[Default constructor]\n";
	litex::Vector3 v;
	check(v.x == 0 && v.y == 0 && v.z == 0,
	      "components are zero when object is default constructed");
	printNewLine();
}

void test_paramConstructor()
{
	std::cout << "[Parametric constructor]: ";
	litex::Vector3 v(1.0f, 2.0f, 3.0f);
	printVec("v", v);
	check(v.x == 1.0f, "x == 1");
	check(v.y == 2.0f, "y == 2");
	check(v.z == 3.0f, "z == 3");
	printNewLine();
}

void test_scalarMultiply()
{
	std::cout << "[Scalar multiply]\n";
	litex::Vector3 v(1.0f, 2.0f, 3.0f);
	litex::Vector3 r = v * 2.0f;
	litex::Vector3 t(2.0f, 4.0f, 6.0f);
	check(t.equals(r), "r=v*2");
	printNewLine();
}

void test_invert()
{
	std::cout << "[Invert]\n";
	litex::Vector3 v(1.0f, -2.0f, 3.0f);
	v.invert();
	check(nearlyEqual(v.x, -1.0f), "x inverted");
	check(nearlyEqual(v.y, 2.0f), "y inverted");
	check(nearlyEqual(v.z, -3.0f), "z inverted");
	printNewLine();
}

void test_squareMagnitude()
{
	std::cout << "[Square magnitude]\n";
	litex::Vector3 v(1.0f, 2.0f, 2.0f);
	check(nearlyEqual(v.squareMagnitude(), 9.0f), "squareMagnitude == 9");
	printNewLine();
}

void test_magnitude()
{
	std::cout << "[Magnitude]\n";
	litex::Vector3 v(1.0f, 2.0f, 2.0f);
	check(nearlyEqual(v.magnitude(), 3.0f), "magnitude == 3");
	printNewLine();
}

void test_normalize()
{
	std::cout << "[Normalize]\n";
	litex::Vector3 v(0.0f, 3.0f, 4.0f);
	v.normalize();
	check(nearlyEqual(v.magnitude(), 1.0f), "magnitude == 1 after normalize");
	printNewLine();
}

void test_normalizeZeroVector()
{
	std::cout << "[Normalize zero vector is safe]\n";
	litex::Vector3 v(0.0f, 0.0f, 0.0f);
	v.normalize();
	check(v.x == 0.0f && v.y == 0.0f && v.z == 0.0f,
	      "zero vector unchanged after normalize");
	printNewLine();
}

void test_sumVectors()
{
	std::cout << "[Sum Diff Vectors]\n";
	litex::Vector3 v1(1.0f, 3.0f, -2.0f);
	litex::Vector3 v2(4.0f, 1.0f, 6.0f);
	litex::Vector3 vDiff = v1 - v2;
	litex::Vector3 vSum = v1 + v2;

	printVec("v1", v1);
	printVec("v2", v2);
	printVec("vSum", vSum);
	printVec("vDiff", vDiff);

	check(vSum.equals(litex::Vector3(5.0f, 4.0f, 4.0f)), "sum vectors ok");
	check(vDiff.equals(litex::Vector3(-3.0f, 2.0f, -8.0f)), "diff vectors ok");
	printNewLine();
}

void test_overloadOperators()
{
	std::cout << "[Overload Vector Operators]\n";
	litex::Vector3 v1(1.0f, 2.0f, 1.0f);
	v1 *= 3;
	litex::Vector3 v2(3.0f, 6.0f, 3.0f);
	printVec("v1", v1);
	printVec("v2", v2);
	check(v1.equals(v2), "test overload *= ok");

	litex::Vector3 v3(2.0f, 2.0f, 2.0f);
	printVec("v3", v3);
	v3 -= v3;
	check(v3.equalsZero(), "test overload -= ok");
	printNewLine();
}

int main()
{
	std::cout << "************TEST SUITE****************\n\n";
	test_defaultConstructor();
	test_paramConstructor();
	test_scalarMultiply();
	test_invert();
	test_squareMagnitude();
	test_magnitude();
	test_normalize();
	test_normalizeZeroVector();
	test_sumVectors();
	test_overloadOperators();
	std::cout << "\nPassed: " << g_testsPassed << "\n";
	std::cout << "Failed: " << g_testsFailed << "\n";
	std::cout << "****************************\n";

	return g_testsFailed > 0 ? 1 : 0;
}
