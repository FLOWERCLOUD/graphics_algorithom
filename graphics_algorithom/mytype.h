#ifndef __MY_TYPE__
#define __MY_TYPE__
#include <vector>
typedef int my_size_type;
typedef int my_index_type;
typedef float my_real_type;

struct VertexTypeStruct
{
	my_real_type x,y,z;
};
class VertexType
{
public:
	union{
		my_real_type array[3];
		struct VertexTypeStruct vtx;
	};
	
};
typedef VertexType NormalType;
class TriangleType
{
public:
	TriangleType()
	{
		i_vertex[0] =i_vertex[1] = i_vertex[2] = 0;
		i_norm[0]= i_norm[1] = i_norm[2] = 0;
	}
	my_index_type i_vertex[3];
	my_index_type i_norm[3];
};

class MeshModelType
{
public:
	void clear()
	{
		n_vertex = n_noraml = n_triangle =0;
		vertex_array.clear();
		normal_array.clear();
		triangle_array.clear();

	}
	std::vector<VertexType> vertex_array;
	std::vector<NormalType> normal_array;
	std::vector<TriangleType> triangle_array;
	my_size_type n_vertex;
	my_size_type n_noraml;
	my_size_type n_triangle;
	
};

enum Mesh_File_Type
{
	OBJ,PLY,OFF
};

class gl_Material
{public:
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float shininess[4];
};

#endif