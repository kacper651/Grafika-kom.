/*************************************************************************************/


// Troch� bardziej skomplikowany program wykorzystuj�cy funkcje biblioteki OpenGL



/*************************************************************************************/

#include <windows.h>
#include <time.h>
#include <gl/gl.h>

#include <gl/glut.h>

/*************************************************************************************/


// Funkcaja okre�laj�ca, co ma by� rysowane
// (zawsze wywo�ywana, gdy trzeba przerysowa� scen�)

GLint depth = 3;
GLfloat a = 100;
GLfloat st_deformacji = 3;

void drawCarpet(GLfloat x, GLfloat y, GLfloat a, GLint depth)
{

    if (depth > 0)
    {
        a = a / 3;
        depth -= 1;
        drawCarpet(x, y, a, depth);
        drawCarpet(x - a, y, a, depth);
        drawCarpet(x - 2 * a, y, a, depth);
        drawCarpet(x, y - a, a, depth);
        drawCarpet(x - 2 * a, y - a, a, depth);
        drawCarpet(x, y - 2 * a, a, depth);
        drawCarpet(x - a, y - 2 * a, a, depth);
        drawCarpet(x - 2 * a, y - 2 * a, a, depth);
    }

    else
    {
        GLfloat def = (rand() % 20) * st_deformacji / (10 * a);
        glBegin(GL_POLYGON);
            glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
            glVertex2f(x + def, y + def);
            glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
            glVertex2f(x + def, y - a + def);
            glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
            glVertex2f(x - a + def, y - a + def);
            glColor3f(((rand() % 101) * 0.01), ((rand() % 101) * 0.01), ((rand() % 101) * 0.01));
            glVertex2f(x - a + def, y + def);
        glEnd();
    }
    glFlush();
    // Przekazanie polece� rysuj�cych do wykonania
}

void RenderScene(void)

{

    glClear(GL_COLOR_BUFFER_BIT);
    // Czyszczenie okna aktualnym kolorem czyszcz�cym

    //glColor3f(0.0f, 1.0f, 0.0f);
    // Ustawienie aktualnego koloru rysowania na zielony

    drawCarpet(50, 50, a, depth);
}

/*************************************************************************************/


// Funkcja ustalaj�ca stan renderowania




void MyInit(void)

{

    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    // Kolor okna wn�trza okna - ustawiono na szary

}

/*************************************************************************************/


// Funkcja s�u��ca do kontroli zachowania proporcji rysowanych obiekt�w
// niezale�nie od rozmiar�w okna graficznego



void ChangeSize(GLsizei horizontal, GLsizei vertical)

// Parametry horizontal i vertical (szeroko�� i wysoko�� okna) s�
// przekazywane do funkcji za ka�dym razem, gdy zmieni si� rozmiar okna

{

    GLfloat AspectRatio;

    // Deklaracja zmiennej AspectRatio okre�laj�cej proporcj� wymiar�w okna



    if (vertical == 0)
        // Zabezpieczenie pzred dzieleniem przez 0

        vertical = 1;

    glViewport(0, 0, horizontal, vertical);
    // Ustawienie wielko�ciokna okna urz�dzenia (Viewport)
    // W tym przypadku od (0,0) do (horizontal, vertical)

    glMatrixMode(GL_PROJECTION);
    // Okre�lenie uk�adu wsp�rz�dnych obserwatora

    glLoadIdentity();
    // Okre�lenie przestrzeni ograniczaj�cej

    AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
    // Wyznaczenie wsp�czynnika proporcji okna

    // Gdy okno na ekranie nie jest kwadratem wymagane jest
    // okre�lenie okna obserwatora.
    // Pozwala to zachowa� w�a�ciwe proporcje rysowanego obiektu
    // Do okre�lenia okna obserwatora s�u�y funkcja glOrtho(...)


    if (horizontal <= vertical)

        glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);

    else

        glOrtho(-100.0 * AspectRatio, 100.0 * AspectRatio, -100.0, 100.0, 1.0, -1.0);



    glMatrixMode(GL_MODELVIEW);
    // Okre�lenie uk�adu wsp�rz�dnych    

    glLoadIdentity();

}

/*************************************************************************************/


// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli




int main(void)

{

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    // Ustawienie trybu wy�wietlania
    // GLUT_SINGLE - pojedynczy bufor wy�wietlania
    // GLUT_RGBA - model kolor�w RGB


    glutCreateWindow("Drugi program w OpenGL");
    // Utworzenie okna i okre�lenie tre�ci napisu w nag��wku okna

    glutDisplayFunc(RenderScene);
    // Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn� (callback)
    // Biblioteka GLUT b�dzie wywo�ywa�a t� funkcj� za ka�dym razem, gdy
    // trzeba b�dzie przerysowa� okno


    glutReshapeFunc(ChangeSize);
    // Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn� za
    // zmiany rozmiaru okna

    MyInit();
    // Funkcja MyInit (zdefiniowana powy�ej) wykonuje wszelkie 
    // inicjalizacje konieczneprzed przyst�pieniem do renderowania


    glutMainLoop();
    // Funkcja uruchamia szkielet biblioteki GLUT

}

/*************************************************************************************/