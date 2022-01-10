QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_statisticstest.cpp  \
        ../Game/statistics.cpp \


HEADERS += \
        ../Game/statistics.hh \
        ../CourseLib/interfaces/istatistics.hh

INCLUDEPATH += \
    $$PWD/../Course/CourseLib \
    $$PWD/../Game/

DEPENDPATH += \
    $$PWD/../Course/CourseLib \
    $$PWD/../Game/
