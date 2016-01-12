#ifndef SFMLSTREAM_H_INCLUDED
#define SFMLSTREAM_H_INCLUDED

#include "soundsManager.h"

namespace sf
{
    class RenderWindowStream : public RenderWindow
    {
    public:
        RenderWindowStream(VideoMode VM, String title, Uint32 style);
        RenderWindowStream();

        sfSounds::SoundsManager soundsManager;

        void operator <<(const Drawable & object);
        void operator <<(const Color & color);

        void operator >>(const char * file);
        void operator >>(Image & image);
        bool operator >>(Event & event);
    };

    RenderWindowStream::RenderWindowStream(VideoMode VM, String title = "SFML application", Uint32 style = Style::Default)
    {
        create(VM, title, style);
    }
    RenderWindowStream::RenderWindowStream(){}

    void RenderWindowStream::operator<<(const Drawable & object)
    {
        draw(object);
    }
    void RenderWindowStream::operator<<(const Color & color)
    {
        clear(color);
    }

    void RenderWindowStream::operator>>(const char * file)
    {
        capture().saveToFile(file);
    }
    bool RenderWindowStream::operator >>(Event & event)
    {
        return pollEvent(event);
    }
    void RenderWindowStream::operator>>(Image & image)
    {
        image = capture();
    }
}

#endif // SFMLSTREAM_H_INCLUDED
