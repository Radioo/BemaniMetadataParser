//
// Created by Radio on 14/06/2024.
//

#ifndef BEMANIMETADATAPARSER_ENCODINGUTIL_HPP
#define BEMANIMETADATAPARSER_ENCODINGUTIL_HPP

#include <string>

class EncodingUtil {
public:
    static std::string convertSDVXMusicDbToUtf8(const std::string& input);
private:
    static std::string convertWithIconv(const std::string& input, const std::string&& fromEncoding, const std::string&& toEncoding);
};


#endif //BEMANIMETADATAPARSER_ENCODINGUTIL_HPP
