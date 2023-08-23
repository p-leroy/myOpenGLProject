#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>

#include <windows.h>
#include <gl/GL.h>
#include <gl/glu.h>

#define LARGEUR_BASE 50
#define HAUTEUR_BASE 20

#define LARGEUR_BRAS_1 150
#define HAUTEUR_BRAS_1 15

#define LARGEUR_BRAS_2 50
#define HAUTEUR_BRAS_2 10

#define TAILLE_CAISSE 10

#define LARGEUR_ECRAN (LARGEUR_BASE + LARGEUR_BRAS_1 + HAUTEUR_BRAS_2 + 50)
#define HAUTEUR_ECRAN (HAUTEUR_BASE + LARGEUR_BRAS_1 + HAUTEUR_BRAS_2 + 50)

int angle1 = 45;
int angle2 = - 20;
int longueur = 50;

void drawRectangle(double largeur,double hauteur)
{
	glBegin(GL_QUADS);
	glVertex2d(0, - hauteur / 2);
	glVertex2d(0, hauteur / 2);
	glVertex2d(largeur, hauteur / 2);
	glVertex2d(largeur, - hauteur / 2);
	glEnd();
}

void drawCoordinateSystem(unsigned int echelle = 1)
{
	glPushMatrix();
	glScalef(echelle, echelle, echelle);
	glBegin(GL_LINES);
	glColor3ub(0, 0, 255);
	glVertex2i(0, 0);
	glVertex2i(1, 0);
	glColor3ub(0, 255, 0);
	glVertex2i(0, 0);
	glVertex2i(0, 1);
	glEnd();
	glPopMatrix();
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity( );

    /* Je déplace mon répère initial (actuellement
    en bas à gauche de l'écran) */
    glTranslated(LARGEUR_BASE / 2,HAUTEUR_BASE, 0);

	// La base
	glColor3ub(254, 128, 1);
	drawRectangle(LARGEUR_BASE, HAUTEUR_BASE);

	//Je me place en haut au milieu de la base
	glTranslated(LARGEUR_BASE / 2,HAUTEUR_BASE / 2, 0);

	// Le grand bras
	glRotated(angle1, 0, 0, 1);
	glColor3ub(248, 230, 7);
	drawRectangle(LARGEUR_BRAS_1, HAUTEUR_BRAS_1);

	// Je me place au bout du grand bras
	glTranslated(LARGEUR_BRAS_1, 0, 0);

	// Puis m'occupe du petit bras
	glRotated(angle2, 0, 0, 1);
	glColor3ub(186, 234, 21);
	drawRectangle(LARGEUR_BRAS_2, HAUTEUR_BRAS_2);

	// Je me place au bout du petit bras
	glTranslated(LARGEUR_BRAS_2, 0, 0);
	/* J'annule les rotations pour avoir mon repère aligné
	avec le repère d'origine */
	glRotated(- angle1 - angle2, 0, 0, 1);

    // Je dessine le fil
    glColor3ub(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2i(0, 0);
    glVertex2i(0, - longueur);
    glEnd();

    /* Je descends en bas du fil (avec un petit décalage
    sur X pour anticiper le dessin de la caisse */
    glTranslated(- TAILLE_CAISSE / 2, - longueur, 0);

	// Et je dessine enfin la caisse
	glColor3ub(175, 175, 85);
	drawRectangle(TAILLE_CAISSE, TAILLE_CAISSE);

	glFlush();
}

void drawCube()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity( );

	gluLookAt(3, 4, 2, 0, 0, 0, 0, 0, 1);

	glBegin(GL_QUADS);

	glColor3ub(255, 0, 0); //face rouge
	glVertex3d(1, 1, 1);
	glVertex3d(1, 1, -1);
	glVertex3d(-1, 1, -1);
	glVertex3d(-1, 1, 1);

	glColor3ub(0, 255, 0); //face verte
	glVertex3d(1, -1, 1);
	glVertex3d(1, -1, -1);
	glVertex3d(1, 1, -1);
	glVertex3d(1, 1, 1);

	glColor3ub(0, 0, 255); //face bleue
	glVertex3d(-1, -1, 1);
	glVertex3d(-1, -1, -1);
	glVertex3d(1, -1, -1);
	glVertex3d(1, -1, 1);

	glEnd();

	glFlush();
}

int main(int argc, char *argv[])
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[debug] %s", SDL_GetError());
		return -1;
	}

	auto window = SDL_CreateWindow("Window name",
								   SDL_WINDOWPOS_UNDEFINED,
								   SDL_WINDOWPOS_UNDEFINED,
								   LARGEUR_ECRAN, HAUTEUR_ECRAN, SDL_WINDOW_OPENGL);
	auto context = SDL_GL_CreateContext(window);

	SDL_SetWindowTitle(window, "Exercice : une grue");

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	gluOrtho2D(0, LARGEUR_ECRAN, 0, HAUTEUR_ECRAN);

	draw();

	SDL_Event event;
	while (SDL_WaitEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			exit(0);
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				longueur --;
				if (longueur < 10)
					longueur = 10;
				break;
			case SDLK_DOWN:
				longueur ++;
				if (longueur > 100)
					longueur = 100;
				break;
			case SDLK_LEFT:
				if ((event.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT)
				{
					angle1++;
					if (angle1 > 90)
						angle1 = 90;
				}
				else
				{
					angle2++;
					if (angle2 > 90)
						angle2 = 90;
				}
				break;
			case SDLK_RIGHT:
				if ((event.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT)
				{
					angle1--;
					if (angle1 < 10)
						angle1 = 10;
				}
				else
				{
					angle2--;
					if (angle2 < -90)
						angle2 = -90;
				}
				break;
			}
			break;
		}

		draw();
		SDL_GL_SwapWindow(window);
	}

	SDL_DestroyWindow(window);

	SDL_Quit();


	return 0;
}
