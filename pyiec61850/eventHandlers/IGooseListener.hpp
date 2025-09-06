#ifndef PYIEC61850_IGOOSELISTENER_HPP
#define PYIEC61850_IGOOSELISTENER_HPP

#include "goose_subscriber.h"

class IGooseListener {

public:
    static void listenerCallback(GooseSubscriber subscriber, void *parameter)
    {
        IGooseListener* listener = reinterpret_cast<IGooseListener*>(parameter);
        listener->on_receive(subscriber);
    }
    
    virtual void on_receive(GooseSubscriber subscriber) = 0;
    virtual ~IGooseListener(){ }

};

#endif // PYIEC61850_IGOOSELISTENER_HPP