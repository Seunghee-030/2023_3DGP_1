#pragma once

#include "GameObject.h"
#include "Camera.h"

class CPlayer : public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	// �÷��̾��� ��ġ ����, x��(Right), y��(Up), z��(Look) ����
	XMFLOAT3					m_xmf3Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	XMFLOAT3					m_xmf3Right = XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMFLOAT3					m_xmf3Up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMFLOAT3					m_xmf3Look = XMFLOAT3(0.0f, 0.0f, 1.0f);

	XMFLOAT3					m_xmf3CameraOffset = XMFLOAT3(0.0f, 0.0f, 0.0f);

	// �÷��̾��� �̵� �ӵ��� ��Ÿ���� ����
	XMFLOAT3					m_xmf3Velocity = XMFLOAT3(0.0f, 0.0f, 0.0f);

	// �÷��̾ �ۿ��ϴ� �߷��� ��Ÿ���� ����
	XMFLOAT3					m__xmf3Gravity;

	// �÷��̾ �ۿ��ϴ� �������� ��Ÿ���� ����
	float						m_fFriction = 125.0f;

	// �÷��̾ ���� x��(Right), y��(Up), z��(Look)���� �󸶸�ŭ ȸ���ߴ°��� ��Ÿ��
	float           			m_fPitch = 0.0f;
	float           			m_fYaw = 0.0f;
	float           			m_fRoll = 0.0f;

	// �÷��̾ ���� ������ ī�޶�
	CCamera*					m_pCamera = NULL;

	//�÷��̾��� ��ġ�� �ٲ� ������ ȣ��Ǵ� OnPlayerUpdateCallback() �Լ����� ����ϴ� �������̴�. 
	LPVOID m_pPlayerUpdatedContext;

	//ī�޶��� ��ġ�� �ٲ� ������ ȣ��Ǵ�OnCameraUpdateCallback() �Լ����� ����ϴ� �������̴�. 
	LPVOID m_pCameraUpdatedContext;

	// �÷��� �� true = player1,  false = player2
	bool playTurn = true;

public:
	void SetPosition(float x, float y, float z);
	/*

		�÷��̾��� ��ġ�� xmf3Position ��ġ�� �����Ѵ�.
		xmf3Position ���Ϳ��� ���� �÷��̾��� ��ġ ���͸� ���� �� �� �÷��̾��� ��ġ���� xmf3Position ���������� ���Ͱ� �ȴ�.
		���� �÷��̾��� ��ġ���� �� ���� ��ŭ �̵��Ѵ�.

	*/
	void SetPosition(XMFLOAT3& xmf3Position) { Move(XMFLOAT3(xmf3Position.x - m_xmf3Position.x, xmf3Position.y - m_xmf3Position.y, xmf3Position.z - m_xmf3Position.z), false); }

	void SetRotation(float x, float y, float z);

	void LookAt(XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up);

	// �÷��̾ �̵��ϴ� �Լ�
	void Move(DWORD dwDirection, float fDistance);
	void Move(XMFLOAT3& xmf3Shift, bool bUpdateVelocity);
	void Move(float x, float y, float z);

	//�÷��̾ ȸ���ϴ� �Լ�
	void Rotate(float fPitch = 0.0f, float fYaw = 0.0f, float fRoll = 0.0f);

	// ī�޶� offset �����ϴ� �Լ�
	void SetCameraOffset(XMFLOAT3& xmf3CameraOffset);
	void SetCamera(CCamera* pCamera) { m_pCamera = pCamera; }
	CCamera* GetCamera() { return(m_pCamera); }

	void Update(float fTimeElapsed = 0.016f);

	// �̵� ������Ʈ �Լ�
	virtual void OnUpdateTransform();

	virtual void Animate(float fElapsedTime);

	// �÷��̾� �޽� ������ �Լ�
	virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera);
	//�÷��̾��� ��ġ�� �ٲ� ������ ȣ��Ǵ� �Լ��� �� �Լ����� ����ϴ� ������ �����ϴ� �Լ��̴�.

	/////////////////////////////////////////////////////////////////////////////////////
	virtual void OnPlayerUpdateCallback(float fTimeElapsed) { }
	void SetPlayerUpdatedContext(LPVOID pContext) { m_pPlayerUpdatedContext = pContext; }

	//ī�޶��� ��ġ�� �ٲ� ������ ȣ��Ǵ� �Լ��� �� �Լ����� ����ϴ� ������ �����ϴ� �Լ��̴�. 
	virtual void OnCameraUpdateCallback(float fTimeElapsed) { }

	void SetCameraUpdatedContext(LPVOID pContext) { m_pCameraUpdatedContext = pContext; }

	//virtual void CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);

	//virtual void ReleaseShaderVariables();
	//virtual void UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList);

	////ī�޶� �����ϱ� ���Ͽ� ȣ���ϴ� �Լ��̴�. 
	CCamera* OnChangeCamera(DWORD nNewCameraMode, DWORD nCurrentCameraMode);
	virtual CCamera* ChangeCamera(DWORD nNewCameraMode, float fTimeElapsed) { return(NULL); }

	//�÷��̾��� ��ġ�� ȸ�������κ��� ���� ��ȯ ����� �����ϴ� �Լ��̴�.
	//virtual void OnPrepareRender();

	//�÷��̾��� ī�޶� 3��Ī ī�޶��� �� �÷��̾�(�޽�)�� �������Ѵ�. 
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
