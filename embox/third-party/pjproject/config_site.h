#define PJ_SOCKADDR_IN_SIN_ZERO_LEN    0
#define PJ_IOQUEUE_MAX_HANDLES         8
#define PJ_LOG_USE_STACK_BUFFER        0

/* make PJSUA slim */
#define PJSUA_MAX_ACC 1
#define PJSUA_MAX_CALLS 1
#define PJSUA_MAX_VID_WINS 0
#define PJSUA_MAX_BUDDIES 1
#define PJSUA_MAX_CONF_PORTS 1
#define PJSUA_MAX_PLAYERS 1
#define PJSUA_MAX_RECORDERS 1

#if 0
#define PJMEDIA_AUDIO_DEV_HAS_OPENSL      0
#define PJMEDIA_AUDIO_DEV_HAS_ANDROID_JNI 0
#define PJMEDIA_AUDIO_DEV_HAS_BB10        0
#define PJMEDIA_AUDIO_DEV_HAS_ALSA        0
#define PJMEDIA_AUDIO_DEV_HAS_COREAUDIO   0
#define PJMEDIA_AUDIO_DEV_HAS_PORTAUDIO   1
#define PJMEDIA_AUDIO_DEV_HAS_WMME        0
#define PJMEDIA_AUDIO_DEV_HAS_BDIMAD      0
#define PJMEDIA_AUDIO_DEV_HAS_SYMB_VAS    0
#define PJMEDIA_AUDIO_DEV_HAS_SYMB_APS    0
#define PJMEDIA_AUDIO_DEV_HAS_SYMB_MDA    0
#define PJMEDIA_AUDIO_DEV_HAS_NULL_AUDIO  0
#endif