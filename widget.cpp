#include "widget.h"

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent), m_texture(0)
{
}

Widget::~Widget()
{
    delete m_texture;
}

void Widget::initializeGL()
{
    glClearColor(0.1f, 0.5f, 0.3f, 1.0f);

    loadShaders();

    float positions[] = {
        0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };
    m_positionBuffer.create();
    m_positionBuffer.bind();
    m_positionBuffer.allocate(positions, sizeof(positions));

    m_texture = new QOpenGLTexture(QImage(":/Data/Textures/TriangleCells.jpg"));
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture->setWrapMode(QOpenGLTexture::Repeat);
    m_texture->bind(0);

    m_program.bind();
    m_program.setUniformValue("uSampler", 0);
    m_program.setAttributeBuffer(0, GL_FLOAT, 0, 3, 0);
    m_program.enableAttributeArray(0);

    float texCoords[] = {
        0.5f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
    };
    m_texCoordBuffer.create();
    m_texCoordBuffer.bind();
    m_texCoordBuffer.allocate(texCoords, sizeof(texCoords));

    m_program.setAttributeBuffer(1, GL_FLOAT, 0, 2, 0);
    m_program.enableAttributeArray(1);
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    m_texture->bind(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void Widget::loadShaders()
{
    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Data/Shaders/vShader.glsl"))
    {
        close();
    }

    if (!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Data/Shaders/fShader.glsl"))
    {
        close();
    }

    if (!m_program.link())
    {
        close();
    }
}
