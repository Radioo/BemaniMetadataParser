//
// Created by Radio on 14/06/2024.
//

#ifndef BEMANIMETADATAPARSER_ENCODINGUTIL_HPP
#define BEMANIMETADATAPARSER_ENCODINGUTIL_HPP

#include <string>
#include <unordered_map>

class EncodingUtil {
public:
    static std::string convertSDVXMusicDbToUtf8(const std::string& input);
    static void replaceSdvxCharacters(std::string& input);
private:
    static inline const std::unordered_map<std::string, std::string> sdvxCharacterMap = {
            {"齷", "é"},
            {"齶", "♡"},
            {"齪", "♣"},
            {"齲", "♥"},
            {"～", "〜"},
            {"曦", "à"},
            {"曩", "è"},
            {"霻", "♠"},
            {"隯", "©"},
            {"鑈", "♦"},
            {"罇", "ê"},
            {"彜", "ū"},
            {"鬯", "ī"},
            {"瑟", "ō"},
            {"驩", "Ø"},
            {"驫", "ā"},
            {"骭", "ü"},
            {"黷", "ē"},
            {"頏", "♮"},
            {"騫", "á"},
            {"蹙", "ℱ"},
            {"趁", "Ǣ"},
            {"黻", "*"},
            {"雋", "Ǜ"},
            {"鬻", "♃"},
            {"鬥", "Ã"},
            {"鬆", "Ý"},
            {"鬮", "¡"},
            {"隍", "Ü"},
            {"頽", "ä"},
            {"龕", "€"},
            {"蹇", "₂"},
            {"釁", "🍄"},
            {"鑷", "ゔ"},
            {"盥", "⚙"},
            {"餮", "Ƶ"},
            {"蔕", "ῦ"},
            {"闃", "Ā"},
    };

    static std::string convertWithIconv(const std::string& input, const std::string&& fromEncoding, const std::string&& toEncoding);
    static void replaceXmlEncoding(std::string& input, std::string&& toEncoding);
};


#endif //BEMANIMETADATAPARSER_ENCODINGUTIL_HPP
