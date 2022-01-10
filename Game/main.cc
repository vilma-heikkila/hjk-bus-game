#include "objectgenerator.hh"
#include <QApplication>

/*  PULSUPELI
 *  30.11.2020
 *
 * Matias Jokinen, H274174, matias.a.jokinen@tuni.fi
 * Vilma Heikkilä, H283288, vilma.heikkila@tuni.fi
 *
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);

    ObjectGenerator o;
    MainWindow* w = o.returnWindow();
    w->show();
    
    return a.exec();
}
