#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    void loadShaders();

    QOpenGLShaderProgram m_program;
    QOpenGLBuffer m_positionBuffer;
    QOpenGLBuffer m_texCoordBuffer;
    QOpenGLTexture *m_texture;

};
#endif // WIDGET_H
