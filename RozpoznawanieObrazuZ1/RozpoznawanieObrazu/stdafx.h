// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <stdio.h>
#include <tchar.h>
#include <exception>
#include <vector>
#include <iomanip>

#include "targetver.h"
#include "mnist/mnist_reader.hpp"
#include "Extractor.h"
#include "ClassifableObject.h"
#include "functions.h"
#include "FileSaver.h"
#include "Classifier.h"
#include "Statistics.h"
#include "ConsoleColor.h"
#include "StarReader.h"
#include "TexturesReader.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


// TODO: reference additional headers your program requires here
