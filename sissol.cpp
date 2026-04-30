#include <GL/glut.h>
#include <math.h>

float anguloTerra = 0.0f;

void circulo(float x, float y, float radius, float r, float g, float b){

    //x e y como centro do circulo
    //radius como raio

    int num_segments = 100; // mais segmentos = círculo mais suave

    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * i / num_segments; // ângulo atual
        float px = radius * cos(theta); // x do ponto
        float py = radius * sin(theta); // y do ponto
        glVertex2f(px + x, py + y);
    }
    glEnd();

    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    /*gluLookAt(
        2.0, 2.0, 0.0,   // posição da câmera
        0.0, 0.0, 0.0,   // olhar para o centro
        0.0, 1.0, 0.0    // "up" no eixo Y
    );*/

    //sol
    glPushMatrix();

    circulo (0, 0, 0.15f, 1.0f, 0.3f, 0.0f);
    glPopMatrix();

    //mercurio
    glPushMatrix();

    //glTranslatef(-0.7f, -0.3f, 0.0f); 
    glRotatef(anguloTerra, 0.0f, 0.0f, 1.0f);

    circulo (0.4f, 0, 0.08f, 1.0f, 0.0f, 0.0f);

    //terra
    glPushMatrix();

    //glTranslatef(-0.7f, -0.3f, 0.0f); 
                    //x,y,z servem para velocidade
    glRotatef(anguloTerra, 0.0f, 0.0f, 1.0f);

    circulo (0.5f, 0, 0.04f, 0.0f, 0.3f, 1.0f);

    glPopMatrix();
}

void animacaoTerra(int valor) {

    anguloTerra += 3.0f;

    if (anguloTerra > 360.0f) {

        anguloTerra -= 360.0f;

    }



    glutPostRedisplay();

    glutTimerFunc(16, animacaoTerra, 0);

}

/*void init() {
    glMatrixMode(GL_PROJECTION); // estamos ajustando a projeção
    glLoadIdentity();            // reset da matriz
    gluPerspective(45.0, 1.0, 0.1, 100.0); // fovy, aspect, zNear, zFar
    glMatrixMode(GL_MODELVIEW);  // volta para modelagem
}*/

//void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(500, 500);
    glutCreateWindow("Circulo OpenGL");

    glutDisplayFunc(display);
    glutTimerFunc(25, animacaoTerra, 0);

    glutMainLoop();
    return 0;
}