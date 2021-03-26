#ifndef HEADERWIDGET_H
#define HEADERWIDGET_H

#include <QWidget>

class QLabel;

class HeaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderWidget(QWidget *parent = nullptr);

private:
    QLabel* m_headerLabel;

signals:

public slots:
    void setHeader(const QString& title);
};

#endif // HEADERWIDGET_H
