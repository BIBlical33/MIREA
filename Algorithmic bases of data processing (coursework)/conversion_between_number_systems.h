#ifndef CONVERTER_CONVERSION_BETWEEN_NUMBER_SYSTEM_H_
#define CONVERTER_CONVERSION_BETWEEN_NUMBER_SYSTEM_H_

#include <map>
#include <string>

namespace conversion_between_number_systems {

// Converts a number from the original base to decimal (base 10)
std::string ConversionToDemical(const std::string& number, const int old_base,
                                const std::map<char, int>& dec_representation);

// Converts a decimal number to a specified new base
std::string DemicalToNewBase(
    int number, const int new_base,
    const std::map<int, char>& search_digits_by_dec_value);

// Converts a number between two different bases
std::string ConversionBetweenNumberSystems(std::string number,
                                           const int old_base,
                                           const int new_base);

}  // namespace conversion_between_number_systems

#endif  // CONVERTER_CONVERSION_BETWEEN_NUMBER_SYSTEM_H_