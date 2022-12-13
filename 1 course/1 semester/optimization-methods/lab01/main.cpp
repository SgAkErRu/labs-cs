#include <iostream>
#include <cmath>
#include <tuple>

using namespace std;

double f(const double x)
{
    return 1.4 * x + exp(fabs(x-2));
}

const double LAMBDA = (1.0 + sqrt(5)) / 2.0;

/**
 * Метод золотого сечения.
 * @param a - левая граница интервала.
 * @param b - правая граница интервала.
 * @param e - точность.
 * @return тройка значений - [значение x; значение y; количество шагов N].
 */
tuple<double, double, int> findMinByGoldenSection(double a, double b, const double e)
{
    double x1 = 0;
    double x2 = 0;

    double y1 = 0;
    double y2 = 0;

    int N = 0;

    // Шаг 1 по схеме алгоритма.
    x1 = b - (b-a) / LAMBDA;
    x2 = a + (b-a) / LAMBDA;

    y1 = f(x1);
    y2 = f(x2);

    do
    {
        ++N;

        // Шаг 2 по схеме алгоритма.
        if (y1 <= y2)
        {
            b = x2;
            x2 = x1;
            y2 = y1;

            x1 = a + b - x2;
            y1 = f(x1);
        }
        else
        {
            a = x1;
            x1 = x2;
            y1 = y2;

            x2 = a + b - x1;
            y2 = f(x2);
        }
    }
    while (fabs(b-a) > e);

    double x_res = 0;
    double y_res = 0;

    // Шаг 3 по схеме алгоритма.
    if (y1 < y2)
    {
        x_res = x1;
        y_res = y1;
    }
    else
    {
        x_res = x2;
        y_res = y2;
    }

    return {x_res, y_res, N};
}

int main()
{
    cout << "Lab01. Find minimum of function by Golden Section method." << endl;

    const auto [x, y, N] = findMinByGoldenSection(0, 2, 0.0015);

    cout << "Algorithm steps: " << N << endl;
    cout << "x: " << x << "; y: " << y << endl;

    return 0;
}
