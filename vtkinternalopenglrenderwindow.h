#ifndef VTKINTERNALOPENGLRENDERWINDOW_H
#define VTKINTERNALOPENGLRENDERWINDOW_H

// Use the OpenGL API abstraction from Qt instead of from VTK because vtkgl.h
// and other Qt OpenGL-related headers do not play nice when included in the
// same compilation unit
#include <QOpenGLFunctions>

#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObject>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkObjectFactory.h>

#include <vtkRendererCollection.h>
#include <vtkCamera.h>

#include "QVTKFramebufferObjectItem.h"

class QVTKFramebufferObjectRenderer;

class vtkInternalOpenGLRenderWindow :
        public vtkGenericOpenGLRenderWindow,
        protected QOpenGLFunctions
{
public:
    vtkTypeMacro(vtkInternalOpenGLRenderWindow, vtkGenericOpenGLRenderWindow);
    static vtkInternalOpenGLRenderWindow* New();

    virtual void OpenGLInitState();

    // Override to use deferred rendering - Tell the QSG that we need to
    // be rendered which will then, at the appropriate time, call
    // InternalRender to do the actual OpenGL rendering.
    virtual void Render();

    // Do the actual OpenGL rendering
    void InternalRender();

    void SetFramebufferObject(QOpenGLFramebufferObject *);

    QVTKFramebufferObjectRenderer *QtParentRenderer;

protected:
    vtkInternalOpenGLRenderWindow();
    ~vtkInternalOpenGLRenderWindow();

};

#endif // VTKINTERNALOPENGLRENDERWINDOW_H
