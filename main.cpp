#include <GL/glut.h>

#define RATIO 1.200
#define WW 100
#define WH (WW / RATIO)
#define HALFX ((int)(WW / 2))
#define HALFY ((int)(WH / 2))
#define deltat .0001

int WindowWidth;
int WindowHeight;

void Init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-HALFX, HALFX, -HALFY, HALFY);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0, 0, 0, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glShadeModel(GL_SMOOTH);
    glViewport(0, 0, WindowWidth, WindowHeight);
}

void Display() {
    glLineWidth(4.0);

    // Hosea Nicolas A. N. P. Putra ( Abjad pertama )
    float startShape[14][2] = {
        {-15, -20}, {-15, -20}, {-15, -20},
        {-5, -20}, {-5, -5}, {5, -5},
        {5, -20}, {15, -20}, {15, 20},
        {5, 20}, {5, 5}, {-5, 5},
        {-5, 20}, {-15, 20}
    }; // Huruf H

    // 14 Juni 2003 ( Digit terakhir tanggal lahir )
    float endShape[14][2] = {
        {-20, -10}, {5, -10}, {5, -20},
        {10, -20}, {10, -10}, {15, -10},
        {20, -5}, {10, -5}, {10, 5},
        {5, 5}, {5, -5}, {-10, -5},
        {5, 20}, {0, 20}
    };// Angka 4

    float intermediateShape[14][2];
    float vertexColor[14][3] = {
        {1, 0, 0}, {1, 1, 0}, {1, 0, 1}, {0, 1, 0}, {0, 1, 1}, {0, 0, 1},
        {1, 0.5, 0}, {1, 0, 0.5}, {0.5, 1, 0}, {0.5, 0, 1}, {1, 0, 0.5}, {0, 1, 0.5},
        {0, 0.5, 1}, {0.5, 0.5, 0}
    };
    static float Tween = 0.0 - deltat;
    if (Tween < 1) {
        Tween += deltat;
    }
    for (int Vtx = 0; Vtx < 14; Vtx++) {
        intermediateShape[Vtx][0] = (1.0 - Tween) * startShape[Vtx][0] + Tween * endShape[Vtx][0];
        intermediateShape[Vtx][1] = (1.0 - Tween) * startShape[Vtx][1] + Tween * endShape[Vtx][1];
    }
    glVertexPointer(2, GL_FLOAT, 0, intermediateShape);
    glColorPointer(3, GL_FLOAT, 0, vertexColor);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_LINE_LOOP, 0, 14);
    glutSwapBuffers();
    glutPostRedisplay();
}

void Reshape(int w, int h) {
    WindowWidth = w;
    WindowHeight = (int)(w / RATIO);
    glViewport(0, 0, w, WindowHeight);
    Init();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    WindowWidth = (int)(glutGet((GLenum)GLUT_SCREEN_WIDTH) * 0.4);
    WindowHeight = (int)(WindowWidth / RATIO);
    glutInitWindowSize(WindowWidth, WindowHeight);
    glutInitWindowPosition((int)(glutGet((GLenum)GLUT_SCREEN_WIDTH) * 0.1), (glutGet((GLenum)GLUT_SCREEN_HEIGHT) / 2) - (WindowHeight / 2));
    glutCreateWindow("Tugas 4 - 672021159");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    Init();
    glutMainLoop();
    return 0;
}
