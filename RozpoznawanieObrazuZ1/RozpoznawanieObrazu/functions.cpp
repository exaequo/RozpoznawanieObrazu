#include "stdafx.h"
#include "functions.h"
#include <math.h>
#include <random>

float extractWhitePixelsCount(pointerFunctionType data)
{
	//linearFilter(data, 1);


	float result = 0.0f;
	for (int i = 0; i < data.size(); ++i)
	{
		if (data.at(i) > (unsigned char)150)
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

float M_ij(pointerFunctionType data, int i, int j)
{
	float result = 0.0f;
	for (int m = 0; m < 28; ++m)
	{
		for (int n = 0; n < 28; ++n)
		{
			if (data.at(m * 28 + n) >(unsigned char)10)
			{
				float t = 1.0f;
				t *= pow(n, i);
				t *= pow(m, j);
				result += t;
			}
		}
	}
	return result;
}

float mi_ij(pointerFunctionType data, int i, int j)
{
	float x_avg = M_ij(data, 1, 0) / M_ij(data, 0, 0);
	float y_avg = M_ij(data, 0, 1) / M_ij(data, 0, 0);
	float result = 0.0f;
	for (int m = 0; m < 28; ++m)
	{
		for (int n = 0; n < 28; ++n)
		{
			if (data.at(m * 28 + n) >(unsigned char)10)
			{
				float t = 1.0f;
				t *= pow((i - x_avg), i);
				t *= pow((m - y_avg), j);
				result += t;
			}
		}
	}
	return result;
}

float eta_ij(pointerFunctionType data, int i, int j)
{
	float result = mi_ij(data, i, j);
	result /= pow(mi_ij(data, 0, 0), (1 + ((i + j) / 2)));
	return result;
}

float I_1(pointerFunctionType data)
{
	float eta20 = eta_ij(data, 2, 0);
	float eta02 = eta_ij(data, 0, 2);
	return eta20 + eta02;
}

float I_2(pointerFunctionType data)
{
	float eta20 = eta_ij(data, 2, 0);
	float eta02 = eta_ij(data, 0, 2);
	float eta11 = eta_ij(data, 1, 1);
	return pow(eta20 - eta02, 2) + 4 * pow(eta11, 2);
}

float I_3(pointerFunctionType data)
{
	float eta30 = eta_ij(data, 3, 0);
	float eta12 = eta_ij(data, 1, 2);
	float eta21 = eta_ij(data, 2, 1);
	float eta03 = eta_ij(data, 0, 3);

	return pow(eta30 - 3 * eta12, 2) + pow(3 * eta21 - eta03, 2);
}

float I_4(pointerFunctionType data)
{
	float eta30 = eta_ij(data, 3, 0);
	float eta12 = eta_ij(data, 1, 2);
	float eta21 = eta_ij(data, 2, 1);
	float eta03 = eta_ij(data, 0, 3);

	return pow(eta30 + eta12, 2) + pow(eta21 + eta03, 2);
}

float I_5(pointerFunctionType data)
{
	float eta30 = eta_ij(data, 3, 0);
	float eta12 = eta_ij(data, 1, 2);
	float eta21 = eta_ij(data, 2, 1);
	float eta03 = eta_ij(data, 0, 3);

	return (eta30 - 3 * eta12) * (eta30 + eta12) * (pow(eta30 + eta12, 2) - 3 * pow(eta21 + eta03, 2)) +
		(3 * eta21 - eta03) * (eta21 + eta03) * (3 * pow(eta30 + eta12, 2) - pow(eta21 + eta03, 2));
}

float I_6(pointerFunctionType data)
{
	float eta20 = eta_ij(data, 2, 0);
	float eta02 = eta_ij(data, 0, 2);
	float eta30 = eta_ij(data, 3, 0);
	float eta12 = eta_ij(data, 1, 2);
	float eta21 = eta_ij(data, 2, 1);
	float eta03 = eta_ij(data, 0, 3);
	float eta11 = eta_ij(data, 1, 1);

	return (eta20 - eta02) * (pow(eta30 + eta12, 2) - pow(eta21 + eta03, 2)) +
		4 * eta11 * (eta30 + eta12) * (eta12 + eta03);
}

float I_7(pointerFunctionType data)
{
	float eta21 = eta_ij(data, 2, 1);
	float eta03 = eta_ij(data, 0, 3);
	float eta30 = eta_ij(data, 3, 0);
	float eta12 = eta_ij(data, 1, 2);

	return (3 * eta21 - eta03) * (eta30 + eta12) * (pow(eta30 + eta12, 2) - 3 * pow(eta21 + eta03, 2)) -
		(eta30 - 3 * eta12) * (eta21 + eta03) * (3 * pow(eta30 + eta12, 2) - pow(eta21 + eta03, 2));
}

float angle(pointerFunctionType data)
{
	float mi00 = mi_ij(data, 0, 0);
	float mip11 = mi_ij(data, 1, 1) / mi00;
	float mip20 = mi_ij(data, 2, 0) / mi00;
	float mip02 = mi_ij(data, 0, 2) / mi00;

	float t = (2 * mip11) / (mip20 - mip02);

	return 0.5f * atan(t);
}


void linearFilter(pointerFunctionType data, int which=1) {

	//std::cout << "|LNEAR!" << std::endl;

	std::vector<unsigned char> list;
	float max = -INFINITY;
	float min = INFINITY;
	int L = 1;

	std::vector<int> filter1 = { 0,-1,0,
		-1,4,-1,
		0,-1,0 };
	std::vector<int> filter2 = { -1,-1,-1,
		-1,8,-1,
		-1,-1,-1 };
	std::vector<int> filter3 = { 1,-2,1,
		-2,4,-2,
		1,-2,1 };
	std::vector<int> selectedFilter;

	switch (which) {
	case 0:
		selectedFilter = filter1;
		break;
	case 1:
		selectedFilter = filter2;
		break;
	case 2:
	default:
		selectedFilter = filter3;
		break;
	}
	L = (int)(sqrt(selectedFilter.size()) / 2);

	for (int i = 0; i < 28; ++i) {
		for (int j = 0; j < 28; ++j) {
			int p = 0;
			int sum = 0;
			for (int m = i - L; m <= i + L; m++) {
				for (int n = j - L; n <= j + L; n++) {
					int value = 0;
					if ((m >= 0 && m < 28) &&
						(n >= 0 && n < 28)) {

						if (data.at(m * 28 + n) >(unsigned char)10)
						{
							value = 1;
						}
						else 
						{ 
							value = 0; 
						}
					}
					else {//obs³uga przypadków krañcowych
						int tmpM = m, tmpN = n;
						if (m<0) {
							tmpM = 0;
						}
						if (m >= 28) {
							tmpM = 28 - 1;
						}
						if (n<0) {
							tmpN = 0;
						}
						if (n >= 28) {
							tmpN = 28 - 1;
						}

						if (data.at(tmpM * 28 + tmpN) >(unsigned char)10)
						{
							value = 1;
						}
						else
						{
							value = 0;
						}
					}
					sum += selectedFilter[p] * value;//splot
					p++;
				}
			}

			float value = sum;
			if (value > max) {
				max = value;
			}
			if (value < min) {
				min = value;
			}
			list.push_back((int)value);
		}
	}

	//normalize(0, 255, list, max, min);//normalizacja
	//int n = 0;
	//for (int i = 0; i< images.first.width(); i++) {//przet³umaczenie znormalizowanego
	//	for (int j = 0; j < images.first.height(); j++) {
	//		int val = (int)list[n];
	//		images.second.setPixelColor(i, j, QColor(val, val, val));
	//		n++;
	//	}
	//}


		for (int i = 0; i < 28; i++)				//size of every image is 28
		{
			for (int j = 0; j < 28; j++)			//by 28
			{
				//it's needed for proper display digits in terminal (but the dataset is correct)
				if ((int)list.at(i * 28 + j) != 10 &&	//ASCII code for new line (we don't want extra new line in digit!)
					(int)list.at(i * 28 + j) != 13 &&	//ASCII code for carriage return (part of digit is at the beggining of a line!)
						(int)list.at(i * 28 + j) != 9) //ASCII code for horizontal tab (it's just get messy!)
				{
					//std::cout << (int)list.at(i * 28 + j);		//yep, it is a struct of vectors of vectors, but it works fast
					//to get a 0-255 pixel value just cast to int (do we even need it?)
				}
				else
				{
					//std::cout << (unsigned char)0;			//it's better to display nothing than some ASCII garbage		
				}
			}									
			std::cout << std::endl;
		}

}