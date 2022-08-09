#include <stdio.h>

// I WANT TO PLAY WITH YOU
//         YOUR FRIEND, AI

int pointLeft = 0;    //счёт слева
int pointRight = 0;   // счёт справа
int size_x = 80;      // размер поля по оси X - горизонталь
int size_y = 25;      // размер поля по оси Y - вертикаль
int ball_x = 40;      // местонахождение шарика по оси X
int ball_y = 12;      // местонахождение шарика по оси Y
int racketLeft = 11;  // местонахождение левой ракетки
int racketRight = 11; // местонахождение правой ракетки
int vel_x = 1;        // вектор движения шарика по оси X
int vel_y = 1;        // вектор движения шарика по оси Y
int x = 0;
int y = 0;
void draw(int racketLeft, int racketRight, int ball_x, int ball_y, int size_x, int size_y); // ввод переменных для последующего использования в самой функции отрисовки

int main()
{
    while (pointLeft < 1 || pointRight < 1)
    {                    // цикл while (пока "счет слева" и "счет справа" меньше 1 (каждый))
        char c;          // переменная символа
        scanf("%c", &c); // принимаем на ввод с клавиатуры символ (введённая буква для перемещения ракеток)
        if ((c == 'A' || c == 'a') && (racketLeft > 0))
        {                    // если c равно А большая или а маленькая И левая ракетка > 0 (не упирается в начало поля)
            racketLeft -= 1; // левая ракетка -1 (двигается вверх)
        }
        else if ((c == 'Z' || c == 'z') && (racketLeft < size_y - 3))
        {
            racketLeft += 1;
        }
        else if ((c == 'K' || c == 'k') && (racketRight > 0))
        {
            racketRight -= 1;
        }
        else if ((c == 'M' || c == 'm') && (racketRight < size_y - 3))
        {
            racketRight += 1;
            // с остальными можно понять. главное помнить, что +1 по Y - это "вниз", а +1 по X - это "вправо". И наоборот: "-" - это вверх/влево.
        }
        ball_x = ball_x + vel_x; // шарик по оси X равен местонахождению шарика + вектору движения по X
        ball_y = ball_y + vel_y; // аналогично по Y

        if (ball_y == size_y - 1)
        {                   //если шарик по Y == размеру поля по Y - 1, то
            vel_y = -vel_y; // вектро по Y падает
        }
        if (ball_y == 0)
        { // аналогично
            vel_y = -vel_y;
        }
        if (ball_x == 3)
        { // если шарик по оси X достигает 3х (гол левому), то
            if (ball_y >= racketLeft && ball_y < racketLeft + 3)
            {                   // если шарик по оси Y больше И меньше левой ракетки, то
                vel_x = -vel_x; // смена вектора движения по оси X
            }
            else
            {                                // если НЕТ, то
                pointRight = pointRight + 1; // счёт справа +1
                racketLeft = 11;             // ракетка левая по центру
                ball_x = 39;                 // шарик по центру
                racketRight = 11;            // ракетка правая по центру
                ball_y = 11;                 // шарик по центру
                vel_x = 1;                   // направление по стандарту (в сторону правого)
            }
        }
        if (ball_x == 77)
        { // если же шарик достигает 77й колонки (гол правому)
            if (ball_y >= racketRight && ball_y < racketRight + 3)
            {                   //и если шарик по Y больше либо равен правая ракетка И шарик по Y меньше правой ракетки +3, то
                vel_x = -vel_x; // смена вектора направления
            }
            else
            {                              // или же,
                pointLeft = pointLeft + 1; // счёт левому +1
                racketLeft = 11;           //
                ball_x = 40;               //
                racketRight = 11;          //
                ball_y = 12;               //
                vel_x = -1;                //
            }
        }
        if (pointLeft == 5)
        {                        //
            printf("Left WIN!"); //
        }                        //  КОД НЕ ЗАРАБОТАЛ ЗДЕСЬ !!!
        if (pointRight == 5)
        {                         //
            printf("Right WIN!"); //
        }
        draw(racketLeft, racketRight, ball_x, ball_y, size_x, size_y);
    }
    if (pointLeft > pointRight)
    {
        printf("Player LEFT WIN!!!");
    }
    else
    {
        printf("Player RIGHT WIN!!!");
    }
}
void draw(int racketLeft, int racketRight, int ball_x, int ball_y, int size_x, int size_y)
{ // начинается функция отрисовки
    for (int y = 0; y < size_y; y++)
    { // цикл увеличивающегося поля по оси Y
        for (int x = 0; x < size_x; x++)
        { // цикл увеличивающегося поля по оси X
            if (x == ball_x && y == ball_y)
            {                // если Х равен шарику по Х, а Y шарику по Y
                printf("@"); // вывод (изображение мяча)
            }
            else if (y >= racketLeft && y < racketLeft + 3 && x == 3)
            {                // если Y больше либо равен Левой Ракетке И Y меньше левой ракетки+3 И X равен 3, то
                printf("|"); // выводим знак (ракетка)
            }
            else if (y >= racketRight && y < racketRight + 3 && x == 77)
            {
                printf("|"); // то же самое с правой ракеткой
            }
            else if (x == 39 || x == 40)
            { // то же самое для сетки
                printf("I");
            }
            else
            {                // если "ничего", то
                printf(" "); // выводим пробел
            }
        }
        printf("\n"); // новая строка
    }
    printf("\e[5;35H%02d", pointLeft);  // выводим знак (сам счёт) -
    printf("\e[5;45H%02d", pointRight); // то же самое для правого
    printf("\e[26;1H");                 // эта штука (как и две предыдущие) из ANSI, управляющая последовательность для, если говорить коротко, разнообразия терминала. Конкретно эта команда убирает курсор со счёта и пермещает его на положенное место (начало новой строки)
}
