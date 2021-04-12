#ifndef SQLCONNECTOR_H
#define SQLCONNECTOR_H

#include <QAbstractItemModel>

struct Vokabel
{
    int vokabelId;
    QString vokabel;
    QString translation;
    int kastenLevel;
    QString spracheVokabel;
    QString spracheTranslation;
};


class SQLConnector:QObject
{
    Q_OBJECT

public:
    void dbConnect();
    QList<Vokabel> readVokabeln();
    int createVokabel(Vokabel vokabel);
    int updateVokabel(int vokabel_id, Vokabel vokabel);
    int deleteVokabel(int vokabel_id);
    QList<Vokabel> customQuery(QString cQuery);
    int getIdSprache(QString sprache);
    QList<QString> getSubjects();


private:
    int getSpracheId(QString sprache);
    int createSprache(QString sprache);
};

#endif // SQLCONNECTOR_H
