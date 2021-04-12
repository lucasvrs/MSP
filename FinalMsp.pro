QT       += core gui
QT       += xml
QT       += sql
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sql/sqlconnector.cpp \
    Txt/txtreader.cpp \
    Txt/txtwriter.cpp \
    Utils/geometrylib.cpp \
    Utils/loader.cpp \
    Widgets/ArithmeticGame/endscreen.cpp \
    Widgets/ArithmeticGame/kopfrechnenspiel.cpp \
    Widgets/ArithmeticGame/kopfrechnenstart.cpp \
    Widgets/ArithmeticGame/scorechart.cpp \
    Widgets/Calculator/calculator.cpp \
    Widgets/Calculator/calculatorwidget.cpp \
    Widgets/Calendar/Widgets/appointmentgroupbox.cpp \
    Widgets/Calendar/Widgets/calendarmonthgroupbox.cpp \
    Widgets/Calendar/Widgets/daydetailsbgwidget.cpp \
    Widgets/Calendar/Widgets/daydetailsgroupbox.cpp \
    Widgets/Calendar/Widgets/daygroupbox.cpp \
    Widgets/Calendar/Widgets/searchdialog.cpp \
    Widgets/Calendar/calendarwidget.cpp \
    Widgets/ColorPicker/Widgets/Edits/hexedit.cpp \
    Widgets/ColorPicker/Widgets/Edits/regexedit.cpp \
    Widgets/ColorPicker/Widgets/Sliders/responsiveslider.cpp \
    Widgets/ColorPicker/Widgets/Sliders/sliderwidget.cpp \
    Widgets/ColorPicker/Widgets/Spectrum/Scene/handleitem.cpp \
    Widgets/ColorPicker/Widgets/Spectrum/Scene/spectrumscene.cpp \
    Widgets/ColorPicker/Widgets/Spectrum/Utils/colorspectrum.cpp \
    Widgets/ColorPicker/Widgets/Spectrum/Widgets/colorspectrumwidget.cpp \
    Widgets/ColorPicker/Widgets/Spectrum/Widgets/spectrumpalettewidget.cpp \
    Widgets/ColorPicker/Widgets/Spectrum/Widgets/spectrumsview.cpp \
    Widgets/ColorPicker/Widgets/allsliderswidget.cpp \
    Widgets/ColorPicker/Widgets/colorpickermodiswidget.cpp \
    Widgets/ColorPicker/Widgets/hsvpickerwidget.cpp \
    Widgets/ColorPicker/Widgets/rgbpickerwidget.cpp \
    Widgets/ColorPicker/Widgets/slideeditconnectwidget.cpp \
    Widgets/ColorPicker/colorpickerwidget.cpp \
    Widgets/ContentsWidget/contentswidget.cpp \
    Widgets/ContentsWidget/headerwidget.cpp \
    Widgets/ContentsWidget/homewidget.cpp \
    Widgets/ContentsWidget/mainviewwidget.cpp \
    Widgets/Converter/converterwidget.cpp \
    Widgets/FormulaCollection/formelsammlung.cpp \
    Widgets/LiteratureEras/epochenscene.cpp \
    Widgets/LiteratureEras/erabutton.cpp \
    Widgets/LiteratureEras/eraview.cpp \
    Widgets/LiteratureEras/erawidget.cpp \
    Widgets/MatrixCalculator/entryedit.cpp \
    Widgets/MatrixCalculator/matrixrechner.cpp \
    Widgets/Navigation/navigationwidget.cpp \
    Widgets/Options/interfaceoptionswidget.cpp \
    Widgets/Options/optionswidget.cpp \
    Widgets/Pathfinding/Algorithms/a_star.cpp \
    Widgets/Pathfinding/Grid/node.cpp \
    Widgets/Pathfinding/Scene/delimiteritem.cpp \
    Widgets/Pathfinding/Scene/griditem.cpp \
    Widgets/Pathfinding/Scene/nodeitem.cpp \
    Widgets/Pathfinding/Scene/pathfindingscene.cpp \
    Widgets/Pathfinding/Scene/view.cpp \
    Widgets/Pathfinding/pathfindingguiwidget.cpp \
    Widgets/Pathfinding/pathfindinglogicoptionswidget.cpp \
    Widgets/Pathfinding/pathfindingoptionswidget.cpp \
    Widgets/Pathfinding/pathfindingwidget.cpp \
    Widgets/Raytracing/raytracingscene.cpp \
    Widgets/Raytracing/raytracingwidget.cpp \
    Widgets/ReactionTest/reaction.cpp \
    Widgets/SubjectWidgetCollection/subjectstartmenu.cpp \
    Widgets/Tiles/addpreviewdialog.cpp \
    Widgets/Tiles/addpreviewscene.cpp \
    Widgets/Tiles/addpreviewview.cpp \
    Widgets/Tiles/addtile.cpp \
    Widgets/Tiles/createcollectiondialog.cpp \
    Widgets/Tiles/previewtilefactory.cpp \
    Widgets/Tiles/previewtilescene.cpp \
    Widgets/Tiles/previewtilesview.cpp \
    Widgets/Tiles/sidemenutilescene.cpp \
    Widgets/Tiles/sidemenutilesview.cpp \
    Widgets/Tiles/tilefactory.cpp \
    Widgets/Tiles/tileitem.cpp \
    Widgets/Tiles/tilescene.cpp \
    Widgets/Tiles/tilesview.cpp \
    Widgets/Tiles/widgetfactory.cpp \
    Widgets/ToDoList/newentry.cpp \
    Widgets/ToDoList/todo.cpp \
    Widgets/ToDoList/todolist.cpp \
    Widgets/VocabularyTrainer/vokabeltrainer.cpp \
    Widgets/mspwidget.cpp \
    Xml/xmlreader.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Sql/sqlconnector.h \
    Txt/txtreader.h \
    Txt/txtwriter.h \
    Utils/constants.h \
    Utils/geometrylib.h \
    Utils/loader.h \
    Utils/msp.h \
    Utils/shapes2d.h \
    Utils/vector2d.h \
    Widgets/ArithmeticGame/const.h \
    Widgets/ArithmeticGame/endscreen.h \
    Widgets/ArithmeticGame/kopfrechnenspiel.h \
    Widgets/ArithmeticGame/kopfrechnenstart.h \
    Widgets/ArithmeticGame/scorechart.h \
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
    Widgets/ColorPicker/Utils/colorpickerconstants.h \
    Widgets/ColorPicker/Widgets/Edits/hexedit.h \
    Widgets/ColorPicker/Widgets/Edits/regexedit.h \
    Widgets/ColorPicker/Widgets/Sliders/responsiveslider.h \
    Widgets/ColorPicker/Widgets/Sliders/sliderwidget.h \
    Widgets/ColorPicker/Widgets/Spectrum/Scene/handleitem.h \
    Widgets/ColorPicker/Widgets/Spectrum/Scene/spectrumscene.h \
    Widgets/ColorPicker/Widgets/Spectrum/Utils/colorspectrum.h \
    Widgets/ColorPicker/Widgets/Spectrum/Utils/spectrumconstants.h \
    Widgets/ColorPicker/Widgets/Spectrum/Widgets/colorspectrumwidget.h \
    Widgets/ColorPicker/Widgets/Spectrum/Widgets/spectrumpalettewidget.h \
    Widgets/ColorPicker/Widgets/Spectrum/Widgets/spectrumsview.h \
    Widgets/ColorPicker/Widgets/allsliderswidget.h \
    Widgets/ColorPicker/Widgets/colorpickermodiswidget.h \
    Widgets/ColorPicker/Widgets/hsvpickerwidget.h \
    Widgets/ColorPicker/Widgets/rgbpickerwidget.h \
    Widgets/ColorPicker/Widgets/slideeditconnectwidget.h \
    Widgets/ColorPicker/colorpickerwidget.h \
    Widgets/ContentsWidget/contentswidget.h \
    Widgets/ContentsWidget/headerwidget.h \
    Widgets/ContentsWidget/homewidget.h \
    Widgets/ContentsWidget/mainviewwidget.h \
    Widgets/Converter/AreaConverter.h \
    Widgets/Converter/DataConverter.h \
    Widgets/Converter/LengthConverter.h \
    Widgets/Converter/MassConverter.h \
    Widgets/Converter/TimeConverter.h \
    Widgets/Converter/VolumeConverter.h \
    Widgets/Converter/converterwidget.h \
    Widgets/FormulaCollection/constants.h \
    Widgets/FormulaCollection/formelsammlung.h \
    Widgets/LiteratureEras/constants.h \
    Widgets/LiteratureEras/epochenscene.h \
    Widgets/LiteratureEras/erabutton.h \
    Widgets/LiteratureEras/eraview.h \
    Widgets/LiteratureEras/erawidget.h \
    Widgets/MatrixCalculator/Matrix.h \
    Widgets/MatrixCalculator/entryedit.h \
    Widgets/MatrixCalculator/matrixrechner.h \
    Widgets/Navigation/navigationwidget.h \
    Widgets/Options/interfaceoptionswidget.h \
    Widgets/Options/optionswidget.h \
    Widgets/Pathfinding/Algorithms/a_star.h \
    Widgets/Pathfinding/Grid/node.h \
    Widgets/Pathfinding/Scene/delimiteritem.h \
    Widgets/Pathfinding/Scene/griditem.h \
    Widgets/Pathfinding/Scene/nodeitem.h \
    Widgets/Pathfinding/Scene/pathfindingscene.h \
    Widgets/Pathfinding/Scene/view.h \
    Widgets/Pathfinding/Utils/constants.h \
    Widgets/Pathfinding/Utils/utils.h \
    Widgets/Pathfinding/pathfindingguiwidget.h \
    Widgets/Pathfinding/pathfindinglogicoptionswidget.h \
    Widgets/Pathfinding/pathfindingoptionswidget.h \
    Widgets/Pathfinding/pathfindingwidget.h \
    Widgets/Raytracing/Utils/constants.h \
    Widgets/Raytracing/Utils/utils.h \
    Widgets/Raytracing/raytracingscene.h \
    Widgets/Raytracing/raytracingwidget.h \
    Widgets/ReactionTest/reaction.h \
    Widgets/SubjectWidgetCollection/subjectstartmenu.h \
    Widgets/Tiles/addpreviewdialog.h \
    Widgets/Tiles/addpreviewscene.h \
    Widgets/Tiles/addpreviewview.h \
    Widgets/Tiles/addtile.h \
    Widgets/Tiles/createcollectiondialog.h \
    Widgets/Tiles/previewtilefactory.h \
    Widgets/Tiles/previewtilescene.h \
    Widgets/Tiles/previewtilesview.h \
    Widgets/Tiles/sidemenutilescene.h \
    Widgets/Tiles/sidemenutilesview.h \
    Widgets/Tiles/tileconstants.h \
    Widgets/Tiles/tilefactory.h \
    Widgets/Tiles/tileitem.h \
    Widgets/Tiles/tilescene.h \
    Widgets/Tiles/tilesview.h \
    Widgets/Tiles/widgetfactory.h \
    Widgets/ToDoList/constants.h \
    Widgets/ToDoList/newentry.h \
    Widgets/ToDoList/todo.h \
    Widgets/ToDoList/todolist.h \
    Widgets/VocabularyTrainer/vokabeltrainer.h \
    Widgets/mspwidget.h \
    Xml/xmlconstants.h \
    Xml/xmlreader.h \
    Xml/xmlwriter.h \
    mainwindow.h

FORMS += \
    Widgets/ArithmeticGame/endscreen.ui \
    Widgets/ArithmeticGame/kopfrechnenspiel.ui \
    Widgets/ArithmeticGame/kopfrechnenstart.ui \
    Widgets/ArithmeticGame/scorechart.ui \
    Widgets/FormulaCollection/formelsammlung.ui \
    Widgets/MatrixCalculator/matrixrechner.ui \
    Widgets/ReactionTest/reaction.ui \
    Widgets/ToDoList/newentry.ui \
    Widgets/ToDoList/todolist.ui \
    Widgets/VocabularyTrainer/vokabeltrainer.ui \
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
    Styling/darkmode.qss \
    Styling/lightmode.qss \
    Widgets/ArithmeticGame/KopfrechnenScore \
    Widgets/FormulaCollection/Formel.xml \
    Widgets/LiteratureEras/eras.xml \
    Widgets/ToDoList/ToDo.xml \
    Widgets/VocabularyTrainer/Vokabeln.db
