import pyiec61850 as iec

class GooseListener(iec.IGooseListener):
    # Define Python class 'constructor'
    def __init__(self):
        # Call C++ base class constructor
        iec.IGooseListener.__init__(self)

    # Override C++ method: virtual int handle(int a, int b) = 0;
    def on_receive(self, subscriber):
        # Return the product
        print("In listener")

subc = iec.GooseSubscriber_create("simpleIOGenericIO/LLN0$GO$gcbAnalogValues", None)

test = GooseListener()
iec.GooseSubscriber_setListener(subc, test)