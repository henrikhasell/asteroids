#include "object.h"

/*********************************************************/
/* These preprocessor defines allow for the subsystem to */
/* convert between  radians (used by the C math library) */
/* and degrees (used by OpenGL 1.1).                     */
/*********************************************************/
#define degrees(rad) ( ( 180.0f / 3.14159f ) * rad )
#define radians(deg) ( ( 3.14159f / 180.0f ) * deg )

static Vertex TransformVertex(Object *object, Vertex *vertex){
	
        float cos_val = cosf(radians(object->rotation));
        float sin_val = sinf(radians(object->rotation));
        
	    Vertex v = {
            object->x + (cos_val * vertex->x - sin_val * vertex->y) * object->scale,
            object->y + (sin_val * vertex->x + cos_val * vertex->y) * object->scale
        };
        
        
        return v;

}

void DrawObject(Object *object){
    /****************************************************/
    /* This function can easily be modified to change   */
    /* the drawing behaviour of object data structures. */
    /****************************************************/
    glPushMatrix();
        /******************************************/
        /* Manipulate the active matrix to        */
        /* correctly position the object polygon. */
        /******************************************/
        glTranslatef(object->x, object->y, 0.0f);
        glRotatef(object->rotation, 0.0f, 0.0f, 1.0f);
        glScalef(object->scale, object->scale, 1.0f);
        /****************************/
        /* Draw the object polygon. */
        /****************************/
        DrawPolygon(object->shape);
    glPopMatrix();
}

int PointInsideObject(Object *object, float x, float y){
    int i, j, collision = 0;
    for (i = 0, j = object->shape->size-1; i < object->shape->size; j = i++) {
        /************************************************/
        /* vi and vj represent the real-world verticies */
        /* of the object's polygon.                     */
        /************************************************/
        Vertex vi = TransformVertex(object, object->shape->verticies + i);
        Vertex vj = TransformVertex(object, object->shape->verticies + j);
        /******************************************/
        /* If the line v goes through the y axis. */
        /******************************************/
        if ( ( vi.y > y ) ^ ( vj.y > y ) ){
            /************************************************************/
            /* If the lines intersect on the correct side of the point. */
            /************************************************************/
            if( ( x < ( vj.x - vi.x ) * ( y - vi.y ) / ( vj.y - vi.y ) + vi.x ) ){
                collision = !collision;
            }
        }
    }
    
    return collision;
}

int ObjectInsideObject(Object *obj1, Object *obj2){
	int i;
	for (i = 0; i < obj1->shape->size; i++){	
		Vertex vertex = TransformVertex(obj1, obj1->shape->verticies + i);
		if(PointInsideObject(obj2, vertex.x, vertex.y)){
			return 1;
		}
	}
	
	for (i = 0; i < obj2->shape->size; i++){	
		Vertex vertex = TransformVertex(obj2, obj2->shape->verticies + i);
		if(PointInsideObject(obj1, vertex.x, vertex.y)){
			return 1;
		}
	}
	
	return 0;
}
