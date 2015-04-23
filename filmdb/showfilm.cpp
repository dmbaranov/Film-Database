#include "showfilm.h"

ShowFilm::ShowFilm(QWidget *pwgt): QWidget(pwgt)
{
    buttonView = new QPushButton(tr("Информация"));
    buttonEdit = new QPushButton(tr("Изменить"));
    buttonDelete = new QPushButton(tr("Удалить"));
    buttonUpdate = new QPushButton(tr("Обновить"));
    info = new QMessageBox;
    form = new EditForm;
    view = new QTableView;
    model = new QSqlQueryModel;

    model->setQuery("SELECT title AS 'Название', year AS 'Год', director AS 'Режиссер', genre AS 'Жанр', time AS 'Продолжительность' "
                    "FROM films ");

    view->setModel(model);
    view->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(buttonView, SIGNAL(clicked()), this, SLOT(slotButtonViewClicked()));
    connect(buttonEdit, SIGNAL(clicked()), this, SLOT(slotButtonEditClicked()));
    connect(buttonDelete, SIGNAL(clicked()), this, SLOT(slotButtonDeleteClicked()));
    connect(buttonUpdate, SIGNAL(clicked()), this, SLOT(slotButtonUpdateClicked()));

    QGridLayout *lay = new QGridLayout;
    lay->addWidget(view, 0, 0, 1, 4);
    lay->addWidget(buttonView, 1, 0);
    lay->addWidget(buttonEdit, 1, 1);
    lay->addWidget(buttonUpdate, 1, 2);
    lay->addWidget(buttonDelete, 1, 3);


    this->setLayout(lay);
}

void ShowFilm::slotButtonViewClicked()
{
    QLabel title;
    QLabel year;
    QLabel director;
    QLabel genre;
    QLabel time;
    QLabel link;
    QLabel description;

    QString film = model->index(view->currentIndex().row(), 0).data().toString();

    QSqlQuery query("SELECT * "
                    "FROM films "
                    "WHERE title = '" + film + "'");
    while(query.next())
    {
        //title, year, director, time, link, description
        title.setText(query.value(0).toString());
        year.setText(query.value(1).toString());
        director.setText(query.value(2).toString());
        genre.setText(query.value(3).toString());
        time.setText(query.value(4).toString());
        description.setText(query.value(5).toString());
        link.setText(query.value(6).toString());
    }

    QPixmap map(link.text());

    info->setWindowTitle(tr("Информация о фильме"));
    info->setText(tr("Название: ") + title.text() + tr("\n\nГод: ") + year.text() + tr("\n\nРежиссер: ") + director.text() + tr("\n\nЖанр: ") + genre.text() + tr("\n\nОписание: ") + description.text());
    info->setIconPixmap(map);
    info->exec();
}

void ShowFilm::slotButtonEditClicked()
{
    filmTitle = model->index(view->currentIndex().row(), 0).data().toString();
    QSqlQuery query("SELECT * "
                    "FROM films "
                    "WHERE title = '" + filmTitle + "'");
    while(query.next())
    {
        form->titleLine->setText(query.value(0).toString());
        form->yearLine->setText(query.value(1).toString());
        form->directorLine->setText(query.value(2).toString());
        form->genreLine->setText(query.value(3).toString());
        form->timeLine->setText(query.value(4).toString());
        form->descriptionText->setText(query.value(5).toString());
        form->linkLine->setText(query.value(6).toString());
    }
    form->show();
    connect(form->buttonOk, SIGNAL(clicked()), this, SLOT(slotEditFormOk()));

}

void ShowFilm::slotEditFormOk()
{
    QSqlQuery query(
                "UPDATE films "
                "SET title = '" + form->titleLine->text() + "', year = " + form->yearLine->text() + ", director = '" + form->directorLine->text() + "', genre = '" + form->genreLine->text() + "', time = " + form->timeLine->text() + ", description = '" + form->descriptionText->toPlainText() + "', link = '" + form->linkLine->text() + "' "
                "WHERE title = '" + filmTitle + "' ");
    query.exec();
    form->close();
}

void ShowFilm::slotButtonDeleteClicked()
{
    filmTitle = model->index(view->currentIndex().row(), 0).data().toString();
    QSqlQuery query(
                "DELETE "
                "FROM films "
                "WHERE title = '" + filmTitle + "' ");
    query.exec();
    view->setRowHidden(view->currentIndex().row(), true);
}

void ShowFilm::slotButtonUpdateClicked()
{
    model->setQuery("SELECT title AS 'Название', year AS 'Год', director AS 'Режиссер', genre AS 'Жанр', time AS 'Продолжительность' "
                    "FROM films ");
}
