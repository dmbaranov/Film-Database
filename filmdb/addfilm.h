#ifndef ADDFILM_H
#define ADDFILM_H
#include <QtGui>
#include <QtSql/QtSql>
#include <QtNetwork/QtNetwork>

class AddFilm: public QWidget
{
    Q_OBJECT

private:
    QLineEdit *titleLine;
    QLineEdit *yearLine;
    QLineEdit *directorLine;
    QLineEdit *genreLine;
    QLineEdit *timeLine;
    QLineEdit *linkLine; //poster
    QLineEdit *urlLine; //html
    QTextEdit *descriptionText;
    QPushButton *buttonAdd;
    QPushButton *downloadButton;
    QPushButton *downloadHtmlButton;
    QPushButton *checkTitleButton;

    QNetworkAccessManager *manager;
    QSqlDatabase db;

public:
    AddFilm(QWidget *pwgt = 0);


private slots:
    void slotAddFilm();
    void download();
    void parseHtml();
    void replyFinished(QNetworkReply *reply);
};

#endif // ADDFILM_H
