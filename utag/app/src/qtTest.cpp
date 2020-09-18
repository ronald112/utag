#include "MyHeaders.h"

int tryMyQt(int argc, char *argv[]) {
    QApplication app (argc, argv);

    QPushButton button ("Hello world !");
    button.show();

    return app.exec();
}