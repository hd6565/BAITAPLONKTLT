#include "functions.h"
#include "main.h"
#include "Console.h"
	

CautruccuaBang CTB; 
CautrucO** CTO;

COORD CVitricontro; 

bool BSuDungPhim = false; 
//khai bao toa do x ; y 
short SToaDoX;
short SToaDoY;

bool BTrangThaiChoiGame = false; 
void taoMang2chieu()
{
	CTO =  new CautrucO * [CTB.SDONG];
	for (int i = 0; i < CTB.SDONG; ++i)
	{
		CTO[i] = new CautrucO[CTB.SCOT];
	}
}
void xoaMang2chieu()
{
	for (int i = 0; i < CTB.SDONG; ++i)
	{
		delete[]CTO[i];
	}
	delete[] CTO;
}

void luuToaDoBang()
{
	SToaDoX = ((ConsoleWidth / 2) - (CTB.SDONG ));
	SToaDoY = (((ConsoleHeight - 6) - CTB.SCOT) / 2) + 7;
}
void khoiTao(short SDONG, short SCOT, short SSOBOM)
{
	CTB.SDONG = SDONG;
	CTB.SCOT = SCOT;
	CTB.SSOBOM = SSOBOM;
	CTB.SSOODAMO = 0;
	CTB.SSOCO = 0;

	taoMang2chieu();
	taoBomrandom();
	luuToaDoBang();
	CVitricontro = { 0, 0 };
	BTrangThaiChoiGame = true; 
	taoBang(); 
	veTrangThaiChoiGame(1); 
	
}

short toaDox(short SX) 
{
	return ((SX * 2)+SToaDoX ) ;
}
short toaDoy(short SY)
{
	return (SY+ SToaDoY) ;

}

void taoO(short SX , short SY, short SKieu ) 
{
	switch (SKieu)
	{
	case 0:
		setColorBGTextXY(toaDox(SX), toaDoy(SY), 0, 10, "  ");
		break;
	case 1:
		setColorBGTextXY(toaDox(SX), toaDoy(SY), 9, 15, "1 ");
		break;
	case 2:
		setColorBGTextXY(toaDox(SX), toaDoy(SY), 2, 15, "2 ");
		break;
	case 3:
		setColorBGTextXY(toaDox(SX), toaDoy(SY), 12, 15, "3 ");
		break;
	case 4:
		setColorBGTextXY(toaDox(SX), toaDoy(SY), 1, 15, "4 ");
		break;
	case 5:
		setColorBGTextXY(toaDox(SX), toaDoy(SY), 4, 15, "5 ");
		break;
	case 6:
		setColorBGTextXY(toaDox(SX), toaDoy(SY), 3, 15, "6 ");
		break;
	case 7:
		setColorBGTextXY(toaDox(SX), toaDoy(SY), 0, 15, "7 ");
		break;
	case 8:
		setColorBGTextXY(toaDox(SX), toaDoy(SY), 13, 15, "8 ");
		break;
	case 9://boom , nen red , chu black
		setColorBGTextXY(toaDox(SX), toaDoy(SY), 0, 12, "B ");
		break;
	case 10://o chan 
		setColorBGTextXY(toaDox(SX), toaDoy(SY), 0, 8, "  ");
		break;
	case 11://o le 
		setColorBGTextXY(toaDox(SX), toaDoy(SY), 0, 7, "  ");
		break;
	case 12://theo doi con tro
		setColorBGTextXY(toaDox(SX) +1 ,toaDoy(SY), 0, 13, " ");
		break;
	case 13:// cam flag , chu red 
		setColorBGTextXY(toaDox(SX), toaDoy(SY), 12, 14, "F ");
		break;
	case 14://cam co sai , nen mau cam 
		setColorBGTextXY(toaDox(SX), toaDoy(SY), 15, 6, "FF ");
		break;
	case 15://cam co dung, chu red 
		setColorBGTextXY(toaDox(SX), toaDoy(SY), 12, 14, "B ");
		break;
	}


	}
	

void taoBang()
{
	for (int i = 0; i < CTB.SDONG; ++i)
	{
		for (int j = 0; j < CTB.SCOT ; ++j) 

		{
			if (CTO[i][j].BCAMCO)
				taoO(j, i, 13);
			else if (CTO[i][j].SSOBOMLANCAN)
			{
				taoO(j, i, CTO[i][j].SSOBOMLANCAN); 
			}
			else if ( CTO[i][j].BDAMO)
			{
				taoO(j, i, 0);


			}
			else if (((i % 2) && (j % 2)) || !((i % 2) || j % 2))
			{
				taoO(j, i, 10);
			}
			else 
			{
				taoO(j, i, 11);
			}
			if (BSuDungPhim)
				taoO(CVitricontro.X, CVitricontro.Y, 12); 
			
		}
	}
}
void taoBomrandom()
{
	short SSoBom = CTB.SSOBOM; 
		short SI, SJ; 
		srand(time(NULL));
		while (SSoBom)
		{
			SI = rand() % CTB.SDONG;
			SJ = rand() % CTB.SCOT;
			if (CTO[SI][SJ].BCOBOM)
				continue;

			CTO[SI][SJ].BCOBOM = true;
			--SSoBom; 
		}
}

void clickPhai(short SX, short SY) // cam co 
{
	if (!CTO[SX][SY].BDAMO)
	{
		if (CTO[SX][SY].BCAMCO)
		{
			CTO[SX][SY].BCAMCO = false;
			CTB.SSOCO--;
		}
		else
		{
			CTO[SX][SY].BCAMCO = true;
			CTB.SSOCO++;
		}
	}
	taoBang(); 
}
short demBomLanCan(short SX, short SY)
{
	short SDem = 0; 
	for (int i = SX - 1; i <= SX + 1; ++i)
	{
		for (int j = SY - 1; j <= SY+1; ++j)
		{
			if (i < 0 || i >= CTB.SDONG || j < 0 || j >= CTB.SCOT || (i == SX && j == SY))
				continue; 

			//xet o co bom hay khong , co thi dem +1 
			if (CTO[i][j].BCOBOM)
				++SDem; 

		}
	}
	return SDem; 
}
void moO(short SX, short SY)
{
	if (!CTO[SX][SY].BDAMO && !CTO[SX][SY].BCAMCO)
	{
		CTO[SX][SY].BDAMO = true;
		if (CTO[SX][SY].BCOBOM) // co boom
			lose(); // Thua nen thoat game 
		else
		{
			CTB.SSOODAMO++;				
			short SSoBomLanCan = demBomLanCan(SX, SY); 
			if (SSoBomLanCan)
				CTO[SX][SY].SSOBOMLANCAN = SSoBomLanCan; 
			else
			{
				for (int i = SX - 1; i <= SX + 1; ++i)
				{
					for (int j = SY - 1; j <= SY+1; ++j)
					{
						if (i < 0 || i >= CTB.SDONG || j < 0 || j >= CTB.SCOT || (i == SX && j == SY))
							continue;


						moO(i, j); 
						
					}
				}
			
			}
		}
	}
}

bool thongKeFlag()
{
	if ((CTB.SSOODAMO + CTB.SSOBOM) == (CTB.SDONG * CTB.SCOT))
		return true; 
	return false; 
}
void clickTrai(short SX, short SY)
{
	if (!CTO[SX][SY].BDAMO && !CTO[SX][SY].BCAMCO)
	{
		moO(SX, SY);
		if (BTrangThaiChoiGame)
		{
			taoBang();
			if (thongKeFlag())
				win();
		}
	
	}
}

void win()
{
	BTrangThaiChoiGame = false; 
	xoaMang2chieu();
	deleteRow(4, 1);
	veTrangThaiChoiGame(2); //win game 
}
void lose()
{
	for (int i = 0; i < CTB.SDONG; ++i)
	{
		for (int j = 0; j < CTB.SCOT; ++j)
		{
			if (CTO[i][j].BCAMCO)
			{
				if (CTO[i][j].BCAMCO)
					taoO(j, i, 15);//cam co dung
				else

					taoO(j, i, 14);//cam co sai
			}
			else//o do khong co cam co
			{
				if (CTO[i][j].BCOBOM)
					taoO(j, i, 9);//hien bom 
			}
		}
	}
	BTrangThaiChoiGame = false; 
	xoaMang2chieu(); //giai phong con tro 
	deleteRow(4, 1);
	veTrangThaiChoiGame(3);//cap nhap lose game 

}

void xuLyphim(KEY_EVENT_RECORD key)
{
	if (key.bKeyDown)
	{
		switch (key.wVirtualKeyCode)
		{
		case VK_UP:
			//	std::cout << "mui ten len " << std::endl;
			switch (STrang)
			{
			case 1:
				if (SMuc == 4)
				{
					if (SVTriChon == 0)
						SVTriChon = SMuc - 1;
					else
						SVTriChon -= 1;
					veMenu(SVTriChon);
				}
				break;
			case 2: // menu chon level
				if (SMuc == 4)
				{
					if (SVTriChon == 0)
						SVTriChon = SMuc - 1;
					else
						SVTriChon -= 1;
					veLevelGame(SVTriChon);
				}
				break;
			case 3:
				if (BTrangThaiChoiGame)
				{
					BSuDungPhim = true;
					CVitricontro.Y = ((CVitricontro.Y == 0) ? CTB.SDONG - 1 : CVitricontro.Y - 1);
					taoBang();
				}// trang thai choi game
				break;
			case 4: // trang lose
				break;
			case 5: // trang win 
				break;
			}
			break;
			/*if (BTrangThaiChoiGame)
			{
				BSuDungPhim = true;
				CVitricontro.Y = ((CVitricontro.Y == 0) ? CTB.SDONG - 1 : CVitricontro.Y - 1);
				taoBang();
			}*/
		
		case VK_DOWN:
			switch (STrang)
			{
			case 1:
				if (SMuc == 4)
				{
					if (SVTriChon == SMuc - 1)
						SVTriChon = 0;
					else
						SVTriChon += 1;
					veMenu(SVTriChon);
				}
				break;
			case 2: // menu chon level
				if (SMuc == 4)
				{
					if (SVTriChon == SMuc - 1)
						SVTriChon = 0;
					else
						SVTriChon += 1;
					veLevelGame(SVTriChon);
				}
				break;
			case 3:
				if (BTrangThaiChoiGame)
				{
					BSuDungPhim = true;
					CVitricontro.Y = ((CVitricontro.Y == CTB.SDONG - 1) ? 0 : CVitricontro.Y + 1);
					taoBang();
				}// trang thai choi game
				break;
			case 4: // trang lose
				break;
			case 5: // trang win 
				break;
			}
			break;
		
					//	std::cout << "mui ten xuong" << std::endl;
						/*if (BTrangThaiChoiGame)
						{
							BSuDungPhim = true;
							CVitricontro.Y = ((CVitricontro.Y == CTB.SDONG - 1) ? 0 : CVitricontro.Y + 1);
							taoBang();
						}
						break;*/
				case VK_RIGHT:
					//	std::cout << "mui ten phai " << std::endl; 
					if (BTrangThaiChoiGame)
					{
						BSuDungPhim = true;
						CVitricontro.X = ((CVitricontro.X == CTB.SCOT - 1) ? 0 : CVitricontro.X + 1);
						taoBang();
					}

					break;
				case VK_LEFT:
					//		std::cout << "mui ten trai" << std::endl;
					if (BTrangThaiChoiGame)
					{
						BSuDungPhim = true;
						CVitricontro.X = ((CVitricontro.X == 0) ? CTB.SCOT - 1 : CVitricontro.X - 1);
						taoBang();
					}
					break;
				case VK_RETURN:// ENTER
					//std::cout << "enter" << std::endl; 
					switch (STrang)
					{
					case 1:
						if (SVTriChon == 1)
						{
							STrang = 2;
							deleteRow(4, 5);
							veLevelGame(0);
						}
						else if (SVTriChon == 1) {

						}
						else if (SVTriChon == 2) {

						}
						else
						{
							exit(0);
						}
						break;
					case 2:
						if (SVTriChon == 0)// level de 
						{
							STrang = 3;
							deleteRow(4, 10);
							khoiTao(9, 9, 10);

						}
						else if (SVTriChon == 1)//level trung binh
						{
							STrang = 3;
							deleteRow(4, 10);
							khoiTao(16, 16, 40);

						}
						else if (SVTriChon == 2) // level kho
						{
							STrang = 3;
							deleteRow(4, 10);
							khoiTao(24, 24, 99);

						}
						else
						{
							STrang = 1;
							deleteRow(4, 10);
							veLevelGame(0);
						}
					}
					break; 
				
					
				case VK_ESCAPE: //THOAT
					std::cout << "ESC" << std::endl; //THOAT
					break;
				case ClickPhai:
					//	std::cout << "X" << std::endl; //CAM CO
					clickPhai(CVitricontro.Y, CVitricontro.X);
					break;
				case ClickTrai:
					//std::cout << "Z" << std::endl;//mo O
					clickTrai(CVitricontro.Y, CVitricontro.X);
					break;
			
				}
			}
		}
	



			void xuLysukien()
			{
				while (1)
				{
					DWORD DWNumberOfEvents = 0;
					DWORD DWNumberOfEventsRead = 0;

					HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
					GetNumberOfConsoleInputEvents(HConsoleInput, &DWNumberOfEvents);

					if (DWNumberOfEvents)
					{
						INPUT_RECORD* IREventBuffer = new INPUT_RECORD[DWNumberOfEvents];
						ReadConsoleInput(HConsoleInput, IREventBuffer, DWNumberOfEvents, &DWNumberOfEventsRead);

						for (DWORD i = 0; i < DWNumberOfEvents; ++i)
						{
							if (IREventBuffer[i].EventType == KEY_EVENT)
							{
								xuLyphim(IREventBuffer[i].Event.KeyEvent);
							}
						}
					}
				}
			}

void veTieuDeGame()
{
	short i;
	for (i = 0; i < ConsoleWidth; ++i)
	{
		printf("%c", 45);
	}

	setColorBGTextXY((ConsoleWidth / 2) -5,1, 5, 0, "GAME DO MIN-NHOM 1\n");
	setColor(7);
	for (i = 0; i < ConsoleWidth; ++i)
	{
		printf("%c", 45);
	}
}
void veTrangThaiChoiGame(short STrangThai)
{
	setColorBGTextXY(1, 3, 15, 0, "BAN DO : %d * %d", CTB.SDONG, CTB.SCOT); 
	setColorBGTextXY(1, 4, 15, 0, "SO BOM  : %d", CTB.SSOBOM);
	if (STrangThai == 1)// dang play
		setColorBGTextXY(ConsoleWidth - 22, 4, 15, 0, "TRANG THAI: %s" ,"PLAYING");
	if (STrangThai == 2)//win
		setColorBGTextXY(ConsoleWidth - 22, 4, 15, 0, "TRANG THAI: %s", "WIN");
	if (STrangThai == 3)//lose
		setColorBGTextXY(ConsoleWidth - 22, 4, 15, 0, "TRANG THAI: %s", "LOSE");

	std::cout << std::endl; 
	setColor(7); short i;
	for (i = 0; i < ConsoleWidth; ++i)
	{
		printf("%c", 45);
	}
	
}
void veMenu(short SIndex)
{
	SVTriChon = SIndex;
	SMuc = 4;
	// VE MENU


	LPCSTR STRMENU = " NEW GAME ";

	/*setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRMENU) / 2), 7, 15, ((SIndex == 0) ? 2 : 0), STRMENU);
	STRMENU = " BANG DIEM ";*/
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRMENU) / 2), 7, 15, ((SIndex == 1) ? 2 : 0), STRMENU);

	STRMENU = " THONG TIN ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRMENU) / 2), 8, 15, ((SIndex == 2) ? 2 : 0), STRMENU);

	STRMENU = " THOAT TRO CHOI ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRMENU) / 2), 9, 15, ((SIndex == 3) ? 2 : 0), STRMENU);
}
void veLevelGame(short SIndex)
{
	SVTriChon = SIndex;
	SMuc = 4;

	LPCSTR STRMENU = " CHON CAP DO TRO CHOI ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRMENU) / 2), 4, 15, 1, STRMENU);

	STRMENU = " DE ( 9X9) ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRMENU) / 2), 8, 15, ((SIndex == 0) ? 2 : 0), STRMENU);

	STRMENU = " TRUNG BINH (16X16) ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRMENU) / 2), 9, 15, ((SIndex == 1) ? 2 : 0), STRMENU);

	STRMENU = " KHO ( 24X24) ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRMENU) / 2), 10, 15, ((SIndex == 2) ? 2 : 0), STRMENU);

	STRMENU = " THOAT TRO CHOI ";
	setColorBGTextXY((ConsoleWidth / 2) - (strlen(STRMENU) / 2), 11, 15, ((SIndex == 3) ? 2 : 0), STRMENU);
}