#include "stdafx.h"
#include "Terrain.h"
#include "Device.h"
#include "TextureMgr.h"

CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	Release();
}

HRESULT CTerrain::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(TEX_MULTI, L"../Texture/Stage/Board/%d.png", L"Terrain", L"Tile", 3)))
	{
		AfxMessageBox(L"Tile Texture Insert Failed");
		return E_FAIL;
	}

	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			TILE*		pTile = new TILE;

			float		fY = TILECY * i + TILECY;
			float		fX = TILECX * j + TILECX;

			pTile->vPos = D3DXVECTOR3(fX, fY, 0.f);
			pTile->vSize = D3DXVECTOR3((float)TILECX, (float)TILECY, 0.f);
			pTile->byOption = 0;
			pTile->byTileIdx = 0;

			m_vecTile.push_back(pTile);
		}
	}

	return S_OK;
}

void CTerrain::Update(void)
{

}

void CTerrain::Render(void)
{
	D3DXMATRIX	matWorld, matScale, matTrans;
	TCHAR		szBuf[64] = L"";
	int			iIndex = 0;

	for (auto& iter : m_vecTile)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans, iter->vPos.x, iter->vPos.y, iter->vPos.z);

		matWorld = matScale * matTrans;

		const	TEXINFO*		pTextureInfo = CTextureMgr::GetInstance()->Get_Texture(L"Terrain", L"Tile", iter->byTileIdx);
		if (nullptr == pTextureInfo)
			return;

		// 이미지의 중심 좌표
		float	fCenterX = pTextureInfo->tImgInfo.Width / 2.f;
		float	fCenterY = pTextureInfo->tImgInfo.Height / 2.f;

		CDevice::GetInstance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::GetInstance()->Get_Sprite()->Draw(pTextureInfo->pTexture,
			nullptr,	// 출력할 이미지 영역에 대한 렉트 구조체 주소값, null인 경우 이미지의 0,0을 기준으로 출력하게됨
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),	// 출력할 이미지의 중심 축 좌표를 vec3 타입의 주소값, null인 경우 0,0이 중심 좌표가 됨
			nullptr,	// 위치 좌표에 대한 vec3타입의 주소값, null인 경우 스크린 상의 0, 0 좌표 출력
			D3DCOLOR_ARGB(255, 255, 255, 255));

		swprintf_s(szBuf, L"%d", iIndex);

		CDevice::GetInstance()->Get_Font()->DrawTextW(CDevice::GetInstance()->Get_Sprite(),
														szBuf, 
														lstrlen(szBuf), 
														nullptr,
														0, 
														D3DCOLOR_ARGB(255, 0, 255, 0));


		++iIndex;
	}
}

void CTerrain::Release(void)
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<TILE*>);
	m_vecTile.clear();
}

int CTerrain::GetTileIndex(const D3DXVECTOR3 & vPos)
{
	for (size_t index = 0; index < m_vecTile.size(); ++index)
	{
		if (Picking(vPos, index))
		{
			return index;
		}
	}

	return -1;		// 0번 타일은 존재하기 때문에 만약 피킹 처리가 올바르지 않다면 음수를 반환한것 뿐
}

POS CTerrain::TileChange(const D3DXVECTOR3 & vPos, const int & iTileIdx)
{
	int		iIndex = GetTileIndex(vPos);

	if (-1 == iIndex || m_vecTile[iIndex]->byTileIdx != 0)
		return make_pair<int, int>(-1,-1);

	m_vecTile[iIndex]->byTileIdx = iTileIdx;
	m_vecTile[iIndex]->byOption  = 1;

	return make_pair<int, int>(iIndex / TILEY, iIndex % TILEX);
}

void CTerrain::TileIndexChange(POS pos, const int& iTileIdx)
{
	int iIndex = pos.first * TILEY + pos.second;

	m_vecTile[iIndex]->byTileIdx = iTileIdx;
	m_vecTile[iIndex]->byOption = 1;
}

/*
bool CTerrain::Picking(const D3DXVECTOR3 & vPos, const int & iIndex)
{

	float		fGradient[4] = { 

		((TILECY / 2.f) / (TILECX / 2.f)) * -1.f,
		((TILECY / 2.f) / (TILECX / 2.f)),
		((TILECY / 2.f) / (TILECX / 2.f)) * -1.f,
		((TILECY / 2.f) / (TILECX / 2.f)),
	};

	// 12시 방향을 기준으로 점들의 위치 값 저장
	D3DXVECTOR3		vPoint[4] = 
	{
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f),
	};

	// 직선의 방정식을 통해서 y절편인 b를 구하자
	// y = ax + b  
	// -b = ax - y
	// b = y - ax

	float	fB[4] = {

		vPoint[0].y - fGradient[0] * vPoint[0].x, 
		vPoint[1].y - fGradient[1] * vPoint[1].x,
		vPoint[2].y - fGradient[2] * vPoint[2].x,
		vPoint[3].y - fGradient[3] * vPoint[3].x
	};

	// 0 = ax + b - y : 직선 상에 놓여있다.
	// 0 > ax + b - y : 직선 아래에 놓여있다.(데카르트 기준)
	// 0 < ax + b - y : 직선 위에 놓여있다.(데카르트 기준)
	
	// vPos 들어오는 마우스는 윈도우 좌표 기준이다. 그래서 부호 반전이 필요하다.

	bool	bCheck[4] = { false };

	if (0 < fGradient[0] * vPos.x + fB[0] - vPos.y)
		bCheck[0] = true;

	if (0 > fGradient[1] * vPos.x + fB[1] - vPos.y)
		bCheck[1] = true;

	if (0 > fGradient[2] * vPos.x + fB[2] - vPos.y)
		bCheck[2] = true;

	if (0 < fGradient[3] * vPos.x + fB[3] - vPos.y)
		bCheck[3] = true;

	return bCheck[0] && bCheck[1] && bCheck[2] && bCheck[3];
}*/ // 직선의 방정식

// 내적을 이용한 픽킹
bool CTerrain::Picking(const D3DXVECTOR3 & vPos, const int & iIndex)
{

	// 12시 방향을 기준으로 점들의 위치 값 저장
	D3DXVECTOR3		vPoint[4] =
	{
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + (TILECY / 2.f), 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY / 2.f), 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - (TILECX / 2.f), m_vecTile[iIndex]->vPos.y, 0.f),
	};

	D3DXVECTOR3		vDir[4] = {

		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};

	// 각 방향 벡터의 법선 벡터를 만들어줘야 한다.
	// 법선벡터는 각 벡터와 직각을 이루는 방향 벡터로 크기는 반드시 1이어야 한다.

	D3DXVECTOR3	vNormal[4] = {

		D3DXVECTOR3(-vDir[0].y, vDir[0].x, 0.f),
		D3DXVECTOR3(-vDir[1].y, vDir[1].x, 0.f),
		D3DXVECTOR3(-vDir[2].y, vDir[2].x, 0.f),
		D3DXVECTOR3(-vDir[3].y, vDir[3].x, 0.f)	
	};
	
	// 타일의 네 점에서 마우스 위치를 향하는 방향 벡터를 구한다.

	D3DXVECTOR3	vMouseDir[4] = {

		vPos - vPoint[0], 
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3]
	};
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);
		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);
	}

	for (int i = 0; i < 4; ++i)
	{
		// 기울기가 양수인 경우(예각)
		if (0.f < D3DXVec3Dot(&vMouseDir[i], &vNormal[i]))
			return false;
	}

	return true;
}
