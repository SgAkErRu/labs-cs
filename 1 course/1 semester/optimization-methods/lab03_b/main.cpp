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

int main()
{
    system("chcp 1251 > nul");

    cout << "Lab03. Градиентный метод с постоянным шагом." << endl;

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
        const double alpha = 0.1;
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
