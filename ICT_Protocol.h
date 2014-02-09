#ifndef ICT_PROTOCOL_INCLUDED
#define ICT_PROTOCOL_INCLUDED
#include <iostream>
#include <map>
#include <stdint.h>
#include <sstream>
#include "SerialPort.h"
#include "config.h"
#include "Logger.h"
#include "ConfigReader.h"
class ICT_Protocol{

public:

//    const ErrorList::value_type error[]={ std::make_pair(0x20, "Motor failure"),
//                                    std::make_pair(0x21,
//                                    std::make_pair(0x22, "Bill jam"),
//                                    std::make_pair(0x23, "Bill remove"),
//                                    std::make_pair(0x24, "Stacker open"),
//                                    std::make_pair(0x25, "Sensor problem"),
//                                    std::make_pair(0x27, "Bill fish"),
//                                    std::make_pair(0x28, "Stacker problem"),
//                                    std::make_pair(0x29, "Bill reject"),
//                                    std::make_pair(0x2A, "Invalid command"),
//                                    std::make_pair(0x2E, "Reserved"),
//                                    std::make_pair(0x2F, "Error status is exclusion")};

    enum CommunicationLineState{
        COMMUNICATION_STATE_UNKNOWN=2,
        COMMUNICATION_STATE_ALIVE=1,
        COMMUNICATION_STATE_BROKEN=0
    };

    enum DeviceEnableState{
        DEVICE_STATE_UNKNOWN=2,
        DEVICE_STATE_ENABLED=1,
        DEVICE_STATE_DISABLED=0
    };

    //Messages from the reader
    enum MessageCodesDevice{
        MSG_DEVICE_POWERUP=0x80,
        MSG_DEVICE_COMM_FAILURE=0x26,
        MSG_DEVICE_ESCROW=0x81,
        MSG_DEVICE_BILL_ACCEPT_FINISH=0x10,
        MSG_DEVICE_BILL_ACCEPT_FAILURE=0x11,
        MSG_DEVICE_STATUS_RESP_ENABLED=0x3e,
        MSG_DEVICE_STATUS_RESP_INHIBIT=0x5e
    };

    //messages from the driver
    enum MessageCodesController{
        MSG_CTRL_PWRUP_COMMFAIL_RESPONSE=0x02,
        MSG_CTRL_BILL_REQUEST_ACCEPT=0x02,
        MSG_CTRL_BILL_REQUEST_REJECT=0x0f,
        MSG_CTRL_ENABLE_ACCEPTOR_REQ=0x3e,
        MSG_CTRL_DISABLE_ACCEPTOR_REQ=0x5e,
        MSG_CTRL_STATUS_REQ=0x0C,
        MSG_CTRL_RESET_DEVICE=0x30
    };

    ICT_Protocol();
    bool init(string serialPortName);
    void run();


private:
    void die();
    bool portReadByte(unsigned char &data);
    bool sendMessage(ICT_Protocol::MessageCodesController messageCode);
    void parseInput(unsigned char data);
    bool sendEnableAcceptor();
    bool sendDisableAcceptor();

    CommunicationLineState commLineState;
    CommunicationLineState lastCommLineState;
    DeviceEnableState deviceInhibitState;
    DeviceEnableState lastDeviceInhibitState;
    uint32_t commErrorCounter;
    SerialPort port;
};
#endif
