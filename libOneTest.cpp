#define G
#ifdef G
#include"framework.h"
#include"window.h"
#include"graphic.h"
#include"mathUtil.h"
#include"input.h"
#include"let.h"
program() {
    window(900, 900);
    let px = Width / 2;
    let radius = 200;
    let vx = 5;
    let deg = 0;
    while(notQuit) {
        px += vx;
        if (px < radius || px > Width - radius) {
            vx *= -1;
        }

        deg += 5;

        clear(200, 200, 200);

        strokeWeight(2);

        fill(255, 255, 255);
        circle(px, 450, radius*2);

        let mx = MouseX;
        let my = MouseY;
        rectMode(CENTER);
        angleMode(DEGREES);
        rect(mx, my, 100, 100, deg);

        fill(0, 0, 0);
        text("mx=" + mx, 0, 20);
        text("my=" + my, 0, 40);
    }
}
#endif

#ifdef F
#include"framework.h"
#include"window.h"
#include"graphic.h"
#include"mathUtil.h"
#include"input.h"
void gmain(){
    window(1600, 900, full);
    float rad = 0;
    font("HG明朝E");
    while (notQuit) {
        getInput();
        clear(250, 200, 0);
        //市松模様
        rad += 0.0025f;
        strokeWeight(0);
        for (int j = 0; j < 9; j++) {
            for (int i = 0; i < 16; i++) {
                if ((j + i) % 2 == 1) {
                    fill(0, 120, 0);
                }
                else {
                    fill(0, 0, 0);
                }
                rect(100 * i, 100 * j, 100, 100, rad);
            }
        }
        //円
        //float x = Width / 2, y = Height / 2;
        float x = MouseX, y = MouseY;
        strokeWeight(4);
        stroke(0, 0, 0);
        fill(250, 0, 0);
        circle(x, y, 400);
        fill(250, 250, 250);
        circle(x-15, y-5, 370);
        //テキスト
        textSize(140);
        fill(190, 190, 190);
        float ofst = 3;
        text("鬼滅の", x - 220 - ofst, y - ofst);
        text("命令書", x - 220 - ofst, y + 140 - ofst);
        fill(0, 0, 0);
        text("鬼滅の", x - 220, y);
        text("命令書", x - 220, y + 140);
    }
}
#endif

#ifdef E
#include"framework.h"
#include"window.h"
#include"graphic.h"
#include"mathUtil.h"
#include"input.h"
void gmain() {
    window(800, 800);
    repeat{
        clear(200, 200, 200);
        //stroke(255, 0, 0);
        strokeWeight(30);
        line(50, 50, 720, 720);
        fill(0, 200, 0);
        rectMode(CENTER);
        rect(200, 200, 200, 200);
        fill(200, 200, 0);
        circle(600, 600, 100 * 2);
    }
}
#endif

#ifdef D
#include"framework.h"
#include"window.h"
#include"graphic.h"
#include"mathUtil.h"
#include"input.h"
void gmain() {
    window(800, 800);
    while (notQuit) {
        getInput();

        clear(50, 50, 50);
        
        fill(220, 200, 200);
        rect(0, 0, Width, Height);
        
        mathAxis(1.1f);
        
        float mX = MathMouseX;
        float mY = MathMouseY;
        fill(255, 255, 255);
        mathCircle(mX, mY, 0.04f);
        mathLine(0, 0, mX, mY);
        mathLine(0, 0, mX, 0);
        mathLine(mX, 0, mX, mY);
        mathLine(0, mY, mX, mY);
        
        fill(0, 0, 0);
        text(mX, 0, 20);
        text(mY, 100, 20);
        text(sqrt(mX * mX + mY * mY), 200, 20);
    }
}


#endif

#ifdef C
#include"framework.h"
#include"window.h"
#include"graphic.h"
#include"mathUtil.h"
float PointStrokeWeight = 4;
float LineStrokeWeight = 0;
float f(float x) {
    return x*x*x;
}
void regularPolygon(int num) {
    angleMode(RADIANS);
    static float r = 0.0f;//radian for animation
    float radius = sin(r);
    r += 0.01f;
    float rad = 3.141592f * 2 / num;
    float sx = 1.0f * radius, sy = 0.0f, ex, ey;
    for (int i = 1; i <= num; i++) {
        ex = cos(rad * i) * radius;
        ey = sin(rad * i) * radius;
        stroke(0, 0, 0);
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
    stroke(255,0,0);
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
void animation() {
    static float px = maxScaleX();
    float speed = 0.01f * maxScaleX();
    px += speed;
    if (px > maxScaleX()) {
        px = -maxScaleX();
    }
    float py = f(px);
    stroke(130, 130, 130);
    strokeWeight(LineStrokeWeight);
    mathLine(px, 0, px, py);
    mathLine(0, py, px, py);
    stroke(255, 255, 0);

    strokeWeight(1);
    stroke(0, 0, 0);
    fill(255, 255, 255);
    mathCircle(px, py,0.03f);
}
void fan(float s, float e, float r) {
    angleMode(DEGREES);
    float sx = cos(s) * r;
    float sy = sin(s) * r;
    float ex = cos(e) * r;
    float ey = sin(e) * r;
    mathLine(0, 0, sx, sy);
    mathLine(0, 0, ex, ey);
    float lsx = sx, lsy = sy, lex, ley;
    for (float deg = s; deg < e; deg += 1) {
        lex = cos(deg+1) * r;
        ley = sin(deg+1) * r;
        mathLine(lsx, lsy, lex, ley);
        lsx = lex;
        lsy = ley;
    }
}
float changeMaxX() {
    static float ar = 0.0f;
    float maxScaleX = (cos(ar) * 0.5f + 0.5f) * 5.14f + 1.1f;
    ar += 0.002f;
    return maxScaleX;
}
void back() {
    fill(255, 200, 200);
    noStroke();
    rect(0, 0, Width, Height);
}

program() {
    window(800, 800, full);
    repeat() {
        clear(50, 50, 50);
        back();
        mathAxis(1.1f);
        graph();
        animation();
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
    while(notQuit) {
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
#include"input.h"
#include"mathUtil.h"
void gmain(){
    window(1600, 900);
    //四角形
    float deg = 45;
    //円
    float x = Width / 2, y = Height / 2, r = 10, vx = 5, vy = -3;
    //画像
    int allImg = loadImage("obake2.png");
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
    int logo = loadImage("logo.png");
    repeat(){
        getInput();

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
        angleMode(DEGREES);
        rectMode(CORNER);
        fill(0,0, 127);
        stroke(0, 255, 255);
        strokeWeight(1);
        rect(200, 200, 200, 200, deg);
        //円
        fill(255, 255, 255);
        stroke(0, 200, 0);
        strokeWeight(20);
        circle(MouseX, MouseY, 100.0f * 2);
        fill(0, 0, 0);
        textSize(80);
        text("制御文", MouseX-120, MouseY+40);
        //線分１
        strokeWeight(9);
        stroke(255, 255, 0);
        line(800, 60, 1340, 140);
        //線分２
        strokeWeight(30);
        stroke(255, 0, 0);
        line(800, 300, 1300, 100);
        //画像
        angleMode(RADIANS);
        rectMode(CENTER);
        image(logo, Width-220, Height-180);
        int itvl = 6;//interval
        for (int j = 0; j < 2; j++) {
            for (int i = 0; i < 2; i++) {
                image(img[ptn][ac / itvl % 4], px + i * 32, py + j * 32, rz);
            }
        }
        rz += -0.01f;
        ++ac %= itvl * 4;
        //テキスト
        fill(220, 220, 220);
        textSize(60);
        text(px, Width / 2 - 150, Height / 2);
        text(py, Width / 2, Height / 2);
        text(MouseX, 0, 60);
        text(MouseY, 0, 120);


    }
}
#endif
