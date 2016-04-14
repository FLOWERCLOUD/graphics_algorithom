#include "kdtree2d.h"
#include <limits.h>
#include <math.h>
#include <iostream>
using namespace std;



Node* KdTreeBuilder::build(vector<Point2D> pointarray)
{

	//1. find the center point
	float minx ,miny;
	float maxx,maxy;
	minx = miny =  10000;
	maxx= maxy = -100000;
	for(size_t i = 0 ;i < pointarray.size() ;++i)
	{
		if( pointarray[i].x <minx )
		{
			minx = pointarray[i].x;
		}
		if( pointarray[i].y < miny )
		{
			miny = pointarray[i].y;
		}
		if( pointarray[i].x > maxx )
		{
			maxx = pointarray[i].x;
		}
		if( pointarray[i].x > maxy )
		{
			maxy = pointarray[i].y;
		}
	}
	WrapBox wrapbox;
	wrapbox.ne = Point2D(maxx ,maxy);
	wrapbox.sw = Point2D(minx ,miny);
	wrapbox.nw = Point2D(minx ,maxy);
	wrapbox.se = Point2D(maxx ,miny);

	
	Node* root = buildcore(pointarray ,wrapbox);
	return root;
}

Node* KdTreeBuilder::build(float  xarray[] ,float yarray[] , int size)
{
	vector<Point2D> array;
	for(int i = 0 ; i<size ;++i)
	{
		Point2D point;
		point.x = xarray[i];
		point.y = yarray[i];
		array.push_back(point);
	}
	return build(array);
}

Node* KdTreeBuilder::buildcore(std::vector<Point2D> pointarray ,WrapBox& wrapbox)
{
	if(!pointarray.size())return NULL;
	Node* node = new Node();
	node->wrapbox = wrapbox;
	if(pointarray.size() ==1)
	{
		node->x = pointarray[0].x;
		node->y = pointarray[0].y;
		return node;
	}
	float centerx ,centery;
	centerx = wrapbox.nw.x + (wrapbox.ne.x - wrapbox.nw.x)/2;
	centery = wrapbox.se.y + (wrapbox.ne.y - wrapbox.se.y)/2;
	float mindis = 10000;
	float centerpointx, centerpointy;
	int centeridx = 0;
	for(size_t i = 0 ;i < pointarray.size() ;++i)
	{
		float distance = sqrt( ( pointarray[i].x -centerx)*(pointarray[i].x -centerx) +
			(pointarray[i].y -centery)*(pointarray[i].y -centery) );
		if(distance <mindis)
		{
			mindis = distance;
			centerpointx = pointarray[i].x;
			centerpointy = pointarray[i].y;
			centeridx = i;
		}

	}

	cout<< "minx: "<<wrapbox.sw.x<<" miny: "<<wrapbox.sw.y<<" maxx: "<<wrapbox.ne.x<<" maxy: "<<wrapbox.ne.y<<endl;

	//2.divide space into four part according to the center point
	WrapBox newrapbox,swwrapbox, nwwrapbox , sewrapbox;
	newrapbox.ne = wrapbox.ne;
	newrapbox.sw = Point2D(centerpointx ,centerpointy);
	newrapbox.nw = Point2D(centerpointx ,wrapbox.ne.y);
	newrapbox.se = Point2D(wrapbox.ne.x ,centerpointy);

	swwrapbox.ne = Point2D(centerpointx ,centerpointy);
	swwrapbox.sw = wrapbox.sw;
	swwrapbox.nw = Point2D(wrapbox.sw.x ,centerpointy);
	swwrapbox.se = Point2D(centerpointx, wrapbox.sw.y);

	nwwrapbox.ne = Point2D(centerpointx ,wrapbox.nw.y);
	nwwrapbox.sw = Point2D(wrapbox.nw.x, centerpointy);
	nwwrapbox.nw = wrapbox.nw;
	nwwrapbox.se = Point2D(centerpointx ,centerpointy);

	sewrapbox.ne = Point2D(wrapbox.se.x,centerpointy);
	sewrapbox.sw = Point2D(centerpointx ,wrapbox.se.y);
	sewrapbox.nw = Point2D(centerpointx ,centerpointy);
	sewrapbox.se = wrapbox.se;
	vector<Point2D> nwarray, nearray ,swarray ,searray;
	for(size_t i = 0 ;i < pointarray.size() ;++i)
	{
		if(i == centeridx)continue;;  //skip the center point
		if( pointarray[i].x <=centerpointx && pointarray[i].y <=centerpointy)
		{
			swarray.push_back(pointarray[i]);
			continue;;
		}
		if( pointarray[i].x >= centerpointx && pointarray[i].y <=centerpointy)
		{
			searray.push_back(pointarray[i]);
			continue;;
		}
		if( pointarray[i].x <= centerpointx && pointarray[i].y >=centerpointy)
		{
			nwarray.push_back(pointarray[i]);
			continue;
		}
		nearray.push_back(pointarray[i]);
	}
	node->x =centerpointx;
	node->y = centerpointy;
	node->ne = buildcore(nearray ,newrapbox);
	node->nw = buildcore(nwarray ,nwwrapbox);
	node->se = buildcore(searray ,sewrapbox);
	node->sw = buildcore(swarray ,swwrapbox);
	return node;
}

void Node::freeNode(Node*& node)
{
	if(node)
	{
		if(node->ne)freeNode(node->ne);
		if(node->sw)freeNode(node->sw);
		if(node->nw)freeNode(node->nw);
		if(node->se)freeNode(node->se);
		delete node;
		node = NULL;
	}
}
void Node::printNode(Node* node)
{
	if(node)
	{
		std::cout<<"Node: "<<"<"<<node->x<<","<<node->y<<">"<<std::endl;
		if(node->ne)printNode(node->ne);
		if(node->sw)printNode(node->sw);
		if(node->nw)printNode(node->nw);
		if(node->se)printNode(node->se);

	}
}
void Node::printNode(Node* node ,int depth)
{
	if(node)
	{
		for(int i = 0 ;i <depth ;++i)
		{
			cout<<"¡ª¡ª";
		}
		std::cout<<"Node: "<<"<"<<node->x<<","<<node->y<<">"<<std::endl;
		if(node->ne)printNode(node->ne,depth+1);
		if(node->sw)printNode(node->sw,depth+1);
		if(node->nw)printNode(node->nw,depth+1);
		if(node->se)printNode(node->se,depth+1);

	}

}



