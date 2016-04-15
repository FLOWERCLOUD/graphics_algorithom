

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
