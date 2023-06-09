#define _USE_MATH_DEFINES

#include "MyGLWidget.h"
#include <QApplication>

#include <QDebug>
// Pour Windows / Linux,
#include <OpenGL/glu.h>
// Pour mac OS,
// #include <OpenGL/glu.h>


// Declarations des constantes
const unsigned int WIN_WIDTH_HEIGHT = 900;

// Constructeur
MyGLWidget::MyGLWidget(QWidget * parent) : QOpenGLWidget(parent)
{



   setFixedSize(WIN_WIDTH_HEIGHT, WIN_WIDTH_HEIGHT);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(6); // Update every 16 milliseconds (approximately 60 FPS)

    distance = -10.0f; // Initial distance

    /* initialize random seed: */
    srand (time(NULL));

    randomId = rand() % 5 + 1;
    w_State = new State(randomId);


}

// Fonction d'initialisation
void MyGLWidget::initializeGL()
{

    // Reglage de la couleur de fond
    initializeOpenGLFunctions();
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);



    glEnable(GL_TEXTURE_2D);

    // Create an array of two texture IDs
    m_textureId = new GLuint[2];

    // Generate two texture IDs
    glGenTextures(2, m_textureId);

    // Bind the first texture ID
    glBindTexture(GL_TEXTURE_2D, m_textureId[0]);

    // Load the logo image from the specified path
    QImage logo("/Users/mac/Desktop/Construction-Labrique-Mur-Exterieur-Brique-1200x675.jpg");

    // Convert the logo image format to RGBA8888
    logo = logo.convertToFormat(QImage::Format_RGBA8888);

    // Specify the texture image data for the first texture
    glTexImage2D(GL_TEXTURE_2D, 0, 4, logo.width(), logo.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, logo.bits());

    // Set the texture filtering options for the first texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Bind the second texture ID
    glBindTexture(GL_TEXTURE_2D, m_textureId[1]);

    // Load the mur image from the specified path
    QImage mur("/Users/mac/Documents/Etudes/TSE/TDS/TestWebCamQt/img/telecom.png");

    // Convert the mur image format to RGBA8888
    mur = mur.convertToFormat(QImage::Format_RGBA8888);

    // Specify the texture image data for the second texture
    glTexImage2D(GL_TEXTURE_2D, 0, 4, mur.width(), mur.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, mur.bits());

    // Set the texture filtering options for the second texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

// Fonction de redimensionnement
void MyGLWidget::resizeGL(int width, int height)
{

    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)width / height, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

// Fonction d'affichage
void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
   if(gameStarted){
    // Set camera position and orientation
    gluLookAt(0, 10, 15, 0, 0, 0, 0, 1, 0);
   if(distance>=-1.0f)
   {
//    detectedId = cam->detectConfig();
//    emit near();
   detectedId= 1;
    if(detectedId!= -1)
    {
         drawHand(detectedId);

        qDebug()<<detectedId;
   }
   }else  drawHand(0);

    drawWall();
}
}





void MyGLWidget::drawWall(){

    glTranslatef(0, 0, distance);

    for (int row = 0; row < 10; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            if(row==9 && col ==7)
            {
                glEnable(GL_TEXTURE_2D);
              glBindTexture(GL_TEXTURE_2D, m_textureId[1]);

            if (w_State->deleteMatrix[row][col])
                continue;

            // Create cube at position (row, col)
            float x = col - 8 / 2.0f + 0.5f;
            float y = row - 10 / 2.0f + 0.5f;

            glPushMatrix();
            glTranslatef(x, y, 0.0f);
            drawCube();
            glPopMatrix();

              glDisable(GL_TEXTURE_2D);

        }
            else{
                glEnable(GL_TEXTURE_2D);
              glBindTexture(GL_TEXTURE_2D, m_textureId[0]);
              if (w_State->deleteMatrix[row][col])
                  continue;

              // Create cube at position (row, col)
              float x = col - 8 / 2.0f + 0.5f;
              float y = row - 10 / 2.0f + 0.5f;

              glPushMatrix();
              glTranslatef(x, y, 0.0f);
              drawCube();
              glPopMatrix();

                glDisable(GL_TEXTURE_2D);
            }


        }
    }

    distance += 0.05f; // Increase the distance to move the wall closer
    if (distance >= 1.0f) // Check if the wall touch the hand
   {
       if(randomId== detectedId)
           emit match();
       else{
           emit loss();
          gameStarted= false;
       }
       emit far();
       distance = -10.0f; // Reset the distance to restart the animation

       srand (time(NULL));
       randomId = rand() % 5 + 1;
       w_State = new State(randomId);
   }

     glDisable(GL_TEXTURE_2D);
}

void MyGLWidget::drawHand(int id){
    h_State = new State(id);
    for (int row = 0; row < 10; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            if (!h_State->deleteMatrix[row][col])
                continue;

            // Create cube at position (row, col)
            float x = col - 8 / 2.0f + 0.5f;
            float y = row - 10 / 2.0f + 0.5f;

            glPushMatrix();
            glTranslatef(x, y, 0.0f);
            drawCube();
            glPopMatrix();
        }
    }
}


void MyGLWidget::replay()
{
    distance = -10.0f; // Reset the distance to restart the animation

    srand (time(NULL));
    randomId = rand() % 5 + 1;
    w_State = new State(randomId);
}

//void MyGLWidget::drawCube()
//{
//   glBegin(GL_QUADS);

//   // Front face
//   glColor3f(1, 0, 0);
//   glVertex3f(-0.5f, -0.5f, 0.5f);
//   glVertex3f(0.5f, -0.5f, 0.5f);
//   glVertex3f(0.5f, 0.5f, 0.5f);
//   glVertex3f(-0.5f, 0.5f, 0.5f);

//   // Back face
//   glColor3f(0, 1, 0);
//   glVertex3f(-0.5f, -0.5f, -0.5f);
//   glVertex3f(-0.5f, 0.5f, -0.5f);
//   glVertex3f(0.5f, 0.5f, -0.5f);
//   glVertex3f(0.5f, -0.5f, -0.5f);

//   // Top face
//   glColor3f(0, 0, 1);
//   glVertex3f(-0.5f, 0.5f, -0.5f);
//   glVertex3f(-0.5f, 0.5f, 0.5f);
//   glVertex3f(0.5f, 0.5f, 0.5f);
//   glVertex3f(0.5f, 0.5f, -0.5f);

//   // Bottom face
//   glColor3f(1, 1, 0);
//   glVertex3f(-0.5f, -0.5f, -0.5f);
//   glVertex3f(0.5f, -0.5f, -0.5f);
//   glVertex3f(0.5f, -0.5f, 0.5f);
//   glVertex3f(-0.5f, -0.5f, 0.5f);

//   // Left face
//   glColor3f(0, 1, 1);
//   glVertex3f(-0.5f, -0.5f, -0.5f);
//   glVertex3f(-0.5f, -0.5f, 0.5f);
//   glVertex3f(-0.5f, 0.5f, 0.5f);
//   glVertex3f(-0.5f, 0.5f, -0.5f);

//   // Right face
//   glColor3f(1, 0, 1);
//   glVertex3f(0.5f, -0.5f, -0.5f);
//   glVertex3f(0.5f, 0.5f, -0.5f);
//   glVertex3f(0.5f, 0.5f, 0.5f);
//   glVertex3f(0.5f, -0.5f, 0.5f);

//   glEnd();
//}
void MyGLWidget::drawCube()
{
    // Enable texturing


    glBegin(GL_QUADS);

    // Front face

    glTexCoord2f(0, 0);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 1);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0, 1);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Back face

    glTexCoord2f(1, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1, 1);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0, 1);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0, 0);
    glVertex3f(0.5f, -0.5f, -0.5f);

    // Top face

    glTexCoord2f(0, 1);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0, 0);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(1, 0);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1, 1);
    glVertex3f(0.5f, 0.5f, -0.5f);

    // Bottom face

    glTexCoord2f(1, 1);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0, 1);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(0, 0);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1, 0);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    // Left face

    glTexCoord2f(1, 0);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1, 1);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(0, 1);

    glEnd();
}
void MyGLWidget::setCam(Cam *cam)
{
   this->cam = cam;
}






void  MyGLWidget::stopGame()
{
    gameStarted= false;
    update();

}
void  MyGLWidget::startGame()
{
    gameStarted= true;
    update();

}

