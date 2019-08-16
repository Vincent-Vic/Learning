QT += widgets gui
QT += network
CONFIG += qaxcontainer

HEADERS += \
    MainServer.h \
    BackGround.h \
    MyButton.h \
    MyTextBrowser.h \
    Main.h \
    MyLabel.h \
    ClientSocket.h

SOURCES += \
    MainServer.cpp \
    BackGround.cpp \
    MyButton.cpp \
    MyTextBrowser.cpp \
    Main.cpp \
    MyLabel.cpp \
    ClientSocket.cpp

RESOURCES += \
    src.qrc
RC_ICONS = "V.ico"
