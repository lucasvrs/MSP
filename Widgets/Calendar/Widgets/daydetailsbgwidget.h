#ifndef DAYDETAILSBGWIDGET_H
#define DAYDETAILSBGWIDGET_H

#include <QWidget>

class DayDetailsGroupBox;

class DayDetailsBgWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DayDetailsBgWidget(const QDate &date, QWidget *parent = nullptr);

private:
    DayDetailsGroupBox* m_details;

protected:
    void mouseReleaseEvent(QMouseEvent* e) override;

signals:
    void clicked();
    void needsUpdate(const QDate& date);
};

#endif // DAYDETAILSBGWIDGET_H
