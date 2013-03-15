TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    Dataset.cpp \
    Pattern.cpp \
    outputlayer.cpp \
    Unit.cpp \
    linearunit.cpp \
    sigmoidalunit.cpp \
    hiddenlayer.cpp \
    network.cpp \
    prova.cpp

HEADERS += \
    Dataset.h \
    Pattern.h \
    outputlayer.h \
    util.h \
    Unit.h \
    sigmoidalunit.h \
    linearunit.h \
    hiddenlayer.h \
    network.h \
    prova.h

OTHER_FILES +=

QMAKE_CXXFLAGS += -std=c++0x
