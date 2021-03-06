#ifndef SCENE_H
#define SCENE_H
#include <QQuaternion>
#include <QMatrix4x4>
#include <QImage>
#include <QVector3D>
#include <QOpenGLTexture>
#include <QImage>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QImage>

#include "src_viewer/camera.h"
#include "src_viewer/transform.h"
#include "src_viewer/vertex.h"
#include "src_viewer/light.h"

class Scene : protected QOpenGLFunctions
{
public:
    Scene();

    // camera
    void rotateCameraX(float angle) { camera.rotateX(angle); }
    void rotateCameraY(float angle) { camera.rotateY(angle); }
    void zoomCameraIn()             { camera.zoomIn(); }
    void zoomCameraOut()            { camera.zoomOut(); }

    QVector3D getCameraPosition()   { return camera.getPosition(); }


    // transform
    void setTransformTranslation(const QVector3D &translation);
    void setTransformScale(float scale);
    void setTransformRotation(float xRot, float yRot);
    // left handed
    // relative to rotations
    QVector3D forwardTransform() const      { return transform.forward(); }
    QVector3D upTransform() const           { return transform.up(); }
    QVector3D rightTransform() const        { return transform.right(); }


    void initializeSceneOpenGLFunctions();
    void changeProjection(int width, int height);


    // transformation matrice getters
    const QMatrix4x4 &getModelToWorldMatrix();
    const QMatrix4x4 &getWorldToCameraMatrix();
    const QMatrix4x4 &getCameraToViewMatrix();


    // add texture to program
    void addDiffuseMap(QImage &diffuseMap, QOpenGLShaderProgram &program);
    void addDisplacementMap(QImage &displacementMap, QOpenGLShaderProgram &program);
    void addNormalMap(QImage &normalMap, QOpenGLShaderProgram &program);
    void addSpecularMap(QImage &specularMap, QOpenGLShaderProgram &program);

    // getters for texture
    QImage &getDiffuse()        { return diffuse; }
    QImage &getDisplacement()   { return displacement; }
    QImage &getNormal()         { return normal; }
    QImage &getSpecular()       { return specular; }

    // flags for textures
    bool applyingDiffuse       = false;
    bool applyingDisplacement  = false;
    bool applyingNormal        = false;
    bool applyingSpecular      = false;

    // vertices
    Vertex vertices[2400];
    void calculateVertices();

    bool checkForReady();
private:
    // transformation matrice
    Camera camera;
    Transform transform;
    QMatrix4x4 projection;

    // Textures
    QImage diffuse;
    QImage displacement;
    QImage normal;
    QImage specular;
};



#endif // SCENE_H
