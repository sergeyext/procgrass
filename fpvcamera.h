#ifndef FPVCAMERA_H
#define FPVCAMERA_H

#include <QMatrix4x4>
#include <QVector3D>

/**
 * @brief First person view camera class.
 *
 * Camera class encapsulates camera position, orientation, side axes (needed for movement)
 * and projection.
 */
class FpvCamera
{
public:
    FpvCamera() {}

    //! @brief Returns scene transformation matrix, including projection.
    inline QMatrix4x4 getMatrix() const {
        return projectionMatrix * orientPosMatrix;
    }

    inline QVector3D getPosition() const {
        return position;
    }

    inline QVector3D getLookDirection() const {
        return look;
    }

    inline void setProjection(float w, float h) {
        float asp = (float)w / h;
        projectionMatrix.setToIdentity();
        projectionMatrix.perspective(60, asp, 1, 1e6);
    }

    inline void setAngles(float pitch, float yaw) {
        this->pitch = pitch;
        this->yaw = yaw;
        updateAxes();
        rebuildMatrix();
        updateLook();
    }

    inline void setPosition(const QVector3D& pos) {
        position = pos;
        rebuildMatrix();
    }

    inline void rotate(float dPitch, float dYaw) {
        pitch += dPitch;
        yaw += dYaw;
        updateAxes();
        rebuildMatrix();
        updateLook();
    }

    inline void move(float dFwd, float dSide) {
        position += zaxis * dFwd;
        position -= xaxis * dSide;
        rebuildMatrix();
    }

private:

    inline void updateAxes() {
        const float cosPitch = cos(pitch);
        const float sinPitch = sin(pitch);
        const float cosYaw = cos(yaw);
        const float sinYaw = sin(yaw);
        xaxis = QVector3D{ cosYaw, 0, -sinYaw };
        yaxis = QVector3D{ sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
        zaxis = QVector3D{ sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };
    }

    inline void updateLook() {
        look = QVector3D{0.0f, 0.0f, -1.0f} * QMatrix4x4 {
            xaxis.x(), xaxis.y(), xaxis.z(), 0.0f,
            yaxis.x(), yaxis.y(), yaxis.z(), 0.0f,
            zaxis.x(), zaxis.y(), zaxis.z(), 0.0f,
            0, 0, 0, 1
        };
    }

    inline void rebuildMatrix() {
        static const auto dotProduct = &QVector3D::dotProduct;
        orientPosMatrix = QMatrix4x4 {
            xaxis.x(), xaxis.y(), xaxis.z(), -dotProduct(xaxis, position),
            yaxis.x(), yaxis.y(), yaxis.z(), -dotProduct(yaxis, position),
            zaxis.x(), zaxis.y(), zaxis.z(), -dotProduct(zaxis, position),
            0, 0, 0, 1
        };
    }

    QMatrix4x4 projectionMatrix;

    QMatrix4x4 orientPosMatrix;

    float pitch = 0.0f;
    float yaw = 0.0f;
    QVector3D look = {0.0f, 0.0f, -1.0f};
    QVector3D position = {0.0f, 0.0f, 0.0f};
    QVector3D xaxis = {1.0f, 0.0f, 0.0f};
    QVector3D yaxis = {0.0f, 1.0f, 0.0f};
    QVector3D zaxis = {0.0f, 0.0f, 1.0f};
};

#endif
