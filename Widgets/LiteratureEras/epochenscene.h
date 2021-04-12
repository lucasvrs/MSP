#ifndef EPOCHENSCENE_H
#define EPOCHENSCENE_H

#include <QGraphicsScene>

#include <unordered_map>

class XMLReader;

class EpochenScene : public QGraphicsScene
{
    Q_OBJECT
public:
    EpochenScene(QObject *parent = nullptr);
    void populateScene();

private:
    bool m_initialized;
    double m_widthMultiplier;
    int m_extraDivisor;
    XMLReader* m_reader;
    std::vector<QString> m_eraNames;
    std::vector<int> m_eraFroms;
    std::vector<int> m_eraTos;
    std::vector<int> m_layers;
    void drawEras();
    void getEras();
    void unpopulateScene();

public slots:
    void adjustWidthMultiplier(double value);

};

#endif // EPOCHENSCENE_H
