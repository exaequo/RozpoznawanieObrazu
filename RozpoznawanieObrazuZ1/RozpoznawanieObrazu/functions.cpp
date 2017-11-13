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

float M_ij(pointerFunctionType data, int i, int j)
{
	float result = 0.0f;
	int width = sqrt(data.size());
	int height = width;

	for (int m = 0; m < height; ++m)
	{
		for (int n = 0; n < width; ++n)
		{
				float t = data.at(m * height + n);
				t *= pow(n, i);
				t *= pow(m, j);
				result += t;
		}
	}
	return result;
}

using namespace cv;

float mi_ij(pointerFunctionType data, int i, int j)
{
	float x_avg = M_ij(data, 1, 0) / M_ij(data, 0, 0);
	float y_avg = M_ij(data, 0, 1) / M_ij(data, 0, 0);
	float result = { 0.0f };


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
	Mat canny_output = src.clone();
	std::vector<std::vector<Point> > contours;
	int thresh = 100;
	int max_thresh = 255;
	std::vector<Vec4i> hierarchy;
	Canny(src, canny_output, thresh, thresh * 2, 3);
	/// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	std::vector<Point> c;

	for (int i = 0; i < contours.size(); ++i)
	{
		c.insert(c.end(), contours[i].begin(), contours[i].end());
	}

	Moments mu{};
	mu = moments(c, false);
	

	if (i == 0 && j == 0)
		return mu.m00;
		//return M_ij(data, 0, 0);
	if (i == 0 && j == 1)
		return mu.m01;
		//return 0.0f;
	if (i == 1 && j == 0)
		return mu.m10;
		//return 0.0f;
	if (i == 1 && j == 1)
		return mu.m11;
	//		return M_ij(data, 1, 1) - x_avg * M_ij(data, 0, 1);
	if (i == 2 && j == 0)
		return mu.m20;
	//return M_ij(data, 2, 0) - x_avg * M_ij(data, 1, 0);
	if (i == 0 && j == 2)
		return mu.m02;
	//return M_ij(data, 0, 2) - y_avg * M_ij(data, 0, 1);
	if (i == 2 && j == 1)
		return mu.m21;
	//return M_ij(data, 2, 1) - 2 * x_avg * M_ij(data, 1, 1) - y_avg * M_ij(data, 2, 0) + 2 * pow(x_avg, 2) * M_ij(data, 0, 1);
	if (i == 1 && j == 2)
		return mu.m12;
	//return M_ij(data, 1, 2) - 2 * y_avg * M_ij(data, 1, 1) - x_avg * M_ij(data, 0, 2) + 2 * pow(y_avg, 2) * M_ij(data, 1, 0);
	if (i == 3 && j == 0)
		return mu.m30;
	//return M_ij(data, 3, 0) - 3 * x_avg * M_ij(data, 2, 0) + 2 * pow(x_avg, 2) * M_ij(data, 1, 0);
	if (i == 0 && j == 3)
		return mu.m03;
	//return M_ij(data, 0, 3) - 3 * y_avg * M_ij(data, 0, 2) + 2 * pow(y_avg, 2) * M_ij(data, 0, 1);


	int width = sqrt(data.size());
	int height = width;

	for (int m = 0; m < height; ++m)
	{
		for (int n = 0; n < width; ++n)
		{
				float t = data.at(m * height + n);
				t *= pow((n - x_avg), i);
				t *= pow((m - y_avg), j);
				result += t;
		}
	}
	return result;
}

float eta_ij(pointerFunctionType data, int i, int j)
{
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
	Mat canny_output = src.clone();
	std::vector<std::vector<Point> > contours;
	int thresh = 100;
	int max_thresh = 255;
	std::vector<Vec4i> hierarchy;
	Canny(src, canny_output, thresh, thresh * 2, 3);
	/// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	std::vector<Point> c;

	for (int i = 0; i < contours.size(); ++i)
	{
		c.insert(c.end(), contours[i].begin(), contours[i].end());
	}

	Moments mu{};
	mu = moments(c, false);

	if (i == 0 && j == 2)
		return mu.nu02;
	if (i == 0 && j == 3)
		return mu.nu03;
	if (i == 1 && j == 1)
		return mu.nu11;
	if (i == 1 && j == 2)
		return mu.nu12;
	if (i == 2 && j == 0)
		return mu.nu20;
	if (i == 2 && j == 1)
		return mu.nu21;
	if (i == 3 && j == 0)
		return mu.nu30;

	float result = mi_ij(data, i, j);
	float mi00 = mi_ij(data, 0, 0);
	result /= pow(mi00, (1.0 + ((i + j) / 2.0)));
	return result;
}

float Hu(pointerFunctionType data, int i)
{
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
	Mat canny_output = src.clone();
	std::vector<std::vector<Point> > contours;
	int thresh = 100;
	int max_thresh = 255;
	std::vector<Vec4i> hierarchy;
	Canny(src, canny_output, thresh, thresh * 2, 3);
	/// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	std::vector<Point> c;

	for (int i = 0; i < contours.size(); ++i)
	{
		c.insert(c.end(), contours[i].begin(), contours[i].end());
	}

	Moments mu{};
	mu = moments(c, false);

	double hu[7];

	HuMoments(mu, hu);

	return hu[i];
}

float I_1(pointerFunctionType data)
{
	//test(data);
	//std::vector<unsigned char> list = test(data);

	//for (int i = 0; i < 256; ++i)
	//{
	//	for (int j = 0; j < 256; ++j)
	//	{
	//		std::cout << data.at(i * 256 + j);
	//	}
	//	std::cout << std::endl;
	//}

	//waitKey(0);

	return Hu(data, 0);
	float eta20 = eta_ij(data, 2, 0);
	float eta02 = eta_ij(data, 0, 2);
	return eta20 + eta02;
}

float I_2(pointerFunctionType data)
{
	//std::vector<unsigned char> list = test(data);
	return Hu(data, 1);
	float eta20 = eta_ij(data, 2, 0);
	float eta02 = eta_ij(data, 0, 2);
	float eta11 = eta_ij(data, 1, 1);
	return pow((eta20 - eta02), 2) + 4 * pow(eta11, 2);
}

float I_3(pointerFunctionType data)
{
	return Hu(data, 2);
	//std::vector<unsigned char> list = test(data);
	float eta30 = eta_ij(data, 3, 0);
	float eta12 = eta_ij(data, 1, 2);
	float eta21 = eta_ij(data, 2, 1);
	float eta03 = eta_ij(data, 0, 3);

	return pow((eta30 - 3 * eta12), 2) + pow((3 * eta21 - eta03), 2);
}

float I_4(pointerFunctionType data)
{
	return Hu(data, 3);
	//std::vector<unsigned char> list = test(data);
	float eta30 = eta_ij(data, 3, 0);
	float eta12 = eta_ij(data, 1, 2);
	float eta21 = eta_ij(data, 2, 1);
	float eta03 = eta_ij(data, 0, 3);

	return pow((eta30 + eta12), 2) + pow((eta21 + eta03), 2);
}

float I_5(pointerFunctionType data)
{
	return Hu(data, 4);
	//std::vector<unsigned char> list = test(data);
	float eta30 = eta_ij(data, 3, 0);
	float eta12 = eta_ij(data, 1, 2);
	float eta21 = eta_ij(data, 2, 1);
	float eta03 = eta_ij(data, 0, 3);

	return (eta30 - 3 * eta12) * (eta30 + eta12) * (pow(eta30 + eta12, 2) - 3 * pow(eta21 + eta03, 2)) +
		(3 * eta21 - eta03) * (eta21 + eta03) * (3 * pow(eta30 + eta12, 2) - pow(eta21 + eta03, 2));
}

float I_6(pointerFunctionType data)
{
	return Hu(data, 5);
	//std::vector<unsigned char> list = test(data);
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
	return Hu(data, 6);
	//std::vector<unsigned char> list = test(data);
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


std::vector<unsigned char> linearFilter(pointerFunctionType data)
{
	std::vector<unsigned char> result;
	std::vector<float> list;
	float max = -INFINITY;
	float min = INFINITY;
	int L = 1;
	int width = sqrt(data.size());
	int height = width;
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
	selectedFilter = filter1;

	L = (int)(sqrt(selectedFilter.size()) / 2);

	for (int i = 0; i < height; ++i) 
	{
		for (int j = 0; j < width; ++j) 
		{
			int p = 0;
			int sum = 0;
			for (int m = i - L; m <= i + L; ++m) 
			{
				for (int n = j - L; n <= j + L; ++n)
				{
					int value = 0;
					if ((m >= 0 && m < height) && (n >= 0 && n < width))
					{
						value = data.at(m * height + n);
					}
					else 
					{//obs³uga przypadków krañcowych
						int tmpM = m, tmpN = n;
						if (m < 0) { tmpM = 0; }
						if (m >= height) { tmpM = height - 1; }
						if (n < 0) { tmpN = 0; }
						if (n >= width) { tmpN = width - 1; }
						value = data.at(tmpM * height + tmpN);
					}
					sum += selectedFilter[p] * value;//splot
					p++;
				}
			}
			float value = sum;
			if (value > max) { max = value; }
			if (value < min) { min = value; }
			list.push_back(value);
		}
	}
	normalize(0, 255, list, max, min);//normalizacja
	int n = 0;
	for (int i = 0; i < height; ++i) {//przet³umaczenie znormalizowanego
		for (int j = 0; j < width; ++j) {
			unsigned char val = (unsigned char)list[n];
			result.push_back(val);
			n++;
		}
	}
	return result;
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

float m_p(pointerFunctionType data, int p, float x_avg, float y_avg)
{
	float result = { 0.0f };
	int width = sqrt(data.size());
	int height = width;
	std::cout << "size: " << width << std::endl;
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if ((int)data.at(i * height + j) != 10 &&
				(int)data.at(i * height + j) != 13 &&
				(int)data.at(i * height + j) != 9 &&
				(int)data.at(i * height + j) > 100)
			{
				//std::cout << "o";
				float d = sqrt(pow(i - x_avg, 2) + pow(j - y_avg, 2));
				result += pow(d, p);
			}
			else
			{
				std::cout << (unsigned char)0;
			}
		}
		//std::cout << "\n";
	}
	return result / data.size();
}

float mi_p(pointerFunctionType data, int p, float x_avg, float y_avg)
{
	float result = { 0.0f };
	float m_1 = m_p(data, p, x_avg, y_avg);
	int width = sqrt(data.size());
	int height = width;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((int)data.at(i * height + j) > 250)
			{
				float d = sqrt(pow(i - x_avg, 2) + pow(j - y_avg, 2));
				result += pow(d - m_1, p);
			}
		}
	}
	return result / data.size();
}

float F_1(pointerFunctionType data)
{
	//std::cout << "TUTEJ" << std::endl;
	float result = { 0.0f };
	std::vector<unsigned char> list = linearFilter(data);

	float x_avg = M_ij(data, 1, 0) / M_ij(data, 0, 0);
	float y_avg = M_ij(data, 0, 1) / M_ij(data, 0, 0);
	result = sqrt(mi_p(list, 2, x_avg, y_avg)) / m_p(list, 1, x_avg, y_avg);

	//std::cout << "sqrt: " << sqrt(mi_p(list, 2, x_avg, y_avg)) << " m1: " << m_p(list, 1, x_avg, y_avg) << std::endl;

	return result;
}

float F_2(pointerFunctionType data)
{
	std::vector<unsigned char> list = linearFilter(data);
	float x_avg = M_ij(data, 1, 0) / M_ij(data, 0, 0);
	float y_avg = M_ij(data, 0, 1) / M_ij(data, 0, 0);
	return mi_p(list, 3, x_avg, y_avg) / pow(mi_p(list, 2, x_avg, y_avg), (3 / 2));
}

float F_3(pointerFunctionType data)
{
	std::vector<unsigned char> list = linearFilter(data);
	float x_avg = M_ij(data, 1, 0) / M_ij(data, 0, 0);
	float y_avg = M_ij(data, 0, 1) / M_ij(data, 0, 0);
	return mi_p(list, 4, x_avg, y_avg) / pow(mi_p(list, 2, x_avg, y_avg), 2);
}

using namespace cv;

std::vector<unsigned char> test(pointerFunctionType data)
{

	std::vector<unsigned char> result;

	// Mat(int rows, int cols, int type, void* data, size_t step=AUTO_STEP);
	Mat src = imread("STaR_database/train/brush/brush_0433.png", 1);   // Read the file
	//imshow("test3", src);
	//waitKey(0);

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
	/*FILTER*/
	//int MAX_KERNEL_LENGTH = 35;
	//Mat dst = src.clone();

	//for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
	//{
		//GaussianBlur(src, dst, Size(i, i), 0, 0);
		//medianBlur(src, dst, i);
		//bilateralFilter(src, dst, i, i * 2, i / 2);
	//}
	//bilateralFilter(src, dst, MAX_KERNEL_LENGTH, MAX_KERNEL_LENGTH * 2, MAX_KERNEL_LENGTH / 2);
	//imshow("test", dst);
	//waitKey(0);
	//src = dst;
	/*FILTER END*/
	Mat samples(src.rows * src.cols, 3, CV_32F);
	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++)
			for (int z = 0; z < 3; z++)
				samples.at<float>(y + x * src.rows, z) = src.at<Vec3b>(y, x)[z];

	int clusterCount = 2;
	Mat labels;
	int attempts = 2;
	Mat centers;
	kmeans(samples, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS, centers);

	//Mat new_image(src.size(), src.type());
	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++)
		{
			int cluster_idx = labels.at<int>(y + x*src.rows, 0);
			result.push_back(centers.at<float>(cluster_idx, 0));
			/*new_image.at<Vec3b>(y, x)[0] = centers.at<float>(cluster_idx, 0);
			new_image.at<Vec3b>(y, x)[1] = centers.at<float>(cluster_idx, 1);
			new_image.at<Vec3b>(y, x)[2] = centers.at<float>(cluster_idx, 2);*/
		}
	//imshow("test2", new_image);
	//waitKey(0);

	return result;

}