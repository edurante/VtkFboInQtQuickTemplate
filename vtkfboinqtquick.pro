TEMPLATE = app

QT += qml quick multimedia
CONFIG += c++11

SOURCES += main.cpp \
    QVTKFramebufferObjectItem.cpp \
    vtkinternalopenglrenderwindow.cpp

HEADERS += \
    QVTKFramebufferObjectItem.h \
    vtkinternalopenglrenderwindow.h

RESOURCES += qml.qrc

OTHER_FILES = main.qml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

android {
    equals(ANDROID_TARGET_ARCH, armeabi-v7a) {
        INCLUDEPATH += /home/max-heinrich/Hacking/vtk/build_android/CMakeExternals/Install/vtk-android/include/vtk-7.0
        VTKLIBS = /home/max-heinrich/Hacking/vtk/build_android/CMakeExternals/Install/vtk-android/lib
    }

    # Linker Flags
    QMAKE_LFLAGS += \

    LIBS += \
    -L/home/max-heinrich/Android/Ndk/platforms/android-21/arch-arm/usr/lib \
    -landroid \
    -llog \
    -lm \
    -lEGL \
    $$VTKLIBS/libvtklibxml2-7.0.a \
    $$VTKLIBS/libvtkParallelCore-7.0.a \
    $$VTKLIBS/libvtkIOGeometry-7.0.a \
    $$VTKLIBS/libvtkIOInfovis-7.0.a \
    $$VTKLIBS/libvtkIOPLY-7.0.a \
    $$VTKLIBS/libvtkIOXML-7.0.a \
    $$VTKLIBS/libvtkIOXMLParser-7.0.a \
    $$VTKLIBS/libvtkInfovisCore-7.0.a \
    $$VTKLIBS/libvtkexpat-7.0.a \
    $$VTKLIBS/libvtkRenderingFreeType-7.0.a \
    $$VTKLIBS/libvtkfreetype-7.0.a \
    $$VTKLIBS/libvtkRenderingOpenGL2-7.0.a \
    $$VTKLIBS/libvtkRenderingCore-7.0.a \
    $$VTKLIBS/libvtkFiltersSources-7.0.a \
    $$VTKLIBS/libvtkFiltersExtraction-7.0.a \
    $$VTKLIBS/libvtkFiltersGeneral-7.0.a \
    $$VTKLIBS/libvtkCommonComputationalGeometry-7.0.a \
    $$VTKLIBS/libvtkImagingFourier-7.0.a \
    $$VTKLIBS/libvtkImagingCore-7.0.a \
    $$VTKLIBS/libvtkalglib-7.0.a \
    $$VTKLIBS/libvtkCommonColor-7.0.a \
    $$VTKLIBS/libvtkFiltersCore-7.0.a \
    $$VTKLIBS/libvtkCommonExecutionModel-7.0.a \
    $$VTKLIBS/libvtkCommonDataModel-7.0.a \
    $$VTKLIBS/libvtkCommonMisc-7.0.a \
    $$VTKLIBS/libvtkCommonTransforms-7.0.a \
    $$VTKLIBS/libvtkCommonMath-7.0.a \
    $$VTKLIBS/libvtkCommonCore-7.0.a \
    $$VTKLIBS/libvtksys-7.0.a \
    $$VTKLIBS/libvtkCommonSystem-7.0.a \
    $$VTKLIBS/libvtkInteractionStyle-7.0.a \
    $$VTKLIBS/libvtkFiltersStatistics-7.0.a \
    $$VTKLIBS/libvtkImagingFourier-7.0.a \
    $$VTKLIBS/libvtkImagingCore-7.0.a \
    $$VTKLIBS/libvtkalglib-7.0.a \
    $$VTKLIBS/libvtkCommonColor-7.0.a \
    $$VTKLIBS/libvtkFiltersGeometry-7.0.a \
    $$VTKLIBS/libvtkImagingHybrid-7.0.a \
    $$VTKLIBS/libvtkIOImage-7.0.a \
    $$VTKLIBS/libvtkDICOMParser-7.0.a \
    $$VTKLIBS/libvtkIOCore-7.0.a \
    $$VTKLIBS/libvtkzlib-7.0.a \
    $$VTKLIBS/libvtkmetaio-7.0.a \
    $$VTKLIBS/libvtkjpeg-7.0.a \
    $$VTKLIBS/libvtkpng-7.0.a \
    $$VTKLIBS/libvtktiff-7.0.a \
    $$VTKLIBS/libvtkglew-7.0.a \
    -ldl

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

DISTFILES += \
    $$ANDROID_PACKAGE_SOURCE_DIR/AndroidManifest.xml \
    $$ANDROID_PACKAGE_SOURCE_DIR/gradle/wrapper/gradle-wrapper.jar \
    $$ANDROID_PACKAGE_SOURCE_DIR/gradlew \
    $$ANDROID_PACKAGE_SOURCE_DIR/res/values/libs.xml \
    $$ANDROID_PACKAGE_SOURCE_DIR/build.gradle \
    $$ANDROID_PACKAGE_SOURCE_DIR/gradle/wrapper/gradle-wrapper.properties \
    $$ANDROID_PACKAGE_SOURCE_DIR/gradlew.bat
}


linux:!android {
    VTK_PATH = /opt/vtk

    INCLUDEPATH += $$VTK_PATH/include/vtk-7.0

    LIBS += \
    $$VTK_PATH/lib/libvtkCommonCore-7.0.so \
    $$VTK_PATH/lib/libvtkRenderingCore-7.0.so \
    $$VTK_PATH/lib/libvtkRenderingOpenGL2-7.0.so \
    $$VTK_PATH/lib/libvtkCommonExecutionModel-7.0.so \
    $$VTK_PATH/lib/libvtkFiltersSources-7.0.so

}

DISTFILES += \
    android-sources/AndroidManifest.xml \
    android-sources/gradle/wrapper/gradle-wrapper.jar \
    android-sources/gradlew \
    android-sources/res/values/libs.xml \
    android-sources/build.gradle \
    android-sources/gradle/wrapper/gradle-wrapper.properties \
    android-sources/gradlew.bat
