#ifndef ADDPREVIEWDIALOG_H
#define ADDPREVIEWDIALOG_H

#include <QDialog>

class TileItem;

class AddPreviewDialog : public QDialog
{
    Q_OBJECT

public:
    AddPreviewDialog(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

protected:
    void closeEvent(QCloseEvent* e) override;

signals:
    void addTile(TileItem* tile);
    void closed();
};

#endif // ADDPREVIEWDIALOG_H
