#ifndef __PACSDK_H
#define __PACSDK_H

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

//VB6 dll=> type is __stdcall, true is -1, after building,change name to xpacsdk_vb.dll
//vc dll => type is __cdecl, true=1
//OutputDebugString + dbgview=>print debug string
#ifdef PACSDK_EXPORTS
	#define PAC_API(type) __declspec(dllexport) type	__cdecl
#else
	#define PAC_API(type) type
#endif

#define PUBLIC_API(type)	type
#define PRIVATE(type) static type
#define PAC_PRIVATE_API PAC_API

#define  PAC_PRIVATE_API          PAC_API
#define  PAC_SERAL_NUMBER_LENGTH  8

#define  AddressMultiplica  1

    //=========================================================================
    //  01. System Information API
    //=========================================================================
#define  PAC_PARALLEL     0x80
#define  PAC_PARALLEL_RW  0x81
#define  PAC_SCAN         0x40
#define  PAC_DI32         0xE3
#define  PAC_32BIT        0x20
#define  PAC_DO32         0xE0
#define  PAC_DI16DO16     0xE2
#define  PAC_DI16         0xC3
#define  PAC_DO16         0xC0
#define  PAC_DI8DO8       0xC2
#define  PAC_8K           8000
#define  PAC_9K           9000
PAC_API(void) pac_SetMemoryMapping();

PAC_API(BOOL) pac_BackwardCompatible();
PAC_API(void) pac_ChangeSlot(BYTE slotNo);
PAC_API(BOOL) pac_CheckSDKVersion(DWORD version);
PAC_API(void) pac_EnableLED(BOOL bFlag);
PAC_API(void) pac_EnableLEDs(int pin, BOOL bFlag);
PAC_API(int)  pac_GetComMapping(int ndx);
PAC_API(void) pac_GetCPUVersion(LPSTR cpu_version);                 
PAC_API(BOOL) pac_ModuleExists(HANDLE hPort, int slot);      
PAC_API(int)  pac_GetModuleName(BYTE slot, LPSTR strName);   
PAC_API(int)  pac_GetModuleType(BYTE slot);                  
PAC_API(int)  pac_GetModuleVersion(BYTE slot, LPSTR strName);   
PAC_API(void) pac_GetOSVersion(LPSTR os_version);            
PAC_API(int)  pac_GetRotaryID();                             
PAC_API(void) pac_GetSDKVersion(LPSTR sdk_version);          
PAC_API(void) pac_GetSerialNumber(LPSTR SerialNumber);                                       

//=========================================================================
// 02. Backplane API
//=========================================================================
PAC_API(void) pac_EnableRetrigger(BYTE iValues);           //W  X   
PAC_API(void) pac_GetBackplaneID(LPSTR backplane_version); //W  X
PAC_API(int)  pac_GetBatteryLevel(int nBattery);           //W  X
PAC_API(int)  pac_GetDIPSwitch();                          //W  X
PAC_API(int)  pac_GetSlotCount();                          //W  X
PAC_API(void) pac_RegistryHotPlug(DWORD hWnd, DWORD msgID);//W
PAC_API(void) pac_UnregistryHotPlug(DWORD hWnd);           //W

//undocumented API
PAC_API(void) pac_ClearHotPlug();                               //W 
PAC_API(void) pac_ClearRisingEdgeIRQ(BYTE slots);               //W 
PAC_API(void) pac_EnableHotPlug(BOOL bEnable);                  //W 
PAC_API(void) pac_EnableRisingEdgeIRQ(BYTE slots, BOOL bEnable);//W
PAC_API(void) pac_EOI();                                        //W  X 
PAC_API(BOOL) pac_GetHotPlugIRQState();                         //W 
PAC_API(BOOL) pac_GetHotPlugStatus();                           //W 
PAC_API(BYTE) pac_GetRisingEdgeEnableStatus();                  //W 
PAC_API(BYTE) pac_GetRisingEdgeIRQStatus();                     //W 
PAC_API(void) pac_ResetBackplane();                             //W  X 
PAC_API(void) pac_ResetSystemToDefault();                       //W  X 


//=========================================================================
// 03. Interrupt API
//=========================================================================
#define  PAC_INTR_DONE  0
#define  PAC_INTR_DONE1 1
#define  PAC_INTR_FAIL  2
#define  PAC_INTR_EXIT  3

#define  INTR_RISING_TRIG   0
#define  INTR_LEVEL_TRIG    1
#define  INTR_Falling_TRIG  2

typedef int (CALLBACK * PAC_CALLBACK_FUNC)();

PAC_API(void)   pac_EnableSlotInterrupt(BYTE slot, BOOL bEnable);         
PAC_API(HANDLE) pac_GetSlotInterruptEvent(BYTE slot);                     
PAC_API(DWORD)  pac_GetSlotInterruptID(BYTE Slot);
PAC_API(void)   pac_InterruptDone(BYTE slot);                             
PAC_API(BOOL)   pac_InterruptInitialize(BYTE slot);                       
PAC_API(BOOL)   pac_RegisterSlotInterrupt(BYTE slot, PAC_CALLBACK_FUNC f);
PAC_API(void)   pac_SetSlotInterruptEvent(BYTE slot, HANDLE hEvent);      
PAC_API(BOOL)   pac_SetSlotInterruptPriority(BYTE slot, int nPriority);   
PAC_API(void)   pac_SetTriggerType(BYTE slot, int iType) ;                
PAC_API(BOOL)   pac_UnregisterSlotInterrupt(BYTE slot);                   

//=========================================================================
// 04. Memory Access API
//=========================================================================
#define  PAC_MEM_SRAM    0
#define  PAC_MEM_EEPROM  1
#define  PAC_MEM_NVRAM   2

PAC_API(DWORD) pac_GetMemorySize(int mem_type);                               //W  X
PAC_API(BOOL)  pac_ReadMemory(DWORD address, LPBYTE lpBuffer, DWORD dwLength, 
    int mem_type);                                                           //W  X
PAC_API(BOOL)  pac_WriteMemory(DWORD address, LPBYTE lpBuffer, DWORD dwLength, 
    int mem_type);                                                           //W  X
PAC_API(void)  pac_EnableEEPROM(BOOL bEnable);                                //W  X



//=========================================================================
// 05. Watchdog API
//=========================================================================
#define  PAC_WDT_HW  0
#define  PAC_WDT_OS  1 //For OS booting process.

PAC_API(void)  pac_DisableWatchDog(int wdt);             //W  X
PAC_API(BOOL)  pac_EnableWatchDog(int wdt, DWORD value); //W  X
PAC_API(BOOL)  pac_GetWatchDogState(int wdt);            //W  X
PAC_API(DWORD) pac_GetWatchDogTime(int wdt);             //W  X
PAC_API(void)  pac_RefreshWatchDog(int wdt);             //W  X
PAC_API(BOOL)  pac_SetWatchDogTime(int wdt, DWORD value);//W  X



//=========================================================================
// 06. microSD Management API (WinPAC only)
//=========================================================================
PAC_API(BOOL) pac_SDExists();                     //W
PAC_API(BOOL) pac_SDMount(LPTSTR szPartitionName);//W
PAC_API(BOOL) pac_SDOnside();                     //W
PAC_API(BOOL) pac_SDUnmount();                    //W



//=========================================================================
// 07. Registry API
//=========================================================================
#define  PKT_NONE    0
#define  PKT_KEY     1
#define  PKT_STRING  2
#define  PKT_DWORD   3

PAC_API(DWORD) pac_RegCountKey(LPCSTR KeyName);                                     //W  X
PAC_API(DWORD) pac_RegCountValue(LPCSTR KeyName);                                   //W  X
PAC_API(BOOL)  pac_RegCreateKey(LPCSTR KeyName);                                    //W  X
PAC_API(BOOL)  pac_RegDeleteKey(LPCSTR KeyName);                                    //W  X
PAC_API(BOOL)  pac_RegDeleteValue(LPCSTR KeyName);                                  //W  X
PAC_API(DWORD) pac_RegGetDWORD(LPCSTR KeyName);                                     //W  X
PAC_API(BOOL)  pac_RegGetKeyByIndex(LPCSTR KeyName, DWORD dwIndex, LPSTR lpName);  //W  X
PAC_API(DWORD) pac_RegGetKeyInfo(LPCSTR KeyName);                                   //W  X
PAC_API(BOOL)  pac_RegGetString(LPCSTR KeyName, LPSTR lpData, DWORD dwLength);     //W  X
PAC_API(BOOL)  pac_RegGetValueByIndex(LPCSTR KeyName, DWORD dwIndex, LPSTR lpName);//W  X
PAC_API(BOOL)  pac_RegKeyExist(LPCSTR KeyName);                                     //W  X
PAC_API(BOOL)  pac_RegSave(LPCSTR KeyName);                                         //W  X
PAC_API(BOOL)  pac_RegSetString(LPCSTR KeyName, LPCSTR assignStr, DWORD dwLength); //W  X
PAC_API(BOOL)  pac_RegSetDWORD(LPCSTR KeyName, DWORD assignVal);                    //W  X
//=========================================================================
// 08. UART API
//=========================================================================
#define  CTO_TIMEOUT_ALL          0
#define  CTO_READ_RETRY_TIMEOUT   1
#define  CTO_READ_TOTAL_TIMEOUT   2
#define  CTO_WRITE_TOTAL_TIMEOUT  3

#define  CTS  0
#define  DSR  1
#define  RI   2
#define  CD   3

#define  IN_DATA   0
#define  OUT_DATA  1

PAC_API(HANDLE) uart_Open(LPCSTR ConnectionString);                        //W  X  
PAC_API(HANDLE) uart_OpenEx(LPCSTR ConnectionString);                      //W  X  undoc
PAC_API(BOOL)   uart_Close(HANDLE hPort);                                  //W  X

PAC_API(BOOL)   uart_Write(HANDLE hPort, LPCSTR buf);                      //W  X  undoc
PAC_API(BOOL)   uart_Read(HANDLE hPort, LPSTR buf);                        //W  X  undoc 

PAC_API(BOOL)   uart_WriteExt(HANDLE hPort, LPCSTR buf, DWORD out_Len);
PAC_API(BOOL)   uart_ReadExt(HANDLE hPort, LPSTR buf, DWORD in_Len);   

PAC_API(BOOL)   uart_Send(HANDLE hPort, LPCSTR buf);                       //W  X
PAC_API(BOOL)   uart_Recv(HANDLE hPort, LPSTR buf);                        //W  X
PAC_API(BOOL)   uart_SendCmd(HANDLE hPort, LPCSTR cmd, LPSTR szResult);    //W  X

PAC_API(BOOL)   uart_SendExt(HANDLE hPort, LPCSTR buf, DWORD out_Len);
PAC_API(BOOL)   uart_RecvExt(HANDLE hPort, LPSTR buf, DWORD in_Len);
PAC_API(BOOL)   uart_SendCmdExt(HANDLE hPort, LPCSTR cmd, DWORD out_Len, 
    LPSTR szResult, DWORD in_Len);                                      

PAC_API(void)   uart_SetTimeOut(HANDLE hPort, DWORD msec, int ctoType);    //W  X
PAC_API(void)   uart_EnableCheckSum(HANDLE hPort, BOOL bEnable);           //W  X
PAC_API(void)   uart_SetTerminator(HANDLE hPort, LPCSTR szTerm);           //W  X

PAC_API(BOOL)   uart_BinSend(HANDLE hPort, LPCSTR buf, DWORD in_Len);      //W  X
PAC_API(BOOL)   uart_BinRecv(HANDLE hPort, LPSTR buf, DWORD in_Len);       //W  X
PAC_API(BOOL)   uart_BinSendCmd(HANDLE hPort, LPCSTR ByteCmd, DWORD in_Len, 
    LPSTR ByteResult, DWORD out_Len);                                     //W  X

PAC_API(DWORD)  uart_GetDataSize(HANDLE hPort, int data_type);             //W  X
PAC_API(BOOL)   uart_GetLineStatus(HANDLE hPort, int pin);                 //W  X
PAC_API(DWORD)  uart_SetLineStatus(HANDLE port, int pin, int mode);        //W  X  undoc 
PAC_API(DWORD)  uart_GetOutputLineStatus(HANDLE hPort);                    //W  X  undoc

PAC_API(BOOL)	uart_ChangeMode(int mode);

//=========================================================================
// 09. PAC_IO API
//=========================================================================
#define  PAC_REMOTE_IO_BASE       (0x1000)
#define  PAC_REMOTE_IO(iAddress)  (PAC_REMOTE_IO_BASE|iAddress)

#define  PAC_REMOTE_iPAC_BASE           (0x100000)
#define  PAC_REMOTE_iPAC(iAddr, iSlot)  (PAC_REMOTE_iPAC_BASE|iAddr<<8|iSlot)

#define  PAC_DAISY_CHAIN_WIRING_MODULE_PORT_BASE       (0x1000000)
#define  PAC_DAISY_CHAIN_WIRING_MODULE_PORT(slot,port) ((slot& PAC_REMOTE_IO_BASE)?(PAC_DAISY_CHAIN_WIRING_MODULE_PORT_BASE|((slot&0xFFF) <<8)|port|(0x1<<6)):((slot& PAC_REMOTE_iPAC_BASE)?(PAC_DAISY_CHAIN_WIRING_MODULE_PORT_BASE|((slot&0xFFFFF) <<8)|port|(0x2<<6)):(PAC_DAISY_CHAIN_WIRING_MODULE_PORT_BASE|(slot<<8)|port)))

#define  pac_GetBit(v, ndx)       (v & (1<<ndx))                                                    

PAC_API(BOOL)  pac_WriteDO(HANDLE hPort, int slot, int iDO_TotalCh, DWORD lDO_Value);            
PAC_API(BOOL)  pac_WriteDOBit(HANDLE hPort, int slot, int iDO_TotalCh, int iChannel, int iBitValue);                                                                             
PAC_API(BOOL)  pac_ReadDO(HANDLE hPort, int slot, int iDO_TotalCh, DWORD *lDO_Value);            
PAC_API(BOOL)  pac_ReadDI(HANDLE hPort, int slot, int iDI_TotalCh, DWORD *lDI_Value);            
PAC_API(BOOL)  pac_ReadDIO(HANDLE hPort, int slot, int iDI_TotalCh, int iDO_TotalCh, DWORD* lDI_Value, DWORD* lDO_Value);                                                        
PAC_API(BOOL)  pac_ReadDILatch(HANDLE hPort, int slot, int iDI_TotalCh, int iLatchType, DWORD *lDI_Latch_Value);                                                    
PAC_API(BOOL)  pac_ClearDILatch(HANDLE hPort, int slot);                                         
PAC_API(BOOL)  pac_ReadDIOLatch(HANDLE hPort, int slot, int iDI_TotalCh, int iDO_TotalCh, int iLatchType, DWORD *lDI_Latch_Value, DWORD *lDO_Latch_Value);           
PAC_API(BOOL)  pac_ClearDIOLatch(HANDLE hPort, int slot);                                        
PAC_API(BOOL)  pac_ReadDICNT(HANDLE hPort, int slot, int iChannel, int iDI_TotalCh, DWORD *lCounter_Value);                                                                     
PAC_API(BOOL)  pac_ClearDICNT(HANDLE hPort, int slot, int iChannel, int iDI_TotalCh);
PAC_API(BOOL)  pac_WriteAO(HANDLE hPort, int slot, int iChannel, int iAO_TotalCh, float fValue); 
PAC_API(BOOL)  pac_ReadAO(HANDLE hPort, int slot, int iChannel, int iAO_TotalCh, float *fValue); 
PAC_API(BOOL)  pac_ReadAI(HANDLE hPort, int slot, int iChannel, int iAI_TotalCh, float *fValue); 
PAC_API(BOOL)  pac_ReadAIHex(HANDLE hPort, int slot, int iChannel, int iAI_TotalCh, int *iValue);
PAC_API(BOOL)  pac_ReadAIAll(HANDLE hPort, int slot, float fValue[]);                            
PAC_API(BOOL)  pac_ReadAIAllHex(HANDLE hPort, int slot, int iValue[]);                           
PAC_API(BOOL)  pac_ReadCNT(HANDLE hPort, int slot, int iChannel, DWORD *lCounter_Value);         
PAC_API(BOOL)  pac_ClearCNT(HANDLE hPort, int slot, int iChannel);                               
PAC_API(BOOL)  pac_ReadCNTOverflow(HANDLE hPort, int slot, int iChannel, int *iOverflow);        
PAC_API(BOOL)  pac_ReadCNTAll(HANDLE hPort, int slot, int iTotalChannel, DWORD lCounter_Value[]);         
PAC_API(BOOL)  pac_ClearCNTAll(HANDLE hPort, int slot, int iTotalChannel);
PAC_API(BOOL)  pac_ReadFREQ(HANDLE hPort, int slot, int iChannel, float *fFreq_Value); 
// (undoc)
PAC_API(short) pac_GetModuleLastOutputSource(HANDLE hPort,int slot); 
PAC_API(BOOL)  pac_GetModuleWDTStatus(HANDLE hPort,int slot);
PAC_API(BOOL)  pac_GetModuleWDTStatusEX(HANDLE hPort,int slot, short *outStatus);
PAC_API(BOOL)  pac_GetModuleWDTConfig(HANDLE hPort,int slot, short* enStatus, unsigned long *wdtTimeout,int *ifWDT_Overwrite);
PAC_API(BOOL)  pac_SetModuleWDTConfig(HANDLE hPort,int slot, short enStatus, unsigned long wdtTimeout,int ifWDT_Overwrite);
PAC_API(BOOL)  pac_ResetModuleWDT(HANDLE hPort,int slot); 
PAC_API(BOOL)  pac_RefreshModuleWDT(HANDLE hPort,int slot); 

PAC_API(BOOL)  pac_InitModuleWDTInterrupt(int slot,PAC_CALLBACK_FUNC f); //only for 8KRW module
PAC_API(BOOL) pac_SetModuleWDTInterruptStatus(int slot,short enStatus);//only for 8KRW module
PAC_API(short) pac_GetModuleWDTInterruptStatus(int slot);               //only for 8KRW module


PAC_API(BOOL)  pac_ReadModuleSafeValueDO(HANDLE hPort,int slot, int iDO_TotalCh, unsigned long *lValue);
PAC_API(BOOL)  pac_WriteModuleSafeValueDO(HANDLE hPort,int slot, int iDO_TotalCh, unsigned long lValue);

PAC_API(BOOL)  pac_ReadModuleSafeValueAO(HANDLE hPort,int slot,int iChannel,int iAO_TotalCh, float *fValue);
PAC_API(BOOL)  pac_WriteModuleSafeValueAO(HANDLE hPort,int slot,int iChannel,int iAO_TotalCh,float fValue); 

PAC_API(BOOL)  pac_ReadModulePowerOnValueDO(HANDLE hPort,int slot, int iDO_TotalCh, unsigned long *lValue); //PowerON status is 0ff and ruturn the 0 of powerOn value even the powerON value isn't 0 saved on fram
PAC_API(BOOL)  pac_WriteModulePowerOnValueDO(HANDLE hPort,int slot, int iDO_TotalCh, unsigned long lValue); //PowerOn value large 0 means the PowerOn value is enabled

PAC_API(BOOL)  pac_ReadModulePowerOnValueAO(HANDLE hPort,int slot,int iChannel,int iAO_TotalCh,float *fValue);
PAC_API(BOOL)  pac_WriteModulePowerOnValueAO(HANDLE hPort,int slot,int iChannel,int iAO_TotalCh,float fValue);

PAC_API(BOOL) pac_WriteDO_MF(HANDLE hPort, int iAddrSlot, int iDO_TotalCh, DWORD lDO_Value);
PAC_API(BOOL) pac_ReadDIO_MF(HANDLE hPort, int iAddrSlot, int iDI_TotalCh, int iDO_TotalCh, DWORD* lDI_Value, DWORD* lDO_Value);
PAC_API(BOOL) pac_ReadDI_MF(HANDLE hPort, int iSlot, int iDI_TotalCh, DWORD *lDI_Value);
PAC_API(BOOL) pac_ReadDO_MF(HANDLE hPort, int iSlot, int iDO_TotalCh, DWORD *lDO_Value);

PAC_API(BOOL) pac_ReadDICNT_MF(HANDLE hPort, int iAddrSlot, int iChannel, int iDI_TotalCh, DWORD *lCounter_Value);
PAC_API(BOOL) pac_ClearDICNT_MF(HANDLE hPort, int iAddrSlot, int iChannel, int iDI_TotalCh);

PAC_API(BOOL) pac_ReadModulePowerOnValueDO_MF(HANDLE hPort, int slot, int iDO_TotalCh, unsigned long *lValue);
PAC_API(BOOL) pac_WriteModulePowerOnValueDO_MF(HANDLE hPort, int slot, int iDO_TotalCh, unsigned long lValue);

PAC_API(BOOL) pac_ReadModuleSafeValueDO_MF(HANDLE hPort, int slot, int iDO_TotalCh, unsigned long *lValue);
PAC_API(BOOL) pac_WriteModuleSafeValueDO_MF(HANDLE hPort, int slot, int iDO_TotalCh, unsigned long lData);

PAC_API(BOOL) pac_ReadAO_MF(HANDLE hPort, int slot, int iChannel, int iAO_TotalCh, float *fValue); //W  X
PAC_API(BOOL) pac_WriteAO_MF(HANDLE hPort, int iAddrSlot, int iChannel, int iAO_TotalCh, float fValue);

PAC_API(BOOL) pac_ReadModulePowerOnValueAO_MF(HANDLE hPort,int slot,int iChannel,int iAO_TotalCh,float *fValue);
PAC_API(BOOL) pac_WriteModulePowerOnValueAO_MF(HANDLE hPort, int iAddrSlot, int iChannel, int iAO_TotalCh, float fValue);

PAC_API(BOOL) pac_ReadModuleSafeValueAO_MF(HANDLE hPort,int slot,int iChannel,int iAO_TotalCh, float *fValue);
PAC_API(BOOL) pac_WriteModuleSafeValueAO_MF(HANDLE hPort, int iAddrSlot, int iChannel, int iAO_TotalCh, float  fValue);

PAC_API(BOOL) pac_ReadAIAllExt(HANDLE hPort, int slot, float fValue[], DWORD Buff_Len, DWORD *Channel);
PAC_API(BOOL) pac_ReadAIAllHexExt(HANDLE hPort, int slot, int iValue[], DWORD Buff_Len, DWORD *Channel);

PAC_API(BOOL) pac_SetModulePowerOnEnStatus(int slot, short enStatus);
PAC_API(BOOL) pac_GetModulePowerOnEnStatus(int slot, short* enStatus);

PAC_API(BOOL) pac_ReadAISensorSerialNumber(HANDLE hPort, int iAddrSlot,int port,int iindex, char *SNstring, DWORD Buff_Len);//for DAISY CHAIN WIRING MODULE , such as i-87004
//=========================================================================
// 10. Backplane timer API
//=========================================================================
#define  TIMEROUT  0
#define  TIMER1    1
#define  TIMER2    2

typedef int (CALLBACK * PAC_TIMEROUT_CALLBACK_FUNC)();


PAC_API(DWORD) pac_GetBPTimerTimeTick_ms(void);                         //W  X
PAC_API(WORD)  pac_GetBPTimerTimeTick_us(void);                         //W  X
PAC_API(void)  pac_KillBPTimer(int type);                               //W  X
PAC_API(BOOL)  pac_SetBPTimer(int type, unsigned int uElapse, 
    PAC_TIMEROUT_CALLBACK_FUNC f);                                     //W  X
PAC_API(BOOL)  pac_SetBPTimerInterruptPriority(int type, int nPriority);//W  X  undoc 
PAC_API(BOOL)  pac_SetBPTimerOut(unsigned int uHighElapse, 
    unsigned int uLOwElapse, PAC_TIMEROUT_CALLBACK_FUNC f);            //W  X




//=========================================================================
//  11. Error Handling API
//=========================================================================
PAC_API(void)  pac_ClearLastError(DWORD errno);                        //W  X  
PAC_API(DWORD) pac_GetLastError();                                     //W  X
PAC_API(void)  pac_SetLastError(DWORD errno);                          //W  X  
PAC_API(void)  pac_GetErrorMessage(DWORD dwMessageID, LPTSTR lpBuffer);//W  X

  //=========================================================================
// 12. MISC API
//========================================================================= 
PAC_API(void) pac_AnsiToWideString(LPCSTR astr, LPWSTR wstr);           
PAC_API(void) pac_DoEvent();  //same function(org wpac            
PAC_API(void) pac_DoEvents(); //same function(org xpac 
PAC_API(void) pac_WideStringToAnsi(const TCHAR *wstr, LPSTR astr);	//W  X 
PAC_API(void) pac_WideToAnsiString(LPCWSTR wstr, LPSTR astr);     
PAC_API(BOOL) pac_GetCurrentDirectory(char* cBuffer, DWORD nSize);	//W  X
PAC_API(BOOL) pac_GetCurrentDirectoryW(LPTSTR lpBuffer, DWORD nSize);//W  X

//=========================================================================
// 13. Buzzer API (undoc)
//=========================================================================
PAC_API(void) pac_BuzzerBeep(WORD count, DWORD milliseconds);//W
PAC_API(void) pac_GetBuzzerFreqDuty(int *freq, int *duty);   //W
PAC_API(void) pac_SetBuzzerFreqDuty(int freq, int duty);     //W
PAC_API(void) pac_StopBuzzer();                              //W

//====================
//PWM
//===================
PAC_API(BOOL) pac_SetPWMDuty(HANDLE port,int slot, short chIndex,float duty);
PAC_API(BOOL) pac_GetPWMDuty(HANDLE port,int slot, short chIndex,float *duty);

PAC_API(BOOL) pac_SetPWMFrequency(HANDLE port,int slot,short chIndex,unsigned long  freq);
PAC_API(BOOL) pac_GetPWMFrequency(HANDLE port,int slot,short chIndex,unsigned long *freq);

PAC_API(BOOL) pac_SetPWMMode(HANDLE port, int slot, short chIndex, long mode);
PAC_API(BOOL) pac_GetPWMMode(HANDLE port, int slot, short chIndex, long *mode);
//  Mode: 1 continue mode, 0 pulse count mode

PAC_API(BOOL) pac_SetPWMDITriggerConfig(HANDLE port, int slot, short chIndex, short config);
PAC_API(BOOL) pac_GetPWMDITriggerConfig(HANDLE port, int slot, short chIndex, short *config);

PAC_API(BOOL) pac_SetPWMStart(HANDLE port, int slot, short enStatus);

PAC_API(BOOL) pac_SetPWMSynChannel(HANDLE port, int slot, short chIndex, short enStatus);
PAC_API(BOOL) pac_GetPWMSynChannel(HANDLE port, int slot, short chIndex, short *enStatus);

PAC_API(BOOL) pac_SyncPWMStart(HANDLE port, int slot, short enStatus);

PAC_API(BOOL) pac_SavePWMConfig(HANDLE port, int slot);

PAC_API(BOOL) pac_GetPWMDIOStatus(HANDLE port, int slot, unsigned char pwmBitArr[], unsigned char diBitArr[]);

PAC_API(BOOL) pac_SetPWMPulseCount(HANDLE port,int slot,short chIndex,long cnt);
PAC_API(BOOL) pac_GetPWMPulseCount(HANDLE port,int slot,short chIndex,long *cnt);



//=========================================================================
// Undocumented API
//=========================================================================
#define  PAC_INP        _pac_inp        //W  X
#define  PAC_OUTP       _pac_outp       //W  X
#define  PAC_MAP        _pac_map        //W
#define  PAC_SLOT_INP   _pac_slot_inp   //W  X
#define  PAC_SLOT_OUTP  _pac_slot_outp  //W  X 

PAC_PRIVATE_API(BYTE)  _pac_inp(int addr);                            //W  X
PAC_PRIVATE_API(void)  _pac_outp(int addr, BYTE val);                 //W  X
PAC_PRIVATE_API(PBYTE) _pac_map(int addr);                            //W
PAC_PRIVATE_API(BYTE)  _pac_slot_inp(BYTE slot, int addr);            //W  X
PAC_PRIVATE_API(void)  _pac_slot_outp(BYTE slot, int addr, BYTE val); //W  X
PAC_PRIVATE_API(PBYTE) _pac_slot_map(BYTE slot, int addr);            //W
PAC_PRIVATE_API(DWORD) _pac_get_slot_offset(BYTE slot);               //W  X
PAC_PRIVATE_API(PBYTE) _pac_get_base_address();                       //W  X

/************************** 16-bit ********************************/
PAC_PRIVATE_API(WORD)  _pac_inpw(int addr);                           //W  X           
PAC_PRIVATE_API(void)  _pac_outpw(int addr, WORD val);                //W  X
PAC_PRIVATE_API(WORD)  _pac_slot_inpw(BYTE slot, int addr);           //W
PAC_PRIVATE_API(void)  _pac_slot_outpw(BYTE slot, int addr, WORD val);//W
/******************************************************************/

PAC_PRIVATE_API(void)  _pac_refresh_screen();                    //W
PAC_PRIVATE_API(void)  _pac_us_delay(DWORD microsecond);         //W  X
PAC_PRIVATE_API(void)  _pac_ticks_delay(DWORD ticks);            //W  X?
PAC_PRIVATE_API(BOOL)  _pac_get_partition_info(LPTSTR szPartName, 
    LPTSTR szFileSys, LPTSTR szVolName);                        //W
PAC_PRIVATE_API(DWORD) _pac_oscr0();                             //W
PAC_PRIVATE_API(float) _pac_delay(WORD wUSec);                   //   X
PAC_PRIVATE_API(DWORD) _pac_slot_addr(BYTE slot, int addr);      //W  X 
PAC_PRIVATE_API(WORD)  _pac_get_CPUtype(void);                   //   X
PAC_PRIVATE_API(WORD)  _pac_get_HWID(void);

//=========================================================================
// Error Codes
//=========================================================================
#define  PAC_ERR_SUCCESS                     0x00000
#define  PAC_ERR_UNKNOWN                     0x00001

//Basic=====================================================================
#define  PAC_ERR_BASE                        0x10000
#define  PAC_ERR_SLOT_REGISTERED             (PAC_ERR_BASE + 1)
#define  PAC_ERR_SLOT_NOT_REGISTERED         (PAC_ERR_BASE + 2)
#define  PAC_ERR_UNKNOWN_MODULE              (PAC_ERR_BASE + 3)
#define  PAC_ERR_INVALID_MAC                 (PAC_ERR_BASE + 4)
#define  PAC_ERR_INVALID_COMPORT_NUMBER      (PAC_ERR_BASE + 5)
#define  PAC_ERR_FUNCTION_NOT_SUPPORT        (PAC_ERR_BASE + 6)
#define  PAC_ERR_MODULE_UNEXISTS             (PAC_ERR_BASE + 7)
#define  PAC_ERR_INVALID_SLOT_NUMBER         (PAC_ERR_BASE + 8)
#define  PAC_ERR_FUNCTION_REPEAT_CALLED      (PAC_ERR_BASE + 9)
#define  PAC_ERR_INVALID_HANDLE_VALUE        (PAC_ERR_BASE + 10)
#define  PAC_ERR_DEVICE_IO_CONTROL           (PAC_ERR_BASE + 11)
#define  PAC_ERR_INVALID_PARAMETER           (PAC_ERR_BASE + 12)

    //Memory Access=============================================================
#define  PAC_ERR_MEMORY_BASE                 0x11000
#define  PAC_ERR_EEP_INVALID_ADDRESS         (PAC_ERR_MEMORY_BASE + 1)
#define  PAC_ERR_SRAM_INVALID_ADDRESS        (PAC_ERR_MEMORY_BASE + 2)
#define  PAC_ERR_MEMORY_INVALID_TYPE         (PAC_ERR_MEMORY_BASE + 3)
#define  PAC_ERR_NVRAM_INVALID_ADDRESS       (PAC_ERR_MEMORY_BASE + 4)
#define  PAC_ERR_EEP_WRITE_PROTECT           (PAC_ERR_MEMORY_BASE + 5)
#define  PAC_ERR_EEP_WRITE_FAIL              (PAC_ERR_MEMORY_BASE + 6)
#define  PAC_ERR_EEP_READ_FAIL               (PAC_ERR_MEMORY_BASE + 7)
#define  PAC_ERR_MEMORY_INVALID_SIZE         (PAC_ERR_MEMORY_BASE + 8)

    //Watch Dog=================================================================
#define  PAC_ERR_WDT_BASE                    0x12000
#define  PAC_ERR_WDT_INVALID_VALUE           (PAC_ERR_WDT_BASE + 1)
#define  PAC_ERR_WDT_UNEXIST                 (PAC_ERR_WDT_BASE + 2)
#define  PAC_ERR_WDT_BASE_NOT_SET            (PAC_ERR_WDT_BASE + 3)
#define  PAC_ERR_WDT_OS_FOR_OS_STARTUP  	 (PAC_ERR_WDT_BASE + 4)
    //Interrupt=================================================================
#define  PAC_ERR_INTR_BASE                   0x13000
#define  PAC_ERR_INTR_CREATE_EVENT_FAILURE    (PAC_ERR_INTR_BASE + 1)

    //UART======================================================================
#define  PAC_ERR_UART_BASE                   0x14000
#define  PAC_ERR_UART_CHECKSUM               (PAC_ERR_UART_BASE+1)
#define  PAC_ERR_UART_READ_TIMEOUT           (PAC_ERR_UART_BASE+2)
#define  PAC_ERR_UART_RESPONSE               (PAC_ERR_UART_BASE+3)
#define  PAC_ERR_UART_UNDER_INPUT_RANGE      (PAC_ERR_UART_BASE+4)
#define  PAC_ERR_UART_EXCEED_INPUT_RANGE     (PAC_ERR_UART_BASE+5)
#define  PAC_ERR_UART_OPEN_FAILED            (PAC_ERR_UART_BASE+6)
#define  PAC_ERR_UART_GET_COMM_STATUS_ERROR  (PAC_ERR_UART_BASE+7)
#define  PAC_ERR_UART_INVALID_VALUE          (PAC_ERR_UART_BASE+8)
#define  PAC_ERR_UART_INTERNAL_BUFFER_OVERFLOW (PAC_ERR_UART_BASE+9)

    //IO========================================================================
#define  PAC_ERR_IO_BASE                     0x15000
#define  PAC_ERR_IO_NOT_SUPPORT              (PAC_ERR_IO_BASE+1)
#define  PAC_ERR_IO_ID                       (PAC_ERR_IO_BASE+2)
#define  PAC_ERR_IO_SLOT                     (PAC_ERR_IO_BASE+3)
#define  PAC_ERR_IO_CHANNEL                  (PAC_ERR_IO_BASE+4)
#define  PAC_ERR_IO_GAIN                     (PAC_ERR_IO_BASE+5)
#define  PAC_ERR_IO_INT_MODE                 (PAC_ERR_IO_BASE+6)
#define  PAC_ERR_IO_VALUE_OUT_OF_RANGE       (PAC_ERR_IO_BASE+7)
#define  PAC_ERR_IO_CHANNEL_OUT_OF_RANGE     (PAC_ERR_IO_BASE+8)
#define  PAC_ERR_IO_DO_CANNOT_OVERWRITE      (PAC_ERR_IO_BASE+10)
#define  PAC_ERR_IO_AO_CANNOT_OVERWRITE      (PAC_ERR_IO_BASE+11)

    //Backplane Timer===========================================================
#define  PAC_ERR_BPTIMER_BASE                0x16000
#define  PAC_ERR_BPTIMER_REGISTERED          (PAC_ERR_BPTIMER_BASE + 1)
#define  PAC_ERR_BPTIMER_NOT_REGISTERED      (PAC_ERR_BPTIMER_BASE + 2)
#define  PAC_ERR_OPEN_TIMER                  (PAC_ERR_BPTIMER_BASE + 3)

#ifdef __cplusplus
}
#endif


#endif // __XPACSDK_H


// Link with command line
//
// cl test.c /link XPacSDK.lib 
//
//	
// #pragma comment(lib, "XPacSDK.lib")
