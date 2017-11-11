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

float extractRightSideShape(pointerFunctionType data)
{
	float result = 0.0f;
	float temp = 0.0f;
	bool done = false;

	for (int i = data.size() - 1; i >= 0; --i)
	{
		temp += 1.0f;
		if ((i + 28) % 28 == 0)
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

float extractTopShape(pointerFunctionType data)
{
	float result = 0.0f;
	float temp = 0.0f;
	bool done = false;

	for (int i = 0; i < 28; ++i)
	{
		for (int j = 0; j < 28; ++j)
		{
			temp += 1.0f;
			if (data.at(i + j * 28) > (unsigned char)10 && !done)
			{
				done = true;
				result += temp;
			}
		}
		temp = 0.0f;
		done = false;
	}
	return result;
}

float extractBottomShape(pointerFunctionType data)
{
	float result = 0.0f;
	float temp = 0.0f;
	bool done = false;

	for (int i = 0; i < 28; ++i)
	{
		for (int j = 27; j > 0; --j)
		{
			temp += 1.0f;
			if (data.at(i + j * 28) >(unsigned char)10 && !done)
			{
				done = true;
				result += temp;
			}
		}
		temp = 0.0f;
		done = false;
	}
	return result;
}

float extractArea(pointerFunctionType data)
{
	float result = {0.0f};
	int minW = 29;
	int maxW = -1;
	int minH = 29;
	int maxH = -1;

	for (int i = 0; i < 28; ++i)
	{
		for (int j = 0; j < 28; ++j)
		{
			if (data.at(j + i * 28) > (unsigned char)10)
			{
				if (j < minW) minW = j;
				if (j > maxW) maxW = j;
				if (i < minH) minH = i;
				if (i > maxH) maxH = i;
			}
		}
	}
	//std::cout << "minW: " << minW << " maxW: " << maxW << std::endl;
	//std::cout << "minH: " << minH << " maxH: " << maxH << std::endl;

	result = (maxW - minW) * (maxH - minH);

	return result;
}

float test(pointerFunctionType data)
{
	return extractWhitePixelsCount(data) / extractArea(data);

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

