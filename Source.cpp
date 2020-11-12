/* 
This program is write for CPT205 assignment 1
You are required to create a 2-dimensional Birthday Card, which could contain 
balloons, flowers, trees, candles, cakes, smiling faces, greeting messages 
and other objects that may appear in a physical Birthday Card.
It should consist of a background and both still and animated objects where appropriate.
Keyboard and mouse functions should be used to trigger the actions or display your Birthday Card in stages.
*/

#define FREEGLUT_STATIC // Define a static library for calling functions
#include <GL/freeglut.h> // Include the header file
#include <math.h>

#define MAX_CHAR 128

GLfloat wordx = 300;
GLfloat wordy = 0;

int wordFlag = 0;
float step = 0.0;
float cloudspeed = 0.0;
int forward = 0;

int time_interval = 16; // declare refresh interval in ms
void when_in_mainloop() { // idle callback function
	glutPostRedisplay(); // force OpenGL to redraw the current window
}
void OnTimer(int value) {
	wordy += step;
	if (wordy >= 530)
	{
		step = 0;
		wordy = 530;
	}

	if (cloudspeed >= 1.1)
	{
		forward = 0;
	}
	if (cloudspeed <= -0.3)
	{
		forward = 1;
	}

	// when_in_mainloop();
	glutTimerFunc(time_interval, OnTimer, 1);
}
void mouse_input(int button, int state, int x, int y) { // mouse interaction
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON && wordy <= 530)
		wordFlag = 1;
		step = 2.0;
}

void keyboard_input(unsigned char key, int x, int y) {// keyboard interaction
	if (key == 'q' || key == 'Q')
		exit(0);
}

void drawSkyline(void)
{
	glLoadIdentity();
	glTranslatef(0.0, -4.3, 0.0);

	// draw skyline
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(2.0f);
	glBegin(GL_POINTS);
	for (float x = 70.0f, y = 0.0f; x <= 929.0f; x += 0.1f)
	{
		float x1 = x - 500.0f;
		y = 70.0f + sqrt(pow(1800.0f, 2) - pow(x1, 2));
		glVertex2f(x, y);
	}
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	for (float x = 71.0f, y = 0.0f; x <= 928.0f; x += 0.1f)
	{
		float x1 = x - 500.0f;
		y = 70.0f + sqrt(pow(1800.0f, 2) - pow(x1, 2));
		glVertex2f(x, y - 1);
		glVertex2f(x, 1576);
	}
	glEnd();
}

void selectFont(int size, int charset, const char* face, int color) {
	if (color == 1)
	{
		glColor3f(0, 0, 0);		
	}
	else if (color == 2)
	{
		glColor3f(1, 0, 0);
	}
	HFONT
		hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS
			, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;
	if (isFirstCall) {
		isFirstCall = 0;
		lists = glGenLists(MAX_CHAR);
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	for (; *str != '\0'; ++str) {
		glCallList(lists + *str);
	}
}

void drawWord(void)
{
	if (wordFlag == 0)
	{
		selectFont(50, ANSI_CHARSET, "Tahoma", 1);
		glRasterPos2f(360, 30);
		drawString("Click to \"receive\"");	
	}
	else if(wordFlag == 1)
	{
		glLoadIdentity();
		selectFont(50, ANSI_CHARSET, "Tahoma", 2);
		glRasterPos2f(wordx, wordy+step);
		drawString("Happy");
		glRasterPos2f(wordx + 280, wordy+step);
		drawString("Birthday");

		if (wordy >= 200)
		{
			selectFont(50, ANSI_CHARSET, "Tahoma", 1);
			glRasterPos2f(310, 30);
			drawString("Press \"Q\" or \"q\" to \"exit\"");
		}
		
	}
	glLoadIdentity();
	glFlush();
}

void drawCake(void)
{
	if (wordFlag == 1)
	{
		glLoadIdentity();
		glTranslatef(1.0, 1.0, 0.0);

		// draw candle
		glLineWidth(2.0f);
		glColor3f(0.5f, 0.5f, 1.0f);
		glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(0, 50);
		glVertex2f(1, 0);
		glVertex2f(1, 50);
		glVertex2f(-1, 0);
		glVertex2f(-1, 50);
		glEnd();

		glColor3f(1.0, 1.0, 0.0);
		glPointSize(3.0f);
		glBegin(GL_POINTS);

		float x = 400.0, y = 0.0f, a = 100.0f, b = 30.0f;
		for (int i = 0; i <= 5 * a; i += 1)
		{

			glVertex2f(a * cos(2 * 3.14 / i * 2 * a), b * sin(2 * 3.14 / i * 2 * a));
			glVertex2f(a * cos(2 * 3.14 / i * 2 * a), b * sin(2 * 3.14 / i * 2 * a));
		}

		for (int i = 0; i <= 5 * a; i += 1)
		{
			float yt = b * sin(2 * 3.14 / i * 2 * a);
			if (yt <= 0)
			{
				glVertex2f(a * cos(2 * 3.14 / i * 2 * a), yt - 50);
			}
		}
		glEnd();


		glLineWidth(2.0f);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		for (int i = 0; i <= 5 * a; i += 1)
		{
			glVertex2f(a * cos(2 * 3.14 / i * 2 * a), b * sin(2 * 3.14 / i * 2 * a));
			glVertex2f(a * cos(2 * 3.14 / 2 * a), b * sin(2 * 3.14 / 2 * a));
		}

		for (int i = 0; i <= 5 * a; i += 1)
		{
			glVertex2f(a * cos(2 * 3.14 / i * 2 * a), b * sin(2 * 3.14 / i * 2 * a));
			glVertex2f(a * cos(2 * 3.14 / i * 2 * a), b * sin(2 * 3.14 / i * 2 * a) - 48);
		}
		glEnd();


		glLineWidth(2.0f);
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_LINES);
		glVertex2f(a * cos(2 * 3.14 / 2 * a) + 2, b * sin(2 * 3.14 / 2 * a) + 3);
		glVertex2f(a * cos(2 * 3.14 / 2 * a) + 2, b * sin(2 * 3.14 / 2 * a) - 49);

		glVertex2f(a * cos(2 * 3.14 / 8 * a), b * sin(2 * 3.14 / 5 * a) + 3);
		glVertex2f(a * cos(2 * 3.14 / 8 * a), b * sin(2 * 3.14 / 5 * a) - 49);
		glEnd();
	}
	glFlush();
}

void drawSkyObjects(void)
{
	glLoadIdentity();

	glColor3f(1.0, 0.3, 0.1);
	glPointSize(3.0f);
	glBegin(GL_LINES);
	for (float x = 780, y = 0; x <= 840; x += 1)
	{
		float x1 = x - 810;
		y = 500 + sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 500);

		float y2 = 500 - sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, 500);
		glVertex2f(x, y2);
	}
	glEnd();

	glTranslatef(cloudspeed, 0.0, 0.0);

	if (forward == 1)
	{
		cloudspeed += 0.001;
	}
	if (forward == 0)
	{
		cloudspeed -= 0.001;
	}

	glColor3f(1.0, 1.0, 1.0);
	glPointSize(3.0f);
	glBegin(GL_LINES);
	for (float x = 300, y = 0; x <= 350; x += 1)
	{
		float x1 = x - 325;
		y = 460 + sqrt(pow(25, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 460);

		float y2 = 460 - sqrt(pow(25, 2) - pow(x1, 2));
		glVertex2f(x, 460);
		glVertex2f(x, y2);
	}

	for (float x = 340, y = 0; x <= 370; x += 1)
	{
		float x1 = x - 355;
		y = 450 + sqrt(pow(15, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 450);

		float y2 = 450 - sqrt(pow(15, 2) - pow(x1, 2));
		glVertex2f(x, 450);
		glVertex2f(x, y2);
	}

	for (float x = 270, y = 0; x <= 310; x += 1)
	{
		float x1 = x - 290;
		y = 455 + sqrt(pow(20, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 455);

		float y2 = 455 - sqrt(pow(20, 2) - pow(x1, 2));
		glVertex2f(x, 455);
		glVertex2f(x, y2);
	}

	for (float x = 250, y = 0; x <= 280; x += 1)
	{
		float x1 = x - 265;
		y = 450 + sqrt(pow(15, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 450);

		float y2 = 450 - sqrt(pow(15, 2) - pow(x1, 2));
		glVertex2f(x, 450);
		glVertex2f(x, y2);
	}
	glEnd();

	glFlush();
}

int firstin = 1;
int flowerx[300] = {};
int flowery[300] = {};

void drawGroundObjects(void)
{
	glLoadIdentity();
	
	// balloons
	glColor3f(1.0, 1.0, 0.0);
	glPointSize(3.0f);
	glBegin(GL_LINES);
	for (float x = 700, y = 0; x <= 750; x += 1)
	{
		float x1 = x - 725;
		y = 270 + sqrt(pow(25, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 270);

		float y2 = 270 - sqrt(pow(25, 2) - pow(x1, 2));
		glVertex2f(x, 270);
		glVertex2f(x, y2);
	}
	glEnd();

	glColor3f(0.5, 0.3, 0.7);
	glPointSize(3.0f);
	glBegin(GL_LINES);
	for (float x = 760, y = 0; x <= 810; x += 1)
	{
		float x1 = x - 785;
		y = 300 + sqrt(pow(25, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 300);

		float y2 = 300 - sqrt(pow(25, 2) - pow(x1, 2));
		glVertex2f(x, 300);
		glVertex2f(x, y2);
	}
	glEnd();

	glColor3f(0.7, 0.3, 0.5);
	glPointSize(3.0f);
	glBegin(GL_LINES);
	for (float x = 820, y = 0; x <= 870; x += 1)
	{
		float x1 = x - 845;
		y = 270 + sqrt(pow(25, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 270);

		float y2 = 270 - sqrt(pow(25, 2) - pow(x1, 2));
		glVertex2f(x, 270);
		glVertex2f(x, y2);
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glPointSize(3.0f);
	glBegin(GL_LINES);
	glVertex2f(725, 270);
	glVertex2f(785, 160);
	glVertex2f(785, 300);
	glVertex2f(785, 160);
	glVertex2f(845, 270);
	glVertex2f(785, 160);
	glEnd();

	// tree
	glColor3f(1.0, 0.5, 0.1);
	glPointSize(3.0f);
	glBegin(GL_LINES);
	for (float x = 200, y = 0; x <= 300; x += 1)
	{
		float x1 = x - 250;
		y = 350 + sqrt(pow(50, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 350);

		float y2 = 350 - sqrt(pow(50, 2) - pow(x1, 2));
		glVertex2f(x, 350);
		glVertex2f(x, y2);
	}

	for (float x = 150, y = 0; x <= 230; x += 1)
	{
		float x1 = x - 190;
		y = 330 + sqrt(pow(40, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 330);

		float y2 = 330 - sqrt(pow(40, 2) - pow(x1, 2));
		glVertex2f(x, 330);
		glVertex2f(x, y2);
	}

	for (float x = 250, y = 0; x <= 330; x += 1)
	{
		float x1 = x - 290;
		y = 330 + sqrt(pow(40, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 330);

		float y2 = 330 - sqrt(pow(40, 2) - pow(x1, 2));
		glVertex2f(x, 330);
		glVertex2f(x, y2);
	}

	for (float x = 110, y = 0; x <= 170; x += 1)
	{
		float x1 = x - 140;
		y = 310 + sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 310);

		float y2 = 310 - sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, 310);
		glVertex2f(x, y2);
	}

	for (float x = 320, y = 0; x <= 360; x += 1)
	{
		float x1 = x - 340;
		y = 330 + sqrt(pow(20, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 330);

		float y2 = 330 - sqrt(pow(20, 2) - pow(x1, 2));
		glVertex2f(x, 330);
		glVertex2f(x, y2);
	}
	glEnd();

	glColor3f(0.5, 0.3, 0.3);
	glPointSize(3.0f);
	glBegin(GL_LINES);
	for (float x = 220, y = 320; x <= 270; x += 1)
	{
		glVertex2f(x, y);
		glVertex2f(x, y - 120);
	}

	for (float x1 = 160, x2 = 220, y = 300; x1 <= 170; x1 += 1, x2 += 1)
	{
		glVertex2f(x1, y);
		glVertex2f(x2, y - 50);
	}

	for (float x1 = 315, x2 =220, y = 305; x1 >= 305; x1 -= 1)
	{
		glVertex2f(x1, y);
		glVertex2f(x2, y - 50);
	}
	glEnd();

	// small flower
	if (firstin == 1)
	{
		// flower in shrub
		for (int i = 0; i <= 299; i++) 
		{
			flowerx[i] = 71 + rand() % 850;
			flowery[i] = 71 + rand() % 250;
		}
		firstin = 0;
	}

	// white flower
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(3.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i <= 99; i++)
	{
		glVertex2f(flowerx[i], flowery[i]);
	}
	glEnd();

	// red flower
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(3.0f);
	glBegin(GL_POINTS);
	for (int i = 100; i <= 199; i++)
	{
		glVertex2f(flowerx[i], flowery[i]);
	}
	glEnd();

	// blue flower
	glColor3f(0.3, 0.5, 0.7);
	glPointSize(3.0f);
	glBegin(GL_POINTS);
	for (int i = 200; i <= 299; i++)
	{
		glVertex2f(flowerx[i], flowery[i]);
	}
	glEnd();

	// shrub and flower
	glColor3f(0.5, 0.7, 0.3);
	glPointSize(3.0f);
	glBegin(GL_LINES);

	for (float x = 71, y = 150; x <= 320; x += 1)
	{
		glVertex2f(x, y);
		glVertex2f(x, y - 79);
	}

	for (float x = 850, y = 150; x <= 928; x += 1)
	{
		glVertex2f(x, y);
		glVertex2f(x, y - 79);
	}

	for (float x = 71, xt = 131; x <= 310; xt = x + 60)
	{
		for (float y = 0; x <= xt; x += 1)
		{
			float x1 = x - (xt - 30);
			y = 150 + sqrt(pow(30, 2) - pow(x1, 2));
			glVertex2f(x, y);
			glVertex2f(x, 150);
		}
	}

	for (float x = 300, y = 0; x <= 360; x += 1)
	{
		float x1 = x - 330;
		y = 130 + sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 130);

		float y2 = 130 - sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, 130);
		glVertex2f(x, y2);
	}

	for (float x = 300, y = 0; x <= 360; x += 1)
	{
		float x1 = x - 330;
		y = 101 + sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 101);

		float y2 = 101 - sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, 101);
		glVertex2f(x, y2);
	}

	for (float x = 100, y = 0; x <= 160; x += 1)
	{
		float x1 = x - 130;
		y = 171 + sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 171);

		float y2 = 171 - sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, 171);
		glVertex2f(x, y2);
	}

	for (float x = 150, y = 0; x <= 210; x += 1)
	{
		float x1 = x - 180;
		y = 175 + sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 175);

		float y2 = 175 - sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, 175);
		glVertex2f(x, y2);
	}

	for (float x = 320, y = 0; x <= 380; x += 1)
	{
		float x1 = x - 350;
		y = 71 + sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 71);
	}

	for (float x = 840, y = 0; x <= 900; x += 1)
	{
		float x1 = x - 870;
		y = 150 + sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 150);

		float y2 = 150 - sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, 150);
		glVertex2f(x, y2);
	}

	for (float x = 868, y = 0; x <= 928; x += 1)
	{
		float x1 = x - 898;
		y = 160 + sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 160);

		float y2 = 160 - sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, 160);
		glVertex2f(x, y2);
	}

	for (float x = 820, y = 0; x <= 880; x += 1)
	{
		float x1 = x - 850;
		y = 101 + sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 101);

		float y2 = 101 - sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, 101);
		glVertex2f(x, y2);
	}
	glEnd();
}

void drawCartoonFigurePanda(void)
{
	glLoadIdentity();
	glTranslatef(-0.05, 0.05, 0.0);

	// draw panda
	// eyes
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(3.0f);
	glBegin(GL_LINES);
	for (float x = 437, y = 0; x <= 457; x += 1)
	{
		float x1 = x - 447;
		y = 205 + sqrt(pow(10, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 205);

		float y2 = 205 - sqrt(pow(10, 2) - pow(x1, 2));
		glVertex2f(x, 205);
		glVertex2f(x, y2);
	}

	for (float x = 463, y = 0; x <= 483; x += 1)
	{
		float x1 = x - 473;
		y = 205 + sqrt(pow(10, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 205);

		float y2 = 205 - sqrt(pow(10, 2) - pow(x1, 2));
		glVertex2f(x, 205);
		glVertex2f(x, y2);
	}
	glEnd();

	// nose and mouse
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(2.0f);
	glBegin(GL_POINTS);

	glVertex2f(460, 190);
	glVertex2f(459, 191);
	glVertex2f(461, 191);
	glVertex2f(458, 190);
	glVertex2f(462, 190);

	for (int i = 0; i <= 8; i++)
	{
		glVertex2f(460, 190 - i);
	}

	for (float x = 450, y = 0; x <= 470; x += 1)
	{
		float x1 = x - 460;
		float y2 = 210 - sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, y2);
	}
	glEnd();

	// head and body
	glColor3f(1.0, 1.0, 1.0);
	glPointSize(3.0f);
	glBegin(GL_LINES);
	for (float x = 430, y = 0; x <= 490; x += 1)
	{
		float x1 = x - 460;
		y = 200 + sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 200);

		float y2 = 200 - sqrt(pow(30, 2) - pow(x1, 2));
		glVertex2f(x, 200);
		glVertex2f(x, y2);
	}

	for (float x = 425, y = 0; x <= 495; x += 1)
	{
		float x1 = x - 460;
		y = 130 + sqrt(pow(35, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 130);

		float y2 = 130 - sqrt(pow(35, 2) - pow(x1, 2));
		glVertex2f(x, 130);
		glVertex2f(x, y2);
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glPointSize(3.0f);
	glBegin(GL_LINES);
	glVertex2f(425, 130);
	glVertex2f(440, 211);

	glVertex2f(495, 130);
	glVertex2f(480, 211);

	for (float x = 440; x <= 480; x += 1)
	{
		glVertex2f(x, 130);
		glVertex2f(x, 211);
	}

	for (float x = 425; x <= 440; x += 1)
	{
		float y = 5.4 * x - 2165;
		glVertex2f(x, 130);
		glVertex2f(x, y);
	}

	for (float x = 480; x <= 495; x += 1)
	{
		float y = -5.4 * x + 2803;
		glVertex2f(x, 130);
		glVertex2f(x, y);
	}

	// arms and legs
	for (int i = 0; i <= 25; i ++)
	{
		glVertex2f(435, 185-i);
		glVertex2f(405, 145-i);
	}

	for (float x = 395, y = 0; x <= 415; x += 1)
	{
		float x1 = x - 405;
		y = 132.5 + sqrt(pow(10, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 132.5);

		float y2 = 132.5 - sqrt(pow(10, 2) - pow(x1, 2));
		glVertex2f(x, 132.5);
		glVertex2f(x, y2);
	}

	for (int i = 0; i <= 20; i ++)
	{
		glVertex2f(485, 185-i);
		glVertex2f(515, 145-i);
	}

	for (float x = 505, y = 0; x <= 525; x += 1)
	{
		float x1 = x - 515;
		y = 133 + sqrt(pow(10, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 133);

		float y2 = 133 - sqrt(pow(10, 2) - pow(x1, 2));
		glVertex2f(x, 133);
		glVertex2f(x, y2);
	}

	for (int i = 0; i <= 20; i ++)
	{
		glVertex2f(425+i, 150);
		glVertex2f(425+i, 80);

		glVertex2f(470 + i, 150);
		glVertex2f(470 + i, 80);
	}

	for (float x = 425, y = 0; x <= 445; x += 1)
	{
		float x1 = x - 435;
		y = 80 + sqrt(pow(10, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 80);

		float y2 = 80 - sqrt(pow(10, 2) - pow(x1, 2));
		glVertex2f(x, 80);
		glVertex2f(x, y2);
	}

	for (float x = 470, y = 0; x <= 490; x += 1)
	{
		float x1 = x - 480;
		y = 80 + sqrt(pow(10, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 80);

		float y2 = 80 - sqrt(pow(10, 2) - pow(x1, 2));
		glVertex2f(x, 80);
		glVertex2f(x, y2);
	}

	glEnd();	

	// ears
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(3.0f);
	glBegin(GL_LINES);
	for (float x = 428, y = 0; x <= 448; x += 1)
	{
		float x1 = x - 438;
		y = 225 + sqrt(pow(10, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 225);

		float y2 = 225 - sqrt(pow(10, 2) - pow(x1, 2));
		glVertex2f(x, 225);
		glVertex2f(x, y2);
	}

	for (float x = 475, y = 0; x <= 495; x += 1)
	{
		float x1 = x - 485;
		y = 225 + sqrt(pow(10, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 225);

		float y2 = 225 - sqrt(pow(10, 2) - pow(x1, 2));
		glVertex2f(x, 225);
		glVertex2f(x, y2);
	}
	glEnd();
}

void drawPeppaPig(void)
{
	glLoadIdentity();
	glTranslatef(0.05, 0.0, 0.0);

	glColor3f(1.0, 0.41, 0.705);
	glPointSize(3.0f);
	glBegin(GL_POINTS);
	for (float x = 629, y = 0; x <= 691; x += 0.5)
	{
		float x1 = x - 645;
		y = 240 + sqrt(pow(16, 2) - pow(x1, 2));
		glVertex2f(x, y);

		float y2 = 240 - sqrt(pow(16, 2) - pow(x1, 2));
		glVertex2f(x, y2);
	}
	glEnd();

	// mouse and nose
	glColor3f(0.88, 0.078, 0.235);
	glPointSize(3.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i <= 3; i++)
	{
		glVertex2f(640, 240-i);
		glVertex2f(641, 240-i);

		glVertex2f(650, 240 - i);
		glVertex2f(651, 240 - i);
	}

	for (float x = 585, y = 0; x <= 615; x += 0.5)
	{
		float x1 = x - 600;
		float y2 = 200 - sqrt(pow(15, 2) - pow(x1, 2));
		glVertex2f(x, y2);
	}
	glEnd();

	// eye
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2f(589, 225);
	glVertex2f(609, 230);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);	
	glBegin(GL_LINES);
	for (float x = 585, y = 0; x <= 593; x += 0.5)
	{
		float x1 = x - 589;
		y = 225 + sqrt(pow(4, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 225);

		float y2 = 225 - sqrt(pow(4, 2) - pow(x1, 2));
		glVertex2f(x, y2);
		glVertex2f(x, 225);
	}

	for (float x = 605, y = 0; x <= 613; x += 0.5)
	{
		float x1 = x - 609;
		y = 230 + sqrt(pow(4, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 230);

		float y2 = 230 - sqrt(pow(4, 2) - pow(x1, 2));
		glVertex2f(x, y2);
		glVertex2f(x, 230);
	}
	glEnd();

	glColor3f(1.0, 0.41, 0.705);
	glBegin(GL_LINES);
	for (float x = 560, y = 0; x <= 580; x += 1)
	{
		float x1 = x - 570;
		y = 200 + sqrt(pow(10, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 200);

		float y2 = 200 - sqrt(pow(10, 2) - pow(x1, 2));
		glVertex2f(x, 200);
		glVertex2f(x, y2);
	}
	glEnd();

	// head
	glColor3f(1.0, 0.75, 0.796);
	glBegin(GL_LINES);
	for (float x = 550, y = 0; x <= 620; x += 1)
	{
		float x1 = x - 585;
		y = 200 + sqrt(pow(35, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 200);

		float y2 = 200 - sqrt(pow(35, 2) - pow(x1, 2));
		glVertex2f(x, 200);
		glVertex2f(x, y2);
	}

	for (float x = 630, y = 0; x <= 690; x += 1)
	{
		float x1 = x - 645;
		y = 240 + sqrt(pow(15, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 240);

		float y2 = 240 - sqrt(pow(15, 2) - pow(x1, 2));
		glVertex2f(x, 240);
		glVertex2f(x, y2);
	}

	for (int i = 0; i <= 30; i ++)
	{
		glVertex2f(585, 235-i);
		glVertex2f(645, 255-i);
	}

	for (int i = 0; i <= 20; i++)
	{
		glVertex2f(585, 205 - i);
		glVertex2f(645, 225);
	}
	glEnd();

	// outline
	glColor3f(1.0, 0.41, 0.705);
	glPointSize(3.0f);
	glBegin(GL_POINTS);
	for (float x = 549, y = 0; x <= 621; x += 0.2)
	{
		float x1 = x - 585;
		y = 200 + sqrt(pow(36, 2) - pow(x1, 2));
		glVertex2f(x, y);

		float y2 = 200 - sqrt(pow(36, 2) - pow(x1, 2));
		glVertex2f(x, y2);
	}

	for (float x = 574, y = 0; x <= 586; x += 0.2)
	{
		float x1 = x - 580;
		y = 250 + sqrt(pow(6, 2) - pow(x1, 2));
		glVertex2f(x, y);
	}

	for (float x = 554, y = 0; x <= 566; x += 0.2)
	{
		float x1 = x - 560;
		y = 245 + sqrt(pow(6, 2) - pow(x1, 2));
		glVertex2f(x, y);
	}
	glEnd();

	// outline
	glColor3f(1.0, 0.41, 0.705);
	glBegin(GL_LINES);
	for (int i = 0; i <= 3; i++)
	{
		glVertex2f(585, 238-i);
		glVertex2f(645, 258-i);
	}

	for (int i = 0; i <= 3; i++)
	{
		glVertex2f(585, 185-i);
		glVertex2f(645, 225-i);
	}

	for (int i = 0; i <= 3; i++)
	{
		glVertex2f(572+i, 250);
		glVertex2f(572 + i, 230);
	}

	for (int i = 0; i <= 3; i++)
	{
		glVertex2f(585 + i, 250);
		glVertex2f(585 + i, 230);
	}

	for (int i = 0; i <= 3; i++)
	{
		glVertex2f(552 + i, 245);
		glVertex2f(552 + i, 220);
	}

	for (int i = 0; i <= 3; i++)
	{
		glVertex2f(565 + i, 245);
		glVertex2f(565 + i, 225);
	}
	glEnd();

	// ears
	glColor3f(1.0, 0.75, 0.796);
	glBegin(GL_LINES);
	for (int i = 0; i <= 10; i++)
	{
		glVertex2f(575 + i, 250);
		glVertex2f(575 + i, 230);
	}

	for (int i = 0; i <= 10; i++)
	{
		glVertex2f(555 + i, 245);
		glVertex2f(555 + i, 225);
	}

	for (float x = 575, y = 0; x <= 585; x += 0.2)
	{
		float x1 = x - 580;
		y = 250 + sqrt(pow(5, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 250);
	}

	for (float x = 555, y = 0; x <= 565; x += 0.2)
	{
		float x1 = x - 560;
		y = 245 + sqrt(pow(5, 2) - pow(x1, 2));
		glVertex2f(x, y);
		glVertex2f(x, 245);
	}
	glEnd();

	// clothing
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);

	glVertex2f(560, 175);
	glVertex2f(540, 120);

	glVertex2f(610, 175);
	glVertex2f(630, 120);

	for (float x = 560; x <= 610; x ++)
	{
		glVertex2f(x, 175);
		glVertex2f(x, 120);
	}

	for (float x = 540; x <= 560; x ++)
	{
		float y = 2.75 * x - 1365;
		glVertex2f(x, y);
		glVertex2f(x, 120);
	}

	for (float x = 610; x <= 630; x++)
	{
		float y = -2.75 * x + 1852.5;
		glVertex2f(x, y);
		glVertex2f(x, 120);
	}
	glEnd();

	// arms and legs
	glColor3f(1.0, 0.75, 0.796);
	glBegin(GL_LINES);
	for (int i = 0; i <= 7; i++)
	{
		glVertex2f(555, 165-i);
		glVertex2f(515, 140-i);
	}

	for (int i = 0; i <= 7; i++)
	{
		glVertex2f(615, 165-i);
		glVertex2f(655, 140-i);
	}

	for (int i = 0; i <= 7; i++)
	{
		glVertex2f(560+i, 120);
		glVertex2f(560+i, 90);
	}

	for (int i = 0; i <= 7; i++)
	{
		glVertex2f(610-i, 120);
		glVertex2f(610-i, 90);
	}
	glEnd();

	// shoese
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	for (int i = 0; i <= 5; i++)
	{
		glVertex2f(559, 90-i);
		glVertex2f(580, 90-i);
	}

	for (int i = 0; i <= 5; i++)
	{
		glVertex2f(602, 90 - i);
		glVertex2f(623, 90 - i);
	}
	glEnd();
}

void drawBainbow(void)
{
	glLoadIdentity();

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i <= 5; i++)
	{
		for (float x = 71, y = 0; y <= 629; x += 0.5)
		{
			float x1 = x - 471-i;
			y = 229-i + sqrt(pow(500, 2) - pow(x1, 2));
			glVertex2f(x, y);
		}
	}
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i <= 5; i++)
	{
		for (float x = 71, y = 0; y <= 629; x += 0.5)
		{
			float x1 = x - 477 - i;
			y = 223 - i + sqrt(pow(500, 2) - pow(x1, 2));
			glVertex2f(x, y);
		}
	}
	glEnd();

	glColor3f(1.0, 0.647, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i <= 5; i++)
	{
		for (float x = 71, y = 0; y <= 629; x += 0.5)
		{
			float x1 = x - 483 - i;
			y = 217 - i + sqrt(pow(500, 2) - pow(x1, 2));
			glVertex2f(x, y);
		}
	}
	glEnd();

	glColor3f(0.753, 0.055, 0.92);
	glBegin(GL_POINTS);
	for (int i = 0; i <= 5; i++)
	{
		for (float x = 71, y = 0; y <= 629; x += 0.5)
		{
			float x1 = x - 489 - i;
			y = 211 - i + sqrt(pow(500, 2) - pow(x1, 2));
			glVertex2f(x, y);
		}
	}
	glEnd();

	glColor3f(0.48, 0.408, 0.93);
	glBegin(GL_POINTS);
	for (int i = 0; i <= 5; i++)
	{
		for (float x = 71, y = 0; y <= 629; x += 0.5)
		{
			float x1 = x - 495 - i;
			y = 205 - i + sqrt(pow(500, 2) - pow(x1, 2));
			glVertex2f(x, y);
		}
	}
	glEnd();
}

void drawCover(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0);  // set color of backgroud as white
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); // Hidden surface removal
	glPushMatrix();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// draw "happy birthday"
	drawWord();
	glLoadIdentity();
	
	// draw panda
	drawCartoonFigurePanda();
	glLoadIdentity();

	// draw Peppa pig
	drawPeppaPig();
	glLoadIdentity();

	// draw cake
	drawCake();
	glLoadIdentity();

	// draw groud things
	drawGroundObjects();
	glLoadIdentity();

	// draw skyline
	drawSkyline();
	glLoadIdentity();

	// sun and clouds
	drawSkyObjects();
	glLoadIdentity();

	// draw RECT
	glLineWidth(1.0f);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(70, 70);
	glVertex2f(70, 630);
	glVertex2f(70, 70);
	glVertex2f(930, 70);
	glVertex2f(70, 630);
	glVertex2f(930, 630);
	glVertex2f(930, 630);
	glVertex2f(930, 70);
	glEnd();
	glLoadIdentity();

	// rainbow
	drawBainbow();
	glLoadIdentity();

	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_LINES); // Start fill RECT with color
	for (float i = 70.0f; i <= 930.0; i += 0.5f)
	{
		glVertex2f(i, 70);
		glVertex2f(i, 630);
	}
	glEnd();
	glLoadIdentity();

	glutSwapBuffers();
}

int main(int argc, char* argv[]) // Standard main function
{
	glutInit(&argc, (char**)argv); // Initialization
	// Define display mode: depth buffer, double buffer and RGBA color
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(150, 70); // Define the location of the window
	glutInitWindowSize(1000, 700); // Define the size of the window
	glutCreateWindow("Birthday Card"); // Create a window called ¡°Birthday Card¡±
	gluOrtho2D(0, 1000, 0, 700);
	glutDisplayFunc(drawCover); // draw cover

	glutIdleFunc(when_in_mainloop);
	glutTimerFunc(time_interval, OnTimer, 1);

	glutMouseFunc(mouse_input);//mouse callback function
	glutKeyboardFunc(keyboard_input); // keyboard callback function

	glutMainLoop(); // Enter the GLUT event processing loop
	return 0; // Return an integer value
}
