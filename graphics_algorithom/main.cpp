// graphics_algorithom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "kdtree2d.h"
#include "drawtools.h"
#include "rayTrace.h"
#include "particle.h"
#include "meshReadAndWrite.h"
#include "mytype.h"
//#include <GL/gl.h>
#include "freeglut.h"
#include <iostream>
#include <math.h>
using namespace std;
int winwidth ,winheight;
Node* globalroot;
MeshModelType* mesh;
//parameter of view
const float PI  = 3.14159f;
float xtranslate , ytranslate = 0.0f;
float ztranslate = 0.5f/tan(30.0f/180.0f*PI );
float xrotate ,yrotate ,zrotate;

float fov = 60.0f;
float aspect;

static float c= PI/180.0f; //弧度和角度转换参数 
static int du=90,oldmy=-1,oldmx=-1; //du是视点绕y轴的角度,opengl里默认y轴是上方向 
static float r=1.5f,h=0.0f; //r是视点绕y轴的半径,h是视点高度即在y轴上的坐标

static bool isRun = false;

extern const gl_Material material = {
	{0.0f, 0.0f, 1.0f, 0.0f},     /* ambient */
	{0.0f, 1.0f, 0.0f, 0.0f},     /* diffuse */
	{0.0f, 1.0f, 0.0f, 1.0f},     /* specular */
	{2.0f, 0, 0, 0}               /* shininess */
};
void display()
{
	//glViewport( 0, 0, winwidth/2,winheight/2 ); 
	cout<<"display"<<endl;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f ,0.0f ,1.0f);

	glViewport(0,0,winwidth,winheight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(r*cos(c*du), h, r*sin(c*du), 0,0.0,-300.0f ,0,1,0);
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
	//drawgrid(50,60);
	drawCube( Point3D(-1.0f ,-1.0f ,1.0f) ,Point3D(1.0f, 1.0f ,-1.0f));
	drawpoint( 0,0);
	drawpoint( 20,30);
	drawpoint( 10,10);
	drawline( 0,0 ,10,10);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	TetraHedron tetra(2);
	tetra.draw();
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	//glFlush();
//	drawgrid(50,60);
	glFlush();
	drawAxis(xrotate,yrotate,zrotate);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	SetMaterial(&material);
	renderMeshModel(mesh);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
//  __NAMESPACE_PARTICLE__::particle_display();
	//draw rectangle
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
		case 'q':
			isRun =!isRun;
			break;
	}
	glutPostRedisplay();

}
void mouseFunc(int button,int action,int xMouse,int yMouse)
{
	
	cout<<"button: "<<button<<endl;
	cout<<"xMouse yMouse: "<<xMouse<<" "<<yMouse<<endl;
	int type = 0;
	if(button == GLUT_LEFT_BUTTON&&action == GLUT_DOWN)
	{	type = 0;
		oldmx=xMouse,oldmy=yMouse;  
	}
	if(button == GLUT_MIDDLE_BUTTON&&action == GLUT_DOWN)type = 1;
	if(button == GLUT_RIGHT_BUTTON&&action == GLUT_DOWN)type = 2;
	if(button == 3)type = 3;
	if(button == 4)type = 4;
	
	switch(type)
	{
	case 0 :		
//		xrotate +=1.0f;
		break;
	case 1 :
		yrotate +=1.0f;
		break;
	case 2 :
		zrotate +=1.0f;
		break;
	case 3 :
		ztranslate +=0.10f;
		break;
	case 4 :
		ztranslate -=0.10f;
		break;
	}
	glutPostRedisplay();

}
void mouseMoveFunc(int x,int y)
{
	cout<<"xMouse yMouse: "<<x<<" "<<y<<endl;
	//printf("%d\n",du);  
	//du+=x-oldmx; //鼠标在窗口x轴方向上的增量加到视点绕y轴的角度上，这样就左右转了  
	//h +=0.03f*(y-oldmy); //鼠标在窗口y轴方向上的改变加到视点的y坐标上，就上下转了  
	//if(h>1.0f) h=1.0f; //视点y坐标作一些限制，不会使视点太奇怪  
	//else if(h<-1.0f) h=-1.0f;  
	int incx =  x - oldmx;
	int incy =  y - oldmy;
	
	oldmx=x,oldmy=y; //把此时的鼠标坐标作为旧值，为下一次计算增量做准备  
	if(abs((float)x)/winwidth <0.1||abs( (float)y)/winheight <0.1||abs((float)(x-winwidth))/winwidth <0.1 || abs( (float)(y-winheight))/winheight <0.1 )zrotate += (incy+incx)/2;
	else
	{
		xrotate += incy;
		yrotate += incx;
	}

	
	glutPostRedisplay();

}
void idlefun(void)
{
	if(isRun)
		cout<<"idle"<<endl;
	__NAMESPACE_PARTICLE__::particle_idle();
}
void mainmenu(int index)
{
	__NAMESPACE_PARTICLE__::particle_mainmenu(index);
}
void init()
{
	__NAMESPACE_PARTICLE__::particle_init();
}
void initWidow(int argc , char** argv)
{
	init();
	glutInit(&argc ,argv);
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB|GLUT_DEPTH);
	//glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition(100,100);
	glutInitWindowSize( 500 ,500);
	glutCreateWindow( "kdtree");
	glutCreateMenu(mainmenu);
	glutAddMenuEntry("more particles" ,1);
	glutAddMenuEntry("fewer particles",2);
	glutAddMenuEntry("speed",3);
	glutAddMenuEntry("gravity",4);
	glutAddMenuEntry("elastic",5);
	glutAddMenuEntry("increase pointsize",6);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyfunc );
	glutMouseFunc( mouseFunc );
	glutMotionFunc( mouseMoveFunc);
	glutIdleFunc(idlefun);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS); //这个用于保证循环退出时能继续运行后面的代码
	glutMainLoop();
}
int _tmain(int argc, _TCHAR* argv[])
{
	
	//KdTreeBuilder kb;
	vector<Point2D> pointarry;
	float xarray[] = {-1.0f , 1.0f ,0.0f, -1.0f,0.0f ,0.2f ,-0.2f , -0.4f ,0.4f };
	float yarray[] = {-1.0f , 1.0f ,0.0f, 0.0f ,-1.0f ,0.3f ,0.2f ,0.4f ,-0.2f};
	mesh = new MeshModelType; 
	_HHY_MESH_::ReadWriteManager::getInstance().readMesh(".\\snake1.obj",*mesh);
	//Node* root = kb.build( xarray ,yarray ,sizeof(xarray)/sizeof(float) );
	//Node::printNode(root,0);
	//Node::freeNode(root);
	//Node::printNode(root,0);
	//globalroot = root;
	initWidow( argc , (char**)argv);
	delete mesh;
	//Node::freeNode(root);
	return 0;
}

