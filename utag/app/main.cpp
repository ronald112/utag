#include <MyHeaders.h>

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    TagEditor w;
    w.show();

    return a.exec();
}
