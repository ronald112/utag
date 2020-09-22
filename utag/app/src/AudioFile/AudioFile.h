#include <MiscHeaders.h>

using namespace std;

class AudioFile final {
public:
    AudioFile(TagLib::FileRef f);

    map<string, string> m_properties;

    int getBitrate();
    int getSampleRate();
    int getChannels();
    int getSeconds();
    int getMinutes();

    void prettyConsoleOutput();

    bool isNull();

    string getProperty(const string &key);
private:
    TagLib::FileRef m_f;
};
