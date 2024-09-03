#ifndef INCLUDE_ECODAN_HEATPUMP_H
#define INCLUDE_ECODAN_HEATPUMP_H

#include "esphome/core/component.h"
#include "esphome/components/number/number.h"
#include "esphome/components/select/select.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/log.h"
#include "esphome/core/defines.h"
#include "commands.h"
#include "fields.h"
#include "parser.h"
#include <string>
#define CONNECT_LEN 8
#define HEADER_LEN 8
#define RCVD_PKT_FAIL 0
#define RCVD_PKT_CONNECT_SUCCESS 1
#define POLL_INTERVAL 10000 // 10 seconds
#define READOUT_DELAY 100 // 100 ms

namespace esphome {
namespace ecodan_ {

using namespace ecodan::fields;
using namespace ecodan::commands;
using namespace ecodan::parser;

using std::string;

const uint8_t CONNECT[CONNECT_LEN] = {0xfc, 0x5a, 0x02, 0x7a, 0x02, 0xca, 0x01, 0x5d};

// ECODAN_**_LIST generated by ESPHome and written in esphome/core/defines

#ifndef ECODAN_SENSOR_LIST
#define ECODAN_SENSOR_LIST(F, SEP)
#endif

#ifndef ECODAN_TEXT_SENSOR_LIST
#define ECODAN_TEXT_SENSOR_LIST(F, SEP)
#endif

#ifndef ECODAN_SWITCH_LIST
#define ECODAN_SWITCH_LIST(F, SEP)
#endif

#ifndef ECODAN_SELECT_LIST
#define ECODAN_SELECT_LIST(F, SEP)
#endif

#ifndef ECODAN_NUMBER_LIST
#define ECODAN_NUMBER_LIST(F, SEP)
#endif

#define ECODAN_DATA_SENSOR(s) s
#define COMMA ,

class EcodanHeatpump;
class EcodanSwitch : public switch_::Switch, public Component {
  public:
    void dump_config() override;
    void set_key(string key) {this->key_ = key;}
    void set_heatpump(EcodanHeatpump* heatpump) {this->heatpump_ = heatpump;}

  protected:
    void write_state(bool state) override;

    string key_;
    EcodanHeatpump* heatpump_;
};

class EcodanSelect: public select::Select, public Component {
  public:
    void dump_config() override;
    void set_key(string key) {this->key_ = key;}
    void set_heatpump(EcodanHeatpump* heatpump) {this->heatpump_ = heatpump;}

  protected:
    void control(const std::string &value) override;

    string key_;
    EcodanHeatpump* heatpump_;
};

class EcodanNumber: public number::Number, public Component {
  public:
    void dump_config() override;
    void set_key(string key) {this->key_ = key;}
    void set_heatpump(EcodanHeatpump* heatpump) {this->heatpump_ = heatpump;}

  protected:
    void control(float value) override;

    string key_;
    EcodanHeatpump* heatpump_;
};

class EcodanHeatpump : public PollingComponent, public uart::UARTDevice {
  public:

    EcodanHeatpump (uart::UARTComponent *parent);

    void setup() override;

    void update() override;

    void dump_config() override;

    void setRemoteTemperature(float value);

    // Sensor setters
#define ECODAN_SET_SENSOR(s) \
    void set_##s(sensor::Sensor* sensor) { s_##s##_ = sensor; }
    ECODAN_SENSOR_LIST(ECODAN_SET_SENSOR, )

#define ECODAN_SET_TEXT_SENSOR(ts) \
    void set_##ts(text_sensor::TextSensor* text_sensor) { ts_##ts##_ = text_sensor; }
    ECODAN_TEXT_SENSOR_LIST(ECODAN_SET_TEXT_SENSOR, )

    // Switch setters
#define ECODAN_SET_SWITCH(sw) \
    void set_##sw(EcodanSwitch* ecodanSwitch) { sw_##sw##_ = ecodanSwitch; ecodanSwitch->set_heatpump(this); }
    ECODAN_SWITCH_LIST(ECODAN_SET_SWITCH, )

    // Select setters
#define ECODAN_SET_SELECT(sl) \
    void set_##sl(EcodanSelect* ecodanSelect) { sl_##sl##_ = ecodanSelect; ecodanSelect->set_heatpump(this); }
    ECODAN_SELECT_LIST(ECODAN_SET_SELECT, )

    // Number setters
#define ECODAN_SET_NUMBER(nb) \
    void set_##nb(EcodanNumber* ecodanNumber) { nb_##nb##_ = ecodanNumber; ecodanNumber->set_heatpump(this); }
    ECODAN_NUMBER_LIST(ECODAN_SET_NUMBER, )

    void sendSerialPacket(uint8_t *sendBuffer);

  private:
    bool isInitialized = false;
    int currentState = 0;
    void initialize();

    void receiveSerialPacket();

    int readPacket(uint8_t *data);
    
    static uint8_t calculateCheckSum(uint8_t *data);

    void parsePacket(uint8_t *packet);

    // Sensor member pointers
#define ECODAN_DECLARE_SENSOR(s) sensor::Sensor* s_##s##_{nullptr};
    ECODAN_SENSOR_LIST(ECODAN_DECLARE_SENSOR, )

#define ECODAN_DECLARE_TEXT_SENSOR(ts) text_sensor::TextSensor* ts_##ts##_{nullptr};
    ECODAN_TEXT_SENSOR_LIST(ECODAN_DECLARE_TEXT_SENSOR, )

    // Switch member pointers
#define ECODAN_DECLARE_SWITCH(sw) EcodanSwitch* sw_##sw##_{nullptr};
    ECODAN_SWITCH_LIST(ECODAN_DECLARE_SWITCH, )

    // Select member pointers
#define ECODAN_DECLARE_SELECT(sl) EcodanSelect* sl_##sl##_{nullptr};
    ECODAN_SELECT_LIST(ECODAN_DECLARE_SELECT, )

    // Number member pointers
#define ECODAN_DECLARE_NUMBER(nb) EcodanNumber* nb_##nb##_{nullptr};
    ECODAN_NUMBER_LIST(ECODAN_DECLARE_NUMBER, )
};

} // namespace ecodan_
} // namespace esphome

#endif // INCLUDE_ECODAN_HEATPUMP_H