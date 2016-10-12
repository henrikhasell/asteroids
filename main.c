/***********************************************************************************/
/* The library used for OpenGL context creation is included here. This can include */
/* any library compatible with the GLUT API. However, it is reccomended to use     */
/* FreeGLUT as this code is optimised for FreeGLUT extensions.                     */
/***********************************************************************************/
#ifdef __APPLE__
#   include "GLUT/glut.h"
#else
#   include "GL/glut.h"
#endif

/***************************************/
/* OpenGL headers are included here.   */
/* The compiler considers the platform */
/* the compiler is aimed at, adjusting */
/* it's include paths appropriately.   */
/***************************************/
#if __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#endif

/**********************************/
/* Standard C library headers are */
/* included here. Include guards  */
/* ensure that appropriate        */
/* headers are included for both  */
/* C and C++ compilers.           */
/**********************************/
#ifdef __cplusplus
#   include <cstdlib>
#   include <cstdio>
#   include <cmath>
#else
#   include <stdlib.h>
#   include <stdio.h>
#   include <math.h>
#endif
/******************************************************/
/* This header file includes function declerations    */
/* and data types used for representing linked lists. */
/* They are required to store objct data.             */
/******************************************************/
#include "list.h"
/***************************************************/
/* This header file includes function declerations */
/* which allow for basic text rendering.           */
/***************************************************/
#include "glyph.h"
/************************************************/
/* This header file includes the necessary data */
/* to represent 2D objects in the application.  */
/* It is included to assist with rendering and  */
/* manipulating 2D objects.                     */
/************************************************/
#include "object.h"
/***************************************************************************/
/* These preprocessor defines allow for the application to convert between */
/* radians (used by the C math library) and degrees (used by OpenGL 1.1).  */
/***************************************************************************/
#define degrees(rad) ( ( 180.0f / 3.14159f ) * rad )
#define radians(deg) ( ( 3.14159f / 180.0f ) * deg )
/***********************************************/
/* This preprocessor define denotes the number */
/* of stars in the application. It can be      */
/* adjusted to allow for any number of stars,  */
/* within reason.                              */
/***********************************************/
#define NUMBER_OF_STARS 32
/*************************************************/
/* Each star is represented by a vertex, as only */
/* positional data is required to render a star  */
/* (each star is a point in space).              */
/*************************************************/
Vertex star_array[NUMBER_OF_STARS];
/***************************************************/
/* This linked list stores all asteroid objects.   */
/*It is initialised in the initContext() function. */
/***************************************************/
LinkedList *asteroid_list = NULL;

typedef struct Bullet{
    float x;
    float y;
    float velocity_x;
    float velocity_y;
    float life;
}Bullet;

LinkedList *bullet_list = NULL;

/**********************************************/
/* This vertex array represents the verticies */
/* inside the asteroid_1 polygon.             */
/**********************************************/
Vertex asteroid_1_verticies[] = {
    { -0.258829f, -0.466654f }, { -0.026869f, -0.217373f },
    {  0.229284f, -0.486908f }, {  0.473549f, -0.231049f },
    {  0.343808f,  0.036211f }, {  0.468176f,  0.270399f },
    {  0.116252f,  0.513091f }, { -0.292469f,  0.513091f },
    { -0.526451f,  0.272889f }, { -0.526451f, -0.203697f }
};
/**********************************************/
/* This vertex array represents the verticies */
/* inside the asteroid_2 polygon.             */
/**********************************************/
Vertex asteroid_2_verticies[] = {
    {  0.093883f, -0.003426f }, {  0.463877f, -0.152118f }, {  0.473194f, -0.265410f },
    {  0.112516f, -0.512724f }, { -0.262802f, -0.512724f }, { -0.174962f, -0.260859f },
    { -0.499283f, -0.260859f }, { -0.499283f,  0.130093f }, { -0.255886f,  0.479549f },
    {  0.126392f,  0.356185f }, {  0.241383f,  0.487276f }, {  0.500717f,  0.231932f }
};
/**********************************************/
/* This vertex array represents the verticies */
/* inside the asteroid_3 polygon.             */
/**********************************************/
Vertex asteroid_3_verticies[] = {
    {  0.006423f, -0.327354f }, { -0.230594f, -0.457312f }, { -0.497797f, -0.197306f },
    { -0.345536f,  0.041065f }, { -0.497575f,  0.282259f }, { -0.230955f,  0.533400f },
    { -0.111968f,  0.396640f }, {  0.229570f,  0.525940f }, {  0.491186f,  0.142602f },
    {  0.253211f, -0.073727f }, {  0.502203f, -0.212973f }, {  0.255415f, -0.466600f }
};
/**********************************************/
/* This vertex array represents the verticies */
/* inside the asteroid_4 polygon.             */
/**********************************************/
Vertex asteroid_4_verticies[] = {
    {  0.004242f,  0.128464f }, {  0.004242f,  0.479359f }, {  0.233801f,  0.479359f },
    {  0.494881f,  0.128464f }, {  0.494881f, -0.197267f }, {  0.233801f, -0.520641f },
    {  0.004242f, -0.520641f }, { -0.085344f, -0.520641f }, { -0.474404f, -0.169746f },
    { -0.269635f, -0.033223f }, { -0.505119f,  0.138784f }, { -0.269635f,  0.469039f }
};
/**********************************************/
/* This vertex array represents the verticies */
/* inside the space_ship polygon.             */
/**********************************************/
Vertex space_ship_verticies[] = {
    {-0.50f,  0.50f },
    { 0.00f, -0.50f },
    { 0.50f,  0.50f },
    { 0.00f,  0.25f }
};

/***************************************************************/
/* Polygon objects are defined here. These represent object    */
/* shapes in a way that supports accurate collision detection. */
/***************************************************************/
ConcavePolygon asteroid_1 = { (Vertex*)&asteroid_1_verticies, 10 };
ConcavePolygon asteroid_2 = { (Vertex*)&asteroid_2_verticies, 12 };
ConcavePolygon asteroid_3 = { (Vertex*)&asteroid_3_verticies, 12 };
ConcavePolygon asteroid_4 = { (Vertex*)&asteroid_4_verticies, 12 };
ConcavePolygon space_ship = { (Vertex*)&space_ship_verticies, 4  };
/*************************************************************************/
/* This object struct represents the space ship the player will control. */
/* It is initially positioned at the center of the screen.               */
/*************************************************************************/
Object player = {&space_ship, 400.0f, 300.0f, 0.0f, 25.0f, 0.0f, 0.0f};
/********************************************************************/
/* These integers represent key states. They correspond to the keys */
/* needed to operate the space ship. Please see the keyboard() and  */
/* keyboardUp() callbacks for more information.                     */
/********************************************************************/
int up = 0, down = 0, left = 0, right = 0, fire = 0;
/******************************************/
/* This unsigned long keeps the score. It */
/* is displayed in the top left corner of */
/* the screen.                            */
/******************************************/
unsigned long score = 0;
/****************************************************************/
/* This unsigned long keeps track of the number of asteroids.   */
/* This feature was added to demonstrate asteroids do infact    */
/* respawn once all asteroids have been destoryed. Occasionally */
/* it appears all asteroids have been destroyed when infact one */
/* has drifted periodically offscreen .                         */
/****************************************************************/
unsigned long number_of_asteroids = 0;

#define PROJECT_TITLE "Coursework"

void initContext(int argc, char *argv[]);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void reshape(int width, int height);
void display(void);
void clean(void);
void timer(int i);

Object *CreateAsteroid();
Bullet *CreateBullet();

void initContext(int argc, char *argv[]){
    int count;
#ifdef __FREEGLUT_EXT_H__
    /*******************************************************************/
    /* If FreeGLUT extensions are available, the compiler will include */
    /* initialisation code to specify the required OpenGL context the  */
    /* application is optimised to.                                    */
    /*******************************************************************/
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_CORE_PROFILE);
#endif
    /*******************************************************/
    /* The GLUT framework is initialised here, followed by */
    /* OpenGL context creation and error handling.         */
    /*******************************************************/
    glutInitWindowSize(800, 600);
    glutInit(&argc, argv);
    if(glutCreateWindow(PROJECT_TITLE) < 1){
        printf("Failed to create a rendering window.\n");
        exit(EXIT_FAILURE);
    }
#ifdef _DEBUG
    /****************************************************************************/
    /* If appropriate, the application will print debug information relating to */
    /* the current OpenGL context. Namely information about the renderer.       */
    /****************************************************************************/
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));
    printf("OpenGL vendor: %s\n", glGetString(GL_VENDOR));
    printf("OpenGL renderer: %s\n", glGetString(GL_RENDERER));
#endif
    /************************************************************************/
    /* The application binds GLUT callbacks used to handle the application. */
    /* Namely, the window reshape and rendering callbacks.                  */
    /************************************************************************/
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
#ifdef __FREEGLUT_EXT_H__
    /*************************************************************************/
    /* If available, the application binds FreeGLUT callbacks used to handle */
    /* the application. Namely a close function intended to free memory      */
    /* after the application has finished.                                   */
    /*************************************************************************/
    glutCloseFunc(clean);
#endif
    /*****************************************************/
    /* The star array is initialised here. Every star is */
    /* positioned randomly within the screen bounds.     */
    /*****************************************************/
    for(count = 0; count < NUMBER_OF_STARS; count++){
        star_array[count].x = (float)(rand() % 800) + 1.0f;
        star_array[count].y = (float)(rand() % 600) + 1.0f;
    }
    /***********************************************/
    /* Initialise and configure OpenGL subsystems. */
    /***********************************************/
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
    glPointSize(2.0f);
    /************************************/
    /* Initialise the glyph subsystem,  */
    /* which allows for text rendering. */
    /************************************/
    InitialiseGlyph();

    asteroid_list = CreateLinkedList();
    bullet_list = CreateLinkedList();
}

/***************************************************************/
/* Keyboard function. According to the GLUT API, this function */
/* is called when the user presses a key. Each ASCII key press */
/* generates this callback.                                    */
/***************************************************************/
void keyboard(unsigned char key, int x, int y){
    switch(key){
    case 'W': case 'w': up    = 1; break;
    case 'S': case 's': down  = 1; break;
    case 'A': case 'a': left  = 1; break;
    case 'D': case 'd': right = 1; break;
              case ' ': fire  = 1; break;
    }
}

/******************************************************************/
/* Keyboard Up function. According to the GLUT API, this function */
/* is called when the user releases a key. Each ASCII key press   */
/* generates this callback.                                       */
/******************************************************************/
void keyboardUp(unsigned char key, int x, int y){
    switch(key){
    case 'W': case 'w': up    = 0; break;
    case 'S': case 's': down  = 0; break;
    case 'A': case 'a': left  = 0; break;
    case 'D': case 'd': right = 0; break;
              case ' ': fire  = 0; break;
    }
}

/***********************************************************************/
/* Reshape function. According to the GLUT API, this callback will     */
/* be triggered when the widnow is created and henceforth whenever the */
/* window is resized.                                                  */
/***********************************************************************/
void reshape(int width, int height){

    glViewport(0, 0, width, height);

    /**********************************************************/
    /* If the matricies are not affected by window dimensions */
    /* it may be more appropriate to include matrix           */
    /* manipulation functions in initContext().               */
    /**********************************************************/

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/***********************************************************************/
/* Display function. According to the GLUT API, this callback will be  */
/* triggered whenever the application should display graphical output. */
/* It can be triggered manualy with glutPostRedisplay().               */
/***********************************************************************/
void display(void){

    Link *l;
    int count;
    
    glClear(GL_COLOR_BUFFER_BIT);

    /* Draw every astereoid in the linked list. */
    for(l = asteroid_list->head; l; l = l->next){
        DrawObject((Object*)l->data);
    }

    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    /* Draw every star in the array. */
    for(count = 0; count < NUMBER_OF_STARS; count++){
        glVertex2fv((GLfloat*)(star_array + count));
    }
    glColor3f(1.0f, 0.0f, 0.0f);
    /* Draw every bullet in the linked list. */
    for(l = bullet_list->head; l; l = l->next){
        glVertex2fv((GLfloat*)l->data);
    }
    glEnd();

    /* Draw the player. */
    DrawObject(&player);
    
    /* Display the score. */
    glColor3f(0.0f, 1.0f, 1.0f);
    RenderString(5.0f, 5.0f, 16.0f, 16.0f, "Score: %010lu", score);
    
    /* Display the number of asteoirds. */
    glColor3f(1.0f, 1.0f, 0.2f);
    RenderString(5.0f, 26.0f, 8.0f, 8.0f, "Number of asteroids: %lu", number_of_asteroids);
    
    glFinish();
}

/***********************************************************************/
/* Close function. This callback is triggered when the window is about */
/* to be destroyed. In this application's case, this signifies the end */
/* of the application. Hence, allocated memoy should be freed here.    */
/* This function name diverts from the naming conventions used         */
/* elsewhere in this document because of naming conflicts with the     */
/* PSOIX file descriptor API.                                          */
/***********************************************************************/
void clean(void){
    Link *l;
    
    for(l = asteroid_list->head; l; l = l->next){
        free(l->data);
    }
    for(l = bullet_list->head; l; l = l->next){
        free(l->data);
    }
    DestroyLinkedList(asteroid_list);
    DestroyLinkedList(bullet_list);
    
    CleanupGlyph();
}

/*******************************************************************************/
/* Timer function. This is not a GLUT callback, but rather a function sheduled */
/* by the GLUT framework every 1000/60 miliseconds. It is intended to handle   */
/* game logic processing.                                                      */
/*******************************************************************************/
void timer(int i){
    /******************************************/
    /* These values are used by the for loops */
    /* below to iterate through linked lists. */
    /******************************************/
    Link *link;
    Link *link2;
    Link *next;
    /***************************************/
    /* This value is used by the for loops */
    /* below to iterate through arrays.    */
    /***************************************/
    int count;
    /*****************************************************************/
    /* This static integer is used to prevent the spaceship firing a */
    /* barrage of bullets; it limits firing to every fith call of    */
    /* this function.                                                */
    /*****************************************************************/
    static int bullet_cooldown = 5;
    bullet_cooldown--;
    /*******************************************************************/
    /* Schedule this function to be called again in 1.66 of a seconds. */
    /* This allows frame independent game logic.                       */
    /*******************************************************************/
    glutTimerFunc(1000/60, timer, ++i);
    /******************************************************************/
    /* This loop iterates through all asteroids in the game. It moves */
    /* each asteroid and repositions it if it goes off screen.        */
    /******************************************************************/
    for(link = asteroid_list->head; link; link = link->next){
        Object *asteroid = (Object*)link->data;
        /***************************************/
        /* Move the asteroid by it's velocity. */
        /***************************************/
        asteroid->x += asteroid->velocity_x;
        asteroid->y += asteroid->velocity_y;
        /*********************************************/
        /* Make sure the asteroid remains in bounds. */
        /*********************************************/
             if(asteroid->x < -50.0f){ asteroid->x += 900.0f; }
        else if(asteroid->x > 850.0f){ asteroid->x -= 900.0f; }
             if(asteroid->y < -50.0f){ asteroid->y += 700.0f; }
        else if(asteroid->y > 650.0f){ asteroid->y -= 700.0f; }
        /************************/
        /* Rotate the asteroid. */
        /************************/
        asteroid->rotation += 0.5f;
        /***************************************************************/
        /* Check is the asteroid collides with the player. If it does, */
        /* restart the game, decrease the life count and return.       */
        /***************************************************************/
        if(ObjectInsideObject(&player, asteroid)){
			/**************************************/
			/* Remove every asteroid in the game. */
			/**************************************/
			while(asteroid_list->head != NULL){
				free(asteroid_list->head->data);
				PopData(asteroid_list, asteroid_list->head->data);
			}
			/************************************/
			/* Remove every bullet in the game. */
			/************************************/
			while(bullet_list->head != NULL){
				free(bullet_list->head->data);
				PopData(bullet_list, bullet_list->head->data);
			}
			/**************************************************/
			/* Reset the score and update the asteorid count. */
			/**************************************************/
			score = 0;
			number_of_asteroids = 0;
			/*******************************************/
			/* Reset the player position and rotation. */
			/*******************************************/
			player.x = 400.0f;
			player.y = 300.0f;
			player.rotation = 0.0f;
			/**********************************/
			/* Set all the control data to 0. */
			/**********************************/
			//memset(&up, 0, sizeof(int) * 5);
			break;
		}
    }
    /**********************************************************/
    /* This loop iterates through every bullet in the game.   */
    /* It moves each bullet, decreases it's life span,        */
    /* destroys it if the life span has expired, then checks  */
    /* for collisions with asteroids.                         */
    /**********************************************************/
    for(link = bullet_list->head; link; link = next){
        Bullet *bullet = (Bullet*)link->data;
        /*******************************************************/
        /* The next link in the list. Used to allow the bullet */
        /* to be freed without causing access violations.      */
        /*******************************************************/
        next = link->next;
        /*******************************************************/
        /* Decrease the bullet's life, then check if it's life */
        /* span has expired. If so, remove the bullet and      */
        /* iterate to the next bullet.                         */
        /*******************************************************/
        bullet->life--;
        if(bullet->life <= 0){
            PopData(bullet_list, bullet);
            free(bullet);
            continue;
        }
        /*******************************************************/
        /* Move the bullet by it's velocity. If it travels out */
        /* of bounds move it back in.                          */
        /*******************************************************/
        bullet->x += bullet->velocity_x;
        bullet->y += bullet->velocity_y;
             if(bullet->x < -50.0f){ bullet->x += 900.0f; }
        else if(bullet->x > 850.0f){ bullet->x -= 900.0f; }
             if(bullet->y < -50.0f){ bullet->y += 700.0f; }
        else if(bullet->y > 650.0f){ bullet->y -= 700.0f; }
        /**********************************************************/
        /* Iterate through every asteroid in the game and compare */
        /* it to the current bullet position. If the bullet is    */
        /* inside the asteroid, destroy both the asteroid and the */
        /* bullet.                                                */
        /**********************************************************/
        for(link2 = asteroid_list->head; link2; link2 = link2->next){
            Object *asteroid = (Object*)link2->data;
            if(PointInsideObject(asteroid, bullet->x, bullet->y)){
                score += 10;
                number_of_asteroids--;
                /*******************************************************************/
                /* If the asteroid has been hit, check that it is an appropriate   */
                /* size to constitute being split. Each asteroid bigger than 25.0f */
                /* is split into three parts, each half the size of the original.  */
                /*******************************************************************/
                if(asteroid->scale > 25.0f){
					int i;
					/*****************************************************/
					/* Changing the number of iterations in this loop to */
					/* ridiculously large numbers is very fun and highly */ 
					/* reccomended!                                      */
					/*****************************************************/
					for(i = 0; i < 3; i++){
						/***************************************************/
						/* Create a new asteroid, representing a fragment. */
						/***************************************************/
						Object *fragment = CreateAsteroid();
						/***************************************************/
						/* Position the fragment to the asteroid location. */
						/***************************************************/
						fragment->x = asteroid->x;
						fragment->y = asteroid->y;
						/********************************************************/
						/* Set the fragment size to half the original asteroid. */
						/********************************************************/
						fragment->scale = asteroid->scale * 0.5f;
					}
                }
                /*************************************************/
                /* Remove the asteroid and the bullet from their */
                /* respective linked lists, then free the memory */
                /* that stores their data.                       */
                /*************************************************/
                PopData(asteroid_list, asteroid);
                free(asteroid);
                PopData(bullet_list, bullet);
                free(bullet);
                /*****************************************/
                /* Since the bullet is destroyed, do not */
                /* iterate through any more asteorids.   */
                /*****************************************/
                break;
            }
        }
    }
    /**********************************************************************/
    /* This loop iterates through every index in the star array and moves */
    /* every star downwards, then repositions them if they go offscreen.  */
    /**********************************************************************/
    for(count = 0; count < NUMBER_OF_STARS; count++){
        star_array[count].y += 5.0f;
        while(star_array[count].y > 600.0f){
            star_array[count].y -= 600.0f;
        }
    }
    /************************************************/
    /* These conditional statements move the player */
    /* if the appropriate keys are pressed.         */
    /************************************************/
    if(up){
        player.x += sinf(radians(player.rotation)) * 2.5f;
        player.y -= cosf(radians(player.rotation)) * 2.5f;
    }
    if(down){
        player.x -= sinf(radians(player.rotation)) * 2.5f;
        player.y += cosf(radians(player.rotation)) * 2.5f;
    }
    if(left){
        player.rotation -= 5.0f;
    }
    if(right){
        player.rotation += 5.0f;
    }
    /*************************************************************/
    /* This conditional statement fires a bullet from the player */
    /* position if the appropriate key is pressed and the        */
    /* bullet_cooldown variable is <= 0.                         */
    /*************************************************************/
    if(fire && bullet_cooldown <= 0){
        CreateBullet();
        bullet_cooldown = 10;
    }
    /****************************************************************/
    /* This code ensures that the player does not drift off screen. */
    /****************************************************************/
         if(player.x < -50.0f){ player.x += 900.0f; }
    else if(player.x > 850.0f){ player.x -= 900.0f; }
         if(player.y < -50.0f){ player.y += 700.0f; }
    else if(player.y > 650.0f){ player.y -= 700.0f; }
    /***************************************/
    /* If there are no asteroids present,  */
    /* this piece of code adds 5 new ones. */
    /***************************************/
    if(!asteroid_list->head){
        CreateAsteroid();
        CreateAsteroid();
        CreateAsteroid();
        CreateAsteroid();
        CreateAsteroid();
    }
    /****************************************************/
    /* Tell GLUT that the scene needs redisplaying.     */
    /* This forces the application to redraw the scene. */
    /****************************************************/
    glutPostRedisplay();
}
/***************************************************/
/* This functions adds an asteroid to the game.    */
/* It does this by allocating memory, initialising */
/* it's values and pushing it to the linked list.  */
/***************************************************/
Object *CreateAsteroid(){
    /***********************************************************/
    /* Determine the angle which the asteroid will move along. */
    /***********************************************************/
    float angle = radians( (float)(rand() % 360) );
    /*****************************************************/
    /* Allocate memory for a new asteroid and insure the */
    /* memory allocation was successful.                 */
    /*****************************************************/
    Object *asteroid = (Object*)malloc(sizeof(Object));
    if(asteroid == NULL){
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    /*******************************************************/
    /* Set a randomised polygon for the asteroid (1 in 4). */
    /*******************************************************/
    switch(rand() % 4){
    case 0: asteroid->shape = &asteroid_1;
        break;
    case 1: asteroid->shape = &asteroid_2;
        break;
    case 2: asteroid->shape = &asteroid_3;
        break;
    case 3: asteroid->shape = &asteroid_4;
        break;
    }
    /**********************************************************/
    /* Set values relating to the object collision detection. */
    /**********************************************************/
    asteroid->scale = 100.0f;
    asteroid->rotation = 0.0f;
    /*************************************************/
    /* Set the asteroid starting position. This code */
    /* positions the new asteroid randomly in the    */
    /* same manner as the original game.             */
    /*************************************************/
    switch(rand() % 2){
    case 0:
        /**************************************/
        /* Place the asteroid offscreen, in a */
        /* random position along the x axis.  */
        /**************************************/
        asteroid->x = (float)(rand() % 800);
        asteroid->y = 650.0f;
        break;
    case 1:
        /**************************************/
        /* Place the asteroid offscreen, in a */
        /* random position along the y axis.  */
        /**************************************/
        asteroid->x = 850.0f;
        asteroid->y = (float)(rand() % 600);
        break;
    }
    //asteroid->x = 400.0f;
    //asteroid->y = 300.0f;
    /*****************************************/
    /* Set the asteroid velocity (constant). */
    /*****************************************/
    asteroid->velocity_x =  sinf(angle) * 1.0f;
    asteroid->velocity_y = -cosf(angle) * 1.0f;
    /****************************************/
    /* Add the asteroid to the linked list. */
    /****************************************/
    PushData(asteroid_list, asteroid);

    number_of_asteroids++;

    return asteroid;
}

Bullet *CreateBullet(){
    /***********************************************/
    /* Attempt to allocate memory then insure that */
    /* memory allocation is successful.            */
    /***********************************************/
    Bullet *bullet = (Bullet*)malloc(sizeof(Bullet));
    if(bullet == NULL){
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    /*******************************************************/
    /* Position the new bullet at the tip of the player's  */
    /* space ship, then set the bullet's x any y velocity. */
    /*******************************************************/
    bullet->x = player.x + sinf(radians(player.rotation)) * 12.5f;
    bullet->y = player.y - cosf(radians(player.rotation)) * 12.5f;
    bullet->velocity_x = + sinf(radians(player.rotation)) * 5.0f;
    bullet->velocity_y = - cosf(radians(player.rotation)) * 5.0f;
    /***************************************/
    /* Set the bullet's life span and add  */
    /* it to the bullet linked list.       */
    /***************************************/
    bullet->life = 100.0f;
    PushData(bullet_list, bullet);

    return bullet;
}

int main(int argc, char *argv[]){
    /*********************************************************/
    /* Initialise an OpenGL context, GLUT/FreeGLUT callbacks */
    /* and application resources.                            */
    /*********************************************************/
    initContext(argc, argv);
    /******************************************/
    /* Schedule the repeating timer function. */
    /* Please see "timer()" for more details. */
    /******************************************/
    glutTimerFunc(1000/60, timer, 0);
    /*************************************************************/
    /* Start the GLUT main loop. This loop will never return,    */
    /* no cleanup code should be placed below this funtion call. */
    /*************************************************************/
    glutMainLoop();

    return 0;
}
