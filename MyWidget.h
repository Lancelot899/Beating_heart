#ifndef MYWIDGET_H
#define MYWIDGET_H


#include <QGLViewer/qglviewer.h>

class Particle {
public:
    void draw();
    void animate();

public:
    Particle();

private :
  qglviewer::Vec pos_;
  float          speed;
  bool           isUp;
  static int     Num;
};


class MyWidget : public QGLViewer {
//public:
//    explicit MyWidget(QWidget* parent=0, const QGLWidget* shareWidget=0, Qt::WFlags flags=0);
//    ~MyWidget();

protected :
    void init();
    void draw();
    void animate();
    virtual QString helpString() const;

    void keyPressEvent(QKeyEvent *event);

private:
    int nbPart;
    Particle* particle;
};

#endif // MYWIDGET_H
