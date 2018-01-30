#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

/*Podaci za matricu*/
#define DIMENZIJA_MATRICE 50
#define MAX_ZMIJICA 50*50
/***************************/
#define TIMER_ID 0
#define TIMER_INTERVAL 100

/*Empirijski utvrdjen makro*/
#define GRANICA_KOEF 3.9


typedef struct polje_zmijice{
    float x_koordinata;
    float y_koordinata;
}Polje_zmijice;

Polje_zmijice zmijica[100];
int duzina_zmijice = 2;

static int uToku = 0;

float brzina = 0.3;

static float koefX = 0;
static float koefY = 0;
static float koefZ = 0;

enum {
    levo = 1,
    gore = 2,
    desno = 3,
    dole = 4
} Smer;

static void on_display(void);
static void on_reshape(int sirina, int visina);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int id);
void pomeri_zmijicu();

int main(int argc, char** argv){
    
    zmijica[0].x_koordinata = 250;
    zmijica[0].y_koordinata = 250;
    zmijica[1].x_koordinata = 250.3;
    zmijica[1].y_koordinata = 250;
    
    
    /*Inicijalizacija gluta*/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    /********************************************************/
    
    glutInitWindowSize(500,500);
    glutCreateWindow("Zmijica");
    
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    
    glClearColor(0.8,0.2,0.3,0);
    glEnable(GL_DEPTH_TEST);
    
    
    glutMainLoop();
    return 0;
}

static void on_reshape(int sirina, int visina){
    /* Podesava se viewport. */
    glViewport(0, 0, sirina, visina);

    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float) sirina / visina, 1, 15);
}
static void on_keyboard(unsigned char key, int x, int y){
    switch(key){
        case 27:
            exit(0);
            break;
            
        case 's':
        case 'S':
             
                Smer = 4;
                if(!uToku){
                    uToku = 1;
                    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                }
            
            break;
            
        case 'd':
        case 'D':
          
                Smer = 3;
                  if(!uToku){
                    uToku = 1;
                    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                }
            break;
            
        case 'w':
        case 'W':
            
                Smer = 2;
                  if(!uToku){
                    uToku = 1;
                    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                }
            break;
            
        case 'a':
        case 'A':
            
                Smer = 1;
                  if(!uToku){
                    uToku = 1;
                    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                }
            break;
            
        case 'p':
        case 'P':
            uToku = 0;
            break;
    }
}

static void on_display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /*Podesava se projekcija*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,1,1,15);
     /* Podesava se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
    
    int i=0;
    for(; i<duzina_zmijice; i++){
        glPushMatrix();
            glColor3f(0,1,1);
            glTranslatef(zmijica[i].x_koordinata,zmijica[i].y_koordinata,koefZ);
            glutWireCube(0.3);
        glPopMatrix();
    }
    glutSwapBuffers();
}
static void on_timer(int id){
    if(TIMER_ID != id)
        return;
    
    if(Smer == 1){
        koefX -=brzina;
    }
    if(Smer == 2){
        koefY +=brzina;
    }
    if(Smer == 3){
        koefX +=brzina;
    }
    if(Smer == 4){
        koefY -=brzina;
    }
    pomeri_zmijicu();
    glutPostRedisplay();
    
    if (uToku) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
        
}

void pomeri_zmijicu(){
    if(koefX > GRANICA_KOEF){
        printf("Udario desno\n");
        exit(1);
    }
    if(koefX < -GRANICA_KOEF){
        printf("Udario levo\n");
        exit(1);
    }
    if(koefY > GRANICA_KOEF){
        printf("Udario gore\n");
        exit(1);
    }
    if(koefY < -GRANICA_KOEF){
        printf("Udario dole\n");
        exit(1);
    }
    
    int i=0;
    for(; i<duzina_zmijice-1; i++){
        zmijica[i+1] = zmijica[i];
    }
    zmijica[0].x_koordinata = koefX;
    zmijica[0].y_koordinata = koefY;
}
