#include <windows.h>
#include <vfw.h>
#include "vfw_signals.h"

typedef HWND CAMERA;

CAMERA GetCamera(HWND ParentHwnd);  //Get cam handle

void StartCam(CAMERA cam);          // Start preview
void StopCam(CAMERA cam);           // Disable cam

void GetPicture(CAMERA cam);        // Save image (PICTURE.BMP) to the app root directory
void StartCapture(CAMERA cam);      // Start capturing 15 sec video (VIDEO.avi) in the app root directory
                                    // video durabity can be enhanced, or canseled by pressing ESC key
