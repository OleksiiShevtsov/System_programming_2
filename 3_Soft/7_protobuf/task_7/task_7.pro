TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/proto_message/lib/ -llibprotobuf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/proto_message/lib/ -llibprotobufd

INCLUDEPATH += $$PWD/proto_message/include
DEPENDPATH += $$PWD/proto_message/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/proto_message/lib/liblibprotobuf.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/proto_message/lib/liblibprotobufd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/proto_message/lib/libprotobuf.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/proto_message/lib/libprotobufd.lib

SOURCES += \
        main.cpp \
        proto_message/user_info.pb.cc

DISTFILES += \
    proto_message/user_info.proto

HEADERS += \
    proto_message/user_info.pb.h
<<<<<<< Updated upstream

LIBS += -lprotobuf

=======
>>>>>>> Stashed changes
