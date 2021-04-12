#ifndef PATHFINDINGGUIWIDGET_H
#define PATHFINDINGGUIWIDGET_H

#include <QWidget>

class QPushButton;

struct GuiColorType
{
    enum Types
    {
        StartIn = 0,
        StartOut,
        DestIn,
        DestOut,
        Obst,
        Node,
        Visited
    };
};

class PathfindingGuiOptionsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PathfindingGuiOptionsWidget(QWidget *parent = nullptr);

private:
    bool m_changes;
    QPalette* m_pal;
    QPushButton* m_startOutColBtn;
    QPushButton* m_startInColBtn;
    QPushButton* m_destOutColBtn;
    QPushButton* m_destInColBtn;
    QPushButton* m_obstColBtn;
    QPushButton* m_nodeColBtn;
    QPushButton* m_visitedColBtn;
    QList<QPushButton*> m_btns;
    std::map<QPushButton*, GuiColorType::Types> m_btnTypeMap;

signals:
    void closeOptions();
    void colorChanged(GuiColorType::Types type, const QColor& color);

private slots:
    void applyChanges();

public slots:
    void openColorPicker(QPushButton* btn);
    void setBtnColor(QPushButton* btn, const QColor& color);
    void setBtnColor(GuiColorType::Types type, const QColor& color);
};

#endif // PATHFINDINGGUIWIDGET_H
