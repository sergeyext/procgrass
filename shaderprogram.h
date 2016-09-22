#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QOpenGLShaderProgram>
#include <QStringList>
#include <QString>

class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram() {
        shader.release();
    }

    int init(const QStringList& prepend, const QString& fname);

    template<typename ...Ts>
    inline void setUniformValue(const char*const name, Ts... values) {
        shader.setUniformValue(name, values...);
    }

    inline void bind() {
        shader.bind();
    }

    inline GLuint programId() const {
        return shader.programId();
    }

private:

    QOpenGLShaderProgram shader;
};

#endif // SHADERPROGRAM_H
