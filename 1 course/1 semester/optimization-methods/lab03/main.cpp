#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double dx = 1e-8;

double f(double x, double y)
{
    return (x-3)*(x-3)+(y-4)*(y-4);
}

double derivX(double x, double y)
{
    return (f(x + dx, y) - f(x, y)) / dx;
}

double derivY(double x, double y)
{
    return (f(x, y + dx) - f(x, y)) / dx;
}

double findMinByGoldenSection(double a, double b, double xk, double yk, const vector<double> &grad, const double eps)
{
    const double LAMBDA = (1.0 + sqrt(5)) / 2.0;

    double x1 = 0;
    double x2 = 0;

    double y1 = 0;
    double y2 = 0;

    vector<double> t(2);

    // Шаг 1 по схеме алгоритма.
    x1 = b - (b-a) / LAMBDA;
    x2 = a + (b-a) / LAMBDA;

    t[0] = xk - x1 * grad[0];
    t[1] = yk - x1 * grad[1];
    y1 = f(t[0], t[1]);

    t[0] = xk - x2 * grad[0];
    t[1] = yk - x2 * grad[1];
    y2 = f(t[0], t[1]);
    do
    {
        // Шаг 2 по схеме алгоритма.
        if (y1 <= y2)
        {
            b = x2;
            x2 = x1;
            y2 = y1;

            x1 = a + b - x2;

            t[0] = xk - x1 * grad[0];
            t[1] = yk - x1 * grad[1];
            y1 = f(t[0], t[1]);
        }
        else
        {
            a = x1;
            x1 = x2;
            y1 = y2;

            x2 = a + b - x1;

            t[0] = xk - x2 * grad[0];
            t[1] = yk - x2 * grad[1];
            y2 = f(t[0], t[1]);
        }
    }
    while (fabs(b-a) > eps);

    double x_res = 0;

    // Шаг 3 по схеме алгоритма.
    if (y1 < y2)
    {
        x_res = x1;
    }
    else
    {
        x_res = x2;
    }

    return x_res;
}

int main()
{
    system("chcp 1251 > nul");

    cout << "Lab03. Метод наискорейшего спуска." << endl;

    // Задаем x0, eps.
    const double x0 = 15;
    const double y0 = 20;
    const double eps = 0.0003;

    cout << "Начальная точка x0: " << x0 << endl;
    cout << "Начальная точка y0: " << y0 << endl;

    // Вычисляем градиент.
    vector<double> gradient;
    gradient.push_back(derivX(x0, y0));
    gradient.push_back(derivY(x0, y0));

    cout << "Вектор-градиент = (" << gradient[0] << ", " << gradient[1] << ")" << endl;

    double xk = x0;
    double yk = y0;

    /// Максимальное количество итераций.
    const int M = 1000;

    for (int k = 0; k <= M; ++k)
    {
        cout << endl << "Итерация алгоритма k = " << k << endl;

        // Вычисление шага alpha_k.
        double alpha = findMinByGoldenSection(-100, 100, xk, yk, gradient, eps);
        cout << "Шаг a_k: " << alpha << endl;

        // Определение точки очередного эксперимента.
        double xk_next = xk - alpha * gradient[0];
        double yk_next = yk - alpha * gradient[1];
        cout << "Новая точка xk_next: " << xk_next << endl;
        cout << "Новая точка yk_next: " << yk_next << endl;

        // Вычисление значения градиента в этой точке.
        gradient[0] = derivX(xk_next, yk_next);
        gradient[1] = derivY(xk_next, yk_next);
        cout << "Вектор-градиент = (" << gradient[0] << ", " << gradient[1] << ")" << endl;

        // Вычисляем длину градиента.
        double gradLen = sqrt(gradient[0]*gradient[0] + gradient[1]*gradient[1]);
        cout << "Длина вектора-градиента ("<< gradient[0] << ", " << gradient[1] << ") = " << gradLen << endl;

        // Проверяем условие остановки.
        if (gradLen <= eps)
        {
            cout << endl << "Приближенное решение (" << xk_next << ", " << yk_next << ")"<< endl;
            cout << "f(x,y) = " << f(xk_next, yk_next) << endl;
            break;
        }

        xk = xk_next;
        yk = yk_next;
    }

    return 0;
}
