#include <string>
#include <fstream>
#include <iostream>

namespace IOReader
{

enum FileAccess
{
    Binary = std::fstream::binary,
    Read = std::fstream::in,
    Write = std::fstream::out,
    Append = std::fstream::app
};

typedef unsigned long long ull;

template<FileAccess FAcess = FileAccess::Read & FileAccess::Binary>
class BinaryReader
{
public:
    BinaryReader( const std::string& filename )
    : m_ifilestream( filename, (std::ios_base::openmode) FAcess )
    {
        if( !m_ifilestream.is_open() )
        {
            throw std::logic_error("File doesn\'t exist");
        }
    }

    ~BinaryReader()
    {
        m_ifilestream.close();
    }

    std::string ReadString()
    {
        std::string result;
        while( true )
        {
            char c = Get<char>();
            if( c == '\0' )
            {
                break;
            }
            result += c;
        }
        return result;
    }

    // FIX
    void Skip( int bytes )
    {
        m_ifilestream.ignore( bytes, std::ios_base::cur );
    }

    template<typename T>
    T Get()
    {
        T chunk;
        m_ifilestream.read( (char*) &chunk, (int)sizeof(T) );
        return chunk;
    }

    bool EndOfFile() const
    {
        return m_ifilestream.eof();
    }

    ull CurrentPosition()
    {
        return (ull) m_ifilestream.tellg();
    }

    ull Size()
    {
        m_ifilestream.seekg (0, m_ifilestream.end);
        ull length = m_ifilestream.tellg();
        m_ifilestream.seekg (0, m_ifilestream.beg);
        return length;
    }

private:
    std::ifstream m_ifilestream;
};

// Write binary data to file
template<FileAccess FAcess = FileAccess::Write & FileAccess::Binary>
class BinaryWriter
{
public:
    BinaryWriter( const std::string& filename )
    : m_ofilestream( filename, (std::ios_base::openmode) FAcess )
    {
        if( !m_ofilestream.is_open() )
        {
            throw std::logic_error("File doesn\'t exist");
        }
    }

    template<typename T>
    void Set( T data, size_t size )
    {
        m_ofilestream.write( (char*) &data, size );
    }

    ~BinaryWriter()
    {
        m_ofilestream.close();
    }

private:
    std::ofstream m_ofilestream;
};

}; // end of IOReader
