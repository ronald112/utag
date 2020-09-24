#include "AudioFile.h"

void checkForRejectedProperties(const TagLib::PropertyMap &tags)
{ // stolen from tagreader.cpp
  if(tags.size() > 0) {
    unsigned int longest = 0;
    for(TagLib::PropertyMap::ConstIterator i = tags.begin(); i != tags.end(); ++i) {
      if(i->first.size() > longest) {
        longest = i->first.size();
      }
    }
    cout << "-- rejected TAGs (properties) --" << endl;
    for(TagLib::PropertyMap::ConstIterator i = tags.begin(); i != tags.end(); ++i) {
      for(TagLib::StringList::ConstIterator j = i->second.begin(); j != i->second.end(); ++j) {
        cout << left << std::setw(longest) << i->first << " - " << '"' << *j << '"' << endl;
      }
    }
  }
}

AudioFile::AudioFile(TagLib::FileRef f, const string &_filePath) : filePath(_filePath), m_f(f) {
    if (!m_f.isNull() && m_f.tag()) {
        TagLib::PropertyMap tags = m_f.file()->properties();

        for(TagLib::PropertyMap::ConstIterator i = tags.begin(); i != tags.end(); ++i) {
            for(TagLib::StringList::ConstIterator j = i->second.begin(); j != i->second.end(); ++j) {
                m_properties[string((i->first).toCString())] = string((*j).toCString());
            }
        }
    }
}

/*
*"-t <title>"  
*"-a <artist>" 
*"-A <album>"  
*"-c <comment>"
*"-g <genre>"  
*"-y <year>"   
*"-T <track>"  
*"-D <tagname>"
*/
void AudioFile::saveFieldWithValue(char field, string value) {
    TagLib::Tag *t = m_f.tag();

    switch (field) {
    case 't':
        t->setTitle(value);
    break;
    case 'a':
        t->setArtist(value);
    break;
    case 'A':
        t->setAlbum(value);
    break;
    case 'c':
        t->setComment(value);
    break;
    case 'g':
        t->setGenre(value);
    break;
    case 'y':
        t->setYear(std::stoi(value));
    break;
    case 'T':
        t->setTrack(std::stoi(value));
    break;
    case 'D':
        TagLib::PropertyMap map = m_f.file()->properties();
        map.erase(value);
        checkForRejectedProperties(m_f.file()->setProperties(map));
    break;
    }
    m_f.file()->save();
}

/*
* TITLE
* ALBUM
* ARTIST
* ALBUMARTIST
* SUBTITLE
* TRACKNUMBER
* DISCNUMBER
* DATE
* ORIGINALDATE
* GENRE
* COMMENT
*/
string AudioFile::getProperty(const string &key) {
    try {
        return m_properties.at(key);
    }
    catch(...) {
        return "";
    }
}

int AudioFile::getBitrate() {
    return m_f.audioProperties()->bitrate();
}
int AudioFile::getSampleRate() {
    return m_f.audioProperties()->sampleRate();
}
int AudioFile::getChannels() {
    return m_f.audioProperties()->channels();
}
int AudioFile::getSeconds() {
    return m_f.audioProperties()->length() % 60;
}
int AudioFile::getMinutes() {
    return (m_f.audioProperties()->length() - getSeconds()) / 60;
}

bool AudioFile::isNull() {
    return !m_f.isNull() && m_f.tag();
}

void AudioFile::prettyConsoleOutput() {
    TagLib::PropertyMap tags = m_f.file()->properties();

    unsigned int longest = 0;
    for(TagLib::PropertyMap::ConstIterator i = tags.begin(); i != tags.end(); ++i) {
        if (i->first.size() > longest) {
        longest = i->first.size();
        }
    }

    cout << "----- TAG (properties) -----" << endl;
    for(TagLib::PropertyMap::ConstIterator i = tags.begin(); i != tags.end(); ++i) {
        for(TagLib::StringList::ConstIterator j = i->second.begin(); j != i->second.end(); ++j) {
            cout << left << setw(longest) << i->first << " - " << '"' << *j << '"' << endl;
        }
    }

    if(!m_f.isNull() && m_f.audioProperties()) {

        TagLib::AudioProperties *properties = m_f.audioProperties();

        int seconds = properties->length() % 60;
        int minutes = (properties->length() - seconds) / 60;

        cout << "-----\tAUDIO\t-----" << endl;
        cout << "bitrate     - " << properties->bitrate() << endl;
        cout << "sample rate - " << properties->sampleRate() << endl;
        cout << "channels    - " << properties->channels() << endl;
        cout << "length      - " << minutes << ":" << setfill('0') << setw(2) << seconds << endl;
    }
}
