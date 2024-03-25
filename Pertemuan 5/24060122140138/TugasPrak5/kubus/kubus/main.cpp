
#include <iostream>
#include <stdlib.h>
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "imageloader.h"
//#include "imageloader.cpp"

using namespace std;

const float BOX_SIZE = 7.0f; //Panjang tiap sisi kubus
float _angle = 0; //Rotasi terhadap box
//ID OpenGL untuk tekstur
GLuint _sisiSatuId;
GLuint _sisiDuaId;
GLuint _sisiTigaId;
GLuint _sisiEmpatId;
GLuint _sisiLimaId;
GLuint _sisiEnamId;

void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 27: //Tekan Escape untuk EXIT
            exit(0);
    }
}

//Membuat gambar menjadi tekstur kemudian berikan ID pada tekstur
GLuint loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    return textureId;
}

void initRendering() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    
    Image* img1 = loadBMP("c.bmp");
    _sisiSatuId = loadTexture(img1);
    delete img1;

    Image* img2 = loadBMP("cpp.bmp");
    _sisiDuaId = loadTexture(img2);
    delete img2;

    Image* img3 = loadBMP("py.bmp");
    _sisiTigaId = loadTexture(img3);
    delete img3;

    Image* img4 = loadBMP("sql.bmp");
    _sisiEmpatId = loadTexture(img4);
    delete img4;

    Image* img5 = loadBMP("html.bmp");
    _sisiLimaId = loadTexture(img5);
    delete img5;

    Image* img6 = loadBMP("css.bmp");
    _sisiEnamId = loadTexture(img6);
    delete img6;
}

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTranslatef(0.0f, 0.0f, -20.0f);
    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    
    GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat lightPos[] = {-2 * BOX_SIZE, BOX_SIZE, 4 * BOX_SIZE, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    glRotatef(-_angle, 1.0f, 1.0f, 0.0f);
    
    //Sisi atas
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _sisiEnamId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glNormal3f(0.0, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glEnd();

    //Sisi bawah
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _sisiLimaId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glNormal3f(0.0, -1.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glEnd();

    //Sisi kiri
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _sisiEmpatId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glNormal3f(-1.0, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glEnd();

    //Sisi kanan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _sisiTigaId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glNormal3f(1.0, 0.0f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glEnd();

    //Sisi depan
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _sisiSatuId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glEnd();

    //Sisi belakang
    glBindTexture(GL_TEXTURE_2D, _sisiDuaId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0f, -1.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}


void update(int value) {
    _angle += 1.0f;
    if (_angle > 360) {
        _angle -= 360;
    }
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Texture With Image");
    initRendering();
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 0;
}
