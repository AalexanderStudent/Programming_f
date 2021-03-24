#include "pch.h"
#include <string>
using namespace std;

TEST(EquationSystemTesting, Case1_AllZero)
{
	string result = tested_function(0, 0, 0, 0, 0, 0);
	EXPECT_EQ(result, "5");
	EXPECT_TRUE(true);
}

TEST(EquationSystemTesting, Case2_GeneralCase)
{
	string result = tested_function(1, 2, 3, 2, 5, 7);
	EXPECT_EQ(result, "2 1.000000 2.000000");
	EXPECT_TRUE(true);
}

TEST(EquationSystemTesting, Case3_1_1_XanyYcertainb0)
{
	string result = tested_function(0, 0, 0, 2, 0, 7);
	EXPECT_EQ(result, "4 3.500000");
	EXPECT_TRUE(true);
}

TEST(EquationSystemTesting, Case3_1_2_XanyYcertaind0)
{
	string result = tested_function(0, 16, 0, 0, 1, 0);
	EXPECT_EQ(result, "4 0.062500");
	EXPECT_TRUE(true);
}

// Case3_1_3 can not be reached

TEST(EquationSystemTesting, Case3_2_1_XcertainYanya0)
{
	string result = tested_function(0, 0, 6.5, 0, 0, 26);
	EXPECT_EQ(result, "3 4.000000");
	EXPECT_TRUE(true);
}

TEST(EquationSystemTesting, Case3_2_2_XcertainYanyc0)
{
	string result = tested_function(6.5, 0, 0, 0, 26, 0);
	EXPECT_EQ(result, "3 4.000000");
	EXPECT_TRUE(true);
}

// Case3_2_3 can not be reached

TEST(EquationSystemTesting, Case3_3_NoSolution)
{
	string result = tested_function(1, 2, 1, 2, 16, -16);
	EXPECT_EQ(result, "0");
	EXPECT_TRUE(true);
}

TEST(EquationSystemTesting, Case3_ShouldHaveZeroDivision1)
// in theory, it should cause division by 0 in "e / b != f / d" check, but doesn't
{
	string result = "Error";
	try
	{
		result = tested_function(0, 7, 0, 0, 7, 0);
	}
	catch (...)
	{
		result = "Error";
	}
	EXPECT_EQ(result, "4 1.000000");		
	EXPECT_TRUE(true);
}

TEST(EquationSystemTesting, Case3_ShouldHaveZeroDivision2)
// in theory, it should cause division by 0 in "e / a != f / c" check, but doesn't
{
	string result = "Error";
	try
	{
		result = tested_function(0, 0, 8, 0, 0, 1);
	}
	catch (...)
	{
		result = "Error";
	}
	EXPECT_EQ(result, "3 0.125000");
	EXPECT_TRUE(true);
}

TEST(EquationSystemTesting, Case4_1_a0c0e0)
{
	string result = tested_function(0, 1, 0, 5, 0, 0);  
	EXPECT_EQ(result, "4 0.000000");
	EXPECT_TRUE(true);
}

// Case4_2 can not be reached

TEST(EquationSystemTesting, Case4_3_a0c0)
{
	string result = tested_function(0, 2, 0, 1, 4, 2);
	EXPECT_EQ(result, "4 2.000000");
	EXPECT_TRUE(true);
}

TEST(EquationSystemTesting, Case5_1_b0d0e0)
{
	string result = tested_function(5, 0, 2, 0, 0, 0);
	EXPECT_EQ(result, "3 0.000000");
	EXPECT_TRUE(true);
}

// Case5_2 can not be reached

TEST(EquationSystemTesting, Case5_3_b0d0)
{
	string result = tested_function(9, 0, 9, 0, 2, 2);
	EXPECT_EQ(result, "3 0.222222");
	EXPECT_TRUE(true);
}

TEST(EquationSystemTesting, Case6_b0e0)
{
	string result = tested_function(6, 0, 3, 8, 0, 0);
	EXPECT_EQ(result, "2 0.000000 0.000000");
	EXPECT_TRUE(true);
}

TEST(EquationSystemTesting, Case7_d0f0)
{
	string result = tested_function(9, 3, 0, 0, 7, 0);
	EXPECT_EQ(result, "1 -3.000000 2.333333");
	EXPECT_TRUE(true);
}

TEST(EquationSystemTesting, Case8_a0e0)
{
	string result = tested_function(0, 9, 1, 6, 0, 0);
	EXPECT_EQ(result, "2 0.000000 0.000000");
	EXPECT_TRUE(true);
}

TEST(EquationSystemTesting, Case9_c0f0)
{
	string result = tested_function(7, 4, 0, 8, 0, 0);
	EXPECT_EQ(result, "2 0.000000 0.000000");
	EXPECT_TRUE(true);
}

TEST(EquationSystemTesting, Case10_abcdProportional)
{
	string result = tested_function(6, 2, 3, 1, 6, 3);
	EXPECT_EQ(result, "1 -3.000000 3.000000");
	EXPECT_TRUE(true);
}

TEST(EquationSystemTesting, Case11_KiddingMe)
{
	string result = tested_function(1, 2, 2, 1, 0, 0);
	EXPECT_EQ(result, "2 0 0");
	EXPECT_TRUE(true);
}

TEST(EquationSystemTesting, PrecisionTrickTest)
// solving it one normal way will generate a mistake
{
	string result = tested_function(0.0000001, 1, 1, 2, 1, 4);
	EXPECT_EQ(result, "2 2.000000 1.000000");		// 2 0.99999979 2.0000004
	EXPECT_TRUE(true);
}
