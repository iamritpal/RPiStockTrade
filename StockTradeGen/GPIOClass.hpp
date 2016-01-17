#ifndef GPIO_CLASS_H
#define GPIO_CLASS_H
 
#include <string>
using namespace std;
/* GPIO Class
 * Purpose: Each object instantiated from this class will control a GPIO pin
 * The GPIO pin number must be passed to the overloaded class constructor
 * Source: http://hertaville.com/2012/11/18/introduction-to-accessing-the-raspberry-pis-gpio-in-c/
 * Author: Hussam Al-Hertani 
 * https://github.com/halherta/RaspberryPi-GPIOClass-v1
 * MGR: Just add a little enhcement handling errors, using is_open() method.
 */
class GPIOClass
{
public:
    GPIOClass();  // create a GPIO object that controls GPIO4 (default
    GPIOClass(string x); // create a GPIO object that controls GPIOx, where x is passed to this constructor
    int export_gpio(); // exports GPIO
    int unexport_gpio(); // unexport GPIO
    int setdir_gpio(string dir); // Set GPIO Direction
    int setval_gpio(string val); // Set GPIO Value (putput pins)
    int getval_gpio(string& val); // Get GPIO Value (input/ output pins)
    string get_gpionum(); // return the GPIO number associated with the instance of an object
private:
    string gpionum; // GPIO number associated with the instance of an object
};
 
#endif