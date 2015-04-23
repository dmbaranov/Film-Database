#ifndef FILMDB_H
#define FILMDB_H
#include <QtGui>
#include <QtSql/QtSql>
#include <QtNetwork/QtNetwork>

class Film: public QWidget
{
    Q_OBJECT

private:
    QTabWidget *tabs;
    QSqlDatabase db;

public: 
    Film(QWidget *pwgt = 0);
};

#endif // FILMDB_H
