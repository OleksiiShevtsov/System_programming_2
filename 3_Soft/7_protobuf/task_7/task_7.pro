TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        proto_message/user_info.pb.cc

DISTFILES += \
    proto_message/user_info.proto

HEADERS += \
    proto_message/user_info.pb.h

LIBS += -lprotobuf
