#include "conversion_between_number_systems.h"

#include <map>
#include <string>

namespace {

void FillingMapsOfDigits(std::map<char, int>& dec_representation,
                         std::map<int, char>& search_digits_by_dec_value) {
  for (int digit = 0; digit != 10; ++digit) {
    search_digits_by_dec_value[digit] = digit + '0';
    dec_representation[digit + '0'] = digit;
  }

  const int kA_ASCII_Index = 65, kF_ASCII_Index = 70;
  int dec_letter_representation = 10;

  for (char digit = kA_ASCII_Index; digit <= kF_ASCII_Index; ++digit) {
    search_digits_by_dec_value[dec_letter_representation] = digit;
    dec_representation[digit] = dec_letter_representation++;
  }
}

}  // namespace

namespace conversion_between_number_systems {

std::string ConversionToDemical(const std::string& number, const int old_base,
                                const std::map<char, int>& dec_representation) {
  if (old_base == 10) return number;

  int dec_number = 0, reverse_digit_index = 0;

  for (auto i = number.size() - 1; i >= 0; i--) {
    dec_number += dec_representation.at(number[i]) *
                  static_cast<int>(pow(old_base, reverse_digit_index));
    reverse_digit_index++;
  }

  return std::to_string(dec_number);
}

std::string DemicalToNewBase(
    int number, const int new_base,
    const std::map<int, char>& search_digits_by_dec_value) {
  if (new_base == 10) return std::to_string(number);

  std::string conversion_number;

  while (number > new_base - 1) {
    conversion_number += search_digits_by_dec_value.at(number % new_base);
    number /= new_base;
  }

  conversion_number += search_digits_by_dec_value.at(number);
  std::reverse(conversion_number.begin(), conversion_number.end());

  return conversion_number;
}

std::string ConversionBetweenNumberSystems(std::string number,
                                           const int old_base,
                                           const int new_base) {
  if (old_base < 2)
    return "Incorrect number system: " + std::to_string(old_base);
  if (new_base < 2)
    return "Incorrect number system: " + std::to_string(new_base);
  if (old_base > 16 || new_base > 16) return "Supports bases <= 16 only";

  static std::map<char, int> dec_representation;
  static std::map<int, char> search_digits_by_dec_value;

  if (static bool is_filling_maps_of_digits_called;
      !is_filling_maps_of_digits_called) {
    FillingMapsOfDigits(dec_representation, search_digits_by_dec_value);
    is_filling_maps_of_digits_called = true;
  }

  // Check for incorrect symbols in number
  for (auto ch : number) {
    if (dec_representation.count(ch) == 0 || dec_representation[ch] >= old_base)
      return "Incorrect number\n";
  }

  return DemicalToNewBase(
      std::stoi(ConversionToDemical(number, old_base, dec_representation)),
      new_base, search_digits_by_dec_value);
}

}  // namespace conversion_between_number_systems
