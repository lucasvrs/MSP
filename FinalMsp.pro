QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Utils/loader.cpp \
    Widgets/Calculator/calculator.cpp \
    Widgets/Calculator/calculatorwidget.cpp \
    Widgets/Calendar/Widgets/appointmentgroupbox.cpp \
    Widgets/Calendar/Widgets/calendarmonthgroupbox.cpp \
    Widgets/Calendar/Widgets/daydetailsbgwidget.cpp \
    Widgets/Calendar/Widgets/daydetailsgroupbox.cpp \
    Widgets/Calendar/Widgets/daygroupbox.cpp \
    Widgets/Calendar/Widgets/searchdialog.cpp \
    Widgets/Calendar/calendarwidget.cpp \
    Widgets/ContentsWidget/contentswidget.cpp \
    Widgets/ContentsWidget/headerwidget.cpp \
    Widgets/ContentsWidget/homewidget.cpp \
    Widgets/ContentsWidget/mainviewwidget.cpp \
    Widgets/Navigation/navigationwidget.cpp \
    Widgets/Options/interfaceoptionswidget.cpp \
    Widgets/Options/optionswidget.cpp \
    Widgets/SubjectWidgetCollection/relatedappssidemenu.cpp \
    Widgets/SubjectWidgetCollection/subjectstartmenu.cpp \
    Widgets/Tiles/addtile.cpp \
    Widgets/Tiles/previewtilefactory.cpp \
    Widgets/Tiles/previewtilescene.cpp \
    Widgets/Tiles/previewtilesview.cpp \
    Widgets/Tiles/tilefactory.cpp \
    Widgets/Tiles/tileitem.cpp \
    Widgets/Tiles/tilescene.cpp \
    Widgets/Tiles/tilesview.cpp \
    Widgets/Tiles/widgetfactory.cpp \
    Widgets/mspwidget.cpp \
    Xml/xmlreader.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Utils/constants.h \
    Utils/loader.h \
    Utils/msp.h \
    Widgets/Calculator/calculator.h \
    Widgets/Calculator/calculatorwidget.h \
    Widgets/Calendar/Utils/calendarconstants.h \
    Widgets/Calendar/Widgets/appointmentgroupbox.h \
    Widgets/Calendar/Widgets/calendarmonthgroupbox.h \
    Widgets/Calendar/Widgets/daydetailsbgwidget.h \
    Widgets/Calendar/Widgets/daydetailsgroupbox.h \
    Widgets/Calendar/Widgets/daygroupbox.h \
    Widgets/Calendar/Widgets/searchdialog.h \
    Widgets/Calendar/calendarwidget.h \
    Widgets/ContentsWidget/contentswidget.h \
    Widgets/ContentsWidget/headerwidget.h \
    Widgets/ContentsWidget/homewidget.h \
    Widgets/ContentsWidget/mainviewwidget.h \
    Widgets/Navigation/navigationwidget.h \
    Widgets/Options/interfaceoptionswidget.h \
    Widgets/Options/optionswidget.h \
    Widgets/SubjectWidgetCollection/relatedappssidemenu.h \
    Widgets/SubjectWidgetCollection/subjectstartmenu.h \
    Widgets/Tiles/addtile.h \
    Widgets/Tiles/previewtilefactory.h \
    Widgets/Tiles/previewtilescene.h \
    Widgets/Tiles/previewtilesview.h \
    Widgets/Tiles/tileconstants.h \
    Widgets/Tiles/tilefactory.h \
    Widgets/Tiles/tileitem.h \
    Widgets/Tiles/tilescene.h \
    Widgets/Tiles/tilesview.h \
    Widgets/Tiles/widgetfactory.h \
    Widgets/mspwidget.h \
    Xml/xmlconstants.h \
    Xml/xmlreader.h \
    Xml/xmlwriter.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Config/appointments.xml \
    Config/apppreviews.xml \
    Config/optionconfig.xml \
    Config/tileconfig.xml \
    Styling/lightmode.qss
