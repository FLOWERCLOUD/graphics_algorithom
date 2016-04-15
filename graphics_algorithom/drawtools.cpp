

#include "drawtools.h"
#include "kdtree2d.h"
#include "freeglut.h"
static void drawiter(Node* node)
{
	if(node)
	{
		glColor3f(1.0,0.0f ,0.0f);
		glBegin(GL_POINTS);
		glVertex2f( node->x ,node->y);
		glEnd(); 
   

		glColor3f(1.0,1.0f ,0.0f);
		glBegin( GL_LINES );  
		glVertex2f( node->wrapbox.nw.x, node->wrapbox.nw.y );  
		glVertex2f( node->wrapbox.ne.x, node->wrapbox.ne.y ); 
		glVertex2f( node->wrapbox.nw.x, node->wrapbox.nw.y ); 
		glVertex2f( node->wrapbox.sw.x, node->wrapbox.sw.y );  
		glVertex2f( node->wrapbox.sw.x, node->wrapbox.sw.y  );  
		glVertex2f( node->wrapbox.se.x, node->wrapbox.se.y  );
		glVertex2f( node->wrapbox.se.x, node->wrapbox.se.y  );
		glVertex2f( node->wrapbox.ne.x, node->wrapbox.ne.y ); 
		glEnd(); 
		
		if( node->nw)drawiter(node->nw);
		if( node->ne)drawiter(node->ne);
		if( node->sw)drawiter(node->sw);
		if( node->se)drawiter(node->se);
	}
	
}
void draw(Node* tree)
{
	//draw round points
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glHint (GL_POINT_SMOOTH, GL_NICEST);
	glEnable(GL_BLEND);  
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
	glPointSize(10.0f);
	
	glEnable(GL_LINE_SMOOTH);  
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	drawiter(tree);

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_BLEND); 
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_BLEND);

}
float g_gridsize;
void drawgrid(int rows ,int cols)
{
	float rangeleft = -1;
	float rangeright = 1;
	float rangeup = 1;
	float rangedown = -1;
	float gridsize;
	if( rows > cols)
	{
		gridsize = 2.0/rows;
	}else{
		gridsize = 2.0/cols;
	}
	 g_gridsize = gridsize;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);  
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
	glEnable(GL_LINE_SMOOTH);  
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glLineWidth(1.0f);
	//glColor3f(1.0,0.0f ,0.0f);
	//glBegin( GL_LINES ); 
	//glVertex2f( -1  ,1);
	//glVertex2f( 1  ,1);
	//glVertex2f( 1  ,1);
	//glVertex2f( 1  ,-1);
	//glVertex2f( 1  ,-1);
	//glVertex2f( -1  ,-1);
	//glVertex2f( -1  ,-1);
	//glVertex2f( -1  ,1);
	//glEnd();

	glColor3f(1.0,1.0f ,0.0f);
	glLineWidth(1.0f);
	glBegin( GL_LINES );  
	int col;
	int row;
	for(col =  0;col <cols ; ++col )
	{
		
		for(row = 0; row <  rows ;++row)
		{
			glVertex2f( -1+gridsize*(row) ,1-gridsize*(col));
			glVertex2f( -1+gridsize*(row+1) ,1-gridsize*(col));
			glVertex2f( -1+gridsize*(row) ,1-gridsize*(col));
			glVertex2f( -1+gridsize*(row) ,1-gridsize*(col+1));

		}
		glVertex2f( -1+gridsize*(row) ,1-gridsize*(col));
		glVertex2f( -1+gridsize*(row) ,1-gridsize*(col+1));		
	}
	for(row = 0; row <  rows ;++row)
	{
		glVertex2f( -1+gridsize*(row) ,1-gridsize*(col));
		glVertex2f( -1+gridsize*(row+1) ,1-gridsize*(col));
	}

	glEnd(); 
	drawpoint(0 ,0);
	drawpoint(rows ,cols);
	drawpoint(rows ,0);
	drawpoint(0,cols);




	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_BLEND);
}

void drawpoint(int indexrow,int indexcol)
{
	
	glEnable(GL_POINT_SMOOTH);
	glHint (GL_POINT_SMOOTH, GL_NICEST);
	glEnable(GL_BLEND);  
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
	glPointSize(10.0f);
	glColor3f(1.0,0.0f ,0.0f);
	glBegin(GL_POINTS);
	glVertex2f( -1.0f + g_gridsize*indexrow ,1.0f - g_gridsize*indexcol);
	glEnd(); 

	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_BLEND); 
	
}

void drawline(int indexrow1,int indexcol1 ,int indexrow2,int indexcol2)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);  
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glColor3f(0.0,0.0f ,1.0f);
	glLineWidth(5.0f);
	glBegin( GL_LINES ); 
	glVertex2f( -1.0f + g_gridsize*indexrow1 ,1.0f - g_gridsize*indexcol1);
	glVertex2f( -1.0f + g_gridsize*indexrow2 ,1.0f - g_gridsize*indexcol2);
	glEnd();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND); 
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_BLEND);
}
