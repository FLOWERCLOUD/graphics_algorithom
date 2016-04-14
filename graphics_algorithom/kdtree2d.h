#ifndef __KD_TREE_2D_
#define __KD_TREE_2D_
#include <vector>
class Point2D
{
public:
	Point2D()
	{
		x = 0.0f;
		y= 0.0f;
	}
	Point2D( float x ,float y)
	{
		this->x = x;
		this->y = y;
	}
	Point2D( const Point2D& p)
	{
		this->x = p.x;
		this->y = p.y;
	}
	float x;
	float y;
};
class	WrapBox
{
public:
	WrapBox()
	{
	
	}
	WrapBox(Point2D& _nw ,Point2D& _ne ,Point2D& _sw ,Point2D& _se)
		:nw(_nw),ne(_ne),sw(_sw),se(_se)
	{
		
	}
	Point2D nw;
	Point2D ne;
	Point2D sw;
	Point2D se;
	
	
};
class Node
{
public:
	static void freeNode(Node*& node);
	static void printNode(Node* node);
	static void printNode(Node* node ,int depth);
	Node()
	{
		x = y = 0.f;
		nw = ne = se = sw = NULL;
	}
	Node( float x ,float y)
	{
		this->x = x;
		this->y = y;
		nw = ne = se = sw = NULL;
	}
	~Node()
	{
		 freeNode(nw);
		 freeNode(ne);
		 freeNode(sw);
		 freeNode(se);
	}
	
	float x;
	float y;
	WrapBox wrapbox;
	Node* nw;//  north west
	Node* ne;
	Node* sw;
	Node* se;
};

class KdTreeBuilder
{
public:
	Node* buildcore(std::vector<Point2D> pointarray ,WrapBox& wrapbox );
	Node* build(std::vector<Point2D> pointarray);
	Node* build(float xarray[] ,float  yarray[] , int size);

};



#endif