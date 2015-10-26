//
//  main.cpp
//  BlockGame
//
//  Created by KawakawaPlanning on 2015/10/26.
//  Copyright © 2015年 KawakawaPlanning. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>
#include <math.h>

// 3  315  0  45   0
//    270  o  90
// 2  225 180 135  1

double bumper_x;
double bumper_y = -0.7;

double ball_x ;
double ball_y = -0.6;

double hantei = 0.96;

int    angle = 0;

#define PART 100 // 分割数

void drawBumper( double x1, double y1, double x2, double y2 ){
    glBegin( GL_POLYGON );
    glVertex2d( x1, y1 );
    glVertex2d( x1, y2 );
    glVertex2d( x2, y2 );
    glVertex2d( x2, y1 );
    glEnd();
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1.0, 0.0, 0.0);
    drawBumper(bumper_x + 0.2, bumper_y, bumper_x-0.2, bumper_y - 0.1);
    
    glColor3f(1.0, 1.0, 1.0); // 描画物体に白色を設定
    glBegin(GL_POLYGON); // ポリゴンの描画
    // 円を描画
    int i ,n = PART;
    float x, y, r = 0.05;
    double rate;
    for (i = 0; i < n; i++) {
        // 座標を計算
        rate = (double)i / n;
        x = r * cos(2.0 * M_PI * rate) + ball_x;
        y = r * sin(2.0 * M_PI * rate) + ball_y;
        glVertex3f(x, y, 0.0); // 頂点座標を指定
    }
    glEnd(); // ポリゴンの描画終了
    
    glFlush();
}

void init(void){
    glClearColor(0.109803922, 0.282352941, 0.9, 1.0);
}

void passive(int x, int y){
    printf("(%d, %d)\n",x,y);
    bumper_x = (x-249.5)/255.0;
}

void gltTimer(int arg){
    
    //壁判定ここから
    switch (angle) {
        case 0:
            ball_y = ball_y + 0.01;
            ball_x = ball_x + 0.01;
            if (ball_x >= hantei)
                angle = 1;
            else if(ball_y >= hantei)
                angle = 3;
            break;
        case 1:
            ball_y = ball_y + 0.01;
            ball_x = ball_x - 0.01;
            if (ball_y >= hantei)
                angle = 2;
            else if(ball_x <= 0-hantei)
                angle = 0;
            break;
        case 2:
            ball_y = ball_y - 0.01;
            ball_x = ball_x - 0.01;
            if (ball_x <= 0-hantei)
                angle = 3;
            break;
        case 3:
            ball_y = ball_y - 0.01;
            ball_x = ball_x + 0.01;
            if (ball_x >= hantei)
                angle = 2;
            break;
    }
    if(ball_y < -1.1)
        exit(1);
    //壁判定ここまで
    
    //バー判定ここから
    if (ball_y <= bumper_y +0.04) {
        if (bumper_x - 0.2 < ball_x && bumper_x + 0.2 > ball_x){
            if (angle == 3) {
                angle = 0;
            }else if (angle == 2) {
                angle = 1;
            }
        }
    }
    //バー判定ここまで
    
    glutPostRedisplay();
    glutTimerFunc(10, gltTimer, 0);
}

int main(int argc, char *argv[]) {
    // insert code here...
    printf("Hello World!\n");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize( 500, 500 );
    glutCreateWindow("BlockGame");
    glutDisplayFunc(display);
    glutPassiveMotionFunc(passive);
    glutTimerFunc(10, gltTimer, 0);    init();
    glutMainLoop();
    
    return 0;
}