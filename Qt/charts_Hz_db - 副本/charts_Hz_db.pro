QT       += core gui charts axcontainer network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += core
QT += charts
QT += axcontainer
QT += network
QT += multimedia
QT += printsupport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    data_save/data_save.cpp \
    excel/excel.cpp \
    led/led.cpp \
    main.cpp \
    chart.cpp \
    pcm/pcm.cpp \
    qcustomplot/qcustomplot.cpp \
    search_null/search_null.cpp \
    test/test.cpp \
    wav/wav.cpp

HEADERS += \
    chart.h \
    data_save/data_save.h \
    excel/excel.h \
    led/led.h \
    pcm/pcm.h \
    qcustomplot/qcustomplot.h \
    search_null/search_null.h \
    test/test.h \
    wav/wav.h

FORMS += \
    chart.ui \
    data_save/data_save.ui \
    search_null/search_null.ui \
    test/test.ui

INCLUDEPATH += \
    F:\USST\Undergraduate\Senior2\Qt\charts_Hz_db\charts_Hz_db\clear \
    F:\USST\Undergraduate\Senior2\Qt\charts_Hz_db\charts_Hz_db\led \
    F:\USST\Undergraduate\Senior2\Qt\charts_Hz_db\charts_Hz_db\search_null \
    F:\USST\Undergraduate\Senior2\Qt\charts_Hz_db\charts_Hz_db\data_save \
    F:\USST\Undergraduate\Senior2\Qt\charts_Hz_db\charts_Hz_db\excel\
    F:\USST\Undergraduate\Senior2\Qt\charts_Hz_db\charts_Hz_db\test\
    F:\USST\Undergraduate\Senior2\Qt\charts_Hz_db\charts_Hz_db\pcm\
    F:\USST\Undergraduate\Senior2\Qt\charts_Hz_db\charts_Hz_db\wav


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
