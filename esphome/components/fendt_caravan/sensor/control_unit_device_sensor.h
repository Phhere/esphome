#pragma once

#ifdef USE_ESP32
#include "esphome/components/fendt_caravan/caravan_device_component.h"
#include "esphome/components/fendt_caravan/fendt_caravan.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/fendt_caravan/variable.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/core/string_ref.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "device_decoders.h"
#include "device_commands.h"
#include <functional>

namespace esphome::fendt_caravan {

class ControlUnitDeviceSensor : public CaravanDeviceComponent, public sensor::Sensor, public Parented<FendtCaravan> {
 public:
  void setup() override;
  void dump_config() override;
  void on_state_change_command(const std::string &tag, const std::string &command) override;
  SUB_SWITCH(main_switch);
  SUB_SENSOR(temp_in);
  SUB_SENSOR(temp_out);
  SUB_SENSOR(ibs0_ubat);
  SUB_SENSOR(ibs0_ibat);
  SUB_SENSOR(ibs0_capacity);
  SUB_SENSOR(ibs0_soc2);
  SUB_SENSOR(ibs0_remaining_time);
  SUB_SENSOR(ibs0_temp);
  SUB_TEXT_SENSOR(power_status);
  SUB_TEXT_SENSOR(software_version);
  SUB_SWITCH(all_lights);
  SUB_SWITCH(floor_heater);
  SUB_SWITCH(therme_on);
  SUB_SWITCH(light_dusche);
  SUB_SWITCH(light_wasch);
  SUB_SWITCH(light_amb1);
  SUB_SWITCH(light_amb2);
  SUB_SWITCH(light_amb3);
  SUB_SWITCH(light_zusatzl);
  SUB_SWITCH(light_zusatzr);
  SUB_SWITCH(light_kueche);
  SUB_SWITCH(light_kueche2);
  SUB_SWITCH(light_aussen);
  SUB_SWITCH(light_dim0);
  SUB_SWITCH(light_dim1);
  SUB_SWITCH(light_dim2);
  SUB_SWITCH(light_dim3);
  SUB_SWITCH(light_dim4);

  SUB_TEXT_SENSOR(panel_version);
  SUB_TEXT_SENSOR(latitude);
  SUB_TEXT_SENSOR(longitude);
  SUB_SENSOR(gsm_signal);
  SUB_SENSOR(vehicle_type);
  SUB_SENSOR(ibs0_recalibrated);
  SUB_SENSOR(ibs0_type);
  SUB_SENSOR(ibs0_available);
  SUB_TEXT_SENSOR(ac_dom_fj_fan_speed);
  SUB_TEXT_SENSOR(ac_dom_fj_enable);
  SUB_TEXT_SENSOR(ac_dom_fj_mode);
  SUB_SENSOR(ac_dom_fj_targettemp);
  SUB_SENSOR(ac_dom_fj_available);
  SUB_SENSOR(ultraheat_available);
  SUB_TEXT_SENSOR(ultraheat_onoff);
  SUB_SENSOR(ultraheat_power);
  SUB_SENSOR(ultraheat_temp);
  SUB_SENSOR(heater_available);
  SUB_SENSOR(heater_onoff);
  SUB_SENSOR(heater_temp);
  SUB_TEXT_SENSOR(heater_water);
  SUB_TEXT_SENSOR(heater_water_temp);
  SUB_TEXT_SENSOR(heater_el);
  SUB_TEXT_SENSOR(heater_gas);
  SUB_SENSOR(pi_pairing);
  SUB_SENSOR(light_busy);
  SUB_SENSOR(ac_truma_available);
  SUB_SENSOR(ac_truma_type);
  SUB_TEXT_SENSOR(ac_truma_enable);
  SUB_SENSOR(ac_truma_temp);
  SUB_SENSOR(ac_truma_mode);
  SUB_SENSOR(ac_truma_fan_level);
  SUB_SENSOR(ac_truma_light_on_off);
  SUB_SENSOR(ac_truma_light_dimmer);
  SUB_SENSOR(ac_truma_mm);
  SUB_SENSOR(th_available);
  SUB_SENSOR(tt_available);
  SUB_SENSOR(th_type);
  SUB_TEXT_SENSOR(th_a_en);
  SUB_TEXT_SENSOR(th_w_en);
  SUB_SENSOR(th_a_t);
  SUB_SENSOR(th_w_t);
  SUB_SENSOR(th_es);
  SUB_SENSOR(th_mm);
  SUB_SENSOR(sat_available);
  SUB_SENSOR(sat_type);
  SUB_SENSOR(sat_status);
  SUB_SENSOR(sat_advanced_status);
  SUB_SENSOR(sat_command);
  SUB_SENSOR(sat_lat);
  SUB_SENSOR(sat_lon);
  SUB_SENSOR(sat_orbital_postion);
  SUB_SENSOR(fridge_available);
  SUB_SENSOR(fridge_on_off);
  SUB_SENSOR(fridge_mode);
  SUB_SENSOR(fridge_source);
  SUB_SENSOR(fridge_temp);
  SUB_SENSOR(fridge_type);

 protected:
  void on_data_decoded(IVariable *variable) override;
};
}  // namespace esphome::fendt_caravan
#endif
