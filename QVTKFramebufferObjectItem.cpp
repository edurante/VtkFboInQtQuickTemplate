#include "QVTKFramebufferObjectItem.h"

QVTKFramebufferObjectRenderer::QVTKFramebufferObjectRenderer(
        vtkInternalOpenGLRenderWindow *rw) :
    m_vtkRenderWindow(rw),
    m_framebufferObject(0)
{
    m_vtkRenderWindow->Register(NULL);
    m_vtkRenderWindow->QtParentRenderer = this;
}

QVTKFramebufferObjectRenderer::~QVTKFramebufferObjectRenderer()
{
    m_vtkRenderWindow->QtParentRenderer = 0;
    m_vtkRenderWindow->Delete();
}

void QVTKFramebufferObjectRenderer::synchronize(QQuickFramebufferObject *item)
{
    // the first synchronize call - right before the the framebufferObject
    // is created for the first time
    if (!m_framebufferObject)
    {
        QVTKFrameBufferObjectItem *vtkItem =
                static_cast<QVTKFrameBufferObjectItem*>(item);
        vtkItem->init();
    }
}

QOpenGLFramebufferObject *QVTKFramebufferObjectRenderer::createFramebufferObject(
        const QSize &size)
{
    qDebug("QVTKFramebufferObjectRenderer::createFramebufferObject");
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::Depth);
    m_framebufferObject = new QOpenGLFramebufferObject(size, format);

    m_vtkRenderWindow->SetFramebufferObject(m_framebufferObject);

    return m_framebufferObject;
}

void QVTKFramebufferObjectRenderer::render()
{    
    m_vtkRenderWindow->PushState();
    m_vtkRenderWindow->OpenGLInit();
    m_vtkRenderWindow->InternalRender(); // vtkXOpenGLRenderWindow renders the scene to the FBO
    m_vtkRenderWindow->PopState();

    // Dolly camera back and forth - FOR DEMONSTRATION PURPOSES ONLY
    static int callCount = 0;
    ++callCount;
    double dolly = 1.0 + ((callCount % 200) > 100 ? -0.001 : 0.001);
    m_vtkRenderWindow->GetRenderers()->GetFirstRenderer()->GetActiveCamera()->Dolly(dolly);
    m_vtkRenderWindow->GetRenderers()->GetFirstRenderer()->GetActiveCamera()->Azimuth(1);
    this->update();
}

QVTKFrameBufferObjectItem::QVTKFrameBufferObjectItem()
{
    m_win = vtkInternalOpenGLRenderWindow::New();
}

QVTKFrameBufferObjectItem::~QVTKFrameBufferObjectItem()
{
    m_win->Delete();
}

QQuickFramebufferObject::Renderer *QVTKFrameBufferObjectItem::createRenderer() const
{
    return new QVTKFramebufferObjectRenderer(static_cast<vtkInternalOpenGLRenderWindow*>(m_win));
}

vtkGenericOpenGLRenderWindow *QVTKFrameBufferObjectItem::GetRenderWindow() const
{
    return m_win;
}

void QVTKFrameBufferObjectItem::init()
{
    qDebug("QVTKFrameBufferObjectItem::init");
}
