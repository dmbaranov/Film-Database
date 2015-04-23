#include "search.h"

Search::Search(QWidget *pwgt): QWidget(pwgt)
{
    form = new EditForm;
    searchByTitle = new QLineEdit;
    buttonSearch = new QPushButton(tr("������"));
    buttonView = new QPushButton(tr("����������"));
    buttonEdit = new QPushButton(tr("��������"));
    buttonDelete = new QPushButton(tr("�������"));
    view = new QTableView;
    model = new QSqlQueryModel;
    info = new QMessageBox;

    view->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(buttonSearch, SIGNAL(clicked()), this, SLOT(slotButtonSearchClicked()));
    connect(buttonView, SIGNAL(clicked()), this, SLOT(slotButtonViewClicked()));
    connect(buttonEdit, SIGNAL(clicked()), this, SLOT(slotButtonEditClicked()));
    connect(buttonDelete, SIGNAL(clicked()), this, SLOT(slotButtonDeleteClicked()));

    QGridLayout *lay = new QGridLayout;
    lay->addWidget(new QLabel(tr("��������")), 0, 0);
    lay->addWidget(searchByTitle, 0, 1);
    lay->addWidget(buttonSearch, 0, 2);
    lay->addWidget(view, 1, 0, 1, 3);
    lay->addWidget(buttonView, 2, 0);
    lay->addWidget(buttonEdit, 2, 1);
    lay->addWidget(buttonDelete, 2, 2);

    this->setLayout(lay);
}

void Search::slotButtonSearchClicked()
{
    model->setQuery("SELECT title AS '��������', year AS '���', director AS '��������', genre AS '����', time AS '�����������������' "
                    "FROM films "
                    "WHERE title = '" + searchByTitle->text() + "'");
    view->setModel(model);
}

void Search::slotButtonViewClicked()
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
        title.setText(query.value(0).toString());
        year.setText(query.value(1).toString());
        director.setText(query.value(2).toString());
        genre.setText(query.value(3).toString());
        time.setText(query.value(4).toString());
        description.setText(query.value(5).toString());
        link.setText(query.value(6).toString());
    }

    QPixmap map(link.text());

    info->setWindowTitle(tr("���������� � ������"));
    info->setText(tr("��������: ") + title.text() + tr("\n\n���: ") + year.text() + tr("\n\n��������: ") + director.text() + tr("\n\n����: ") + genre.text() + tr("\n\n��������: ") + description.text());
    info->setIconPixmap(map);
    info->exec();
}

void Search::slotButtonEditClicked()
{
    qDebug() << "here";
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

void Search::slotEditFormOk()
{
    QSqlQuery query(
                "UPDATE films "
                "SET title = '" + form->titleLine->text() + "', year = " + form->yearLine->text() + ", director = '" + form->directorLine->text() + "', genre = '" + form->genreLine->text() + "', time = " + form->timeLine->text() + ", description = '" + form->descriptionText->toPlainText() + "', link = '" + form->linkLine->text() + "' "
                "WHERE title = '" + filmTitle + "' ");
    query.exec();
    form->close();
}

void Search::slotButtonDeleteClicked()
{
    filmTitle = model->index(view->currentIndex().row(), 0).data().toString();
    QSqlQuery query(
                "DELETE "
                "FROM films "
                "WHERE title = '" + filmTitle + "' ");
    query.exec();
    view->setRowHidden(view->currentIndex().row(), true);
}
