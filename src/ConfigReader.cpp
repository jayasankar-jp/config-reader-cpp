#include <ConfigReader.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>

std::string_view ConfigReader::mefn_trim_sv(std::string_view str)
{
    const auto first = str.find_first_not_of(" \t\r\n");
    if (first == std::string_view::npos)
        return {};
    const auto last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

std::string ConfigReader::mefn_trim(const std::string &str)
{
    return std::string(mefn_trim_sv(str));
}

void ConfigReader::mefn_split(const std::string &text, char delimiter, std::string &left, std::string &right)
{
    size_t pos = text.find(delimiter);
    if (pos != std::string::npos)
    {
        left = std::string(mefn_trim_sv(text.substr(0, pos)));
        right = std::string(mefn_trim_sv(text.substr(pos + 1)));
    }
    else
    {
        left = std::string(mefn_trim_sv(text));
        right.clear();
    }
}

int ConfigReader::mcfn_readConfig(const std::string &file_name)
{
    std::ifstream in_file(file_name);
    if (!in_file.is_open())
    {
        return 0;
    }

    std::string sl_currentSession;
    std::string line;

    while (std::getline(in_file, line))
    {
        std::string_view trimmed = mefn_trim_sv(line);
        if (trimmed.empty())
            continue;

        // Skip full line comments
        if (trimmed.front() == '#' || trimmed.front() == ';')
            continue;

        // Section header
        if (trimmed.size() >= 2 && trimmed.front() == '[' && trimmed.back() == ']')
        {
            sl_currentSession = std::string(trimmed.substr(1, trimmed.size() - 2));
            mecm_session_map[sl_currentSession]; // Ensure section exists
            continue;
        }

        // Handle inline comments (strip anything after '#' or ';' not inside quotes)
        bool in_quotes = false;
        size_t comment_pos = std::string_view::npos;
        for (size_t i = 0; i < trimmed.size(); ++i)
        {
            if (trimmed[i] == '"')
            {
                in_quotes = !in_quotes;
            }
            else if (!in_quotes && (trimmed[i] == '#' || trimmed[i] == ';'))
            {
                comment_pos = i;
                break;
            }
        }

        if (comment_pos != std::string_view::npos)
        {
            trimmed = mefn_trim_sv(trimmed.substr(0, comment_pos));
            if (trimmed.empty())
                continue;
        }

        // Key = Value
        size_t eq_pos = trimmed.find('=');
        if (eq_pos == std::string_view::npos)
        {
            continue;
        }

        std::string key(mefn_trim_sv(trimmed.substr(0, eq_pos)));
        std::string value(mefn_trim_sv(trimmed.substr(eq_pos + 1)));

        if (!key.empty())
        {
            mecm_session_map[sl_currentSession][key] = value;
        }
    }

    return 1;
}

int CConfigValue::as_int() const
{
    try
    {
        return std::stoi(mes_value);
    }
    catch (...)
    {
        return -1;
    }
}

double CConfigValue::as_double() const
{
    try
    {
        return std::stod(mes_value);
    }
    catch (...)
    {
        return -1.0;
    }
}

bool CConfigValue::as_bool() const
{
    std::string temp = mes_value;
    std::transform(temp.begin(), temp.end(), temp.begin(), [](unsigned char c) { return std::tolower(c); });
    return (temp == "true" || temp == "1" || temp == "yes");
}

std::string CConfigValue::as_string() const
{
    return mes_value;
}

Array CConfigValue::as_array() const
{
    return Array(mes_value);
}

CConfigValue CSession::operator[](const std::string &key) const
{
    auto it = data.find(key);
    if (it != data.end())
        return CConfigValue(it->second);
    return CConfigValue("");
}

CSession ConfigReader::operator[](const std::string &section) const
{
    auto it = mecm_session_map.find(section);
    if (it != mecm_session_map.end())
        return CSession(it->second);
    return CSession();
}

Array::Array(const std::string &data)
{
    std::string_view trimmed = ConfigReader::mefn_trim_sv(data);
    if (trimmed.size() >= 2 && trimmed.front() == '[' && trimmed.back() == ']')
    {
        trimmed = trimmed.substr(1, trimmed.size() - 2);
    }

    size_t start = 0;
    while (start < trimmed.size())
    {
        size_t comma_pos = trimmed.find(',', start);
        if (comma_pos == std::string_view::npos)
        {
            std::string_view elem = ConfigReader::mefn_trim_sv(trimmed.substr(start));
            if (!elem.empty())
                mecV_data.emplace_back(elem);
            break;
        }

        std::string_view elem = ConfigReader::mefn_trim_sv(trimmed.substr(start, comma_pos - start));
        mecV_data.emplace_back(elem);
        start = comma_pos + 1;
    }
}

std::vector<int> Array::as_int() const
{
    std::vector<int> cl_vec;
    cl_vec.reserve(mecV_data.size());
    for (const auto &item : mecV_data)
    {
        try
        {
            cl_vec.push_back(std::stoi(item));
        }
        catch (...)
        {
        }
    }
    return cl_vec;
}

std::vector<double> Array::as_double() const
{
    std::vector<double> cl_vec;
    cl_vec.reserve(mecV_data.size());
    for (const auto &item : mecV_data)
    {
        try
        {
            cl_vec.push_back(std::stod(item));
        }
        catch (...)
        {
        }
    }
    return cl_vec;
}

std::vector<std::string> Array::as_string() const
{
    return mecV_data;
}