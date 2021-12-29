#pragma once

#include "Include.h"

class CTerrain
{
public:
	CTerrain();
	~CTerrain();

public:
	HRESULT		Initialize(void);
	void		Update(void);
	void		Render(void);
	void		Release(void);

	POS	TileChange(const D3DXVECTOR3& vPos, const int& iTileIdx);
	void TileIndexChange(POS pos, const int& iTileIdx);



private:
	int		GetTileIndex(const D3DXVECTOR3& vPos);
	// bool	Picking(const D3DXVECTOR3& vPos, const int& iIndex); // 직선의 방정식
	bool	Picking(const D3DXVECTOR3& vPos, const int& iIndex);


private:
	vector<TILE*>		m_vecTile;
};

