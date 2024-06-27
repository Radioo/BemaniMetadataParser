//
// Created by Radio on 14/06/2024.
//

#include <iconv.h>
#include <stdexcept>
#include <iostream>
#include <regex>

#include "EncodingUtil.hpp"

std::string EncodingUtil::convertSDVXMusicDbToUtf8(const std::string& input) {
    auto converted = convertWithIconv(input, "CP932", "UTF-8");
    replaceXmlEncoding(converted, "UTF-8");
    replaceSdvxCharacters(converted);
    return std::move(converted);
//    return input;
}

std::string EncodingUtil::convertWithIconv(const std::string& input, const std::string&& fromEncoding, const std::string&& toEncoding) {
    auto descriptor = iconv_open(toEncoding.c_str(), fromEncoding.c_str());

    std::string output;

    char* input_ptr = const_cast<char*>(input.data());
    size_t input_size = input.size();
    size_t output_size = input_size * 4;
    output.resize(output_size);
    char* output_ptr = output.data();

    if(size_t result = iconv(descriptor, &input_ptr, &input_size, &output_ptr, &output_size); result == static_cast<size_t>(-1)) {
        throw std::runtime_error("Failed to convert string");
    }

    iconv_close(descriptor);

    return std::move(output);
}

void EncodingUtil::replaceSdvxCharacters(std::string& input) {
//    input = convertWithIconv(input, "CP932", "UTF-8");
    for(auto& [key, value] : sdvxCharacterMap) {
        size_t pos = 0;
        while((pos = input.find(key, pos)) != std::string::npos) {
            std::cout << "Replacing " << key << " with " << value << '\n';
            input.replace(pos, key.length(), value);
            pos += value.length();
        }
    }
}

void EncodingUtil::replaceXmlEncoding(std::string& input, std::string&& toEncoding) {
    auto xmlPrologPattern = std::regex(R"(^<\?xml version="1.0" encoding="[^"]+"\?>)");
    // Search only the first 50 characters
    auto match = std::smatch();
    if(std::regex_search(input, match, xmlPrologPattern)) {
        auto xmlProlog = match[0].str();
        auto newXmlProlog = std::regex_replace(xmlProlog, std::regex(R"(encoding="[^"]+")"), "encoding=\"" + toEncoding + "\"");
        input.replace(0, xmlProlog.length(), newXmlProlog);
    }
}
