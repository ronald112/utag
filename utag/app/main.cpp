#include <MyHeaders.h>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2 && argc != 1) {
        cerr << "usage: ./utag [folder]" << endl;
        exit(EXIT_FAILURE);
    }
    QApplication a(argc, argv);

    TagEditor w;
    w.show();

    return a.exec();
}
