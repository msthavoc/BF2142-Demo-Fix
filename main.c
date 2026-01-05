#include <windows.h>
#include <tlhelp32.h>
#include "resource.h"

#pragma comment(linker,"/FILEALIGN:512 /MERGE:.rdata=.text /MERGE:.data=.text /SECTION:.text,EWR /IGNORE:4078")
BOOL GameRunning;

/** Start of Declarations here **/
BOOL GetProcessList( );

// Below is the about text that is shown when "About" button is clicked

/////////////////////////////////////////////////////////////////////

char *gameWindow = "BF2142.exe"; // exe name here
DWORD pid; HWND hwndWindow; DWORD bytes; HANDLE hand = NULL;


HANDLE pFile; //Used for logging address to file (not implimented in this build)

//below you will list the BOOLs for function toggles
BOOL IsHack1On, FirstTime1;

///////////////////////////////////////////////////////
////Global Variables
				
	int dem_fix=144;
	

///////////////////////////////////////////////////////

	/** End of Declarations here **/


void Initialize(HWND hwnd,WPARAM wParam, LPARAM lParam) {
	GetProcessList();

	FirstTime1=TRUE; //This is the true / false flag for "is this the first time the trainers read the game code

	IsHack1On=FALSE; // used in our example hack function below


	if(GameRunning==TRUE)
	{		 
         GetWindowThreadProcessId(hwndWindow, &pid);
		 hand = OpenProcess(PROCESS_ALL_ACCESS,0,pid);
		 SetTimer(hwnd, 1, 10, NULL);	//Timer speed is 10ms, you can change it here
	} 
	else 
	{ //Error message for when game not found in process list
		MessageBox(NULL, "BF2142 not detected, please run the game before running the trainer", "Error", MB_OK + MB_ICONWARNING);
	}
}

void HookExe() //This function ensures we are attatched to the game at all times
{
	
	CloseHandle(hand);
    GetProcessList( );
    GetWindowThreadProcessId(hwndWindow, &pid);
	hand = OpenProcess(PROCESS_ALL_ACCESS,0,pid);

}

	/*----- Here comes the good stuff -----*/


void timerCall() //functions in here run according to timer above
{
		HookExe(); //Call to function above (game always attatched)


/////////////////////////////////////////////////////////////////////////
/////ReadProcMem arrays are used to read and store original code so we 
/////toggle the code on and off


	if(FirstTime1==TRUE) //checks to see if this is the first time its run, if it is continue
	{
				WriteProcessMemory(hand, (void*)0x48CCF8, &dem_fix,1, &bytes);
		WriteProcessMemory(hand, (void*)0x48CCF9, &dem_fix,1, &bytes);
		WriteProcessMemory(hand, (void*)0x48CCFA, &dem_fix,1, &bytes);
		WriteProcessMemory(hand, (void*)0x48CCFB, &dem_fix,1, &bytes);
		WriteProcessMemory(hand, (void*)0x48CCFC, &dem_fix,1, &bytes);
		WriteProcessMemory(hand, (void*)0x48CCFD, &dem_fix,1, &bytes);
		WriteProcessMemory(hand, (void*)0x48CCFE, &dem_fix,1, &bytes);
		
		WriteProcessMemory(hand, (void*)0x4B78A2, &dem_fix,1, &bytes);																		
		WriteProcessMemory(hand, (void*)0x4B78A3, &dem_fix,1, &bytes);	
		WriteProcessMemory(hand, (void*)0x4B78A4, &dem_fix,1, &bytes);	
		WriteProcessMemory(hand, (void*)0x4B78A5, &dem_fix,1, &bytes);	
		WriteProcessMemory(hand, (void*)0x4B78A6, &dem_fix,1, &bytes);	
		WriteProcessMemory(hand, (void*)0x4B78A7, &dem_fix,1, &bytes);	
		WriteProcessMemory(hand, (void*)0x4B78A8, &dem_fix,1, &bytes);	
		
		FirstTime1=FALSE;
	}
	// What we are doing here is reading 2 bytes of the games code and storing them in a variable called "original_code"
	//	The number in sqaure brackets is the number of bytes, this has to match the number after our variable
	// "original_code" in the ReadProcessMemory line.

	// You can add more addresses in, just be sure to have unique varible names and specify the right number of bytes.


///////////////////////////////////////////////////////////////////////////
/////Start Hotkey Functions Below

		/* --Example Function----------------------------------------- */

	if(GetAsyncKeyState(VK_NUMPAD1)) // User Pressed the NumPad1 to switch on code
	{			
				
		WriteProcessMemory(hand, (void*)0x48CCF8, &dem_fix,1, &bytes);
		WriteProcessMemory(hand, (void*)0x48CCF9, &dem_fix,1, &bytes);
		WriteProcessMemory(hand, (void*)0x48CCFA, &dem_fix,1, &bytes);
		WriteProcessMemory(hand, (void*)0x48CCFB, &dem_fix,1, &bytes);
		WriteProcessMemory(hand, (void*)0x48CCFC, &dem_fix,1, &bytes);
		WriteProcessMemory(hand, (void*)0x48CCFD, &dem_fix,1, &bytes);
		WriteProcessMemory(hand, (void*)0x48CCFE, &dem_fix,1, &bytes);
		
		WriteProcessMemory(hand, (void*)0x4B78A2, &dem_fix,1, &bytes);																		
		WriteProcessMemory(hand, (void*)0x4B78A3, &dem_fix,1, &bytes);	
		WriteProcessMemory(hand, (void*)0x4B78A4, &dem_fix,1, &bytes);	
		WriteProcessMemory(hand, (void*)0x4B78A5, &dem_fix,1, &bytes);	
		WriteProcessMemory(hand, (void*)0x4B78A6, &dem_fix,1, &bytes);	
		WriteProcessMemory(hand, (void*)0x4B78A7, &dem_fix,1, &bytes);	
		WriteProcessMemory(hand, (void*)0x4B78A8, &dem_fix,1, &bytes);	
																
	}
	
				

}


BOOL GetProcessList( )
{
  HANDLE hProcessSnap;
  HANDLE hProcess;
  PROCESSENTRY32 pe32;
  DWORD dwPriorityClass;
  int PidTest;
  GameRunning=FALSE;
 
  
  // Take a snapshot of all processes in the system.
  hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
  if( hProcessSnap == INVALID_HANDLE_VALUE ) return( FALSE );
  

  // Set the size of the structure before using it.
  pe32.dwSize = sizeof( PROCESSENTRY32 );

  // Retrieve information about the first process,
  // and exit if unsuccessful
  if( !Process32First( hProcessSnap, &pe32 ) )
  {
    CloseHandle( hProcessSnap );     // Must clean up the snapshot object!
    return( FALSE );
  }

  // Now walk the snapshot of processes, and
  // display information about each process in turn
  
  do
  {
    // Retrieve the priority class.
    dwPriorityClass = 0;
    hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID );
    if( hProcess != NULL )
    {
      dwPriorityClass = GetPriorityClass( hProcess );
      if( !dwPriorityClass )
        
      CloseHandle( hProcess );
    }

    PidTest=strcmp(gameWindow, pe32.szExeFile);
	if(PidTest==0){ pid=pe32.th32ProcessID; GameRunning=TRUE;}

  } while( Process32Next( hProcessSnap, &pe32 ) );

  // Don't forget to clean up the snapshot object!
  CloseHandle( hProcessSnap );
  return( TRUE );
}

BOOL CALLBACK DialogProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
	{
		case WM_INITDIALOG:
			Initialize(hwnd,wParam,lParam);
			return TRUE;

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDC_EXIT:
					EndDialog (hwnd, 0);
					return TRUE;
			}
		return TRUE;

		case WM_DESTROY:
			CloseHandle(pFile);
			PostQuitMessage(0);
			return TRUE;

		case WM_CLOSE:
			PostQuitMessage(0);
			return TRUE;
		case WM_TIMER:
			timerCall();
			return TRUE;
    }
    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{


	DialogBox(hInstance,MAKEINTRESOURCE(IDD_MAINDLG), NULL,DialogProc);
	return 0;
}


