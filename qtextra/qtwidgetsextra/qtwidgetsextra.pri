# Input
HEADERS += \
    $$PWD/src/*.h \
    $$files($$PWD/src/utils/*.h) \
    $$files($$PWD/src/widgets/*.h)


SOURCES += \
    $$files($$PWD/src/utils/*.cpp) \
    $$files($$PWD/src/widgets/*.cpp)
