#ifndef __CONFIG_READER_LIB_H__
#define __CONFIG_READER_LIB_H__

#include <vector>
#include <unordered_map>
#include <string>
#include <string_view>

class Array
{
private:
    std::vector<std::string> mecV_data;

public:
    explicit Array(const std::string &data);
    std::vector<int> as_int() const;
    std::vector<double> as_double() const;
    std::vector<std::string> as_string() const;
};

class CConfigValue
{
private:
    std::string mes_value;

public:
    CConfigValue(std::string value)
        : mes_value(std::move(value)) {}

    int as_int() const;
    double as_double() const;
    bool as_bool() const;
    Array as_array() const;
    std::string as_string() const;
};

class CSession
{
private:
    static inline const std::unordered_map<std::string, std::string> empty_map{};
    const std::unordered_map<std::string, std::string> &data;

public:
    CSession() : data(empty_map) {}
    CSession(const std::unordered_map<std::string, std::string> &d) : data(d) {}

    CConfigValue operator[](const std::string &key) const;
};

class ConfigReader
{
public:
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> mecm_session_map;

    static std::string mefn_trim(const std::string &str);
    static std::string_view mefn_trim_sv(std::string_view str);
    static void mefn_split(const std::string &text, char delimiter, std::string &left, std::string &right);

    CSession operator[](const std::string &section) const;
    int mcfn_readConfig(const std::string &file_name);
};

#endif

