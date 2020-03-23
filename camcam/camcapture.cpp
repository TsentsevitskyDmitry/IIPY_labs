#include "camcapture.h"

CAMERA GetCamera(HWND ParentHwnd)
{
    CAMERA cam = capCreateCaptureWindow (TEXT("camera window"), WS_CHILD | WS_VISIBLE, 0, 150, 600, 400, ParentHwnd, 0);
    ShowWindow(cam,SW_SHOW);
    SendMessage(cam,WM_CAP_DRIVER_CONNECT,0,0);
    capDlgVideoSource(cam);
    capDlgVideoFormat(cam);
    capDlgVideoDisplay(cam);
    capOverlay(cam, TRUE);
    return cam;
}

void StartCam(CAMERA camhwnd)
{
    SendMessage(camhwnd,WM_CAP_DRIVER_CONNECT,0,0);
    SendMessage(camhwnd, WM_CAP_SET_SCALE, true , 0);
    SendMessage(camhwnd, WM_CAP_SET_PREVIEWRATE, 33, 0);
    SendMessage(camhwnd, WM_CAP_SET_PREVIEW, true , 0);
}

void StopCam(CAMERA camhwnd)
{
    SendMessage(camhwnd, WM_CAP_DRIVER_DISCONNECT, 0, 0);
}


void GetPicture(CAMERA camhwnd)
{
    capFileSaveDIB(camhwnd,"PICTURE.BMP");
    SendMessage(camhwnd,WM_CAP_DRIVER_CONNECT,0,0);
    SendMessage(camhwnd, WM_CAP_SET_SCALE, true , 0);
    SendMessage(camhwnd, WM_CAP_SET_PREVIEWRATE, 33, 0);
    SendMessage(camhwnd, WM_CAP_SET_PREVIEW, true , 0);
}

void StartCapture(CAMERA camhwnd)
{
    CAPTUREPARMS CaptureParms;
    CaptureParms.dwRequestMicroSecPerFrame = 80000;        // 25 images par seconde
    CaptureParms.fMakeUserHitOKToCapture = FALSE;        // Boite de dialogue pour le
    CaptureParms.wPercentDropForError = 10;                        // Message d'erreurs si nombre
    CaptureParms.fYield = FALSE;
    CaptureParms.dwIndexSize = 34952;                // Nombre total de frames capturées
    CaptureParms.wChunkGranularity = 2048;
    CaptureParms.fUsingDOSMemory = TRUE;                        // Utilisation de la mémoire pour la
    CaptureParms.wNumVideoRequested = 5;                        // Nombre de vidéo buffers alloués
    CaptureParms.fCaptureAudio = TRUE;                                // Capture du son
    CaptureParms.wNumAudioRequested = 4;        // Nombre de audio buffers alloués
    CaptureParms.vKeyAbort = VK_ESCAPE;                                // Touche d'arret de la capture
    CaptureParms.fAbortLeftMouse = FALSE;                         // Bouton gauche d'arret de la
    CaptureParms.fAbortRightMouse = FALSE;                         // Bouton droit d'arret de la
    CaptureParms.fLimitEnabled = TRUE;                                // Limite de la capture
    CaptureParms.wTimeLimit = (WORD)15;                        // Durée de capture
    CaptureParms.fMCIControl = FALSE;                                // MCI vidéo control
    CaptureParms.fStepMCIDevice = FALSE;
    CaptureParms.dwMCIStartTime = 0;
    CaptureParms.dwMCIStopTime = 0;
    CaptureParms.fStepCaptureAt2x = FALSE;                        // deux fois la résolution de la
    CaptureParms.wStepCaptureAverageFrames = 0;
    CaptureParms.dwAudioBufferSize = 0;
    CaptureParms.fDisableWriteCache = TRUE;

    capCaptureSetSetup(camhwnd, &CaptureParms, sizeof(CaptureParms));

    capFileSetCaptureFile( camhwnd, TEXT("VIDEO.AVI"));
    capFileAlloc( camhwnd, (1024L * 1024L * 5));
    capCaptureSequence(camhwnd);
}
