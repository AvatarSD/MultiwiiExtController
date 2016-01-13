#ifndef PPM_H
#define PPM_H

#include <BoostSerialPort/BSerialPort.h>

class RC
{
public:
    RC();
    RC(uint8_t channel, uint16_t value);

    uint8_t channel() const;
    void setChannel(const uint8_t &channel);
    uint16_t value() const;
    void setValue(const uint16_t &value);
    void *operator ()(uint8_t channel, uint16_t value);
private:

    uint8_t _channel;
    uint16_t _value;
};

class PPM : public BSerialPort
{
public:
    PPM();
    void read(const uint8_t *inData, int byteToRead);
private:
    RC _rcTemp;
    virtual void dataResived(const RC & data);
};

#endif // PPM_H
