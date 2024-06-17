//
// Created by Radio on 14/06/2024.
//

#include <iconv.h>
#include <stdexcept>

#include "EncodingUtil.hpp"

std::string EncodingUtil::convertSDVXMusicDbToUtf8(const std::string& input) {
    return convertWithIconv(input, "CP932", "UTF-8");
}

std::string EncodingUtil::convertWithIconv(const std::string& input, const std::string&& fromEncoding, const std::string&& toEncoding) {
    return input;
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

    return output;
}