QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../databasesystem.cpp \
    ../people.cpp \
    ../ticket.cpp \
    ../trainticketsystem.cpp \
    main.cpp \
    trainticketsystemserver.cpp


HEADERS += \
    ../databasesystem.h \
    ../people.h \
    ../ticket.h \
    ../trainticketsystem.h \
    trainticketsystemserver.h

FORMS += \
    trainticketsystemserver.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
