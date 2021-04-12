#ifndef ERABUTTON_H
#define ERABUTTON_H

#include <QGraphicsItem>
#include <QFont>

class EraButton : public QGraphicsItem
{
public:
    EraButton(const QString& title, QGraphicsItem *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void setColor(const QColor& color);
    void setGeometry(double x, double y, double width, double height);
    void setFont(const QFont& font);
    QRectF boundingRect() const override;

private:
    QFont m_font;
    QColor m_color;
    QString m_title;
    double m_x, m_y, m_width, m_height;

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*e) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent*e) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*e) override;
};

#endif // ERABUTTON_H
