#pragma once

#include "GameObject.h"
#include "Camera.h"

class CPlayer : public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	// 플레이어의 위치 벡터, x축(Right), y축(Up), z축(Look) 벡터
	XMFLOAT3					m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3					m_xmf3Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMFLOAT3					m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMFLOAT3					m_xmf3Look = XMFLOAT3(0.0f, 0.0f, 1.0f);

	XMFLOAT3					m_xmf3CameraOffset = XMFLOAT3(0.0f, 0.0f, 0.0f);

	// 플레이어의 이동 속도를 나타내는 벡터
	XMFLOAT3					m_xmf3Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);

	// 플레이어에 작용하는 중력을 나타내는 벡터
	XMFLOAT3					m__xmf3Gravity;

	// 플레이어에 작용하는 마찰력을 나타내는 벡터
	float						m_fFriction = 125.0f;

	// 플레이어가 로컬 x축(Right), y축(Up), z축(Look)으로 얼마만큼 회전했는가를 나타냄
	float           			m_fPitch = 0.0f;
	float           			m_fYaw = 0.0f;
	float           			m_fRoll = 0.0f;

	// 플레이어에 현재 설정된 카메라
	CCamera*					m_pCamera = NULL;

	//플레이어의 위치가 바뀔 때마다 호출되는 OnPlayerUpdateCallback() 함수에서 사용하는 데이터이다. 
	LPVOID m_pPlayerUpdatedContext;

	//카메라의 위치가 바뀔 때마다 호출되는OnCameraUpdateCallback() 함수에서 사용하는 데이터이다. 
	LPVOID m_pCameraUpdatedContext;

	// 플레이 턴 true = player1,  false = player2
	bool playTurn = true;

public:
	void SetPosition(float x, float y, float z);
	/*

		플레이어의 위치를 xmf3Position 위치로 설정한다.
		xmf3Position 벡터에서 현재 플레이어의 위치 벡터를 빼면 현 재 플레이어의 위치에서 xmf3Position 방향으로의 벡터가 된다.
		현재 플레이어의 위치에서 이 벡터 만큼 이동한다.

	*/
	void SetPosition(XMFLOAT3& xmf3Position) { Move(XMFLOAT3(xmf3Position.x - m_xmf3Position.x, xmf3Position.y - m_xmf3Position.y, xmf3Position.z - m_xmf3Position.z), false); }

	void SetRotation(float x, float y, float z);

	void LookAt(XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up);

	// 플레이어를 이동하는 함수
	void Move(DWORD dwDirection, float fDistance);
	void Move(XMFLOAT3& xmf3Shift, bool bUpdateVelocity);
	void Move(float x, float y, float z);

	//플레이어를 회전하는 함수
	void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f);

	// 카메라 offset 설정하는 함수
	void SetCameraOffset(XMFLOAT3& xmf3CameraOffset);
	void SetCamera(CCamera* pCamera) { m_pCamera = pCamera; }
	CCamera* GetCamera() { return(m_pCamera); }

	void Update(float fTimeElapsed = 0.016f);

	// 이동 업데이트 함수
	virtual void OnUpdateTransform();

	virtual void Animate(float fElapsedTime);

	// 플레이어 메쉬 렌더링 함수
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);
	//플레이어의 위치가 바뀔 때마다 호출되는 함수와 그 함수에서 사용하는 정보를 설정하는 함수이다.

	/////////////////////////////////////////////////////////////////////////////////////
	virtual void OnPlayerUpdateCallback(float fTimeElapsed) { }
	void SetPlayerUpdatedContext(LPVOID pContext) { m_pPlayerUpdatedContext = pContext; }

	//카메라의 위치가 바뀔 때마다 호출되는 함수와 그 함수에서 사용하는 정보를 설정하는 함수이다. 
	virtual void OnCameraUpdateCallback(float fTimeElapsed) { }

	void SetCameraUpdatedContext(LPVOID pContext) { m_pCameraUpdatedContext = pContext; }

	//virtual void CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);

	//virtual void ReleaseShaderVariables();
	//virtual void UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList);

	////카메라를 변경하기 위하여 호출하는 함수이다. 
	CCamera* OnChangeCamera(DWORD nNewCameraMode, DWORD nCurrentCameraMode);
	virtual CCamera* ChangeCamera(DWORD nNewCameraMode, float fTimeElapsed) { return(NULL); }

	//플레이어의 위치와 회전축으로부터 월드 변환 행렬을 생성하는 함수이다.
	//virtual void OnPrepareRender();

	//플레이어의 카메라가 3인칭 카메라일 때 플레이어(메쉬)를 렌더링한다. 
	//virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera = NULL);



};

#define BULLETS					50

class CAirplanePlayer : public CPlayer
{
public:
	CAirplanePlayer();
	virtual ~CAirplanePlayer();

	float						m_fBulletEffectiveRange = 150.0f;
	CBulletObject*				m_ppBullets[BULLETS];

	void FireBullet(CGameObject* pLockedObject);

	virtual void OnUpdateTransform();
	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);
};

class CTankPlayer : public CPlayer
{
public:
	CTankPlayer();
	virtual ~CTankPlayer();

	CGameObject*				m_pTurret = NULL;
	CGameObject*				m_pGun = NULL;

	float						m_fBulletEffectiveRange = 150.0f;
	CBulletObject*				m_ppBullets[BULLETS];

	void RotateTurret(float fAngle) { m_pTurret->Rotate(0.0f, fAngle, 0.0f); }
	void RotateGun(float fAngle) { m_pGun->Rotate(fAngle, 0.0f, 0.0f); }

	void FireBullet(CGameObject* pLockedObject);

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);


};


class CTerrainPlayer : public CPlayer {

public:
	CTerrainPlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, void* pContext, int nMeshes = 1);
	virtual ~CTerrainPlayer();

	virtual CCamera* ChangeCamera(DWORD nNewCameraMode, float fTimeElapsed);
	virtual void OnPlayerUpdateCallback(float fTimeElapsed);
	virtual void OnCameraUpdateCallback(float fTimeElapsed);

};
