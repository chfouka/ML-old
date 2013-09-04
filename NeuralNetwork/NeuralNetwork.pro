TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += \
    cross_numUnits.cpp \
    test_exam.cpp \
    test_monk.cpp \
    ms_units.cpp \
    ms_etas.cpp \
    ms_etal.cpp \
    ms_lamda.cpp \
    ms_alpha.cpp \
    simulator.cpp \
    splitter.cpp

HEADERS += \
    Dataset.h \
    Pattern.h \
    outputlayer.h \
    Unit.h \
    sigmoidalunit.h \
    linearunit.h \
    hiddenlayer.h \
    network.h

OTHER_FILES += \
    Sconstruct \
    validation.py \
    CMakeLists.txt

QMAKE_CXXFLAGS += -std=c++0x
