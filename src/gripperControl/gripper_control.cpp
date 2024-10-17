#include "gripper_control.h"
#include <ArduinoJson.h>

void GripperControl::action(JsonDocument messageJson) {
    if (messageJson["id"] == "arm") {
        if (messageJson["commands"] == "hold"){
            this->hold();
        }
        else if (messageJson["commands"] == "release") {
            this->release();
        }
        else if (messageJson["commands"] == "disable") {
            this->disable();
        }
    }
}

void GripperControl::hold() {
    relay.openA();
}

void GripperControl::release() {
    relay.openB();
}

void GripperControl::disable() {
    relay.disable();
}