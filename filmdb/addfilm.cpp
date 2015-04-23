#include "addfilm.h"
#include "filmdb.h"

AddFilm::AddFilm(QWidget *pwgt): QWidget(pwgt)
{
    titleLine = new QLineEdit;
    yearLine = new QLineEdit;
    directorLine = new QLineEdit;
    genreLine = new QLineEdit;
    timeLine = new QLineEdit;
    linkLine = new QLineEdit;
    urlLine = new QLineEdit;
    descriptionText = new QTextEdit;
    buttonAdd = new QPushButton(tr("Добавить"));
    downloadButton = new QPushButton(tr("Загрузить"));
    downloadHtmlButton = new QPushButton(tr("Получить информацию"));
    checkTitleButton = new QPushButton(tr("Проверить"));
    manager = new QNetworkAccessManager(this);

    QGridLayout *lay = new QGridLayout;
    lay->addWidget(new QLabel(tr("Ссылка на страницу")), 0, 0);
    lay->addWidget(urlLine, 0, 1);
    lay->addWidget(downloadHtmlButton, 0, 2);
    lay->addWidget(new QLabel(tr("Название")), 1, 0);
    lay->addWidget(titleLine, 1, 1);
    lay->addWidget(new QLabel(tr("Год")), 2, 0);
    lay->addWidget(yearLine, 2, 1);
    lay->addWidget(new QLabel(tr("Режиссер")), 3, 0);
    lay->addWidget(directorLine, 3, 1);
    lay->addWidget(new QLabel(tr("Жанр")), 4, 0);
    lay->addWidget(genreLine, 4, 1);
    lay->addWidget(new QLabel(tr("Продолжительность")), 5, 0);
    lay->addWidget(timeLine, 5, 1);
    lay->addWidget(new QLabel(tr("Ссылка на постер")), 6, 0);
    lay->addWidget(linkLine, 6, 1);
    lay->addWidget(downloadButton, 6, 2);
    lay->addWidget(new QLabel(tr("Описание")), 7, 0);
    lay->addWidget(descriptionText, 7, 1);
    lay->addWidget(buttonAdd, 8, 0, 1, 3);

    connect(buttonAdd, SIGNAL(clicked()), this, SLOT(slotAddFilm()));
    connect(downloadButton, SIGNAL(clicked()), this, SLOT(download()));
    connect(downloadHtmlButton, SIGNAL(clicked()), this, SLOT(parseHtml()));

    this->setLayout(lay);
}

void AddFilm::slotAddFilm()
{
    int ctr = 0;
    QString command;
    QSqlQuery query;

    if(query.next())
    {
        ctr++;
    }

    QString temp =
            "INSERT INTO films (title, year, director, genre, time, description, link) "
            "VALUES ('%0', %1, '%2', '%3', %4, '%5', '%6');";

    command = temp.arg(titleLine->text()).arg(yearLine->text()).arg(directorLine->text()).arg(genreLine->text()).arg(timeLine->text()).arg(descriptionText->toPlainText()).arg("img/" + linkLine->text().section('/', -1));
    if(!query.exec(command))
    {
        qDebug() << "Inside the addFilm(). Error: " << query.lastError();
    }
    titleLine->clear();
    yearLine->clear();
    directorLine->clear();
    genreLine->clear();
    timeLine->clear();
    linkLine->clear();
    descriptionText->clear();
}

void AddFilm::download()
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(linkLine->text());
    manager->get(request);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

void AddFilm::replyFinished(QNetworkReply *reply)
{
    if(reply->error())
    {
        qDebug() << "Error" << reply->errorString();
    }
    QFile file("img/" + linkLine->text().section('/', -1));
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(reply->readAll());
        file.flush();
        file.close();
    }
    reply->deleteLater();
}

void AddFilm::parseHtml()
{
    int begin, end = 0;
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(urlLine->text())));
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    //QByteArray arr = reply->readAll();
    QString text = reply->readAll();//QString::fromAscii(arr.data());
    //text = tr("%1").arg(text);

    //------------------название фильма-------------------------//

    begin = text.indexOf("<meta itemprop=\"name\" content=\"");
    end = text.indexOf("<meta itemprop=\"alternativeHeadline\"");

    qDebug() << begin;
    qDebug() << end;

    QString title = text.mid(begin, end - begin);
    title.remove("<meta itemprop=\"name\" content=\"");
    title.remove("/>");
    title.remove("\"");
    title.remove(title.length() - 1, 1);
    titleLine->setText(title);

    //------------------название фильма-------------------------//


    //------------------год фильма-------------------------//

    begin = text.indexOf("<meta itemprop=\"dateCreated\" content=\"");
    end = text.indexOf("<meta itemprop=\"url\"");

    QString year = text.mid(begin, end - begin);
    year.remove("/>");
    year.remove("\"");
    year.remove(year.length() - 1, 1);
    year = year.right(4);
    yearLine->setText(year);

    //------------------год фильма-------------------------//


    //------------------режиссер фильма-------------------------//
    end = text.indexOf("</span></a></p><p");
    begin = end - 50;
    QString director = text.mid(begin, end - begin);
    int temp = director.indexOf("name\">");
    director.remove(0, temp + 6);
    directorLine->setText(director);

    //------------------режиссер фильма-------------------------//



    //------------------жанр фильма-------------------------//

    begin = text.indexOf("<br/></td></tr><tr><td colspan='2'><span style='header'>");
    end = text.indexOf("</a></td></tr><tr><td colspan='2'><em class=");
    QString genre = text.mid(begin, end - begin);
    genre.remove(QRegExp("[a-zA-Z</>=':-#]"));
    genre.remove(0, 7);
    genre = genre.simplified();
    genreLine->setText(genre);

    //------------------жанр фильма-------------------------//



    //------------------описание фильма-------------------------//

    begin = text.indexOf("<meta itemprop=\"description\" content=");
    end = text.indexOf("/><meta itemprop=\"name\"");

    qDebug() << begin;
    qDebug() << end;

    QString desc = text.mid(begin, end - begin);
    desc.remove(0, 38);
    desc.remove(desc.length() - 2, 1);
    desc = desc.simplified();
    descriptionText->setText(desc);

    //------------------описание фильма-------------------------//


    //------------------постер фильма-------------------------//

    begin = text.indexOf("<link rel='image_src' href=");
    end = text.indexOf("<meta property=\"og:url\"");
    QString url = text.mid(begin, end - begin);
    url.remove(0, 28);
    url = url.simplified();
    url.remove(url.length() - 3, 3);
    linkLine->setText(url);

    //------------------постер фильма-------------------------//


    //------------------ппродолжительность фильма-------------------------//

    end = text.indexOf("<br/></td></tr><tr><td colspan='2'><p align=");
    begin = end - 5;
    QString time = text.mid(begin, end - begin);
    qDebug() << time;
    int h1 = time.left(1).toInt();
    int h2 = time.left(2).toInt();
    int m1 = time.left(4).toInt();
    int m2 = time.left(5).toInt();
    qDebug() << h1 << h2 << m1 << m2;

    //------------------ппродолжительность фильма-------------------------//
}
