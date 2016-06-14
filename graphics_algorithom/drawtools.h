#ifndef  _DRAW_TOOLS
#define  _DRAW_TOOLS

class Node;
class Point3D;
void draw(Node* tree);
void drawgrid(int rows ,int cols);
void drawpoint(int indexrow,int indexcol);
void drawline(int indexrow1,int indexcol1 ,int indexrow2,int indexcol2);
void drawCube(const Point3D& lefdown ,const Point3D& rightTop);
void drawAxis( float xrotate ,float yrotate ,float zrotate);
class MeshModelType;
void renderMeshModel(const MeshModelType* const _model);
void renderMeshModelWired(const MeshModelType* const _model);
void renderPanel(void);
class gl_Material;
void SetMaterial(const gl_Material *material);

#endif