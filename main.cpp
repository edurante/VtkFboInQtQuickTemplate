#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)

#include "QVTKFramebufferObjectItem.h"

#include "vtkNew.h"
#include <vtkActor.h>
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkRendererCollection.h>
#include <vtkCamera.h>
#include <vtkProperty.h>

#include <QGuiApplication>
#include <QQuickView>
#include <QList>

int main(int argc, char **argv)
{
   QGuiApplication app(argc, argv);

   qmlRegisterType<QVTKFrameBufferObjectItem>("VtkQuick", 1, 0, "VtkRenderWindow");

   QQuickView view;
   view.setSource(QUrl("qrc:///main.qml"));
   QList<QVTKFrameBufferObjectItem*> vtkItems = view.rootObject()->findChildren<QVTKFrameBufferObjectItem*>();

   // For demonstration: Add a cone to the scene of each QVTKFrameBufferObjectItem
   Q_FOREACH(QVTKFrameBufferObjectItem *vtkItem, vtkItems)
   {
      vtkGenericOpenGLRenderWindow *r_win = vtkItem->GetRenderWindow();

      vtkSmartPointer<vtkConeSource> cone = vtkSmartPointer<vtkConeSource>::New();
      //cone->SetHeight(3.0);
      //cone->SetRadius(1.0);
      cone->SetResolution(100);

      vtkSmartPointer<vtkPolyDataMapper> coneMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
      coneMapper->SetInputConnection(cone->GetOutputPort());

      vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
      coneActor->SetMapper(coneMapper);

      vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
      ren1->AddActor(coneActor);

      r_win->AddRenderer(ren1);
   }

   view.setResizeMode( QQuickView::SizeRootObjectToView );
   view.show();

   return app.exec();
}
