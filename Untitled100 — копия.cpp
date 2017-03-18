#include "TXLib.h"

const int Parallax = 50;

struct Hero
    {
    int x, y;
    int vx, vy;
    HDC image;


    };


void Move();
void Yprava (Hero* hero);
void Ris  (Hero hero);
void Dvig (Hero* hero, int dt);
void Final(int x, int y, HDC vzriv);

int main()
    {
    txCreateWindow (2560, 1140);
    txBegin();
    Move();
    }

void Move ()
    {
    HDC  Untitled_waflia = txLoadImage ("Untitled_waflia.bmp");

    Hero main = { 300, 300, 6, 4, Untitled_waflia };

    Hero bot1 = { 800, 600, 4, 3, Untitled_waflia };

    Hero bot2 = { 500, 900, 3, 4, Untitled_waflia };

    Hero bot3 = { 1300, 100, 3, 4, Untitled_waflia };

    int dt = 1;

    HDC  derevoPered     = txLoadImage ("#дерево п.п.bmp");
    HDC  derevoZad       = txLoadImage ("#дерево средний план.bmp");
    HDC  derevoZad2      = txLoadImage ("#дерево задний план.bmp");
    HDC  vzriv           = txLoadImage ("#112.bmp");

     while (!GetAsyncKeyState(VK_F1))
        {
        txBitBlt(txDC(), -main.x/Parallax, -main.y/Parallax, 2560, 1140, derevoZad2, 0, 0);
        txTransparentBlt(txDC(), 0, 0, 2560, 1140, derevoZad,  0, 0);

        Ris(main);

        Ris(bot1);
        Ris(bot2);
        Ris(bot3);
        txTransparentBlt(txDC(), main.x/Parallax, main.y/Parallax, 2560, 1140, derevoPered, 0, 0);


        Dvig (&main, dt);

        Dvig(&bot1, dt);
        Dvig(&bot2, dt);
        Dvig(&bot3, dt);
        Yprava ( &main);

        int dist  = sqrt ((main.x - bot1.x) * (main.x - bot1.x) + (main.y - bot1.y) * (main.y - bot1.y));
        int dist1 = sqrt ((main.x - bot2.x) * (main.x - bot2.x) + (main.y - bot2.y) * (main.y - bot2.y));
        int dist2 = sqrt ((main.x - bot3.x) * (main.x - bot3.x) + (main.y - bot3.y) * (main.y - bot3.y));

        if (dist <= 50 || dist1 <= 50 || dist2 <= 50)
            {
            Final(main.x, main.y, vzriv);
            break;
            }
        txSleep(0);
        }
    }

void Ris(Hero hero)
    {
    txTransparentBlt (txDC(), hero.x - 40, hero.y, 250, 187, hero.image, 0, 0, TX_WHITE);
    }

void Dvig (Hero* hero, int dt)
    {
        (*hero).x = (*hero).x + (*hero).vx * dt;

        hero->y = hero->y + hero->vy * dt;

        if (hero->x > 2100)
        {
            hero->vx = -hero->vx;
            hero->x = 2100;
        };

        if (hero->y > 1000)
        {
            hero->vy = -hero->vy;
            hero->y = 1000;
        };

        if (hero->x < 300)
        {
            hero->vx = -hero->vx;
            hero->x = 300;
        };

        if (hero->y < -0)
        {
            hero->vy = -hero->vy;
            hero->y = -0;
        };
    }

void Yprava(Hero* hero)
    {

    if (GetAsyncKeyState('A'))
        {
        hero->vx = -hero->vx;
        }
    if (GetAsyncKeyState('S'))
        {
        hero->vy = -hero->vy;
        }
    }


void Final(int x, int y, HDC vzriv)
    {
    txTransparentBlt (txDC(), x, y, 520, 290, vzriv, 0, 0) ; ;
    txClear();
    txSetFillColor (TX_BLACK);
    txSetColor (TX_RED);
    txSelectFont ("Arial", 200);
    txTextOut (850, 500, "YOU LOSE :(");
    }
