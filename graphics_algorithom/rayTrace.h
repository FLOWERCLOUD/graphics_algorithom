#ifndef _RAY_TRACE_
#define _RAY_TRACE_
#include "kdtree2d.h"
#include "freeglut.h"
#include <math.h>
#include <vector>
class Point3D;
Point3D operator+ (const Point3D& l ,const Point3D& r);
Point3D operator- (const Point3D& l ,const Point3D& r);
template<class T,class U> Point3D operator* (const T& l ,const U& r);
template<>  Point3D operator* (const float& l ,const Point3D& r);
template<>  Point3D operator* (const  Point3D& l ,const float& r);
class Point3D :public Point2D
{
public:
	Point3D():Point2D(),z(0.0f){}
	Point3D(float x ,float y ,float z1):Point2D(x ,y),z(z1){}
	Point3D(const float* fv):Point2D(fv[0],fv[1]),z(fv[2]){};
	Point3D(const Point3D& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
	}
	friend Point3D operator+ (const Point3D& l ,const Point3D& r);
	void norm()
	{
		float length = sqrt( x*x +y*y+z*z);
		x = x/length;
		y = y/length;
		z = z/length;
	}
	float z;

};

template<class T,class U> Point3D operator* (const T& l ,const U& r)
{

}
template<>  inline Point3D operator* (const float& l ,const Point3D& r)
{

}
template<>  inline Point3D operator* (const  Point3D& l ,const float& r)
{

}
inline Point3D operator- (const Point3D& l ,const Point3D& r)
{

}
inline Point3D operator+ (const Point3D& l ,const Point3D& r)
{
	return Point3D(l.x+r.x , l.y+r.y , l.z + r.z);
}
class Point4D :public Point3D
{
public:
	Point4D():Point3D(),a(0.0f){}
	Point4D(float x ,float y ,float z ,float a1):Point3D(x ,y ,z),a(a1){}
	Point4D(const Point4D& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		a = p.a;
	}
	float a;

};

typedef Point3D Point;
typedef Point Vector;
typedef Point Color;
/*
 Rira  Riga  Riba
 Rird  Rigd  Ribd
 Rirs  Rigs  Ribs
*/
class Light;
class Vertex
{
public:
	float R[3][3];  //
	Point position;
	Vector normal;
	Vector getNormal(){return normal;}
	void setNormal(Vector norm){ normal = norm;}
	Vector getReflect(Vector in_light)
	{
		return Vector();
	};
	Vector getTransmitted(Vector in_light)
	{
		return Vector();
	}
	Vector getViewDir()//from vertex to view
	{
		return Vector();
	}
	Color getByPhong(Light l);
	Color getByPhong(Vector l);
	
};
/*
 Lira  Liga  Liba
 Lird  Ligd  Libd
 Lirs  Ligs  Libs
*/
class Light
{
public:
	Light(){}
	float L[3][3];   //
	Point position;
	Vector lightdir;
};

class Face
{
	Vector normal;
};
class Material
{
	float ka ,kd ,ks;
	Vector normal;

};
class VertexProperty
{
	Vector normal;
	std::vector<Face> adjacent_faces;
	Material mm;
};
//quad
class QUAD
{
public:
	static const int indexs[6][4];
	QUAD(){}
	void begin()
	{
		facesidx.clear();
		points.clear();
		vtxproperties.clear();
	}
	void insert(Point3D p){
		if(points.size() == 8)return;
		points.push_back(p);
	};
	void insert(Point3D p ,VertexProperty pp){
		if(points.size() == 8)return;
		points.push_back(p);
		vtxproperties.push_back(pp);
	};
	void end()
	{
		if(points.size() == 8)
		{
			std::vector<int> AfaceIdx;
			for(int i = 0 ;i < 6 ;++i)
			{
				AfaceIdx.clear();
				AfaceIdx.push_back(indexs[i][0]);
				AfaceIdx.push_back(indexs[i][1]);
				AfaceIdx.push_back(indexs[i][2]);
				AfaceIdx.push_back(indexs[i][3]);
				facesidx.push_back(AfaceIdx);
			}			
		}
	}
private:
	std::vector< std::vector<int> > facesidx;	
	std::vector<Point3D> points;
	std::vector<VertexProperty> vtxproperties;
	std::vector<std::vector<int> > facedidxofvtx;

};


void normalize(Point3D& p);
class TetraHedron
{
public:
	static const float initpoint[4][3];
	static std::vector<Point> pretriangles;
	static std::vector<Point> triangles;
	TetraHedron(int n):depth(n)
	{
		
		if(triangles.size() == 0)
		{
			divide_triangle( Point(initpoint[0]) , Point(initpoint[1]) , Point(initpoint[2]) ,n );
			divide_triangle( Point(initpoint[3]) , Point(initpoint[2]) , Point(initpoint[1]),n );
			divide_triangle( Point(initpoint[0]) , Point(initpoint[3]) , Point(initpoint[1]),n );
			divide_triangle( Point(initpoint[0]) , Point(initpoint[2]) , Point(initpoint[3]),n );
		}

	}
	void draw()
	{
		
		int pretri_num = pretriangles.size()/3;
		for(int i = 0 ; i< pretri_num*3 ; i+=3 )
		{
			glEnable(GL_DEPTH_TEST);
			glBegin(GL_TRIANGLES);
			glNormal3f(pretriangles[i].x ,pretriangles[i].y ,pretriangles[i].z);
			glVertex3f(pretriangles[i].x ,pretriangles[i].y ,pretriangles[i].z);
			glNormal3f(pretriangles[i+1].x ,pretriangles[i+1].y ,pretriangles[i+1].z);
			glVertex3f(pretriangles[i+1].x ,pretriangles[i+1].y ,pretriangles[i+1].z);
			glNormal3f(pretriangles[i+2].x ,pretriangles[i+2].y ,pretriangles[i+2].z);
			glVertex3f(pretriangles[i+2].x ,pretriangles[i+2].y ,pretriangles[i+2].z);
			glEnd();
			glDisable(GL_DEPTH_TEST);

		}

		int tri_num = triangles.size()/3;
		for(int i = 0 ; i< tri_num*3 ; i+=3 )
		{
			
			glEnable(GL_DEPTH_TEST);
			glBegin(GL_LINE_LOOP);
			//glBegin(GL_TRIANGLES);
			glNormal3f(triangles[i].x ,triangles[i].y ,triangles[i].z);
			glVertex3f(triangles[i].x ,triangles[i].y ,triangles[i].z);
			glNormal3f(triangles[i+1].x ,triangles[i+1].y ,triangles[i+1].z);
			glVertex3f(triangles[i+1].x ,triangles[i+1].y ,triangles[i+1].z);
			glNormal3f(triangles[i+2].x ,triangles[i+2].y ,triangles[i+2].z);
			glVertex3f(triangles[i+2].x ,triangles[i+2].y ,triangles[i+2].z);
			glEnd();
			glDisable(GL_DEPTH_TEST);

		}
	}
private:
	void divide_triangle(const Point3D& p1, const Point3D& p2 ,const Point3D& p3 ,int n )
	{

		if(n>0)
		{
			Point3D new_p1,new_p2,new_p3;
			new_p1 = p1 + p2;
			normalize(new_p1);
			new_p2 = p1 + p3;
			normalize(new_p2);
			new_p3 = p2 + p3;
			normalize(new_p3);
			divide_triangle( p1, new_p2, new_p1 ,n-1);
			divide_triangle( p3 ,new_p3 ,new_p2 ,n-1);
			divide_triangle( p2, new_p1 ,new_p3 ,n-1);
			divide_triangle( new_p1 ,new_p2,new_p3,n-1);
			if( n == 1)
			{
				pretriangles.push_back(p1);
				pretriangles.push_back(p2);
				pretriangles.push_back(p3);
			}
		}
		else
		{
			triangle(p1 ,p2 ,p3);
		}
				
		
	}
	void triangle(const Point3D& p1, const Point3D& p2 ,const Point3D& p3)
	{
		triangles.push_back(p1);
		triangles.push_back(p2);
		triangles.push_back(p3);
		//glBegin(GL_LINE_LOOP);
		//glEnable(GL_DEPTH_TEST);
		//glBegin(GL_TRIANGLES);
		//glNormal3f(p1.x,p1.y,p1.z);
		//glVertex3f(p1.x,p1.y,p1.z);
		//glNormal3f(p2.x,p2.y,p2.z);
		//glVertex3f(p2.x,p2.y,p2.z);
		//glNormal3f(p3.x,p3.y,p3.z);
		//glVertex3f(p3.x,p3.y,p3.z);
		//glEnd();
		//glDisable(GL_DEPTH_TEST);
	}
	int depth;
};

inline void normalize(Point3D& p)
{
	float sum = 0.0f;
	sum = p.x*p.x + p.y*p.y + p.z*p.z;
	sum = sqrt(sum);
	if(sum>0)p.x = p.x/sum;p.y = p.y/sum;p.z = p.z/sum;
}
inline float dotproduct(const Vector& l , const Vector& r);
inline Vector crossproduct(const Vector& l ,const Vector& r);
inline Vector getReflect( Vector in_light , Vector normal ,Point intersect_point)
{
	return -2* dotproduct(in_light ,normal)*normal- in_light;
}
inline Vector getTransmit( Vector in_light , Vector normal ,Point intersect_point)
{

}
inline Color getPhongColor(Vertex intersected ,Vector in_light)
{

}
inline float dotproduct(const Vector& l , const Vector& r)
{
	return 0.0f;
}
inline Vector crossproduct(const Vector& l ,const Vector& r)
{
	return Vector();
}
enum statustype
{
	light_source,
	no_intersection
};
struct intersect_status
{
	statustype status;
};
static int  itermax = 30;
static Color background_color;
static Color light_source_color;
//return the intersected point
Vertex intersect( Point startpoint, Vector lightdirect ,intersect_status& status);
Color trace(Point p , Vector d ,int step);

#endif