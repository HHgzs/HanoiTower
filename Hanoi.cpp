#include <iostream>
#include <vector>
#include <easyx.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#define height 540
#define width 960
#define sleeptime 100

void vector_initialize(std::vector<int> &A, int n)
{
    for (int i = 1; i <= n; i++)
    {
        A.push_back(n - i + 1);
    }
}

void vector_control(int k, std::vector<int> &M, std::vector<int> &N)
{
    N.push_back(k);
    M.pop_back();
}

void display_coloring(int pixel_width, int pixel_height, int k, int x, int y)
{
    solidrectangle((x - k * pixel_width), (y - pixel_height), (x + k * pixel_width), y);
}

void display_calculate_each(int wid, int hei, int y_sta, std::vector<int> &V)
{
    std::vector<int>::iterator it;
    int i = 0;
    int x_start;
    if (V[0] == 1)
    {
        x_start = width / 6;
    }
    else if (V[0] == 2)
    {
        x_start = width / 2;
    }
    else if (V[0] == 3)
    {
        x_start = 5 * width / 6;
    }

    for (it = (V.begin() + 1); it != V.end(); it++)
    {
        display_coloring(wid, hei, *it, x_start, y_sta - (i * hei));
        i++;
    }
}

void display_calculate_total(const int wid, const int hei, int n, std::vector<int> &A, std::vector<int> &B, std::vector<int> &C)
{
    cleardevice();
    int y_start = 6 * height / 7;
    display_calculate_each(wid, hei, y_start, A);
    display_calculate_each(wid, hei, y_start, B);
    display_calculate_each(wid, hei, y_start, C);
}

void Hanoi(int n, int wid, int hei, std::vector<int> &A, std::vector<int> &B, std::vector<int> &C)
{
    if (n == 1)
    {
        vector_control(n, A, C);
        display_calculate_total(wid, hei, n, A, B, C);
    }

    else
    {
        Hanoi(n - 1, wid, hei, A, C, B);
        display_calculate_total(wid, hei, n, A, B, C);
        Sleep(sleeptime);
        vector_control(n, A, C);
        display_calculate_total(wid, hei, n, A, B, C);
        Sleep(sleeptime);
        Hanoi(n - 1, wid, hei, B, A, C);
    }
}

int main()
{

    initgraph(width, height);
    setbkcolor(RGB(164, 225, 202));
    cleardevice();

    char enter = getchar();
    int n = static_cast<int>(enter) - 48;

    if (n < 1)
        return 0;
    int pixel_width = (((width / 6) - 20) / n);
    int pixel_height = 1.5 * pixel_width;

    std::vector<int> A(1, 1);
    std::vector<int> B(1, 2);
    std::vector<int> C(1, 3);

    vector_initialize(A, n);

    Hanoi(n, pixel_width, pixel_height, A, B, C);

    system("pause");
    closegraph();

    return 0;
}
