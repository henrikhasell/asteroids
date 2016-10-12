#include "polygon.h"

void DrawPolygon(ConcavePolygon *polygon){
    /**********************************/
    /* Set the colour of the polygon. */
    /**********************************/
    glColor3f(1.0f, 1.0f, 1.0f);
    /*****************************************/
    /* Pass the polygon verticies and vertex */
    /* array length to DrawVerticies().      */
    /*****************************************/
    DrawVerticies(polygon->verticies, polygon->size);
}

void DrawVerticies(Vertex *pointer, int size){
    int count;
    /***************************************/
    /* Begin drawing in mode GL_LINE_LOOP. */
    /***************************************/
    glBegin(GL_LINE_LOOP);
    for(count = 0; count < size; count++){
        /*******************************************/
        /* Create a pointer to the current vertex. */
        /*******************************************/
        Vertex *current_vertex = (pointer + count);
        /****************************/
        /* Draw the current vertex. */
        /****************************/
        glVertex2fv((GLfloat*)current_vertex);
    }
    glEnd();
}
