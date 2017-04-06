#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <set>
#include <map>
#include <assert.h>
#include <direct.h>

using namespace std;

const double DOUBLE_PRECISION = 1E-07;

// Define specific strings(about file)
const string ABS_FILE_DIR = []()-> const string // Program 동작시에 절대경로를 알아와서 경로 세팅
{
    char the_path[256];
    _getcwd(the_path, 256);

    string strpath(the_path);
    strpath.resize(strpath.find("StockClustering"));

    return strpath + "StockClustering\\";
}();