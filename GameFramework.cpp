//-----------------------------------------------------------------------------
// File: CGameFramework.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GameFramework.h"

void CGameFramework::OnCreate(HINSTANCE hInstance, HWND hMainWnd)
{
	::srand(timeGetTime());

	m_hInstance = hInstance;
	m_hWnd = hMainWnd;

	BuildFrameBuffer();

	BuildObjects();

	_tcscpy_s(m_pszFrameRate, _T("2020184025 ("));
}

void CGameFramework::OnDestroy()
{
	ReleaseObjects();

	if (m_hBitmapFrameBuffer) ::DeleteObject(m_hBitmapFrameBuffer);
	if (m_hDCFrameBuffer) ::DeleteDC(m_hDCFrameBuffer);
}

void CGameFramework::BuildFrameBuffer()
{
	::GetClientRect(m_hWnd, &m_rcClient);

	HDC hDC = ::GetDC(m_hWnd);

	m_hDCFrameBuffer = ::CreateCompatibleDC(hDC);
	m_hBitmapFrameBuffer = ::CreateCompatibleBitmap(hDC, m_rcClient.right - m_rcClient.left, m_rcClient.bottom - m_rcClient.top);
	::SelectObject(m_hDCFrameBuffer, m_hBitmapFrameBuffer);

	::ReleaseDC(m_hWnd, hDC);
	::SetBkMode(m_hDCFrameBuffer, TRANSPARENT);
}

void CGameFramework::ClearFrameBuffer(DWORD dwColor)
{
	HPEN hPen = ::CreatePen(PS_SOLID, 0, dwColor);
	HPEN hOldPen = (HPEN)::SelectObject(m_hDCFrameBuffer, hPen);
	HBRUSH hBrush = ::CreateSolidBrush(dwColor);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(m_hDCFrameBuffer, hBrush);
	::Rectangle(m_hDCFrameBuffer, m_rcClient.left, m_rcClient.top, m_rcClient.right, m_rcClient.bottom);
	::SelectObject(m_hDCFrameBuffer, hOldBrush);
	::SelectObject(m_hDCFrameBuffer, hOldPen);
	::DeleteObject(hPen);
	::DeleteObject(hBrush);
}

void CGameFramework::PresentFrameBuffer()
{
	HDC hDC = ::GetDC(m_hWnd);
	::BitBlt(hDC, m_rcClient.left, m_rcClient.top, m_rcClient.right - m_rcClient.left, m_rcClient.bottom - m_rcClient.top, m_hDCFrameBuffer, m_rcClient.left, m_rcClient.top, SRCCOPY);
	::ReleaseDC(m_hWnd, hDC);
}

//렌더링할 객체를 생성하는 함수
void CGameFramework::BuildObjects()
{

	CCamera* pCamera = new CCamera();
	CCamera* pCamera2 = new CCamera();
	pCamera->SetViewport(0, 0, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
	pCamera->GeneratePerspectiveProjectionMatrix(1.01f, 500.0f, 60.0f);
	pCamera->SetFOVAngle(60.0f);

	pCamera->GenerateOrthographicProjectionMatrix(1.01f, 50.0f, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);

	pCamera2->SetViewport(0, 0, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
	pCamera2->GeneratePerspectiveProjectionMatrix(1.01f, 500.0f, 60.0f);
	pCamera2->SetFOVAngle(60.0f);

	pCamera2->GenerateOrthographicProjectionMatrix(1.01f, 50.0f, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);

	m_pPlayer = new CTankPlayer();
	m_pPlayer->SetPosition(0.0f, 1.0f, -50.0f);
	m_pPlayer->SetCamera(pCamera);
	m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 10.0f, -20.0f));
	m_pPlayer->LookAt(XMFLOAT3(0.0f, 0.0f, 0.0f), m_pPlayer->GetUp());

	m_pPlayer2 = new CTankPlayer();
	m_pPlayer2->SetPosition(0.0f, 1.0f, 20.0f);
	m_pPlayer2->SetCamera(pCamera2);
	m_pPlayer2->SetCameraOffset(XMFLOAT3(0.0f, 10.0f, 10.0f));
	m_pPlayer2->LookAt(XMFLOAT3(0.0f, 1.0f, 0.0f), m_pPlayer2->GetUp());

	m_pPlayer2->playTurn = true;
	m_pPlayer2->MoveStrafe(10);
	m_pScene = new CScene(m_pPlayer, m_pPlayer2);
	m_pLockedObject = m_pScene->PickObjectPointedByCursor(LOWORD(1), HIWORD(1), m_pPlayer->m_pCamera);
	m_pScene->BuildObjects();
}

// 렌더링할 객체를 소멸시키는 함수
void CGameFramework::ReleaseObjects()
{
	if (m_pScene)
	{
		m_pScene->ReleaseObjects();
		delete m_pScene;
	}

	if (m_pPlayer) delete m_pPlayer;
	if (m_pPlayer2) delete m_pPlayer2;
}

void CGameFramework::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (m_pScene) m_pScene->OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
	// mouse input
	switch (nMessageID)
	{
	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
		::SetCapture(hWnd);
		::GetCursorPos(&m_ptOldCursorPos);
		// 오른 쪽 버튼
		if (nMessageID == WM_RBUTTONDOWN)
		{
			m_pLockedObject = m_pScene->PickObjectPointedByCursor(LOWORD(lParam), HIWORD(lParam), m_pPlayer->m_pCamera);
			if (m_pLockedObject)
				m_pLockedObject->SetColor(RGB(0, 0, 0));
		}
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		::ReleaseCapture();
		break;
	case WM_MOUSEMOVE:
		break;
	default:
		break;
	}
}

void CGameFramework::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	// keyboard input
	if (m_pScene) m_pScene->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);

	switch (nMessageID)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			::PostQuitMessage(0);
			break;
		case VK_RETURN:
			break;
			// 탱크 객체1
		case 'F':
			((CTankPlayer*)m_pPlayer)->RotateTurret(+5.0f);
			break;
		case 'S':
			((CTankPlayer*)m_pPlayer)->RotateTurret(-5.0f);
			break;
		case 'D':
			((CTankPlayer*)m_pPlayer)->RotateGun(+1.0f);
			break;
		case 'E':
			((CTankPlayer*)m_pPlayer)->RotateGun(-1.0f);
			break;
		case 'N':
			//토글 뷰 변환
			if (togleView) {
				togleView = false;
				m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 10.0f, -20.0f));
			}
			else{
				togleView = true;
				m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 50.0f,-1.0f));
			}
			break;
			//	// 탱크 객체 2
			//case 'L': //상
			//	((CTankPlayer*)m_pPlayer2)->RotateTurret(+5.0f);
			//	break;
			//case 'J': //하
			//	((CTankPlayer*)m_pPlayer2)->RotateTurret(-5.0f);
			//	break;
			//case 'K': //좌
			//	((CTankPlayer*)m_pPlayer2)->RotateGun(+1.0f);
			//	break;
			//case 'I': //우
			//	((CTankPlayer*)m_pPlayer2)->RotateGun(-1.0f);
				//break;
			// 게임 타이머 다시 가동
		case 'R':
			BuildObjects();
			m_pScene->GameOver = false;
			m_GameTimer.Start();
			m_pPlayer2->HP = 10;
			m_pPlayer->HP = 10;
			break;
		case VK_CONTROL:
			if (!m_pScene->GameOver) {
				((CTankPlayer*)m_pPlayer)->FireBullet(m_pLockedObject2);
				//m_pLockedObject = NULL;
			}
			break;
		case 'O':
			if (!m_pScene->GameOver) {
				((CTankPlayer*)m_pPlayer2)->FireBullet(m_pLockedObject);
				m_pLockedObject2 = NULL;
			}
			break;
		case VK_F1:
		case VK_F2:
		case VK_F3:
			m_pCamera = m_pPlayer->ChangeCamera((DWORD)(wParam - VK_F1 + 1), m_GameTimer.GetTimeElapsed());
			break;

		default:
			m_pScene->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
			break;
		}
		break;
	default:
		break;
	}
}

LRESULT CALLBACK CGameFramework::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_ACTIVATE:
	{
		// window 활성화 = timer 가동
		// window 비활성화 = timer 멈춤
		if (LOWORD(wParam) == WA_INACTIVE)
			m_GameTimer.Stop();
		else
			m_GameTimer.Start();
		break;
	}
	case WM_SIZE:// 창 크기
		break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
		break;
	case WM_KEYDOWN:
	case WM_KEYUP:
		OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
		break;
	}
	return(0);
}

// 사용자 입력을 처리하는 함수
void CGameFramework::ProcessInput()
{
	static UCHAR pKeyBuffer[256];
	if (GetKeyboardState(pKeyBuffer) && !m_pScene->GameOver)
	{
		DWORD dwDirection = 0;
		if (pKeyBuffer[VK_UP] & 0xF0) dwDirection |= DIR_FORWARD;		// ‘↑’
		if (pKeyBuffer[VK_DOWN] & 0xF0) dwDirection |= DIR_BACKWARD;	// ‘↓’
		if (pKeyBuffer[VK_LEFT] & 0xF0) dwDirection |= DIR_LEFT;		// ‘←’
		if (pKeyBuffer[VK_RIGHT] & 0xF0) dwDirection |= DIR_RIGHT;		// ‘→’
		if (pKeyBuffer[VK_PRIOR] & 0xF0) dwDirection |= DIR_UP;			// 'page up'
		if (pKeyBuffer[VK_NEXT] & 0xF0) dwDirection |= DIR_DOWN;		// 'page down'

		if (dwDirection) {
			m_pPlayer->Move(dwDirection, 0.2f);
			//m_pPlayer2->Move(dwDirection, 0.25f);
		}
	}

	// 마우스 또는 키 입력이 있으면 플레이어를 이동 or 회전
	if (GetCapture() == m_hWnd)
	{
		// 마우스 커서가 보이지 않게 한다
		SetCursor(NULL);

		// 마우스 커서 위치 받아오기
		POINT ptCursorPos;
		GetCursorPos(&ptCursorPos);

		// cxMouseDelta는 y축의 회전 | 오른쪽 마우스 버튼이 눌려진 경우 z축의 회전
		// cyMouseDelta는 x축의 회전
		float cxMouseDelta = (float)(ptCursorPos.x - m_ptOldCursorPos.x) / 3.0f;
		float cyMouseDelta = (float)(ptCursorPos.y - m_ptOldCursorPos.y) / 3.0f;

		// 마우스 커서의 위치 = 마우스 클릭 위치로 설정
		SetCursorPos(m_ptOldCursorPos.x, m_ptOldCursorPos.y);

		// 일단 x축 회전은 허용안함
		if (cxMouseDelta || cyMouseDelta)
		{
			if (pKeyBuffer[VK_RBUTTON] & 0xF0)
				m_pPlayer->Rotate(0.0f, 0.0f, -cxMouseDelta);
			else
				m_pPlayer->Rotate(0.0f, cxMouseDelta, 0.0f);
		}
	}
	// 플레이어를 실제로 이동하고 카메라 갱신
	// 중력과 마찰력의 영향을 속도 벡터에 적용
	m_pPlayer->Update(m_GameTimer.GetTimeElapsed());
	m_pPlayer2->Update(m_GameTimer.GetTimeElapsed());

}

// 오브젝트들의 움직임을 처리하는 함수 
void CGameFramework::AnimateObjects()
{
	float fTimeElapsed = m_GameTimer.GetTimeElapsed();

	if (m_pPlayer && !m_pScene->GameOver) m_pPlayer->Animate(fTimeElapsed);
	if (m_pPlayer2 && !m_pScene->GameOver) m_pPlayer2->Animate(fTimeElapsed);
	if (m_pScene && !m_pScene->GameOver) m_pScene->Animate(fTimeElapsed);
	((CTankPlayer*)m_pPlayer2)->FireBullet(m_pLockedObject);
}

// 오브젝트들을 렌더링 해주는 함수
void CGameFramework::FrameAdvance()
{
	m_GameTimer.Tick(60.0f);

	ProcessInput();

	AnimateObjects();

	// 배경 색 클리어
	//ClearFrameBuffer(RGB(210, 255, 255));
	ClearFrameBuffer(RGB(150, 150, 150));

	m_pCamera = m_pPlayer->GetCamera();
	if (m_pScene) m_pScene->Render(m_hDCFrameBuffer, m_pCamera);
	if (m_pScene->GameOver)
		m_GameTimer.Stop();
	PresentFrameBuffer();

	m_GameTimer.GetFrameRate(m_pszFrameRate + 12, 37);
	::SetWindowText(m_hWnd, m_pszFrameRate);
}


