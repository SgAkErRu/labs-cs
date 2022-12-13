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
    return (x-3)*(x-3)+(y-4)*(y-4); // 3 и 4
}

bool pointIsEqual (point a, point b, double eps)
{
    return (fabs(a.x - b.x) < eps && fabs (a.y - b.y) < eps);
}

point isledPoisk (point b2, double h)
{

    double value_b2 = z(b2.x, b2.y); // Вычисляем значение в базисной точке

    // для первой координаты
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

    // для второй координаты
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
    cout << "Задайте координаты базисной точки." << endl;
    cout << "Для x: ";
    cin >> b1.x;
    cout << "Для y: ";
    cin >> b1.y;
    cout << "Задайте шаг h: ";
    cin >> h;
    cout << "Задайте точность eps: ";
    cin >> eps;
    b2 = b1;

    cout << "Базисная точка (" << b1.x << ";" << b1.y << ")" << endl;
    cout << "Значение в базисной точке: " << z(b1.x,b1.y) << endl;
    size_t i = 1;
    for (i = 1; h > eps; ++i)
    {
        // Информация о шаге.
        cout << "Шаг " << i << "." << endl;
        cout << "Текущая базисная точка (" << b2.x << ";" << b2.y << ")" << endl;
        cout << "Значение в этой точке: " << z(b2.x,b2.y) << endl;

        /// Исследующий поиск
        b2 = isledPoisk(b2,h);

        /// Конец исследования
        cout << "После исследования (" << b2.x << ";" << b2.y << ")" << endl;
        cout << "Значение в этой точке: " << z(b2.x,b2.y) << endl;

        // Если текущее значение больше чем значение в базисной точке
        // Уменьшаем длину шага и повторяем исследование
        cout << "Текущая длина шага: " << h << endl;
        if (pointIsEqual(b1,b2,eps))
        {
            h /= 10;
        }
        ///Делаем 1 шаг поиска по образцу
        else
        {
            bool poisk = true;
            for (unsigned int i_poisk = 0; poisk; ++i_poisk)
            {
                point P {};
                P.x = b1.x + 2 * (b2.x-b1.x);
                P.y = b1.y + 2 * (b2.y-b1.y);
                cout << "Поиск по образцу (" << P.x << "; " << P.y << ")" << endl;

                /// Исследующий поиск
                P = isledPoisk(P,h);

                /// Конец исследования
                cout << "Поиск по образцу после исследования (" << P.x << "; " << P.y << ")" << endl;
                cout << "Значение в этой точке: " << z(P.x,P.y) << endl;

                /// Если значение в новой временной базисной точке P > чем в предыдущей базисной точке b2, то возвращаемся к прошлой точке b2
                if (z(P.x,P.y) >= z(b2.x,b2.y) )
                {
                    b1 = b2;
                    poisk = false;

                }
                /// Иначе берем временную базисную точку P за новую базисную точку b2
                else
                {
                    b1 = b2;
                    b2 = P;
                }

                if (i_poisk == 1000)
                {
                    int menu = 0;
                    cout << "Было произведено 1000 шагов поиска по образцу." << endl;
                    cout << "Возможно функция не имеет минимума." << endl;
                    cout << "Текущая базисная точка (" << b2.x << ";" << b2.y << ")" << endl;
                    cout << "Значение в этой точке:" << z(b2.x,b2.y) << endl;
                    cout << "Хотите продолжить работу алгоритма?" << endl;
                    cout << "1. Да." << endl;
                    cout << "2. Завершить работу программы." << endl;
                    cout << "Ввод: ";
                    cin >> menu;
                    while (menu < 1 || menu > 2)
                    {
                        cout << "Ошибка! Повторите ввод: ";
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
    cout << "Работа алгоритма завершена!" << endl;
    cout << "Шагов итерации алгоритма: " << i-1 << endl;
    okruglenie(b2.x,eps);
    okruglenie(b2.y,eps);
    cout << "Базисная точка (" << b2.x << ";" << b2.y << ")" << endl;
    double value_output = z(b2.x,b2.y);
    okruglenie(value_output,eps);
    cout << "Значение:" << value_output << endl;
    system("pause");
    return 0;
}
