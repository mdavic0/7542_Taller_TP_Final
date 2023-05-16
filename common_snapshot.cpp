#include "common_snapshot.h"
#include <string>
#include <iostream>
#include <sstream>

Snapshot::Snapshot(Event event, uint32_t code, uint8_t ok,  const std::string& str) :
    event(event), code(code), ok(ok), str(str) {}

Event Snapshot::getEvent() const {
    return event;
}

uint32_t Snapshot::getCode() const {
    return code;
}

uint8_t Snapshot::getOk() const {
    return ok;
}

std::string Snapshot::getStr() const {
    return str;
}

void Snapshot::print(const bool& showBroadcast) const {
    std::ostringstream print;

    if (event == Event::event_create) {
        print << "Created match: " << code << "\n";
    } else if (event == Event::event_join) {
        if (ok == 0x00) {
            print << "Joined to match: " << code << "\n";
        } else if (ok == 0x01) {
            print << "Match does not exist: " << code << "\n";
        }
    } else if (event == Event::event_broadcast && showBroadcast) {
        print << "Broadcasted: " << str << "\n";
    } else if (event == Event::event_invalid) {
        std::istringstream auxss(str);
        for (uint32_t i = 0; i < code; i++) {     // code is used as n, same type
            std::string auxstr;
            auxss >> auxstr;
            print << "Broadcasted: " << auxstr << "\n";
        }
    }
    std::string endPrint = print.str();
    if (endPrint.size() > 0) {
        std::cout << print.str();
    }
    return;
}

Snapshot::Snapshot(Snapshot&& other) {
    this->event = other.event;
    this->code = other.code;
    this->ok = other.ok;
    this->str = other.str;

    other.event = Event::event_invalid;
    other.code = 0;
    other.ok = 0;
    other.str = "";
}

Snapshot& Snapshot::operator=(Snapshot&& other) {
    if (this == &other)
        return *this;

    this->event = other.event;
    this->code = other.code;
    this->ok = other.ok;
    this->str = other.str;

    other.event = Event::event_invalid;
    other.code = 0;
    other.ok = 0;
    other.str = "";

    return *this;
}