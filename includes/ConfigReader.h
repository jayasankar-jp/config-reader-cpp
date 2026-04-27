#ifndef __CONFIG_READER_LIB_H__
#define __CONFIG_READER_LIB_H__
#include <vector>
#include <map>
#include <string>
#include <fstream>
class CConfigValue
{
private:
    std::string mes_value;

public:
    CConfigValue(const std::string &value)
        : mes_value(value) {}

    int as_int() const;

    double as_double() const;

    bool as_bool() const;

    std::string as_string() const;
};
class CSession
{
private:
    const std::map<std::string, std::string> &data;

public:
    CSession(const std::map<std::string, std::string> &d) : data(d) {}

    CConfigValue operator[](const std::string &key) const;
};

class ConfigReader
{
private:
public:
    std::map<std::string, std::map<std::string, std::string>> mecm_session_map;
    std::ifstream meC_file;
    std::string mefn_trim(const std::string &str);
    void mefn_split(const std::string &text, char delimiter, std::string &left, std::string &right);
    // CConfigValue operator[](const std::string &key) const;
    CSession operator[](const std::string &section) const;

public:
    int mcfn_readConfig(const std::string &file_name);
};

#endif
