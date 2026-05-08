#include <ConfigReader.h>
#include <iostream>
#include <sstream>
int ConfigReader::mcfn_readConfig(const std::string &file_name)
{
    try
    {
        std::string sl_currentSession = "";
        meC_file.open(file_name);
        if (meC_file.is_open())
        {
            std::string sl_currentLine;
            while (std::getline(meC_file, sl_currentLine))
            {
                // std::cout<<sl_currentLine<<std::endl;
                sl_currentLine = mefn_trim(sl_currentLine);
                if (sl_currentLine.length() > 0)
                {
                    if (sl_currentLine[0] == '#' || sl_currentLine[0] == ';')
                    {
                        // std::cout << "slipiing" << std::endl;
                        continue;
                    }
                    if (sl_currentLine.size() >= 2 && sl_currentLine.front() == '[' && sl_currentLine.back() == ']')
                    {
                        sl_currentSession = sl_currentLine.substr(1, sl_currentLine.size() - 2);

                        // std::cout << "Header " << sl_currentLine << sl_currentSession<<std::endl; // abcd
                    }
                    else if (sl_currentLine.front() != '[' && sl_currentSession.size() > 0 && sl_currentSession != "")
                    {
                        std::string sL_key, sL_value;
                        std::string temp, result;
                        if (sl_currentLine.find('#') != std::string::npos)
                        {
                            mefn_split(sl_currentLine, '#', result, temp);
                            sl_currentLine = result;
                        }
                        else
                        {
                            result = sl_currentLine;
                        }
                        if (sl_currentLine.find(';') != std::string::npos)
                        {

                            mefn_split(sl_currentLine, ';', result, temp);
                        }
                        // std::cout << "Data : " << result << std::endl;
                        if (result.find('=') != std::string::npos)
                            mefn_split(result, '=', sL_key, sL_value);
                        else
                        {
                            std::cout << "Not a vaild config " << result;
                            continue;
                        }
                        if (sL_key != "")
                        {
                            auto cl_it = mecm_session_map.find(sl_currentSession);
                            if (cl_it != mecm_session_map.end())
                            {
                                cl_it->second.insert({sL_key, sL_value});
                            }
                            else
                            {
                                std::map<std::string, std::string> cl_pairvec;
                                cl_pairvec.insert({sL_key, sL_value});
                                mecm_session_map.insert({sl_currentSession, cl_pairvec});
                            }
                            // meC_readdData.insert({sL_key, sL_value});
                            // std::cout << "key: " << sL_key << " value: " << sL_value << std::endl;
                        }
                    }
                }
                else
                {
                    continue;
                }
            }

            meC_file.close();
        }
        else
        {
            return 0;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
    return 1;
}

std::string ConfigReader::mefn_trim(const std::string &str)
{
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");

    if (start == std::string::npos)
        return "";

    return str.substr(start, end - start + 1);
}
void ConfigReader::mefn_split(const std::string &text, char delimiter, std::string &left, std::string &right)
{
    size_t pos = text.find(delimiter);

    if (pos != std::string::npos)
    {
        left = mefn_trim(text.substr(0, pos));
        right = mefn_trim(text.substr(pos + 1));
    }
}
int CConfigValue::as_int() const
{
    try
    {
        return std::stoi(mes_value);
    }
    catch (const std::exception &e)
    {
        // std::cerr << e.what() << '\n';
        return -1;
    }
}
double CConfigValue::as_double() const
{
    try
    {
        return std::stod(mes_value);
    }
    catch (const std::exception &e)
    {
        // std::cerr << e.what() << '\n';
        return -1;
    }
}
bool CConfigValue::as_bool() const
{
    try
    {
        return (mes_value == "true" || mes_value == "1");
    }
    catch (const std::exception &e)
    {
        // std::cerr << e.what() << '\n';
        return 0;
    }
}
std::string CConfigValue::as_string() const
{
    try
    {
        return mes_value;
    }
    catch (const std::exception &e)
    {
        // std::cerr << e.what() << '\n';
        return "";
    }
}
Array CConfigValue::as_array() const
{
    return Array(mes_value);
}
CConfigValue CSession::operator[](const std::string &key) const
{
    try
    {
        auto it = data.find(key);
        if (it != data.end())
            return CConfigValue(it->second);

        return CConfigValue("");
    }
    catch (const std::exception &e)
    {
        return CConfigValue("");
        // std::cerr << e.what() << '\n';
    }
}
CSession ConfigReader::operator[](const std::string &section) const
{
    try
    {
        auto it = mecm_session_map.find(section);

        if (it != mecm_session_map.end())
            return CSession(it->second);

        static std::map<std::string, std::string> empty;
        return CSession(empty);
    }
    catch (const std::exception &e)
    {
        // std::cerr << e.what() << '\n';
        static std::map<std::string, std::string> empty;
        return CSession(empty);
    }
}

Array::Array(const std::string &data)
{
    if (data.size() >= 2 && data.front() == '[' && data.back() == ']')
    {
        std::stringstream ss;
        ss << data.substr(1, data.size() - 2);
        std::string singel_data;
        while (getline(ss, singel_data, ','))
        {
            mecV_data.push_back(singel_data);
        }
    }
}
std::vector<int> Array::as_int()
{
    std::vector<int> cl_vec;
    try
    {
        for (auto i : mecV_data)
        {
            cl_vec.push_back(std::stoi(i));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return cl_vec;
}
std::vector<double> Array::as_double()
{
    std::vector<double> cl_vec;
    try
    {
        for (auto i : mecV_data)
        {
            cl_vec.push_back(std::stod(i));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return cl_vec;
}
std::vector<std::string> Array::as_string()
{
    return mecV_data;
}