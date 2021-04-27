#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QWidget>

class QLabel;
class QPushButton;

class HeaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderWidget(QWidget *parent = nullptr);

private:
    QLabel* m_headerLabel;
    QWidget* m_prevWidget;
    QPushButton* m_prevBtn;

signals:
    void showOptions();
    void showWidget(QWidget* w);

public slots:
    void setHeader(const QString& title);
    void setPrevWidget(QWidget* w);
    void disablePrev();
};

#endif // HEADERWIDGET_H
