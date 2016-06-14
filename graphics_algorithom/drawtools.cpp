

#include "drawtools.h"
#include "kdtree2d.h"
#include "freeglut.h"
#include "rayTrace.h"
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
		gridsize = 2.0f/rows;
	}else{
		gridsize = 2.0f/cols;
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

void drawCube(const Point3D& lefdown ,const Point3D& rightTop)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glHint (GL_POINT_SMOOTH, GL_NICEST);
	glEnable(GL_BLEND);  
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

	glColor3f(1.0f ,0.0f ,0.0f);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glVertex3f(lefdown.x ,lefdown.y,lefdown.z);
	glVertex3f(lefdown.x, rightTop.y,rightTop.z);
	glVertex3f(lefdown.x ,rightTop.y,lefdown.z);
	glVertex3f(lefdown.x ,lefdown.y,rightTop.z);
	glVertex3f(rightTop.x ,lefdown.y,lefdown.z);
	glVertex3f(rightTop.x ,rightTop.y,lefdown.z);
	glVertex3f(rightTop.x ,lefdown.y,rightTop.z);
	glVertex3f(rightTop.x ,rightTop.y ,rightTop.z);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_BLEND); 

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);  
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glColor3f(0.0,0.0f ,1.0f);
	glLineWidth(5.0f);
	glBegin( GL_LINES ); 
	glVertex3f(lefdown.x ,lefdown.y,lefdown.z);
	glVertex3f(lefdown.x ,lefdown.y,rightTop.z);//
	glVertex3f(lefdown.x ,lefdown.y,lefdown.z);
	glVertex3f(lefdown.x ,rightTop.y,lefdown.z);//
	glVertex3f(lefdown.x ,lefdown.y,lefdown.z);
	glVertex3f(rightTop.x ,lefdown.y,lefdown.z);//

	glVertex3f(lefdown.x ,lefdown.y,rightTop.z);
	glVertex3f(lefdown.x ,rightTop.y,rightTop.z);
	glVertex3f(lefdown.x ,lefdown.y,rightTop.z);
	glVertex3f(rightTop.x ,lefdown.y,rightTop.z);

	glVertex3f(lefdown.x ,rightTop.y,lefdown.z);
	glVertex3f(rightTop.x ,rightTop.y,lefdown.z);
	glVertex3f(lefdown.x ,rightTop.y,lefdown.z);
	glVertex3f(lefdown.x ,rightTop.y,rightTop.z);

	glVertex3f(rightTop.x ,lefdown.y,lefdown.z);
	glVertex3f(rightTop.x ,rightTop.y,lefdown.z);
	glVertex3f(rightTop.x ,lefdown.y,lefdown.z);
	glVertex3f(rightTop.x ,lefdown.y,rightTop.z);

	glVertex3f(rightTop.x ,rightTop.y ,rightTop.z);
	glVertex3f(lefdown.x ,rightTop.y ,rightTop.z);
	glVertex3f(rightTop.x ,rightTop.y ,rightTop.z);
	glVertex3f(rightTop.x ,lefdown.y ,rightTop.z);
	glVertex3f(rightTop.x ,rightTop.y ,rightTop.z);
	glVertex3f(rightTop.x ,rightTop.y ,lefdown.z);

	glEnd();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND); 
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_BLEND);

}

void drawAxis( float xrotate ,float yrotate ,float zrotate)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();	
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef( 0.0f, 0.0f ,-1.0f);
	glRotatef( xrotate, 1.0f ,0.0f ,0.0f);
	glRotatef( yrotate, 0.0f ,1.0f ,0.0f);
	glRotatef( zrotate, 0.0f ,0.0f ,1.0f);
	glColor4f( 1.0f ,0.0f ,0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f( 0.0f ,0.0f ,0.0f);
	glVertex3f( 1.0f ,0.0f ,0.0f);
	glEnd();
	glColor4f( 0.0f ,1.0f ,0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f( 0.0f ,0.0f ,0.0f);
	glVertex3f( 0.0f ,1.0f ,0.0f);
	glEnd();
	glColor4f( 0.0f ,0.0f ,1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f( 0.0f ,0.0f ,0.0f);
	glVertex3f( 0.0f ,0.0f ,1.0f);
	glEnd();
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}
#include "mytype.h"
void renderMeshModel(const MeshModelType* const _model)
{
	my_index_type i_triangle;
	my_size_type n_triangel = _model->n_triangle;
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_TRIANGLES);
	for(i_triangle = 0; i_triangle < n_triangel;++i_triangle)
	{
		const std::vector<NormalType>& m_norms = _model->normal_array;
		const std::vector<VertexType>& m_vtxs = _model->vertex_array;
		const TriangleType& m_triangle = _model->triangle_array[i_triangle];
		if(m_triangle.i_norm[0]!=-1)glNormal3fv( (GLfloat*)m_norms[m_triangle.i_norm[0]].array );
		glVertex3fv( (GLfloat*)m_vtxs[m_triangle.i_vertex[0]].array );
		if(m_triangle.i_norm[1]!=-1)glNormal3fv( (GLfloat*)m_norms[m_triangle.i_norm[1]].array );
		glVertex3fv( (GLfloat*)m_vtxs[m_triangle.i_vertex[1]].array );
		if(m_triangle.i_norm[2]!=-1)glNormal3fv( (GLfloat*)m_norms[m_triangle.i_norm[2]].array );
		glVertex3fv( (GLfloat*)m_vtxs[m_triangle.i_vertex[2]].array );
	}
	glEnd();
	glDisable(GL_DEPTH_TEST);
}

void renderMeshModelWired(const MeshModelType* const _model)
{
	my_index_type i_triangle;
	my_size_type n_triangel = _model->n_triangle;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	for(i_triangle = 0; i_triangle < n_triangel;++i_triangle)
	{
		const std::vector<NormalType>& m_norms = _model->normal_array;
		const std::vector<VertexType>& m_vtxs = _model->vertex_array;
		const TriangleType& m_triangle = _model->triangle_array[i_triangle];
		glBegin(GL_LINE_LOOP);
		if(m_triangle.i_norm[0]!=-1)glNormal3fv( (GLfloat*)m_norms[m_triangle.i_norm[0]].array );
		glVertex3fv( (GLfloat*)m_vtxs[m_triangle.i_vertex[0]].array );
		if(m_triangle.i_norm[1]!=-1)glNormal3fv( (GLfloat*)m_norms[m_triangle.i_norm[1]].array );
		glVertex3fv( (GLfloat*)m_vtxs[m_triangle.i_vertex[1]].array );
		if(m_triangle.i_norm[2]!=-1)glNormal3fv( (GLfloat*)m_norms[m_triangle.i_norm[2]].array );
		glVertex3fv( (GLfloat*)m_vtxs[m_triangle.i_vertex[2]].array );
		glEnd();
	}
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	
}

void renderPanel(void)
{
	extern MeshModelType* mesh;
	extern const gl_Material material;
	SetMaterial(&material);
	renderMeshModel(mesh);
}


void SetMaterial(const gl_Material *material)
{
	/* define material properties of all polygons */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   material->ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   material->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  material->specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material->shininess);
}


