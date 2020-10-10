#define E

//�̂�RPG�L�����A�j���[�V����
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
//���񂱂����
#ifdef I
#include"framework.h"
#include"graphic.h"
#include"input.h"
#include"rand.h"
#include"mathUtil.h"
void gmain() {
    window(1920, 1080, full);
    //�摜�ǂݍ���
    int goriImg = loadImage("gorilla.png");
    int unchImg = loadImage("unchi.png");
    //���[�h�ݒ�
    rectMode(CENTER);
    angleMode(DEGREES);
    //�\���̌^
    struct DATA {
        float px;
        float py;
        float vx;
        float vy;
        int life;
    };
    //�S�����f�[�^
    struct DATA gori;
    gori.px = 960;
    gori.py = 300;
    gori.vx = 5;
    //�^�Ńf�[�^
    const int numUnch = 100;
    struct DATA unch[numUnch];
    for (int i = 0; i < numUnch; i++) {
        unch[i].life = 0;
        unch[i].vy = 10;
    }
    int triggerCnt = 0;
    int deg = 0;
    //�Q�[�����[�v
    while (notQuit) {
        //�S�����̓���
        if (isPress(KEY_A)) {
            gori.px -= gori.vx;
        }
        if (isPress(KEY_D)) {
            gori.px += gori.vx;
        }
        gori.px += sin(deg);
        deg += 10;
        //�_�q����
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
        //�_�q�ړ�
        for (int i = 0; i < numUnch; i++) {
            if (unch[i].life == 1) {
                unch[i].py += unch[i].vy;
                if (unch[i].py > 1000) {
                    unch[i].life = 0;
                }
            }
        }
        //�`��
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

//����񂯂� �֐�����
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
    //�摜�ǂݍ���
    int playerGuImg = 0;
    int playerChokiImg = 0;
    int playerPaImg = 0;
    int pcGuImg = 0;
    int pcChokiImg = 0;
    int pcPaImg = 0;
    int circleImg = 0;
    int equalImg = 0;
    int circleSmallImg = 0;
    //�v���C���[�f�[�^
    int playerImg = 0;
    float playerPx = 0;
    float playerPy = 0;
    int playerHand = 0;
    int playerWinCnt = 0;
    //�p�\�R���f�[�^
    int pcImg = 0;
    float pcPx = 0;
    float pcPy = 0;
    int pcHand = 0;
    int pcWinCnt = 0;
    //���茋��
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
    //�v���C���[�f�[�^
    data->playerImg = data->playerGuImg;
    data->playerPx = 225;
    data->playerPy = 225;
    data->playerHand = GU;
    data->playerWinCnt = 0;
    //�p�\�R���f�[�^
    data->pcImg = data->pcGuImg;
    data->pcPx = 800 - 225;
    data->pcPy = 225;
    data->pcHand = GU;
    data->pcWinCnt = 0;
    //���茋��
    data->playerWinHand = 0;
    data->resultImg = data->equalImg;
    data->resultPx = -200;
    data->resultPy = 225;
    data->blinkCnt = 0;
    rectMode(CENTER);
    data->gameState = GAME_STATE_PLAY;
}
void playerHand(struct DATA* data) {
    //�v���C���[�̎������
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
    //�p�\�R���̎������
    data->pcHand = getRand() % 3;
    if (data->pcHand == GU) {
        data->pcImg = data->pcGuImg;
        data->playerWinHand = PA;//player���������������ł���
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
    //���ʔ���
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
    //�����I��
    data->blinkCnt++;
    //�������
    if (isTrigger(KEY_SPACE)) {
        data->gameState = GAME_STATE_INIT;
    }
    draw(data);
}

void draw(struct DATA* data) {
    //�`��
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
        text("�������`�@���傫���r�@�ς����c", 80, 360);
    }
    else {
        text("������񂷂遨�X�y�[�X", 120, 360);
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

//����񂯂�
#ifdef G
#include"framework.h"
#include"graphic.h"
#include"input.h"
#include"rand.h"
void gmain() {
    window(800, 450);
    //�摜�ǂݍ���
    int playerGuImg = loadImage("playerGu.png");
    int playerChokiImg = loadImage("playerChoki.png");
    int playerPaImg = loadImage("playerPa.png");
    int pcGuImg = loadImage("pcGu.png");
    int pcChokiImg = loadImage("pcChoki.png");
    int pcPaImg = loadImage("pcPa.png");
    int circleImg = loadImage("circle.png");
    int equalImg = loadImage("equal.png");
    int circleSmallImg = loadImage("circleSmall.png");
    //0��GU,1��CHOKI, 2��PA�Ƃ���
    const int GU = 0;
    const int CHOKI = 1;
    const int PA = 2;
    //�v���C���[�f�[�^
    int playerImg = playerGuImg;
    float playerPx = 225;
    float playerPy = 225;
    int playerHand = GU;
    int playerWinCnt = 0;
    //�p�\�R���f�[�^
    int pcImg = pcGuImg;
    float pcPx = 800 - 225;
    float pcPy = 225;
    int pcHand = GU;
    int pcWinCnt = 0;
    //���茋��
    int playerWinHand = 0;//pc�̎�����Ƃ�player���������������
    int resultImg = equalImg;
    float resultPx = -200;
    float resultPy = 225;
    int blinkCnt = 0;
    rectMode(CENTER);
    while(notQuit) {
        //�������������I�������f
        if (playerWinCnt < 5 && pcWinCnt < 5) {
            //������
            if (isTrigger(KEY_A) || isTrigger(KEY_S) || isTrigger(KEY_D)) {
                //�v���C���[�̎������
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
                //�p�\�R���̎������
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
                //���ʔ���
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
            //�����I��
            blinkCnt++;
            //�������
            if (isTrigger(KEY_SPACE)) {
                blinkCnt = 0;
                playerWinCnt = 0;
                pcWinCnt = 0;
                pcImg = pcGuImg;
                playerImg = playerGuImg;
                resultPx = -200;
            }
        }

        //�`��
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
            text("�������`�@���傫���r�@�ς����c", 80, 360);
        }
        else {
            text("������񂷂遨�X�y�[�X", 120, 360);
        }
    }
}
#endif

//�S�ł̖��ߏ�
#ifdef F
#include"framework.h"
#include"graphic.h"
#include"mathUtil.h"
#include"input.h"
void gmain(){
    window(1600, 900, full);
    float rad = 0;
    font("HG����E");
    while (notQuit) {
        getInput();
        clear(250, 200, 0);
        //�s���͗l
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
        //�~
        //float x = Width / 2, y = Height / 2;
        float x = MouseX, y = MouseY;
        strokeWeight(4);
        stroke(0, 0, 0);
        fill(250, 0, 0);
        circle(x, y, 400);
        fill(250, 250, 250);
        circle(x-15, y-5, 370);
        //�e�L�X�g
        textSize(140);
        fill(190, 190, 190);
        float ofst = 3;
        text("�S�ł�", x - 220 - ofst, y - ofst);
        text("���ߏ�", x - 220 - ofst, y + 140 - ofst);
        fill(0, 0, 0);
        text("�S�ł�", x - 220, y);
        text("���ߏ�", x - 220, y + 140);
    }
}
#endif

//�e�X�g�����p
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
    //�������ĂȂ��ʒu�ɖ߂�
    float l = sqrt(vx * vx + vy * vy);
    vx /= l;
    vy /= l;
    *x += vx * (rs - l);
    *y += vy * (rs - l);
    //���˃x�N�g�������߂�
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
    //�u���b�N�̊p�Ɖ~�̒��S�܂ł̃x�N�g��
    float vx, vy;
    repeat(){
        //�~�ړ�
        x += dx;
        y += dy;
        //�l�p�`�ړ�
        if (isPress(KEY_A))l += -2;
        if (isPress(KEY_D))l += 2;
        if (isPress(KEY_W))t += -2;
        if (isPress(KEY_S))t += 2;
        r = l + w;
        b = t + h;

        //�~�ƃE�B�h�E�g�Ƃ̓����蔻��
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
        //�����蔻��
        fill(255, 255, 255);
        if (x >= l && x <= r && y < t && y + rs > t) {
            //���u���b�N�̏�ӂƓ�������
            fill(255, 0, 0, 128);
            //�H�����񂾕������ǂ��o��
            y += t - (y + rs);
            dy *= -1;
        }
        else if (x >= l && x <= r && y > b && y - rs < b) {
            //���u���b�N�̉��ӂƓ�������
            fill(255, 0, 0, 128);
            y += b - (y - rs);
            dy *= -1;
        }
        else if (x < l && x+rs > l && y >= t && y <= b) {
            //���u���b�N�̍��ӂƓ�������
            fill(255, 0, 0, 128);
            x += l - (x + rs);
            dx *= -1;
        }
        else if (x > r && x - rs < r && y >= t && y <= b) {
            //���u���b�N�̍��ӂƓ�������
            fill(255, 0, 0, 128);
            x += r - (x - rs);
            dx *= -1;
        }
        else if (x < l && y < t) {
            //���u���b�N����̗̈�ɂ���
            vx = x - l;
            vy = y - t;
            if (reflect(vx, vy, rs, &x, &y, &dx, &dy)) {
                //���u���b�N����p�Ɠ�������
                fill(0, 255, 0, 128);

            }
        }
        else if (x < l && y > b) {
            //���u���b�N�����̗̈�ɂ���
            vx = x - l;
            vy = y - b;
            if (reflect(vx, vy, rs, &x, &y, &dx, &dy)) {
                //���u���b�N�����p�Ɠ�������
                fill(0, 255, 0, 128);
            }
        }
        else if (x > r && y < t) {
            //���u���b�N�E��̗̈�ɂ���
            vx = x - r;
            vy = y - t;
            if (reflect(vx, vy, rs, &x, &y, &dx, &dy)) {
                //���u���b�N�E��p�Ɠ�������
                fill(0, 0, 255, 128);
            }
        }
        else if (x > r && y > b) {
            //���u���b�N�E���̗̈�ɂ���
            vx = x - r;
            vy = y - b;
            if (reflect(vx, vy, rs, &x, &y, &dx, &dy)) {
                //���u���b�N�E���p�Ɠ�������
                fill(0, 0, 255, 128);
            }
        }
        //fill(255, 255, 255);
        //�`��
        clear(240, 200, 200);
        circle(x, y, rs * 2);
        rect(l, t, w, h);
    }
}
#endif

//���w ���W
#ifdef D
#include"framework.h"
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
        mathLine(0, 0, mX, mY);
        mathLine(0, 0, mX, 0);
        mathLine(mX, 0, mX, mY);
        mathLine(0, mY, mX, mY);
        fill(255, 255, 255, 128);
        mathCircle(mX, mY, 0.2f);
        
        fill(0, 0, 0);
        text(mX, 0, 20);
        text(mY, 100, 20);
        text(sqrt(mX * mX + mY * mY), 200, 20);
    }
}


#endif

//�֐��O���t
#ifdef C
#include"framework.h"
#include"graphic.h"
#include"mathUtil.h"
float PointStrokeWeight = 4;
float LineStrokeWeight = 2;
float f(float x) {
    return x;
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
    float inc = 0.025f * maxScaleX();//�|�C���g�ƃ|�C���g�̊Ԋu
    float x, y, ex, ey;
    stroke(255,0,0);
    for (x = 0; x < maxScaleX(); x += inc) {
        //�����O�ɕK���|�C���g��`�悷�邽�ߍ��E�𕪂��Ă���
        //�����O
        y = f(x);
        strokeWeight(PointStrokeWeight);
        mathPoint(x, y);
        ex = x + inc;
        ey = f(ex);
        strokeWeight(LineStrokeWeight);
        mathLine(x, y, ex, ey);
        //�����O
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

//�~�Ɖ~�̓����蔻��
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

//�ŏ��̃e�X�g
#ifdef A
#include"framework.h"
#include"graphic.h"
#include"input.h"
#include"mathUtil.h"
#include"rand.h"
#include"var.h"
void gmain(){
    window(1600, 900, full);
    //�l�p�`
    float deg = 45;
    //�~
    //float x = Width / 2, y = Height / 2, r = 10, vx = 5, vy = -3;
    //�摜
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
        //�l�p�`
        angleMode(DEGREES);
        rectMode(CORNER);
        fill(0, 0, 127);
        stroke(0, 255, 255);
        strokeWeight(1);
        rect(200, 200, 200, 200, deg);
        //�~
        fill(255, 255, 255);
        stroke(0, 200, 0);
        strokeWeight(20);
        circle(MouseX, MouseY, 100.0f * 2);
        fill(0, 0, 0);
        textSize(80);
        text("���䕶", MouseX-120, MouseY+40);
        //�����P
        strokeWeight(9);
        stroke(255, 255, 0);
        line(800, 60, 1340, 140);
        //�����Q
        strokeWeight(30);
        stroke(255, 0, 0);
        line(800, 300, 1300, 100);
        //�摜
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
        //�e�L�X�g
        fill(220, 220, 220);
        textSize(60);
        text(px, Width / 2 - 150, Height / 2);
        text(py, Width / 2, Height / 2);
        text(MouseX, 0, 60);
        text(MouseY, 0, 120);
        //�����e�X�g
        // �擾
        if (isTrigger(KEY_Z)) { 
            for (int i = 0; i < 5; i++) {
                random[i] = getRandInt(9);
            }
            randomf = getRandFloat(-5,5);
        }
        // �\��
        for (int i = 0; i < 5; i++) {
            text(random[i], 30.0f*i, 240.0f);
        }
        text("����="+(var)randomf, 0, 300);
    }
}
#endif
