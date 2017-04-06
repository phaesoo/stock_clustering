
#include "basic_definition.h"
#include "basic_function.h"


// http://www.investopedia.com/terms/c/correlation.asp

// SUM(X)
double Sum(const vector<double>& X)
{
    double sum = 0.0;

    size_t sz = X.size();
    for (size_t i = 0; i < sz; ++i)
    {
        sum += X[i];
    }

    return sum;
}

// SUM(X^2)
double SumSquare(const vector<double>& X)
{
    double sum = 0.0;

    size_t sz = X.size();
    for (size_t i = 0; i < sz; ++i)
    {
        sum += pow(X[i], 2.0);
    }

    return sum;
}

// SUM(X,Y)
double Sum(const vector<double>& X, const vector<double>& Y)
{
    double sum = 0.0;

    size_t sz = X.size();
    if (sz != Y.size()) { assert(0); return 0.0; } // size가 다르면 에러

    for (size_t i = 0; i < sz; ++i)
    {
        sum += X[i] * Y[i];
    }

    return sum;
}

double CorrelationCoefficient(const vector<double>& X, const vector<double>& Y)
{
    size_t n = X.size();
    if (n != Y.size()) { assert(0); return 0.0; } // size가 다르면 에러

    double upper = n * Sum(X, Y) - Sum(X) * Sum(Y);
    double lower = sqrt((n * SumSquare(X) - pow(Sum(X), 2.0)) * (n * SumSquare(Y) - pow(Sum(Y), 2.0)));

    if (lower < DOUBLE_PRECISION)
    {
        assert(0);
        return 0.0;
    }

    return upper / lower;
}

void TestCorrelationCoefficient()
{
    vector<double> X = { 41, 19, 23, 40, 55, 57, 33 };
    vector<double> Y = { 94, 60, 74, 71, 82, 76, 61 };

    vector<double> x = { 1, 3, 5, 7 };
    vector<double> y = { 35, 45, 35, 45 };

    double r = CorrelationCoefficient(x, y);

    int a = 0;
}

double SumOfCorrelationCoefficient(const vector< vector<double> >& stockData,  const vector<int>& clusterIndex)
{
    size_t sz = clusterIndex.size();

    double sum = 0.0;

    for (size_t i = 0; i < sz; ++i)
    {
        for (size_t j = 0; j < sz; ++j)
        {
            if (i == j)
            {
                sum += 1.0;
            }
            else
            {
                sum += CorrelationCoefficient(stockData[clusterIndex[i]], stockData[clusterIndex[j]]);
            }
        }
    }

    return sum;
}

int main()
{
    vector< vector<double> > stockData(505);


    ifstream infile(ABS_FILE_DIR + "profit_ratio.csv");

    int line = 0;

    string strline;
    while (getline(infile, strline))
    {
        vector<string> stringlist = SeperateString(strline, ',');

        size_t sz = stringlist.size();

        for (size_t i = 0; i < sz; ++i)
        {
            if (i == 0) { continue; }

            try // stoi 비정상 동작시 예외 검사위해
            {
                stockData[line].push_back(static_cast<double>(stoi(stringlist[i])));
            }
            catch (...)
            {
                assert(0);
                stockData[line].push_back(0.0);
            }

        }
        ++line;
    }

    int size = 505;

    // 500 x 500 매트릭스 생성
    vector< vector<double> > matrix(size, vector<double>(size));

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (i == j)
            {
                matrix[i][j] = 1.0;
            }
            else
            {
                matrix[i][j] = CorrelationCoefficient(stockData[i], stockData[j]); // 2개의 data로부터 correlation coefficion 계산
            }
        }
    }

    double validcoef = 0.5;

    // 데이터 중복 체크용
    set<int> duplicateCheker;

    map<int, int> dataChecker;

    map< int, vector<int> > dataMap;

    vector< set<int> >cluster;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (i < j)
            {
                if (matrix[i][j] - validcoef > DOUBLE_PRECISION)
                {
                    auto itr = dataChecker.find(j);
                    if (itr != dataChecker.end()) // map에 등록된 값이 아닌 경우
                    {
                        dataMap.insert(map< int, vector<int> >::value_type(i, vector<int>{ j }));
                    }
                    else // map에 등록된 값인 경우
                    {
                        dataMap[itr->second].push_back(j);
                    }

                    dataChecker.insert(map<int, int>::value_type(j, i));
                }
            }
        }
    }

    TestCorrelationCoefficient();

    int a = 0;
}