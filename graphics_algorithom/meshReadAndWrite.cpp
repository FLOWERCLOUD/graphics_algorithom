#include "meshReadAndWrite.h"
#include "mytype.h"
namespace _HHY_MESH_
{
	class Reader
	{public:
		virtual bool read(char* path ,MeshModelType& _model) = 0;
	};
	class OBJ_reader
	{
	public:
		int read(char* path ,MeshModelType& _model)
		{
			char pref[3];
			_model.clear();
			FILE* fd = get_mesh_model_scale(path, &(_model.n_vertex),&(_model.n_noraml),&(_model.n_triangle) );
			if(fd)
			{
				while( fscanf(fd ,"%2s",pref) != EOF)
				{
					VertexType vt;
					if(strcmp(pref,"v")==0)
					{
						fscanf(fd, "%f %f %f",&(vt.vtx.x),&(vt.vtx.y),&(vt.vtx.z));
						_model.vertex_array.push_back(vt);
					}else if(strcmp(pref,"vn") ==0)
					{
						NormalType nt;
						fscanf(fd,"%f %f %f",&(nt.vtx.x),&(nt.vtx.y),&(nt.vtx.z));
						_model.normal_array.push_back(nt);
					}else if( strcmp(pref,"f")==0)
					{   
						TriangleType tt;
						for(int i_v = 0; i_v<3 ; i_v++)
						{
							fscanf(fd, "%d",&tt.i_vertex[i_v]);
							if((pref[0] = (char)getc(fd)) ==' ')
							{
								while( (pref[0] = (char)getc(fd)) ==' ');
								if( pref[0] == '\n'||pref[0]==EOF )
								{

								}else
								{
									ungetc(pref[0],fd);
								}
							}
							else if(pref[0] =='/')
							{
								if( (pref[0] = (char)getc(fd))!='/')
								{
									//while((char)get(fd) ==" ");
									ungetc(pref[0],fd);
									fscanf(fd ,"%d");
									if( (pref[0] = (char)getc(fd))!='/')
									{
										fscanf(fd,"%d",&tt.i_norm[i_v]);
									}

								}else{
									fscanf(fd,"%d",&tt.i_norm[i_v]);

								}								

							}
							
						}
						tt.i_vertex[0]--;tt.i_norm[0]--;
						tt.i_vertex[1]--;tt.i_norm[1]--;
						tt.i_vertex[2]--;tt.i_norm[2]--;
						_model.triangle_array.push_back(tt);
					}else if(pref[0] =='#')
					{
						skip_this_line(fd);
					}
					else skip_this_line(fd);
				}
				fclose(fd);
				return 0;
			}else
			{		
				return -1;
			}
			
		}
	private:
		FILE* get_mesh_model_scale(const char* path ,
			my_size_type* n_vertex,
			my_size_type* n_normal,
			my_size_type* n_triangle)
		{
			FILE* fd = fopen(path ,"r");
			char pref[3];  //µÚÈý¸ö×Ö·û´æ"\0"
			if(fd)
			{
				*n_vertex = *n_normal = *n_triangle;
				while(fscanf(fd,"%2s",pref)!= EOF)
				{
					if( strcmp(pref, "v")==0) *n_vertex+=1;
					else if(strcmp(pref,"vn")==0)*n_normal +=1;
					else if(strcmp(pref,"f")==0)*n_triangle+=1;
					else{
						skip_this_line(fd);
					}
				}
				fseek(fd,SEEK_SET,0);
			}else
			{
				return NULL;
			}

			return fd;

		}
		void skip_this_line(FILE* fd)
		{
			int ret =0;
			while( ret = fgetc(fd)!= '\n'&& ret !=EOF );

		}
	};
	int ReadWriteManager::readMesh(char* path ,MeshModelType& _model)
	{
		OBJ_reader* reader;
		Mesh_File_Type mesh_type = OBJ;
		if( mesh_type == OBJ )
		{
			reader = new OBJ_reader();
		}else
		{
	
		}
		int ret;		
		if( ret = reader->read(path,_model) !=0)
		{
			fprintf(stderr, "file: %s - ", path);
			delete reader;
			return ret;
		}
		delete reader;

		return 0;
	}

	ReadWriteManager::ReadWriteManager()
	{

	}



}

