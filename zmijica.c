#include <stdlib.h>
#include <GL/glut.h>

#define DIMENZIJA_MATRICE 50
#define MAX_ZMIJICA 50*50

typedef struct polje_zmijice{
    int x_koordinata;
    int y_koordinata;
    struct polje_zmijice *sledece;
    struct polje_zmijice *prethodno;
}Polje_zmijice;

static int matrica[DIMENZIJA_MATRICE][DIMENZIJA_MATRICE];

enum {
    levo = 1,
    gore = 2,
    desno = 3,
    dole = 4
} Smer;

static void on_display(void);
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv){
    
    /*Inicijalizacija glave zmije*/
    Polje_zmijice glava;
    glava.x_koordinata = DIMENZIJA_MATRICE/2;
    glava.y_koordinata = DIMENZIJA_MATRICE/2;
    glava.sledece = NULL;
    glava.prethodno = NULL;
    /****************************************/
    
    /*Inicijalizacija zmijice*/
    Polje_zmijice Zmijica[MAX_ZMIJICA];
    Zmijica[0] = glava;
    /**********************************/
    
    /*Inicijalizacija matrice*/
    int i,j;
    for(i=1; i<=DIMENZIJA_MATRICE; i++){
        for(j=1; j<=DIMENZIJA_MATRICE; j++){
            matrica[i][j] = 0;
        }
    }
    matrica[glava.x_koordinata][glava.y_koordinata] = 1;
    /*****************************************************/
    
    /*Inicijalizacija gluta*/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    /********************************************************/
    
    glutMainLoop();
    return 0;
}

static void on_display(void){
}

static void on_reshape(int width, int height){
    
}
static void on_keyboard(unsigned char key, int x, int y){
}
