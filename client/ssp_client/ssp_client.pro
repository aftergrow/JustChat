QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    message_define.pb.cc \
    message_info_base.pb.cc \
    photo_info_base.pb.cc \
    relation_info_base.pb.cc \
    user_info_base.pb.cc

HEADERS += \
    mainwindow.h \
    message_define.pb.h \
    message_info_base.pb.h \
    photo_info_base.pb.h \
    relation_info_base.pb.h \
    user_info_base.pb.h

FORMS += \
    mainwindow.ui

#CONFIG += lrelease
#根据 QM_FILES_RESOURCE_PREFIX 设置，将 lrelease 生成的翻译文件嵌入可执行文件中。此外还需要配置 lrelease。默认不配置。
#CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/protobuf/lib/ -llibprotobuf.dll
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/protobuf/lib/ -llibprotobuf.dlld

LIBS += -LD:\Haizei\ssp_new\ssp_client\protobuf\lib -lprotobuf
LIBS += -LD:\Haizei\ssp_new\ssp_client\protobuf\lib -lws2_32

INCLUDEPATH += $$PWD/protobuf/include
INCLUDEPATH += D:\ToolsAndLib\protobuf_version\protobuf-3.15.0\src
DEPENDPATH += $$PWD/protobuf/include

TRANSLATIONS += \
    ssp_client_zh_CN.ts
