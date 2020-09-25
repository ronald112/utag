#include <MiscHeaders.h>

using namespace std;

class AudioFile final {
public:
    AudioFile(TagLib::FileRef f, const string &_filePath);

    map<string, string> m_properties;

    int getBitrate();
    int getSampleRate();
    int getChannels();
    int getSeconds();
    int getMinutes();

    void saveFieldWithValue(char field, string value);

    void prettyConsoleOutput();

    bool isNull();

    void getAlbumArt();

    string getProperty(const string &key);
    string filePath;
    string fileName;
private:
    TagLib::FileRef m_f;
};
