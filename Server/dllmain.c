// dllmain.cpp: DLL 응용 프로그램의 진입점을 정의합니다.
#include <Windows.h>

DWORD ServerSendMessage = 0x0043E0E0;
DWORD FormatString = 0x0040836C;//mapcenter func
DWORD FormatStringMapServer = 0x0048236A;
DWORD FindArmy = 0x0048849C;
DWORD SendArmyChat = 0x00463070;

char ChatString[7] = "%s%c%s";
char ChatString2[3] = "%d";
char SLString[13] = "%d:%d:%d:%d.";

int gv1 = 0;
int gv2 = 0;

__declspec (dllexport naked) void  NewMapServerChat()// global/alliance chat functions
{
	__asm
	{
		cmp dword ptr[esp], 0x0043f49d //->0043f49d
		je func1
		cmp dword ptr[esp], 0x0043FCFB //->0043FCFB
		je func2
		cmp dword ptr[esp], 0x0046312f //->0046312f
		je func3
		cmp dword ptr[esp], 0x0043fd19 //->0043fd19
		je func4

		/*
		cmp dword ptr[esp], 0x004410BD
		je func1
		cmp dword ptr[esp], 0x0044186B
		je func2
		cmp dword ptr[esp], 0x00473B9F
		je func3
		cmp dword ptr[esp], 0x00441889
		je func4
		*/

	func1:
		MOV EAX, DWORD PTR[ESP + 0x10]//stm
			MOVSX ECX, BYTE PTR[EAX]//st
			cmp ecx, 8
			je gchat
			cmp ecx, 9
			je achat
			retn
			gchat :
		mov dword ptr[esp], 0x0043F4FB
			retn
			achat :
		mov dword ptr[esp], 0x0043F4FB
			retn

			func2 :
		//cmp byte ptr[ebx], 8
		cmp byte ptr[edi - 1], 8
			je func2gchat
			MOV EAX, DWORD PTR[ESI + 0x4520] //0x42C8 이엿던거
			retn
			func2gchat :

		cmp DWORD PTR[ESI + 0x3800], 10 //37F8
			jae func2next
			push eax
			push ecx
			push edx
			LEA EAX, DWORD PTR[ESP + 0x30]
			push 4
			push eax
			push 23
			mov ecx, esi
			MOV DWORD PTR[ESP + 0x3C], 10
			CALL ServerSendMessage
			pop edx
			pop ecx
			pop eax
			jmp func2exit1
			func2next :
		mov dword ptr[esp], 0x0043FCFF //0x0044186F
			retn
			func2exit1 :
		mov dword ptr[esp], 0x0043FD27 //0x00441897
			retn

			func3 :
		MOV EAX, DWORD PTR[ESP + 0x18]
			NOT ECX

			mov edx, dword ptr[esp + 0x0C]
			cmp byte ptr[edx - 1], 8
			je func3gchat
			retn
			func3gchat :
		mov byte ptr[ebx], 8
			retn


			func4 :

		add esp, 4
			push eax
			call SendArmyChat
			push 0x0043FD27
			retn
	}
}

__declspec (dllexport naked) void  NewMapCenterChat()
{
	__asm
	{

		cmp dword ptr[esp], 0x00404D77//->
		je func1
		cmp dword ptr[esp], 0x00404F8E//->
		je func2
		cmp dword ptr[esp], 0x00407133//->00407133
		je func3
		cmp dword ptr[esp], 0x00405243//->
		je func4


		/*
		cmp dword ptr[esp], 0x00404D77
		je func1
		cmp dword ptr[esp], 0x00404F8E
		je func2
		cmp dword ptr[esp], 0x00407043
		je func3
		cmp dword ptr[esp], 0x00405243
		je func4
		*/
	func1:
		cmp esi, 8
			je gchat

			ADD ESI, -3//st
			CMP ESI, 3//st
			retn
			gchat :
		mov dword ptr[esp], 0x00404D8D
			retn



			func2 :
		mov eax, dword ptr[esp + 0x8]
			cmp eax, 8
			je func2gchat
			MOV EAX, DWORD PTR[ESI + 0x21C4]//st
			retn
			func2gchat :
		mov dword ptr[esp], 0x00404FA4
			retn


			func3 :
		mov eax, dword ptr[esp + 0x44]
			cmp eax, 8
			je func3gchat
			pop eax
			push 0x0040DA28//st
			push ecx//st
			push eax
			retn
			func3gchat :
		mov eax, dword ptr[esp + 8]
			findnameend :
			cmp byte ptr[eax], 0x0A
			je next
			inc eax
			jmp findnameend
			next :
		mov byte ptr[eax], 0
			add eax, 1
			mov dword ptr[esp + 8], eax
			sub eax, 2
			findnamestart :
			cmp byte ptr[eax], 0x0
			je next2
			dec eax
			jmp findnamestart
			next2 :
		add eax, 1
			add esp, 8
			push 12
			push eax
			lea eax, dword ptr ChatString
			push eax
			push ecx
			call FormatString
			add esp, 4
			push 0x00407138
			retn

			func4 :
		cmp dword ptr[esp + 8], 9
			jne func4exit2
			mov ecx, eax
			push esi
			mov esi, dword ptr[eax - 8]
			func4findsymbol :
			cmp byte ptr[ecx], 0x0A
			je func4achat
			inc ecx
			dec esi
			je func4exit1
			jmp func4findsymbol
			func4achat :
		mov byte ptr[ecx], 0x0D
			func4exit1 :
			pop esi
			MOV ECX, DWORD PTR[EDI + 0x21C0]//st
			retn
			func4exit2 :
		MOV ECX, DWORD PTR[EDI + 0x21C0]//st
			retn
	}
}





BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

