#include "ConfigReader.h"
#include <iostream>

int main()
{
    ConfigReader reader;
    if (reader.mcfn_readConfig("System.ini"))
    {
        std::cout << "Read Successfully" << std::endl;
    }
    else
    {
        std::cerr << "Failed to read System.ini" << std::endl;
        return 1;
    }
    std::cout << "GLOBAL APPNAME: '" << reader["GLOBAL"]["APPNAME"].as_string() << "'" << std::endl;
    std::cout << "MY_APP LOG_LEVEL: " << reader["MY_APP"]["LOG_LEVEL"].as_int() << std::endl;
    std::cout << "MY_APP LOG_DIR: '" << reader["MY_APP"]["LOG_DIR"].as_string() << "'" << std::endl;
    
    auto vec = reader["MY_APP"]["MY_LIST"].as_array().as_string();
    for (const auto &i : vec)
    {
        std::cout << "List item: '" << i << "'" << std::endl;
    }

    return 0;
}