#include "stdafx.h"
#include "Scene.h"
#include "GraphicsPipeline.h"


CScene::CScene(CPlayer* pPlayer)
{

}
CScene::CScene(CPlayer* pPlayer, CPlayer* pPlayer2)
{
	m_pPlayer = pPlayer;
	m_pPlayer2 = pPlayer2;
}

CScene::~CScene()
{
}


void CScene::BuildObjects()
{
	CExplosiveObject::PrepareExplosion();

	float fHalfWidth = 45.0f, fHalfHeight = 45.0f, fHalfDepth = 200.0f;
	CFloorMesh* pFloorMesh = new CFloorMesh(fHalfWidth * 2.0f, fHalfDepth * 2.0f, 30);

	m_pFloorObject = new CFloorObject();
	m_pFloorObject->SetPosition(0.0f, 0.0f, 0.0f);
	m_pFloorObject->SetMesh(pFloorMesh);
	m_pFloorObject->SetColor(RGB(0, 0, 0));
	m_pFloorObject->m_pxmf4FloorPlane = XMFLOAT4(0.0f, +1.0f, 0.0f, 0.0f);

	CCubeMesh* pCubeMesh = new CCubeMesh(5.0f, 5.0f, 5.0f);
	CTankPlayer* pTankMesh = new CTankPlayer();

	m_nObjects = 13;
	m_ppObjects = new CGameObject * [m_nObjects];
	// 폭발물 set
	CExplosiveObject* pExplosiveObject = new CExplosiveObject();
	pExplosiveObject->SetMesh(pCubeMesh);
	pExplosiveObject->SetColor(RGB(255, 0, 0));
	pExplosiveObject->SetPosition(-15.0f, 0.0f, 90.0f);
	pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	pExplosiveObject->SetRotationSpeed(90.0f);
	m_ppObjects[0] = pExplosiveObject;

	pExplosiveObject = new CExplosiveObject();
	pExplosiveObject->SetMesh(pCubeMesh);
	pExplosiveObject->SetColor(RGB(0, 0, 255));
	pExplosiveObject->SetPosition(0.0f, 0.0f, 90.0f);
	pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	pExplosiveObject->SetRotationSpeed(180.0f);
	m_ppObjects[1] = pExplosiveObject;

	pExplosiveObject = new CExplosiveObject();
	pExplosiveObject->SetMesh(pCubeMesh);
	pExplosiveObject->SetColor(RGB(0, 255, 0));
	pExplosiveObject->SetPosition(15.0f, 0.0f, 90.0f);
	pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	pExplosiveObject->SetRotationSpeed(30.15f);
	m_ppObjects[2] = pExplosiveObject;

	pExplosiveObject = new CExplosiveObject();
	pExplosiveObject->SetMesh(pCubeMesh);
	pExplosiveObject->SetColor(RGB(0, 255, 255));
	pExplosiveObject->SetPosition(+43.5f, 0.0f, +44.0f);
	pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	pExplosiveObject->SetRotationSpeed(40.6f);
	m_ppObjects[3] = pExplosiveObject;

	pExplosiveObject = new CExplosiveObject();
	pExplosiveObject->SetMesh(pCubeMesh);
	pExplosiveObject->SetColor(RGB(128, 0, 255));
	pExplosiveObject->SetPosition(0.0f, 0.0f, 40.0f);
	pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	pExplosiveObject->SetRotationSpeed(50.06f);
	m_ppObjects[4] = pExplosiveObject;

	pExplosiveObject = new CExplosiveObject();
	pExplosiveObject->SetMesh(pCubeMesh);
	pExplosiveObject->SetColor(RGB(255, 0, 255));
	pExplosiveObject->SetPosition(-20.0f, 0.0f, -20.0f);
	pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	pExplosiveObject->SetRotationSpeed(60.06f);
	m_ppObjects[5] = pExplosiveObject;

	pExplosiveObject = new CExplosiveObject();
	pExplosiveObject->SetMesh(pCubeMesh);
	pExplosiveObject->SetColor(RGB(255, 0, 255));
	pExplosiveObject->SetPosition(-20.0f, 0.0f, +20.0f);
	pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	pExplosiveObject->SetRotationSpeed(60.06f);
	m_ppObjects[6] = pExplosiveObject;

	pExplosiveObject = new CExplosiveObject();
	pExplosiveObject->SetMesh(pCubeMesh);
	pExplosiveObject->SetColor(RGB(255, 0, 128));
	pExplosiveObject->SetPosition(+20.0f, 0.0f, -20.0f);
	pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	pExplosiveObject->SetRotationSpeed(70.06f);
	m_ppObjects[7] = pExplosiveObject;

	pExplosiveObject = new CExplosiveObject();
	pExplosiveObject->SetMesh(pCubeMesh);
	pExplosiveObject->SetColor(RGB(128, 0, 255));
	pExplosiveObject->SetPosition(+20.0f, 0.0f, +20.0f);
	pExplosiveObject->SetRotationAxis(XMFLOAT3(1.0f, 0.0f, 0.0f));
	pExplosiveObject->SetRotationSpeed(90.06f);
	m_ppObjects[8] = pExplosiveObject;

	pExplosiveObject = new CExplosiveObject();
	pExplosiveObject->SetMesh(pCubeMesh);
	pExplosiveObject->SetColor(RGB(255, 64, 64));
	pExplosiveObject->SetPosition(+15.0f, 0.0f, 0.0f);
	pExplosiveObject->SetRotationAxis(XMFLOAT3(1.0f, 0.0f, 0.0f));
	pExplosiveObject->SetRotationSpeed(90.06f);
	m_ppObjects[9] = pExplosiveObject;
	pExplosiveObject = new CExplosiveObject();
	pExplosiveObject->SetMesh(pCubeMesh);
	pExplosiveObject->SetColor(RGB(255, 0, 128));
	pExplosiveObject->SetPosition(+20.0f, 0.0f, -20.0f);
	pExplosiveObject->SetRotationAxis(XMFLOAT3(0.0f, 1.0f, 0.0f));
	pExplosiveObject->SetRotationSpeed(70.06f);
	m_ppObjects[10] = pExplosiveObject;

	pExplosiveObject = new CExplosiveObject();
	pExplosiveObject->SetMesh(pCubeMesh);
	pExplosiveObject->SetColor(RGB(128, 0, 255));
	pExplosiveObject->SetPosition(+20.0f, 0.0f, +20.0f);
	pExplosiveObject->SetRotationAxis(XMFLOAT3(1.0f, 0.0f, 0.0f));
	pExplosiveObject->SetRotationSpeed(90.06f);
	m_ppObjects[11] = pExplosiveObject;

	pExplosiveObject = new CExplosiveObject();
	pExplosiveObject->SetMesh(pCubeMesh);
	pExplosiveObject->SetColor(RGB(255, 64, 64));
	pExplosiveObject->SetPosition(+15.0f, 0.0f, 0.0f);
	pExplosiveObject->SetRotationAxis(XMFLOAT3(1.0f, 0.0f, 0.0f));
	pExplosiveObject->SetRotationSpeed(90.06f);
	m_ppObjects[12] = pExplosiveObject;

#ifdef _WITH_DRAW_AXIS
	m_pWorldAxis = new CGameObject();
	CAxisMesh* pAxisMesh = new CAxisMesh(0.5f, 0.5f, 0.5f);
	m_pWorldAxis->SetMesh(pAxisMesh);
#endif
}

void CScene::ReleaseObjects()
{
	if (CExplosiveObject::m_pExplosionMesh) CExplosiveObject::m_pExplosionMesh->Release();

	for (int i = 0; i < m_nObjects; i++) if (m_ppObjects[i]) delete m_ppObjects[i];
	if (m_ppObjects) delete[] m_ppObjects;

	if (m_pFloorObject) delete m_pFloorObject;

#ifdef _WITH_DRAW_AXIS
	if (m_pWorldAxis) delete m_pWorldAxis;
#endif
}

void CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[int(wParam - '1')];
			pExplosiveObject->m_bBlowingUp = true;
			break;
		}
		/*case 'A':
			for (int i = 0; i < m_nObjects; i++)
			{
				CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[i];
				pExplosiveObject->m_bBlowingUp = true;
			}
			break;*/
		default:
			break;
		}
		break;
	default:
		break;
	}
}

CGameObject* CScene::PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera)
{
	/*XMFLOAT3 xmf3PickPosition;
	xmf3PickPosition.x = (((2.0f * xClient) / (float)pCamera->m_Viewport.m_nWidth) - 1) / pCamera->m_xmf4x4PerspectiveProject._11;
	xmf3PickPosition.y = -(((2.0f * yClient) / (float)pCamera->m_Viewport.m_nHeight) - 1) / pCamera->m_xmf4x4PerspectiveProject._22;
	xmf3PickPosition.z = 1.0f;

	XMVECTOR xmvPickPosition = XMLoadFloat3(&xmf3PickPosition);
	XMMATRIX xmmtxView = XMLoadFloat4x4(&pCamera->m_xmf4x4View);*/

	int nIntersected = 0;
	float fNearestHitDistance = FLT_MAX;
	CGameObject* pNearestObject = NULL;

	float fHitDistance = FLT_MAX;
	//nIntersected = m_pPlayer->PickObjectByRayIntersection(xmvPickPosition, xmmtxView, &fHitDistance);
	/*if ((nIntersected > 0) && (fHitDistance < fNearestHitDistance))
	{*/
		fNearestHitDistance = fHitDistance;
		pNearestObject = m_pPlayer;
	//}

	return(pNearestObject);
}

//csene 에서 오브젝트끼리 충돌 체크하는 함수
void CScene::CheckObjectByObjectCollisions()
{
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->m_pObjectCollided = NULL;
	for (int i = 0; i < m_nObjects; i++)
	{
		for (int j = (i + 1); j < m_nObjects; j++)
		{
			if (m_ppObjects[i]->m_xmOOBB.Intersects(m_ppObjects[j]->m_xmOOBB))
			{
				m_ppObjects[i]->m_pObjectCollided = m_ppObjects[j];
				m_ppObjects[j]->m_pObjectCollided = m_ppObjects[i];
			}
		}
	}
	for (int i = 0; i < m_nObjects; i++)
	{
		if (m_ppObjects[i]->m_pObjectCollided)
		{
			XMFLOAT3 xmf3MovingDirection = m_ppObjects[i]->m_xmf3MovingDirection;
			float fMovingSpeed = m_ppObjects[i]->m_fMovingSpeed;
			m_ppObjects[i]->m_xmf3MovingDirection = m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection;
			m_ppObjects[i]->m_fMovingSpeed = m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection = xmf3MovingDirection;
			m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed = fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_pObjectCollided = NULL;
			m_ppObjects[i]->m_pObjectCollided = NULL;
		}
	}
}

//Cscene의 총알과 오브젝트 충돌 체크하는 함수
void CScene::CheckObjectByBulletCollisions()
{
	CBulletObject** ppBullets = ((CTankPlayer*)m_pPlayer)->m_ppBullets;
	for (int i = 0; i < m_nObjects; i++)
	{
		for (int j = 0; j < BULLETS; j++)
		{
			if (ppBullets[j]->m_bActive && m_ppObjects[i]->m_xmOOBB.Intersects(ppBullets[j]->m_xmOOBB))
			{
				if (m_pPlayer->HP < 10)
					m_pPlayer->HP += 1;
				CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[i];
				pExplosiveObject->m_bBlowingUp = true;
				ppBullets[j]->Reset();
			}
		}
	}

	CBulletObject** ppBullets2 = ((CTankPlayer*)m_pPlayer2)->m_ppBullets;
	for (int i = 0; i < m_nObjects; i++)
	{
		for (int j = 0; j < BULLETS; j++)
		{
			if (ppBullets2[j]->m_bActive && m_ppObjects[i]->m_xmOOBB.Intersects(ppBullets2[j]->m_xmOOBB))
			{
				if (m_pPlayer2->HP < 10)
					m_pPlayer2->HP += 1;
				CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[i];
				pExplosiveObject->m_bBlowingUp = true;
				ppBullets2[j]->Reset();
			}
		}
	}

}


void CScene::FollwPlayer()
{
	for (int i = 0; i < m_nObjects; i++) {
		XMFLOAT3 AttackDirection = Vector3::Subtract(m_pPlayer->GetPosition(), m_ppObjects[i]->GetPosition());
		//	float AttackRotatex = Vector3::AngleX(m_ppGameMissileObjects[i]->GetLook(), AttackDirection) ;
		//	float AttackRotatey = Vector3::AngleY(m_ppGameMissileObjects[i]->GetLook(), AttackDirection) ;
			//float AttackRotatez = Vector3::AngleZ(m_ppGameMissileObjects[i]->GetLook(), AttackDirection) ;
			//m_ppGameObjects[i]->Rotate(AttackRotatex, AttackRotatey, AttackRotatez);
			//XMFLOAT3 RotateTemp=
		/*m_ppObjects[i]->SetLookAt(AttackDirection,
			XMFLOAT3(m_pPlayer.x,m_ppGameObjects[i]->GetUp().y,m_ppGameObjects[i]->GetUp().z));
		float AttackRotatez = Vector3::AngleX(m_ppGameObjects[i]->GetUp(), XMFLOAT3(1, 1, 1));*/
		//if (AttackRotatez > 90) {
		//	//m_ppGameObjects[i]->Rotate(0, 0, 0);
		//}

		//m_ppGameObjects[i]->SetMovingDirection(m_ppGameMissileObjects[i]->GetLook());
	}
}
//Cscene의 탱크와 오브젝트 충돌 체크하는 함수
void CScene::CheckObjectByTankCollisions()
{
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->m_pObjectCollided = NULL;
	for (int i = 0; i < m_nObjects; i++)
	{
		if (m_ppObjects[i]->m_xmOOBB.Intersects(m_pPlayer->m_xmOOBB))
		{
			m_pFloorObject->SetColor(RGB(0, 0, 255));

			m_ppObjects[i]->m_pObjectCollided = m_pPlayer;
			m_pPlayer->m_pObjectCollided = m_ppObjects[i];

			CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_ppObjects[i];
			pExplosiveObject->m_bBlowingUp = true;
		}

	}
	for (int i = 0; i < m_nObjects; i++)
	{
		if (m_ppObjects[i]->m_pObjectCollided)
		{
			XMFLOAT3 xmf3MovingDirection = m_ppObjects[i]->m_xmf3MovingDirection;
			float fMovingSpeed = m_ppObjects[i]->m_fMovingSpeed;
			m_ppObjects[i]->m_xmf3MovingDirection = m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection;
			m_ppObjects[i]->m_fMovingSpeed = m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_xmf3MovingDirection = xmf3MovingDirection;
			m_ppObjects[i]->m_pObjectCollided->m_fMovingSpeed = fMovingSpeed;
			m_ppObjects[i]->m_pObjectCollided->m_pObjectCollided = NULL;
			m_ppObjects[i]->m_pObjectCollided = NULL;
		}
	}

}
//Cscene의 총알과 탱크 충돌 체크하는 함수
void CScene::CheckTankByBulletCollisions()
{
	CBulletObject** ppBullets = ((CTankPlayer*)m_pPlayer)->m_ppBullets;
	for (int j = 0; j < BULLETS; j++)
	{
		if (ppBullets[j]->m_bActive && m_pPlayer2->m_xmOOBB.Intersects(ppBullets[j]->m_xmOOBB))
		{
			m_pFloorObject->SetColor(RGB(255, 0, 0));
			m_pPlayer2->HP -= 1;
			if (m_pPlayer2->HP <= 0) {
				//내가 이기면 흰색 바닥
				m_pFloorObject->SetColor(RGB(255, 255, 255));
				GameOver = true;
				CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_pPlayer2;
				pExplosiveObject->m_bBlowingUp = true;
				//m_pPlayer2->HP = 10;

			}
			ppBullets[j]->Reset();
		}
	}
	CBulletObject** ppBullets2 = ((CTankPlayer*)m_pPlayer2)->m_ppBullets;
	for (int j = 0; j < BULLETS; j++)
	{
		if (ppBullets2[j]->m_bActive && m_pPlayer->m_xmOOBB.Intersects(ppBullets2[j]->m_xmOOBB))
		{
			m_pFloorObject->SetColor(RGB(0, 0, 255));
			m_pPlayer->HP -= 1;
			if (m_pPlayer->HP <= 0) {
				//내가 지면 검정 바닥
				m_pFloorObject->SetColor(RGB(0, 0, 0));
				GameOver = true;
				CExplosiveObject* pExplosiveObject = (CExplosiveObject*)m_pPlayer;
				pExplosiveObject->m_bBlowingUp = true;
			}
			ppBullets2[j]->Reset();
		}
	}
}

void CScene::Animate(float fElapsedTime)
{
	m_pFloorObject->Animate(fElapsedTime);
	
	m_pFloorObject->ComputeWorldTransform(NULL);

	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Animate(fElapsedTime);
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->ComputeWorldTransform(NULL);

	CheckObjectByObjectCollisions();
	CheckObjectByBulletCollisions();
	CheckTankByBulletCollisions();
	CheckObjectByTankCollisions();
}

void CScene::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
	CGraphicsPipeline::SetViewport(&pCamera->m_Viewport);
	CGraphicsPipeline::SetViewPerspectiveProjectTransform(&pCamera->m_xmf4x4ViewPerspectiveProject);

	m_pFloorObject->Render(hDCFrameBuffer, pCamera);
	for (int i = 0; i < m_nObjects; i++) m_ppObjects[i]->Render(hDCFrameBuffer, pCamera);

	if (m_pPlayer) m_pPlayer->Render(hDCFrameBuffer, pCamera);
	if (m_pPlayer2) m_pPlayer2->Render(hDCFrameBuffer, pCamera);

	//UI
#ifdef _WITH_DRAW_AXIS
	CGraphicsPipeline::SetViewOrthographicProjectTransform(&pCamera->m_xmf4x4ViewOrthographicProject);
	m_pWorldAxis->SetRotationTransform(&m_pPlayer->m_xmf4x4World);
	m_pWorldAxis->Render(hDCFrameBuffer, pCamera);
#endif
}
