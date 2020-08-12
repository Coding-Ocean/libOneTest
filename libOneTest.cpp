#define C

#ifdef C
#include<cmath>
#include"framework.h"
#include"window.h"
#include"graphic.h"
#include"mathUtil.h"
float PointStrokeWeight = 6;
float LineStrokeWeight = 0;
float f(float x) {
    return x*x*x;
}
void regularPolygon(int num) {
    static float r = 0.0f;//radian for animation
    float radius = sin(r);
    r += 0.01f;
    float rad = 3.141592f * 2 / num;
    float sx = 1.0f * radius, sy = 0.0f, ex, ey;
    for (int i = 1; i <= num; i++) {
        ex = cos(rad * i) * radius;
        ey = sin(rad * i) * radius;
        stroke(0, 200, 0);
        strokeWeight(PointStrokeWeight);
        mathPoint(sx, sy);
        strokeWeight(LineStrokeWeight);
        mathLine(sx, sy, ex, ey);
        sx = ex;
        sy = ey;
    }
}
void graph() {
    //Graph
    float inc = 0.025f * maxScaleX();//ポイントとポイントの間隔
    float x, y, ex, ey;
    stroke(0, 0, 255);
    for (x = 0; x < maxScaleX(); x += inc) {
        //ｘ＝０に必ずポイントを描画するため左右を分けている
        //ｘ＞０
        y = f(x);
        strokeWeight(PointStrokeWeight);
        mathPoint(x, y);
        ex = x + inc;
        ey = f(ex);
        strokeWeight(LineStrokeWeight);
        mathLine(x, y, ex, ey);
        //ｘ＜０
        y = f(-x);
        strokeWeight(PointStrokeWeight);
        mathPoint(-x, y);
        ex = -x - inc;
        ey = f(ex);
        strokeWeight(LineStrokeWeight);
        mathLine(-x, y, ex, ey);
    }
}
void animation(int img) {
    static float px = maxScaleX();
    float speed = 0.01f * maxScaleX();
    px += speed;
    if (px > maxScaleX()) {
        px = -maxScaleX();
    }
    float py = f(px);
    stroke(190, 190, 190);
    strokeWeight(LineStrokeWeight);
    mathLine(px, 0, px, py);
    mathLine(0, py, px, py);
    stroke(255, 255, 0);
    //必ずポイントを描く
    strokeWeight(10);
    mathPoint(px, py);
    rectMode(CENTER);
    static unsigned ac = 0;
    mathImage(img, px, py);
}
float changeMaxX() {
    static float ar = 0.0f;
    float maxScaleX = (cos(ar) * 0.5f + 0.5f) * 5.14f + 1.1f;
    ar += 0.002f;
    return maxScaleX;
}

void gmain() {
    window(800, 800);
    float r = 0;
    int _img = loadImage("obake3.png");
    int img[2] = { 
        cutImage(_img, 0, 0, 32, 32),
        cutImage(_img, 32, 0, 32, 32) 
    };
    unsigned ac = 0;
    float scale = 4.1f;
    float x, y;

    struct DATA {
        int flag = 0;
        float px = 0;
        float py = 0;
        float dx = 0;
        float dy = 0;
    };
    DATA blt[50];
    unsigned cnt = 0;
    repeat() {
        clear(210, 200, 200);
        line(0, 0, 0, Height);
        line(0, 0, Width, 0);
        line(Width, 0, Width, Height);
        line(0, Height, Width, Height);
        //mathAxis(changeMaxX());
        mathAxis(scale);
        //scale += 0.01f*maxScaleX();
        //regularPolygon(6);
        graph();
        animation(img[0]);

        //三角関数
        x = cos(r);
        y = sin(r);
        r += 0.01f;
        if (r > 3.141592f * 2)r -= 3.141592f * 2;

        stroke(0, 0, 0);
        strokeWeight(1);
        fill(255, 255, 0);
        mathCircle(x, y, 10);
        rectMode(CENTER);
        mathImage(img[0], x, y-0.01f);
        stroke(170, 170, 170);
        strokeWeight(2);
        mathLine(x, 0, x, y);
        mathLine(0, 0, x, y);

        x *= 2;
        y *= 2;
        stroke(0, 0, 0);
        strokeWeight(1);
        fill(255, 255, 0);
        mathCircle(x, y, 10);
        rectMode(CENTER);
        mathImage(img[0], x, y - 0.01f);
        stroke(170, 170, 170);
        strokeWeight(2);
        mathLine(x, 0, x, y);
        mathLine(0, 0, x, y);

        //一発選んで発射準備
        if (++cnt % 10 == 0) {
            cnt = 0;
            for (int i = 0; i < 50; i++) {
                if (blt[i].flag == 0) {
                    blt[i].flag = 1;
                    blt[i].px = x;
                    blt[i].py = y;
                    blt[i].dx = x * 0.02f * maxScaleX();
                    blt[i].dy = y * 0.02f * maxScaleX();
                    break;
                }
            }
        }
        //発射済みの弾を移動。ウィンドウの外に出たら消す。
        for (int i = 0; i < 50; i++) {
            if (blt[i].flag) {
                blt[i].px += blt[i].dx;
                blt[i].py += blt[i].dy;
                if (blt[i].px < -maxScaleX() || blt[i].px > maxScaleX() ||
                    blt[i].py > maxScaleY() || blt[i].py < -maxScaleY()) {
                    blt[i].flag = 0;
                }
                mathImage(img[0], blt[i].px, blt[i].py);
                strokeWeight(4);
                mathLine(blt[i].px, blt[i].py, blt[i].px + blt[i].dx * 20, blt[i].py + blt[i].dy * 20);
            }
        }
        
        fill(0, 0, 0);
        text(r , 0, 20);
    }
}


#endif

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
        //四角形
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
        //円
        fill(255, 255, 255);
        stroke(250, 0, 0);
        strokeWeight(2);
        circle(x, y, r * 2);
        //線分１
        strokeWeight(9);
        stroke(255, 255, 0);
        line(60, 60, 340, 140);
        //線分２
        strokeWeight(30);
        stroke(255, 0, 0);
        line(100, 300, 300, 100);
        //画像
        rectMode(CENTER);
        int itvl = 6;//interval
        for (int j = 0; j < 2; j++) {
            for (int i = 0; i < 2; i++) {
                image(img[ptn][ac / itvl % 4], px + i * 32, py + j * 32);
            }
        }
        ++ac %= itvl * 4;
        //テキスト
        fill(200, 200, 0);
        textSize(60);
        text(px, Width / 2 - 150, Height / 2);
        text(py, Width / 2, Height / 2);

        rz += -0.01f;
    }
}
#endif
