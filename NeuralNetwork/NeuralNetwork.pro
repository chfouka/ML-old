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
    utile.cpp

HEADERS += \
    Dataset.h \
    Pattern.h \
    outputlayer.h \
    Unit.h \
    sigmoidalunit.h \
    linearunit.h \
    hiddenlayer.h \
    network.h \
    util.h

OTHER_FILES +=

QMAKE_CXXFLAGS += -std=c++0x
