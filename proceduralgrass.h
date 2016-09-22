#ifndef PROCEDURALGRASS_H
#define PROCEDURALGRASS_H

#include <QOpenGLFunctions_4_1_Core>

class ProceduralGrass : private QOpenGLFunctions_4_1_Core {
public:
    ProceduralGrass();
    ~ProceduralGrass();

    void draw();

    GLuint getNumClusters() const {
        return numClusters;
    }

private:

    GLuint vao;

    GLuint posVbo;

    GLint numClusters;
};

#endif // PROCEDURALGRASS_H
