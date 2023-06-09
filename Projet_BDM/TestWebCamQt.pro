#-------------------------------------------------
#
# Project created by QtCreator 2016-04-13T15:06:48
#
#-------------------------------------------------

#QT       += core gui

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = TestWebCamQt
#TEMPLATE = app


#SOURCES += main.cpp\
#        widget.cpp

#HEADERS  += widget.h

#FORMS    += widget.ui

#INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

#LIBS += -L$$(OPENCV_DIR)\lib \
#    -lopencv_core470 \
#    -lopencv_highgui470 \
#    -lopencv_imgproc470 \
#    -lopencv_imgcodecs470 \
#    -lopencv_videoio470 \
#    -lopencv_features2d470 \
#    -lopencv_calib3d470\
#    -lopencv_dnn470


QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WebCamQt
TEMPLATE = app


SOURCES += main.cpp\
        cam.cpp \
        gameWindow.cpp \
        handconfig.cpp \
        myglwidget.cpp \
        namedialog.cpp \
        starterwindow.cpp \
        state.cpp

HEADERS  += \
    cam.h \
    gameWindow.h \
    handconfig.h \
    myglwidget.h \
    namedialog.h \
    starterwindow.h \
    state.h

FORMS    += \
    gameWindow.ui \
    namedialog.ui \
    starterwindow.ui

    QMAKE_MACOSX_DEPLOYMENT_TARGET = 13.2.1

    INCLUDEPATH += /usr/local/include/opencv4

    LIBS += -L/usr/local/lib \
    -lopencv_core \
    -lopencv_highgui \
    -lopencv_imgproc \
    -lopencv_imgcodecs \
    -lopencv_videoio \
    -lopencv_features2d \
    -lopencv_calib3d \
    -lopencv_dnn \
    -framework OpenGL

RESOURCES += \
    ressource.qrc

