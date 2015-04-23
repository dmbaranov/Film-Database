#ifndef EDITFORM_H
#define EDITFORM_H
#include <QtGui>

class EditForm: public QWidget
{
    Q_OBJECT

public:
    QLineEdit *titleLine;
    QLineEdit *yearLine;
    QLineEdit *directorLine;
    QLineEdit *genreLine;
    QLineEdit *timeLine;
    QLineEdit *linkLine;
    QTextEdit *descriptionText;
    QPushButton *buttonOk;

    EditForm(QWidget *pwgt = 0);
};

#endif // EDITFORM_H
