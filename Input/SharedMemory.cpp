
#include <iostream>
#include <windows.h>

using namespace std;

#define BUF_SIZE 1024

TCHAR cstrSzName[] = L"NameOfMappingObject"; // 共享内存名

int main()
{
    // 1.创建共享文件句柄 CreateFileMapping（）函数创建一个文件映射内核对象
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE, // 物理文件句柄，
        NULL,                 // 默认安全级别
        PAGE_READWRITE,       // 权限可读可写
        0,                    // 高位文件大小
        BUF_SIZE,             // 低位文件大小
        cstrSzName            // 共享内存名
    );

    // 2.获取指向文件视图的指针 pBuf, MapViewOfFile()函数负责把文件数据映射到进程的地址空间
    char* pBuf = (char*)MapViewOfFile(
        hMapFile,             // 共享内存的句柄
        FILE_MAP_ALL_ACCESS,  // 可读写
        0,
        0,
        BUF_SIZE
    );

    // 3.将数据放到内存共享
    while (true)
    {
        cout << "input...." << endl;
        char szInfo[BUF_SIZE] = { 0 };
        gets_s(szInfo, BUF_SIZE);  // C++ 11
        // 将 szInfo 拷贝到 pBuf 中
        memcpy(pBuf, szInfo, BUF_SIZE - 1);
        pBuf[BUF_SIZE - 1] = '\0';
        
        // 程序B显示共享内存中的数据


    }

    // 4.撤销文件视图UnMapViewOffFile()
    UnmapViewOfFile(pBuf);
    
    // 5. 关闭映射文件句柄CloseHandle()
    CloseHandle(hMapFile);

    return 0;


}
