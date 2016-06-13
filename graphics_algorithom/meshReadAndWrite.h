#ifndef _MESH_READ_AND_WRITE_
#define _MESH_READ_AND_WRITE_
class MeshModelType;
namespace _HHY_MESH_
{
	class ReadWriteManager{
	public:
		static ReadWriteManager& getInstance(){
			static ReadWriteManager my_instance;

			return my_instance;
		}
		int readMesh(char* path ,MeshModelType& _model );
	private:
		ReadWriteManager();;
	};

}

#endif
