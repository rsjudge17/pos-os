#ifndef _MQTT_CONFIG_H_
#define _MQTT_CONFIG_H_
#include "sdkconfig.h"



#ifdef CONFIG_MQTT_LOG_ERROR_ON
    #define mqtt_error( format, ... ) printf( "[ERROR] "format, ## __VA_ARGS__ )
#else
    #define mqtt_error( format, ... )
#endif
#ifdef CONFIG_MQTT_LOG_WARN_ON
    #define mqtt_warn( format, ... ) printf( "[WARN] "format, ## __VA_ARGS__ )
#else
    #define mqtt_warn( format, ... )
#endif
#ifdef CONFIG_MQTT_LOG_INFO_ON
    #define mqtt_info( format, ... ) printf( "[INFO] "format, ## __VA_ARGS__ )
#else
    #define mqtt_info( format, ... )
#endif

#ifndef CONFIG_MQTT_QUEUE_BUFFER_SIZE_WORD
#define CONFIG_MQTT_QUEUE_BUFFER_SIZE_WORD 1024
#endif

#endif