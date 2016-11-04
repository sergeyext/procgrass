#ifndef PROCEDURALGRASS_H
#define PROCEDURALGRASS_H

#include <QOpenGLFunctions_4_1_Core>

/**
 * @brief Procedural grass "geometry" wrapper.
 *
 * Each grass cluster holds only one abstract vertex with one 4-dimensional vertex attribute.
 * Three first elements are cluster position in world space, and the fourth one is the number of
 * stems in the cluster.
 * Positions are generated as randomly distorted two-dimensional square lattice points.
 * Number of stems cannot exceed 64 due to OpenGL tesselation level limitations.
 * See isolines abstract patch description: https://www.opengl.org/wiki/Tessellation
 */
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
