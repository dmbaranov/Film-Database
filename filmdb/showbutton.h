#ifndef SHOWBUTTON_H
#define SHOWBUTTON_H
#include <QtGui>
#include <QtSql/QtSql>

class ButtonFilm: public QWidget
{
    Q_OBJECT

private:
    QLabel *title;
    QLabel *year;
    QLabel *director;
    QLabel *genre;
    QLabel *time;
    QLabel *link;
    QLabel *description;
    QToolButton *button[6];
    QPushButton *updateButton;
    QMessageBox *info;
    QSqlDatabase db;

public:
    ButtonFilm(QWidget *pwgt = 0);

private slots:
    void slotUpdateButtons();
    void slotButtonClicked();
};

#endif // SHOWBUTTON_H
