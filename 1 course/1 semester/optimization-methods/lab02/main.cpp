#include <iostream>
#include <cmath>

using namespace std;

struct point
{
    double x;
    double y;
};

double z(double x, double y)
{
    return (x-3)*(x-3)+(y-4)*(y-4); // 3 � 4
}

bool pointIsEqual (point a, point b, double eps)
{
    return (fabs(a.x - b.x) < eps && fabs (a.y - b.y) < eps);
}

point isledPoisk (point b2, double h)
{

    double value_b2 = z(b2.x, b2.y); // ��������� �������� � �������� �����

    // ��� ������ ����������
    if ( z((b2.x+h),b2.y) < value_b2 )
    {
        b2.x += h;
        value_b2 = z(b2.x, b2.y);
    }
    else if ( z((b2.x-h),b2.y) < value_b2 )
    {
        b2.x -= h;
        value_b2 = z(b2.x, b2.y);
    }

    // ��� ������ ����������
    if ( z(b2.x,(b2.y+h)) < value_b2 )
    {
        b2.y += h;
    }
    else if ( z(b2.x,(b2.y-h)) < value_b2 )
    {
        b2.y -= h;
    }

    return b2;
}

void okruglenie (double &chislo, double eps)
{
    if (fabs(chislo - static_cast<int>(chislo)) < eps) chislo = static_cast<int>(chislo);
}

int main()
{
    system("chcp 1251 > nul");

    point b1 {};
    point b2 {};

    double h = 0;
    double eps = 0;
    cout << "������� ���������� �������� �����." << endl;
    cout << "��� x: ";
    cin >> b1.x;
    cout << "��� y: ";
    cin >> b1.y;
    cout << "������� ��� h: ";
    cin >> h;
    cout << "������� �������� eps: ";
    cin >> eps;
    b2 = b1;

    cout << "�������� ����� (" << b1.x << ";" << b1.y << ")" << endl;
    cout << "�������� � �������� �����: " << z(b1.x,b1.y) << endl;
    size_t i = 1;
    for (i = 1; h > eps; ++i)
    {
        // ���������� � ����.
        cout << "��� " << i << "." << endl;
        cout << "������� �������� ����� (" << b2.x << ";" << b2.y << ")" << endl;
        cout << "�������� � ���� �����: " << z(b2.x,b2.y) << endl;

        /// ����������� �����
        b2 = isledPoisk(b2,h);

        /// ����� ������������
        cout << "����� ������������ (" << b2.x << ";" << b2.y << ")" << endl;
        cout << "�������� � ���� �����: " << z(b2.x,b2.y) << endl;

        // ���� ������� �������� ������ ��� �������� � �������� �����
        // ��������� ����� ���� � ��������� ������������
        cout << "������� ����� ����: " << h << endl;
        if (pointIsEqual(b1,b2,eps))
        {
            h /= 10;
        }
        ///������ 1 ��� ������ �� �������
        else
        {
            bool poisk = true;
            for (unsigned int i_poisk = 0; poisk; ++i_poisk)
            {
                point P {};
                P.x = b1.x + 2 * (b2.x-b1.x);
                P.y = b1.y + 2 * (b2.y-b1.y);
                cout << "����� �� ������� (" << P.x << "; " << P.y << ")" << endl;

                /// ����������� �����
                P = isledPoisk(P,h);

                /// ����� ������������
                cout << "����� �� ������� ����� ������������ (" << P.x << "; " << P.y << ")" << endl;
                cout << "�������� � ���� �����: " << z(P.x,P.y) << endl;

                /// ���� �������� � ����� ��������� �������� ����� P > ��� � ���������� �������� ����� b2, �� ������������ � ������� ����� b2
                if (z(P.x,P.y) >= z(b2.x,b2.y) )
                {
                    b1 = b2;
                    poisk = false;

                }
                /// ����� ����� ��������� �������� ����� P �� ����� �������� ����� b2
                else
                {
                    b1 = b2;
                    b2 = P;
                }

                if (i_poisk == 1000)
                {
                    int menu = 0;
                    cout << "���� ����������� 1000 ����� ������ �� �������." << endl;
                    cout << "�������� ������� �� ����� ��������." << endl;
                    cout << "������� �������� ����� (" << b2.x << ";" << b2.y << ")" << endl;
                    cout << "�������� � ���� �����:" << z(b2.x,b2.y) << endl;
                    cout << "������ ���������� ������ ���������?" << endl;
                    cout << "1. ��." << endl;
                    cout << "2. ��������� ������ ���������." << endl;
                    cout << "����: ";
                    cin >> menu;
                    while (menu < 1 || menu > 2)
                    {
                        cout << "������! ��������� ����: ";
                        cin >> menu;
                    }
                    switch (menu)
                    {
                    case 1:
                    {
                        i_poisk = 0;
                        break;
                    }
                    case 2:
                    {
                        poisk = false;
                        h = eps;
                        break;
                    }
                    }
                }
            }
        }
    }
    cout << "������ ��������� ���������!" << endl;
    cout << "����� �������� ���������: " << i-1 << endl;
    okruglenie(b2.x,eps);
    okruglenie(b2.y,eps);
    cout << "�������� ����� (" << b2.x << ";" << b2.y << ")" << endl;
    double value_output = z(b2.x,b2.y);
    okruglenie(value_output,eps);
    cout << "��������:" << value_output << endl;
    system("pause");
    return 0;
}
