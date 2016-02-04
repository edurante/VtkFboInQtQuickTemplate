#ifndef QVTKFrameBufferObjectItem_h_
#define QVTKFrameBufferObjectItem_h_

#include <QtQuick/QQuickFramebufferObject>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkinternalopenglrenderwindow.h>

class QVTKFrameBufferObjectItem;
class vtkInternalOpenGLRenderWindow;

class QVTKFramebufferObjectRenderer : public QQuickFramebufferObject::Renderer
{
    friend class vtkInternalOpenGLRenderWindow;

public:
    QVTKFramebufferObjectRenderer(vtkInternalOpenGLRenderWindow*);
    ~QVTKFramebufferObjectRenderer();

    virtual void synchronize(QQuickFramebufferObject*);

    // Called from the render thread when the GUI thread is NOT blocked
    virtual void render();

    QOpenGLFramebufferObject *createFramebufferObject(const QSize&);

    vtkInternalOpenGLRenderWindow *m_vtkRenderWindow;
    QOpenGLFramebufferObject *m_framebufferObject;
};

class QVTKFrameBufferObjectItem : public QQuickFramebufferObject
{
   Q_OBJECT

public:
   QVTKFrameBufferObjectItem();
   ~QVTKFrameBufferObjectItem();
   Renderer *createRenderer() const;
   vtkGenericOpenGLRenderWindow* GetRenderWindow() const;

protected:
   // Called once before the FBO is created for the first time. This method is
   // called from render thread while the GUI thread is blocked.
   virtual void init();

   vtkGenericOpenGLRenderWindow *m_win;

   friend class QVTKFramebufferObjectRenderer;
};

#endif
