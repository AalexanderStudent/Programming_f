#include "pch.h"
#include <iostream>
#include <cmath>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

inline string get_results(int regime, double result1, double result2)
{
	return to_string(regime) + " " + to_string(result1) + " " + to_string(result2);
}

inline string get_results(int regime, double result1)
{
	return to_string(regime) + " " + to_string(result1);
}

string tested_function(double a, double b, double c, double d, double e, double f)
{
	string result;
	if ((a == 0) && (b == 0) && (c == 0) && (d == 0) && (e == 0) && (f == 0)) // Case1
	{
		result = "5";
	}
	else if ((a*d - c * b != 0) && ((e*d - b * f != 0) || (a*f - c * e != 0))) // Case2
	{
		double y = (a * f - c * e) / (a * d - c * b);
		double x = (d * e - b * f) / (d * a - b * c);
		result = get_results(2, x, y);
	}
	else if (((a*d - c * b == 0) && ((e*d - b * f != 0) || (a*f - c * e != 0))) ||
		(a == 0 && c == 0 && e / b != f / d) ||		// 0 7 0 0 7 0 - should /0 fail
		(b == 0 && d == 0 && e / a != f / c) ||		// 0 0 8 0 0 1 - should /0 fail
		(a == 0 && b == 0 && c == 0 && d == 0 && (e / f > 0)))
	{
		if (((a == 0 && b == 0 && e == 0 && d != 0 && c == 0) ||
			(c == 0 && d == 0 && f == 0 && b != 0 && a == 0)))	// Case3_1
		{
			double y;
			if (b == 0)											// Case_3_1_1
				y = f / d;
			else if (d == 0)									// Case_3_1_2
				y = e / b;
			else if (e == 0 || f == 0)							// Case_3_1_3
				y = 0;
			result = get_results(4, y);
		}
		else if (((a == 0 && b == 0 && e == 0 && c != 0 && d == 0) ||
			(c == 0 && d == 0 && f == 0 && a != 0 && b == 0)))	// Case3_2
		{
			double x;
			if (a == 0)											// Case3_2_1
				x = f / c;
			else if (c == 0)									// Case3_2_2
				x = e / a;
			else if (e == 0 || f == 0)							// Case3_2_3
				x = 0;
			result = get_results(3, x);
		}
		else													// Case3_3
			result = "0";
	}
	else if (a == 0 && c == 0)
	{
		double y;  
		if (e == 0)												// Case4_1
			y = f / d;
		else if (f == 0)										// Case4_2
			y = e / b;
		else
			y = e / b;											// Case4_3
		result = get_results(4, y);
	}
	else if (b == 0 && d == 0)
	{
		double x;
		if (e == 0)												// Case5_1
			x = f / c;
		else if (f == 0)										// Case5_2
			x = e / a;
		else
			x = e / a;											// Case5_3
		result = get_results(3, x);
	}
	else if (b == 0 && e == 0)									// Case6
	{
		double k, n;
		k = -c / d;
		n = f / d;
		result = get_results(1, k, n);
	}
	else if (d == 0 && f == 0)									// Case7
	{
		double k, n;
		k = -a / b;
		n = e / b;
		result = get_results(1, k, n);
	}
	else if (a == 0 && e == 0)									// Case8
	{
		double k, n;
		k = -d / c;
		n = f / c;
		result = get_results(1, k, n);
	}
	else if (c == 0 && f == 0)									// Case9
	{
		double k, n;
		k = -b / a;
		n = e / a;
		result = get_results(1, k, n);
	}
	else if ((a / b == c / d))									// Case10
	{
		double k, n;
		k = -c / d;
		n = f / d;
		result = get_results(1, k, n);
	}
	else														// Case11
	{
		result = "Are you kidding me?";
	}
	return result;
}
