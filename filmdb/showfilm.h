#ifndef SHOWFILM_H
#define SHOWFILM_H
#include <QtGui>
#include <QtSql/QtSql>
#include "editform.h"

class ShowFilm: public QWidget
{
    Q_OBJECT

private:
    QPushButton *buttonView;
    QPushButton *buttonEdit;
    QPushButton *buttonDelete;
    QPushButton *buttonUpdate;
    QMessageBox *info;
    EditForm *form;
    QTableView *view;
    QSqlQueryModel *model;
    QSqlDatabase db;
    QString filmTitle;

public:
    ShowFilm(QWidget *pwgt = 0);

private slots:
    void slotButtonViewClicked();
    void slotButtonEditClicked();
    void slotButtonDeleteClicked();
    void slotButtonUpdateClicked();
    void slotEditFormOk();
};

#endif // SHOWFILM_H
