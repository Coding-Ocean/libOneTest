#define B
#ifdef B
#include"framework.h"
#include"window.h"
#include"graphic.h"
class BALL {
    float x;
    float y;
    float r;
    float vx;
    float vy;
    bool flag;
public:
    BALL(float x, float y, float r, float vx, float vy) :
        x(x), y(y), r(r), vx(vx), vy(vy), flag(false) {
    }
    void move() {
        x += vx;
        y += vy;
        if (x<r || x>Width - r)vx *= -1;
        if (y<r || y>Height - r)vy *= -1;
    }
    void intersects(BALL* other) {
        float a = other->x - x;
        float b = other->y - y;
        float c = other->r + r;
        if (a * a + b * b <= c * c) {
            flag = true;
            other->flag = true;
        }
        else {
            flag = false;
            other->flag = false;
        }
    }
    void draw() {
        if (flag) {
            fill(250, 0, 0, 128);
        }
        else {
            fill(250, 250, 200);
        }
        circle(x, y, r * 2);
    }
    void lineto(BALL* other) {
        line(x, y, other->x, other->y);
    }
};
void back() {
    fill(250, 200, 220);
    noStroke();
    rect(0, 0, Width, Height);
}
void gmain() {
    window(1600, 900);
    BALL* a = new BALL(Width / 2+200, Height / 2, 200, 6, -3);
    BALL* b = new BALL(Width / 2-200, Height / 2, 100, -3, 6);
    repeat() {
        a->move();
        b->move();
        a->intersects(b);

        clear(250, 200, 220);
        a->draw();
        b->draw();
        a->lineto(b);
    }
    delete a;
    delete b;
}
#endif

#ifdef A
#include"framework.h"
#include"window.h"
#include"graphic.h"
void gmain() {
    window(640, 480, true);

    float x = Width / 2, y = Height / 2, r = 10, vx = 5, vy = -3;

    int allImg = loadImage("zenemy.png");
    int img[4][4];
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            if (i < 3) {
                img[j][i] = cutImage(allImg, 32 * i, 32 * j, 32, 32);
            }
            else {
                img[j][3] = img[j][1];
            }
        }
    }
    int ac = 0;
    int ptn = 0;
    float px = Width - 16 * 3, py = 16, rz = 0, dx = 0, dy = 3;

    repeat() {
        x += vx;
        y += vy;
        if (x<r || x>Width - r)vx *= -1;
        if (y<r || y>Height - r)vy *= -1;

        px += dx;
        py += dy;
        if (py > Height - 16 * 3) {
            py = Height - 16 * 3;
            dx = -3;
            dy = 0;
            ptn = 1;
        }
        if (px < 16) {
            px = 16;
            dx = 0;
            dy = -3;
            ptn = 3;
        }
        if (py < 16) {
            py = 16;
            dx = 3;
            dy = 0;
            ptn = 2;
        }
        if (px > Width - 16 * 3) {
            px = Width - 16 * 3;
            dx = 0;
            dy = 3;
            ptn = 0;
        }
        //px = Width/2;
        //py = Height/2;

        clear(50, 50, 50);
        //éläpå`
        rectMode(LEFTTOP);
        noStroke();
        float len = 80;
        for (int j = 0; j < 6; j++) {
            for (int i = 0; i < 8; i++) {
                if ((j + i) % 2) {
                    fill(0, 80, 0);
                }
                else {
                    fill(0, 0, 0);
                }
                rect(len * i, len * j, len, len);
            }
        }
        //â~
        fill(255, 255, 255);
        stroke(250, 0, 0);
        strokeWeight(2);
        circle(x, y, r * 2);
        //ê¸ï™ÇP
        strokeWeight(9);
        stroke(255, 255, 0);
        line(60, 60, 340, 140);
        //ê¸ï™ÇQ
        strokeWeight(30);
        stroke(255, 0, 0);
        line(100, 300, 300, 100);
        //âÊëú
        rectMode(CENTER);
        int itvl = 6;//interval
        for (int j = 0; j < 2; j++) {
            for (int i = 0; i < 2; i++) {
                image(img[ptn][ac / itvl % 4], px + i * 32, py + j * 32);
            }
        }
        ++ac %= itvl * 4;
        //ÉeÉLÉXÉg
        fill(200, 200, 0);
        textSize(60);
        text(px, Width / 2 - 150, Height / 2);
        text(py, Width / 2, Height / 2);

        rz += -0.01f;
    }
}
#endif
