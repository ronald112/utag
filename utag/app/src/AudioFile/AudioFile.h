#include <MiscHeaders.h>
#include <QImage>

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

    QImage getAlbumArt();

    string getProperty(const string &key);
    string filePath;
    string fileName;
private:
    QImage APECase(TagLib::APE::Tag* tag);
    QImage ID3Case(TagLib::ID3v2::Tag* tag);
    QImage ASFCase(TagLib::ASF::File* file);
    QImage FLACCase(TagLib::FLAC::File* file);
    QImage MP4Case(TagLib::MP4::File* file);
    TagLib::FileRef m_f;
};
