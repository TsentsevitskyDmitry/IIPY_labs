//Setup some defines you need to connect to a webcam
//You can put these in a header
//If you are using Microsoft Visual Studio you wont need them as they
//Are included in Microsoft's version of vfw.h

#define WM_CAP_START  0x0400
#define WM_CAP_DRIVER_CONNECT  (WM_CAP_START + 10)
#define WM_CAP_DRIVER_DISCONNECT  (WM_CAP_START + 11)
#define WM_CAP_EDIT_COPY (WM_CAP_START + 30)
#define WM_CAP_GRAB_FRAME (WM_CAP_START + 60)
#define WM_CAP_SET_SCALE (WM_CAP_START + 53)
#define WM_CAP_SET_PREVIEWRATE (WM_CAP_START + 52)
#define WM_CAP_SET_PREVIEW (WM_CAP_START + 50)
#define WM_CAP_DLG_VIDEOSOURCE  (WM_CAP_START + 42)
#define WM_CAP_STOP (WM_CAP_START+ 68)
#define WM_CAP_FILE_SAVEDIB (WM_CAP_START+  25)

//End of defines
