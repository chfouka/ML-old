TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += \
    test.cpp

HEADERS += \
    Dataset.h \
    Pattern.h \
    outputlayer.h \
    Unit.h \
    sigmoidalunit.h \
    linearunit.h \
    hiddenlayer.h \
    network.h

OTHER_FILES +=

QMAKE_CXXFLAGS += -std=c++0x
