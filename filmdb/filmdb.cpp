#include "filmdb.h"
#include "addfilm.h"
#include "showfilm.h"
#include "showbutton.h"
#include "search.h"

Film::Film(QWidget *pwgt): QWidget (pwgt)
{
    tabs = new QTabWidget;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("films.fdtb");
    if(!db.open())
    {
        qDebug() << "DB is not opened";
    }

    tabs->addTab(new AddFilm, tr("�������� �����"));
    tabs->addTab(new ShowFilm, tr("������ �������"));
    tabs->addTab(new ButtonFilm, tr("������������"));
    tabs->addTab(new Search, tr("�����"));

    QVBoxLayout *lay = new QVBoxLayout;
    lay->addWidget(tabs);

    this->setLayout(lay);
}
