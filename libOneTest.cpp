#include"framework.h"
#include"window.h"
#include"graphic.h"
program() {
    window(1280, 720);
    float x=640, y=360, r=250,vx=5, vy=-3;
    repeat() {
        x += vx;
        y += vy;
        if (x<r || x>Width - r)vx *= -1;
        if (y<r || y>Height - r)vy *= -1;

        clear(250,200,220);
        //ê¸ï™ÇP
        strokeWeight(5);
        stroke(255, 255, 0);
        line(100, 0, 300, 100);
        //ê¸ï™ÇQ
        strokeWeight(10);
        stroke(255, 0, 0);
        line(0, 300, 300, 0);
        //éläpå`
        rectMode(CENTER);
        fill(255, 0, 255);
        stroke(0, 0, 0);
        strokeWeight(1);
        rect(50, 50, 100, 100);
        //â~
        fill(0, 0, 255);
        circle(x, y, r*2);
    }
}