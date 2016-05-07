#include "rayTrace.h"

const int QUAD::indexs[6][4] = { 0 ,3 ,2 ,1, 3 ,7 ,6,2,  7 ,4 ,5 ,6 ,  4,0,1,5,  1,2,6,5, 0,4,7,3};
const float  TetraHedron::initpoint[4][3] = { {0.0f,0.0f,1.0f},
{0.0f,0.942809f,-0.333333f},
{-0.816497f,-0.471405f,-0.33333f},
{0.816497f,-0.471405f,-0.333333f}};
std::vector<Point> TetraHedron:: triangles;
std::vector<Point> TetraHedron:: pretriangles;

Color trace(Point p , Vector d ,int step)
{
	Color local , reflected ,transmitted;
	Vertex q; //the point from light intersect on the object
	Vector n , r ,t; //normal
	if(step > itermax) return  background_color;
	intersect_status status;
	q = intersect(p ,d ,status);
	if(status.status ==  light_source)return(light_source_color);
	if(status.status ==  no_intersection)return(background_color);
	n = q.getNormal();
	r = q.getReflect( d );
	r = q.getTransmitted(d);
	local = q.getByPhong(d);//getPhongColor( q ,d);
	reflected = trace(q.position ,r, step+1);
	transmitted = trace( q.position ,t ,step+1);
	return local + reflected + transmitted;
}

Vertex intersect(Point startpoint, Vector lightdirect ,intersect_status& status)
{
	return Vertex();
}





Color Vertex::getByPhong(Light l)
{
	float Ia[3];
	float Id[3];
	float Is[3];
	
	/*ambient*/
	for(int i = 0 ;i <3 ;++i)
	{
		Ia[i] = R[0][i]* l.L[0][i];
	}
	/*diffuse*/
	for(int i = 0 ; i< 3 ;++i)
	{
		Id[i] = - R[1][i]*dotproduct(l.lightdir,normal) * l.L[1][i];
		if(Id[i] <0 ) Id[i] = 0;
	}
	/*specular */
	for(int i = 0 ; i< 3 ;++i)
	{
		Is[i] = - R[2][i]*l.L[2][i]*dotproduct( getReflect(l.lightdir) , getViewDir()); //alpha = 1
		if(Is[i] <0 ) Is[i] = 0;
	}
	Color result( Ia[0]+Id[0]+Is[0] ,Ia[1]+Id[1]+Is[1],Ia[2]+Id[2]+Is[2]);
	return result;	
}

Color Vertex::getByPhong(Vector l)
{
	return Vector();
}
