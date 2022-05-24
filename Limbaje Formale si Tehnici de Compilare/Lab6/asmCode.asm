bits 32
global start

extern exit
import exit msvcrt.dll

extern scanf
import scanf msvcrt.dll

extern printf
import printf msvcrt.dll

segment data use32 class=data
	 r times 4 db 0
	 p times 4 db 0
	 a times 4 db 0
	 format db "%d", 0

segment code use32 class=code
	start:
		mov AL, [2]
		mov [p], AL

		mov AL, [2]
		mov DL, 3
		mul DL
		mov [p], AL

		mov AL, [3]
		mul byte [r]
		mov [a], AL

		push dword [p]
		push dword format
		call [printf]
		add ESP, 4 * 1

		push dword [a]
		push dword format
		call [printf]
		add ESP, 4 * 1

		push dword 0
		call [exit]
