#ifndef CREATECOLLECTIONDIALOG_H
#define CREATECOLLECTIONDIALOG_H

#include <QDialog>

class CreateCollectionDialog : public QDialog
{
    Q_OBJECT

public:
    CreateCollectionDialog(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

private:
    QColor m_color;
    QColor m_textColor;
    QPushButton* m_colorBtn;
    QPushButton* m_textColorBtn;

protected:
    void closeEvent(QCloseEvent* e) override;

signals:
    void newTile();
    void closed();

private slots:
    void createTile(const QString& text, const QColor& color, const QColor &textColor);
    void getColor();
    void getTextColor();
};

#endif // CREATECOLLECTIONDIALOG_H
