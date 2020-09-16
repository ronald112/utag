#include "MiscHeaders.h"

using namespace std;

int dummy(int argc, char *argv[]) {
    for(int i = 1; i < argc; i++) {

        cout << "******************** \"" << argv[i] << "\" ********************" << endl;

        TagLib::FileRef f(argv[i]);

        if(!f.isNull() && f.tag()) {

            TagLib::Tag *tag = f.tag();

            cout << "-- TAG (basic) --" << endl;
            cout << "title   - \"" << tag->title()   << "\"" << endl;
            cout << "artist  - \"" << tag->artist()  << "\"" << endl;
            cout << "album   - \"" << tag->album()   << "\"" << endl;
            cout << "year    - \"" << tag->year()    << "\"" << endl;
            cout << "comment - \"" << tag->comment() << "\"" << endl;
            cout << "track   - \"" << tag->track()   << "\"" << endl;
            cout << "genre   - \"" << tag->genre()   << "\"" << endl;

            TagLib::PropertyMap tags = f.file()->properties();

            unsigned int longest = 0;
            for(TagLib::PropertyMap::ConstIterator i = tags.begin(); i != tags.end(); ++i) {
                if (i->first.size() > longest) {
                longest = i->first.size();
                }
            }

            cout << "-- TAG (properties) --" << endl;
            for(TagLib::PropertyMap::ConstIterator i = tags.begin(); i != tags.end(); ++i) {
                for(TagLib::StringList::ConstIterator j = i->second.begin(); j != i->second.end(); ++j) {
                cout << left << std::setw(longest) << i->first << " - " << '"' << *j << '"' << endl;
                }
            }

        }

        if(!f.isNull() && f.audioProperties()) {

            TagLib::AudioProperties *properties = f.audioProperties();

            int seconds = properties->length() % 60;
            int minutes = (properties->length() - seconds) / 60;

            cout << "-- AUDIO --" << endl;
            cout << "bitrate     - " << properties->bitrate() << endl;
            cout << "sample rate - " << properties->sampleRate() << endl;
            cout << "channels    - " << properties->channels() << endl;
            cout << "length      - " << minutes << ":" << setfill('0') << setw(2) << seconds << endl;
        }
    }
    return 0;
}

