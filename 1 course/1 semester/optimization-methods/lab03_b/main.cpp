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

    cout << "Lab03. ����������� ����� � ���������� �����." << endl;

    // ������ x0, eps.
    const double x0 = 15;
    const double y0 = 20;
    const double eps = 0.0003;

    cout << "��������� ����� x0: " << x0 << endl;
    cout << "��������� ����� y0: " << y0 << endl;

    // ��������� ��������.
    vector<double> gradient;
    gradient.push_back(derivX(x0, y0));
    gradient.push_back(derivY(x0, y0));

    cout << "������-�������� = (" << gradient[0] << ", " << gradient[1] << ")" << endl;

    double xk = x0;
    double yk = y0;

    /// ������������ ���������� ��������.
    const int M = 1000;

    for (int k = 0; k <= M; ++k)
    {
        cout << endl << "�������� ��������� k = " << k << endl;

        // ���������� ���� alpha_k.
        const double alpha = 0.1;
        cout << "��� a_k: " << alpha << endl;

        // ����������� ����� ���������� ������������.
        double xk_next = xk - alpha * gradient[0];
        double yk_next = yk - alpha * gradient[1];
        cout << "����� ����� xk_next: " << xk_next << endl;
        cout << "����� ����� yk_next: " << yk_next << endl;

        // ���������� �������� ��������� � ���� �����.
        gradient[0] = derivX(xk_next, yk_next);
        gradient[1] = derivY(xk_next, yk_next);
        cout << "������-�������� = (" << gradient[0] << ", " << gradient[1] << ")" << endl;

        // ��������� ����� ���������.
        double gradLen = sqrt(gradient[0]*gradient[0] + gradient[1]*gradient[1]);
        cout << "����� �������-��������� ("<< gradient[0] << ", " << gradient[1] << ") = " << gradLen << endl;

        // ��������� ������� ���������.
        if (gradLen <= eps)
        {
            cout << endl << "������������ ������� (" << xk_next << ", " << yk_next << ")"<< endl;
            cout << "f(x,y) = " << f(xk_next, yk_next) << endl;
            break;
        }

        xk = xk_next;
        yk = yk_next;
    }

    return 0;
}
