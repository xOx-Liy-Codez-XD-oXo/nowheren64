GLuint dlStage;
GLuint dlLakeHead, dlLakeHair, dlLakeEars, dlLakeHairTufts, dlLakeEye, dlLakePupil, dlLakeHairClipping;
GLuint dlLakeEyebrow;
GLuint dlLakeMouthClose, dlLakeMouthTeeth, dlLakeMouthEh, dlLakeMouthM, dlLakeMouthO;
GLuint dlLakeHairRipLeft, dlLakeHairTuftsRipLeft, dlLakeEarsRipLeft;
GLuint dlLakeHairRipRight, dlLakeHairTuftsRipRight, dlLakeEarsRipRight;
GLuint dlLakeTorso;
GLuint dlscissor1, dlscissor2;
GLuint dlstring;

void makeDisplayLists() {
	dlStage = glGenLists(1);
	dlLakeHairClipping = glGenLists(1);
	dlLakeHead = glGenLists(1);
	dlLakeEars = glGenLists(1);
	dlLakeHair = glGenLists(1);
	dlLakeHairTufts = glGenLists(1);
	dlLakeEye = glGenLists(1);
	dlLakeEyebrow = glGenLists(1);
	dlLakePupil = glGenLists(1);
	dlLakeMouthClose = glGenLists(1);
	dlLakeMouthTeeth = glGenLists(1);
	dlLakeMouthEh = glGenLists(1);
	dlLakeMouthM = glGenLists(1);
	dlLakeMouthO = glGenLists(1);
	dlLakeEarsRipLeft = glGenLists(1);
	dlLakeHairRipLeft = glGenLists(1);
	dlLakeHairTuftsRipLeft = glGenLists(1);
	dlLakeEarsRipRight = glGenLists(1);
	dlLakeHairRipRight = glGenLists(1);
	dlLakeHairTuftsRipRight = glGenLists(1);
	dlLakeTorso = glGenLists(1);
	dlscissor1 = glGenLists(1);
	dlscissor2 = glGenLists(1);
	dlstring = glGenLists(1);


	glNewList(dlStage, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < 18; i++) {
		int i3 = i * 3;
		glColor3f(stageVertCol[i3], stageVertCol[i3+1], stageVertCol[i3+2]);
		glVertex3f(stageVertPos[i3], stageVertPos[i3+1], stageVertPos[i3+2]);
	}
	glEnd();
	glEndList();
	
	glNewList(dlLakeHead, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < lakeHeadtricount * 3; i++) {
		int i3 = i * 3;
		glColor3b(lakeHeadvertcol[i3], lakeHeadvertcol[i3+1], lakeHeadvertcol[i3+2]);
		glVertex3f(lakeHeadvertpos[i3], lakeHeadvertpos[i3+1], lakeHeadvertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlLakeTorso, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < lakeTorsotricount * 3; i++) {
		int i3 = i * 3;
		glColor3b(lakeTorsovertcol[i3], lakeTorsovertcol[i3+1], lakeTorsovertcol[i3+2]);
		glVertex3f(lakeTorsovertpos[i3], lakeTorsovertpos[i3+1], lakeTorsovertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlLakeEars, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < lakeEarstricount * 3; i++) {
		int i3 = i * 3;
		glColor3b(lakeEarsvertcol[i3], lakeEarsvertcol[i3+1], lakeEarsvertcol[i3+2]);
		glVertex3f(lakeEarsvertpos[i3], lakeEarsvertpos[i3+1], lakeEarsvertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlLakeEarsRipLeft, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < lakeEarsRipLefttricount * 3; i++) {
		int i3 = i * 3;
		glColor3b(lakeEarsRipLeftvertcol[i3], lakeEarsRipLeftvertcol[i3+1], lakeEarsRipLeftvertcol[i3+2]);
		glVertex3f(lakeEarsRipLeftvertpos[i3], lakeEarsRipLeftvertpos[i3+1], lakeEarsRipLeftvertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlLakeEarsRipRight, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < lakeEarsRipRighttricount * 3; i++) {
		int i3 = i * 3;
		glColor3b(lakeEarsRipRightvertcol[i3], lakeEarsRipRightvertcol[i3+1], lakeEarsRipRightvertcol[i3+2]);
		glVertex3f(lakeEarsRipRightvertpos[i3], lakeEarsRipRightvertpos[i3+1], lakeEarsRipRightvertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlLakeHairTufts, GL_COMPILE);
	glColor3b(0, 0, 0);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < lakeHairTuftstricount * 3; i++) {
		int i3 = i * 3;
		glVertex3f(lakeHairTuftsvertpos[i3], lakeHairTuftsvertpos[i3+1], lakeHairTuftsvertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlLakeHairTuftsRipLeft, GL_COMPILE);
	glColor3b(0, 0, 0);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < lakeHairTuftsRipLefttricount * 3; i++) {
		int i3 = i * 3;
		glVertex3f(lakeHairTuftsRipLeftvertpos[i3], lakeHairTuftsRipLeftvertpos[i3+1], lakeHairTuftsRipLeftvertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlLakeHairTuftsRipRight, GL_COMPILE);
	glColor3b(0, 0, 0);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < lakeHairTuftsRipRighttricount * 3; i++) {
		int i3 = i * 3;
		glVertex3f(lakeHairTuftsRipRightvertpos[i3], lakeHairTuftsRipRightvertpos[i3+1], lakeHairTuftsRipRightvertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlLakeHair, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < lakeHairRegulartricount * 3; i++) {
		int i3 = i * 3;
		glColor3b(lakeHairRegularvertcol[i3], lakeHairRegularvertcol[i3+1], lakeHairRegularvertcol[i3+2]);
		glVertex3f(lakeHairRegularvertpos[i3], lakeHairRegularvertpos[i3+1], lakeHairRegularvertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlLakeHairRipLeft, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < lakeHairRipLefttricount * 3; i++) {
		int i3 = i * 3;
		glColor3b(lakeHairRipLeftvertcol[i3], lakeHairRipLeftvertcol[i3+1], lakeHairRipLeftvertcol[i3+2]);
		glVertex3f(lakeHairRipLeftvertpos[i3], lakeHairRipLeftvertpos[i3+1], lakeHairRipLeftvertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlLakeHairRipRight, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < lakeHairRipRighttricount * 3; i++) {
		int i3 = i * 3;
		glColor3b(lakeHairRipRightvertcol[i3], lakeHairRipRightvertcol[i3+1], lakeHairRipRightvertcol[i3+2]);
		glVertex3f(lakeHairRipRightvertpos[i3], lakeHairRipRightvertpos[i3+1], lakeHairRipRightvertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlLakeEye, GL_COMPILE);
	glColor3b(255, 255, 255);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < lakeEyetricount * 3; i++) {
		int i3 = i * 3;
		glVertex3f(lakeEyevertpos[i3], lakeEyevertpos[i3+1], lakeEyevertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlLakePupil, GL_COMPILE);
	glColor3b(0, 0, 0);
	glBegin(GL_QUADS);
		glVertex3f(-1.0, 1.0, 0.0f);
		glVertex3f(1.0, 1.0, 0.0f);
		glVertex3f(1.0, -1.0, 0.0f);
		glVertex3f(-1.0, -1.0, 0.0f);
	glEnd();
	glEndList();

	glNewList(dlLakeMouthEh, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < lakeMouthEhtricount * 3; i++) {
		int i3 = i * 3;
		glColor3b(lakeMouthEhvertcol[i3], lakeMouthEhvertcol[i3+1], lakeMouthEhvertcol[i3+2]);
		glVertex3f(lakeMouthEhvertpos[i3], lakeMouthEhvertpos[i3+1], lakeMouthEhvertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlLakeMouthTeeth, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < lakeMouthClosejawShoteeftricount * 3; i++) {
		int i3 = i * 3;
		glColor3b(lakeMouthClosejawShoteefvertcol[i3], lakeMouthClosejawShoteefvertcol[i3+1], lakeMouthClosejawShoteefvertcol[i3+2]);
		glVertex3f(lakeMouthClosejawShoteefvertpos[i3], lakeMouthClosejawShoteefvertpos[i3+1], lakeMouthClosejawShoteefvertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlLakeMouthClose, GL_COMPILE);
	glColor3b(16, 16, 16);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < lakeMouthClosetricount * 3; i++) {
		int i3 = i * 3;
		glVertex3f(lakeMouthClosevertpos[i3], lakeMouthClosevertpos[i3+1], lakeMouthClosevertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlLakeMouthO, GL_COMPILE);
	glColor3b(16, 16, 16);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < lakeMouthOtricount * 3; i++) {
		int i3 = i * 3;
		glVertex3f(lakeMouthOvertpos[i3], lakeMouthOvertpos[i3+1], lakeMouthOvertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlLakeMouthM, GL_COMPILE);
	glColor3b(16, 16, 16);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < lakeMouthMtricount * 3; i++) {
		int i3 = i * 3;
		glVertex3f(lakeMouthMvertpos[i3], lakeMouthMvertpos[i3+1], lakeMouthMvertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlLakeEyebrow, GL_COMPILE);
	glColor3b(255, 255, 255);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < lakeMouthMtricount * 3; i++) {
		int i3 = i * 3;
		glVertex3f(lakeEyebrowvertpos[i3], lakeEyebrowvertpos[i3+1], lakeEyebrowvertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlscissor1, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < scissor1tricount * 3; i++) {
		int i3 = i * 3;
		glColor3b(scissor1vertcol[i3], scissor1vertcol[i3+1], scissor1vertcol[i3+2]);
		glVertex3f(scissor1vertpos[i3], scissor1vertpos[i3+1], scissor1vertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlscissor2, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < scissor2tricount * 3; i++) {
		int i3 = i * 3;
		glColor3b(scissor2vertcol[i3], scissor2vertcol[i3+1], scissor2vertcol[i3+2]);
		glVertex3f(scissor2vertpos[i3], scissor2vertpos[i3+1], scissor2vertpos[i3+2]);
	}
	glEnd();
	glEndList();

	glNewList(dlLakeHairClipping, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < clippingtricount * 3; i++) {
		int i3 = i * 3;
		glColor3b(clippingvertcol[i3], clippingvertcol[i3+1], clippingvertcol[i3+2]);
		glVertex3f(clippingvertpos[i3] * 16.0f, clippingvertpos[i3+1] * 16.0f, clippingvertpos[i3+2] * 16.0f);
	}
	glEnd();
	glEndList();

	glNewList(dlstring, GL_COMPILE);
	glColor3b(96, 96, 96);
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < stringtricount * 3; i++) {
		int i3 = i * 3;
		glVertex3f(stringvertpos[i3], stringvertpos[i3+1], stringvertpos[i3+2]);
	}
	glEnd();
	glEndList();
}