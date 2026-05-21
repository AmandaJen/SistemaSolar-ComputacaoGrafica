#include <GL/glut.h>

//Mercurio, Venus, Terra, Marte, Jupiter, Saturno, Netuno, Lua
float anguloOrbita [9] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float anguloRotacao [9] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

GLfloat iluBranca[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat iluAmbi[] = { 0.2f, 0.2f, 0.2f, 1.0f };

// Função de inicialização
void init() {
    glEnable(GL_DEPTH_TEST);

    // Iluminação
    glEnable(GL_LIGHTING);

    // Material padrão
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glClearColor(0.0, 0.0, 0.0, 1.0); // fundo preto (espaço)
}

void hajaLuz() {
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, iluAmbi);
  
    // LÂMPADA 0: O Sol irradiando luz (Luz Pontual) ---
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, iluBranca);
    // Posição no centro
    GLfloat posPontual[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, posPontual);
 
 
    // LÂMPADA 1: Iluminação do Sol (Luz Pontual) ---
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, iluBranca);
    // Posição pouco a frente do Sol, iluminando o próprio Sol
    GLfloat posPontual1[] = { 0.0f, 1.0f, 2.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, posPontual1);
 }
 

void desenhaPlaneta(float anguloOrbita, float anguloRotacao, float xDoSol, float r, float g, float b, float raio){
    glPushMatrix();

    glRotatef(anguloOrbita, 0.0, 1.0, 0.0); //angulo da orbita em relacao ao sol
    glTranslatef(xDoSol, 0.0, 0.0); // x muda a distancia em relacao ao sol

    // Rotação do planeta
    glRotatef(anguloRotacao, 0.2, 0.7, 0.0); //rotação no proprio eixo 

  
    glColor3f(r, g, b); //cor laranja
    glutSolidSphere(raio, 50, 50); // raio, e detalhamento  

    glPopMatrix(); 
}

void desenhaSatelite(float anguloOrbitaP, float anguloOrbitaS, float anguloRotacaoS, float distanciaP, float r, float g, float b, float raio){

glPushMatrix();

// Rotaciona em torno do Sol para seguir o planeta
glRotatef(anguloOrbitaP, 0.0, 1.0, 0.0);
glTranslatef(distanciaP, 0.0, 0.0); // posição da Terra

// Agora a Lua orbita a Terra
glRotatef(anguloOrbitaS, 0.0, 1.0, 0.0);
glTranslatef(0.5f, 0.0, 0.0); // distância Lua-Terra (ajuste a escala)

// Rotação da Lua em torno de si mesma
glRotatef(anguloRotacaoS, 0.0, 1.0, 0.0);

glColor3f(r, g, b);
glutSolidSphere(raio, 50, 50);

glPopMatrix();
}

// Desenhar cena
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer de cor e o buffer de profundidade, usado para determinar qual objeto está na frente do outro

    glLoadIdentity(); //reseta a matriz de rotação e translação

    // Câmera
    gluLookAt(0, 10, 30,  // posição da câmera, onde a camera está
              0, 0, 0,   // para onde a câmera olha
              0, 1, 0);  // eixo Y // define que o  y é para cima
    hajaLuz();

    //  Sol (com emissão de luz)
    GLfloat emissaoSol[] = {1.0, 0.8, 0.0, 1.0}; // brilho amarelo r,g,b e alfa
    glMaterialfv(GL_FRONT, GL_EMISSION, emissaoSol); 

    glColor3f(1.0, 0.8, 0.0); //cor da esfera 
    glutSolidSphere(1.0, 50, 50); //esfera

    // Tirar emissão depois do sol
    GLfloat semEmissao[] = {0.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_EMISSION, semEmissao);

    //Mercurio
    desenhaPlaneta(anguloOrbita[0], anguloRotacao[0], 3.0f, 1.0, 0.3, 0.1, 0.3f);
    
    //Venus
    desenhaPlaneta(anguloOrbita[1], anguloRotacao[1], 5.0, 0.7, 0.7, 0.4, 0.7);

    //Terra
    desenhaPlaneta(anguloOrbita[2], anguloRotacao[2], 7.5, 0.0, 0.5, 1.0, 0.4);

    //Lua Terra
    desenhaSatelite(anguloOrbita[2],anguloOrbita[8],anguloRotacao[8], 7.5, 1.0, 1.0, 1.0, 0.1);

    //Marte
    desenhaPlaneta(anguloOrbita[3], anguloRotacao[3], 11.0, 1.0f, 0.4f, 0.2f, 0.3);

    //Jupiter
    desenhaPlaneta(anguloOrbita[4], anguloRotacao[4], 15.0, 0.7, 0.4, 0.15, 0.8);

    //Saturno
    desenhaPlaneta(anguloOrbita[5], anguloRotacao[5], 20.0, 1.0, 1.0, 0.7, 0.64);

    //Urano
    desenhaPlaneta(anguloOrbita[6], anguloRotacao[6], 25.0, 0.4, 0.8, 1.1, 0.3);

    //Netuno
    desenhaPlaneta(anguloOrbita[7], anguloRotacao[7], 30.0, 0.1, 0.1, 1.0, 0.3);


    glutSwapBuffers(); //troca de buffer 
}

//Atualização (animação)
void update(int value) {
    anguloOrbita[0] += 2.0f;
    anguloRotacao[0] += 0.0f;

    anguloOrbita[1] += 1.46f;
    anguloRotacao[1] += 0.0f;

    anguloOrbita[2] += 1.24f;     // velocidade da órbita
    anguloRotacao[2] += 2.0f;    // velocidade da rotação

    anguloOrbita[3] += 1.0f;
    anguloRotacao[3] += 0.0f;

    anguloOrbita[4] += 0.5f;
    anguloRotacao[4] += 0.0f;

    anguloOrbita[5] += 0.4f;     
    anguloRotacao[5] += 1.5f;

    anguloOrbita[6] += 0.3f;
    anguloRotacao[6] += 0.0f;

    anguloOrbita[7] += 0.2f;
    anguloRotacao[7] += 0.0f;

    anguloOrbita[8] += 2.0f;
    anguloRotacao[8] += 0.0f;

    for (int x=0; x<9; x++){
        if (anguloOrbita[x] > 360) anguloOrbita[x] -= 360;
        if (anguloRotacao[x] > 360) anguloRotacao[x] -= 360;
    }

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
    glutInitWindowSize(1200, 500);
    glutCreateWindow("Trabalho de Computação gráfica: Sistema Solar ");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
