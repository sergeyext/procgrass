#include "proceduralgrass.h"

#include <random>

const GLuint ATTRIBINDEX_VERTEX = 0;

ProceduralGrass::ProceduralGrass() {
    initializeOpenGLFunctions();
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &posVbo);
    glEnableVertexAttribArray(ATTRIBINDEX_VERTEX);
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);

    const int numNodes = 14;
    const GLfloat gridStep = 3.0f;
    const GLfloat xDispAmp = 5.0f;
    const GLfloat zDispAmp = 5.0f;
    const GLfloat yDispAmp = 0.3f;
    numClusters = numNodes * numNodes;
    GLfloat *vertices = new GLfloat[numClusters * 4];
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<GLfloat> xDisp(-xDispAmp, xDispAmp);
    std::uniform_real_distribution<GLfloat> yDisp(-yDispAmp, yDispAmp);
    std::uniform_real_distribution<GLfloat> zDisp(-zDispAmp, zDispAmp);
    std::uniform_int_distribution<GLint> numStems(12, 64);
    for(int i = 0; i < numNodes; ++i) {
        for(int j = 0; j < numNodes; ++j) {
            const int idx = (i * numNodes + j) * 4;
            vertices[idx]     = (i - numNodes / 2) * gridStep + xDisp(mt);
            vertices[idx + 1] = yDisp(mt);
            vertices[idx + 2] = (j - numNodes / 2) * gridStep + zDisp(mt);
            vertices[idx + 3] = numStems(mt);
        }
    }
    glVertexAttribPointer(ATTRIBINDEX_VERTEX, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numClusters * 4, vertices, GL_STATIC_DRAW);
    glFinish();
    delete[] vertices;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ProceduralGrass::draw() {
    glBindVertexArray(vao);
    glPatchParameteri(GL_PATCH_VERTICES, 1);
    glDrawArrays(GL_PATCHES, 0, numClusters);
    glBindVertexArray(0);
}

ProceduralGrass::~ProceduralGrass() {
    glDeleteBuffers(1, &posVbo);
    glDeleteVertexArrays(1, &vao);
}
