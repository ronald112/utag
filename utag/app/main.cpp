#include <MyHeaders.h>

using namespace std;

int main(int argc, char *argv[]) {
    // if (argc != 2) {
    //     cerr << "usage: ./utag [folder]" << endl;
    //     exit(EXIT_FAILURE);
    // }
    // const regex pattern(R"((\.mp3|\.flac|\.waw|\.ogg)$)");
    // for (const auto & entry : fs::directory_iterator(argv[1])) {
    //     cmatch match;
    //     if (entry.is_directory() == false
    //         && regex_match(entry.path().extension().string().c_str(), match, pattern)
    //         ) {
    //             // std::cout << match.str(1) << std::endl;
    //             std::cout << entry.path().filename().string() << std::endl;
    //     }
    // }
    // TagLib::FileRef f(argv[1]);

    // if(!f.isNull() && f.tag()) {
    //     AudioFile a(f);

    //     a.prettyConsoleOutput();
    // }
    // return 0;

    // Creates an instance of QApplication
    QApplication a(argc, argv);

    // This is our MainWidget class containing our GUI and functionality
    TagEditor w;
    w.show(); // Show main window

    // run the application and return execs() return value/code
    return a.exec();

 return 0;
}
