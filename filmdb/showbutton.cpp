#include "showbutton.h"

ButtonFilm::ButtonFilm(QWidget *pwgt): QWidget(pwgt)
{
    title = new QLabel;
    year = new QLabel;
    director = new QLabel;
    genre = new QLabel;
    time = new QLabel;
    link = new QLabel;
    description = new QLabel;
    description->setWordWrap(true);
    updateButton = new QPushButton(tr("Обновить"));
    info = new QMessageBox;

    for(int i = 0; i < 6; i++)
    {
        button[i] = new QToolButton;
        button[i]->setText("test");
        connect(button[i], SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
    }

    connect(updateButton, SIGNAL(clicked()), this, SLOT(slotUpdateButtons()));

    QGridLayout *lay = new QGridLayout;
    lay->addWidget(button[0], 0, 0);
    lay->addWidget(button[1], 0, 1);
    lay->addWidget(button[2], 0, 2);
    lay->addWidget(button[3], 1, 0);
    lay->addWidget(button[4], 1, 1);
    lay->addWidget(button[5], 1, 2);
    lay->addWidget(updateButton, 2, 0, 1, 3);

    this->setLayout(lay);

    slotUpdateButtons();
}

void ButtonFilm::slotUpdateButtons()
{
    QString ttl;
    QPixmap map;

    for(int i = 0; i < 6; i++)
    {
        QSqlQuery randQuery(
                "SELECT title "
                "FROM films "
                "ORDER BY RANDOM() LIMIT 1");
        randQuery.first();
        ttl = randQuery.value(0).toString();
        QSqlQuery selectQuery(
                    "SELECT * "
                    "FROM films "
                    "WHERE title = '" + ttl + "'");
        selectQuery.first();
        title->setText(selectQuery.value(0).toString());
        year->setText(selectQuery.value(1).toString());
        director->setText(selectQuery.value(2).toString());
        genre->setText(selectQuery.value(3).toString());
        time->setText(selectQuery.value(4).toString());
        description->setText(selectQuery.value(5).toString());
        link->setText(selectQuery.value(6).toString());
        map.load(link->text());

        button[i]->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        button[i]->setIcon(map);
        button[i]->setIconSize(QSize(150, 230));
        button[i]->setText(title->text());
    }
}

void ButtonFilm::slotButtonClicked()
{
    QPixmap map;
    QToolButton *temp = dynamic_cast<QToolButton*>(sender());
    QSqlQuery query("SELECT * "
                    "FROM films "
                    "WHERE title = '" + temp->text() + "' ");
    while(query.next())
    {
        title->setText(query.value(0).toString());
        year->setText(query.value(1).toString());
        director->setText(query.value(2).toString());
        genre->setText(query.value(3).toString());
        time->setText(query.value(4).toString());
        description->setText(query.value(5).toString());
        link->setText(query.value(6).toString());
    }
    map.load(link->text());

    info->setWindowTitle(tr("Информация о фильме"));
    info->setText(tr("Название: ") + title->text() + tr("\n\nГод: ") + year->text() + tr("\n\nРежиссер: ") + director->text() + tr("\n\nЖанр: ") + genre->text() + tr("\n\nОписание: ") + description->text());
    info->setIconPixmap(map);
    info->exec();
}
