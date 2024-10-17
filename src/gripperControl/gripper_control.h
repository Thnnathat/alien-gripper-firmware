#ifndef GRIPPER_CONTROL_H
    #define GRIPPER_CONTROL_H
    #include <ArduinoJson.h>
    #include "relayControl/relay_control.h"
    class GripperControl {
        private:
            RelayControl relay;

        public:
            JsonDocument messageJson;
            GripperControl(RelayControl relay) {
                relay = relay;
            }
            void action(JsonDocument messageJson);
            void hold();
            void release();
            void disable();
    };
#endif