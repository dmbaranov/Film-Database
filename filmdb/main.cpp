#include <QTextCodec>
#include "filmdb.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));
    QApplication a(argc, argv);
    Film film;
    film.resize(1024, 768);
    film.show();
    
    return a.exec();
}
