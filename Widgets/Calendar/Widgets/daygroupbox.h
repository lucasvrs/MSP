#ifndef DAYGROUPBOX_H
#define DAYGROUPBOX_H

#include <QGroupBox>

class QGridLayout;

class DayGroupBox : public QGroupBox
{
    Q_OBJECT

public:
    DayGroupBox(const QDate &date, bool mainMonth = true, QWidget* parent = nullptr);
    const QDate& date() const;
    void removeLayout();
    void addAppointments();
    double height() const;
    void setHeight(double height);
    void setWidth(double width);
    double width() const;

private:
    QGridLayout* m_layout;
    bool m_mainMonth;
    double m_height;
    double m_width;
    QDate* m_date;
    QPalette m_defPalette;
    QPalette curDayPalette() const;
    QPalette hoverPalette() const;
    QPalette otherMonthPalette() const;
    QPalette pressedPalette() const;
    QStringList allAppointments();

protected:
    void enterEvent(QEvent* e) override;
    void leaveEvent(QEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
    void paintEvent(QPaintEvent* e) override;

signals:
    void clicked(const QDate& date);
};

#endif // DAYGROUPBOX_H
