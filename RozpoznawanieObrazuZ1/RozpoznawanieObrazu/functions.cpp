#include "stdafx.h"
#include "functions.h"
#include <math.h>
#include <random>

float extractWhitePixelsCount(pointerFunctionType data)
{
	float result = 0.0f;
	for (int i = 0; i < data.size(); ++i)
	{
		if (data.at(i) > (unsigned char)10)
		{
			result += 1.0f;
		}
	}
	return result;
}

float extractRoundShapesCount(pointerFunctionType)
{
	return rand() % 4;
}


float extractWhitePixelsOnBottomHalfCount(pointerFunctionType data)
{
	float result = 0.0f;
	for (int i = data.size() / 2; i < data.size(); ++i)
	{
		if (data.at(i) >(unsigned char)10)
		{
			result += 1.0f;
		}
	}
	return result;
}

float extractWhitePixelsOnTopHalfCount(pointerFunctionType data)
{
	float result = 0.0f;
	for (int i = 0; i < data.size() / 2; ++i)
	{
		if (data.at(i) >(unsigned char)10)
		{
			result += 1.0f;
		}
	}
	return result;
}

float extractLeftSideShape(pointerFunctionType data)
{
	float result = 0.0f;
	float temp = 0.0f;
	bool done = false;
	for (int i = 0; i < data.size(); ++i)
	{
		temp += 1.0f;
		if (i % 28 == 0)
		{
			temp = 0.0f;
			done = false;
		}
		if (data.at(i) >(unsigned char)10 && !done)
		{
			done = true;
			result += temp;
		}
	}
	return result;

}
