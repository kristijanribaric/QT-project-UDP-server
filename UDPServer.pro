QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += "C:/Program Files/OpenSSL-Win64/include"

LIBS += "C:/Program Files/OpenSSL-Win64/lib/libcrypto.lib"
LIBS += "C:/Program Files/OpenSSL-Win64/lib/libssl.lib"

SOURCES += \
    cipher.cpp \
    main.cpp \
    udpserver.cpp

HEADERS += \
    cipher.h \
    udpserver.h

FORMS += \
    udpserver.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_CXXFLAGS += -std=gnu++11
