#include "shaderprogram.h"

#include <QFile>
#include <QList>
#include <QPair>
#include <QMessageBox>
#include <QTextStream>

ShaderProgram::ShaderProgram() {
}

int ShaderProgram::init(const QStringList& prepend, const QString& fname) {
    // Shader types with file extensions
    const QVector<QPair<QOpenGLShader::ShaderTypeBit, QString>> shaderTypes = {
        {QOpenGLShader::Vertex, ".vsh"},
        {QOpenGLShader::Fragment, ".fsh"},
        {QOpenGLShader::Geometry, ".gsh"},
        {QOpenGLShader::TessellationControl, ".tcs"},
        {QOpenGLShader::TessellationEvaluation, ".tes"}
    };
    // Shader "library" code
    QString sharedCode;
    for(const QString& prependFname : prepend) {
        QFile f(prependFname);
        if(!f.open(QIODevice::ReadOnly)) {
            qDebug() << "Could not open shader library file: " + prependFname;
            return 5;
        }
        QTextStream in(&f);
        sharedCode += in.readAll();
    }
    // Shaders stage code which contains main()
    for(const auto& st : shaderTypes) {
        const QString shaderFname = fname + st.second;
        QFile f(shaderFname);
        if(!f.open(QIODevice::ReadOnly)) {
            qDebug() << "Could not open shader stage file: " + shaderFname;
            return 4;
        }
        QTextStream in(&f);
        if(!shader.addShaderFromSourceCode(st.first, sharedCode + in.readAll())) {
            qDebug() << "Shader compilation failed.";
            return 1;
        }
    }
    // Linking shaders into program
    if(!shader.link()) {
        qDebug() << "Shader linking failed.";
        return 2;
    }
    return 0;
}
