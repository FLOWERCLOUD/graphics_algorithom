// graphics_algorithom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "kdtree2d.h"
#include "drawtools.h"
//#include <GL/gl.h>
#include "freeglut.h"
#include <iostream>
#include <math.h>
using namespace std;
int winwidth ,winheight;
Node* globalroot;

//parameter of view
const float PI  = 3.14159f;
float xtranslate , ytranslate = 0.0f;
float ztranslate = 0.5f/tan(30.0f/180.0f*PI );
float xrotate ,yrotate ,zrotate;

float fov = 60.0f;
float aspect;
void display()
{
	//glViewport( 0, 0, winwidth/2,winheight/2 ); 
	cout<<"display"<<endl;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f ,0.0f ,1.0f);

	glViewport(0,0,winwidth,winheight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt( xtranslate, ytranslate ,ztranslate, 0,0.0,-300.0f ,0,1,0);
	glRotatef( xrotate, 1.0f ,0.0f ,0.0f);
	glRotatef( yrotate, 0.0f ,1.0f ,0.0f);
	glRotatef( zrotate, 0.0f ,0.0f ,1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(winwidth < winheight)
	{	if(0)
		glOrtho( -1.1f , 1.1f, -1.1f*winheight/winwidth , 1.1f*winheight/ winwidth, 10,30);
		else
		gluPerspective(fov ,1.0f*winwidth/winheight, 0.01f/tan(30.0f/180.0f*PI ) ,0.01f/tan(30.0f/180.0f*PI )+300);
		cout<<"apspect: "<<1.0f*winwidth/winheight<<endl;
	}		
	else
	{	if(0)
		glOrtho( -1.1f* winwidth/winheight,1.1f* winwidth/winheight, -1.1f , 1.1f ,10,30);
		else
		gluPerspective(fov ,1.0f*winwidth/winheight, 0.01f/tan(30.0f/180.0f*PI ) ,0.01f/tan(30.0f/180.0f*PI )+300);
		cout<<"apspect: "<<1.0f*winwidth/winheight<<endl;
	} 

	glColor3f(1.0,0.0f ,0.0f);

	//draw(globalroot);
	drawgrid(50,60);
	drawpoint( 0,0);
	drawpoint( 20,30);
	drawpoint( 10,10);
	drawline( 0,0 ,10,10);
	//drwa rectangle
	//glRectf( -0.5f ,-0.5f , 0.5f, 0.5f);

	////draw round points
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_POINT_SMOOTH);
	//glHint (GL_POINT_SMOOTH, GL_NICEST);
	//glEnable(GL_BLEND);  
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
	//glPointSize(50.0f);
	//glBegin(GL_POINTS);
	//glVertex2f( 0.5f ,0.5f);
	//glVertex2f( 0.0f ,0.0f);
	//glEnd();
	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_POINT_SMOOTH);
	//glDisable(GL_BLEND);  

	//
	//glColor3f( 1.0, 0.0, 0.0 );  
	////画分割线，分成四个视见区  
	//glViewport( 0, 0, winwidth,winheight );  
	//glBegin( GL_LINES );  
	//glVertex2f( -1.0, 0 );  
	//glVertex2f( 1.0, 0 );  
	//glVertex2f( 0.0, -1.0 );  
	//glVertex2f( 0.0, 1.0 );  
	//glEnd();  

	/*glBegin(GL_TRIANGLES);
	glVertex2f( 0.0f ,30.0f);
	glVertex2f( -40.0f ,-30.0f);
	glVertex2f( 40.0f ,-30.0f);
	glEnd();*/
	//glFlush(); //把绘图命令立即发给gpu,这个不写也没什么问题 ，因为调用 glutSwapBuffers() 就会隐含有glFlush(),
	glutSwapBuffers(); //少了这个时显示的是back ground frame buffer 的内容
}
void reshape(int width ,int height)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f ,0.0f ,1.0f);
	winwidth = width ;
	winheight = height;
	/*glViewport(0,0,width,height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt( 0.0f, 0.0f ,-10.0f, 0,0.0,-300.0f ,0,1,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(width < height)
		glOrtho( -1.1f , 1.1f, -1.1f*height/width, 1.1f*height/width,-10,30);
	else
		glOrtho( -1.1f*width/height,1.1f*width/height, -1.1f , 1.1f ,-10,30);
	cout<<"reshpae width"<<width<<"height:"<<height<<endl;*/
	cout<<"reshpae width: "<<width<<" height: "<<height<<endl;
	glutPostRedisplay();
	
}
void keyfunc(unsigned char key, int xMouse,int yMouse)
{
	cout<<key<<endl;
	switch(key)
	{
		case 'a':
		xtranslate -=0.1f;
		break;
		case 'd':
		xtranslate +=0.1f; 
		break;
		case 'w':
		ytranslate +=0.1f; 	 
		break;
		case 's':
		ytranslate -=0.1f;  
		break;
		case 'z':
		ztranslate -=0.1f;
		break;
		case 'x':
		ztranslate +=0.1f;
		break;
		case 'j':
		xrotate +=1.0f;
			break;
		case 'k':
		xrotate -=1.0f;
		break;

		case 'u':
			yrotate +=1.0f;
			break;
		case 'i':
			yrotate -=1.0f;
			break;

		case 'o':
			zrotate +=1.0f;
			break;
		case 'p':
			zrotate -=1.0f;
			break;
	}
	glutPostRedisplay();

}
void mouseFunc(int button,int action,int xMouse,int yMouse)
{
	
}
void mouseMoveFunc(int xMouse,int yMouse)
{

}
void initWidow(int argc , char** argv)
{
	glutInit(&argc ,argv);
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition(100,100);
	glutInitWindowSize( 500 ,500);
	glutCreateWindow( "kdtree");
	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyfunc );
	glutMouseFunc( mouseFunc );
	glutMotionFunc( mouseMoveFunc);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS); 
	glutMainLoop();
}
int _tmain(int argc, _TCHAR* argv[])
{
	
	KdTreeBuilder kb;
	vector<Point2D> pointarry;
	float xarray[] = {-1.0f , 1.0f ,0.0f, -1.0f,0.0f ,0.2f ,-0.2f , -0.4f ,0.4f };
	float yarray[] = {-1.0f , 1.0f ,0.0f, 0.0f ,-1.0f ,0.3f ,0.2f ,0.4 ,-0.2f};
	 
	Node* root = kb.build( xarray ,yarray ,sizeof(xarray)/sizeof(float) );
	Node::printNode(root,0);
	//Node::freeNode(root);
	//Node::printNode(root,0);
	globalroot = root;
	initWidow( argc , (char**)argv);
	Node::freeNode(root);
	return 0;
}

