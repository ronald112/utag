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

QImage AudioFile::getAlbumArt() {

    if (TagLib::MPEG::File* file = dynamic_cast<TagLib::MPEG::File*>(m_f.file()))
    {
        if (file->ID3v2Tag())
        {
            return ID3Case(file->ID3v2Tag());
        }
        if (file->APETag())
        {
            return APECase(file->APETag());
        }
    }
    else if (TagLib::ASF::File* file = dynamic_cast<TagLib::ASF::File*>(m_f.file()))
    {
        return ASFCase(file);
    }
    else if (TagLib::MP4::File* file = dynamic_cast<TagLib::MP4::File*>(m_f.file()))
    {
        if (file->tag())
        {
            return MP4Case(file);
        }
    }
    else if (TagLib::FLAC::File* file = dynamic_cast<TagLib::FLAC::File*>(m_f.file()))
    {
        return FLACCase(file);
    }
    else if (TagLib::APE::File* file = dynamic_cast<TagLib::APE::File*>(m_f.file()))
    {
        if (file->APETag())
        {
            return APECase(file->APETag());
        }
    }
    else if (TagLib::MPC::File* file = dynamic_cast<TagLib::MPC::File*>(m_f.file()))
    {
        if (file->APETag())
        {
            return APECase(file->APETag());
        }
    }
    else if (TagLib::WavPack::File* file = dynamic_cast<TagLib::WavPack::File*>(m_f.file()))
    {
        if (file->APETag())
        {
            return APECase(file->APETag());
        }
    }
    return{};
}

/*
** Extracts cover art embedded in ID3v2 tags.
**
*/
QImage AudioFile::ID3Case(TagLib::ID3v2::Tag* tag)
{
    const TagLib::ID3v2::FrameList& frameList = tag->frameList("APIC");
    if (!frameList.isEmpty())
    {
        // Grab the first image
        TagLib::ID3v2::AttachedPictureFrame* frame = static_cast<TagLib::ID3v2::AttachedPictureFrame*>(frameList.front());
        QImage img;
        img.loadFromData((const unsigned char*)frame->picture().data(), (int)frame->picture().size());

        return img;
    }

    return {};
}

/*
** Extracts cover art embedded in APE tags.
**
*/
QImage AudioFile::APECase(TagLib::APE::Tag* tag)
{
    const TagLib::APE::ItemListMap& listMap = tag->itemListMap();

    if (listMap.contains("COVER ART (FRONT)"))
    {
        const TagLib::ByteVector nullStringTerminator(1, 0);

        TagLib::ByteVector item = listMap["COVER ART (FRONT)"].value();
        int pos = item.find(nullStringTerminator);	// Skip the filename

        if (++pos > 0)
        {
            const TagLib::ByteVector& pic = item.mid(pos);

            QImage img;
            img.loadFromData((const unsigned char*)pic.data(), pic.size());
            return img;
        }
    }

    return {};
}

/*
** Extracts cover art embedded in ASF/WMA files.
**
*/
QImage AudioFile::ASFCase(TagLib::ASF::File* file)
{
    const TagLib::ASF::AttributeListMap& attrListMap = file->tag()->attributeListMap();
    if (attrListMap.contains("WM/Picture"))
    {
        const TagLib::ASF::AttributeList& attrList = attrListMap["WM/Picture"];

        if (!attrList.isEmpty())
        {
            // Let's grab the first cover. TODO: Check/loop for correct type
            TagLib::ASF::Picture wmpic = attrList[0].toPicture();
            if (wmpic.isValid())
            {
                QImage img;
                img.loadFromData((const unsigned char*)wmpic.picture().data(), (int)wmpic.picture().size());
                return img;
            }
        }
    }

    return {};
}

/*
** Extracts cover art embedded in FLAC files.
**
*/
QImage AudioFile::FLACCase(TagLib::FLAC::File* file)
{
    const TagLib::List<TagLib::FLAC::Picture*>& picList = file->pictureList();
    if (!picList.isEmpty())
    {
        // Let's grab the first image
        TagLib::FLAC::Picture* pic = picList[0];
        QImage img;
        img.loadFromData((const unsigned char*)pic->data().data(), (int)pic->data().size());
        return img;
    }

    return {};
}

/*
** Extracts cover art embedded in MP4-like files.
**
*/
QImage AudioFile::MP4Case(TagLib::MP4::File* file)
{
    TagLib::MP4::Tag* tag = file->tag();
    if (tag->itemListMap().contains("covr"))
    {
        TagLib::MP4::CoverArtList coverList = tag->itemListMap()["covr"].toCoverArtList();

        if (coverList[0].data().size() > 0)
        {
            QImage img;
            img.loadFromData((const unsigned char*)coverList[0].data().data(), coverList[0].data().size());
            return img;
        }
    }

    return {};
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
*"TITLE"
*"ALBUM"
*"ARTIST"
*"ALBUMARTIST"
*"SUBTITLE"
*"TRACKNUMBER"
*"DISCNUMBER"
*"DATE"
*"ORIGINALDATE"
*"GENRE"
*"COMMENT"
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
