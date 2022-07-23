#include "Lesper/basic.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 0;
    }

    std::string path = argv[1];
    run(path);

    return 0;
}