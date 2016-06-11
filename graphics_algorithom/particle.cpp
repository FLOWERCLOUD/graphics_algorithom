#include "particle.h"
#include "freeglut.h"
#include <stdlib.h>
namespace __NAMESPACE_PARTICLE__
{
#define MAX_NUM_PARTICLES 1000
#define INITIAL_NUM_PARTICLES 25
#define INTIAL_POINT_SIZE 5.0
#define INITIAL_SPEED 1.0

	//typedef int BOOL;
#define TRUE 1
#define FALSE 0

	typedef struct particle
	{
		int color;
		float position[3];
		float velocity[3];
		float mass;
	}particle;
	particle particles[MAX_NUM_PARTICLES];

	static int present_time;
	static int last_time;
	static int num_particles = INITIAL_NUM_PARTICLES;
	static float point_size = INTIAL_POINT_SIZE ;
	static float speed = INITIAL_SPEED;
	static int gravity = false;
	static bool elastic = false;
	static float coef = 1.0f;

	float colors[8][3] = { {0.0 ,0.0 ,0.0} ,{1.0 ,1.0 ,1.0} ,{0.0,1.0,0.0},{0.0,0.0,1.0},
	{0.0,1.0,1.0},{1.0,0.0,1.0},{1.0,1.0,0.0},{1.0,1.0,1.0}
	};


	void particle_init()
	{
		int i,j;
		for(i = 0;i<num_particles;++i)
		{
			particles[i].mass = 1.0;
			particles[i].color = i%8;
			for(j=0;j<3;++j)
			{
				particles[i].position[j] = 2.0f*(float)rand()/RAND_MAX-1.0f;
				particles[i].velocity[j] = speed*.0f*(float)rand()/RAND_MAX-1.0f;
			}
		}
		glPointSize(point_size);
	}
	float forces(int i ,int j)
	{
		float force = 0.0;
		if(gravity&j == 1) force = -10.0f;
		return force;
	}
	void collistion(int n)
	{
		int i ;
		for(i = 0;i<3;++i)
		{
			if(particles[n].position[i]>=1.0f)
			{
				particles[n].velocity[i] = -coef*particles[n].velocity[i];
				particles[n].position[i] = 1.0f-coef*(particles[n].position[i]-1.0f);
			}
			if(particles[n].position[i]<=-1.0f)
			{
				particles[n].velocity[i] = -coef*particles[n].velocity[i];
				particles[n].position[i] = -1.0f-coef*(particles[n].position[i]+1.0f);
			}
			//if(particles[n].velocity[i]<0.01f&&particles[n].velocity[i]>-0.01f)particles[n].velocity[i]= 0.0f;

		}
	}

	void particle_idle()
	{
		int i,j;
		float dt;
		present_time = glutGet(GLUT_ELAPSED_TIME);
		dt = 0.001f*(present_time - last_time);
		for(i = 0; i<num_particles;++i)
		{
			for(j=0;j<3;++j)
			{
				particles[i].position[j]+= dt*particles[i].velocity[j];   //s2-s1 = v*(t2-t1)
				particles[i].velocity[j]+= dt*forces(i,j)/particles[i].mass; //v2 = v1-t* mg/m
				if(particles[i].velocity[j]>0) particles[i].velocity[j]-= dt*0.1f;	 //Ä¦²ÁÁ¦
				if(particles[i].velocity[j]<0) particles[i].velocity[j]+= dt*0.1f;
			}
			collistion(i);
		}
		last_time = present_time;
		glutPostRedisplay();
	}
	void particle_display()
	{
		glEnable(GL_POINT_SMOOTH);
		glHint (GL_POINT_SMOOTH, GL_NICEST);
		glEnable(GL_BLEND);  
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
		glPointSize(point_size);
		glBegin(GL_POINTS);
		for(int i=0;i<num_particles;++i)
		{
			glColor3fv(colors[particles[i].color]);
			glVertex3fv(particles[i].position);
		}
		glEnd();
		glDisable(GL_POINT_SMOOTH);
		glDisable(GL_BLEND); 
	}
	void particle_mainmenu(int index)
	{
		switch(index)
		{
		case(1):
			{
				num_particles = 2*num_particles;
				particle_init();
				break;
			}
		case(2):
			{
				num_particles = num_particles/2;
				particle_init();
				break;
			}
		case(3):
			{
				speed = speed/2.0f;
				particle_init();
				break;
			}
		case(4):
			{
				gravity = !gravity;
				particle_init();
				break;
			}
		case(5):
			{
				elastic =!elastic;
				if(elastic)coef = 0.5f;
				else coef = 1.0f;
				particle_init();
				break;

			}
		case(6):
			{
				point_size = point_size*2.0f;
				particle_init();
				break;

			}
		}
		glutPostRedisplay();
	}


}

