#include "ConfigReader.h"
#include <iostream>
int main()
{
    ConfigReader reader;
    if (reader.mcfn_readConfig("System.ini"))
    {
        std::cout << "Read Sucessfully" << std::endl;
    }
    else
    {
        return 0;
    }
    std::cout << reader["GLOBAL"]["APPNAME"].as_string() << std::endl;
    std::cout << reader["MY_APP"]["LOG_LEVEL"].as_int() << std::endl;
    std::cout << reader["MY_APP"]["LOG_DIR"].as_string() << std::endl;
    std::cout << reader["MY_APP"]["MY_LIST"].as_array().as_string()[0] << std::endl;

    return 0;
}