#include "BinaryStream.h"
#include <vector>
#include <cinttypes>
#include <json.hpp>

using namespace IOReader;
using json = nlohmann::json;

constexpr FileAccess ReadBinary = FileAccess(FileAccess::Read & FileAccess::Binary);
constexpr FileAccess WriteBinary = FileAccess(FileAccess::Write & FileAccess::Binary);

const std::string outputFolder = "./output/";
const std::string sceneFile = "scene.json";

class MViewParser
{
public:
    MViewParser( const std::string& filename )
        : m_binary_reader( filename )
    {}

    void GetPackedFiles()
    {
        while( !m_binary_reader.EndOfFile() )
        {
            std::string filename = m_binary_reader.ReadString();
            std::string mimetype = m_binary_reader.ReadString();
            if( filename.empty() )
            {
                break;
            }
            // Skip trash
            // Zero byte
            m_binary_reader.Get<uint32_t>();
            // Get file size
            int filesize = m_binary_reader.Get<uint32_t>();
            m_binary_reader.Get<uint32_t>();
            // Create a new file buffer
            {
                std::string path = outputFolder + filename;
                m_files.push_back( path );
                BinaryWriter<WriteBinary> bw( path );
                for( int i = 0; i < filesize; ++i )
                {
                    char filebyte = m_binary_reader.Get<char>();
                    bw.Set<char>( filebyte, sizeof(char) );
                }
            }
        }
    }

    void ParseScene()
    {
        BinaryReader<FileAccess::Read> scene( outputFolder + sceneFile );
        std::string incoming_json = scene.ReadString();
        json j = json::parse( incoming_json );

        std::cout << "Dump: " << j["meshes"][0].dump(4) << std::endl;
    }

private:
    BinaryReader<ReadBinary> m_binary_reader;
    std::vector<std::string> m_files;
};

