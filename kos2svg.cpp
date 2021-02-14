// stp2svglinux.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "string"
#include <algorithm>
#include "LinuxCStringA.h"
#include "kos_loader.h"
#include "WindowsToLinuxDefine.h"

void make_lower(std::string& str)
{
	for (int i = 0; i < str.length(); ++i)
	{
		str[i] = tolower(str[i]);
	}
}


int main(int argc, char* argv[])
{

	if (argc < 4)
	{

		printf("arguments : [filename] [pathonly] [filenameonly]\n");
		printf("example : /home/hileejaeho/stp/test.stp /home/hileejaeho/stp test\n");

		//	kos_loader kl;
	//#ifdef _MSC_VER
		//	kl.Run("d:\\1.stp", "d:", "1");
	//#else
			//kl.Run("/home/hileejaeho/stp/1.stp", "/home/hileejaeho/stp", "1-1");
	//#endif
	}
	else
	{
		// kos파일이면 압축을 푼다
		CString filename = argv[1];
		std::string ext = filename.GetBuffer().substr(filename.GetBuffer().length() - 3, 3);
		make_lower(ext);

		if (ext == "kos")
		{
			// 로그 파일 삭제
			remove("extract.log");

			// 압축을 모두 푼다.
			printf("extract %s to %s\n", filename.GetBuffer().c_str(), argv[2]);
			CString cmd = "";
			cmd.Format("./cabextract -e EUC-KR \"%s\" >> extract.log", filename.GetBuffer().c_str());
			system(cmd);

			// 로그파일에서 stp 파일이름을 찾는다.
			ifstream logfile;
			std::string logline;
			logfile.open("extract.log");
			if (logfile.is_open())
			{
				getline(logfile, logline);
				// 두번째 줄이 stp 파일명이다.
				getline(logfile, logline);
				int len = logline.length();
				logline = logline.substr(13, len - 13);
			}
			else
			{
				cout << "[NG] not found extract.log file" << endl;
				logfile.close();
				return 0;
			}
			logfile.close();

			// 압축해제된 파일중에서 stp 파일을 찾자
			filename.Format("./%s", logline.c_str());


			// stp 파일이 있는지 검사
			std::cout << "open stp file : " << filename << endl;
			ifstream ifile;
			ifile.open(filename);
			if (!ifile)
			{
				printf("[NG] stp not opened");
				return -1;
			}
			else
			{
				ifile.close();
				std::cout << "stp file opened(stp closed now) : " << filename << endl;
			}
		}

		std::cout << "kl.Run(filename, argv[2], argv[3]);" << endl;
		kos_loader kl;
		kl.Run(filename, argv[2], argv[3]);
	}
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁:
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
