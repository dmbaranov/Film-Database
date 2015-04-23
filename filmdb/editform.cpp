#include "editform.h"

EditForm::EditForm(QWidget *pwgt): QWidget(pwgt)
{
    titleLine = new QLineEdit;
    yearLine = new QLineEdit;
    directorLine = new QLineEdit;
    genreLine = new QLineEdit;
    timeLine = new QLineEdit;
    linkLine = new QLineEdit;
    descriptionText = new QTextEdit;
    buttonOk = new QPushButton("Ок");

    QGridLayout *lay = new QGridLayout;
    lay->addWidget(new QLabel(tr("Название")), 0, 0);
    lay->addWidget(titleLine, 0, 1);
    lay->addWidget(new QLabel(tr("Год")), 1, 0);
    lay->addWidget(yearLine, 1, 1);
    lay->addWidget(new QLabel(tr("Режиссер")), 2, 0);
    lay->addWidget(directorLine, 2, 1);
    lay->addWidget(new QLabel(tr("Жанр")), 3, 0);
    lay->addWidget(genreLine, 3, 1);
    lay->addWidget(new QLabel(tr("Продолжительность")), 4, 0);
    lay->addWidget(timeLine, 4, 1);
    lay->addWidget(new QLabel(tr("Ссылка на постер")), 5, 0);
    lay->addWidget(linkLine, 5, 1);
    lay->addWidget(new QLabel(tr("Описание")), 6, 0);
    lay->addWidget(descriptionText, 6, 1);
    lay->addWidget(buttonOk, 7, 0);

    this->setLayout(lay);
}
