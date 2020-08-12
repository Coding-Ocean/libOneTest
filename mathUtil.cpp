#include"graphic.h"
static float Cx = 0;
static float Cy = 0;
static float Unit = 0;
static float MaxScaleX = 0;
float maxScaleX() {
    return MaxScaleX;
}
void mathAxis(float maxScaleX) {
    Cx = Width / 2;
    Cy = Height / 2;
    MaxScaleX = maxScaleX;
    Unit = Cx / MaxScaleX;
    strokeWeight(1);
    stroke(0, 0, 0);
    line(0, Cy, Width, Cy);
    line(Cx, 0, Cx, Height);

    int ofst[3][4] = {
        15,25,35,45,//>100
        10,20,25,35,//>10
        5,15,15,25
    };
    float l = 5;
    if (MaxScaleX > 1000) {
    }
    else if (MaxScaleX > 100) {
        for (int i = 100; i < Cx / Unit; i+=100) {
            float sx = Unit * i;
            line(Cx + sx, Cy - l, Cx + sx, Cy + l);//x>0
            line(Cx - sx, Cy - l, Cx - sx, Cy + l);//x<0
            text(i, Cx + sx - 15, Cy + 25);
            text(-i, Cx - sx - 25, Cy + 25);
        }
        //scale y
        for (int i = 100; i < Cy / Unit; i+=100) {
            float sy = Unit * i;
            line(Cx - l, Cy - sy, Cx + l, Cy - sy);//y>0
            line(Cx - l, Cy + sy, Cx + l, Cy + sy);//y<0
            text(i, Cx - 35, Cy - sy + 10);
            text(-i, Cx - 45, Cy + sy + 10);
        }
    }
    else if (MaxScaleX > 10) {
        fill(0, 0, 0);
        //scale x
        for (int i = 10; i < Cx / Unit; i+=10) {
            float sx = Unit * i;
            line(Cx + sx, Cy - l, Cx + sx, Cy + l);//x>0
            line(Cx - sx, Cy - l, Cx - sx, Cy + l);//x<0
            text(i, Cx + sx - 10, Cy + 25);
            text(-i, Cx - sx - 20, Cy + 25);
        }
        //scale y
        for (int i = 10; i < Cy / Unit; i+=10) {
            float sy = Unit * i;
            line(Cx - l, Cy - sy, Cx + l, Cy - sy);//y>0
            line(Cx - l, Cy + sy, Cx + l, Cy + sy);//y<0
            text(i, Cx - 25, Cy - sy + 10);
            text(-i, Cx - 35, Cy + sy + 10);
        }
    }
    else {
        fill(0, 0, 0);
        //scale x
        for (int i = 1; i < Cx / Unit; i++) {
            float sx = Unit * i;
            line(Cx + sx, Cy - l, Cx + sx, Cy + l);//x>0
            line(Cx - sx, Cy - l, Cx - sx, Cy + l);//x<0
            text(i, Cx + sx - 5, Cy + 25);
            text(-i, Cx - sx - 15, Cy + 25);
        }
        //scale y
        for (int i = 1; i < Cy / Unit; i++) {
            float sy = Unit * i;
            line(Cx - l, Cy - sy, Cx + l, Cy - sy);//y>0
            line(Cx - l, Cy + sy, Cx + l, Cy + sy);//y<0
            text(i, Cx - 15, Cy - sy + 10);
            text(-i, Cx - 25, Cy + sy + 10);
        }
    }
    text(0, Cx - 15, Cy + 25);
}
void mathPoint(float x, float y) {
    point(Cx + x * Unit, Cy - y * Unit);
}
void mathCircle(float x, float y, float r) {
    circle(Cx + x * Unit, Cy - y * Unit, r * 2);
}
void mathLine(float sx, float sy, float ex, float ey) {
    line(Cx + sx * Unit, Cy - sy * Unit, Cx + ex * Unit, Cy - ey * Unit);
}
void mathImage(int img, float x, float y, float r) {
    image(img, Cx + x * Unit, Cy - y * Unit, r);
}
