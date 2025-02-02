#pragma once

#include <string>

typedef int IARM_EventId_t;

typedef enum _IARM_Result_t {
    IARM_RESULT_SUCCESS,
    IARM_RESULT_INVALID_PARAM,
    IARM_RESULT_INVALID_STATE,
    IARM_RESULT_IPCCORE_FAIL,
    IARM_RESULT_OOM,
} IARM_Result_t;

#define IARM_BUS_DAEMON_NAME "Daemon"

typedef IARM_Result_t (*IARM_BusCall_t)(void* arg);
typedef void (*IARM_EventHandler_t)(const char* owner, IARM_EventId_t eventId, void* data, size_t len);

class IarmBusImpl {
public:
    virtual ~IarmBusImpl() = default;

    virtual IARM_Result_t IARM_Bus_Init(const char* name) = 0;
    virtual IARM_Result_t IARM_Bus_Connect() = 0;
    virtual IARM_Result_t IARM_Bus_IsConnected(const char* memberName, int* isRegistered) = 0;
    virtual IARM_Result_t IARM_Bus_RegisterEventHandler(const char* ownerName, IARM_EventId_t eventId, IARM_EventHandler_t handler) = 0;
    virtual IARM_Result_t IARM_Bus_UnRegisterEventHandler(const char* ownerName, IARM_EventId_t eventId) = 0;
    virtual IARM_Result_t IARM_Bus_Call(const char* ownerName, const char* methodName, void* arg, size_t argLen) = 0;
    virtual IARM_Result_t IARM_Bus_RegisterCall(const char* methodName, IARM_BusCall_t handler) = 0;
};

class IarmBus {
public:
    static IarmBus& getInstance()
    {
        static IarmBus instance;
        return instance;
    }

    IarmBusImpl* impl;

    static IARM_Result_t IARM_Bus_Init(const char* name)
    {
        return getInstance().impl->IARM_Bus_Init(name);
    }

    static IARM_Result_t IARM_Bus_Connect()
    {
        return getInstance().impl->IARM_Bus_Connect();
    }

    static IARM_Result_t IARM_Bus_IsConnected(const char* memberName, int* isRegistered)
    {
        return getInstance().impl->IARM_Bus_IsConnected(memberName, isRegistered);
    }

    static IARM_Result_t IARM_Bus_RegisterEventHandler(const char* ownerName, IARM_EventId_t eventId, IARM_EventHandler_t handler)
    {
        return getInstance().impl->IARM_Bus_RegisterEventHandler(ownerName, eventId, handler);
    }

    static IARM_Result_t IARM_Bus_UnRegisterEventHandler(const char* ownerName, IARM_EventId_t eventId)
    {
        return getInstance().impl->IARM_Bus_UnRegisterEventHandler(ownerName, eventId);
    }
    static IARM_Result_t IARM_Bus_Call(const char* ownerName, const char* methodName, void* arg, size_t argLen)
    {
        return getInstance().impl->IARM_Bus_Call(ownerName, methodName, arg, argLen);
    }

    static IARM_Result_t IARM_Bus_RegisterCall(const char* methodName, IARM_BusCall_t handler)
    {
        return getInstance().impl->IARM_Bus_RegisterCall(methodName, handler);
    }
};

constexpr auto IARM_Bus_Init = &IarmBus::IARM_Bus_Init;
constexpr auto IARM_Bus_Connect = &IarmBus::IARM_Bus_Connect;
constexpr auto IARM_Bus_IsConnected = &IarmBus::IARM_Bus_IsConnected;
constexpr auto IARM_Bus_RegisterEventHandler = &IarmBus::IARM_Bus_RegisterEventHandler;
constexpr auto IARM_Bus_UnRegisterEventHandler = &IarmBus::IARM_Bus_UnRegisterEventHandler;
constexpr auto IARM_Bus_Call = &IarmBus::IARM_Bus_Call;
constexpr auto IARM_Bus_RegisterCall = &IarmBus::IARM_Bus_RegisterCall;

#define IARM_BUS_COMMON_API_SysModeChange "SysModeChange"

typedef enum _IARM_Bus_Daemon_PowerState_t {
    IARM_BUS_PWRMGR_POWERSTATE_OFF,
    IARM_BUS_PWRMGR_POWERSTATE_STANDBY,
    IARM_BUS_PWRMGR_POWERSTATE_ON,
    IARM_BUS_PWRMGR_POWERSTATE_STANDBY_LIGHT_SLEEP,
    IARM_BUS_PWRMGR_POWERSTATE_STANDBY_DEEP_SLEEP
} IARM_Bus_PowerState_t;

typedef IARM_Bus_PowerState_t IARM_Bus_PWRMgr_PowerState_t;

typedef enum _IARM_Bus_Daemon_SysMode_t {
    IARM_BUS_SYS_MODE_NORMAL,
    IARM_BUS_SYS_MODE_EAS,
    IARM_BUS_SYS_MODE_WAREHOUSE
} IARM_Bus_Daemon_SysMode_t;

#define IARMBUS_AUDIOCAPTUREMGR_NAME "audiocapturemgr"
#define IARMBUS_AUDIOCAPTUREMGR_REQUEST_SAMPLE "requestSample"

#define IARMBUS_AUDIOCAPTUREMGR_OPEN "open"
#define IARMBUS_AUDIOCAPTUREMGR_CLOSE "close"
#define IARMBUS_AUDIOCAPTUREMGR_START "start"
#define IARMBUS_AUDIOCAPTUREMGR_STOP "stop"
#define IARMBUS_AUDIOCAPTUREMGR_GET_DEFAULT_AUDIO_PROPS "getDefaultAudioProperties"
#define IARMBUS_AUDIOCAPTUREMGR_GET_AUDIO_PROPS "getAudioProperties"
#define IARMBUS_AUDIOCAPTUREMGR_GET_OUTPUT_PROPS "getOutputProperties"
#define IARMBUS_AUDIOCAPTUREMGR_SET_AUDIO_PROPERTIES "setAudioProperties"
#define IARMBUS_AUDIOCAPTUREMGR_SET_OUTPUT_PROPERTIES "setOutputProperties"

#define AUDIOCAPTUREMGR_FILENAME_PREFIX "audio_sample"
#define AUDIOCAPTUREMGR_FILE_PATH "/opt/"

#define DATA_CAPTURE_IARM_EVENT_AUDIO_CLIP_READY 100

#define ACM_RESULT_GENERAL_FAILURE 0
#define ACM_RESULT_PRECAPTURE_NOT_SUPPORTED 1
#define ACM_RESULT_STREAM_UNAVAILABLE 2
#define ACM_RESULT_DURATION_OUT_OF_BOUNDS 3
#define BUFFERED_FILE_OUTPUT ""

enum Format {
    acmFormate16BitStereo,
    acmFormate16BitMonoLeft,
    acmFormate16BitMonoRight,
    acmFormate16BitMono,
    acmFormate24BitStereo,
    acmFormate24Bit5_1
};

enum Sampling_frequency {
    acmFreqe48000,
    acmFreqe44100,
    acmFreqe32000,
    acmFreqe24000,
    acmFreqe16000
};

namespace audiocapturemgr {
using session_id_t = int;

struct audio_properties_ifce_t {
    Format format;
    Sampling_frequency sampling_frequency;
};
}

struct iarmbus_notification_payload_t {
    char dataLocator[64];
};

struct iarmbus_acm_arg_t {
    struct iarmbus_open_args {
        int source;
        std::string output_type;
    };

    struct iarmbus_request_payload_t {
        float duration;
        bool is_precapture;
    };

    struct output_t {
        unsigned int buffer_duration;
        unsigned int max_buffer_duration;
    };

    struct arg_output_props_t {
        output_t output;
    };

    struct Details {
        iarmbus_open_args arg_open;
        audiocapturemgr::audio_properties_ifce_t arg_audio_properties;
        iarmbus_request_payload_t arg_sample_request;
        arg_output_props_t arg_output_props;
    };

    int session_id;
    int result;
    Details details;
};

#define IARM_BUS_CECMGR_NAME "CECMgr"
#define IARM_BUS_CECMGR_MAX_DATA_LENGTH 62
#define IARM_BUS_CECMGR_API_Send "Send"

typedef struct _IARM_Bus_CECMgr_Send_Param_t {
    uint8_t length;
    uint8_t data[IARM_BUS_CECMGR_MAX_DATA_LENGTH + 1];
    uint8_t retVal;
} IARM_Bus_CECMgr_Send_Param_t;

#define IARM_BUS_DEEPSLEEPMGR_NAME "DEEPSLEEPMgr"

#define IARM_BUS_DEEPSLEEPMGR_API_GetLastWakeupReason "GetLastWakeupReason"
#define IARM_BUS_DEEPSLEEPMGR_API_GetLastWakeupKeyCode "GetLastWakeupKeycode"

typedef enum _DeepSleep_WakeupReason_t {
    DEEPSLEEP_WAKEUPREASON_IR = 0,
    DEEPSLEEP_WAKEUPREASON_RCU_BT,
    DEEPSLEEP_WAKEUPREASON_RCU_RF4CE,
    DEEPSLEEP_WAKEUPREASON_GPIO,
    DEEPSLEEP_WAKEUPREASON_LAN,
    DEEPSLEEP_WAKEUPREASON_WLAN,
    DEEPSLEEP_WAKEUPREASON_TIMER,
    DEEPSLEEP_WAKEUPREASON_FRONT_PANEL,
    DEEPSLEEP_WAKEUPREASON_WATCHDOG,
    DEEPSLEEP_WAKEUPREASON_SOFTWARE_RESET,
    DEEPSLEEP_WAKEUPREASON_THERMAL_RESET,
    DEEPSLEEP_WAKEUPREASON_WARM_RESET,
    DEEPSLEEP_WAKEUPREASON_COLDBOOT,
    DEEPSLEEP_WAKEUPREASON_STR_AUTH_FAILURE,
    DEEPSLEEP_WAKEUPREASON_CEC,
    DEEPSLEEP_WAKEUPREASON_PRESENCE,
    DEEPSLEEP_WAKEUPREASON_VOICE,
    DEEPSLEEP_WAKEUPREASON_UNKNOWN
} DeepSleep_WakeupReason_t;

typedef struct _IARM_Bus_DeepSleepMgr_WakeupKeyCode_Param_t {
    unsigned int keyCode;
} IARM_Bus_DeepSleepMgr_WakeupKeyCode_Param_t;

#define IARM_BUS_MFRLIB_NAME "MFRLib"
#define IARM_BUS_MFRLIB_API_SetBootLoaderPattern "mfrSetBootloaderPattern"
#define IARM_BUS_MFRLIB_API_GetSerializedData "mfrGetManufacturerData"

typedef enum _mfrSerializedType_t {
    mfrSERIALIZED_TYPE_MANUFACTURER = 0,
    mfrSERIALIZED_TYPE_MANUFACTUREROUI,
    mfrSERIALIZED_TYPE_MODELNAME,
    mfrSERIALIZED_TYPE_DESCRIPTION,
    mfrSERIALIZED_TYPE_PRODUCTCLASS,
    mfrSERIALIZED_TYPE_SERIALNUMBER,
    mfrSERIALIZED_TYPE_HARDWAREVERSION,
    mfrSERIALIZED_TYPE_SOFTWAREVERSION,
    mfrSERIALIZED_TYPE_PROVISIONINGCODE,
    mfrSERIALIZED_TYPE_FIRSTUSEDATE,
    mfrSERIALIZED_TYPE_DEVICEMAC,
    mfrSERIALIZED_TYPE_MOCAMAC,
    mfrSERIALIZED_TYPE_HDMIHDCP,
    mfrSERIALIZED_TYPE_PDRIVERSION,
    mfrSERIALIZED_TYPE_WIFIMAC,
    mfrSERIALIZED_TYPE_BLUETOOTHMAC,
    mfrSERIALIZED_TYPE_WPSPIN,
    mfrSERIALIZED_TYPE_MANUFACTURING_SERIALNUMBER,
    mfrSERIALIZED_TYPE_SKYMODELNAME,
    mfrSERIALIZED_TYPE_HWID,
    mfrSERIALIZED_TYPE_MAX,
} mfrSerializedType_t;

typedef enum _mfrBlPattern_t {
    mfrBL_PATTERN_NORMAL = 0,
    mfrBL_PATTERN_SILENT,
    mfrBL_PATTERN_SILENT_LED_ON
} mfrBlPattern_t;

typedef struct _IARM_Bus_MFRLib_SetBLPattern_Param_t {
    mfrBlPattern_t pattern;
} IARM_Bus_MFRLib_SetBLPattern_Param_t;

typedef struct _IARM_Bus_MFRLib_GetSerializedData_Param_t {
    mfrSerializedType_t type;
    char buffer[1280];
    int bufLen;
} IARM_Bus_MFRLib_GetSerializedData_Param_t;

#define PWRMGR_MAX_REBOOT_REASON_LENGTH 100

#define MAX_PWR_STATE_BEF_REBOOR_STR_LEN (32)
#define IARM_BUS_PWRMGR_API_GetPowerStateBeforeReboot "GetPowerStateBeforeReboot"
#define IARM_BUS_PWRMGR_API_SetStandbyVideoState "SetStandbyVideoState"
#define IARM_BUS_PWRMGR_API_GetStandbyVideoState "GetStandbyVideoState"
#define IARM_BUS_PWRMGR_API_SetNetworkStandbyMode "SetNetworkStandbyMode"
#define IARM_BUS_PWRMGR_API_GetNetworkStandbyMode "GetNetworkStandbyMode"
#define IARM_BUS_PWRMGR_API_Reboot "performReboot"

typedef struct _IARM_Bus_PWRMgr_NetworkStandbyMode_Param_t {
    bool bStandbyMode;
} IARM_Bus_PWRMgr_NetworkStandbyMode_Param_t;

typedef struct _IARM_Bus_PWRMgr_GetPowerStateBeforeReboot_Param_t {
    char powerStateBeforeReboot[MAX_PWR_STATE_BEF_REBOOR_STR_LEN];
} IARM_Bus_PWRMgr_GetPowerStateBeforeReboot_Param_t;

typedef struct _IARM_Bus_PWRMgr_SetDeepSleepTimeOut_Param_t {
    unsigned int timeout;
} IARM_Bus_PWRMgr_SetDeepSleepTimeOut_Param_t;

typedef enum _IARM_Bus_PWRMgr_ThermalState_t {
    IARM_BUS_PWRMGR_TEMPERATURE_NORMAL = 0,
    IARM_BUS_PWRMGR_TEMPERATURE_HIGH,
    IARM_BUS_PWRMGR_TEMPERATURE_CRITICAL
} IARM_Bus_PWRMgr_ThermalState_t;

typedef enum _WakeupSrcType_t {
    WAKEUPSRC_VOICE = 0,
    WAKEUPSRC_PRESENCE_DETECTION,
    WAKEUPSRC_BLUETOOTH,
    WAKEUPSRC_WIFI,
    WAKEUPSRC_IR,
    WAKEUPSRC_POWER_KEY,
    WAKEUPSRC_TIMER,
    WAKEUPSRC_CEC,
    WAKEUPSRC_LAN
} WakeupSrcType_t;

typedef struct _PWRMgr_EventData_t {
    union {
        struct _MODE_DATA {
            IARM_Bus_PWRMgr_PowerState_t curState;
            IARM_Bus_PWRMgr_PowerState_t newState;
            uint32_t deep_sleep_timeout;
            bool nwStandbyMode;
        } state;
        struct _THERM_DATA {
            IARM_Bus_PWRMgr_ThermalState_t curLevel;
            IARM_Bus_PWRMgr_ThermalState_t newLevel;
            float curTemperature;
        } therm;
        bool bNetworkStandbyMode;
        int32_t reset_sequence_progress;
    } data;
} IARM_Bus_PWRMgr_EventData_t;

typedef struct _IARM_Bus_PWRMgr_GetThermalState_Param_t {
    IARM_Bus_PWRMgr_ThermalState_t curLevel;
    float curTemperature;
} IARM_Bus_PWRMgr_GetThermalState_Param_t;

typedef struct _IARM_Bus_PWRMgr_GetTempThresholds_Param_t {
    float tempHigh;
    float tempCritical;
} IARM_Bus_PWRMgr_GetTempThresholds_Param_t;

typedef struct _IARM_Bus_PWRMgr_SetTempThresholds_Param_t {
    float tempHigh;
    float tempCritical;
} IARM_Bus_PWRMgr_SetTempThresholds_Param_t;

typedef struct _IARM_Bus_PWRMgr_GetOvertempGraceInterval_Param_t {
    int graceInterval;
} IARM_Bus_PWRMgr_GetOvertempGraceInterval_Param_t;

typedef struct _IARM_Bus_PWRMgr_SetOvertempGraceInterval_Param_t {
    int graceInterval;
} IARM_Bus_PWRMgr_SetOvertempGraceInterval_Param_t;

typedef struct _IARM_Bus_CommonAPI_SysModeChange_Param_t {
    IARM_Bus_Daemon_SysMode_t oldMode;
    IARM_Bus_Daemon_SysMode_t newMode;
} IARM_Bus_CommonAPI_SysModeChange_Param_t;

typedef enum _PWRMgr_EventId_t {
    IARM_BUS_PWRMGR_EVENT_MODECHANGED = 0,
    IARM_BUS_PWRMGR_EVENT_DEEPSLEEP_TIMEOUT,
    IARM_BUS_PWRMGR_EVENT_RESET_SEQUENCE,
    IARM_BUS_PWRMGR_EVENT_REBOOTING,
    IARM_BUS_PWRMGR_EVENT_THERMAL_MODECHANGED,
    IARM_BUS_PWRMGR_EVENT_WAREHOUSEOPS_STATUSCHANGED,
    IARM_BUS_PWRMGR_EVENT_NETWORK_STANDBYMODECHANGED,
    IARM_BUS_PWRMGR_EVENT_MAX,
} IARM_Bus_PWRMgr_EventId_t;

typedef struct _IARM_Bus_PWRMgr_RebootParam_t {
    char reboot_reason_custom[PWRMGR_MAX_REBOOT_REASON_LENGTH];
    char reboot_reason_other[PWRMGR_MAX_REBOOT_REASON_LENGTH];
    char requestor[PWRMGR_MAX_REBOOT_REASON_LENGTH];
} IARM_Bus_PWRMgr_RebootParam_t;

#define IARM_BUS_PWRMGR_NAME "PWRMgr"
#define IARM_BUS_PWRMGR_API_SetPowerState "SetPowerState"
#define IARM_BUS_PWRMGR_API_GetPowerState "GetPowerState"

typedef struct _IARM_Bus_PWRMgr_SetPowerState_Param_t {
    IARM_Bus_PWRMgr_PowerState_t newState;
    int keyCode;
} IARM_Bus_PWRMgr_SetPowerState_Param_t;

typedef struct _IARM_Bus_PWRMgr_GetPowerState_Param_t {
    IARM_Bus_PWRMgr_PowerState_t curState;
} IARM_Bus_PWRMgr_GetPowerState_Param_t;

#define IARM_BUS_PWRMGR_API_GetThermalState "GetThermalState"
#define IARM_BUS_PWRMGR_API_GetTemperatureThresholds "GetTemperatureThresholds"
#define IARM_BUS_PWRMGR_API_SetTemperatureThresholds "SetTemperatureThresholds"
#define IARM_BUS_PWRMGR_API_GetOvertempGraceInterval "GetOvertempGraceInterval"
#define IARM_BUS_PWRMGR_API_SetOvertempGraceInterval "SetOvertempGraceInterval"

typedef struct _IARM_Bus_PWRMgr_SetWakeupSrcConfig_Param_t {
    WakeupSrcType_t srcType;
    bool config;
} IARM_Bus_PWRMgr_SetWakeupSrcConfig_Param_t;
#define IARM_BUS_PWRMGR_API_SetWakeupSrcConfig "setWakeupSrcConfig"

#define IARM_BUS_SYSMGR_NAME "SYSMgr"
#define IARM_BUS_SYSMGR_API_GetSystemStates "GetSystemStates"

typedef enum _SYSMgr_EventId_t {
    IARM_BUS_SYSMGR_EVENT_SYSTEMSTATE,
    IARM_BUS_SYSMGR_EVENT_XUPNP_DATA_REQUEST, /*!< Xupnp data  request frm Receiver to UPNP*/
    IARM_BUS_SYSMGR_EVENT_XUPNP_DATA_UPDATE, /*!< Xupnp data  frm  UPNP to  Receiver*/
    IARM_BUS_SYSMGR_EVENT_IMAGE_DNLD, /*Image download status to Receiver   */
    IARM_BUS_SYSMGR_EVENT_CARD_FWDNLD, /*!< CARD FW download event to Receiver - Valid on Cisco CA*/
    IARM_BUS_SYSMGR_EVENT_HDCP_PROFILE_UPDATE, /*!< HDCP Profile Update */
    IARM_BUS_SYSMGR_EVENT_INTRUSION, /*!< Intrusion Detection */
    IARM_BUS_SYSMGR_EVENT_EISS_FILTER_STATUS, /*!< EISS Filter status event */
    IARM_BUS_SYSMGR_EVENT_EISS_APP_ID_UPDATE, /*!< EISS App ID update */
    IARM_BUS_SYSMGR_EVENT_KEYCODE_LOGGING_CHANGED, /*!< Key Code logging status update */
    IARM_BUS_SYSMGR_EVENT_USB_MOUNT_CHANGED, /*!< Fires when USB mounts change */
    IARM_BUS_SYSMGR_EVENT_APP_RELEASE_FOCUS, /*!< Application fires event to release focus*/
    IARM_BUS_SYSMGR_EVENT_MAX /*!< Max Event Id */
} IARM_Bus_SYSMgr_EventId_t;

typedef struct _IARM_BUS_SYSMGR_KEYCodeLoggingInfo_Param_t {
    int logStatus; /*!< HDCP Profile Data */
} IARM_BUS_SYSMGR_KEYCodeLoggingInfo_Param_t;

#define IARM_BUS_SYSMGR_API_GetKeyCodeLoggingPref "GetKeyCodeLoggingPref"
#define IARM_BUS_SYSMGR_API_SetKeyCodeLoggingPref "SetKeyCodeLoggingPref"

typedef enum _SYSMgr_SystemState_t {
    IARM_BUS_SYSMGR_SYSSTATE_CHANNELMAP, //0
    IARM_BUS_SYSMGR_SYSSTATE_DISCONNECTMGR, //1
    IARM_BUS_SYSMGR_SYSSTATE_TUNEREADY, //2
    IARM_BUS_SYSMGR_SYSSTATE_EXIT_OK, //3
    IARM_BUS_SYSMGR_SYSSTATE_CMAC, //4
    IARM_BUS_SYSMGR_SYSSTATE_MOTO_ENTITLEMENT, //5
    IARM_BUS_SYSMGR_SYSSTATE_MOTO_HRV_RX, //6
    IARM_BUS_SYSMGR_SYSSTATE_CARD_CISCO_STATUS, //7
    IARM_BUS_SYSMGR_SYSSTATE_VIDEO_PRESENTING, //8
    IARM_BUS_SYSMGR_SYSSTATE_HDMI_OUT, //9
    IARM_BUS_SYSMGR_SYSSTATE_HDCP_ENABLED, //10
    IARM_BUS_SYSMGR_SYSSTATE_HDMI_EDID_READ, //11
    IARM_BUS_SYSMGR_SYSSTATE_FIRMWARE_DWNLD, //12
    IARM_BUS_SYSMGR_SYSSTATE_TIME_SOURCE, //13
    IARM_BUS_SYSMGR_SYSSTATE_TIME_ZONE, //14
    IARM_BUS_SYSMGR_SYSSTATE_CA_SYSTEM, //15
    IARM_BUS_SYSMGR_SYSSTATE_ESTB_IP, //16
    IARM_BUS_SYSMGR_SYSSTATE_ECM_IP, //17
    IARM_BUS_SYSMGR_SYSSTATE_LAN_IP, //18
    IARM_BUS_SYSMGR_SYSSTATE_MOCA, //19
    IARM_BUS_SYSMGR_SYSSTATE_DOCSIS, //20
    IARM_BUS_SYSMGR_SYSSTATE_DSG_BROADCAST_CHANNEL, //21
    IARM_BUS_SYSMGR_SYSSTATE_DSG_CA_TUNNEL, //22
    IARM_BUS_SYSMGR_SYSSTATE_CABLE_CARD, //23
    IARM_BUS_SYSMGR_SYSSTATE_CABLE_CARD_DWNLD, //24
    IARM_BUS_SYSMGR_SYSSTATE_CVR_SUBSYSTEM, //25
    IARM_BUS_SYSMGR_SYSSTATE_DOWNLOAD, //26
    IARM_BUS_SYSMGR_SYSSTATE_VOD_AD, //27
    IARM_BUS_SYSMGR_SYSSTATE_DAC_INIT_TIMESTAMP, //28
    IARM_BUS_SYSMGR_SYSSTATE_CABLE_CARD_SERIAL_NO, //29
    IARM_BUS_SYSMGR_SYSSTATE_ECM_MAC, //30
    IARM_BUS_SYSMGR_SYSSTATE_DAC_ID, //31
    IARM_BUS_SYSMGR_SYSSTATE_PLANT_ID, //32
    IARM_BUS_SYSMGR_SYSSTATE_STB_SERIAL_NO, //33
    IARM_BUS_SYSMGR_SYSSTATE_BOOTUP, //34
    IARM_BUS_SYSMGR_SYSSTATE_GATEWAY_CONNECTION, //35
    IARM_BUS_SYSMGR_SYSSTATE_DST_OFFSET, //36
    IARM_BUS_SYSMGR_SYSSTATE_RF_CONNECTED, //37
    IARM_BUS_SYSMGR_SYSSTATE_PARTNERID_CHANGE, //38
    IARM_BUS_SYSMGR_SYSSTATE_IP_MODE, //39
    IARM_BUS_SYSMGR_SYSSTATE_LP_CONNECTION_RESET, //40
    IARM_BUS_SYSMGR_SYSSTATE_RWS_CONNECTION_RESET, //41
    IARM_BUS_SYSMGR_SYSSTATE_QAM_READY, //42
    IARM_BUS_SYSMGR_SYSSTATE_FIRMWARE_UPDATE_STATE //43, Added as part of RDK-19978, As the IARM
} IARM_Bus_SYSMgr_SystemState_t;

typedef enum _SYSMgr_FirmwareUpdateState_t {
    IARM_BUS_SYSMGR_FIRMWARE_UPDATE_STATE_UNINITIALIZED = 0,
    IARM_BUS_SYSMGR_FIRMWARE_UPDATE_STATE_REQUESTING = 1,
    IARM_BUS_SYSMGR_FIRMWARE_UPDATE_STATE_DOWNLOADING = 2,
    IARM_BUS_SYSMGR_FIRMWARE_UPDATE_STATE_FAILED = 3,
    IARM_BUS_SYSMGR_FIRMWARE_UPDATE_STATE_DOWNLOAD_COMPLETE = 4,
    IARM_BUS_SYSMGR_FIRMWARE_UPDATE_STATE_VALIDATION_COMPLETE = 5,
    IARM_BUS_SYSMGR_FIRMWARE_UPDATE_STATE_PREPARING_TO_REBOOT = 6,
    IARM_BUS_SYSMGR_FIRMWARE_UPDATE_STATE_ONHOLD_FOR_OPTOUT = 7, /* On Hold for opt-out */
    IARM_BUS_SYSMGR_FIRMWARE_UPDATE_STATE_CRITICAL_REBOOT = 8
} IARM_Bus_SYSMGR_FirmwareUpdateState_t;

typedef struct _IARM_BUS_SYSMgr_EventData_t {
    union {
        struct _CARD_FWDNLD_DATA {
            char eventType;
            char status;
        } cardFWDNLD;
        struct _IMAGE_FWDNLD_DATA {
            char status;
        } imageFWDNLD;
        struct _XUPNP_DATA {
            unsigned long deviceInfoLength;
        } xupnpData;
        struct _HDCP_PROFILE {
            unsigned int hdcpProfile;
        } hdcpProfileData;
        struct _SystemStates {
            IARM_Bus_SYSMgr_SystemState_t stateId;
            int state;
            int error;
            char payload[128];
        } systemStates;
        struct _EISS_STATUS {
            int filterStatus;
        } eissEventData;
        struct _EISS_APP_ID {
            unsigned char idList[4][6];
            int count;
        } eissAppIDList;
        struct _KEY_CODE_LOG {
            int logStatus;
        } keyCodeLogData;
        struct _USB_MOUNT {
            int mounted;
            char device[128];
            char dir[256];
        } usbMountData;

    } data;
} IARM_Bus_SYSMgr_EventData_t;

typedef struct _propertyValue {
    int state;
    int error;
    char payload[128];
} state_property;

typedef struct _IARM_Bus_SYSMgr_GetSystemStates_Param_t {
    state_property channel_map;
    state_property disconnect_mgr_state;
    state_property TuneReadyStatus;
    state_property exit_ok_key_sequence;
    state_property cmac;
    state_property card_moto_entitlements;
    state_property card_moto_hrv_rx;
    state_property dac_init_timestamp;
    state_property card_cisco_status;
    state_property video_presenting;
    state_property hdmi_out;
    state_property hdcp_enabled;
    state_property hdmi_edid_read;
    state_property firmware_download;
    state_property time_source;
    state_property time_zone_available;
    state_property ca_system;
    state_property estb_ip;
    state_property ecm_ip;
    state_property lan_ip;
    state_property moca;
    state_property docsis;
    state_property dsg_broadcast_tunnel;
    state_property dsg_ca_tunnel;
    state_property cable_card;
    state_property cable_card_download;
    state_property cvr_subsystem;
    state_property download;
    state_property vod_ad;
    state_property card_serial_no;
    state_property ecm_mac;
    state_property dac_id;
    state_property plant_id;
    state_property stb_serial_no;
    state_property bootup;
    state_property dst_offset;
    state_property rf_connected;
    state_property ip_mode;
    state_property qam_ready_status;
    state_property firmware_update_state;
} IARM_Bus_SYSMgr_GetSystemStates_Param_t;

#define IARM_BUS_DSMGR_NAME "DSMgr"

/*! Events published from DS Mananger */
typedef enum _DSMgr_EventId_t {
    IARM_BUS_DSMGR_EVENT_RES_PRECHANGE = 0, /*!< Resolution Pre Change Event  */
    IARM_BUS_DSMGR_EVENT_RES_POSTCHANGE, /*!< Resolution Post Change Event  */
    IARM_BUS_DSMGR_EVENT_ZOOM_SETTINGS, /*!< Zoom Settings Events */
    IARM_BUS_DSMGR_EVENT_HDMI_HOTPLUG, /*!< HDMI HPD DETECT Change Event  */
    IARM_BUS_DSMGR_EVENT_AUDIO_MODE, /*!< HDMI HPD DETECT Change Event  */
    IARM_BUS_DSMGR_EVENT_HDCP_STATUS, /*!< HDMI HDCP status */
    IARM_BUS_DSMGR_EVENT_RX_SENSE, /*!< HDMI Rx Sense status */
    IARM_BUS_DSMGR_EVENT_HDMI_IN_HOTPLUG, /*!< HDMI IN HPD change event */
    IARM_BUS_DSMGR_EVENT_HDMI_IN_SIGNAL_STATUS, /*!< HDMI IN signal status change event */
    IARM_BUS_DSMGR_EVENT_HDMI_IN_STATUS, /*!< HDMI IN status change event */
    IARM_BUS_DSMGR_EVENT_HDMI_IN_VIDEO_MODE_UPDATE, /*!< HDMI IN video mode update event */
    IARM_BUS_DSMGR_EVENT_HDMI_IN_ALLM_STATUS, /*!< HDMI IN ALLM mode update event */
    IARM_BUS_DSMGR_EVENT_COMPOSITE_IN_HOTPLUG, /*!< COMPOSITE IN HPD change event */
    IARM_BUS_DSMGR_EVENT_COMPOSITE_IN_SIGNAL_STATUS, /*!< COMPOSITE IN signal status change event */
    IARM_BUS_DSMGR_EVENT_COMPOSITE_IN_STATUS, /*!< COMPOSITE IN status change event */
    IARM_BUS_DSMGR_EVENT_TIME_FORMAT_CHANGE, /*!< Clock Time Format Change Event*/
    IARM_BUS_DSMGR_EVENT_AUDIO_LEVEL_CHANGED, /*!< Audio Level Change Event*/
    IARM_BUS_DSMGR_EVENT_AUDIO_OUT_HOTPLUG, /*!< AUDIO OUT HPD change event */
    IARM_BUS_DSMGR_EVENT_AUDIO_FORMAT_UPDATE, /*!< Audio Format change event */
    IARM_BUS_DSMGR_EVENT_AUDIO_PRIMARY_LANGUAGE_CHANGED, /*!< Audio Primary Language change event */
    IARM_BUS_DSMGR_EVENT_AUDIO_SECONDARY_LANGUAGE_CHANGED, /*!< Audio Secondary Language change event */
    IARM_BUS_DSMGR_EVENT_AUDIO_FADER_CONTROL_CHANGED, /*!< Audio Fader Control change event */
    IARM_BUS_DSMGR_EVENT_AUDIO_ASSOCIATED_AUDIO_MIXING_CHANGED, /*!< Audio Associated Audio Mixing change event */
    IARM_BUS_DSMGR_EVENT_VIDEO_FORMAT_UPDATE, /*!< Video Format change event */
    IARM_BUS_DSMGR_EVENT_DISPLAY_FRAMRATE_PRECHANGE, /*!< Frame rate pre change */
    IARM_BUS_DSMGR_EVENT_DISPLAY_FRAMRATE_POSTCHANGE, /*!< Frame rate post change */
    IARM_BUS_DSMGR_EVENT_AUDIO_PORT_STATE, /*!< Audio Port Init State */
    IARM_BUS_DSMGR_EVENT_SLEEP_MODE_CHANGED, /*!< Sleep Mode Change Event*/
    IARM_BUS_DSMGR_EVENT_MAX, /*!< Max Event  */
} IARM_Bus_DSMgr_EventId_t;
