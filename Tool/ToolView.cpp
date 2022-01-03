
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView()
	
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CToolView::~CToolView()
{
	Safe_Delete(m_pTerrain);
	
	CTextureMgr::GetInstance()->DestroyInstance();
	CDevice::GetInstance()->DestroyInstance();
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CToolView �׸���

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

#pragma region ������
	//pDC->Rectangle(100, 100, 200, 200);

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	/*CDevice::GetInstance()->Get_Sprite()->Draw(m_pSingle->Get_Texture()->pTexture,
	nullptr,	// ����� �̹��� ������ ���� ��Ʈ ����ü �ּҰ�, null�� ��� �̹����� 0,0�� �������� ����ϰԵ�
	nullptr,	// ����� �̹����� �߽� �� ��ǥ�� vec3 Ÿ���� �ּҰ�, null�� ��� 0,0�� �߽� ��ǥ�� ��
	nullptr,	// ��ġ ��ǥ�� ���� vec3Ÿ���� �ּҰ�, null�� ��� ��ũ�� ���� 0, 0 ��ǥ ���
	D3DCOLOR_ARGB(255, 255, 255, 255));*/
	// ����� ���� �̹����� ���� ���� ��, 0xffffffff���� �Ѱ��ָ� ���� ������ �����ϴ� �ɼ�	

	/*const	TEXINFO*		pTextureInfo = CTextureMgr::GetInstance()->Get_Texture(L"Terrain", L"Tile", 2);
	if (nullptr == pTextureInfo)
		return;

	// �̹����� �߽� ��ǥ
	float	fCenterX = pTextureInfo->tImgInfo.Width / 2.f;
	float	fCenterY = pTextureInfo->tImgInfo.Height / 2.f;

	D3DXMATRIX	matWorld, matScale, matRot, matTrans;

	// dx �����ϴ� ��� ����Լ� ���� �۵��� output�ش��ϴ� ����� �ݵ�� �׵���ķ� �ʱ�ȭ �۾��� �ǽ��Ѵ�.

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(45.f));
	D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);

	matWorld = matScale * matRot * matTrans;

	CDevice::GetInstance()->Get_Sprite()->SetTransform(&matWorld);

	CDevice::GetInstance()->Get_Sprite()->Draw(pTextureInfo->pTexture,
		nullptr,	// ����� �̹��� ������ ���� ��Ʈ ����ü �ּҰ�, null�� ��� �̹����� 0,0�� �������� ����ϰԵ�
		&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// ����� �̹����� �߽� �� ��ǥ�� vec3 Ÿ���� �ּҰ�, null�� ��� 0,0�� �߽� ��ǥ�� ��
		nullptr,	// ��ġ ��ǥ�� ���� vec3Ÿ���� �ּҰ�, null�� ��� ��ũ�� ���� 0, 0 ��ǥ ���
		D3DCOLOR_ARGB(255, 255, 255, 255));*/
#pragma endregion ������
	
	CDevice::GetInstance()->Render_Begin();

	m_pTerrain->Render();

	swprintf_s(aiScore, L"AI : %d", omok.Check_Marker_Score(board, AI_MARKER));
	CDevice::GetInstance()->Get_Font()->DrawText(NULL, aiScore, lstrlen(aiScore), &rect, DT_CENTER | DT_TOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	swprintf_s(playerScore, L"PLAYER : %d", omok.Check_Marker_Score(board, PLAYER_MARKER));
	CDevice::GetInstance()->Get_Font()->DrawText(NULL, playerScore, lstrlen(playerScore), &rect1, DT_CENTER | DT_TOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	swprintf_s(nonABText, L"MINIMAX Ž�� �� : %d", nonAB);
	CDevice::GetInstance()->Get_Font()->DrawText(NULL, nonABText, lstrlen(nonABText), &rect2, DT_CENTER | DT_TOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	swprintf_s(aBText, L"AB Ž�� ��: %d",AB);
	CDevice::GetInstance()->Get_Font()->DrawText(NULL, aBText, lstrlen(aBText), &rect3, DT_CENTER | DT_TOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	swprintf_s(nonABTimerText, L"MINIMAX �ð� : %.3f", nonABTimer);
	CDevice::GetInstance()->Get_Font()->DrawText(NULL, nonABTimerText, lstrlen(nonABTimerText), &rect4, DT_CENTER | DT_TOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	swprintf_s(aBTimerText, L"AB �ð� : %.3f", ABTimer);
	CDevice::GetInstance()->Get_Font()->DrawText(NULL, aBTimerText, lstrlen(aBTimerText), &rect5, DT_CENTER | DT_TOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	CDevice::GetInstance()->Render_End();

}


// CToolView �μ�

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����



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

		// AfxGetMainWnd : ���� ���� �����츦 ��ȯ�ϴ� ���� �Լ�
		// ��ȯŸ���� �θ�Ÿ���̾ �ڽ� Ÿ������ ����ȯ ����
	CMainFrame*	pMainFrm = (CMainFrame*)AfxGetMainWnd();

	RECT	rcWindow{};

	// GetWindowRect : ���� �������� rect ������ ������ �Լ�
	pMainFrm->GetWindowRect(&rcWindow);

	// SetRect : ������ ���ڰ� ��� rect������ �����ϴ� �Լ�
	// 0,0 �������� ������ ��Ʈ ������ ������
	SetRect(&rcWindow, 0, 0, rcWindow.right - rcWindow.left, rcWindow.bottom - rcWindow.top);

	RECT		rcMainView{};

	// ���� view â�� rect ������ ������ �Լ�
	GetClientRect(&rcMainView);

	float	fRowFrm = float(rcWindow.right - rcMainView.right);
	float	fColFrm = float(rcWindow.bottom - rcMainView.bottom);

	// SetWindowPos : ������ â�� ��ġ �� ũ�⸦ �������ϴ� �Լ�
	// 1���� : ��ġ�� �������� z������ ���� ������
	// x��ǥ, y��ǥ, ���� ũ��, ���� ũ��
	// SWP_NOZORDER : ���� z������ �����ϰڴٴ� �÷��� ��
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

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}


void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
			MessageBoxW(L"�¸�", L"Result", NULL);
		else if(state == LOSE)
			MessageBoxW(L"�й�", L"Result", NULL);
		else 
			MessageBoxW(L"���º�", L"Result", NULL);

		for (int i = 0; i < 25; ++i)
		{
			firstTurn = true;
			board[i / 5][i % 5] = NONE;
			m_pTerrain->TileIndexChange(POS(i / 5, i % 5), 0);
		}
	}

	//Invalidate : ȣ�� �� ������ wm_paint�� wm_erasebkgnd �޼����� �߻���Ŵ
	// ondraw �Լ��� �ٽ� �� �� ȣ��
	// ���ڰ��� FALSE�϶��� wm_paint�� �޽����� �߻�
	// ���ڰ��� true�϶� wm_paint�� wm_erasebkgnd �� �޼����� ���ÿ� �߻�
	// wm_erasebkgnd �޼��� : ����� ������ �޽���
	Invalidate(FALSE);

	
}


void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnMouseMove(nFlags, point);

	/*if (GetAsyncKeyState(VK_LBUTTON))
	{
		m_pTerrain->TileChange(D3DXVECTOR3(point.x, point.y, 0.f), 0);
		Invalidate(FALSE);
	}*/
}
