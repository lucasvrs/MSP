#include "sqlconnector.h"
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>


/*!
 * \fn SQLConnector::dbConnect
 *
 * Connects to the Sqlite Database, if opened again old instance is closed.
 *
 */
void SQLConnector::dbConnect()
{
    if(QSqlDatabase::isDriverAvailable("QSQLITE"))
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("./../FinalMsp/Widgets/VocabularyTrainer/Vokabeln.db");
        if(!db.open())
        {
            qWarning() << "SQLConnector::databaseConnect - ERROR: " << db.lastError().text();
        }
    }
    else
    {
        qWarning() << "SQLConnector::databaseConnect - ERROR: no driver QSQLITE available";
    }
}


/*!
 * \fn SQLConnector::readVokabeln
 * \return QList<Vokabel>
 *
 * Reads all Entries from the Database and puts them into a QList<Vokabel>
 * if no entries are found QList is empty.
 *
 */
QList<Vokabel> SQLConnector::readVokabeln()
{
    Vokabel tempVokabel;
    QList<Vokabel> result;
    QSqlQuery query;

    if(query.exec("SELECT vokabel_id, vokabel, translation, kasten_level, vokabel_sprache.sprache AS vok_sprache, translation_sprache.sprache As trans_sprache "
                    "FROM vokabeln, sprachen vokabel_sprache, sprachen translation_sprache "
                    "WHERE sprache_vokabel_id = vokabel_sprache.sprache_id and sprache_translation_id = translation_sprache.sprache_id ORDER BY vokabel"))
    {
        while(query.next())
        {
            tempVokabel.vokabelId = query.value("vokabel_id").toInt();
            tempVokabel.vokabel = query.value("vokabel").toString();
            tempVokabel.translation = query.value("translation").toString();
            tempVokabel.kastenLevel = query.value("kasten_level").toInt();
            tempVokabel.spracheVokabel = query.value("vok_sprache").toString();
            tempVokabel.spracheTranslation = query.value("trans_sprache").toString();

            result.append(tempVokabel);
        }
        return result;
    }else
    {
        qWarning() << "SQLConnector::readVokabeln - ERROR: " << query.lastError().text();
        return result;
    }
}
/*!
 * \fn customQuery
 * \param cQuery
 * \return QList<Vokabel>
 *
 * Reads specified Entries from the Database and puts them into a QList<Vokabel>
 * if no entries are found QList is empty.
 *
 */
QList<Vokabel> customQuery(QString cQuery){
    Vokabel tempVokabel;
    QList<Vokabel> result;
    QSqlQuery query;
    if(query.exec(cQuery))
    {
        while(query.next())
        {
            tempVokabel.vokabelId = query.value("vokabel_id").toInt();
            tempVokabel.vokabel = query.value("vokabel").toString();
            tempVokabel.translation = query.value("translation").toString();
            tempVokabel.kastenLevel = query.value("kasten_level").toInt();
            tempVokabel.spracheVokabel = query.value("vok_sprache").toString();
            tempVokabel.spracheTranslation = query.value("trans_sprache").toString();

            result.append(tempVokabel);
        }
        return result;
    }else
    {
        qWarning() << "SQLConnector::readVokabeln - ERROR: " << query.lastError().text();
        return result;
    }
}

/*!
 * \fn SQLConnector::createVokabel
 * \param vokabel
 * \return Count of changed rows or -1 if there was an Error.
 *
 * Creates a new entry in the SQLite-Database
 *
 */
int SQLConnector::createVokabel(Vokabel vokabel)
{
    QSqlQuery query;

    query.prepare("INSERT INTO vokabeln (vokabel, translation, kasten_level, sprache_vokabel_id, "
                    "sprache_translation_id) VALUES ((:vokabel), (:translation), "
                    "(:kastenLevel), (:vokabelSprache), (:translationSprache))");

    query.bindValue(":vokabel",vokabel.vokabel);
    query.bindValue(":translation",vokabel.translation);
    query.bindValue(":kastenLevel",vokabel.kastenLevel);
    query.bindValue(":vokabelSprache",getSpracheId(vokabel.spracheVokabel));
    query.bindValue(":translationSprache",getSpracheId(vokabel.spracheTranslation));
    if(query.exec())
    {
        return query.numRowsAffected();
    }else
    {
        qWarning() << "SQLConnector::createVokabel - ERROR: " << query.lastError() << " " << query.lastQuery();
        return -1;
    }
}
/*!
 * \fn SQLConnector::updateVokabel
 * \param vokabelId
 * \param vokabel
 * \return Count of changed rows or -1 if there was an Error.
 *
 * Changes entry with vokabelId in the SQLite-Database to match vokabel
 *
 */
int SQLConnector::updateVokabel(int vokabelId, Vokabel vokabel)
{
    QSqlQuery query;
    query.prepare("UPDATE vokabeln "
                    "SET vokabel = (:vokabel), translation = (:translation), kasten_level = (:kasten_level), "
                    "sprache_vokabel_id = (:spracheVokabelId), sprache_translation_id = (:spracheTranslationId) "
                    "WHERE vokabel_id = :vokabel_id");

    query.bindValue(":vokabel_id",vokabelId);

    query.bindValue(":vokabel",vokabel.vokabel);
    query.bindValue(":translation",vokabel.translation);
    query.bindValue(":kastenLevel",vokabel.kastenLevel);
    query.bindValue(":spracheVokabelId",getSpracheId(vokabel.spracheVokabel));
    query.bindValue(":spracheTranslationId",getSpracheId(vokabel.spracheTranslation));
    if(query.exec())
    {
        return query.numRowsAffected();
    }else
    {
        qWarning() << "SQLConnector::updateVokabel - ERROR: " << query.lastError().text() << " " << query.lastQuery();
        return -1;
    }
}

/*!
 * \fn SQLConnector::deleteVokabel
 * \param vokabelId
 * \return Changed rows or -1 if there was an Error
 *
 * Deletes entry with vokabelId in the SQLite-Database
 *
 */
int SQLConnector::deleteVokabel(int vokabel_id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM vokabeln WHERE vokabel_id = (:vokabel_id)");
    query.bindValue(":vokabel_id",vokabel_id);
    if(query.exec())
    {
        return query.numRowsAffected();
    }else
    {
        qWarning() << "SQLConnector::deleteVokabel - ERROR: " << query.lastError().text() << " " << query.lastQuery();
        return -1;
    }
}

int SQLConnector::getIdSprache(QString sprache)
{
    QSqlQuery query;
    query.prepare("SELECT sprache_id FROM sprachen WHERE sprache = " + sprache);
    if (!query.exec())
    {
        qWarning() << "SQLConnector::getSpracheId - ERROR: " << query.lastError().text() << " " << query.lastQuery();
    }
    if (query.next())
    {
       return query.value(0).toInt();
    }
    return -1;
}

QList<QString> SQLConnector::getSubjects()
{
    QList<QString> result;
    QSqlQuery query;

    if(query.exec("SELECT sprache FROM sprachen "))
    {
        while(query.next())
        {
            result.append(query.value("sprache").toString());
        }
        return result;
    }else
    {
        qWarning() << "SQLConnector::readVokabeln - ERROR: " << query.lastError().text();
        return result;
    }
}

/*!
 * \fn SQLConnector::getSpracheId
 * \param sprache
 * \return Id for "sprache"
 *
 * Gets ID for "sprache" from tabelle "sprachen" From the SQLite Database and if it not exists creates it
 *
 */
int SQLConnector::getSpracheId(QString sprache)
{
    QSqlQuery query;
    query.prepare("SELECT sprache_id FROM sprachen WHERE sprache = (:sprache)");
    query.bindValue(":sprache", sprache);

    if (!query.exec())
    {
        qWarning() << "SQLConnector::getSpracheId - ERROR: " << query.lastError().text() << " " << query.lastQuery();
    }
    if (query.next())
    {
       return query.value(0).toInt();
    }
    else
    {
        if(SQLConnector::createSprache(sprache) > 0){
            return SQLConnector::getSpracheId(sprache);
        }else {
            //todo
            //fehler beim erstellen
            qWarning() << "SQLConnector::getSpracheId - ERROR: " << query.lastError().text() << " " << query.lastQuery();
            return -1;
        }
    }
}

/*!
 * \fn SQLConnector::createSprache
 * \param sprache
 * \return Changed rows or -1 if there was an Error
 *
 * Creates new entry for "sprache" in SQLite Database
 *
 */
int SQLConnector::createSprache(QString sprache)
{
    QSqlQuery query;

    query.prepare("INSERT INTO sprachen (sprache) VALUES (:sprache)");
    query.bindValue(":sprache", sprache);
    if(query.exec())
    {
       return query.numRowsAffected();
    }else
    {
        qWarning() << "SQLConnector::createSprache - ERROR: " << query.lastError().text() << " " << query.lastQuery();
        return -1;
    }
}
