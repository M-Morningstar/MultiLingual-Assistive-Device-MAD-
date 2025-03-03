/**
 * @brief languageCodes.cpp class for keeping and comparing all language codes in translations
 * @authors Mert Osoydan
*/

#include "languageCodes.h"

using namespace std;

// Declare a map to hold language names and their ISO 639-1 codes
std::map<std::string, std::string> languageMap = {
    {"Abkhazian", "AB"},
    {"Afar", "AA"},
    {"Afrikaans", "AF"},
    {"Albanian", "SQ"},
    {"Amharic", "AM"},
    {"Arabic", "AR"},
    {"Armenian", "HY"},
    {"Assamese", "AS"},
    {"Aymara", "AY"},
    {"Azerbaijani", "AZ"},
    {"Bashkir", "BA"},
    {"Basque", "EU"},
    {"Bengali, Bangla", "BN"},
    {"Bhutani", "DZ"},
    {"Bihari", "BH"},
    {"Bislama", "BI"},
    {"Breton", "BR"},
    {"Bulgarian", "BG"},
    {"Burmese", "MY"},
    {"Byelorussian", "BE"},
    {"Cambodian", "KM"},
    {"Catalan", "CA"},
    {"Chinese", "ZH"},
    {"Corsican", "CO"},
    {"Croatian", "HR"},
    {"Czech", "CS"},
    {"Danish", "DA"},
    {"Dutch", "NL"},
    {"English, American", "EN"},
    {"Esperanto", "EO"},
    {"Estonian", "ET"},
    {"Faeroese", "FO"},
    {"Fiji", "FJ"},
    {"Finnish", "FI"},
    {"French", "FR"},
    {"Frisian", "FY"},
    {"Gaelic (Scots Gaelic)", "GD"},
    {"Galician", "GL"},
    {"Georgian", "KA"},
    {"German", "DE"},
    {"Greek", "EL"},
    {"Greenlandic", "KL"},
    {"Guarani", "GN"},
    {"Gujarati", "GU"},
    {"Hausa", "HA"},
    {"Hebrew", "IW"},
    {"Hindi", "HI"},
    {"Hungarian", "HU"},
    {"Icelandic", "IS"},
    {"Indonesian", "IN"},
    {"Interlingua", "IA"},
    {"Interlingue", "IE"},
    {"Inupiak", "IK"},
    {"Irish", "GA"},
    {"Italian", "IT"},
    {"Japanese", "JA"},
    {"Javanese", "JW"},
    {"Kannada", "KN"},
    {"Kashmiri", "KS"},
    {"Kazakh", "KK"},
    {"Kinyarwanda", "RW"},
    {"Kirghiz", "KY"},
    {"Kirundi", "RN"},
    {"Korean", "KO"},
    {"Kurdish", "KU"},
    {"Laothian", "LO"},
    {"Latin", "LA"},
    {"Latvian, Lettish", "LV"},
    {"Lingala", "LN"},
    {"Lithuanian", "LT"},
    {"Macedonian", "MK"},
    {"Malagasy", "MG"},
    {"Malay", "MS"},
    {"Malayalam", "ML"},
    {"Maltese", "MT"},
    {"Maori", "MI"},
    {"Marathi", "MR"},
    {"Moldavian", "MO"},
    {"Mongolian", "MN"},
    {"Nauru", "NA"},
    {"Nepali", "NE"},
    {"Norwegian", "NO"},
    {"Occitan", "OC"},
    {"Oriya", "OR"},
    {"Oromo, Afan", "OM"},
    {"Pashto, Pushto", "PS"},
    {"Persian", "FA"},
    {"Polish", "PL"},
    {"Portuguese", "PT"},
    {"Punjabi", "PA"},
    {"Quechua", "QU"},
    {"Rhaeto-Romance", "RM"},
    {"Romanian", "RO"},
    {"Russian", "RU"},
    {"Samoan", "SM"},
    {"Sangro", "SG"},
    {"Sanskrit", "SA"},
    {"Serbian", "SR"},
    {"Serbo-Croatian", "SH"},
    {"Sesotho", "ST"},
    {"Setswana", "TN"},
    {"Shona", "SN"},
    {"Sindhi", "SD"},
    {"Singhalese", "SI"},
    {"Siswati", "SS"},
    {"Slovak", "SK"},
    {"Slovenian", "SL"},
    {"Somali", "SO"},
    {"Spanish", "ES"},
    {"Sudanese", "SU"},
    {"Swahili", "SW"},
    {"Swedish", "SV"},
    {"Tagalog", "TL"},
    {"Tajik", "TG"},
    {"Tamil", "TA"},
    {"Tatar", "TT"},
    {"Tegulu", "TE"},
    {"Thai", "TH"},
    {"Tibetan", "BO"},
    {"Tigrinya", "TI"},
    {"Tonga", "TO"},
    {"Tsonga", "TS"},
    {"Turkish", "TR"},
    {"Turkmen", "TK"},
    {"Twi", "TW"},
    {"Ukrainian", "UK"},
    {"Urdu", "UR"},
    {"Uzbek", "UZ"},
    {"Vietnamese", "VI"},
    {"Volapuk", "VO"},
    {"Welsh", "CY"},
    {"Wolof", "WO"},
    {"Xhosa", "XH"},
    {"Yiddish", "JI"},
    {"Yoruba", "YO"},
    {"Zulu", "ZU"},
};

/**
 * @brief isValidLanguageCode checks if a given code is a valid ISO 639-1 language code in the map
 * @param code The language code having it's validity verified
 * @returns a boolean for if the lanuage provided is valid or invalid
 * @authors Mert Osoydan
*/
bool isValidLanguageCode(const std::string& code) {
    std::string lowerCode = code;
    // Convert the parameter to lowercase
    std::transform(lowerCode.begin(), lowerCode.end(), lowerCode.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    // Compare code to the codes in the map
    for (const auto& pair : languageMap) {
        std::string lowerMapCode = pair.second;
        // Convert the code in the map to lowercase
        std::transform(lowerMapCode.begin(), lowerMapCode.end(), lowerMapCode.begin(),
                       [](unsigned char c){ return std::tolower(c); });

        if (lowerMapCode == lowerCode) {
            return true; // Found a matching language code
        }
    }
    return false; // No matching language code found
}

/**
 * @brief convertToGoogleVoiceFormat converts language code to google's version of a language code
 * @param isoCode The language code to be converted into a google language code
 * @returns a string representing the new code that will be used to identify the selected language
 * @authors Mert Osoydan
*/
std::string convertToGoogleVoiceFormat(const std::string& isoCode) {
    std::map<std::string, std::string> googleVoiceFormat = {
    {"ar", "ar-XA"}, // Arabic
    {"cs", "cs-CZ"}, // Czech
    {"da", "da-DK"}, // Danish
    {"nl", "nl-NL"}, // Dutch
    {"en", "en-US"}, // English (US)
    {"fil", "fil-PH"}, // Filipino
    {"fi", "fi-FI"}, // Finnish
    {"fr", "fr-FR"}, // French
    {"de", "de-DE"}, // German
    {"el", "el-GR"}, // Greek
    {"hi", "hi-IN"}, // Hindi
    {"hu", "hu-HU"}, // Hungarian
    {"id", "id-ID"}, // Indonesian
    {"it", "it-IT"}, // Italian
    {"ja", "ja-JP"}, // Japanese
    {"ko", "ko-KR"}, // Korean
    {"cmn", "cmn-CN"}, // Mandarin Chinese
    {"nb", "nb-NO"}, // Norwegian
    {"pl", "pl-PL"}, // Polish
    {"pt", "pt-BR"}, // Portuguese (Brazil)
    {"ru", "ru-RU"}, // Russian
    {"sk", "sk-SK"}, // Slovak
    {"es", "es-ES"}, // Spanish (Spain)
    {"sv", "sv-SE"}, // Swedish
    {"th", "th-TH"}, // Thai
    {"tr", "tr-TR"}, // Turkish
    {"uk", "uk-UA"}, // Ukrainian
    {"vi", "vi-VN"}, // Vietnamese
};

    // Check for compare code in the google format map
    auto it = googleVoiceFormat.find(isoCode);
    if (it != googleVoiceFormat.end()) {
        return it->second;
    } else {
        std::cerr << "No Google Voice format found for ISO code: " << isoCode << std::endl;
        return "";
    }
}

