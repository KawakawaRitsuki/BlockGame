//
//  main.cpp
//  BlockGame
//
//  Created by KawakawaPlanning on 2015/10/26.
//  Copyright © 2015年 KawakawaPlanning. All rights reserved.
//

#include <stdio.h>
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    
//    glBegin(GL_LINE_LOOP);
    
    glFlush();
}

void init(void){
    glClearColor(0.109803922, 0.282352941, 0.8, 1.0);
}

//void motion(int x, int y){
//    printf("(%d, %d)\n",x,y);
//}

void passive(int x, int y){
    printf("(%d, %d)\n",x,y);
}

int main(int argc, char *argv[]) {
    // insert code here...
    printf("Hello World!\n");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
//    glutMotionFunc( motion );
     glutPassiveMotionFunc(passive);
    init();
    glutMainLoop();
    
    
    return 0;
}
