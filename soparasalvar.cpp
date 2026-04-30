#include <GL/glut.h>

float anguloOrbita = 0.0f;
float anguloRotacao = 0.0f;

// Função de inicialização
void init() {
    glEnable(GL_DEPTH_TEST);

    // Iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat posicaoLuz[] = {0.0f, 0.0f, 0.0f, 1.0f}; // luz no sol
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    // Material padrão
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glClearColor(0.0, 0.0, 0.0, 1.0); // fundo preto (espaço)
}

// Desenhar cena
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer de cor e o buffer de profundidade, usado para determinar qual objeto está na frente do outro

    glLoadIdentity(); //reseta a matriz de rotação e translação

    // Câmera
    gluLookAt(0, 5, 15,  // posição da câmera, onde a camera está
              0, 0, 0,   // para onde a câmera olha
              0, 1, 0);  // eixo Y // define que o  y é para cima

    //  SOL (com emissão de luz)
    GLfloat emissaoSol[] = {1.0, 0.8, 0.0, 1.0}; // brilho amarelo r,g,b e alfa
    glMaterialfv(GL_FRONT, GL_EMISSION, emissaoSol); //

    glColor3f(1.0, 0.8, 0.0); //cor da esfera 
    glutSolidSphere(2.0, 50, 50); //esfera

    // Tirar emissão depois do sol
    GLfloat semEmissao[] = {0.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_EMISSION, semEmissao);

   
    glPushMatrix();

    // Translação (orbitar)
    glRotatef(anguloOrbita, 0.0, 1.0, 0.0); //rotação em y 
    glTranslatef(6.0, 0.0, 0.0); // translação em x 

    // Rotação do planeta
    glRotatef(anguloRotacao, 0.2, 0.7, 0.0); //rotação em y 

  
    glColor3f(0.0, 0.0, 1.0); //cor rosa 
    glutSolidSphere(1.0, 50, 50); //monta a esfera 

glPopMatrix(); 


    glutSwapBuffers(); //troca de buffer 
}

//Atualização (animação)
void update(int value) {
    anguloOrbita += 1.5f;     // velocidade da órbita
    anguloRotacao += 2.0f;    // velocidade da rotação

    if (anguloOrbita > 360) anguloOrbita -= 360;
    if (anguloRotacao > 360) anguloRotacao -= 360;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

// Ajuste de tela
void reshape(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(55.0, (float)w/h, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

// Main
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutCreateWindow("Trabalho de Computação gráfica: Sistema Solar ");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
