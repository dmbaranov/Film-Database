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

    tabs->addTab(new AddFilm, tr("Добавить фильм"));
    tabs->addTab(new ShowFilm, tr("Список фильмов"));
    tabs->addTab(new ButtonFilm, tr("Фильмокнопки"));
    tabs->addTab(new Search, tr("Поиск"));

    QVBoxLayout *lay = new QVBoxLayout;
    lay->addWidget(tabs);

    this->setLayout(lay);
}
