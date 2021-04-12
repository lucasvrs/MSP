#ifndef PATHFINDINGWIDGET_H
#define PATHFINDINGWIDGET_H

#include <QWidget>

class PathfindingOptionsWidget;
class PathfindingScene;
class QComboBox;

struct Pathfinding
{
    enum Modes
    {
        DelimiterMode = 0,
        ObstacleMode,
        DeleteMode,
        ModeAmount
    };
};

class PathfindingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PathfindingWidget(QWidget *parent = nullptr);

private:
    QComboBox* m_modeBox;
    PathfindingScene* m_scene;
    Pathfinding::Modes m_curMode;
    void setMode(Pathfinding::Modes mode);
    Pathfinding::Modes mode() const;
    const Pathfinding::Modes m_modeList[Pathfinding::ModeAmount] = {Pathfinding::DelimiterMode,
                                                                    Pathfinding::ObstacleMode,
                                                                    Pathfinding::DeleteMode};
    PathfindingOptionsWidget* m_options;

protected:
    void keyReleaseEvent(QKeyEvent* e) override;
    void resizeEvent(QResizeEvent* e) override;

signals:

private slots:
    void openOptions();

public slots:

};

#endif // PATHFINDINGWIDGET_H
