#include "control_unit_device_sensor.h"

#ifdef USE_ESP32
namespace esphome::fendt_caravan {
static const char *const TAG = "FC.CU";

void ControlUnitDeviceSensor::setup() {
  auto *network = new Variable<std::string>("LINE_EN", [](const std::string &value) {
    const char *tmp[] = {"Connected", "Disconnected"};
    return DeviceDecoders::decode_bool_str(value, tmp);
  });
  this->add_variable(network);

  auto *main_switch = new Variable<bool>("HS_EN", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(main_switch);

  auto *hs_key = new Variable<bool>("HS_KEY", nullptr, Commands::update_run);
  this->add_variable(hs_key);

  auto *hs_key_long = new Variable<bool>("HS_KEY_LONG", nullptr, Commands::update_run);
  this->add_variable(hs_key_long);

  auto *d_plus = new Variable<bool>("D_PLUS", DeviceDecoders::decode_bool);
  this->add_variable(d_plus);

  auto *battery_loading_status = new Variable<int>("IBAT_BAL", DeviceDecoders::decode_int);
  this->add_variable(battery_loading_status);

  auto *ac_active = new Variable<std::string>("AC_EN", [](const std::string &value) {
    const char *tmp[] = {"Enable", "Disable"};
    return DeviceDecoders::decode_bool_str(value, tmp);
  });
  this->add_variable(ac_active);

  auto *alarm_clock_active = new Variable<bool>("WAKE_EN", DeviceDecoders::decode_bool);
  this->add_variable(alarm_clock_active);

  auto *temp_in = new Variable<float>("TEMP_IN", DeviceDecoders::decode_temperature);
  this->add_variable(temp_in);

  auto *temp_out = new Variable<float>("TEMP_OUT", DeviceDecoders::decode_temperature);
  this->add_variable(temp_out);

  auto *battery_voltage = new Variable<float>("UBAT", DeviceDecoders::decode_voltage);
  this->add_variable(battery_voltage);

  auto *battery_voltage2 = new Variable<float>("UBATM", DeviceDecoders::decode_voltage);
  this->add_variable(battery_voltage2);

  auto *ibs0_ubat = new Variable<float>("IBS0_UBAT", DeviceDecoders::decode_voltage);
  this->add_variable(ibs0_ubat);

  auto *ibs0_ibat = new Variable<float>("IBS0_IBAT", DeviceDecoders::decode_ampere);
  this->add_variable(ibs0_ibat);

  auto *ibs0_temp = new Variable<float>("IBS0_TEMPERATURE", DeviceDecoders::decode_temperature);
  this->add_variable(ibs0_temp);

  auto *date = new Variable<time_t>("DATE", DeviceDecoders::decode_date);
  this->add_variable(date);

  auto *time = new Variable<time_t>("TIME", DeviceDecoders::decode_time);
  this->add_variable(time);

  auto *floor_heater =
      new Variable<bool>("FLOOR_HEATER_ON", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(floor_heater);

  auto *temp_in_offset = new Variable<int>("TEMP_IN_OFFSET", DeviceDecoders::decode_int);
  this->add_variable(temp_in_offset);

  auto *temp_out_offset = new Variable<int>("TEMP_OUT_OFFSET", DeviceDecoders::decode_int);
  this->add_variable(temp_out_offset);

  auto *software_version = new Variable<std::string>("SOFTWARE_VERSION", DeviceDecoders::decode_str);
  this->add_variable(software_version);

  auto *hs_key_state = new Variable<int>("HS_KEY_STATE", DeviceDecoders::decode_int);
  this->add_variable(hs_key_state);

  auto *th_error = new Variable<int>("TH_ERROR", DeviceDecoders::decode_int);
  this->add_variable(th_error);

  auto *trade_show = new Variable<int>("TRADE_SHOW", DeviceDecoders::decode_int);
  this->add_variable(trade_show);

  auto *therme_config = new Variable<int>("THERME_CONFIG", DeviceDecoders::decode_int);
  this->add_variable(therme_config);

  auto *therme_on = new Variable<bool>("THERME_ON", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(therme_on);

  auto *floor_heater_config =
      new Variable<bool>("FLOOR_HEATER_CONFIG", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(floor_heater_config);

  auto *waste_water_heater_config = new Variable<int>("WASTE_WATER_HEATER_CONFIG", DeviceDecoders::decode_int);
  this->add_variable(waste_water_heater_config);

  auto *radio_config = new Variable<bool>("RADIO_CONFIG", DeviceDecoders::decode_bool);
  this->add_variable(radio_config);

  auto *ibs0_capacity = new Variable<int>("IBS0_CAPACITY", DeviceDecoders::decode_int);
  this->add_variable(ibs0_capacity);

  auto *ibs0_soc2 = new Variable<float>("IBS0_SOC2", DeviceDecoders::decode_percentage);
  this->add_variable(ibs0_soc2);

  auto *ibs0_remaining_time = new Variable<float>("IBS0_REMAINING_TIME", [](const std::string &value) {
    std::string tmp = value;
    while (!tmp.empty() && std::isspace(static_cast<unsigned char>(tmp.front()))) tmp.erase(tmp.begin());
    while (!tmp.empty() && std::isspace(static_cast<unsigned char>(tmp.back()))) tmp.pop_back();
    const auto h_pos = tmp.find(" h");
    if (h_pos != std::string::npos) tmp.erase(h_pos, 2);
    const auto comma_pos = tmp.find(',');
    if (comma_pos != std::string::npos) tmp.replace(comma_pos, 1, ".");
    float v = 0.0f;
    auto [ptr, ec] = std::from_chars(tmp.data(), tmp.data() + tmp.size(), v);
    if (ec == std::errc() || ptr != tmp.data() + tmp.size())
      return 0.0f;
    return v;
  });
  this->add_variable(ibs0_remaining_time);

  auto *light_dusche = new Variable<bool>("LIGHT_DUSCHE", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(light_dusche);

  auto *light_wasch = new Variable<bool>("LIGHT_WASCH", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(light_wasch);

  auto *light_amb1 = new Variable<bool>("LIGHT_AMB1", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(light_amb1);

  auto *light_amb2 = new Variable<bool>("LIGHT_AMB2", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(light_amb2);

  auto *light_amb3 = new Variable<bool>("LIGHT_AMB3", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(light_amb3);

  auto *light_zusatzl = new Variable<bool>("LIGHT_ZUSATZL", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(light_zusatzl);

  auto *light_zusatzr = new Variable<bool>("LIGHT_ZUSATZR", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(light_zusatzr);

  auto *light_kueche = new Variable<bool>("LIGHT_KUECHE", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(light_kueche);

  auto *light_kueche2 = new Variable<bool>("LIGHT_KUECHE2", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(light_kueche2);

  auto *light_aussen = new Variable<bool>("LIGHT_AUSSEN", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(light_aussen);

  auto *light_dim0 = new Variable<bool>("LIGHT_DIM0", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(light_dim0);

  auto *light_dim1 = new Variable<bool>("LIGHT_DIM1", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(light_dim1);

  auto *light_dim2 = new Variable<bool>("LIGHT_DIM2", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(light_dim2);

  auto *light_dim3 = new Variable<bool>("LIGHT_DIM3", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(light_dim3);

  auto *light_dim4 = new Variable<bool>("LIGHT_DIM4", DeviceDecoders::decode_bool, Commands::update_toggle<bool>);
  this->add_variable(light_dim4);

  // Additional variables observed in device notifications
  auto *panel_version = new Variable<std::string>("PANEL_VERSION", DeviceDecoders::decode_str);
  this->add_variable(panel_version);

  auto *latitude = new Variable<std::string>("LATITUDE", DeviceDecoders::decode_str);
  this->add_variable(latitude);
  auto *longitude = new Variable<std::string>("LONGITUDE", DeviceDecoders::decode_str);
  this->add_variable(longitude);

  auto *gsm_signal = new Variable<int>("GSM_SIGNAL", DeviceDecoders::decode_int);
  this->add_variable(gsm_signal);
  auto *vehicle_type = new Variable<int>("VEHICLE_TYPE", DeviceDecoders::decode_int);
  this->add_variable(vehicle_type);

  auto *ibs0_recalibrated = new Variable<int>("IBS0_RECALIBRATED", DeviceDecoders::decode_int);
  this->add_variable(ibs0_recalibrated);
  auto *ibs0_type = new Variable<int>("IBS0_TYPE", DeviceDecoders::decode_int);
  this->add_variable(ibs0_type);
  auto *ibs0_available = new Variable<bool>("IBS0_AVAILABLE", DeviceDecoders::decode_bool);
  this->add_variable(ibs0_available);

  auto *ac_dom_fj_fan_speed = new Variable<std::string>("AC_DOM_FJ_FAN_SPEED", DeviceDecoders::decode_str);
  this->add_variable(ac_dom_fj_fan_speed);
  auto *ac_dom_fj_enable = new Variable<std::string>("AC_DOM_FJ_ENABLE", DeviceDecoders::decode_str);
  this->add_variable(ac_dom_fj_enable);
  auto *ac_dom_fj_mode = new Variable<std::string>("AC_DOM_FJ_MODE", DeviceDecoders::decode_str);
  this->add_variable(ac_dom_fj_mode);
  auto *ac_dom_fj_targettemp = new Variable<int>("AC_DOM_FJ_TARGETTEMP", DeviceDecoders::decode_int);
  this->add_variable(ac_dom_fj_targettemp);
  auto *ac_dom_fj_available = new Variable<bool>("AC_DOM_FJ_AVAILABLE", DeviceDecoders::decode_bool);
  this->add_variable(ac_dom_fj_available);

  auto *ultraheat_available = new Variable<bool>("ULTRAHEAT_AVAILABLE", DeviceDecoders::decode_bool);
  this->add_variable(ultraheat_available);
  auto *ultraheat_onoff = new Variable<std::string>("ULTRAHEAT_ONOFF", DeviceDecoders::decode_str);
  this->add_variable(ultraheat_onoff);
  auto *ultraheat_power = new Variable<int>("ULTRAHEAT_POWER", [](const std::string &v) {
    std::string tmp = v;
    // remove non-digit characters (e.g., " W") and commas
    for (auto it = tmp.begin(); it != tmp.end();) {
      if (*it == ',') it = tmp.erase(it);
      else if (!std::isdigit(static_cast<unsigned char>(*it)) && *it != '-' ) it = tmp.erase(it);
      else ++it;
    }
    int out = 0;
    auto [ptr, ec] = std::from_chars(tmp.data(), tmp.data() + tmp.size(), out);
    if (ec == std::errc() || ptr != tmp.data() + tmp.size())
      return 0;
    return out;
  });
  this->add_variable(ultraheat_power);
  auto *ultraheat_temp = new Variable<int>("ULTRAHEAT_TEMP", DeviceDecoders::decode_int);
  this->add_variable(ultraheat_temp);

  auto *heater_available = new Variable<bool>("HEATER_AVAILABLE", DeviceDecoders::decode_bool);
  this->add_variable(heater_available);
  auto *heater_onoff = new Variable<bool>("HEATER_ONOFF", DeviceDecoders::decode_bool);
  this->add_variable(heater_onoff);
  auto *heater_temp = new Variable<float>("HEATER_TEMP", DeviceDecoders::decode_temperature);
  this->add_variable(heater_temp);
  auto *heater_water = new Variable<std::string>("HEATER_WATER", DeviceDecoders::decode_str);
  this->add_variable(heater_water);
  auto *heater_water_temp = new Variable<std::string>("HEATER_WATER_TEMP", DeviceDecoders::decode_str);
  this->add_variable(heater_water_temp);
  auto *heater_el = new Variable<std::string>("HEATER_EL", DeviceDecoders::decode_heater_el);
  this->add_variable(heater_el);
  auto *heater_gas = new Variable<std::string>("HEATER_GAS", DeviceDecoders::decode_str);
  this->add_variable(heater_gas);

  auto *pi_pairing = new Variable<int>("PI_PAIRING", DeviceDecoders::decode_int);
  this->add_variable(pi_pairing);

  auto *light_busy = new Variable<int>("LIGHT_BUSY", DeviceDecoders::decode_int);
  this->add_variable(light_busy);

  auto *ac_truma_available = new Variable<bool>("AC_TRUMA_AVAILABLE", DeviceDecoders::decode_bool);
  this->add_variable(ac_truma_available);
  auto *ac_truma_type = new Variable<int>("AC_TRUMA_TYPE", DeviceDecoders::decode_int);
  this->add_variable(ac_truma_type);
  auto *ac_truma_enable = new Variable<std::string>("AC_TRUMA_ENABLE", DeviceDecoders::decode_str);
  this->add_variable(ac_truma_enable);
  auto *ac_truma_temp = new Variable<int>("AC_TRUMA_TEMP", DeviceDecoders::decode_int);
  this->add_variable(ac_truma_temp);
  auto *ac_truma_mode = new Variable<int>("AC_TRUMA_MODE", DeviceDecoders::decode_int);
  this->add_variable(ac_truma_mode);
  auto *ac_truma_fan_level = new Variable<int>("AC_TRUMA_FAN_LEVEL", DeviceDecoders::decode_int);
  this->add_variable(ac_truma_fan_level);
  auto *ac_truma_light_on_off = new Variable<int>("AC_TRUMA_LIGHT_ON_OFF", DeviceDecoders::decode_int);
  this->add_variable(ac_truma_light_on_off);
  auto *ac_truma_light_dimmer = new Variable<int>("AC_TRUMA_LIGHT_DIMMER", DeviceDecoders::decode_int);
  this->add_variable(ac_truma_light_dimmer);
  auto *ac_truma_mm = new Variable<int>("AC_TRUMA_MM", DeviceDecoders::decode_int);
  this->add_variable(ac_truma_mm);

  auto *th_available = new Variable<int>("TH_AVAILABLE", DeviceDecoders::decode_int);
  this->add_variable(th_available);
  auto *tt_available = new Variable<int>("TT_AVAILABLE", DeviceDecoders::decode_int);
  this->add_variable(tt_available);
  auto *th_type = new Variable<int>("TH_TYPE", DeviceDecoders::decode_int);
  this->add_variable(th_type);
  auto *th_a_en = new Variable<std::string>("TH_A_EN", DeviceDecoders::decode_str);
  this->add_variable(th_a_en);
  auto *th_w_en = new Variable<std::string>("TH_W_EN", DeviceDecoders::decode_str);
  this->add_variable(th_w_en);
  auto *th_a_t = new Variable<float>("TH_A_T", DeviceDecoders::decode_temperature);
  this->add_variable(th_a_t);
  auto *th_w_t = new Variable<float>("TH_W_T", DeviceDecoders::decode_temperature);
  this->add_variable(th_w_t);
  auto *th_es = new Variable<int>("TH_ES", DeviceDecoders::decode_int);
  this->add_variable(th_es);
  auto *th_mm = new Variable<int>("TH_MM", DeviceDecoders::decode_int);
  this->add_variable(th_mm);

  auto *sat_available = new Variable<int>("SAT_AVAILABLE", DeviceDecoders::decode_int);
  this->add_variable(sat_available);
  auto *sat_type = new Variable<int>("SAT_TYPE", DeviceDecoders::decode_int);
  this->add_variable(sat_type);
  auto *sat_status = new Variable<int>("SAT_STATUS", DeviceDecoders::decode_int);
  this->add_variable(sat_status);
  auto *sat_advanced_status = new Variable<int>("SAT_ADVANCED_STATUS", DeviceDecoders::decode_int);
  this->add_variable(sat_advanced_status);
  auto *sat_command = new Variable<int>("SAT_COMMAND", DeviceDecoders::decode_int);
  this->add_variable(sat_command);
  auto *sat_lat = new Variable<int>("SAT_LAT", DeviceDecoders::decode_int);
  this->add_variable(sat_lat);
  auto *sat_lon = new Variable<int>("SAT_LON", DeviceDecoders::decode_int);
  this->add_variable(sat_lon);
  auto *sat_orbital_postion = new Variable<int>("SAT_ORBITAL_POSTION", DeviceDecoders::decode_int);
  this->add_variable(sat_orbital_postion);

  auto *fridge_available = new Variable<int>("FRIDGE_AVAILABLE", DeviceDecoders::decode_int);
  this->add_variable(fridge_available);
  auto *fridge_on_off = new Variable<int>("FRIDGE_ON_OFF", DeviceDecoders::decode_int);
  this->add_variable(fridge_on_off);
  auto *fridge_mode = new Variable<int>("FRIDGE_MODE", DeviceDecoders::decode_int);
  this->add_variable(fridge_mode);
  auto *fridge_source = new Variable<int>("FRIDGE_SOURCE", DeviceDecoders::decode_int);
  this->add_variable(fridge_source);
  auto *fridge_temp = new Variable<int>("FRIDGE_TEMP", DeviceDecoders::decode_int);
  this->add_variable(fridge_temp);
  auto *fridge_type = new Variable<int>("FRIDGE_TYPE", DeviceDecoders::decode_int);
  this->add_variable(fridge_type);
}

void ControlUnitDeviceSensor::dump_config() {
  ESP_LOGCONFIG(TAG, "Fendt Control Unit");
  LOG_SWITCH(TAG, "  Main Switch", this->main_switch_switch_);
  LOG_SWITCH(TAG, "  All Lights Status", this->all_lights_switch_);
  LOG_SENSOR(TAG, "  Temp In", this->temp_in_sensor_);
  LOG_SENSOR(TAG, "  Temp Out", this->temp_out_sensor_);
  LOG_SENSOR(TAG, "  IBS0 UBAT", this->ibs0_ubat_sensor_);
  LOG_SENSOR(TAG, "  IBS0 Capacity", this->ibs0_capacity_sensor_);
  LOG_SENSOR(TAG, "  IBS0 IBAT", this->ibs0_ibat_sensor_);
  LOG_SENSOR(TAG, "  IBS0 SOC2", this->ibs0_soc2_sensor_);
  LOG_SENSOR(TAG, "  IBS0 Remaining Time", this->ibs0_remaining_time_sensor_);
  LOG_SENSOR(TAG, "  IBS0 Temp", this->ibs0_temp_sensor_);
  LOG_TEXT_SENSOR(TAG, "  Power Status", this->power_status_text_sensor_);
  LOG_TEXT_SENSOR(TAG, "  Software Version", this->software_version_text_sensor_);
  LOG_SWITCH(TAG, "  Floor Heater", this->floor_heater_switch_);
  LOG_SWITCH(TAG, "  Therme On", this->therme_on_switch_);
  LOG_SWITCH(TAG, "  Light Dusche", this->light_dusche_switch_);
  LOG_SWITCH(TAG, "  Light Wasch", this->light_wasch_switch_);
  LOG_SWITCH(TAG, "  Light Amb1", this->light_amb1_switch_);
  LOG_SWITCH(TAG, "  Light Amb2", this->light_amb2_switch_);
  LOG_SWITCH(TAG, "  Light Amb3", this->light_amb3_switch_);
  LOG_SWITCH(TAG, "  Light Zusatz L", this->light_zusatzl_switch_);
  LOG_SWITCH(TAG, "  Light Zusatz R", this->light_zusatzr_switch_);
  LOG_SWITCH(TAG, "  Light Kueche", this->light_kueche_switch_);
  LOG_SWITCH(TAG, "  Light Kueche2", this->light_kueche2_switch_);
  LOG_SWITCH(TAG, "  Light Aussen", this->light_aussen_switch_);
  LOG_SWITCH(TAG, "  Light Dim0", this->light_dim0_switch_);
  LOG_SWITCH(TAG, "  Light Dim1", this->light_dim1_switch_);
  LOG_SWITCH(TAG, "  Light Dim2", this->light_dim2_switch_);
  LOG_SWITCH(TAG, "  Light Dim3", this->light_dim3_switch_);
  LOG_SWITCH(TAG, "  Light Dim4", this->light_dim4_switch_);

  // Log all internal variables
  for (auto *var : this->variables_) {
    ESP_LOGCONFIG(TAG, "  Variable '%s': raw='%s', decoded='%s', active=%s",
                  var->get_name().c_str(), var->get_raw_value().c_str(), var->get_value_str().c_str(), var->is_active() ? "yes" : "no");
  }
}

void ControlUnitDeviceSensor::on_data_decoded(IVariable *variable) {
  if (this->main_switch_switch_ && variable->get_name() == "HS_KEY_STATE") {
    auto *hs_key_state = static_cast<Variable<int> *>(variable);
    if (hs_key_state->is_active()) {
      if (this->main_switch_switch_)
        this->main_switch_switch_->publish_state(hs_key_state->get_value() > 0);
      if (this->all_lights_switch_)
        this->all_lights_switch_->publish_state(hs_key_state->get_value() == 2);
    }
  }
}

void ControlUnitDeviceSensor::on_state_change_command(const std::string &tag, const std::string &command) {
  std::string cmd = command;
  if (tag == "MAIN_SWITCH") {
    auto *hs_key_long = GET_VARIABLE(bool, "HS_KEY_LONG");
    auto *hs_key_state = GET_VARIABLE(int, "HS_KEY_STATE");
    if (!(hs_key_long && hs_key_state)) {
      ESP_LOGW(TAG, "HS_KEY_LONG or HS_KEY_STATE not available");
      return;
    }
    bool current_state = hs_key_state->get_value() > 0;
    ESP_LOGV(TAG, "Main switch state changed. cs: %s", ONOFF(current_state));
    if (current_state) {
      hs_key_long->set_value(true);
      cmd = hs_key_long->get_command();
    } else {
      auto *hs_key = GET_VARIABLE(bool, "HS_KEY");
      if (hs_key) {
        hs_key->set_value(true);
        cmd = hs_key->get_command();
      }
    }
  } else if (tag == "ALL_LIGHTS_SWITCH") {
    auto *hs_key = GET_VARIABLE(bool, "HS_KEY");
    auto *hs_key_state = GET_VARIABLE(int, "HS_KEY_STATE");
    if (!(hs_key && hs_key_state)) {
      ESP_LOGW(TAG, "HS_KEY or HS_KEY_STATE not available");
      return;
    }
    bool current_state = hs_key_state->get_value() == 2;
    ESP_LOGV(TAG, "Light switch state changed. cs: %s", ONOFF(current_state));
    cmd = hs_key->get_command();
  }
  if (!cmd.empty()) {
    ESP_LOGV(TAG, "Switch state changed command:%s", cmd.c_str());
    this->command_callback_.call(cmd);
  }
}
}  // namespace esphome::fendt_caravan
#endif
