#include "vtkinternalopenglrenderwindow.h"

vtkStandardNewMacro(vtkInternalOpenGLRenderWindow);

vtkInternalOpenGLRenderWindow::vtkInternalOpenGLRenderWindow() :
    QtParentRenderer(0)
{

}

vtkInternalOpenGLRenderWindow::~vtkInternalOpenGLRenderWindow()
{
    // Prevent superclass destructors from destroying the framebuffer object.
    // QOpenGLFramebufferObject owns the FBO and manages it's lifecyle.
    this->OffScreenRendering = 0;
}

void vtkInternalOpenGLRenderWindow::OpenGLInitState()
{
    Superclass::OpenGLInitState();

    // Before any of the gl* functions in QOpenGLFunctions are called for a
    // given OpenGL context, an initialization must be run within that context
    this->MakeCurrent();
    initializeOpenGLFunctions();

    //glUseProgram(0); // Shouldn't Superclass::OpenGLInitState() handle this?
}

void vtkInternalOpenGLRenderWindow::Render()
{
    if (this->QtParentRenderer)
    {
        this->QtParentRenderer->update();
    }
}

void vtkInternalOpenGLRenderWindow::InternalRender()
{
    Superclass::Render();
}

void vtkInternalOpenGLRenderWindow::SetFramebufferObject(
        QOpenGLFramebufferObject *fbo)
{
   // QOpenGLFramebufferObject documentation states that "The color render
   // buffer or texture will have the specified internal format, and will
   // be bound to the GL_COLOR_ATTACHMENT0 attachment in the framebuffer
   // object"
   this->BackLeftBuffer = this->FrontLeftBuffer = this->BackBuffer = this->FrontBuffer =
         static_cast<unsigned int>(GL_COLOR_ATTACHMENT0);

   // Save GL objects by static casting to standard C types. GL* types
   // are not allowed in VTK header files.
   QSize fboSize = fbo->size();
   this->Size[0] = fboSize.width();
   this->Size[1] = fboSize.height();
   this->NumberOfFrameBuffers = 1;
   this->FrameBufferObject       = static_cast<unsigned int>(fbo->handle());
   this->DepthRenderBufferObject = 0; // static_cast<unsigned int>(depthRenderBufferObject);
   this->TextureObjects[0]       = static_cast<unsigned int>(fbo->texture());
   this->OffScreenRendering = 1;
   this->OffScreenUseFrameBuffer = 1;
   this->Modified();
}
