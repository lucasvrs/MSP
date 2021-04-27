#ifndef TILEITEM_H
#define TILEITEM_H

#include <QGraphicsItem>

class TileItem : public QGraphicsItem
{
public:
    TileItem(QGraphicsItem* parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    void setColor(const QColor& c);
    void setTextColor(const QColor& c);
    void setHeight(double h);
    void setWidth(double w);
    void setText(const QString& text);
    void setWidget(QWidget* widget);
    void setId(int id);
    void setPreviews(QList<TileItem*> previews);
    const QString& text() const;
    double height() const;
    double width() const;
    QList<TileItem*> previews() const;
    QWidget* widget() const;
    QRectF boundingRect() const override;
    int id() const;

private:
    int m_id;
    double m_height;
    double m_width;
    QColor m_color;
    QColor m_textColor;
    QString m_text;
    QWidget* m_widget;
    QList<TileItem*> m_previews;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* e) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* e) override;
};

#endif // TILEITEM_H
