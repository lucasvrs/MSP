#ifndef PATHFINDINGLOGICOPTIONSWIDGET_H
#define PATHFINDINGLOGICOPTIONSWIDGET_H

#include <QWidget>

class QSpinBox;

class PathfindingLogicOptionsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PathfindingLogicOptionsWidget(QWidget *parent = nullptr);

private:
    bool m_changes;
    QSpinBox* m_startRowSpinBox;
    QSpinBox* m_startColSpinBox;
    QSpinBox* m_destRowSpinBox;
    QSpinBox* m_destColSpinBox;

signals:
    void closeOptions();
    void delimiterPosChanged(int sCol, int sRow, int dCol, int dRow);

public slots:
    void setDestRow(int i);
    void setStartRow(int i);
    void setDestCol(int i);
    void setStartCol(int i);
    void applyChanges();
};

#endif // PATHFINDINGLOGICOPTIONSWIDGET_H
