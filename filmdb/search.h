#ifndef SEARCH_H
#define SEARCH_H
#include <QtGui>
#include <QtSql/QtSql>
#include "editform.h"

class Search: public QWidget
{
    Q_OBJECT

private:
    QLineEdit *searchByTitle;
    QPushButton *buttonSearch;
    QPushButton *buttonView;
    QPushButton *buttonEdit;
    QPushButton *buttonDelete;
    QTableView *view;
    QSqlQueryModel *model;
    QMessageBox *info;
    QString filmTitle;
    EditForm *form;
    QSqlDatabase db;

public:
    Search(QWidget *pwgt = 0);

private slots:
    void slotButtonSearchClicked();
    void slotButtonViewClicked();
    void slotButtonEditClicked();
    void slotButtonDeleteClicked();
    void slotEditFormOk();
};

#endif // SEARCH_H
