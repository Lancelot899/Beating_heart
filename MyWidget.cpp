#include <math.h>
#include <time.h>

#include <QEvent>
#include <QKeyEvent>

#include "MyWidget.h"

//MyWidget::MyWidget(QWidget* parent, const QGLWidget* shareWidget, Qt::WFlags flags)
//    : QGLViewer(parent, shareWidget, flags)
//{
//    init();
//}

//MyWidget::~MyWidget()
//{
//    if(particle != nullptr)
//        delete[] particle;
//}

int Particle::Num = 0;

void MyWidget::init()
{
    restoreStateFromFile();

    glDisable(GL_LIGHTING);
    nbPart = 10000;
    particle = new Particle[nbPart];
    glPointSize(3.0);
    setGridIsDrawn();
    help();
    startAnimation();

    setSceneRadius(1000);
}

void MyWidget::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_F11 ) {
        setFullScreen(!isFullScreen());
        return;
    }

    QGLViewer::keyPressEvent(event);
}

void MyWidget::draw()
{
    time_t tm;
    time(&tm);
    srand(tm);
    glBegin(GL_POINTS);
    for (int i=0; i<nbPart; i++)
      particle[i].draw();
    glEnd();
}

void MyWidget::animate()
{
    for (int i=0; i<nbPart; i++)
        particle[i].animate();
}

QString MyWidget::helpString() const
{
    QString text("<h2>A n i m a t i o n</h2>");
    text += "Use the <i>animate()</i> function to implement the animation part of your ";
    text += "application. Once the animation is started, <i>animate()</i> and <i>draw()</i> ";
    text += "are called in an infinite loop, at a frequency that can be fixed.<br><br>";
    text += "Press <b>Return</b> to start/stop the animation.";
    return text;
}


void Particle::draw()
{
    int r_ = rand() % 256;
    int g_ = rand() % 256;
    int b_ = rand() % 256;
    float r = float(r_) / 255.0;
    float g = float(g_) / 255.0;
    float b = float(b_) / 255.0;
    glColor3f(r, g, b);
    glVertex3fv(pos_);
}

void Particle::animate()
{
    if(pos_[2] < -M_PI / 2)
        isUp = true;
    else if(pos_[2] > M_PI / 2)
        isUp = false;
    if(isUp)
        pos_[2] += speed;
    else
        pos_[2] -= speed;
}

Particle::Particle()
    : speed(0.1 * M_PI), isUp(false)
{
    int sampNum = 1000;
    int _Odd = rand() % 2;
    double t = 2.0  * M_PI / double(sampNum);
    t *= double(++Num);
    double x = 16.0 * sin(t) * sin(t) * sin(t);
    double y = 13.0 * cos(t) - 5.0 * cos(2.0 * t) - 2.0 * cos(3.0 * t)- cos(4.0 * t);

    int sampParticleNum = 100;
    double shrink =  1.0 / (double(rand() % sampParticleNum) + 1.0);
    shrink = sqrt(shrink);
    int sampZ = rand() % 100 + 1;
    double z = M_PI / double(sampZ);
    z -= M_PI / 2;
    pos_ = qglviewer::Vec(x * shrink, y * shrink, z);
    if(z < 0.0000001)
        isUp = true;
}
