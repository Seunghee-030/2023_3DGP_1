#include "stdafx.h"
#include "Player.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	if (m_pCamera) delete m_pCamera;
}

void CPlayer::SetPosition(float x, float y, float z)
{
	m_xmf3Position = XMFLOAT3(x, y, z);

	CGameObject::SetPosition(x, y, z);
}

void CPlayer::SetCameraOffset(XMFLOAT3& xmf3CameraOffset)
{
	m_xmf3CameraOffset = xmf3CameraOffset;
	m_pCamera->SetLookAt(Vector3::Add(m_xmf3Position, m_xmf3CameraOffset), m_xmf3Position, m_xmf3Up);
	m_pCamera->GenerateViewMatrix();
}

// 벡터의 덧셈으로 플레이어 위치 정보 바꾸는 함수
// 사용자가 키보드를 누를 때 변경
void CPlayer::Move(DWORD dwDirection, float fDistance)
{
	if (dwDirection)
	{
		XMFLOAT3 xmf3Shift = XMFLOAT3(0, 0, 0);
		if (dwDirection & DIR_FORWARD) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Look, fDistance);
		if (dwDirection & DIR_BACKWARD) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Look, -fDistance);
		if (dwDirection & DIR_RIGHT) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Right, fDistance);
		if (dwDirection & DIR_LEFT) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Right, -fDistance);
		if (dwDirection & DIR_UP) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Up, fDistance);
		if (dwDirection & DIR_DOWN) xmf3Shift = Vector3::Add(xmf3Shift, m_xmf3Up, -fDistance);

		// 플레이어를 현재 위치 벡터에서 xmf3Shift 벡터만큼 이동
		Move(xmf3Shift, true);
	}
}

// 받은 위치 정보로 velocity와 계산 후 이동하는 move함수
void CPlayer::Move(XMFLOAT3& xmf3Shift, bool bUpdateVelocity)
{
	// bUpdateVelocity가 참이면 플레이어를 이동하지 않고 속도 벡터를 변경
	if (bUpdateVelocity)
	{
		// 속도 벡터를 xmf3Shift 벡터만큼 변경
		m_xmf3Velocity = Vector3::Add(m_xmf3Velocity, xmf3Shift);
	}
	else
	{
		// 플레이어를 현재 위치 벡터에서 xmf3Shift 벡터만큼 이동
		m_xmf3Position = Vector3::Add(xmf3Shift, m_xmf3Position);

		//플레이어의 위치가 변경되었으므로 카메라의 위치도xmf3Shift 벡터만큼 이동
		m_pCamera->Move(xmf3Shift);
	}
}

void CPlayer::Move(float x, float y, float z)
{
	Move(XMFLOAT3(x, y, z), false);
}

void CPlayer::Rotate(float fPitch, float fYaw, float fRoll)
{
	DWORD nCameraMode = m_pCamera->GetMode();

	//1인칭 카메라 또는 3인칭 카메라의 경우 플레이어의 회전은 약간의 제약이 따른다. 
	if ((nCameraMode == FIRST_PERSON_CAMERA) || (nCameraMode == THIRD_PERSON_CAMERA))
	{
		/*

			로컬 x-축을 중심으로 회전하는 것은 고개를 앞뒤로 숙이는 동작에 해당한다.
			그러므로 x-축을 중심으로 회전하는 각도는 -89.0~+89.0도 사이로 제한한다.
			x는 현재의 m_fPitch에서 실제 회전하는 각도이므로 x만큼 회전한 다음
			Pitch가 +89도 보다 크거나 -89도 보다 작으면 m_fPitch가 +89도 또는 -89도가 되도록 회전각도(x)를 수정한다.

		*/

		m_pCamera->Rotate(fPitch, fYaw, fRoll);
		if (fPitch != 0.0f)
		{
			XMMATRIX mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Right), XMConvertToRadians(fPitch));
			m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, mtxRotate);
			m_xmf3Up = Vector3::TransformNormal(m_xmf3Up, mtxRotate);
		}
		if (fYaw != 0.0f)
		{
			XMMATRIX mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Up), XMConvertToRadians(fYaw));
			m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, mtxRotate);
			m_xmf3Right = Vector3::TransformNormal(m_xmf3Right, mtxRotate);
		}
		if (fRoll != 0.0f)
		{
			XMMATRIX mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Look), XMConvertToRadians(fRoll));
			m_xmf3Up = Vector3::TransformNormal(m_xmf3Up, mtxRotate);
			m_xmf3Right = Vector3::TransformNormal(m_xmf3Right, mtxRotate);
		}


		//카메라를 x, y, z 만큼 회전한다. 플레이어를 회전하면 카메라가 회전하게 된다.
		m_pCamera->Rotate(fPitch, fYaw, fRoll);

		/*
		플레이어를 회전한다. 1인칭 카메라 또는 3인칭 카메라에서 플레이어의 회전은 로컬 y-축에서만 일어난다.
		플레이어 의 로컬 y-축(Up 벡터)을 기준으로 로컬 z-축(Look 벡터)와 로컬 x-축(Right 벡터)을 회전시킨다.
		기본적으로 Up 벡 터를 기준으로 회전하는 것은 플레이어가 똑바로 서있는 것을 가정한다는 의미이다.
		*/
		if (fYaw != 0.0f) {
			XMMATRIX xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Up), XMConvertToRadians(fYaw));
			m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, xmmtxRotate); m_xmf3Right = Vector3::TransformNormal(m_xmf3Right, xmmtxRotate);
		}

	}
	else if (nCameraMode == SPACESHIP_CAMERA) { /*스페이스-쉽 카메라에서 플레이어의 회전은 회전 각도의 제한이 없다. 그리고 모든 축을 중심으로 회전을 할 수 있 다.*/
		m_pCamera->Rotate(fPitch, fYaw, fRoll);
		if (fPitch != 0.0f) {
			XMMATRIX xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Right), XMConvertToRadians(fPitch));
			m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, xmmtxRotate);
			m_xmf3Up = Vector3::TransformNormal(m_xmf3Up, xmmtxRotate);
		}
		if (fYaw != 0.0f) {
			XMMATRIX xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Up), XMConvertToRadians(fYaw));
			m_xmf3Look = Vector3::TransformNormal(m_xmf3Look, xmmtxRotate);
			m_xmf3Right = Vector3::TransformNormal(m_xmf3Right, xmmtxRotate);
		}
		if (fRoll != 0.0f)
		{
			XMMATRIX xmmtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_xmf3Look), XMConvertToRadians(fRoll));
			m_xmf3Up = Vector3::TransformNormal(m_xmf3Up, xmmtxRotate);
			m_xmf3Right = Vector3::TransformNormal(m_xmf3Right, xmmtxRotate);
		}

	}
	/*
		회전으로 인해 플레이어의 로컬 x-축, y-축, z-축이 서로 직교하지 않을 수 있으므로
		z-축(LookAt 벡터)을 기준으 로 하여 서로 직교하고 단위벡터가 되도록 한다.
	*/
	m_xmf3Look = Vector3::Normalize(m_xmf3Look);
	m_xmf3Right = Vector3::Normalize(Vector3::CrossProduct(m_xmf3Up, m_xmf3Look));
	m_xmf3Up = Vector3::Normalize(Vector3::CrossProduct(m_xmf3Look, m_xmf3Right));
}

void CPlayer::LookAt(XMFLOAT3& xmf3LookAt, XMFLOAT3& xmf3Up)
{
	XMFLOAT4X4 xmf4x4View = Matrix4x4::LookAtLH(m_xmf3Position, xmf3LookAt, xmf3Up);
	m_xmf3Right = Vector3::Normalize(XMFLOAT3(xmf4x4View._11, xmf4x4View._21, xmf4x4View._31));
	m_xmf3Up = Vector3::Normalize(XMFLOAT3(xmf4x4View._12, xmf4x4View._22, xmf4x4View._32));
	m_xmf3Look = Vector3::Normalize(XMFLOAT3(xmf4x4View._13, xmf4x4View._23, xmf4x4View._33));
}

// 매 프레임마다 호출. 플레이어의 속도 벡터에 중력과 마찰력 등을 적용
void CPlayer::Update(float fTimeElapsed)
{
	Move(m_xmf3Velocity, false);

	m_pCamera->Update(this, m_xmf3Position, fTimeElapsed);
	m_pCamera->GenerateViewMatrix();

	XMFLOAT3 xmf3Deceleration = Vector3::Normalize(Vector3::ScalarProduct(m_xmf3Velocity, -1.0f));

	/*
		플레이어의 속도 벡터가 마찰력 때문에 감속이 되어야 한다면 감속 벡터를 생성한다.
		속도 벡터의 반대 방향 벡터를 구하고 단위 벡터로 만든다.
		마찰 계수를 시간에 비례하도록 하여 마찰력을 구한다.
		단위 벡터에 마찰력을 곱하여 감 속 벡터를 구한다.
		속도 벡터에 감속 벡터를 더하여 속도 벡터를 줄인다.
		마찰력이 속력보다 크면 속력은 0이 될 것이다.
	*/

	float fLength = Vector3::Length(m_xmf3Velocity);
	float fDeceleration = m_fFriction * fTimeElapsed;

	if (fDeceleration > fLength) 
		fDeceleration = fLength;
	m_xmf3Velocity = Vector3::Add(m_xmf3Velocity, xmf3Deceleration, fDeceleration);
}

void CPlayer::Animate(float fElapsedTime)
{
	OnUpdateTransform();

	CGameObject::Animate(fElapsedTime);
}

void CPlayer::OnUpdateTransform()
{
	m_xmf4x4Transform._11 = m_xmf3Right.x; m_xmf4x4Transform._12 = m_xmf3Right.y; m_xmf4x4Transform._13 = m_xmf3Right.z;
	m_xmf4x4Transform._21 = m_xmf3Up.x; m_xmf4x4Transform._22 = m_xmf3Up.y; m_xmf4x4Transform._23 = m_xmf3Up.z;
	m_xmf4x4Transform._31 = m_xmf3Look.x; m_xmf4x4Transform._32 = m_xmf3Look.y; m_xmf4x4Transform._33 = m_xmf3Look.z;
	m_xmf4x4Transform._41 = m_xmf3Position.x; m_xmf4x4Transform._42 = m_xmf3Position.y; m_xmf4x4Transform._43 = m_xmf3Position.z;
}

void CPlayer::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CGameObject::Render(hDCFrameBuffer, pCamera);
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
CAirplanePlayer::CAirplanePlayer()
{
	CAirplaneMesh* pAirplaneMesh = new CAirplaneMesh(6.0f, 6.0f, 1.0f);

	SetMesh(pAirplaneMesh);
	SetColor(RGB(0, 0, 255));

	CCubeMesh* pBulletMesh = new CCubeMesh(1.0f, 4.0f, 1.0f);
	for (int i = 0; i < BULLETS; i++)
	{
		m_ppBullets[i] = new CBulletObject(m_fBulletEffectiveRange);
		m_ppBullets[i]->SetMesh(pBulletMesh);
		m_ppBullets[i]->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
		m_ppBullets[i]->SetRotationSpeed(360.0f);
		m_ppBullets[i]->SetMovingSpeed(120.0f);
		m_ppBullets[i]->SetActive(false);
	}
}

CAirplanePlayer::~CAirplanePlayer()
{
	for (int i = 0; i < BULLETS; i++) if (m_ppBullets[i]) delete m_ppBullets[i];
}

void CAirplanePlayer::Animate(float fElapsedTime)
{
	CPlayer::Animate(fElapsedTime);

	//수정
	ComputeWorldTransform(NULL);
	UpdateBoundingBox();

	for (int i = 0; i < BULLETS; i++)
	{
		if (m_ppBullets[i]->m_bActive)
		{
			m_ppBullets[i]->Animate(fElapsedTime);
			m_ppBullets[i]->ComputeWorldTransform(NULL);
		}
	}
}

void CAirplanePlayer::OnUpdateTransform()
{
	CPlayer::OnUpdateTransform();

	m_xmf4x4Transform = Matrix4x4::Multiply(XMMatrixRotationRollPitchYaw(XMConvertToRadians(90.0f), 0.0f, 0.0f), m_xmf4x4Transform);

	ComputeWorldTransform(NULL);
}

void CAirplanePlayer::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CPlayer::Render(hDCFrameBuffer, pCamera);

	for (int i = 0; i < BULLETS; i++) if (m_ppBullets[i]->m_bActive) m_ppBullets[i]->Render(hDCFrameBuffer, pCamera);
}

void CAirplanePlayer::FireBullet(CGameObject* pLockedObject)
{
	CBulletObject* pBulletObject = NULL;
	for (int i = 0; i < BULLETS; i++)
	{
		if (!m_ppBullets[i]->m_bActive)
		{
			pBulletObject = m_ppBullets[i];
			break;
		}
	}

	if (pBulletObject)
	{
		XMFLOAT3 xmf3Position = GetPosition();
		XMFLOAT3 xmf3Direction = GetUp();
		XMFLOAT3 xmf3FirePosition = Vector3::Add(xmf3Position, Vector3::ScalarProduct(xmf3Direction, 6.0f, false));

		pBulletObject->m_xmf4x4Transform = m_xmf4x4World;

		pBulletObject->SetFirePosition(xmf3FirePosition);
		pBulletObject->SetMovingDirection(xmf3Direction);
		pBulletObject->SetColor(RGB(255, 0, 0));
		pBulletObject->SetActive(true);

		if (pLockedObject)
		{
			pBulletObject->m_pLockedObject = pLockedObject;
			pBulletObject->SetColor(RGB(0, 0, 255));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////
//
CTankPlayer::CTankPlayer()
{
	
	CCubeMesh* pBodyMesh = new CCubeMesh(6.0f, 2.0f, 6.0f);
	SetMesh(pBodyMesh);
	SetColor(RGB(0, 0, 255));

	m_pTurret = new CGameObject();
	CCubeMesh* pTurretMesh = new CCubeMesh(4.0f, 1.5f, 4.0f);
	m_pTurret->SetMesh(pTurretMesh);
	m_pTurret->SetColor(RGB(255, 0, 0));
	m_pTurret->SetPosition(0.0f, 1.75f, 0.0f);
	SetChild(m_pTurret);

	m_pGun = new CGameObject();
	CCubeMesh* pGunMesh = new CCubeMesh(1.0f, 1.0f, 10.0f);
	m_pGun->SetMesh(pGunMesh);
	m_pGun->SetColor(RGB(255, 0, 255));
	m_pGun->SetPosition(0.0f, 1.25f, 4.0f);
	m_pTurret->SetChild(m_pGun);

	CCubeMesh* pBulletMesh = new CCubeMesh(1.0f, 1.0f, 4.0f);
	for (int i = 0; i < BULLETS; i++)
	{
		m_ppBullets[i] = new CBulletObject(m_fBulletEffectiveRange);
		m_ppBullets[i]->SetMesh(pBulletMesh);
		m_ppBullets[i]->SetRotationAxis(XMFLOAT3(0.0f, 0.0f, 1.0f));
		m_ppBullets[i]->SetRotationSpeed(360.0f);
		m_ppBullets[i]->SetMovingSpeed(120.0f);
		m_ppBullets[i]->SetActive(false);
	}

}

CTankPlayer::~CTankPlayer()
{
	for (int i = 0; i < BULLETS; i++) if (m_ppBullets[i]) delete m_ppBullets[i];
}

void CTankPlayer::Animate(float fElapsedTime)
{
	CPlayer::Animate(fElapsedTime);
	ComputeWorldTransform(NULL);

	for (int i = 0; i < BULLETS; i++)
	{
		if (m_ppBullets[i]->m_bActive)
		{
			m_ppBullets[i]->Animate(fElapsedTime);
			m_ppBullets[i]->ComputeWorldTransform(NULL);
		}
	}
}

void CTankPlayer::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CPlayer::Render(hDCFrameBuffer, pCamera);

	for (int i = 0; i < BULLETS; i++) if (m_ppBullets[i]->m_bActive) m_ppBullets[i]->Render(hDCFrameBuffer, pCamera);
}

void CTankPlayer::FireBullet(CGameObject* pLockedObject)
{
	
	CBulletObject* pBulletObject = NULL;
	for (int i = 0; i < BULLETS; i++)
	{
		if (!m_ppBullets[i]->m_bActive)
		{
			pBulletObject = m_ppBullets[i];
			break;
		}
	}

	if (pBulletObject)
	{
		XMFLOAT3 xmf3Position = m_pGun->GetPosition();
		XMFLOAT3 xmf3Direction = m_pGun->GetLook();
		XMFLOAT3 xmf3FirePosition = Vector3::Add(xmf3Position, Vector3::ScalarProduct(xmf3Direction, 6.0f, false));

		pBulletObject->m_xmf4x4Transform = m_pGun->m_xmf4x4World;

		pBulletObject->SetFirePosition(xmf3FirePosition);
		pBulletObject->SetMovingDirection(xmf3Direction);
		pBulletObject->SetColor(RGB(255, 50, 150));
		pBulletObject->SetActive(true);

		if (pLockedObject)
		{
			pBulletObject->m_pLockedObject = pLockedObject;
			pBulletObject->SetColor(RGB(255, 255, 0));
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////

CTerrainPlayer::CTerrainPlayer(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, void* pContext, int nMeshes) : CPlayer() {

	m_pCamera = ChangeCamera(THIRD_PERSON_CAMERA, 0.0f);

	CHeightMapTerrain* pTerrain = (CHeightMapTerrain*)pContext;

	//플레이어의 위치를 지형의 가운데(y-축 좌표는 지형의 높이보다 1500 높게)로 설정한다. 
	//플레이어 위치 벡터의 y좌표가 지형의 높이보다 크고 중력이 작용하도록 플레이어를 설정하였으므로 플레이어는 점차적으로 하강하게 된다. 
	float fHeight = pTerrain->GetHeight(pTerrain->GetWidth() * 0.5f, pTerrain->GetLength() * 0.5f);
	SetPosition(XMFLOAT3(pTerrain->GetWidth() * 0.5f, fHeight + 1500.0f, pTerrain->GetLength() * 0.5f));

	//플레이어의 위치가 변경될 때 지형의 정보에 따라 플레이어의 위치를 변경할 수 있도록 설정한다.
	SetPlayerUpdatedContext(pTerrain);

	//카메라의 위치가 변경될 때 지형의 정보에 따라 카메라의 위치를 변경할 수 있도록 설정한다. 
	SetCameraUpdatedContext(pTerrain);

	

	////플레이어를 렌더링할 셰이더를 생성한다. 
	//CPlayerShader* pShader = new CPlayerShader();
	//pShader->CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
	//SetShader(pShader);
	//CreateShaderVariables(pd3dDevice, pd3dCommandList);

}

CTerrainPlayer::~CTerrainPlayer() {

}

CCamera* CTerrainPlayer::ChangeCamera(DWORD nNewCameraMode, float fTimeElapsed) {

	DWORD nCurrentCameraMode = (m_pCamera) ? m_pCamera->GetMode() : 0x00;
	//if (nCurrentCameraMode == nNewCameraMode)
	//	return(m_pCamera);

	//switch (nNewCameraMode) {

	//case FIRST_PERSON_CAMERA:
	//	SetFriction(250.0f);
	//	//1인칭 카메라일 때 플레이어에 y-축 방향으로 중력이 작용한다. 
	//	SetGravity(XMFLOAT3(0.0f, -250.0f, 0.0f));
	//	SetMaxVelocityXZ(300.0f);
	//	SetMaxVelocityY(400.0f);
	//	m_pCamera = OnChangeCamera(FIRST_PERSON_CAMERA, nCurrentCameraMode);
	//	m_pCamera->SetTimeLag(0.0f); m_pCamera->SetOffset(XMFLOAT3(0.0f, 20.0f, 0.0f));
	//	m_pCamera->GenerateProjectionMatrix(1.01f, 50000.0f, ASPECT_RATIO, 60.0f);
	//	break;

	//case SPACESHIP_CAMERA:
	//	SetFriction(125.0f);
	//	//스페이스 쉽 카메라일 때 플레이어에 중력이 작용하지 않는다. 
	//	SetGravity(XMFLOAT3(0.0f, 0.0f, 0.0f));
	//	SetMaxVelocityXZ(300.0f);
	//	SetMaxVelocityY(400.0f);
	//	m_pCamera = OnChangeCamera(SPACESHIP_CAMERA, nCurrentCameraMode);
	//	m_pCamera->SetTimeLag(0.0f);
	//	m_pCamera->SetOffset(XMFLOAT3(0.0f, 0.0f, 0.0f));
	//	m_pCamera->GenerateProjectionMatrix(1.01f, 50000.0f, ASPECT_RATIO, 60.0f);
	//	break;

	//case THIRD_PERSON_CAMERA:
	//	SetFriction(250.0f);
	//	//3인칭 카메라일 때 플레이어에 y-축 방향으로 중력이 작용한다. 
	//	SetGravity(XMFLOAT3(0.0f, -250.0f, 0.0f));
	//	SetMaxVelocityXZ(300.0f);
	//	SetMaxVelocityY(400.0f);
	//	m_pCamera = OnChangeCamera(THIRD_PERSON_CAMERA, nCurrentCameraMode);
	//	m_pCamera->SetTimeLag(0.25f);
	//	m_pCamera->SetOffset(XMFLOAT3(0.0f, 20.0f, -50.0f));
	//	m_pCamera->GenerateProjectionMatrix(1.01f, 50000.0f, ASPECT_RATIO, 60.0f);
	//	break;

	//default:
	//	break;
	//}
	//Update(fTimeElapsed);

	return(m_pCamera);

}

void CTerrainPlayer::OnPlayerUpdateCallback(float fTimeElapsed) {

	//XMFLOAT3 xmf3PlayerPosition = GetPosition();
	//CHeightMapTerrain* pTerrain = (CHeightMapTerrain*)m_pPlayerUpdatedContext;
	///*
	//지형에서 플레이어의 현재 위치 (x, z)의 지형 높이(y)를 구한다.
	//그리고 플레이어 메쉬의 높이가 12이고 플레이어의 중심이 직육면체의 가운데이므로 y 값에 메쉬의 높이의 절반을 더하면 플레이어의 위치가 된다.
	//*/
	//float fHeight = pTerrain->GetHeight(xmf3PlayerPosition.x, xmf3PlayerPosition.z) + 6.0f;

	///*
	//	플레이어의 위치 벡터의 y-값이 음수이면(예를 들어, 중력이 적용되는 경우) 플레이어의 위치 벡터의 y-값이 점점 작아지게 된다.
	//	이때 플레이어의 현재 위치 벡터의 y 값이 지형의 높이(실제로 지형의 높이 + 6)보다 작으면 플레이어의 일부가 지형 아래에 있게 된다.
	//	이러한 경우를 방지하려면 플레이어의 속도 벡터의 y 값을 0으로 만들고 플레이어 의 위치 벡터의 y-값을 지형의 높이(실제로 지형의 높이 + 6)로 설정한다.
	//	그러면 플레이어는 항상 지형 위에 있게 된 다.
	//*/

	//if (xmf3PlayerPosition.y < fHeight)
	//{
	//	XMFLOAT3 xmf3PlayerVelocity = GetVelocity();
	//	xmf3PlayerVelocity.y = 0.0f;
	//	SetVelocity(xmf3PlayerVelocity);
	//	xmf3PlayerPosition.y = fHeight;
	//	SetPosition(xmf3PlayerPosition);
	//}

}

void CTerrainPlayer::OnCameraUpdateCallback(float fTimeElapsed) {

	//XMFLOAT3 xmf3CameraPosition = m_pCamera->GetPosition();
	///*
	//	높이 맵에서 카메라의 현재 위치 (x, z)에 대한 지형의 높이(y 값)를 구한다.
	//	이 값이 카메라의 위치 벡터의 y-값 보 다 크면 카메라가 지형의 아래에 있게 된다.
	//	이렇게 되면 다음 그림의 왼쪽과 같이 지형이 그려지지 않는 경우가 발생 한다(카메라가 지형 안에 있으므로 삼각형의 와인딩 순서가 바뀐다).
	//	이러한 경우가 발생하지 않도록 카메라의 위치 벡 터의 y-값의 최소값은 (지형의 높이 + 5)로 설정한다.
	//	카메라의 위치 벡터의 y-값의 최소값은 지형의 모든 위치에서 카메라가 지형 아래에 위치하지 않도록 설정해야 한다.
	//*/
	//CHeightMapTerrain* pTerrain = (CHeightMapTerrain*)m_pCameraUpdatedContext;
	//float fHeight = pTerrain->GetHeight(xmf3CameraPosition.x, xmf3CameraPosition.z) + 5.0f;
	//if (xmf3CameraPosition.y <= fHeight)
	//{
	//	xmf3CameraPosition.y = fHeight;
	//	m_pCamera->SetPosition(xmf3CameraPosition);
	//	if (m_pCamera->GetMode() == THIRD_PERSON_CAMERA)
	//	{
	//		//3인칭 카메라의 경우 카메라 위치(y-좌표)가 변경되었으므로 카메라가 플레이어를 바라보도록 한다. 
	//		CThirdPersonCamera* p3rdPersonCamera = (CThirdPersonCamera*)m_pCamera;
	//		p3rdPersonCamera->SetLookAt(GetPosition());
	//	}
	//}


}