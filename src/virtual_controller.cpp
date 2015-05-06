#include "virtual_controller.h"
#include "lms/datamanager.h"
#include "gamepad/gamepad.h"

#include <cmath>

bool VirtualController::initialize(){
    config = getConfig();
    maxFrontServoRange = config->get<int>("maxFrontServoRange");
    maxMotorRange = config->get<int>("maxMotorRange");

    senseBoard = datamanager()
            ->writeChannel<sense_link::SenseBoard>(this, "SENSE_BOARD");
    gamePad = datamanager()
            ->readChannel<Gamepad>(this,"360");
    return true;
}

bool VirtualController::cycle(){
    using sense_link::SensorData;

    static int16_t servoValue = 0;
    static int16_t motorValue = 0;

    // get axis from gamePad LS -> LeftStick value (LS.x,LS.y)
    Gamepad::axis ls = gamePad->getAxis("LS");
    Gamepad::axis rt = gamePad->getAxis("RT");
    Gamepad::axis lt = gamePad->getAxis("LT");

    // generates values between -10000 and 10000
    servoValue = (int) (ls.x*maxMotorRange);
    motorValue = ((rt.x-lt.x)*maxMotorRange/2); // 10000/2 => (rt.x-lt.x = 2)


    logger.warn("cycle") << "ServoValue: " << servoValue;
    SensorData data;

    data.MotorVelocity.acceleration = motorValue;
    senseBoard->setSensor(sense_link::MOTOR_VELOCITY,1,data);

    data.Servo.angle = servoValue;
    senseBoard->setSensor(sense_link::SERVO,1,data);
    return true;
}

bool VirtualController::deinitialize(){
    return true;
}
