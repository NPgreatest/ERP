QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    equation.cpp \
    main.cpp \
    mainwindow.cpp \
    mps.cpp \
    part.cpp \
    part_check.cpp \
    request.cpp \
    store.cpp \
    timeline.cpp

HEADERS += \
    equation.h \
    mainwindow.h \
    mps.h \
    part.h \
    part_check.h \
    request.h \
    store.h \
    timeline.h

FORMS += \
    equation.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    other.qrc

DISTFILES += \
    advanced/advanced.qss
