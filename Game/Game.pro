TEMPLATE = app
TARGET = NYSSE

QT += core gui widgets network multimedia

CONFIG += c++14

SOURCES += \
    actoritem.cpp \
    beeritem.cpp \
    city.cpp \
    dialog.cpp \
    gamelogic.cpp \
    home.cpp \
    homeitem.cpp \
    main.cc \
    mainwindow.cpp \
    nysseitem.cpp \
    objectgenerator.cpp \
    passengeritem.cpp \
    pulsu.cpp \
    pulsuitem.cpp \
    statistics.cpp \

win32:CONFIG(release, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/release/ -lCourseLib
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/debug/ -lCourseLib
else:unix: LIBS += \
    -L$$OUT_PWD/../Course/CourseLib/ -lCourseLib

INCLUDEPATH += \
    $$PWD/../Course/CourseLib

DEPENDPATH += \
    $$PWD/../Course/CourseLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/libCourseLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/libCourseLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/release/CourseLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/debug/CourseLib.lib
else:unix: PRE_TARGETDEPS += \
    $$OUT_PWD/../Course/CourseLib/libCourseLib.a

HEADERS += \
    actoritem.hh \
    beeritem.hh \
    city.hh \
    dialog.hh \
    gamelogic.hh \
    home.hh \
    homeitem.hh \
    mainwindow.hh \
    nysseitem.hh \
    objectgenerator.hh \
    passengeritem.hh \
    pulsu.hh \
    pulsuitem.hh \
    statistics.hh

FORMS += \
    dialog.ui \
    mainwindow.ui

RESOURCES += \
    data.qrc \
