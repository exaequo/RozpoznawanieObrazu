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
	return result / extractWhitePixelsCount(data);
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

float Hu(pointerFunctionType data, int i)
{
	using namespace cv;

	Mat src = imread("STaR_database/train/brush/brush_0433.png", 1);
	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			unsigned char t = data.at(y * src.rows + x);
			src.at<Vec3b>(y, x)[0] = t;
			src.at<Vec3b>(y, x)[1] = t;
			src.at<Vec3b>(y, x)[2] = t;
		}
	}

	Mat d = src.clone();
	cvtColor(src, d, CV_BGR2GRAY, 1);
	Moments mu{};
	mu = moments(d, false);
	double hu[7];
	HuMoments(mu, hu);
	return hu[i];
}

float I_1(pointerFunctionType data)
{
	return Hu(data, 0);
}

float I_2(pointerFunctionType data)
{
	return Hu(data, 1);
}

float I_3(pointerFunctionType data)
{
	return Hu(data, 2);
}

float I_4(pointerFunctionType data)
{
	return Hu(data, 3);
}

float I_5(pointerFunctionType data)
{
	return Hu(data, 4);
}

float I_6(pointerFunctionType data)
{
	return Hu(data, 5);
}

float I_7(pointerFunctionType data)
{
	return Hu(data, 6);
}

void normalize(int newMin, int newMax, std::vector<float> &list, float max, float min)
{
	if (max == -1 || min == INFINITY)
	{
		for (int i = 0; i < list.size(); i++)
		{
			if (list[i] < min)
			{
				min = list[i];
			}
			if (list[i] > max)
			{
				max = list[i];
			}
		}
	}

	for (int i = 0; i < list.size(); i++)
	{
		list[i] = (newMin - newMax) * (list[i] - min) / (min - max) + newMin;
	}
}