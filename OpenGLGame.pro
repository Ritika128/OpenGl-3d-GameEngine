TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += OGL3D/Include
INCLUDEPATH += OGL3D/Vendor/glad/include




unix:!macx {

}
win32: {
    SOURCES += \
    OGL3D/source/OGL3D/Game/Win32/CWin32Game.cpp \
    OGL3D/source/OGL3D/Graphics/Win32/CWin32GraphicsEngine.cpp \
    OGL3D/source/OGL3D/Window/CWin32Window.cpp\
    OGL3D/vendor/glad/src/glad_wgl.c

    HEADERS+=\
        OGL3D/vendor/glad/include/glad/glad_wgl.h
}
macx: {
    SOURCES += \
        OGL3D/source/OGL3D/Game/Cocoa/CCocoaGame.mm \
        OGL3D/source/OGL3D/Graphics/Cocoa/CCocoaGraphicsEngine.mm \
        OGL3D/source/OGL3D/Window/CCocoaWindow.mm\
}


SOURCES += \
    Game/main.cpp \
    OGL3D/source/OGL3D/Game/OGame.cpp \
    OGL3D/source/OGL3D/Graphics/OGraphicsEngine.cpp \
    OGL3D/vendor/glad/src/glad.c

HEADERS += \
    OGL3D/include/OGL3D/Game/OGame.h \
    OGL3D/include/OGL3D/Graphics/OGraphicsEngine.h \
    OGL3D/include/OGL3D/Math/OColor.h \
    OGL3D/include/OGL3D/OPrerequisites.h \
    OGL3D/include/OGL3D/Window/OWindow.h \
    OGL3D/vendor/glad/include/KHR/khrplatform.h \
    OGL3D/vendor/glad/include/glad/glad.h





macx {
         LIBS += -framework Cocoa -framework QuartzCore
         LIBS += -framework AppKit -framework OpenGL -framework Quartz
}

unix:!macx {
}
