#include <vector>
#include <iostream>
#include <MViewParser.h>

int main( int argc, char const *argv[] )
{
    if( argc < 2 )
    {
        std::cout << "No enought params!" << std::endl;
    }
    std::string file( argv[1] );
    try
    {
        MViewParser parser( file );
        parser.GetPackedFiles();
        parser.ParseScene();
        parser.GenerateWavefront();
    }
    catch( const std::exception& ex )
    {
        std::cout << "Exception: " << ex.what() << std::endl;
    }
    return 0;
}
