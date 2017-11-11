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
	int minW = { 29 };
	int maxW = { -1 };
	int minH = { 29 };
	int maxH = { -1 };

	for (int i = 0; i < 28; ++i)
	{
		for (int j = 0; j < 28; ++j)
		{
			if (data.at(i * 28 + j) >(unsigned char)10)
			{
				if (j < minW) { minW = j; }
				if (j > maxW) { maxW = j; }
				if (i < minH) { minH = i; }
				if (i > maxH) { maxH = i; }
			}
		}
	}

	if (maxH % 2 != 0) maxH++;
	if (maxW % 2 != 0) maxW++;

	float result = 0.0f;
	for (int i = maxH / 2; i < maxH; ++i)
	{
		for (int j = minW; j < maxW; ++j)
		{
			if (data.at(i * 28 + j) >(unsigned char)10)
			{
				result += 1.0f;
			}
		}
	}
	return result;
}

float extractWhitePixelsOnTopHalfCount(pointerFunctionType data)
{
	int minW = { 29 };
	int maxW = { -1 };
	int minH = { 29 };
	int maxH = { -1 };

	for (int i = 0; i < 28; ++i)
	{
		for (int j = 0; j < 28; ++j)
		{
			if (data.at(i * 28 + j) >(unsigned char)10)
			{
				if (j < minW) { minW = j; }
				if (j > maxW) { maxW = j; }
				if (i < minH) { minH = i; }
				if (i > maxH) { maxH = i; }
			}
		}
	}

	if (maxH % 2 != 0) maxH++;
	if (maxW % 2 != 0) maxW++;

	float result = 0.0f;
	for (int i = minH; i < maxH / 2; ++i)
	{
		for (int j = minW; j < maxW; ++j)
		{
			if (data.at(i * 28 + j) >(unsigned char)10)
			{
				result += 1.0f;
			}
		}
	}
	return result;
}

float extractLeftSideShape(pointerFunctionType data)
{
	int minW = { 29 };
	int maxW = { -1 };
	int minH = { 29 };
	int maxH = { -1 };

	for (int i = 0; i < 28; ++i)
	{
		for (int j = 0; j < 28; ++j)
		{
			if (data.at(i * 28 + j) >(unsigned char)10)
			{
				if (j < minW) { minW = j; }
				if (j > maxW) { maxW = j; }
				if (i < minH) { minH = i; }
				if (i > maxH) { maxH = i; }
			}
		}
	}

	float temp = { 0.0f };
	float result = { 0.0f };
	bool done = false;
	for (int i = minH; i < maxH; ++i)
	{
		for (int j = minW; j < maxW; ++j)
		{
			temp += 1.0f;
			if (data.at(i * 28 + j) >(unsigned char)10 && !done)
			{
				done = true;
				result += temp;
				break;
			}
		}
		done = false;
		temp = 0.0f;
	}
	return result;
}

float extractRightSideShape(pointerFunctionType data)
{
	int minW = { 29 };
	int maxW = { -1 };
	int minH = { 29 };
	int maxH = { -1 };

	for (int i = 0; i < 28; ++i)
	{
		for (int j = 0; j < 28; ++j)
		{
			if (data.at(i * 28 + j) >(unsigned char)10)
			{
				if (j < minW) { minW = j; }
				if (j > maxW) { maxW = j; }
				if (i < minH) { minH = i; }
				if (i > maxH) { maxH = i; }
			}
		}
	}

	float temp = { 0.0f };
	float result = { 0.0f };
	bool done = false;
	for (int i = minH; i < maxH; ++i)
	{
		for (int j = maxW; j > minW; --j)
		{
			temp += 1.0f;
			if (data.at(i * 28 + j) >(unsigned char)10 && !done)
			{
				done = true;
				result += temp;
				break;
			}
		}
		done = false;
		temp = 0.0f;
	}
	return result;
}

float extractTopShape(pointerFunctionType data)
{
	float temp = { 0.0f };
	float result = { 0.0f };
	bool done = false;
	for (int i = 0; i < 28; ++i)
	{
		for (int j = 0; j < 28; ++j)
		{
			temp += 1.0f;
			if (data.at(j * 28 + i) >(unsigned char)10 && !done)
			{
				done = true;
				result += temp;
				break;
			}
		}
		done = false;
		temp = 0.0f;
	}
	return result;
}

float extractBottomShape(pointerFunctionType data)
{
	int minW = { 29 };
	int maxW = { -1 };
	int minH = { 29 };
	int maxH = { -1 };

	for (int i = 0; i < 28; ++i)
	{
		for (int j = 0; j < 28; ++j)
		{
			if (data.at(i * 28 + j) >(unsigned char)10)
			{
				if (j < minW) { minW = j; }
				if (j > maxW) { maxW = j; }
				if (i < minH) { minH = i; }
				if (i > maxH) { maxH = i; }
			}
		}
	}

	float temp = { 0.0f };
	float result = { 0.0f };
	bool done = false;
	for (int i = minH; i < maxH; ++i)
	{
		for (int j = maxW; j > minW; --j)
		{
			temp += 1.0f;
			if (data.at(j * 28 + i) >(unsigned char)10 && !done)
			{
				done = true;
				result += temp;
				break;
			}
		}
		done = false;
		temp = 0.0f;
	}
	return result;
}

float extractRectangleArea(pointerFunctionType data)
{
	int minW = { 29 };
	int maxW = { -1 };
	int minH = { 29 };
	int maxH = { -1 };

	for (int i = 0; i < 28; ++i)
	{
		for (int j = 0; j < 28; ++j)
		{
			if (data.at(j + i * 28) > (unsigned char)10)
			{
				if (j < minW) { minW = j; }
				if (j > maxW) { maxW = j; }
				if (i < minH) { minH = i; }
				if (i > maxH) { maxH = i; }
			}
		}
	}
	return (maxW - minW) * (maxH - minH);
}

float pixelRectangleRatio(pointerFunctionType data)
{
	return extractWhitePixelsCount(data) / extractRectangleArea(data);
}

float centerWidth(pointerFunctionType data)
{
	int t = { 0 };
	float result = { 0.0f };
	for (int i = 0; i < 28; ++i)
	{
		for (int j = 0; j < 28; ++j)
		{
			if (data.at(j + i * 28) >(unsigned char)10)
			{
				result += i;
				t++;
			}
		}
	}
	return result / t;
}

float centerHeight(pointerFunctionType data)
{
	int t = { 0 };
	float result = { 0.0f };
	for (int i = 0; i < 28; ++i)
	{
		for (int j = 0; j < 28; ++j)
		{
			if (data.at(j + i * 28) >(unsigned char)10)
			{
				result += j;
				t++;
			}
		}
	}
	return result / t;
}

float distanceCenter(pointerFunctionType data)
{
	float x = centerWidth(data);
	float y = centerHeight(data);
	float result = { 0.0f };
	for (int i = 0; i < 28; ++i)
	{
		for (int j = 0; j < 28; ++j)
		{
			if (data.at(j + i * 28) >(unsigned char)10)
			{
				float distance = sqrt((i - x)*(i - x) + (j - y)*(j - y));
				result += distance;
			}
		}
	}
	return result;
}

float heightWidthRatio(pointerFunctionType data)
{
	float x = centerWidth(data);
	float y = centerHeight(data);
	float resultW = { 0.0f };
	float resultH = { 0.0f };
	for (int i = 0; i < 28; ++i)
	{
		for (int j = 0; j < 28; ++j)
		{
			if (data.at(j + i * 28) >(unsigned char)10)
			{
				resultW += fabsf(j - x);
				resultH += fabsf(i - y);
			}
		}
	}
	return resultH / resultW;
}

float extractWholeImage(pointerFunctionType data)
{
	float result{ 0.f };

	for (int i = 0; i < data.size(); ++i)
	{
		if (data[i] >(unsigned char)10)
		{
			result += i;// *(i % 28 + 1);
		}
	}

	return result;
}

float extractWholeImageInverse(pointerFunctionType data)
{
	float result{ 0.f };

	for (int i = data.size() - 1; i > 0; --i)
	{
		if (data[i] >(unsigned char)10)
		{
			result += (data.size() - i);// *(i % 28 + 1);
		}
	}

	return result;
}

