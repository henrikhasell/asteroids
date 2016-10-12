/*************************************************************************************/
/* This subsystem provides all the necessary abstractions to represent an object in  */
/* 2D space. It also provides functions to conduct verious operations on 2D objects. */
/*************************************************************************************/
#ifndef OBJECT_H
#define OBJECT_H

/***********************************************************************************/
/* The library used for OpenGL context creation is included here. This can include */
/* any library based off of the GLUT API. However, it is reccomended to use        */
/* FreeGLUT as this code is optimised for FreeGLUT extensions.                     */
/***********************************************************************************/
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

#ifdef _cpluplus
#   include <cmath>
#else
#   include <math.h>
#endif

/*******************************************************/
/* Objects are represented as polygons. Therefore,     */
/* the polygon subsystem is required to abstract them. */
/*******************************************************/
#include "polygon.h"

/**********************************************************************/
/* This struct represents a 2D object as a polygon with a position,   */
/* scale, and rotation. It's intended purpouse is to simplify polygin */
/* collision detection.                                               */
/**********************************************************************/
typedef struct Object{
    /****************************************************/
    /* This pointer represents the shape of the object. */
    /* Multiple objects can point to a single polygon   */
    /* to avoid memory duplication.                     */
    /****************************************************/
    ConcavePolygon *shape;
    /****************************************/
    /* The positional data of the object is */
    /* represented by the following floats. */
    /****************************************/
    float x;
    float y;
    /**************************************/
    /* The following int represents the   */
    /* rotation of the object in degrees. */
    /**************************************/
    float rotation;
    /***************************************/
    /* Polygon coordinates are normalised. */
    /* This float represents the scale of  */
    /* the object polygon.                 */
    /***************************************/
    float scale;
    /**********************************/
    /* This pair of floats represents */
    /* the velocity of the object.    */
    /**********************************/
    float velocity_x;
    float velocity_y;
}Object;

/*********************************************************/
/* This function draws an object. This function utilises */
/* DrawPolygon() to render the object shape.             */
/*********************************************************/
void DrawObject(Object *object);

int PointInsideObject(Object *object, float x, float y);

int ObjectInsideObject(Object *obj1, Object *obj2);

#endif /* OBJECT_H */
