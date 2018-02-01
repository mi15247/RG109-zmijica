#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <GL/glut.h>

/*Makroi za tajmer*/
#define TIMER_ID 0
static int TIMER_INTERVAL = 100;
static int rezultat = 0;

/*Empirijski utvrdjen makro*/
#define GRANICA_KOEF 3.9
#define MAX_ZMIJICA 729

/*Struktuja koja cuva podatke o svakoj kockici koja cini zmijicu i njena inicijalizacija*/
typedef struct polje_zmijice{
    float x_koordinata;
    float y_koordinata;
}Polje_zmijice;
Polje_zmijice zmijica[MAX_ZMIJICA];
static int duzina_zmijice = 1;

/*Parametar koji govori da li je igrica u toku*/
static int uToku = 0;

/*Koeficijent koji koristim za promenu vrednosti ostalim koeficijentima*/
float brzina = 0.3;

/*Globalne promenljive koje ce sluziti za postavljanje hrane*/
int POJEDENO = 1;
float x_koordinata_hrane;
float y_koordinata_hrane;
float koefXhrana = 0;
float koefYhrana = 0;

/*Globalne promenljive koje ce sluziti za translaciju zmijice*/
static float koefX = 0;
static float koefY = 0;
static float koefZ = 0;

/*Enum vrednosti za smer kretanja*/
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
/*Deklaracije mojih funkcija*/
void pomeri_zmijicu();
void game_over();
void postavi_hranu();
void pojedeno();

int main(int argc, char** argv){
    /*Inicijalizacija pocetnih koordinata zmijice i hrane*/
    zmijica[0].x_koordinata = 250;
    zmijica[0].y_koordinata = 250;
    
    x_koordinata_hrane = 250;
    y_koordinata_hrane = 250;
    postavi_hranu();
    
    /*Inicijalizacija gluta*/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
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
    /*Klasicna on_keyboard funkcija u kojo se na pritisak odredjenog tastera postavlja smer i poziva se on_timer*/
    switch(key){
        case 27:
            exit(0);
            break;
            
        case 's':
        case 'S':
             
                Smer = dole;
                if(!uToku){
                    uToku = 1;
                    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                }
            
            break;
            
        case 'd':
        case 'D':
          
                Smer = desno;
                  if(!uToku){
                    uToku = 1;
                    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                }
            break;
            
        case 'w':
        case 'W':
            
                Smer = gore;
                  if(!uToku){
                    uToku = 1;
                    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
                }
            break;
            
        case 'a':
        case 'A':
            
                Smer = levo;
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
static void on_timer(int id){
    /*Klasicna on_timer funkcija u kojoj samo proveravam smer i azuriram koeficijente kojima se odredjuje translacija zmijice*/
    if(TIMER_ID != id)
        return;
    
    if(Smer == levo){
        koefX -=brzina;
    }
    if(Smer == gore){
        koefY +=brzina;
    }
    if(Smer == desno){
        koefX +=brzina;
    }
    if(Smer == dole){
        koefY -=brzina;
    }
    
    pomeri_zmijicu();
    game_over();
    
    glutPostRedisplay();
    
    if (uToku) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
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
    
    /*Iscrtavanje zmijice i njena translacija gde treba*/
    int i=0;
    for(; i<duzina_zmijice; i++){
        glPushMatrix();
            glColor3f(0,1,1);
            glTranslatef(zmijica[i].x_koordinata,zmijica[i].y_koordinata,koefZ);
            glutWireCube(0.3);
        glPopMatrix();
    }
    /*Iscrtavanje hrane i njena translacija gde treba*/
    glPushMatrix();
        glColor3f(0,0,1);
        glTranslatef(x_koordinata_hrane,y_koordinata_hrane,koefZ);
        glutWireCube(0.3);
    glPopMatrix();
    
 //   printf("(%.2f, %.2f)-(%.2f, %.2f)\n", koefX, koefY, koefXhrana, koefYhrana);
    
    glutSwapBuffers();
}

void game_over(){
    /*funkcija koja proverava da li je zmijica napustila ekran ili je udarila u samu sebe*/
    if(koefX > GRANICA_KOEF){
        printf("Udario desno\nRezultat:%d\n", rezultat);
        exit(1);
    }
    if(koefX < -GRANICA_KOEF){
        printf("Udario levo\nRezultat:%d\n", rezultat);
        exit(1);
    }
    if(koefY > GRANICA_KOEF){
        printf("Udario gore\nRezultat:%d\n", rezultat);
        exit(1);
    }
    if(koefY < -GRANICA_KOEF){
        printf("Udario dole\nRezultat:%d\n", rezultat);
        exit(1);
    }
    /*Pocinjem proveru od cetvrtog clana zmijice jer ne mogu sa 3 kocke da udarim u sebe*/
    int i = 1;
    if(duzina_zmijice >= 2){
        for(; i<duzina_zmijice; i++){
            if(zmijica[i].x_koordinata == zmijica[0].x_koordinata && zmijica[i].y_koordinata == zmijica[0].y_koordinata){
                printf("Udario u sebe\nRezultat:%d \n", rezultat);
                exit(1);
            }
        }
    }
    
}
void pomeri_zmijicu(){
    /*funkcija koja, kada dodje do prosirenja zmijice, podatke prebacuje u polje iza, a novu glavu postavlja na trenutnu poziciju*/
    int i=duzina_zmijice;
    
    for(; i>0; i--){
        zmijica[i].x_koordinata = zmijica[i-1].x_koordinata;
        zmijica[i].y_koordinata = zmijica[i-1].y_koordinata;
    }
    zmijica[0].x_koordinata = koefX;
    zmijica[0].y_koordinata = koefY;
    pojedeno();
}
void postavi_hranu(){
    /*Ovde postavljam koordinate hrane i proveravam uslov da se hrana ne postavi na zmijicu*/
    int brojac = 0;
    while(POJEDENO){
        /*Postavljanje koordinata*/
        if(!brojac){
            srand(time(NULL));
            int x = (int)((float)rand()/RAND_MAX*26)-13;
            koefXhrana = x*brzina;
            int y = (int)((float)rand()/RAND_MAX*26)-13;
            koefYhrana = y*brzina;
        }
        /*Provera da li je hrana negde na zmijici, ako nije to je u redu, ako jeste vrtimo se opet u petlji*/
        int i = 0;
        for(; i<duzina_zmijice-1; i++){
            if(zmijica[i].x_koordinata == koefXhrana && zmijica[i].y_koordinata == koefYhrana){
                brojac++;
            }
        }
        if(brojac == 0){
            POJEDENO = 0;
        }
        else{
            brojac = 0;
        }
    }
    /*ako je sve kako treba postavljaju se koordinate hrane*/
    x_koordinata_hrane = koefXhrana;
    y_koordinata_hrane = koefYhrana;
}
void pojedeno(){
    /*funkcija koja treba da detektuje kada se pojela hrana i da da dozvolu za prosirenje zmijice i postavljanje nove hrane na ekran*/
    /*Poredjenje realnih brojeva mi bas i nije islo pa sam sa fabsom to resio*/
    if(fabs(x_koordinata_hrane - zmijica[0].x_koordinata) < 0.1 && fabs(y_koordinata_hrane - zmijica[0].y_koordinata) < 0.1){
        duzina_zmijice++;
        POJEDENO = 1;
        /*Ovde cemo malo da ubrzamo zmijicu nakon svake 3 pojedene kockice*/
        rezultat++;
        if(rezultat%3 == 0){
            TIMER_INTERVAL-= 10;
        }
        postavi_hranu();
    }
}