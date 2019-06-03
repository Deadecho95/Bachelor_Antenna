
INCLUDEPATH += $$PWD/..

# Path to default implementation of the XF port
DEFAULT_IMPL_PATH = $$PWD/../default
# Path to qt based IDF implementation
IDF_QT_PATH = $$PWD/../idf-qt

DEFAULT_IMPL_SOURCES += \
    $${DEFAULT_IMPL_PATH}/xf-default.cpp \
    $${DEFAULT_IMPL_PATH}/timeoutmanager-default.cpp \
    $${DEFAULT_IMPL_PATH}/dispatcher-active.cpp

DEFAULT_IMPL_HEADERS += \
    $${DEFAULT_IMPL_PATH}/timeoutmanager-default.h \
    $${DEFAULT_IMPL_PATH}/dispatcher-active.h

SOURCES += \
    $${DEFAULT_IMPL_SOURCES}$$ \
    $${IDF_QT_PATH}/xf.cpp \
    $${IDF_QT_PATH}/port-functions.cpp \
    $${IDF_QT_PATH}/mutex.cpp \
    $${IDF_QT_PATH}/thread.cpp \
    $${IDF_QT_PATH}/eventqueue.cpp \
    $$PWD/resourcefactory.cpp

HEADERS += \
    $${DEFAULT_IMPL_HEADERS}$$ \
    $${IDF_QT_PATH}/mutex.h\
    $${IDF_QT_PATH}/thread.h\
    $${IDF_QT_PATH}/eventqueue.h \
    $$PWD/resourcefactory.h
