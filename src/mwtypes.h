#ifndef MWTYPES
#define MWTYPES

/*
Структуры и макросы для мультивишки
*/

#define BAROstat 1
#define MAGstat 2
#define GPSstat 3
#define SONARstat 4

struct mw_move
{
    short int ROLL, PITCH, YAW, THROTTLE, AUX1, AUX2, AUX3, AUX4; //Range [1000;2000]
};

struct mw_status
{
    unsigned int cycleTime;         //unit: microseconds
    unsigned int i2c_errors_count;  //
    unsigned int sensor;            //BARO<<1|MAG<<2|GPS<<3|SONAR<<4
    unsigned long int flag;         //a bit variable to indicate which BOX are active,
                                    //the bit position depends on the BOX which are configured
    char globalConf_currentSet;     //to indicate the current configuration setting
};

struct mw_analog
{
    char vbat;              //unit: 1/10 volt
    int intPowerMeterSum;   //
    int rssi;               //range: [0;1023]
    int amperage;           //
};

struct mw_gps
{
    char FIX;                   //	0 or 1
    char  numSat;               //
    unsigned long int coord_LAT;//  1 / 10 000 000 deg
    unsigned long int coord_LON;//	1 / 10 000 000 deg
    unsigned long int altitude;	//  meter
    unsigned int speed;         //	cm/s
    unsigned int ground_course; //  degree*10
};

struct mw_metric
{
    int AccelX;
    int AccelY;
    int AccelZ;

    int GyroX;
    int GyroY;
    int GyroZ;

    int MagX;
    int MagY;
    int MagZ;
};

struct mw_info
{
    char VERSION;                   //  version of MultiWii
    char MULTITYPE;                 //  type of multi:
                                    //      TRI/QUADP,QUADX,BI,GIMBAL,Y6,HEX6,FLYING_WING,Y4,HEX6X,OCTOX8, OCTOFLATP,OCTOFLATX,AIRPLANE,HELI_120,HELI_90,VTAIL4,HEX6H,SINGLECOPTER,DUALCOPTER
    char MSP_VERSION;               //  not used currently
    unsigned long int capability;	//  A 32 bit variable to indicate capability of FC board.
                                    //  Currently, BIND button is used on first bit, DYNBAL on second, FLAP on third
};

struct mw_altitude
{
    int EstAlt; //cm
    int vario;  //cm/s
};

struct mw_attitude
{
    int angx;       //Range [-1800;1800] (unit: 1/10 degree)
    int angy;       //Range [-900;900] (unit: 1/10 degree)
    int heading;	//Range [-180;180]
};

#endif // MWTYPES

