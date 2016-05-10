#include "multiwii.h"

#include "stdio.h"

#define MSP_IDENT               100 //коды сообщений с мультивишки
#define MSP_STATUS              101
#define MSP_RAW_IMU             102
#define MSP_RAW_GPS             106
#define MSP_ATTITUDE            108
#define MSP_ALTITUDE            109
#define MSP_ANALOG              110
#define MSP_SET_RAW_RC          200

#define $_byte                  0   //позиции нужных байтов
#define M_byte                  1
#define direction_byte          2
#define lenth_byte              3
#define cmd_byte                4
#define crc_shift_byte          5

#define additinal_all_bytes     6   //ко-во байт в сообщении помимо данных
#define additional_crc_bytes    2   //ко-во байт помимо данных, с которых вычисляется контрольная сумма
#define start_calk_crc_shift    3   //начальный байт, с которого начинается вычисление контрольной суммы
#define start_data_byte         5   //байт, с которого начинаются данные

#define min_range 				1000 //проверка входных значений
#define max_range 				2000

MultiWii::MultiWii() : BSerialPort(){}

MultiWii::~MultiWii(){}

void MultiWii::read(char * inData, int byteToRead)
{
    /*outputs*/
    static char * outData = new char[_buffersize];
    static int OutReadingByte = 0;
    static char CmdDataLenth;
    //char CmdCRC, CalcCRC;

    for(int InputReadingByte = 0; InputReadingByte<byteToRead; InputReadingByte++)
    {
        if(OutReadingByte==$_byte) memset(outData, 0, _buffersize);
        outData[OutReadingByte] = inData[InputReadingByte];

        //detect some inportant for us data(number bytes in arrived  command)
        switch (OutReadingByte)
        {
        case $_byte:
            if(outData[OutReadingByte]!='$') OutReadingByte = 0; else OutReadingByte++;
            break;
        case M_byte:
            if(outData[OutReadingByte]!='M') OutReadingByte = 0; else OutReadingByte++;
            break;
        case direction_byte:
            if(outData[OutReadingByte]!='>') OutReadingByte = 0; else OutReadingByte++;
            break;
        case lenth_byte:
            CmdDataLenth = outData[OutReadingByte];
            OutReadingByte++;
            break;
        default:
            OutReadingByte++;
            break;
        }
        if (crc_shift_byte+CmdDataLenth==OutReadingByte)
        {
            /*CmdCRC = outData[OutReadingByte];
            calculate CRC
            CalcCRC = 0;
            for(int i = 0; i<CmdDataLenth+additional_crc_bytes; i++)
            {
             CalcCRC ^=outData[start_calk_crc_shift+i];
            }*/
            //Checking CRC
            /* if(CalcCRC==CmdCRC)
            {*/
            //call next func
            this->detect(outData);
            //}
            OutReadingByte = 0;
        }
        else if((crc_shift_byte+CmdDataLenth<=OutReadingByte)&&(OutReadingByte<0)) OutReadingByte = 0;
    }
}

void MultiWii::detect(char * command)
{
    if(command[lenth_byte]==0)  answer(command[cmd_byte]);
    else
    {
        switch (command[cmd_byte])
        {
        case MSP_IDENT:
            _infoData.VERSION = command[start_data_byte+0];
            _infoData.MULTITYPE = command[start_data_byte+1];
            _infoData.MSP_VERSION = command[start_data_byte+2];
            _infoData.capability = (((signed char)command[start_data_byte+6])<<24)|((command[start_data_byte+5])<<16)|((command[start_data_byte+4])<<8)|(command[start_data_byte+3]);
            MWInfoRecived(&_infoData);
            break;

        case MSP_ANALOG:
            _analogData.vbat = command[start_data_byte+0];
            _analogData.intPowerMeterSum = (((signed char)command[start_data_byte+2])<<8)|(command[start_data_byte+1]);
            _analogData.rssi = (((signed char)command[start_data_byte+4])<<8)|(command[start_data_byte+3]);
            _analogData.amperage = (((signed char)command[start_data_byte+6])<<8)|(command[start_data_byte+5]);
            analogRecived(&_analogData);
            break;

        case MSP_RAW_IMU:
            _metricData.AccelX = (((signed char)command[start_data_byte+1])<<8)|(command[start_data_byte+0]);
            _metricData.AccelY = (((signed char)command[start_data_byte+3])<<8)|(command[start_data_byte+2]);
            _metricData.AccelZ = (((signed char)command[start_data_byte+5])<<8)|(command[start_data_byte+4]);
            _metricData.GyroX = (((signed char)command[start_data_byte+7])<<8)|(command[start_data_byte+6]);
            _metricData.GyroY = (((signed char)command[start_data_byte+9])<<8)|(command[start_data_byte+8]);
            _metricData.GyroZ = (((signed char)command[start_data_byte+11])<<8)|(command[start_data_byte+10]);
            _metricData.MagX = (((signed char)command[start_data_byte+13])<<8)|(command[start_data_byte+12]);
            _metricData.MagY = (((signed char)command[start_data_byte+15])<<8)|(command[start_data_byte+14]);
            _metricData.MagZ = (((signed char)command[start_data_byte+17])<<8)|(command[start_data_byte+16]);
            metricRecived(&_metricData);
            break;

        case MSP_RAW_GPS:
            _gpsData.FIX = command[start_data_byte+0];
            _gpsData.numSat = command[start_data_byte+1];
            _gpsData.coord_LAT = (((signed char)command[start_data_byte+5])<<24)|((command[start_data_byte+4])<<16)|((command[start_data_byte+3])<<8)|(command[start_data_byte+2]);
            _gpsData.coord_LON = (((signed char)command[start_data_byte+9])<<24)|((command[start_data_byte+8])<<16)|((command[start_data_byte+7])<<8)|(command[start_data_byte+6]);
            _gpsData.altitude = (((signed char)command[start_data_byte+11])<<8)|(command[start_data_byte+10]);
            _gpsData.speed = (((signed char)command[start_data_byte+13])<<8)|(command[start_data_byte+12]);
            gpsRecived(&_gpsData);
            break;

        case MSP_STATUS:
            _statusData.cycleTime = (((signed char)command[start_data_byte+1])<<8)|(command[start_data_byte+0]);
            _statusData.i2c_errors_count = (((signed char)command[start_data_byte+3])<<8)|(command[start_data_byte+2]);
            _statusData.sensor = (((signed char)command[start_data_byte+5])<<8)|(command[start_data_byte+4]);
            _statusData.flag = (((signed char)command[start_data_byte+9])<<24)|((command[start_data_byte+8])<<16)|((command[start_data_byte+7])<<8)|(command[start_data_byte+6]);
            _statusData.globalConf_currentSet = command[start_data_byte+10];
            statusRecived(&_statusData);
            break;

        case MSP_ALTITUDE:
            _altitudeData.EstAlt = (((signed char)command[start_data_byte+3])<<24)|((command[start_data_byte+2])<<16)|((command[start_data_byte+1])<<8)|(command[start_data_byte+0]);
            _altitudeData.vario = _metricData.AccelZ = (((signed char)command[start_data_byte+5])<<8)|(command[start_data_byte+4]);
            altitudeRecived(&_altitudeData);
            break;

        case MSP_ATTITUDE:
            _attitudeData.angx = (((signed char)command[start_data_byte+1])<<8)|(command[start_data_byte+0]);
            _attitudeData.angy = (((signed char)command[start_data_byte+3])<<8)|(command[start_data_byte+2]);
            _attitudeData.heading = (((signed char)command[start_data_byte+5])<<8)|(command[start_data_byte+4]);
            attitudeRecived(&_attitudeData);
            break;

        default:
            //unsupported command
        	UnsupportedCmd(command[cmd_byte]);
            break;
        }
    }
}

void MultiWii::directMove(const mw_move& data)
{
    char checksum = 0;
    char CmdDataLength = sizeof(mw_move);
    char raw_data[CmdDataLength+additinal_all_bytes];
    short int tmp;

    /* Write the MSP header and message length */
    raw_data[$_byte] = '$';
    raw_data[M_byte] = 'M';
    raw_data[direction_byte] = '<';
    raw_data[lenth_byte] = CmdDataLength;
    raw_data[cmd_byte] = MSP_SET_RAW_RC;

    /*ROLL, PITCH, YAW, THROTTLE, AUX1, AUX2, AUX3, AUX4
     *Check input range
     *Write to buffer*/
    if(data.ROLL < min_range) tmp = min_range;
    else if(data.ROLL > max_range) tmp = max_range;
    else tmp = data.ROLL;
    raw_data[0+start_data_byte] = (tmp)&0xff;
    raw_data[1+start_data_byte] = ((tmp)>>8)&0xff;

    if(data.PITCH < min_range) tmp = min_range;
	else if(data.PITCH > max_range) tmp = max_range;
	else tmp = data.PITCH;
    raw_data[2+start_data_byte] = (tmp)&0xff;
    raw_data[3+start_data_byte] = ((tmp)>>8)&0xff;

    if(data.YAW < min_range) tmp = min_range;
	else if(data.YAW > max_range) tmp = max_range;
	else tmp = data.YAW;
    raw_data[4+start_data_byte] = (tmp)&0xff;
    raw_data[5+start_data_byte] = ((tmp)>>8)&0xff;

    if(data.THROTTLE < min_range) tmp = min_range;
	else if(data.THROTTLE > max_range) tmp = max_range;
	else tmp = data.THROTTLE;
    raw_data[6+start_data_byte] = (tmp)&0xff;
    raw_data[7+start_data_byte] = ((tmp)>>8)&0xff;

    if(data.AUX1 < min_range) tmp = min_range;
	else if(data.AUX1 > max_range) tmp = max_range;
	else tmp = data.AUX1;
    raw_data[8+start_data_byte] = (tmp)&0xff;
    raw_data[9+start_data_byte] = ((tmp)>>8)&0xff;

    if(data.AUX2 < min_range) tmp = min_range;
	else if(data.AUX2 > max_range) tmp = max_range;
	else tmp = data.AUX2;
    raw_data[10+start_data_byte] = (tmp)&0xff;
    raw_data[11+start_data_byte] = ((tmp)>>8)&0xff;

    if(data.AUX3 < min_range) tmp = min_range;
	else if(data.AUX3 > max_range) tmp = max_range;
	else tmp = data.AUX3;
    raw_data[12+start_data_byte] = (tmp)&0xff;
    raw_data[13+start_data_byte] = ((tmp)>>8)&0xff;

    if(data.AUX4 < min_range) tmp = min_range;
	else if(data.AUX4 > max_range) tmp = max_range;
	else tmp = data.AUX4;
    raw_data[14+start_data_byte] = (tmp)&0xff;
    raw_data[15+start_data_byte] = ((tmp)>>8)&0xff;

    /* Calculate checksum */
    checksum ^= CmdDataLength;
    checksum ^= MSP_SET_RAW_RC;
    for(int i = 0; i < CmdDataLength; i++) checksum ^= raw_data[i+start_data_byte];

    raw_data[crc_shift_byte+CmdDataLength] = checksum;

    /* Send message */
    write(raw_data, CmdDataLength+additinal_all_bytes);
}

void MultiWii::getStatus(){sendRequest(MSP_STATUS);}

void MultiWii::getMetric(){sendRequest(MSP_RAW_IMU);}

void MultiWii::getGPS(){sendRequest(MSP_RAW_GPS);}

void MultiWii::getAnalog(){sendRequest(MSP_ANALOG);}

void MultiWii::getMWInfo(){sendRequest(MSP_IDENT);}

void MultiWii::getAltitude(){sendRequest(MSP_ALTITUDE);}

void MultiWii::getAttitude(){sendRequest(MSP_ATTITUDE);}

void MultiWii::disconnectEvent(std::string err)
{
	error(err);
}


void MultiWii::sendRequest(unsigned char requestCode)
{
	char buf[additinal_all_bytes] = {'$', 'M', '<', 0, (char)requestCode, (char)requestCode};
	write(buf,sizeof(buf));
}
