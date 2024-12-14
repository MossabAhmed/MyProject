#pragma once
#include "Event.h"
#include "Movie.h"
#include "Concert.h"
#include "Play.h"
#include <string>

class EventFactory {
public:
  

    static Event* createEvent(string type) {
        Event* event = nullptr;

        if (type == "Movie")
            event = new Movie();

        else if (type == "Concert")
            event = new Concert();

        else
            event = new Play;

        
        return event;
    }

    
};