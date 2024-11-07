#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

// URL 编码函数
std::string urlEncode(const std::string& str) {
    std::ostringstream encoded;
    for (char c : str) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            encoded << c;  // 不需要编码的字符
        } else if (c == ' ') {
            encoded << '+';  // 将空格编码为 '+'
        } else {
            encoded << '%' << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << static_cast<int>(static_cast<unsigned char>(c));
        }
    }
    return encoded.str();
}

// URL 解码函数
std::string urlDecode(const std::string& str) {
    std::ostringstream decoded;
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == '%') {
            if (i + 2 < str.length()) {
                std::string hexValue = str.substr(i + 1, 2);
                char decodedChar = static_cast<char>(std::stoi(hexValue, nullptr, 16));
                decoded << decodedChar;
                i += 2;
            }
        } else if (str[i] == '+') {
            decoded << ' ';  // '+' 解码为空格
        } else {
            decoded << str[i];
        }
    }
    return decoded.str();
}