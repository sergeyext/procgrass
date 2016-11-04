#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QOpenGLShaderProgram>
#include <QStringList>
#include <QString>

/**
 * @brief Thin shader program wrapper class.
 */
class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram() {
        shader.release();
    }

    /**
     * @brief Initialize shader program.
     * @param[in] preprend List of file names with shaders to be prepended to each shader source.
     * @param[in] fname Shader file name stub.
     * @return 0 - Success. Nonzero indicates failure.
     *
     * Algorithm:
     * 1) Append ".vsh", ".fsh", ".gsh", ".tcs" and ".tes" to fname in turn. Use each string as a
     * filename to read the appropriate shader source.
     * 2) Read all files from prepend, concatenate them together and prerpend to each shader stage
     * source.
     * 3) Compile shaders, link the program.
     */
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
