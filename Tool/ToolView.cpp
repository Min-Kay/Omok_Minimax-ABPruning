
// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "ToolDoc.h"
#include "ToolView.h"
#include "MainFrm.h"
#include "Omok.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "../Header/Define.h"

// CToolView

char board[BOARD_SIZE_Y][BOARD_SIZE_X];

Omok	omok;
TCHAR		aiScore[100] = L"";
TCHAR		playerScore[100] = L"";
TCHAR		nonABText[100] = L"";
TCHAR		aBText[100] = L"";
TCHAR		nonABTimerText[100] = L"";
TCHAR		aBTimerText[100] = L"";

RECT rect, rect1, rect2, rect3,rect4,rect5;
float nonABTimer = 0.f;
float ABTimer = 0.f;
int nonAB = 0;
int AB = 0;
bool firstTurn = true;
HWND	g_hWnd = nullptr;
IMPLEMENT_DYNCREATE(CToolView, CView)

BEGIN_MESSAGE_MAP(CToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView()
	
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CToolView::~CToolView()
{
	Safe_Delete(m_pTerrain);
	
	CTextureMgr::GetInstance()->DestroyInstance();
	CDevice::GetInstance()->DestroyInstance();
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CToolView 그리기

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

#pragma region 복습용
	//pDC->Rectangle(100, 100, 200, 200);

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	/*CDevice::GetInstance()->Get_Sprite()->Draw(m_pSingle->Get_Texture()->pTexture,
	nullptr,	// 출력할 이미지 영역에 대한 렉트 구조체 주소값, null인 경우 이미지의 0,0을 기준으로 출력하게됨
	nullptr,	// 출력할 이미지의 중심 축 좌표를 vec3 타입의 주소값, null인 경우 0,0이 중심 좌표가 됨
	nullptr,	// 위치 좌표에 대한 vec3타입의 주소값, null인 경우 스크린 상의 0, 0 좌표 출력
	D3DCOLOR_ARGB(255, 255, 255, 255));*/
	// 출력할 원본 이미지와 섞을 색상 값, 0xffffffff값을 넘겨주면 원본 색상을 유지하는 옵션	

	/*const	TEXINFO*		pTextureInfo = CTextureMgr::GetInstance()->Get_Texture(L"Terrain", L"Tile", 2);
	if (nullptr == pTextureInfo)
		return;

	// 이미지의 중심 좌표
	float	fCenterX = pTextureInfo->tImgInfo.Width / 2.f;
	float	fCenterY = pTextureInfo->tImgInfo.Height / 2.f;

	D3DXMATRIX	matWorld, matScale, matRot, matTrans;

	// dx 제공하는 모든 행렬함수 최초 작동시 output해당하는 행렬을 반드시 항등행렬로 초기화 작업을 실시한다.

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(45.f));
	D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);

	matWorld = matScale * matRot * matTrans;

	CDevice::GetInstance()->Get_Sprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->Get_Sprite()->Draw(pTextureInfo->pTexture,
		nullptr,	// 출력할 이미지 영역에 대한 렉트 구조체 주소값, null인 경우 이미지의 0,0을 기준으로 출력하게됨
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// 출력할 이미지의 중심 축 좌표를 vec3 타입의 주소값, null인 경우 0,0이 중심 좌표가 됨
		nullptr,	// 위치 좌표에 대한 vec3타입의 주소값, null인 경우 스크린 상의 0, 0 좌표 출력
		D3DCOLOR_ARGB(255, 255, 255, 255));*/
#pragma endregion 복습용
	
	CDevice::GetInstance()->Render_Begin();

	m_pTerrain->Render();

	swprintf_s(aiScore, L"AI : %d", omok.Check_Marker_Score(board, AI_MARKER));
	CDevice::GetInstance()->Get_Font()->DrawText(NULL, aiScore, lstrlen(aiScore), &rect, DT_CENTER | DT_TOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	swprintf_s(playerScore, L"PLAYER : %d", omok.Check_Marker_Score(board, PLAYER_MARKER));
	CDevice::GetInstance()->Get_Font()->DrawText(NULL, playerScore, lstrlen(playerScore), &rect1, DT_CENTER | DT_TOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	swprintf_s(nonABText, L"MINIMAX 탐색 수 : %d", nonAB);
	CDevice::GetInstance()->Get_Font()->DrawText(NULL, nonABText, lstrlen(nonABText), &rect2, DT_CENTER | DT_TOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	swprintf_s(aBText, L"AB 탐색 수: %d",AB);
	CDevice::GetInstance()->Get_Font()->DrawText(NULL, aBText, lstrlen(aBText), &rect3, DT_CENTER | DT_TOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	swprintf_s(nonABTimerText, L"MINIMAX 시간 : %.3f", nonABTimer);
	CDevice::GetInstance()->Get_Font()->DrawText(NULL, nonABTimerText, lstrlen(nonABTimerText), &rect4, DT_CENTER | DT_TOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	swprintf_s(aBTimerText, L"AB 시간 : %.3f", ABTimer);
	CDevice::GetInstance()->Get_Font()->DrawText(NULL, aBTimerText, lstrlen(aBTimerText), &rect5, DT_CENTER | DT_TOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	CDevice::GetInstance()->Render_End();

}


// CToolView 인쇄

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기



void CToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	g_hWnd = m_hWnd;

	if (FAILED(CDevice::GetInstance()->InitDevice()))
	{
		AfxMessageBox(L"Device Init Failed");
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_SINGLE, L"../Texture/Cube.png", L"CUBE")))
	{
		AfxMessageBox(L"Cube Texture Insert Failed");
		return;
	}

	m_pTerrain = new CTerrain;
	m_pTerrain->Initialize();

		// AfxGetMainWnd : 현재 메인 윈도우를 반환하는 전역 함수
		// 반환타입이 부모타입이어서 자식 타입으로 형변환 했음
	CMainFrame*	pMainFrm = (CMainFrame*)AfxGetMainWnd();

	RECT	rcWindow{};

	// GetWindowRect : 현재 윈도우의 rect 정보를 얻어오는 함수
	pMainFrm->GetWindowRect(&rcWindow);

	// SetRect : 지정한 인자값 대로 rect정보를 세팅하는 함수
	// 0,0 기준으로 윈도우 렉트 정보를 재조정
	SetRect(&rcWindow, 0, 0, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top);

	RECT		rcMainView{};

	// 현재 view 창의 rect 정보를 얻어오는 함수
	GetClientRect(&rcMainView);

	float	fRowFrm = float(rcWindow.right - rcMainView.right);
	float	fColFrm = float(rcWindow.bottom - rcMainView.bottom);

	// SetWindowPos : 윈도우 창의 위치 및 크기를 재조정하는 함수
	// 1인자 : 배치할 윈도우의 z순서에 대한 포인터
	// x좌표, y좌표, 가로 크기, 세로 크기
	// SWP_NOZORDER : 현재 z순서를 유지하겠다는 플래그 값
	pMainFrm->SetWindowPos(NULL, 0,0, int(WINCX + fRowFrm), int(WINCY + fColFrm), SWP_NOZORDER);
	
	omok.Initialize();

	for (int y = 0; y < BOARD_SIZE_Y; ++y)
	{
		for (int x = 0; x < BOARD_SIZE_X; ++x)
		{
			board[y][x] = NONE;
		}
	}

	SetRectEmpty(&rect);
	SetRectEmpty(&rect1);
	SetRectEmpty(&rect2);
	SetRectEmpty(&rect3);
	SetRectEmpty(&rect4);
	SetRectEmpty(&rect5);

	rect.left = 0;
	rect.right = 200;
	rect.top = 300;
	rect.bottom = 400;

	rect1.left = 0;
	rect1.right = 200;
	rect1.top = 400;
	rect1.bottom = 500;

	rect2.left = 300;
	rect2.right = 700;
	rect2.top = 300;
	rect2.bottom = 400;

	rect3.left = 300;
	rect3.right = 700;
	rect3.top = 400;
	rect3.bottom = 500;

	rect4.left = 300;
	rect4.right = 700;
	rect4.top = 350;
	rect4.bottom = 450;

	rect5.left = 300;
	rect5.right = 700;
	rect5.top = 450;
	rect5.bottom = 550;

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonDown(nFlags, point);

	STATE state = omok.Check_Game_State(board);
	if (state != DRAW || omok.Board_Full(board))
		return; 

	POS pick = m_pTerrain->TileChange(D3DXVECTOR3(point.x, point.y, 0.f), 1);

	VECPOS aval;
	aval = omok.availableSlot(board);
	if (omok.Check_AvaliablePick(aval, pick))
		board[pick.first][pick.second] = PLAYER_MARKER;
	else
		return;

	if (firstTurn)
	{
		if (pick.second + 1 < BOARD_SIZE_X)
		{
			board[pick.first][pick.second + 1] = AI_MARKER;
			m_pTerrain->TileIndexChange(POS(pick.first,pick.second + 1), 2);

		}
		else
		{
			board[pick.first][pick.second - 1] = AI_MARKER;
			m_pTerrain->TileIndexChange(POS(pick.first, pick.second - 1), 2);

		}
		firstTurn = false;
	}
	else
	{
		DWORD timer = GetTickCount();
		SCOREPOS aiMoveNon = omok.MinimaxNon(board, AI_MARKER, DEPTH);
		DWORD tick = GetTickCount();
		nonABTimer = (tick - timer) / 1000.f;
		nonAB = omok.Get_Count();
		omok.Set_Count();

		timer = GetTickCount();
		SCOREPOS aiMove = omok.Minimax(board, AI_MARKER, DEPTH, LOSE, WIN);
		tick = GetTickCount();
		ABTimer = (tick - timer) / 1000.f;
		AB = omok.Get_Count();
		omok.Set_Count();

		if (aiMove.second.first != DEFAULT && aiMove.second.second != DEFAULT)
		{
			m_pTerrain->TileIndexChange(aiMove.second, 2);
			board[aiMove.second.first][aiMove.second.second] = AI_MARKER;
		}

	}
	
	state = omok.Check_Game_State(board);
	if (state != DRAW || omok.Board_Full(board))
	{
		if (state == WIN)
			MessageBoxW(L"승리", L"Result", NULL);
		else if(state == LOSE)
			MessageBoxW(L"패배", L"Result", NULL);
		else 
			MessageBoxW(L"무승부", L"Result", NULL);

		for (int i = 0; i < 25; ++i)
		{
			firstTurn = true;
			board[i / 5][i % 5] = NONE;
			m_pTerrain->TileIndexChange(POS(i / 5, i % 5), 0);
		}
	}

	//Invalidate : 호출 시 윈도우 wm_paint와 wm_erasebkgnd 메세지를 발생시킴
	// ondraw 함수를 다시 한 번 호출
	// 인자값이 FALSE일때는 wm_paint만 메시지만 발생
	// 인자값이 true일때 wm_paint와 wm_erasebkgnd 두 메세지를 동시에 발생
	// wm_erasebkgnd 메세지 : 배경을 지우라는 메시지
	Invalidate(FALSE);

	
}


void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnMouseMove(nFlags, point);

	/*if (GetAsyncKeyState(VK_LBUTTON))
	{
		m_pTerrain->TileChange(D3DXVECTOR3(point.x, point.y, 0.f), 0);
		Invalidate(FALSE);
	}*/
}
