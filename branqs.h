
////////////////////////////////////////////////////////////////////////////////////
// Rotina: setDigitalOutput
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      setDigitalOutput | Defines BC8S module output state
@param:     int moduleAddress | CAN module address defined by J1 to J4 jumpers configuration
@param:     int value | Output value. Each bit value corresponds to each output state. Ex: 197 = 11000101
@area:      BC8S
*/

void setDigitalOutput(int moduleAddress,int value);

////////////////////////////////////////////////////////////////////////////////////
// Rotina: set220HzPWMoutput
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      set220HzPWMoutput | Defines BC8S module 220Hz PWM output state
@param:     int moduleAddress | CAN module address defined by J1 to J4 jumpers
@param:     int PWMvalue | PWM Output value (0 to 1023)
@note:      The BC8S must be configured with the "220Hz PWM firmware - one channel"
@area:      BC8S
*/

void set220HzPWMoutput(int moduleAddress,int PWMvalue);

////////////////////////////////////////////////////////////////////////////////////
// Rotina: set170HzPWMoutput
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      set170HzPWMoutput | Defines BC8S module PWM outputs states
@param:     int moduleAddress | CAN module address defined by J1 to J4 jumpers
@param:     int channel | Output number (0 to 7 corresponding 1 to 8 output)
@param:     int PWMvalue | Percentual PWM Output value (0 to 100)
@note:      The BC8S must be configured with the "eight channel PWM firmware"
@area:      BC8S
*/

void set170HzPWMoutput(int moduleAddress,int channel,int PWMvalue);

////////////////////////////////////////////////////////////////////////////////////
// Rotina: getDigitalInput
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      getDigitalInput | Read the BC8E module inputs
@param:     int moduleAddress | CAN module address defined by J1 to J4 jumpers configuration
@return:    int | Input states. Each bit value corresponds to each input. Ex: 197 = 11000101
@area:      BC8E
*/

int getDigitalInput(int moduleAddress);


////////////////////////////////////////////////////////////////////////////////////
// Rotina: getDigitalInputCounter
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      getDigitalInputCounter | Read the BC8E module input counters
@param:     int moduleAddress | CAN module address defined by J1 to J4 jumpers configuration
@param:     int channel | Input number (0,1,2,3,4,5,6 or 7)
@return:    int | Input Counter value (0 @ 65535)
@area:      BC8E
*/

int getDigitalInputCounter(int moduleAddress,int channel);


////////////////////////////////////////////////////////////////////////////////////
// Rotina: getDigitalInputBC16E
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      getDigitalInputBC16E | Read the BC16E module inputs
@param:     int moduleAddress | CAN module address defined by J1 to J4 jumpers configuration
@return:    int | Input states. Each bit value corresponds to each input. Ex: 197 = 00000000 11000101
@area:      BC16E
*/

int getDigitalInputBC16E(int moduleAddress);

////////////////////////////////////////////////////////////////////////////////////
// Rotina: setAnalogOutput
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      setAnalogOutput | Defines BC4SA module outputs state
@param:     int moduleAddress | CAN module address defined by J1 to J4 jumpers configuration
@param:     int channel | Output number (1,2,3 or 4)
@param:     int value | Output value (0 = -10 Volts, 2048 = 0 Volts, 4095 = 10 Volts)
@area:      BC4SA
*/

void setAnalogOutput(int moduleAddress,int channel, int value);

////////////////////////////////////////////////////////////////////////////////////
// Rotina: getAnalogInput
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      getAnalogInput | Read the BC4EA inputs
@param:     int moduleAddress | CAN module address defined by J1 to J4 jumpers configuration
@param:     int channel | Input number (1,2,3 or 4)
@return:    int | Input value (0 = 0 Volts, 4000 = 10 Volts)
@area:      BC4EA
*/

int getAnalogInput(int moduleAddress,int channel);

////////////////////////////////////////////////////////////////////////////////////
// Rotina: getTemperature
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      getTemperature | Read the BC4TP inputs
@param:     int moduleAddress | CAN module address defined by J1 to J4 jumpers configuration
@param:     int channel | Input number (0=environment temperature) (1,2,3 or 4 for each input)
@param:     int termocoupleType | 0 = J_Type , 1 = K_Type
@return:    int | Input value in Celsius degrees
@note:      The environment temperature of each module must be read (ate leats once) to be automatically added to the module's inputs
@area:      BC4TP
*/

int getTemperature(int moduleAddress,int chanell,int termocoupleType);

////////////////////////////////////////////////////////////////////////////////////
// Internal Driver states
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// Rotina: getSPIdelay
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      getSPIdelay | Gets the software loop delay counter to perform SPI communication into BCCAN
@return:    int | SPI software loop counter delay
@note:      Normaly, this register don't need to be modified.
@area:      Internal Driver State
*/

int getSPIdelay();

////////////////////////////////////////////////////////////////////////////////////
// Rotina: getMaxCommunicationDelay
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      getMaxCommunicationDelay | Gets the maximum counter time to complete communication with any module
@return:    int | Time counter
@note:      This state registrate the maximum time spent to communicate with a module. During a communication, if this register reaches the "TimeoutLimit", the driver indicates a communication error increasing the "CommunicationErrors" state. Corresponds to the original "statusCAN_maxContadorTimeout".
@area:      Internal Driver State
*/

int getMaxCommunicationDelay();

////////////////////////////////////////////////////////////////////////////////////
// Rotina: getCommunicationErrors
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      getCommunicationErrors | Gets the accumulated communication errors counter
@return:    int | Errors counter
@note:      This register is increased, each time occurs a communication error. Corresponds to the original "statusCAN_numeroConfigMCP".
@area:      Internal Driver State
*/

int getCommunicationErrors();

////////////////////////////////////////////////////////////////////////////////////
// Rotina: getTimeoutLimit
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      getTimeoutLimit | Gets the timeout limit counter defined during initialization
@return:    int | Timeout limit
@note:      This register is originaly defined with the value 400. Corresponds to the original "configCAN_limiteTimeout"
@area:      Internal Driver State
*/

int getTimeoutLimit();

////////////////////////////////////////////////////////////////////////////////////
// Rotina: setSPIdelay
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      setSPIdelay | Sets the software loop delay counter to perform SPI communication into BCCAN
@param:     int newValue | The new SPI software loop delay
@note:      Normaly, this register don´t need to be modified. 
@area:      Internal Driver State
*/

void setSPIdelay(int newValue);

////////////////////////////////////////////////////////////////////////////////////
// Rotina: setMaxCommunicationDelay
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      setMaxCommunicationDelay | Sets the maximum counter time to complete communication with any module
@param:     int newValue | New maximum time counter
@note:      You can change this register to "reset" to a initial value. Corresponds to the original "statusCAN_maxContadorTimeout"
@area:      Internal Driver State
*/

void setMaxCommunicationDelay(int newValue);

////////////////////////////////////////////////////////////////////////////////////
// Rotina: setCommunicationErrors
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      setCommunicationErrors | Sets the accumulated communication errors count
@param:     int newValue | A new "errors count"
@note:      You can change this register to "reset" to a initial value. Corresponds to the original "statusCAN_numeroConfigMCP"
@area:      Internal Driver State
*/

void setCommunicationErrors(int newValue);

////////////////////////////////////////////////////////////////////////////////////
// Rotina: setTimeoutLimit
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      setTimeoutLimit | Sets the timeout limit counter constant
@param:     int newValue | A new timeout limit constant
@note:      This register is originaly defined with the value 400. If desired, you can change this register to a secure value. Corresponds to the original "configCAN_limiteTimeout".
@area:      Internal Driver State
*/

void setTimeoutLimit(int newValue);


//branqsOpenPLCdriverV01R11_t1.1 Begining of the block

////////////////////////////////////////////////////////////////////////////////////
// Rotina: spican_turnOnCS
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      spican_turnOnCS | Turn on ChipSelect on SPICAN module
@param:     int moduleAddress | CAN module address defined by J1 to J4 jumpers configuration
@area:      SPICAN
*/

void spican_turnOnCS(int enderecoPlaca);

////////////////////////////////////////////////////////////////////////////////////
// Rotina: spican_turnOffCS
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      spican_turnOffCS | Turn off ChipSelect on SPICAN module
@param:     int moduleAddress | CAN module address defined by J1 to J4 jumpers configuration
@area:      SPICAN
*/

void spican_turnOffCS(int enderecoPlaca);

////////////////////////////////////////////////////////////////////////////////////
// Rotina: spican_xfer
////////////////////////////////////////////////////////////////////////////////////

/*
@func:      spican_xfer | Send and receive a byte through SPI
@param:     int moduleAddress | CAN module address defined by J1 to J4 jumpers configuration
@param:     int byteToSend | Byte that will be sent through SPI
@return:    int | byte received from SPI
@area:      SPICAN
*/

int spican_xfer(int enderecoPlaca, int _byteToSend);

//branqsOpenPLCdriverV01R11_t1.1 End of the block
