#include "converterwidget.h"
#include "LengthConverter.h"
#include "TimeConverter.h"
#include "MassConverter.h"
#include "AreaConverter.h"
#include "VolumeConverter.h"
#include "DataConverter.h"
#include <QList>
#include <QGridLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QRegExpValidator>

using namespace lengthconv;
using namespace timeconv;
using namespace massconv;
using namespace areaconv;
using namespace volumeconv;
using namespace dataconv;

ConverterWidget::ConverterWidget(QWidget *parent) : QWidget(parent)
{
    QGridLayout* layout = new QGridLayout(this);
    QList<QString> units = { "Länge", "Masse", "Zeit", "Fläche", "Volumen", "Datengröße" };
    QSpacerItem* hSpacerL = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* hSpacerR = new QSpacerItem(50, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* vSpacerT = new QSpacerItem(10, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem* vSpacerB = new QSpacerItem(10, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);
    m_unitBox = new QComboBox;
    m_unitBox->addItems(units);
    m_fromBox = new QComboBox;
    m_toBox = new QComboBox;
    m_fromEdit = new QLineEdit;
    m_toEdit = new QLineEdit;
    m_fromEdit->setValidator(new QRegExpValidator(QRegExp("[0-9.]{1,}")));
    m_toEdit->setValidator(new QRegExpValidator(QRegExp("[0-9.]{1,}")));
    layout->addItem(vSpacerT, 0, 1);
    layout->addItem(hSpacerL, 1, 0);
    layout->addWidget(m_unitBox, 1, 1);
    layout->addWidget(m_fromBox, 2, 1);
    layout->addWidget(m_toBox, 2, 2);
    layout->addWidget(m_fromEdit, 3, 1);
    layout->addWidget(m_toEdit, 3, 2);
    layout->addItem(vSpacerB, 4, 1);
    layout->addItem(hSpacerR, 1, 3);
    connect(m_toEdit, &QLineEdit::textChanged, [this](const QString&)
    {
        convertFrom();
    });
    connect(m_fromEdit, &QLineEdit::textChanged, [this](const QString&)
    {
        convertTo();
    });
    connect(m_toBox, &QComboBox::currentTextChanged, [this](const QString&)
    {
        convertTo();
    });
    connect(m_fromBox, &QComboBox::currentTextChanged, [this](const QString&)
    {
        convertFrom();
    });
    connect(m_unitBox, &QComboBox::currentTextChanged, [this](const QString&)
    {
        changeUnit();
        convertTo();
    });
    changeUnit();
}

void ConverterWidget::convertFrom()
{
    m_fromEdit->setText(QString::number(convert(m_toEdit->text().toDouble(), m_toBox->currentText(),
                                                m_fromBox->currentText(), m_unitBox->currentText())));
}

void ConverterWidget::convertTo()
{
    m_toEdit->setText(QString::number(convert(m_fromEdit->text().toDouble(), m_fromBox->currentText(),
                                              m_toBox->currentText(), m_unitBox->currentText())));
}

//SLOTS******************************************************************
double ConverterWidget::convert(double sourceValue, QString sourceUnit, QString targetUnit, QString selectedUnit)
{
    if (selectedUnit == "Länge") {

        LengthConverter<double> lengthConverter(sourceValue);

        if (sourceUnit == "mm") {
            if (targetUnit == "m") {
                return lengthConverter.mmToM();
            } else if (targetUnit == "km") {
                return lengthConverter.mmToKM();
            } else if (targetUnit == "cm") {
                return lengthConverter.mmToCm();
            }
        }

        if (sourceUnit == "cm") {
            if (targetUnit == "m") {
                return lengthConverter.cmToM();
            } else if (targetUnit == "km") {
                return lengthConverter.cmToKM();
            } else if (targetUnit == "mm") {
                return lengthConverter.cmToMM();
            }
        }

        if (sourceUnit == "m") {
            if (targetUnit == "cm") {
                return lengthConverter.mToCM();
            } else if (targetUnit == "km") {
                return lengthConverter.mToKM();
            } else if (targetUnit == "mm") {
                return lengthConverter.mToMM();
            }
        }

        if (sourceUnit == "km") {
            if (targetUnit == "cm") {
                return lengthConverter.kmToCM();
            } else if (targetUnit == "m") {
                return lengthConverter.kmToM();
            } else if (targetUnit == "mm") {
                return lengthConverter.kmToMM();
            }
        }
    }

    if (selectedUnit == "Zeit") {

        TimeConverter<double> timeConverter(sourceValue);

        if (sourceUnit == "ms") {
            if (targetUnit == "s") {
                return timeConverter.msecsToSecs();
            } else if (targetUnit == "min") {
                return timeConverter.msecsToMin();
            } else if (targetUnit == "h") {
                return timeConverter.msecsToHour();
            }
        }

        if (sourceUnit == "s") {
            if (targetUnit == "ms") {
                return timeConverter.secsToMsecs();
            } else if (targetUnit == "min") {
                return timeConverter.secsToMin();
            } else if (targetUnit == "h") {
                return timeConverter.secsToHour();
            }
        }

        if (sourceUnit == "min") {
            if (targetUnit == "ms") {
                return timeConverter.minToMsecs();
            } else if (targetUnit == "s") {
                return timeConverter.minToSecs();
            } else if (targetUnit == "h") {
                return timeConverter.minToHour();
            }
        }

        if (sourceUnit == "h") {
            if (targetUnit == "ms") {
                return timeConverter.hourToMsecs();
            } else if (targetUnit == "s") {
                return timeConverter.hourToSecs();
            } else if (targetUnit == "min") {
                return timeConverter.hourToMin();
            }
        }
    }

    if (selectedUnit == "Masse") {

        MassConverter<double> massConverter(sourceValue);

        if (sourceUnit == "mg") {
            if (targetUnit == "g") {
                return massConverter.mgToG();
            } else if (targetUnit == "kg") {
                return massConverter.mgToKG();
            }
        }

        if (sourceUnit == "g") {
            if (targetUnit == "mg") {
                return massConverter.gToKG();
            } else if (targetUnit == "kg") {
                return massConverter.gToMG();
            }
        }

        if (sourceUnit == "kg") {
            if (targetUnit == "mg") {
                return massConverter.kgToMG();
            } else if (targetUnit == "g") {
                return massConverter.kgToG();
            }
        }
    }

    if (selectedUnit == "Fläche") {

        AreaConverter<double> areaConverter(sourceValue);

        if (sourceUnit == "cm²") {
            if (targetUnit == "m²") {
                return areaConverter.sqrCMToSQRM();
            } else if (targetUnit == "km²") {
                return areaConverter.sqrCMToSQRKM();
            }
        }

        if (sourceUnit == "m²") {
            if (targetUnit == "cm²") {
                return areaConverter.sqrMToSQRCM();
            } else if (targetUnit == "km²") {
                return areaConverter.sqrMToSQRKM();
            }
        }

        if (sourceUnit == "km²") {
            if (targetUnit == "cm²") {
                return areaConverter.sqrKMToSQRCM();
            } else if (targetUnit == "m²") {
                return areaConverter.sqrKMToSQRM();
            }
        }
    }

    if (selectedUnit == "Volumen") {

        VolumeConverter<double> volumeConverter(sourceValue);

        if (sourceUnit == "ml") {
            if (targetUnit == "cl") {
                return volumeConverter.mlToCL();
            } else if (targetUnit == "dl") {
                return volumeConverter.mlToDL();
            } else if (targetUnit == "l") {
                return volumeConverter.mlToL();
            }
        }

        if (sourceUnit == "l") {
            if (targetUnit == "cl") {
                return volumeConverter.lToCL();
            } else if (targetUnit == "dl") {
                return volumeConverter.lToDL();
            } else if (targetUnit == "ml") {
                return volumeConverter.lToML();
            }
        }

        if (sourceUnit == "cl") {
            if (targetUnit == "l") {
                return volumeConverter.clToL();
            } else if (targetUnit == "dl") {
                return volumeConverter.clToDL();
            } else if (targetUnit == "ml") {
                return volumeConverter.clToML();
            }
        }

        if (sourceUnit == "dl") {
            if (targetUnit == "l") {
                return volumeConverter.dlToL();
            } else if (targetUnit == "cl") {
                return volumeConverter.dlToCL();
            } else if (targetUnit == "ml") {
                return volumeConverter.dlToML();
            }
        }
    }

    if (selectedUnit == "Datengröße") {

        DataConverter<double> dataConverter(sourceValue);

        if (sourceUnit == "KB") {
            if (targetUnit == "GB") {
                return dataConverter.kbToGB();
            } else if (targetUnit == "TB") {
                return dataConverter.kbToTB();
            } else if (targetUnit == "MB") {
                return dataConverter.kbToMB();
            }
        }

        if (sourceUnit == "MB") {
            if (targetUnit == "GB") {
                return dataConverter.mbToGB();
            } else if (targetUnit == "TB") {
                return dataConverter.mbToTB();
            } else if (targetUnit == "KB") {
                return dataConverter.mbToKB();
            }
        }


        if (sourceUnit == "GB") {
            if (targetUnit == "MB") {
                return dataConverter.gbToMB();
            } else if (targetUnit == "TB") {
                return dataConverter.gbToTB();
            } else if (targetUnit == "KB") {
                return dataConverter.gbToKB();
            }
        }

        if (sourceUnit == "TB") {
            if (targetUnit == "MB") {
                return dataConverter.tbToMB();
            } else if (targetUnit == "GB") {
                return dataConverter.tbToGB();
            } else if (targetUnit == "KB") {
                return dataConverter.tbToKB();
            }
        }
    }


    return sourceValue;
}

/*!
 * \brief changes unit in combobox
 */
void ConverterWidget::changeUnit()
{
    QString selectedUnit = m_unitBox->currentText();

    if (selectedUnit == "Länge") {
        // remove previous items from comboBox
        m_fromBox->clear();
        m_toBox->clear();

        QList<QString> length = { "mm", "cm", "m", "km" };

        // add new items
        m_fromBox->addItems(length);
        m_toBox->addItems(length);
    }

    if (selectedUnit == "Masse") {
        m_fromBox->clear();
        m_toBox->clear();

        QList<QString> mass = { "mg", "g", "kg" };

        m_fromBox->addItems(mass);
        m_toBox->addItems(mass);
    }

    if (selectedUnit == "Zeit") {
        m_fromBox->clear();
        m_toBox->clear();

        QList<QString> time = { "ms", "s", "min", "h" };

        m_fromBox->addItems(time);
        m_toBox->addItems(time);
    }

    if (selectedUnit == "Fläche") {
        m_fromBox->clear();
        m_toBox->clear();

        QList<QString> area = { "cm²", "m²", "km²" };

        m_fromBox->addItems(area);
        m_toBox->addItems(area);
    }

    if (selectedUnit == "Volumen") {
        m_fromBox->clear();
        m_toBox->clear();

        QList<QString> volume = { "ml", "cl", "dl", "l" };

        m_fromBox->addItems(volume);
        m_toBox->addItems(volume);
    }

    if (selectedUnit == "Datengröße") {
        m_fromBox->clear();
        m_toBox->clear();

        QList<QString> data = { "KB", "MB", "GB", "TB" };

        m_fromBox->addItems(data);
        m_toBox->addItems(data);
    }
}
