/*
Author : Vicky Bhuva
Objective : Making of "Let'me pass" game using OpenGL Libraries
Date : 23 March, 2017
*/
#include <GL/glut.h>
#include<stdlib.h>

int score = 0,exit1=0;
float x,y=90,flag=0;
float x1=0,y1=1000,x2=200,y2=1500,x3=-200,y3=2000,x4=100,y4=3000;

void barrier(float a, float b){
    glBegin(GL_POLYGON);
        glColor3f(0.9,0.3,0.3);
        glVertex2f(-45+a,20+b);
        glVertex2f(-60+a,b);
        glVertex2f(-45+a,-20+b);
        glVertex2f(45+a,-20+b);
        glVertex2f(60+a,b);
        glVertex2f(45+a,20+b);
    glEnd();
}

void barrier2(float a, float b){
    glBegin(GL_POLYGON);
        glColor3f(0.9,0.3,0.3);
        glVertex2f(a,60+b);
        glVertex2f(-20+a,45+b);
        glVertex2f(-20+a,-45+b);
        glVertex2f(a,-60+b);
        glVertex2f(20+a,-45+b);
        glVertex2f(20+a,45+b);
    glEnd();
}

void ball(float a,float b){
    glBegin(GL_QUADS);
        glColor3f(1,1,1);
        glVertex2f(-20+a,20+b);
        glVertex2f(20+a,20+b);
        glVertex2f(20+a,-20+b);
        glVertex2f(-20+a,-20+b);
    glEnd();
}


void sc(int a)//score board
{
    int i,j,k;
	i=a/100;
	j=a/10-i*10;
	k=a-j*10-i*100;
	glPushMatrix();
	glTranslated(70,900,0);//translate(0,0) to (70,900)
	glScaled(0.3,0.3,0);
	glColor3f(1,1,1);
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)i+48);//48 for convert ASCII to int...
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)j+48);
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)k+48);
	glPopMatrix();
}

void display(){
if(exit1==0)//till exit bit is not zero
	{
	    glLineWidth(1);
	    //Speed increment of barrier...
		if(score<50){
            y1-=0.6;
            y2-=0.7;
            y3-=0.4;
            y4-=0.8;
		}
        if(score>=50&&score<100){
            y1-=0.7;
            y2-=0.8;
            y3-=0.9;
            y4-=0.6;
        }
        if(score>=100){
            y1-=1;
            y2-=1.3;
            y3-=1.5;
            y4-=1.7;
        }
        //update y1 y2 and y3...
        if(y1<-250)
        {
            score+=5;
            y1=1000;
        }
        if(y2<-250)
        {
            score+=5;
            y2=1500;
        }
        if(y3<-250)
        {
            score+=5;
            y3=2000;
        }
        if(y4<-400)
        {
            score+=5;
            y4=3000;
            if(x4>0){
                x4=-100;
                flag=1;
            }
            else{
                x4=100;
                flag=0;
            }
        }
    //by any accident exit bit will counter to one

    //for middle barrier
       if(20+x>-60&&-20+x<60) // left part and right part
        if(20+y>-20+y1&&20+y1>20+y)
            exit1=1;

    //for right barrier
        if(20+x>140 &&-20+x  <260)
         if(20+y>-20+y2&&20+y2>20+y)
            exit1=1;

    //for left barrier
        if(20+x>-260&&-20+x<-140)
         if(20+y>-20+y3&&20+y3>20+y)
           exit1=1;

    //for vertical barrier
        if(flag == 0){
            if(20+x>80 && -20+x<120)
             if(20+y>-60+y4 && 60+y4>20+y)
                exit1=1;
        }
        else{
            if(20+x>-120 && -20+x<-80)
             if(20+y>-60+y4 && 60+y4>20+y)
                exit1=1;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glPopMatrix();

        sc(score);
        ball(x,y);
        barrier(x1,y1);
        barrier(x2,y2);
        barrier(x3,y3);
        barrier2(x4,y4);
        glutSwapBuffers();
}
else{
    glLineWidth(5);
    glPushMatrix();
	glColor3f(1,1,1);
	glTranslated(-225,700,0);//translation (0,0) to (-500,500)
	glScaled(0.5,0.5,0);//scaling
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'G');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'A');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'M');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'E');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)' ');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'O');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'V');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'E');
	glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,(int)'R');
	glPopMatrix();
	glutSwapBuffers(); //for change display data
}
}


void keyboards(unsigned char keys,int x5,int y5)
{
	//to quit
    if(keys=='q'||keys=='Q')
	{
		  exit(-1);
	}


	//to start
	if(keys=='s')
    {
		glutIdleFunc(display);
    }

    //to restart
    if(keys=='r')
    {
        exit1=0;    //reinitialization
        x=0;y=90;
        x1=0;y1=1000;x2=200;y2=1500;x3=-200;y3=2000;x4=100;y4=3000,flag=0;
        score=0;

    }

  	//movement keys
	if((keys=='a' || keys=='4')&& x > -160)
		x-=100;
	if((keys=='d'|| keys=='6') && x < 160)
		x+=100;
}



int main(int argc, char **argv)
{
  glutInit(&argc,argv);
  glutInitWindowSize(500,700);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
  glutCreateWindow("Let'me pass");
  glClearColor(0,0,0,1);//set Background
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboards);
  gluOrtho2D(-255,255,0,1000); //->x(-255,255) and ->y(0,1000)y
  glutMainLoop();

  return 0;
}
