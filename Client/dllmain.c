// dllmain.cpp: DLL 응용 프로그램의 진입점을 정의합니다.
#include <Windows.h>
#include <stdio.h>

int gv1 = 0;
int gv2 = 1;

__declspec (dllexport naked) void  NewChat1()//32FEF
{
	__asm
	{
		MOV     edx, [edi + 0CC4F8h]
		CMP     word ptr[eax], 2102h
		JZ label1
		RETN
		label1 :
		push    esi
		push    edi
		mov     byte ptr[eax], 8
		mov     ecx, [esp - 0x18]
		dec     ecx
		mov[esp - 0x18], ecx
		mov[eax - 8], ecx
		LEA     esi, [eax + 2]
		LEA     edi, [eax + 1]
		rep movsb
		POP     edi
		POP     esi
		MOV     edx, [edi + 0CC4F8h]
		RETN
	}
}

//push    edi
//cmp     eax, 6
//mov     edi, ecx

__declspec (dllexport naked) void  NewChat2() //1fc88
{
	__asm
	{
		pop     ebx
		push    edi
		mov     edi, ecx
		cmp     gv1, 8
		jz      label1
		push    ebx
		cmp     eax, 6
		retn
		label1 :
		mov     gv1, 0
			cmp     gv2, 1
			jnz     label2
			push    ebx
			mov     ebx, 0E9D35Ch
			add[esp], 3Fh
			retn

			label2 :
		push    ebx
			add[esp], 99h
			retn
	}
}


//6a00     push    0
//8d4c2414 lea     ecx, [esp + 40h + var_2C]
__declspec (dllexport naked) void  NewChat3()//1086412
{
	__asm
	{
		pop     ecx
		cmp     edi, 2
		jz      label1
		jmp     label2
		label1 :
		lea     eax, [esi + 4CCh]
			mov     eax, [eax + 1F0h]
			cmp     eax, 1
			jnz     label2
			mov     edi, 8
			jmp     label2
			label2 :
		push    0
			push    ecx
			lea     ecx, [esp + 0x18]
			retn
	}
}
//10038570 8D 41 FF                                lea     eax, [ecx - 1]; 
//10038573 83 F8 06                                cmp     eax, 6
__declspec (dllexport naked) void  NewChat4()
{
	__asm
	{
		//dec     eax
		//mov     esi, ecx
		lea     eax, [ecx - 1]
		cmp     gv1, 8
		jz      label1
		cmp     eax, 6
		retn
		label1 :
		mov     eax, 0E9D35Ch
			add     dword ptr[esp + 0], 31h
			retn
	}
}

//1002A0E0 8A 58 01                                mov     bl, [eax + 1]
//1002A0E3 83 C0 02                                add     eax, 2
__declspec (dllexport naked) void  NewChat5()
{
	__asm
	{
		mov     edx, eax
		add     edx, 2
		push    esi
		mov     esi, [esp + 8]
		label1:
		cmp     byte ptr[edx], 0Ch
			jz      label2
			inc     edx
			dec     esi
			jz      label4
			jmp     label1

			label2 :
		mov     byte ptr[edx], 0Ah
			mov     byte ptr[eax + 1], 2
			mov     gv1, 8
			jmp     label3

			label3 :
		pop     esi
			mov     bl, [eax + 1]
			add     eax, 2
			retn
			label4 :
		pop     esi
			mov     gv1, 0
			mov     bl, [eax + 1]
			add     eax, 2
			retn
	}
}



DWORD MsgQ()
{
	struct tagMSG Msg;
	if (!GetMessageA(&Msg, 0, 0, 0))
	{
		return 1;

	}
	do
	{
		TranslateMessage(&Msg);
		DispatchMessageA(&Msg);
	} while (GetMessageA(&Msg, 0, 0, 0));
	return 1;
}
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	FILE* out = 0;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//AllocConsole();
		//freopen_s(&out, "CON", "w", stdout);
		//printf("start");
		//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MsgQ, 0, 0, 0);
		
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

