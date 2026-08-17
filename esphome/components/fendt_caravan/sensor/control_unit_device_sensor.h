#pragma once

#ifdef USE_ESP32
#include "esphome/components/fendt_caravan/caravan_device_component.h"
#include "esphome/components/fendt_caravan/fendt_caravan.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/fendt_caravan/variable.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/core/application.h"
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
  void set_auto_report_entities(bool enabled) { this->auto_report_entities_ = enabled; }
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

 protected:
  void on_data_decoded(IVariable *variable) override;
  template<typename T>
  void add_auto_report_sensor_(Variable<T> *variable) {
    auto *entity = new sensor::Sensor();
    entity->set_name(variable->get_name());
    entity->set_unique_id("fendt_caravan_" + variable->get_name());
    App.register_component(entity);
    variable->set_on_decode_callback([entity](const T &value) { entity->publish_state(value); });
  }
  void add_auto_report_switch_(Variable<bool> *variable) {
    auto *entity = new switch::Switch();
    entity->set_name(variable->get_name());
    entity->set_unique_id("fendt_caravan_" + variable->get_name());
    App.register_component(entity);
    variable->set_on_decode_callback([entity](const bool &value) { entity->publish_state(value); });
  }
  void add_auto_report_text_sensor_(Variable<std::string> *variable) {
    auto *entity = new text_sensor::TextSensor();
    entity->set_name(variable->get_name());
    entity->set_unique_id("fendt_caravan_" + variable->get_name());
    App.register_component(entity);
    variable->set_on_decode_callback([entity](const std::string &value) { entity->publish_state(value); });
  }
  void add_auto_report_entities_();

  bool auto_report_entities_{true};
};
}  // namespace esphome::fendt_caravan
#endif
