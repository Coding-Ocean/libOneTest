#define R

//三角関数
#ifdef R
#include"framework.h"
#include"graphic.h"
#include"input.h"
#include"mathUtil.h"
#include"MATRIX.h"
//正三角形
int createEquilateral() {
    SHAPE_VERTEX v[] = {
        -sin(0),-cos(0),
        -sin(120),-cos(120),
        -sin(240),-cos(240)
    };
    return createShape(v, 3);
}
void gmain() {
    window(900, 900);
    float cx = width / 2;
    float cy = height / 2;
    angleMode(DEGREES);
    int sh = createEquilateral();
    float x = 0, y = 0, diameter = 50;
    float radius=450, angle = 0;
    repeat() {
        if (isPress(KEY_SPACE))angle += 1;
        else angle = 0;
        x = cx + radius * sin(angle);
        y = cy + radius * -cos(angle);
        clear(220, 220, 220);
        //line(cx, cy, x, y);
        //strokeWeight(2);
        //shape(sh, x, y, angle, 5);
        rectMode(CENTER);
        rect(x, y, 20, 20,angle);
        static float angl = 0;
        MATRIX m1,m2;
        m1.identity();
        m1.mulTranslate(width / 2, height / 2);
        m1.mulRotateZ(angl);
        m1.mulTranslate(100,0);

        m2.identity();
        m2.mulRotateZ(angl*2);
        m2.mulScale(100, 100);

        m1 = m1 * m2;

        angl += 1;
        shape(sh, m1);
    }
}
#endif
//自機
#ifdef P
#include"framework.h"
#include"graphic.h"
#include"input.h"
#include"mathUtil.h"
struct PLAYER_SHIP {
    int idx;
    float px, py, angle, size, vx, vy, rotSpeed, advSpeed;
};
int createPlayerShip() {
    SHAPE_VERTEX v[] = {
        sin(0),-cos(0),
        sin(120),-cos(120),
        0, 0.1f,
        sin(240), -cos(240)
    };
    return createShape(v, sizeof(v) / sizeof(SHAPE_VERTEX));
}
void init(struct PLAYER_SHIP& ps) {
    ps.idx = createPlayerShip();
    ps.px = Width / 2;
    ps.py = Height / 2;
    ps.angle = 0;
    ps.size = 30;
    ps.vx = 0;
    ps.vy = 0;
    ps.rotSpeed = 2;
    ps.advSpeed = 4;
}
void move(struct PLAYER_SHIP& ps) {
    /*
    if (isPress(KEY_A)) {
        ps.angle += -ps.rotSpeed;
    }
    if (isPress(KEY_D)) {
        ps.angle += ps.rotSpeed;
    }
    ps.vx = 0;
    ps.vy = 0;
    if (isPress(KEY_W)) {
        ps.vx = sin(ps.angle);
        ps.vy = -cos(ps.angle);
        ps.px += ps.vx * ps.advSpeed;
        ps.py += ps.vy * ps.advSpeed;
    }
    if (isPress(KEY_S)) {
        ps.vx = -sin(ps.angle);
        ps.vy = cos(ps.angle);
        ps.px += ps.vx * ps.advSpeed;
        ps.py += ps.vy * ps.advSpeed;
    }
    if (ps.py < -ps.size)ps.py = Height + ps.size;
    if (ps.py > Height + ps.size)ps.py = -ps.size;
    if (ps.px < -ps.size)ps.px = Width + ps.size;
    if (ps.px > Width + ps.size)ps.px = -ps.size;
    */
}
void draw(struct PLAYER_SHIP& ps) {
    stroke(200, 200, 200);
    fill(60, 120, 240);
    shape(ps.idx, ps.px, ps.py, ps.angle, ps.size);
}

struct PLAYER_BULLET {
    float px, py, angle, size, vx, vy, rotSpeed, advSpeed;
    int life;
    static int triggerCnt;
    static int shapeIdx;
    static const int num;
};
int PLAYER_BULLET::triggerCnt = 0;
int PLAYER_BULLET::shapeIdx = 0;
const int PLAYER_BULLET::num = 20;
int createStarShape() {
    //頂点位置
    angleMode(DEGREES);
    const int numVertices = 10;
    SHAPE_VERTEX vertices[numVertices];
    float divDeg = 360.0f / numVertices;
    for (int i = 0; i < numVertices; i++) {
        float radius = 0.4f + 0.4f * (i % 2);
        float deg = divDeg * i;
        vertices[i].x = sin(deg) * radius;
        vertices[i].y = cos(deg) * radius;
    }
    //シェープを作って番号を返す
    return createShape(vertices, numVertices);
}
void init(struct PLAYER_BULLET* pb) {
    pb->shapeIdx = createStarShape();
    pb->triggerCnt = -1;
    for (int i = 0; i < pb->num; i++) {
        pb[i].size = 10;
        pb[i].advSpeed = 6;
        pb[i].life = 0;
    }
}
void launch(struct PLAYER_BULLET* pb, float px, float py, float angle) {
    if (isPress(KEY_SPACE)) {
        if (++pb->triggerCnt % 10 == 0) {
            for (int i = 0; i < pb->num; i++) {
                if (pb[i].life == 0) {
                    pb[i].angle = angle;
                    pb[i].vx = sin(angle);
                    pb[i].vy = -cos(angle);
                    pb[i].px = px + pb[i].vx * 20;
                    pb[i].py = py + pb[i].vy * 20;
                    pb[i].life = 1;
                    break;
                }
            }
        }
    }
    else {
        pb->triggerCnt = -1;
    }
}
void move(struct PLAYER_BULLET* pb) {
    for (int i = 0; i < pb->num; i++) {
        if (pb[i].life) {
            pb[i].px += pb[i].vx * pb[i].advSpeed;
            pb[i].py += pb[i].vy * pb[i].advSpeed;
            if (pb[i].px < -pb[i].size || pb[i].py < -pb[i].size ||
                pb[i].px > Width+pb[i].size || pb[i].py > Height+pb[i].size) {
                pb[i].life = 0;
            }
        }
    }
}
void draw(struct PLAYER_BULLET* pb) {
    stroke(200, 200, 200);
    fill(240, 240, 0);
    for (int i = 0; i < pb->num; i++) {
        if (pb[i].life) {
            shape(pb->shapeIdx, pb[i].px, pb[i].py, pb[i].angle, pb[i].size);
        }
    }
}

void gmain() {
    window(800, 450);
    angleMode(DEGREES);
    struct PLAYER_SHIP playerShip;
    struct PLAYER_BULLET playerBullets[PLAYER_BULLET::num];
    init(playerShip);
    init(playerBullets);
    while (notQuit) {
        move(playerShip);
        launch(playerBullets, playerShip.px,playerShip.py,playerShip.angle);
        move(playerBullets);
        clear(50, 50, 50);
        stroke(200, 200, 200);
        line(0, Height / 2, Width, Height / 2);
        line(Width / 2, 0, Width / 2, Height);
        static float angle = 0;
        ps.px = Width / 2 + sin(angle) * 100;
        ps.py = Height / 2 + cos(angle) * 100;
        if (isPress(KEY_C))angle += 2;
        else angle = 0;

        draw(playerBullets);
        draw(playerShip);
    }
}
#endif

//サムネ用プログラム
#ifdef O
#include"framework.h"
#include"graphic.h"
#include"mathUtil.h"
void background() {
    //画像cube１面のひし形の対角線の半分の長さlx,ly
    //cubeの１辺の長さは80
    float lx = 69.28203f;//80*cos(30)
    float ly = 40;//80*sin(30)
    //ずらしながら描画していくときの距離
    float dx = lx * 2;
    float dy = ly * 3;
    //縦横に並べる個数
    int ny = 10;
    int nx = 15;
    //画像読み込み
    int imgs[2];
    imgs[0] = loadImage("cube0.png");
    imgs[1] = loadImage("cube1.png");
    //矩形描画モード
    rectMode(CENTER);
    clear(0, 0, 0);
    for (int j = 0; j < ny; j++) {
        for (int i = 0; i < nx; i++) {
            float x = (j % 2 * lx) + dx * i;
            float y = ly + dy * j;
            int idx = (j / 2 + i) % 2;
            image(imgs[idx], x, y);
        }
    }
}
void title() {
    //文字列
    font("UD デジタル 教科書体 NP-B");
    textSize(160);
    const char* str1 = "ゲームプログラミング講座";
    const char* str2 = "　　スタートします！";
    const char* str3 = "「#0 イントロダクション」";
    //文字位置
    float x = 120;
    float y = 300;
    float y2 = 200;
    float y3 = 500;
    //輪郭 contour
    float cx = 0;//ずらすベクトルｘ
    float cy = 0;//ずらすベクトルｙ
    float cw = 10;//ずらす量
    int n = 16;
    angleMode(DEGREES);
    float deg = 360.0f / n;
    for (int i = 0; i < n + 1; i++) {
        if (i < n) {
            //輪郭
            fill(20, 20, 20);
            cx = cos(deg * i) * cw;
            cy = sin(deg * i) * cw;
            text(str1, x + cx, y + cy);
            text(str2, x + cx, y + y2 + cy);
            text(str3, x + cx, y + y3 + cy);
        }
        else {
            //本体
            fill(255, 255, 255);
            text(str1, x, y);
            text(str2, x, y + y2);
            text(str3, x, y + y3);
        }
    }
}
void gmain() {
    window(1920, 1080, 1);
    clear(250, 250, 125);
    background();
    title();
    pause();
}
#endif
//鬼滅テスト
#ifdef N
#include"framework.h"
#include"graphic.h"
#include"input.h"
#include"mathUtil.h"
void cube(float x, float y, float radius) {
    float sx, sy, ex, ey, sr, r;
    sr = 90;
    sx = x + cos(sr) * radius;
    sy = y + sin(sr) * radius;
    for (int i = 0; i < 6; i++) {
        r = sr + 60 * (i + 1);
        ex = x + cos(r) * radius;
        ey = y + sin(r) * radius;
        line(sx, sy, ex, ey);
        sx = ex;
        sy = ey;
    }
    for (int i = 0; i < 3; i++) {
        r = sr + 120 * i;
        ex = x + cos(r) * radius;
        ey = y + sin(r) * radius;
        line(x, y, ex, ey);
    }
}
void gmain() {
    float radius = 90;
    angleMode(DEGREES);
    float lx = radius * cos(30);
    float ly = radius * sin(30);
    int nx = 12;
    int ny = 8;
    window((nx-1)*2*lx+lx, (ny-1)*3*ly+ly);
    clear(220, 220, 220);
    while (notQuit) {
        for (int j = 0; j < ny; j++) {
            for (int i = 0; i < nx; i++) {
                float x = lx * (j % 2) + lx * 2 * i;
                float y = ly + ly * 3 * j;
                cube(x, y, radius);
            }
        }
    }
}
#endif
//鬼滅・画像
#ifdef M
#include"framework.h"
#include"graphic.h"
void gmain() {
    //画像cube１面のひし形の対角線の半分の長さlx,ly
    //cubeの１辺の長さは80
    float lx = 69.28203f;//80*cos(30)
    float ly = 40;//80*sin(30)
    //ずらしながら描画していくときの距離
    float w = lx * 2;
    float h = ly * 3;
    //cubeがぴったり収まるような大きさのウィンドウにする
    int numX = 14;
    int numY = 9;
    window(
        int((numX - 1) * w + lx), 
        int((numY - 1) * h + ly)
    );
    //画像読み込み
    int imgs[2];
    imgs[0] = loadImage("cube0.png");
    imgs[1] = loadImage("cube1.png");
    //矩形描画モード
    rectMode(CENTER);
    clear(0, 0, 0);
    for (int j = 0; j < numY; j++) {
        for (int i = 0; i < numX; i++) {
            float x = (j % 2 * lx) + w * i;
            float y = ly + h * j;
            int idx = (j / 2 + i) % 2;
            image(imgs[idx], x, y);
        }
    }

    pause();
}
#endif
//鬼滅・カスタムシェイプ
#ifdef L
#include"framework.h"
#include"graphic.h"
#include"input.h"
#include"mathUtil.h"
#include"VECTOR3.h"
/*
正三角形ベースのcubeに見えるような図形を並べて描画する
*/
struct CUBE {
    //cubeの辺の長さ
    float len;
    //ひし形の対角線の半分の長さ
    float lx, ly;
    //
    int shapeIdx;
    //cubeとcubeの間隔
    float distX, distY;
    //縦横に並べる数
    int nx, ny;
    //windowの大きさ
    float winW, winH;
    CUBE() {
        angleMode(DEGREES);
        //ひし形の辺の長さ
        len = 100;
        //ひし形の対角線の半分の長さ
        lx = len * cos(30);
        ly = len * sin(30);
        //
        shapeIdx = 0;
        //cubeとcubeの間隔
        distX = lx * 2;
        distY = ly * 3;
        //縦横に並べる数
        nx = 11;
        ny = 7;
        //windowの大きさ
        winW = (nx - 1) * distX + lx;
        winH = (ny - 1) * distY + ly;
    }
    void createDiamondShape() {
        //ひし形をつくる
        SHAPE_VERTEX vertices[] = {
            0, 0,
            lx,-ly,
            0,-len,
            -lx,-ly,
        };
        shapeIdx = createShape(vertices, sizeof(vertices) / sizeof(SHAPE_VERTEX));
    }
    void draw(float x, float y, int colType) {
        //ひし形を120度ずつ回転描画してcubeに見せる
        if (colType == 0)fill(255, 190, 0);
        else fill(0, 120, 0);
        shape(shapeIdx, x, y, 0, 1);
        if (colType == 0)fill(0, 190, 0);
        else fill(255, 120, 0);
        shape(shapeIdx, x, y, 120, 1);
        if (colType == 0)fill(0, 150, 0);
        else fill(255, 80, 0);
        shape(shapeIdx, x, y, -120, 1);
    }
    void drawAll() {
        strokeWeight(2);
        for (int j = 0; j < ny; j++) {
            for (int i = 0; i < nx; i++) {
                float x = (j % 2 * lx) + distX * i;
                float y = ly + distY * j;
                int colType = (j / 2 + i) % 2;
                draw(x, y, colType);
            }
        }
    }
};
void gmain() {
    struct CUBE cube;
    window(cube.winW, cube.winH);
    cube.createDiamondShape();
    while (notQuit) {
        clear(220, 220, 220);
        //cube.draw(Width / 2, Height / 2, 1);
        cube.drawAll();
    }
}
#endif
//カスタムシェイプ
#ifdef K
#include"framework.h"
#include"graphic.h"
#include"input.h"
#include"mathUtil.h"
#include"VECTOR2.h"
//----------------------------------------------------------------------
// シェープの輪郭となる頂点位置を一筆書きとなるようにプログラムしていく
// 最初の頂点からトライアングルファンで塗りつぶせるように考慮する必要がある
//----------------------------------------------------------------------

//ひし形をつくる
int createDiamondShape() {
    //ひし形の対角線の半分の長さlx ly
    float lx = 0.5f;
    float ly = 0.7f;
    //頂点位置
    SHAPE_VERTEX vertices[] = {
        0, ly,
        lx, 0,
        0, -ly,
        -lx, 0,
    };
    //シェープを作って番号を返す
    return createShape(vertices, sizeof(vertices) / sizeof(SHAPE_VERTEX));
}

//星形をつくる
int createStarShape() {
    //頂点位置
    angleMode(DEGREES);
    const int numVertices = 10;
    SHAPE_VERTEX vertices[numVertices];
    float divDeg = 360.0f / numVertices;
    for (int i = 0; i < numVertices; i++) {
        float radius = 0.4f + 0.4f * (i % 2);
        float deg = divDeg * i;
        vertices[i].x = sin(deg) * radius;
        vertices[i].y = cos(deg) * radius;
    }
    //シェープを作って番号を返す
    return createShape(vertices, numVertices);
}


//角丸多角形
int createKadomaruShape(
    //扇型(角)の数
    int numCorners,
    //弧を分割する角度(輪郭の滑らかさ)
    int divDeg,
    //半径
    float radius,
    //扇型を中心から移動させる距離
    float vlen
) {
    angleMode(DEGREES);
    //扇型の中心角
    const int angle = 360 / numCorners;
    const int numVertices = (angle / divDeg + 1) * numCorners;
    //最初に頂点を用意する角度
    float offsetDeg = (180 - angle) / 2.0f;
    SHAPE_VERTEX* vertices = new SHAPE_VERTEX[numVertices];
    for (int i = 0; i < numVertices; i++) {
        int w = i / (numVertices / numCorners);
        float vx = -sin((float)angle * w) * vlen;
        float vy = -cos((float)angle * w) * vlen;
        float deg = offsetDeg + divDeg * (i - w);
        vertices[i].x = vx + cos(deg) * radius;
        vertices[i].y = vy + -sin(deg) * radius;
    }
    //　シェープを作って番号を返す
    int shapeIdx = createShape(vertices, numVertices);
    delete[] vertices;
    return shapeIdx;
}

//カプセルをつくる
int createCapsuleShape() {
    angleMode(DEGREES);
    //弧を分割する角度
    const int divDeg = 10;
    //半径
    float radius = 0.5f;
    const int numVertices = (180 / divDeg + 1) * 2;
    SHAPE_VERTEX vertices[numVertices];
    //上の半円
    float vy = -0.1f;
    for (int i = 0; i < numVertices / 2; i++) {
        float deg = (float)divDeg * i;
        vertices[i].x = cos(deg) * radius;
        vertices[i].y = vy + -sin(deg) * radius;
    }
    //下の半円
    vy = -vy;
    for (int i = numVertices / 2; i < numVertices; i++) {
        float deg = (float)divDeg * (i-1);
        vertices[i].x = cos(deg) * radius;
        vertices[i].y = vy + -sin(deg) * radius;
    }

    //　シェープを作って番号を返す
    return createShape(vertices, numVertices);
}

//おにぎり（角丸正三角形）をつくる
int createOnigiriShape() {
    angleMode(DEGREES);
    //曲線を分割する角度
    const int divDeg = 10;
    const int numVertices = (120 / divDeg + 1) * 3;
    SHAPE_VERTEX vertices[numVertices];
    float offsetDeg = 30;
    float radius = 0.5f;
    float vl = 0.1f;
    for (int i = 0; i < numVertices; i++) {
        int w = i / (numVertices / 3);
        float vx = -sin(120.0f * w) * vl;
        float vy = -cos(120.0f * w) * vl;
        float deg = offsetDeg + divDeg * (i-w);
        vertices[i].x = vx + cos(deg) * radius;
        vertices[i].y = vy + -sin(deg) * radius;
    }
/*
    //上の丸角
    float vx = -sin(0)*vl;
    float vy = -cos(0)*vl;
    for (int i = 0; i < numVertices / 3; i++) {
        float deg = offsetDeg + divDeg * i;
        vertices[i].x = vx + cos(deg) * radius;
        vertices[i].y = vy + -sin(deg) * radius;
    }
    //左下の丸角
    vx = -sin(120)*vl;
    vy = -cos(120)*vl;
    for (int i = numVertices / 3; i < numVertices / 3 * 2; i++) {
        float deg = offsetDeg + divDeg * (i - 1);
        vertices[i].x = vx + cos(deg) * radius;
        vertices[i].y = vy + -sin(deg) * radius;
    }
    //右下の丸角
    vx = -sin(240)*vl;
    vy = -cos(240)*vl;
    for (int i = numVertices / 3 * 2; i < numVertices; i++) {
        float deg = offsetDeg + divDeg * (i - 2);
        vertices[i].x = vx + cos(deg) * radius;
        vertices[i].y = vy + -sin(deg) * radius;
    }
*/
    //　シェープを作って番号を返す
    return createShape(vertices, numVertices);
}

//角丸正方形をつくる
int createKakumaruShape() {
    angleMode(DEGREES);
    //曲線を分割する角度
    const int divDeg = 10;
    //頂点数
    const int numVertices = (90 / divDeg + 1) * 4;
    SHAPE_VERTEX vertices[numVertices];
    //半径
    float radius = 0.3f;
    //中心から離す距離
    float vl = 0.3f;
    for (int i = 0; i < numVertices; i++) {
        int w = i / (numVertices / 4);
        float vx = cos(45.0f+90*w) * vl;
        float vy = -sin(45.0f+90*w) * vl;
        float deg = (float)divDeg * (i-w);
        vertices[i].x = vx + cos(deg) * radius;
        vertices[i].y = vy + -sin(deg) * radius;
    }
/*
    //右上の丸角
    float vx = cos(45) * vl;
    float vy = -sin(45) * vl;
    for (int i = 0; i < numVertices / 4; i++) {
        float deg = (float)divDeg * i;
        vertices[i].x = vx + cos(deg) * radius;
        vertices[i].y = vy + -sin(deg) * radius;
    }
    //左上の丸角
    vx = cos(135) * vl;
    vy = -sin(135) * vl;
    for (int i = numVertices / 4; i < numVertices / 4 * 2; i++) {
        float deg = (float)divDeg * (i - 1);
        vertices[i].x = vx + cos(deg) * radius;
        vertices[i].y = vy + -sin(deg) * radius;
    }
    //左下の丸角
    vx = cos(225) * vl;
    vy = -sin(225) * vl;
    for (int i = numVertices / 4 * 2; i < numVertices / 4 * 3; i++) {
        float deg = (float)divDeg * (i - 2);
        vertices[i].x = vx + cos(deg) * radius;
        vertices[i].y = vy + -sin(deg) * radius;
    }
    //左下の丸角
    vx = cos(315) * vl;
    vy = -sin(315) * vl;
    for (int i = numVertices / 4 * 3; i < numVertices; i++) {
        int debug = i / (numVertices / 4);
        float deg = (float)divDeg * (i - 3);
        vertices[i].x = vx + cos(deg) * radius;
        vertices[i].y = vy + -sin(deg) * radius;
    }
*/
    //　シェープを作って番号を返す
    return createShape(vertices, numVertices);
}

//ハート型をつくる
int createHeartShape() {
    angleMode(DEGREES);
    const int divDeg = 5;
    const int numVertices = 360 / divDeg;
    SHAPE_VERTEX vertices[numVertices];
    float scale = 1.0f / 24;
    for (int i = 0; i < numVertices; i++) {
        float deg = (float)divDeg * i;
        vertices[i].x = 
            16 * pow(sin(deg), 3) * scale;
        vertices[i].y =
           (-13 * cos(deg)
            + 5 * cos(2 * deg)
            + 2 * cos(3 * deg)
            + 1 * cos(4 * deg)) * scale;
    }
    //　シェープを作って番号を返す
    return createShape(vertices, numVertices);
}

void gmain() {
    window(1280, 720, full);
    const int n = 6;
    int shapes[n];
    COLOR colors[n];
    shapes[0] = createKadomaruShape(6, 10, 0.3f, 0.3f);
    //shapes[0] = createCapsuleShape();
    shapes[1] = createDiamondShape();
    shapes[2] = createOnigiriShape();
    shapes[3] = createStarShape();
    shapes[4] = createKakumaruShape();
    shapes[5] = createHeartShape();
    colors[0] = COLOR(255, 187, 187);
    colors[1] = COLOR(170, 221, 221);
    colors[2] = COLOR(153, 221, 255);
    colors[3] = COLOR(255, 255, 187);
    colors[4] = COLOR(221, 238, 170);
    colors[5] = COLOR(255, 187, 221);
    //描画パラメータ
    //縦横に並べる数
    float size = 15;
    stroke(128, 128, 128);
    float sw = 1;
    float deg = 0;
    bool rotateFlag = true;
    enum STATE {LEVEL1, LEVEL2, LEVEL3 };
    STATE state = STATE::LEVEL1;
    struct LEVEL {
        int nx, ny;
    };
    struct LEVEL level[3] = {
        6,1,
        6,3,
        8,5
    };
    int nx = level[state].nx;
    int ny = level[state].ny;
    while (notQuit) {
        switch (state) {
        case STATE::LEVEL1:
            if (isTrigger(KEY_D)) {
                state = STATE::LEVEL2;
                nx = level[state].nx;
                ny = level[state].ny;
            }
            break;
        case STATE::LEVEL2:
            if (isTrigger(KEY_A)) {
                state = STATE::LEVEL1;
                nx = level[state].nx;
                ny = level[state].ny;
            }
            if (isTrigger(KEY_D)) {
                state = STATE::LEVEL3;
                nx = level[state].nx;
                ny = level[state].ny;
            }
            break;
        case STATE::LEVEL3:
            if (isTrigger(KEY_D)) { 
                nx *= 2;
                ny *= 2;
                if (nx > 128) {
                    nx = 128;
                    ny = 60;
                }
            }
            if (isTrigger(KEY_LEFT) || isTrigger(KEY_A)) { 
                nx /= 2; 
                ny /= 2; 
                if (nx < 8) { 
                    state = STATE::LEVEL2;
                    nx = level[state].nx;
                    ny = level[state].ny;
                }
            }
            break;
        }
        //シェイプ同士の間隔
        float dx = Width / nx;
        float dy = Height / ny;
        size = dx / 2;
        //輪郭線の太さ
        if (isPress(KEY_W)) { 
            sw += 0.25f; 
        }
        if (isPress(KEY_S)) { 
            sw -= 0.25f; 
            if (sw < 0.0f) { sw = 0.0f; }
        }
        strokeWeight(sw);
        //回転するしない
        if (isTrigger(KEY_SPACE)) {
            rotateFlag = !rotateFlag;
        }
        if (rotateFlag) {
            deg += 1;
        }
        else {
            deg = 0;
        }
        //描画
        clear(255, 221, 238);
        for (int j = 0; j < ny; j++) {
            for (int i = 0; i < nx; i++) {
                int idx = (j + i) % n;
                float x = dx / 2 + dx * i;
                float y = dy / 2 + dy * j;
                int dirRot = 1 - idx % 2 * 2;
                fill(colors[idx]);
                shape(shapes[idx], x, y, deg*dirRot, size);
            }
        }
    }
}
#endif
//昔のRPGキャラアニメーション
#ifdef J
#include"framework.h"
#include"graphic.h"
#include"input.h"
program() {
    window(1600, 900);
    int img = loadImage("pipo-halloweenchara2016_26.png");
    int imgs[16];
    int animCnt = 0;
    int animIdx = 0;
    for (int i = 0; i < 16; i++) {
        int _i = i % 4;
        if (_i <= 2) {
            imgs[i] = cutImage(img, 32 * _i, 32 * (i / 4), 32, 32);
        }
        else {
            imgs[i] = imgs[i - 2];
        }
    }
    repeat() {
        if (isPress(KEY_S))     animIdx = ++animCnt / 10 % 4;
        else if (isPress(KEY_A))animIdx = ++animCnt / 10 % 4 + 4;
        else if (isPress(KEY_D))animIdx = ++animCnt / 10 % 4 + 8;
        else if (isPress(KEY_W))animIdx = ++animCnt / 10 % 4 + 12;
        else animCnt = 0;
        clear(50, 50, 50);
        image(imgs[animIdx], Width / 2 - 16, Height / 2 - 16);
    }
}
#endif
//うんこごりら
#ifdef I
#include"framework.h"
#include"graphic.h"
#include"input.h"
#include"rand.h"
#include"mathUtil.h"
void gmain() {
    window(1920, 1080, full);
    //画像読み込み
    int goriImg = loadImage("gorilla.png");
    int unchImg = loadImage("unchi.png");
    //モード設定
    rectMode(CENTER);
    angleMode(DEGREES);
    //構造体型
    struct DATA {
        float px;
        float py;
        float vx;
        float vy;
        int life;
    };
    //ゴリラデータ
    struct DATA gori;
    gori.px = 960;
    gori.py = 300;
    gori.vx = 5;
    //運固データ
    const int numUnch = 100;
    struct DATA unch[numUnch];
    for (int i = 0; i < numUnch; i++) {
        unch[i].life = 0;
        unch[i].vy = 10;
    }
    int triggerCnt = 0;
    int deg = 0;
    //ゲームループ
    while (notQuit) {
        //ゴリラの動き
        if (isPress(KEY_A)) {
            gori.px -= gori.vx;
        }
        if (isPress(KEY_D)) {
            gori.px += gori.vx;
        }
        gori.px += sin(deg);
        deg += 10;
        //雲子発射
        if (++triggerCnt % 20 == 0) {
            for (int i = 0; i < numUnch; i++) {
                if (unch[i].life == 0) {
                    unch[i].life = 1;
                    unch[i].px = gori.px + 10;
                    unch[i].py = gori.py + 100;
                    triggerCnt = 0;
                    break;
                }
            }
        }
        //雲子移動
        for (int i = 0; i < numUnch; i++) {
            if (unch[i].life == 1) {
                unch[i].py += unch[i].vy;
                if (unch[i].py > 1000) {
                    unch[i].life = 0;
                }
            }
        }
        //描画
        clear(150, 250, 150);
        for (int i = 0; i < numUnch; i++) {
            if (unch[i].life == 1) {
                fill(133, 100, 12);
                circle(unch[i].px, unch[i].py, 100);
                //image(unchImg, unch[i].px, unch[i].py, deg);
            }
        }
        image(goriImg, gori.px, gori.py);
    }
}
#endif
//じゃんけん 関数分割
#ifdef H
#include"framework.h"
#include"graphic.h"
#include"input.h"
#include"rand.h"
const int GAME_STATE_INIT = 0;
const int GAME_STATE_PLAY = 1;
const int GAME_STATE_RESULT = 2;
const int GU = 0;
const int CHOKI = 1;
const int PA = 2;
struct DATA {
    int gameState = GAME_STATE_INIT;
    //画像番号
    int playerGuImg = 0;
    int playerChokiImg = 0;
    int playerPaImg = 0;
    int pcGuImg = 0;
    int pcChokiImg = 0;
    int pcPaImg = 0;
    int circleImg = 0;
    int equalImg = 0;
    int circleSmallImg = 0;
    //プレイヤーデータ
    int playerImg = 0;
    float playerPx = 0;
    float playerPy = 0;
    int playerHand = 0;
    int playerWinCnt = 0;
    //パソコンデータ
    int pcImg = 0;
    float pcPx = 0;
    float pcPy = 0;
    int pcHand = 0;
    int pcWinCnt = 0;
    //判定結果
    int playerWinHand = 0;
    int resultImg = 0;
    float resultPx = 0;
    float resultPy = 0;
    int blinkCnt = 0;
};
void draw(struct DATA* data);
void loadImages(struct DATA* data) {
    data->playerGuImg = loadImage("playerGu.png");
    data->playerChokiImg = loadImage("playerChoki.png");
    data->playerPaImg = loadImage("playerPa.png");
    data->pcGuImg = loadImage("pcGu.png");
    data->pcChokiImg = loadImage("pcChoki.png");
    data->pcPaImg = loadImage("pcPa.png");
    data->circleImg = loadImage("circle.png");
    data->equalImg = loadImage("equal.png");
    data->circleSmallImg = loadImage("circleSmall.png");
}
void init(struct DATA* data) {
    //プレイヤーデータ
    data->playerImg = data->playerGuImg;
    data->playerPx = 225;
    data->playerPy = 225;
    data->playerHand = GU;
    data->playerWinCnt = 0;
    //パソコンデータ
    data->pcImg = data->pcGuImg;
    data->pcPx = 800 - 225;
    data->pcPy = 225;
    data->pcHand = GU;
    data->pcWinCnt = 0;
    //判定結果
    data->playerWinHand = 0;
    data->resultImg = data->equalImg;
    data->resultPx = -200;
    data->resultPy = 225;
    data->blinkCnt = 0;
    rectMode(CENTER);
    data->gameState = GAME_STATE_PLAY;
}
void playerHand(struct DATA* data) {
    //プレイヤーの手を決定
    if (isTrigger(KEY_A)) {
        data->playerImg = data->playerGuImg;
        data->playerHand = GU;
    }
    else if (isTrigger(KEY_S)) {
        data->playerImg = data->playerChokiImg;
        data->playerHand = CHOKI;
    }
    else if (isTrigger(KEY_D)) {
        data->playerImg = data->playerPaImg;
        data->playerHand = PA;
    }
}
void pcHand(struct DATA* data) {
    //パソコンの手を決定
    data->pcHand = getRand() % 3;
    if (data->pcHand == GU) {
        data->pcImg = data->pcGuImg;
        data->playerWinHand = PA;//playerが勝つ手を書き込んでおく
    }
    else if (data->pcHand == CHOKI) {
        data->pcImg = data->pcChokiImg;
        data->playerWinHand = GU;
    }
    else if (data->pcHand == PA) {
        data->pcImg = data->pcPaImg;
        data->playerWinHand = CHOKI;
    }
}
void judge(struct DATA* data) {
    //結果判定
    if (data->playerHand == data->pcHand) {
        data->resultImg = data->equalImg;
        data->resultPx = 400;
    }
    else if (data->playerHand == data->playerWinHand) {
        data->resultImg = data->circleImg;
        data->resultPx = data->playerPx;
        data->playerWinCnt++;
    }
    else {
        data->resultImg = data->circleImg;
        data->resultPx = data->pcPx;
        data->pcWinCnt++;
    }
    if (data->playerWinCnt >= 5 || data->pcWinCnt >= 5) {
        data->gameState = GAME_STATE_RESULT;
    }
}
void play(struct DATA* data) {
    if (isTrigger(KEY_A) || isTrigger(KEY_S) || isTrigger(KEY_D)) {
        playerHand(data);
        pcHand(data);
        judge(data);
    }
    draw(data);
}

void result(struct DATA* data) {
    //試合終了
    data->blinkCnt++;
    //もう一回
    if (isTrigger(KEY_SPACE)) {
        data->gameState = GAME_STATE_INIT;
    }
    draw(data);
}

void draw(struct DATA* data) {
    //描画
    clear(30, 60, 120);
    image(data->playerImg, data->playerPx, data->playerPy);
    image(data->pcImg, data->pcPx, data->pcPy);
    if (data->blinkCnt / 10 % 2 == 0) {
        image(data->resultImg, data->resultPx, data->resultPy);
    }
    for (int i = 0; i < data->playerWinCnt; i++) {
        image(data->circleSmallImg, data->playerPx - 80 + 40 * i, 100);
    }
    for (int i = 0; i < data->pcWinCnt; i++) {
        image(data->circleSmallImg, data->pcPx - 80 + 40 * i, 100);
    }
    if (data->gameState != GAME_STATE_RESULT) {
        text("ぐぅ→Ａ　ちょき→Ｓ　ぱぁ→Ｄ", 80, 360);
    }
    else {
        text("もう一回する→スペース", 120, 360);
    }
}

void gmain() {
    window(800, 450);
    struct DATA data;
    loadImages(&data);
    while (notQuit) {
        if (data.gameState == GAME_STATE_INIT) {
            init(&data);
        }else 
        if (data.gameState == GAME_STATE_PLAY) {
            play(&data);
        }else 
        if (data.gameState == GAME_STATE_RESULT) {
            result(&data);
        }
    }
}
#endif
//じゃんけん
#ifdef G
#include"framework.h"
#include"graphic.h"
#include"input.h"
#include"rand.h"
void gmain() {
    window(800, 450);
    //画像読み込み
    int playerGuImg = loadImage("playerGu.png");
    int playerChokiImg = loadImage("playerChoki.png");
    int playerPaImg = loadImage("playerPa.png");
    int pcGuImg = loadImage("pcGu.png");
    int pcChokiImg = loadImage("pcChoki.png");
    int pcPaImg = loadImage("pcPa.png");
    int circleImg = loadImage("circle.png");
    int equalImg = loadImage("equal.png");
    int circleSmallImg = loadImage("circleSmall.png");
    //0をGU,1をCHOKI, 2をPAとする
    const int GU = 0;
    const int CHOKI = 1;
    const int PA = 2;
    //プレイヤーデータ
    int playerImg = playerGuImg;
    float playerPx = 225;
    float playerPy = 225;
    int playerHand = GU;
    int playerWinCnt = 0;
    //パソコンデータ
    int pcImg = pcGuImg;
    float pcPx = 800 - 225;
    float pcPy = 225;
    int pcHand = GU;
    int pcWinCnt = 0;
    //判定結果
    int playerWinHand = 0;//pcの手をもとにplayerが勝つ手を書き込む
    int resultImg = equalImg;
    float resultPx = -200;
    float resultPy = 225;
    int blinkCnt = 0;
    rectMode(CENTER);
    while(notQuit) {
        //試合中か試合終了か判断
        if (playerWinCnt < 5 && pcWinCnt < 5) {
            //試合中
            if (isTrigger(KEY_A) || isTrigger(KEY_S) || isTrigger(KEY_D)) {
                //プレイヤーの手を決定
                if (isTrigger(KEY_A)) {
                    playerImg = playerGuImg;
                    playerHand = GU;
                }
                else if (isTrigger(KEY_S)) {
                    playerImg = playerChokiImg;
                    playerHand = CHOKI;
                }
                else if (isTrigger(KEY_D)) {
                    playerImg = playerPaImg;
                    playerHand = PA;
                }
                //パソコンの手を決定
                pcHand = getRand() % 3;
                if (pcHand == GU) {
                    pcImg = pcGuImg;
                    playerWinHand = PA;
                }
                else if (pcHand == CHOKI) {
                    pcImg = pcChokiImg;
                    playerWinHand = GU;
                }
                else if (pcHand == PA) {
                    pcImg = pcPaImg;
                    playerWinHand = CHOKI;
                }
                //結果判定
                if (playerHand == pcHand) {
                    resultImg = equalImg;
                    resultPx = 400;
                }
                else if (playerHand == playerWinHand) {
                    resultImg = circleImg;
                    resultPx = playerPx;
                    playerWinCnt++;
                }
                else {
                    resultImg = circleImg;
                    resultPx = pcPx;
                    pcWinCnt++;
                }
            }
        }
        else {
            //試合終了
            blinkCnt++;
            //もう一回
            if (isTrigger(KEY_SPACE)) {
                blinkCnt = 0;
                playerWinCnt = 0;
                pcWinCnt = 0;
                pcImg = pcGuImg;
                playerImg = playerGuImg;
                resultPx = -200;
            }
        }

        //描画
        clear(30, 60, 120);
        image(playerImg, playerPx, playerPy);
        image(pcImg, pcPx, pcPy);
        if (blinkCnt / 10 % 2 == 0) {
            image(resultImg, resultPx, resultPy);
        }
        for (int i = 0; i < playerWinCnt; i++) {
            image(circleSmallImg, playerPx - 80 + 40 * i, 100);
        }
        for (int i = 0; i < pcWinCnt; i++) {
            image(circleSmallImg, pcPx - 80 + 40 * i, 100);
        }
        if (blinkCnt==0) {
            text("ぐぅ→Ａ　ちょき→Ｓ　ぱぁ→Ｄ", 80, 360);
        }
        else {
            text("もう一回する→スペース", 120, 360);
        }
    }
}
#endif
//鬼滅の命令書
#ifdef F
#include"framework.h"
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
//テスト実験用
#ifdef E
#include"framework.h"
#include"graphic.h"
#include"input.h"
#include"mathUtil.h"
bool reflect(float vx, float vy, float rs, float* x, float* y,float* dx, float* dy) {
    float sqlen = vx * vx + vy * vy;
    if (sqlen >= rs * rs) {
        return 0;
    }
    //当たってない位置に戻す
    float l = sqrt(vx * vx + vy * vy);
    vx /= l;
    vy /= l;
    *x += vx * (rs - l);
    *y += vy * (rs - l);
    //反射ベクトルを求める
    float len = -*dx * vx + -*dy * vy;
    float vx2 = vx * len * 2;
    float vy2 = vy * len * 2;
    *dx = *dx + vx2;
    *dy = *dy + vy2;
    return 1;
}
program(){
    window(320,320);
    //rect data : left top right bottom width height
    float l, t, r, b, w, h;
    w = 20;
    h = 20;
    l = Width/2-w/2;
    t = Height/2-h/2;
    //circle data : posX posY radius dirX dirY
    float x, y, rs, dx, dy;
    rs = 10;
    x = rs + 10;
    y = rs + 20;
    dx = 3;
    dy = 3;
    //ブロックの角と円の中心までのベクトル
    float vx, vy;
    repeat(){
        //円移動
        x += dx;
        y += dy;
        //四角形移動
        if (isPress(KEY_A))l += -2;
        if (isPress(KEY_D))l += 2;
        if (isPress(KEY_W))t += -2;
        if (isPress(KEY_S))t += 2;
        r = l + w;
        b = t + h;

        //円とウィドウ枠との当たり判定
        if (x < rs) {
            x = rs;
            dx = -dx;
        }
        if (x > Width - rs) {
            x = Width - rs;
            dx = -dx;
        }
        if (y < rs) {
            y = rs;
            dy *= -1;
        }
        if (y > Height - rs) {
            y = Height - rs;
            dy *= -1;
        }
        //当たり判定
        fill(255, 255, 255);
        if (x >= l && x <= r && y < t && y + rs > t) {
            //↑ブロックの上辺と当たった
            fill(255, 0, 0, 128);
            //食い込んだ分だけ追い出す
            y += t - (y + rs);
            dy *= -1;
        }
        else if (x >= l && x <= r && y > b && y - rs < b) {
            //↑ブロックの下辺と当たった
            fill(255, 0, 0, 128);
            y += b - (y - rs);
            dy *= -1;
        }
        else if (x < l && x+rs > l && y >= t && y <= b) {
            //↑ブロックの左辺と当たった
            fill(255, 0, 0, 128);
            x += l - (x + rs);
            dx *= -1;
        }
        else if (x > r && x - rs < r && y >= t && y <= b) {
            //↑ブロックの左辺と当たった
            fill(255, 0, 0, 128);
            x += r - (x - rs);
            dx *= -1;
        }
        else if (x < l && y < t) {
            //↑ブロック左上の領域にいる
            vx = x - l;
            vy = y - t;
            if (reflect(vx, vy, rs, &x, &y, &dx, &dy)) {
                //↑ブロック左上角と当たった
                fill(0, 255, 0, 128);

            }
        }
        else if (x < l && y > b) {
            //↑ブロック左下の領域にいる
            vx = x - l;
            vy = y - b;
            if (reflect(vx, vy, rs, &x, &y, &dx, &dy)) {
                //↑ブロック左下角と当たった
                fill(0, 255, 0, 128);
            }
        }
        else if (x > r && y < t) {
            //↑ブロック右上の領域にいる
            vx = x - r;
            vy = y - t;
            if (reflect(vx, vy, rs, &x, &y, &dx, &dy)) {
                //↑ブロック右上角と当たった
                fill(0, 0, 255, 128);
            }
        }
        else if (x > r && y > b) {
            //↑ブロック右下の領域にいる
            vx = x - r;
            vy = y - b;
            if (reflect(vx, vy, rs, &x, &y, &dx, &dy)) {
                //↑ブロック右下角と当たった
                fill(0, 0, 255, 128);
            }
        }
        //fill(255, 255, 255);
        //描画
        clear(240, 200, 200);
        circle(x, y, rs * 2);
        rect(l, t, w, h);
    }
}
#endif
//数学 座標
#ifdef D
#include"framework.h"
#include"graphic.h"
#include"mathUtil.h"
#include"input.h"
#include"var.h"
void gmain() {
    window(800, 800);
    while (notQuit) {
        getInput();

        clear(220, 220, 220);
        //clear(50, 50, 50);
        //fill(220, 200, 200);
        //rect(0, 0, Width, Height);
        
        mathAxis(1.1f);
        
        float mX = MathMouseX;
        float mY = MathMouseY;
        mathLine(0, 0, mX, mY);
        mathLine(0, 0, mX, 0);
        mathLine(mX, 0, mX, mY);
        mathLine(0, mY, mX, mY);
        fill(255, 255, 255, 128);
        mathCircle(mX, mY, 0.2f);
        
        fill(0, 0, 0);
        text("x:"+(var)mX, 0, 20);
        text("y:"+(var)mY, 0, 40);
        text("l:"+(var)sqrt(mX * mX + mY * mY), 0, 60);
    }
}


#endif
//関数グラフ
#ifdef C
#include"framework.h"
#include"graphic.h"
#include"mathUtil.h"
float PointStrokeWeight = 4;
float LineStrokeWeight = 2;
float f(float x) {
    return x*x;
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
        mathAxis(3.14f);
        graph();
        animation();
    }
}
#endif
//円と円の当たり判定
#ifdef B
#include"framework.h"
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
//最初のテスト
#ifdef A
#include"framework.h"
#include"graphic.h"
#include"input.h"
#include"mathUtil.h"
#include"rand.h"
#include"var.h"
void gmain(){
    window(1600, 900, full);
    //四角形
    float deg = 45;
    //円
    //float x = Width / 2, y = Height / 2, r = 10, vx = 5, vy = -3;
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
    //setRandSeed();
    int random[5] = { 0 };
    float randomf = 0;

    while(notQuit){

        //x += vx;
        //y += vy;
        //if (x<r || x>Width - r)vx *= -1;
        //if (y<r || y>Height - r)vy *= -1;

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
        fill(0, 0, 127);
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
        //rz += -0.01f;
        ++ac %= itvl * 4;
        //テキスト
        fill(220, 220, 220);
        textSize(60);
        text(px, Width / 2 - 150, Height / 2);
        text(py, Width / 2, Height / 2);
        text(MouseX, 0, 60);
        text(MouseY, 0, 120);
        //乱数テスト
        // 取得
        if (isTrigger(KEY_Z)) { 
            for (int i = 0; i < 5; i++) {
                random[i] = getRandInt(9);
            }
            randomf = getRandFloat(-5,5);
        }
        // 表示
        for (int i = 0; i < 5; i++) {
            text(random[i], 30.0f*i, 240.0f);
        }
        text("実数="+(var)randomf, 0, 300);
    }
}
#endif
