#include "stdafx.h"
#include "functions.h"
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
	float whitePixels = { 0.0 };
	for (int i = 0; i < 28; ++i)
	{
		for (int j = 0; j < 28; ++j)
		{
			if (data.at(j + i * 28) >(unsigned char)10)
			{
				whitePixels += 1.0f;
				float distance = sqrt((i - x)*(i - x) + (j - y)*(j - y));
				result += distance;
			}
		}
	}
	return result / whitePixels;
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

void normalizePicture(std::vector<unsigned char>& pic)
{
	/*float avg = 0.f;
	float var = 0.f;
	for (int i = 0; i < pic.size(); ++i)
	{
		avg += pic[i];
	}
	avg /= pic.size();

	for (int i = 0; i < pic.size(); ++i)
	{
		var += (pic[i] - avg)*(pic[i] - avg);
	}
	var /= pic.size();

	var = sqrtf(var);

	for (int i = 0; i < pic.size(); ++i)
	{
		float val = ((float)pic[i] - avg) / var;
		pic[i] = (unsigned char)val;
	}*/
	
	float min = 256.f;
	float max = -1.f;
	for (int i = 0; i < pic.size(); ++i)
	{
		if (pic[i] > max) { max = pic[i]; }
		if (pic[i] < min) { min = pic[i]; }
	}

	for (int i = 0; i < pic.size(); ++i)
	{
		pic[i] = (unsigned char)((pic[i] - min) * 255 / (max - min));
	}
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

std::complex<double> WNmnC(int N, int m, int n)
{
	double angle = -2 * M_PI * n * m / N;
	std::complex<double> c(cos(angle), sin(angle));
	return c;
}

std::vector<std::complex<double>> OddEvenVector(std::vector<std::complex<double>>& vec, int n)
{
	std::vector<std::complex<double>> vR;
	for (int i = 0; i < vec.size(); i++)
	{
		if (i % 2 == n)
		{
			vR.push_back(vec.at(i));
		}
	}
	return vR;
}

void FFTR(std::vector<std::complex<double>>& x, int l)
{
	int N = x.size();
	if (N <= 1)
		return;
	std::vector<std::complex<double>> even = OddEvenVector(x, 0);
	std::vector<std::complex<double>> odd = OddEvenVector(x, 1);
	FFTR(even, l);
	FFTR(odd, l);
	for (int k = 0; k < N / 2; k++)
	{
		std::complex<double> W = WNmnC(N, k, l) * odd[k];
		x[k] = even.at(k) + W;
		x[k + N / 2] = even.at(k) - W;
	}
}

std::vector<std::complex<double>> fft(pointerFunctionType data)
{
	int width = sqrt(data.size());
	int height = sqrt(data.size());

	std::vector<std::complex<double>> complexColors = std::vector<std::complex<double>>(width * height);
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			complexColors[i + width * j] = data[i + width * j];
		}
	}

	for (int i = 0; i < height; i++)
	{
		std::vector<std::complex<double>>::const_iterator first = complexColors.begin() + (i * width);
		std::vector<std::complex<double>>::const_iterator last = complexColors.begin() + (i * width) + width;
		std::vector<std::complex<double>> row(first, last);
		FFTR(row, 1);
		for (int j = 0; j < width; j++)
		{
			complexColors[j + width * i] = row[j];
		}
	}

	for (int i = 0; i < width; i++)
	{
		std::vector<std::complex<double>> column(height);
		for (int j = 0; j < height; j++)
		{
			column[j] = complexColors[i + width * j];
		}
		FFTR(column, 1);
		for (int j = 0; j < width; j++)
		{
			complexColors[i + width * j] = column[j];
		}
	}

	return complexColors;
	//we should return something...
	//unless..
	//of course, we have to change quarters, normalize and then get something from spectrum!
}

void changeQuarters(std::vector<std::complex<double>> &data)
{
	int width = sqrt(data.size());
	int height = sqrt(data.size());
	std::vector<std::complex<double>> quarters(data.size());
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (i < width / 2 && j < height / 2)
			{
				quarters[i + width * j] = data[(i + width / 2) + width * (j + height / 2)];
			}
			else if (i >= width / 2 && j >= height / 2)
			{
				quarters[i + width * j] = data[(i - width / 2) + width * (j - height / 2)];
			}
			else if (i < width / 2 && j >= height / 2)
			{
				quarters[i + width * j] = data[(i + width / 2) + width * (j - height / 2)];
			}
			else if (i >= width / 2 && j < height / 2)
			{
				quarters[i + width * j] = data[(i - width / 2) + width * (j + height / 2)];
			}
			else
			{
				quarters[i + width * j] = data[i + width * j];
			}
		}
	}
	data = quarters;
}

double cMultiplier(std::vector<float> &values)
{
	float max = 0;
	float min = 0;

	for (int i = 0; i < values.size(); i++)
	{
		if (values[i] < min)
		{
			min = values[i];
		}
		if (values[i] > max)
		{
			max = values[i];
		}
	}
	double R = fabs(max);
	if (R < fabs(min))
	{
		R = fabs(min);
	}
	return 255.0f / log10(1 + R);
}

float spectrum(pointerFunctionType data, float inner, float outer)
{
	using namespace cv;
	//std::cout << "SPECTRUM" << std::endl;
	std::vector<unsigned char> result(data.size());
	int width = sqrt(data.size());
	int height = sqrt(data.size());
	std::vector<std::complex<double>> complexColors = fft(data);
	changeQuarters(complexColors);
	std::vector<float> values(complexColors.size());
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
				values[i + width * j] = sqrt(real(complexColors[i + width * j]) * real(complexColors[i + width * j]) + imag(complexColors[i + width * j]) * imag(complexColors[i + width * j]));
		}
	}
	double c = cMultiplier(values);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int color = c * log10(1 + fabs(values[i + width * j]));
			result[i + width * j] = color;
		}
	}



	//for (int i = 0; i < width; i++)				//size of every image is 28
	//{
	//	for (int j = 0; j < height; j++)			//by 28
	//	{
	//		//it's needed for proper display digits in terminal (but the dataset is correct)
	//		if ((int)result.at(i * width + j) != 10 &&	//ASCII code for new line (we don't want extra new line in digit!)
	//			(int)result.at(i * width + j) != 13 &&	//ASCII code for carriage return (part of digit is at the beggining of a line!)
	//			(int)result.at(i * width + j) != 9 //ASCII code for horizontal tab (it's just get messy!)
	//			&& (int)result.at(i * width + j) > 180)
	//		{
	//			std::cout << (int)result.at(i * width + j);		//yep, it is a struct of vectors of vectors, but it works fast
	//																			//to get a 0-255 pixel value just cast to int (do we even need it?)
	//		}
	//		else
	//		{
	//			std::cout << (unsigned char)0;			//it's better to display nothing than some ASCII garbage		
	//		}
	//	}
	//	std::cout << std::endl;
	//}


	//system("pause");

	Mat mask = Mat::zeros(width, height, CV_8UC3);
	int thickness = -1;
	int lineType = 8;
	Point center(width / 2, height / 2);
	circle(mask,
		center,
		outer,
		Scalar(1, 1, 1),
		thickness,
		lineType);

	circle(mask,
		center,
		inner,
		Scalar(0, 0, 0),
		thickness,
		lineType);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			result[i + width * j] *= mask.at<Vec3b>(i, j)[0];
		}
	}
	float r = 0.0f;
	int counter = 0;
	for (int i = 0; i < data.size(); ++i)
	{
		//if ((int)result.at(i) > 180)
		//{
			//counter++;
			r += (int)result.at(i);
		//}
	}
	return r;
}

float circle_5_10(pointerFunctionType data)
{
	return spectrum(data, 2.0, 4.0);
}

float circle_10_20(pointerFunctionType data)
{
	return spectrum(data, 14.0, 16.0);
}

float circle_20_40(pointerFunctionType data)
{
	return spectrum(data, 25.0, 27.0);
}

float circle_20_32(pointerFunctionType data)
{
	return spectrum(data, 8.0, 10.0);
}

float laplaceOperator(pointerFunctionType data)
{
	using namespace cv;
	Mat src, src_gray, dst;
	src = imread("textures/texture-train/linen/linen233.bmp", 1);
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
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	char* window_name = "Laplace Demo";
	int c;
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(src, src_gray, CV_BGR2GRAY);
	Mat abs_dst;
	Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);
	threshold(abs_dst, dst, 128, 255, THRESH_BINARY_INV);
	float r = 0.0f;
	int counter = 0;
	for (int y = 0; y < dst.rows; y++)
	{
		for (int x = 0; x < dst.cols; x++)
		{
			r += (int)dst.at<Vec3b>(y, x)[0];
		}
	}
	return r;
}

float HuTextures(pointerFunctionType data, int i)
{
	using namespace cv;
	Mat src, src_gray, dst;
	src = imread("textures/texture-train/linen/linen233.bmp", 1);
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
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	char* window_name = "Laplace Demo";
	int c;
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	cvtColor(src, src_gray, CV_BGR2GRAY);
	Mat abs_dst;
	Laplacian(src_gray, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(dst, abs_dst);
	//threshold(abs_dst, dst, 128, 255, THRESH_BINARY_INV);
	
	Mat d = abs_dst.clone();
	
	//cvtColor(abs_dst, d, CV_BGR2GRAY, 1);
	Moments mu{};
	mu = moments(d, false);
	double hu[7];
	HuMoments(mu, hu);
	return hu[i];
}

float I_1T(pointerFunctionType data)
{
	return HuTextures(data, 0);
}

float I_2T(pointerFunctionType data)
{
	return HuTextures(data, 1);
}

float I_3T(pointerFunctionType data)
{
	return HuTextures(data, 2);
}

float I_4T(pointerFunctionType data)
{
	return HuTextures(data, 3);
}

float I_5T(pointerFunctionType data)
{
	return HuTextures(data, 4);
}

float I_6T(pointerFunctionType data)
{
	return HuTextures(data, 5);
}

float I_7T(pointerFunctionType data)
{
	return HuTextures(data, 6);
}