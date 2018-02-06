class PauseMenu {
private:
	int highlight_x, highlight_y, ymax, ymin;
public:
	PauseMenu();
	int ReadInput(int input);
	void Draw();
	void HighlightDraw();
};

PauseMenu::PauseMenu(void) {
	highlight_x = 530;
	highlight_y = 255;
	ymin = 255;
	ymax = 355;
}

void PauseMenu::Draw(void) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//menu shape
	glColor4f(1.0, 1.0, 1.0, 0.7);
	glBegin(GL_QUADS);
	glVertex2i(0, 0);
	glVertex2i(1600, 0);
	glVertex2i(1600, 600);
	glVertex2i(0, 600);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex2i(400, 200);
	glVertex2i(800, 200);
	glVertex2i(800, 400);
	glVertex2i(400, 400);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(400, 200);
	glVertex2i(800, 200);
	glVertex2i(800, 200);
	glVertex2i(800, 400);
	glVertex2i(800, 400);
	glVertex2i(400, 400);
	glVertex2i(400, 400);
	glVertex2i(400, 200);
	glEnd();
	//menu content
	HighlightDraw();
	glColor3ub(0, 0, 0);
	glRasterPos2i(550, 250);
	YsGlDrawFontBitmap16x20("RESUME");
	glColor3ub(0, 0, 0);
	glRasterPos2i(550, 300);
	YsGlDrawFontBitmap16x20("RESTART");
	glColor3ub(0, 0, 0);
	glRasterPos2i(550, 350);
	YsGlDrawFontBitmap16x20("MENU");

}

void PauseMenu::HighlightDraw(void) {
	glColor4f(0.2, 0.0, 1.0, 0.8);
	glBegin(GL_QUADS);
	glVertex2i(highlight_x, highlight_y);
	glVertex2i(highlight_x+150, highlight_y);
	glVertex2i(highlight_x+150, highlight_y-35);
	glVertex2i(highlight_x, highlight_y-35);
	glEnd();
}


int PauseMenu::ReadInput(int input) {
	switch (input) {
	case FSKEY_UP:
		highlight_y -= 50;
		if (highlight_y < ymin) {
			highlight_y = ymax;
		}
		break;
	case FSKEY_DOWN:
		highlight_y += 50;
		if (highlight_y > ymax) {
			highlight_y = ymin;
		}
		break;
	case FSKEY_ENTER:
		switch (highlight_y) {
		case 255:
			return 0;
		case 305:
			return 1;
		case 355:
			return 2;
		}
		break;
	}
	return 3;
}
