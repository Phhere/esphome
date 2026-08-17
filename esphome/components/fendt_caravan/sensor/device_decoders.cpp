#include "device_decoders.h"

#include <algorithm> 
#include <cctype>
#include <string>

// Trim from the start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// Trim from the end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// Trim from both ends (in place)
inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}


#ifdef USE_ESP32
namespace esphome::fendt_caravan {
static const char *const TAG = "FC.COD";

float DeviceDecoders::decode_temperature(const std::string &data) {
  std::string value = data;
  size_t start = value.find("^C");
  if (start != std::string::npos)
    value.replace(start, 2, "");
  start = value.find(',');
  if (start != std::string::npos)
    value.replace(start, 1, ".");
  return std::stof(value);
}
float DeviceDecoders::decode_voltage(const std::string &data) {
  std::string value = data;
  size_t start = value.find(" V");
  if (start != std::string::npos)
    value.replace(start, 2, "");
  start = value.find(',');
  if (start != std::string::npos)
    value.replace(start, 1, ".");
  trim(value);
  auto result = parse_data<float>(value);
  if (!result) {
    ESP_LOGE(TAG, "Data parse error. Data: %s", value.c_str());
    return 0.0f;
  }
  return result.value();
}

float DeviceDecoders::decode_ampere(const std::string &data) {
  std::string value = data;
  size_t start = value.find(" A");
  if (start != std::string::npos)
    value.replace(start, 2, "");
  start = value.find(',');
  if (start != std::string::npos)
    value.replace(start, 1, ".");
  trim(value);
  auto result = parse_data<float>(value);
  if (!result) {
    ESP_LOGE(TAG, "Data parse error. Data: %s", value.c_str());
    return 0.0f;
  }
  return result.value();
}


float DeviceDecoders::decode_percentage(const std::string &data) {
  std::string value = data;
  size_t start = value.find('%');
  if (start != std::string::npos)
    value.replace(start, 1, "");
  start = value.find(',');
  if (start != std::string::npos)
    value.replace(start, 1, ".");
  trim(value);
  auto result = parse_data<float>(value);
  if (!result) {
    ESP_LOGE(TAG, "Data parse error. Data: %s", value.c_str());
    return 0.0f;
  }
  return result.value();
}

int DeviceDecoders::decode_int(const std::string &data) {
  auto result = parse_data<int>(data);
  if (!result) {
    ESP_LOGE(TAG, "Data parse error. Data: %s", data.c_str());
    return 0;
  }
  return result.value();
}

time_t DeviceDecoders::decode_date(const std::string &data) {
  std::istringstream date(data);
  tm tm = {};
  date >> std::get_time(&tm, "%d.%m.%y");
  if (date.fail()) {
    ESP_LOGE(TAG, "Date Parsing failed");
    return 0;
  }
  time_t ret = mktime(&tm);
  return ret;
}
time_t DeviceDecoders::decode_time(const std::string &data) {
  std::istringstream date(data);
  tm tm = {};
  date >> std::get_time(&tm, "%H:%M:%S");
  if (date.fail()) {
    ESP_LOGE(TAG, "Date Parsing failed");
    return 0;
  }
  time_t ret = mktime(&tm);
  return ret;
}
std::string DeviceDecoders::decode_int_str(const std::string &data, const std::vector<std::string> &list) {
  auto result = parse_data<int>(data);
  if (!result) {
    ESP_LOGE(TAG, "Data parse error. Data: %s", data.c_str());
    return "";
  }
  int val = result.value();
  return list.at(val);
}

template<typename T> std::optional<T> DeviceDecoders::parse_data(const std::string &str) {
  T value;
  auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value);

  if (ec == std::errc() && ptr == str.data() + str.size()) {
    return value;
  }
  return std::nullopt;
}
}  // namespace esphome::fendt_caravan
#endif
