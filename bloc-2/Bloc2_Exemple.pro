TEMPLATE    = app
QT         += opengl

INCLUDEPATH +=  /usr/include/glm

FORMS += MyForm.ui

HEADERS += MyForm.h BL2GLWidget.h MyGLWidget.h

SOURCES += main.cpp MyForm.cpp \
        BL2GLWidget.cpp MyGLWidget.cpp

INCLUDEPATH += /home/ferran/Documentos/IDI/bloc-2/Model

SOURCES += /home/ferran/Documentos/IDI/bloc-2/Model/model.cpp

HEADERS += /home/ferran/Documentos/IDI/bloc-2/Model/model.h
