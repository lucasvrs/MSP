#ifndef MSPWIDGET_H
#define MSPWIDGET_H

#include <QStackedWidget>

class OptionsWidget;

class MspWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit MspWidget(QWidget *parent = nullptr);

private:
    OptionsWidget* m_options;

signals:
    void changeStyle(int mode);
};

#endif // MSPWIDGET_H
