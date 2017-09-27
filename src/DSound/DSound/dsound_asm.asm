.386
.MODEL small, c
.code
extern mProcs:DWORD
;extern chosenOutput:DWORD
DirectSoundCaptureCreate proc
	jmp DWORD ptr mProcs[0*4]
DirectSoundCaptureCreate endp
DirectSoundCaptureCreate8 proc
	jmp DWORD ptr mProcs[1*4]
DirectSoundCaptureCreate8 endp
DirectSoundCaptureEnumerateA proc
	jmp DWORD ptr mProcs[2*4]
DirectSoundCaptureEnumerateA endp
DirectSoundCaptureEnumerateW proc
	jmp DWORD ptr mProcs[3*4]
DirectSoundCaptureEnumerateW endp
DirectSoundCreate proc
	;mov eax, chosenOutput
	;push eax
	jmp DWORD ptr mProcs[4*4]
DirectSoundCreate endp
DirectSoundCreate8 proc
	jmp DWORD ptr mProcs[5*4]
DirectSoundCreate8 endp
DirectSoundEnumerateA proc
	jmp DWORD ptr mProcs[6*4]
DirectSoundEnumerateA endp
DirectSoundEnumerateW proc
	jmp DWORD ptr mProcs[7*4]
DirectSoundEnumerateW endp
DirectSoundFullDuplexCreate proc
	jmp DWORD ptr mProcs[8*4]
DirectSoundFullDuplexCreate endp
DllCanUnloadNow proc
	jmp DWORD ptr mProcs[9*4]
DllCanUnloadNow endp
DllGetClassObject proc
	jmp DWORD ptr mProcs[10*4]
DllGetClassObject endp
GetDeviceID proc
	jmp DWORD ptr mProcs[11*4]
GetDeviceID endp
end