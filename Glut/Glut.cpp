#include "stdafx.h"
#include "Plg.h"
// Skeleton of the glut application used from David HENRY
// http://tfc.duke.free.fr/

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <string.h>

// Keyboard
struct keyboard_input_t
{
	unsigned char keymap[256];
	int special[256];
	int modifiers;
} keyboard;

// Mouse
struct mouse_input_t
{
	int buttons[3];
	int x, y;
} mouse;

// Camera vectors
vertex rot, eye;
Plg NewObj;
int wirePolygon = 1;
int lightOn = 1;

void clear()
{
}
// Application initialisation. Setup keyboard input,
// mouse input, timer, camera and OpenGL.
void init()
{
	// Init keyboard
	memset(keyboard.keymap, 0, 256);
	memset(keyboard.special, 0, 256);
	// Init mouse 
	mouse.buttons[GLUT_LEFT_BUTTON] = GLUT_UP;
	mouse.buttons[GLUT_MIDDLE_BUTTON] = GLUT_UP;
	mouse.buttons[GLUT_RIGHT_BUTTON] = GLUT_UP;
	mouse.x = 0;
	mouse.y = 0;
	// Init camera input
	rot.x = 0.0f;   eye.x = 0.0f;
	rot.y = 0.0f;   eye.y = 0.0f;
	rot.z = 0.0f;   eye.z = 7.0f;
	// OpenGL initialization
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat lightpos[] = {0, 0, 0, 1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightpos); // GL_DIFUSE
}

// GLUT's reshape callback function.
// Update the viewport and the projection matrix.
void reshape(int w, int h)
{
	if (h == 0)
		h = 1;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutPostRedisplay();
}
// GLUT's Key press callback function.
// Called when user press a key.
void keyPress(unsigned char key, int x, int y)
{
	// Update key state
	keyboard.keymap[key] = 1;
	// Escape 
	if (key == 27)
		glutLeaveMainLoop();
	// 'w' : toggle wireframe
	if (key == 'w')
		wirePolygon = !wirePolygon;
	// 'l': toggle light
	if (key == 'l')
		lightOn = !lightOn;

	if (lightOn)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);
	glutPostRedisplay();
}
// GLUT's display callback function.
// Render the main OpenGL scene.
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	// Camera rotation
	glTranslated(-eye.x, -eye.y, -eye.z);
	glRotated(rot.x, 1.0f, 0.0f, 0.0f);
	glRotated(rot.y, 0.0f, 1.0f, 0.0f);
	glRotated(rot.z, 0.0f, 0.0f, 1.0f);
	// Draw ground
//	glColor3f(0.9f, 0.9f, 0.9f);
//	glBegin(GL_QUADS);
//	glVertex3f(-10.0f, 0.0f, -10.0f);
//	glVertex3f(-10.0f, 0.0f, 10.0f);
//	glVertex3f(10.0f, 0.0f, 10.0f);
//	glVertex3f(10.0f, 0.0f, -10.0f);
//	glEnd();
// draw our axes
	glBegin(GL_LINES);
	// draw line for x axis
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);
	// draw line for y axis
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);
	// draw line for Z axis
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();
	// Polygon type
	if (wirePolygon)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(0.9, 0.9, 0.9);
	// Load PLG
	for (unsigned int i = 0; i < NewObj.PolygonList.size(); i++) 
	{
		glBegin(GL_POLYGON);
		for (unsigned int j = 0; j < NewObj.PolygonList[i].size(); j++)
			glVertex3f(NewObj.PolygonList[i][j].x / 100.0,
				NewObj.PolygonList[i][j].y / 100.0,
				NewObj.PolygonList[i][j].z / 100.0);
		glEnd();
	}
	glutSwapBuffers();
}
// GLUT's Key up callback function.
// Called when user release a key.
void keyUp(unsigned char key, int x, int y)
{
	keyboard.keymap[key] = 0;
}
// GLUT's Key press callback function.
// Called when user press a special key.
void specialKeyPress(int key, int x, int y)
{
	keyboard.special[key] = 1;
}
// GLUT's key up callback function.
// Called when user release a special key.
void specialKeyUp(int key, int x, int y)
{
	keyboard.special[key] = 0;
}
// GLUT's mouse motion callback function.
// Called when the user move the mouse. Update the camera.
void mouseMotion(int x, int y)
{
	if (mouse.buttons[GLUT_RIGHT_BUTTON] == GLUT_DOWN)
	{
		// Zoom
		eye.z += (x - mouse.x) * 0.1;
	}
	else if (mouse.buttons[GLUT_LEFT_BUTTON] == GLUT_DOWN)
	{
		if (keyboard.modifiers & GLUT_ACTIVE_SHIFT)
		{
			// Translation
			eye.x -= (x - mouse.x) * 0.02;
			eye.y += (y - mouse.y) * 0.02;
		}
		else
		{
			// Rotation
			rot.x += (y - mouse.y);
			rot.y += (x - mouse.x);
		}
	}
	mouse.x = x;
	mouse.y = y;
	glutPostRedisplay();
}
// GLUT's mouse button callback function.
// Called when the user press a mouse button. Update mouse
// state and keyboard modifiers.
void mouseButton(int button, int state, int x, int y)
{
	// Update key modifiers
	keyboard.modifiers = glutGetModifiers();
	// Update mouse state 
	mouse.buttons[button] = state;
	mouse.x = x;
	mouse.y = y;
}
// GLUT's idle callback function.
// Continuously called. Perform background processing tasks.
void idleVisible()
{
}

// GLUT's window status callback function.
// Called when the status of the window changes.
void windowStatus(int state)
{
	// Disable rendering and/or animation when the
	// window is not visible 
	if ((state != GLUT_HIDDEN) &&
		(state != GLUT_FULLY_COVERED))
	{
		glutIdleFunc(idleVisible);
	}
	else
	{
		glutIdleFunc(NULL);
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		std::cout << "Error: file not found" << argv[1];
		exit(EXIT_FAILURE);
	}
	if (NewObj.Load(argv[1]))
	{
		// Initialize GLUT
		glutInit(&argc, argv);
		// Create an OpenGL window
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
		glutInitWindowSize(640, 480);
		glutCreateWindow(argv[1]);
		init();
		atexit(clear);
		// Setup GLUT's callback functions
		glutReshapeFunc(reshape);
		glutDisplayFunc(display);
		glutKeyboardFunc(keyPress);
		glutKeyboardUpFunc(keyUp);
		glutSpecialFunc(specialKeyPress);
		glutSpecialUpFunc(specialKeyUp);
		glutMotionFunc(mouseMotion);
		glutMouseFunc(mouseButton);
		glutWindowStatusFunc(windowStatus);
		glutIdleFunc(idleVisible);
		// Enter the main loop
		glutMainLoop();
		return 0;
	}
	return EXIT_FAILURE;
}