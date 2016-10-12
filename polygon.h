/***************************************************************************/
/* This module provides all the necessary resources to represent polygons. */
/* This includes displaying polygons and repreenting verticies.            */
/***************************************************************************/
#ifndef POLYGON_H
#define POLYGON_H

/********************************************************************/
/* The library used for OpenGL context creation is included here.   */
/* This can include any library based off of the GLUT API. However, */
/* it is reccomended to use FreeGLUT as this code is optimised for  */
/* FreeGLUT extensions.                                             */
/********************************************************************/
#ifdef __APPLE__
#   include "GLUT/glut.h"
#else
#   include "GL/glut.h"
#endif

/*************************************************************************/
/* OpenGL headers are included here. The compiler considers the platform */
/* the compiler is aimed at, adjusting it's include paths appropriately. */
/*************************************************************************/
#if __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#endif

/********************************************************/
/* This vertex structure is used to represent the shape */
/* of a polygon as a one dimensional array.             */
/********************************************************/
typedef struct Vertex{
    float x;
    float y;
}Vertex;

/****************************************************************/
/* This ConcavePolygon structure represents a 2D complex shape. */
/* While the structure does not need to represent a polygon     */
/* which is Concave, it is able to represent both Concave and   */
/* Convex polygons.                                             */
/****************************************************************/
typedef struct ConcavePolygon{
    /******************************************/
    /* This vertex array points to the        */
    /* verticies which represent the polygon. */
    /******************************************/
    Vertex *verticies;
    /**************************************/
    /* This integer holds the size of the */
    /* vertex array.                      */
    /**************************************/
    int size;
}ConcavePolygon;

/************************************************************************************/
/* This function draws a polygon. It can be modified to change rendering behaviour. */
/* Currently, this function is essentially a front end to DrawVerticies().          */
/************************************************************************************/
void DrawPolygon(ConcavePolygon *polygon);

/*******************************************************************/
/* This function draws an array of Verticies as a polygon outline. */
/*******************************************************************/
void DrawVerticies(Vertex *pointer, int size);

#endif /* POLYGON_H */
