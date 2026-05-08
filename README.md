# Config Reader C++ Library

A lightweight and easy-to-use INI-style configuration reader library for C++.

Supports:

- Section-based config parsing
- Integer, double, bool, string conversion
- Array parsing
- Comment support (`#` and `;`)
- `make install` support
- Simple API
- Lightweight and dependency-free

---

# GitHub Repository

https://github.com/jayasankar-jp/config-reader-cpp

---

# Features

- Easy INI-style configuration parsing
- Simple and clean API
- Type-safe value conversion
- Array support
- Lightweight implementation
- Cross-platform C++ support
- Comment support
- Easy integration with existing C++ projects
- Installable using `make install`

---

# Supported Config Format

```ini
# Sample config

[SERVER]
HOST = 127.0.0.1
PORT = 8080
SSL = true

[DATABASE]
USER = postgres
PASSWORD = root
TIMEOUT = 10.5

[ARRAY]
NUMBERS = [1,2,3,4]
NAMES = [john,alex,mike]
```

---

# Installation

## Clone Repository

```bash
git clone git@github.com:jayasankar-jp/config-reader-cpp.git
cd config-reader-cpp
```

---

# Build

```bash
mkdir build
cd build
cmake ..
make
```

---

# Install Library

```bash
sudo make install
```

Default installation paths:

| Type | Path |
|---|---|
| Header Files | `/usr/local/include` |
| Library Files | `/usr/local/lib` |

---

# Usage

## Include Header

```cpp
#include <ConfigReader.h>
```

---

# Example

## Config File

```ini
[SERVER]
HOST = 127.0.0.1
PORT = 8080
SSL = true

[ARRAY]
NUMBERS = [1,2,3]
```

---

## C++ Example

```cpp
#include <ConfigReader.h>
#include <iostream>

int main()
{
    ConfigReader config;

    if (!config.mcfn_readConfig("config.ini"))
    {
        std::cout << "Failed to read config" << std::endl;
        return -1;
    }

    std::string host = config["SERVER"]["HOST"].as_string();
    int port = config["SERVER"]["PORT"].as_int();
    bool ssl = config["SERVER"]["SSL"].as_bool();

    std::vector<int> numbers =
        config["ARRAY"]["NUMBERS"]
            .as_array()
            .as_int();

    std::cout << "Host : " << host << std::endl;
    std::cout << "Port : " << port << std::endl;
    std::cout << "SSL  : " << ssl << std::endl;

    std::cout << "Numbers : ";

    for (auto n : numbers)
    {
        std::cout << n << " ";
    }

    std::cout << std::endl;

    return 0;
}
```

---

# Compile Example

```bash
g++ main.cpp -lConfigReader
```

If installed in a custom location:

```bash
g++ main.cpp -I/usr/local/include -L/usr/local/lib -lConfigReader
```

---

# API Reference

## Read Config File

```cpp
int mcfn_readConfig(const std::string &file_name);
```

### Return Values

| Value | Meaning |
|---|---|
| `1` | Success |
| `0` | Failed |

---

# Access Sections

```cpp
config["SECTION"]
```

Example:

```cpp
config["SERVER"]
```

---

# Access Keys

```cpp
config["SECTION"]["KEY"]
```

Example:

```cpp
config["SERVER"]["PORT"]
```

---

# Supported Type Conversion

## Integer

```cpp
.as_int()
```

---

## Double

```cpp
.as_double()
```

---

## Boolean

```cpp
.as_bool()
```

Supported true values:

```text
true
1
```

---

## String

```cpp
.as_string()
```

---

# Array Support

## Config Example

```ini
VALUES = [1,2,3]
```

---

## Usage

```cpp
std::vector<int> values =
    config["DATA"]["VALUES"]
        .as_array()
        .as_int();
```

---

# Supported Array Types

| Method | Return Type |
|---|---|
| `as_int()` | `std::vector<int>` |
| `as_double()` | `std::vector<double>` |
| `as_string()` | `std::vector<std::string>` |

---

# Supported Comments

```ini
# Comment

; Comment
```

Inline comments are also supported:

```ini
PORT = 8080 # HTTP Port
```

---

# Project Structure

```text
config-reader-cpp/
│
├── include/
│   └── ConfigReader.h
│
├── src/
│   └── ConfigReader.cpp
│
├── examples/
│
├── CMakeLists.txt
│
└── README.md
```

---

# CMake Integration

## Using Installed Library

```cmake
find_library(CONFIG_READER_LIB ConfigReader)

target_link_libraries(MyApp ${CONFIG_READER_LIB})
```

---

# Future Improvements

- Nested sections
- JSON export support
- Environment variable support
- Auto reload support
- UTF-8 support
- Better error reporting
- Header-only version
- Thread-safe access

---

# License

GNU GENERAL PUBLIC LICENSE (GPL)

---

# Contributing

Contributions are welcome.

Feel free to:

- Report bugs
- Suggest features
- Improve documentation
- Submit pull requests

If you would like to contribute:

```bash
git fork
git clone <your-fork-url>
```

Create a new branch:

```bash
git checkout -b feature-name
```

Commit your changes:

```bash
git commit -m "Added new feature"
```

Push to your fork:

```bash
git push origin feature-name
```

Then create a Pull Request.

---

# Author

Jayasankar JP

GitHub:
https://github.com/jayasankar-jp

---

# Support the Project

If you like this project:

- Star the repository
- Share it with others
- Contribute improvements
- Report issues

Community contributions help improve the project for everyone.