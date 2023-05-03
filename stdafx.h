// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//
// stdafx.h�� header�� �߰��ϴ� ����
// PCH( PreCompiled Header ) �� ���Ͽ� ���� �������� �ʴ�  
// ��� ���Ͽ� ���� �������� �Ź����� �ʾƵ� �Ǵ� ����� �����ϱ� ����
#pragma once

#define WIN32_LEAN_AND_MEAN		// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C�� ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>
#include <d3d12.h>
#include <d3dcompiler.h>

#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")

// Direct Math �Լ�
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>

// Import Library �߰� 
#pragma comment( lib , "d3dCompiler.lib" )
#pragma comment( lib , "d3d12.lib" )
#pragma comment( lib , "dxgi.lib" )
#pragma comment( lib , "winmm.lib" )

using namespace DirectX;
using namespace DirectX::PackedVector;

#define FRAMEBUFFER_WIDTH		1280
#define FRAMEBUFFER_HEIGHT		960

#define DIR_FORWARD				0x01
#define DIR_BACKWARD			0x02
#define DIR_LEFT				0x04
#define DIR_RIGHT				0x08
#define DIR_UP					0x10
#define DIR_DOWN				0x20

#define EXPLOSION_DEBRISES		240

#define RANDOM_COLOR			(0xFF000000 | ((rand() * 0xFFFFFF) / RAND_MAX))

#define DegreeToRadian(x)		float((x)*3.141592654f/180.0f)

#define EPSILON					1.0e-6f

inline bool IsZero(float fValue) { return((fabsf(fValue) < EPSILON)); }
inline bool IsEqual(float fA, float fB) { return(::IsZero(fA - fB)); }

// ���� ���ҽ��� �����ϴ� �Լ��̴�.
// ���ε�� ��� ���ҽ��� �÷� ���� ��, �׷��� ī�忡���� �̿��ϰ� �� ��
// ������ �� ������ ���� ���� ���ҽ��� �����ϰ� �ʱ�ȭ �����Ͱ� ������ �ʱ�ȭ �Ѵ�
extern ID3D12Resource* CreateBufferResource(ID3D12Device* pd3dDevice,
	ID3D12GraphicsCommandList* pd3dCommandList, void* pData, UINT nBytes,
	D3D12_HEAP_TYPE d3dHeapType = D3D12_HEAP_TYPE_UPLOAD,
	D3D12_RESOURCE_STATES d3dResourceStates = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER,
	ID3D12Resource** ppd3dUploadBuffer = NULL
);

// 3���� ������ ����
namespace Vector3
{
	inline bool IsZero(XMFLOAT3& xmf3Vector) {
		if (xmf3Vector.x == 0.0f && xmf3Vector.y == 0.0f && xmf3Vector.z == 0.0f)
			return(true);

		return(false);
	}
	// Vector�� XMFloat3���� �ٲ��ִ� �Լ�
	inline XMFLOAT3 XMVectorToFloat3(XMVECTOR& xmvVector)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, xmvVector);
		return(xmf3Result);
	}

	// ���Ϳ� ��Į�� �������� ���ش�
	inline XMFLOAT3 ScalarProduct(XMFLOAT3& xmf3Vector, float fScalar, bool bNormalize = true)
	{
		XMFLOAT3 xmf3Result;
		if (bNormalize)
			XMStoreFloat3(&xmf3Result, XMVector3Normalize(XMLoadFloat3(&xmf3Vector)) * fScalar);
		else
			XMStoreFloat3(&xmf3Result, XMLoadFloat3(&xmf3Vector) * fScalar);
		return(xmf3Result);
	}

	// ������ �� ����
	inline XMFLOAT3 Add(const XMFLOAT3& xmf3Vector1, const XMFLOAT3& xmf3Vector2)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMLoadFloat3(&xmf3Vector1) + XMLoadFloat3(&xmf3Vector2));
		return(xmf3Result);
	}

	inline XMFLOAT3 Add(XMFLOAT3& xmf3Vector1, XMFLOAT3& xmf3Vector2, float fScalar)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMLoadFloat3(&xmf3Vector1) + (XMLoadFloat3(&xmf3Vector2) * fScalar));
		return(xmf3Result);
	}

	inline XMFLOAT3 Subtract(XMFLOAT3& xmf3Vector1, XMFLOAT3& xmf3Vector2)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMLoadFloat3(&xmf3Vector1) - XMLoadFloat3(&xmf3Vector2));
		return(xmf3Result);
	}

	// ������ ���� ����
	inline float DotProduct(XMFLOAT3& xmf3Vector1, XMFLOAT3& xmf3Vector2)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMVector3Dot(XMLoadFloat3(&xmf3Vector1), XMLoadFloat3(&xmf3Vector2)));
		return(xmf3Result.x);
	}

	// ������ ���� ����
	inline XMFLOAT3 CrossProduct(XMFLOAT3& xmf3Vector1, XMFLOAT3& xmf3Vector2, bool bNormalize = true)
	{
		XMFLOAT3 xmf3Result;
		if (bNormalize)
			XMStoreFloat3(&xmf3Result, XMVector3Normalize(XMVector3Cross(XMVector3Normalize(XMLoadFloat3(&xmf3Vector1)), XMVector3Normalize(XMLoadFloat3(&xmf3Vector2)))));
		else
			XMStoreFloat3(&xmf3Result, XMVector3Cross(XMVector3Normalize(XMLoadFloat3(&xmf3Vector1)), XMVector3Normalize(XMLoadFloat3(&xmf3Vector2))));
		return(xmf3Result);
	}

	// ���͸� �븻������ �ؼ� XMFLOAT3���� ��ȯ
	inline XMFLOAT3 Normalize(XMFLOAT3& xmf3Vector)
	{
		XMFLOAT3 m_xmf3Normal;
		XMStoreFloat3(&m_xmf3Normal, XMVector3Normalize(XMLoadFloat3(&xmf3Vector)));
		return(m_xmf3Normal);
	}

	// ������ ���̸� ���ϴ� �Լ�
	inline float Length(XMFLOAT3& xmf3Vector)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMVector3Length(XMLoadFloat3(&xmf3Vector)));
		return(xmf3Result.x);
	}

	inline float Distance(XMFLOAT3& xmf3Vector1, XMFLOAT3& xmf3Vector2)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMVector3Length(XMVectorSubtract(XMLoadFloat3(&xmf3Vector1), XMLoadFloat3(&xmf3Vector2))));
		return(xmf3Result.x);
	}

	// �� Vector ������ ���� ���ϴ� �Լ�
	inline float Angle(XMVECTOR& xmvVector1, XMVECTOR& xmvVector2)
	{
		XMVECTOR xmvAngle = XMVector3AngleBetweenNormals(xmvVector1, xmvVector2);
		return(XMVectorGetX(XMVectorACos(xmvAngle)));
	}

	// �� XMFLOAT3 ������ Vector������ ���� �����ִ� �Լ�
	inline float Angle(XMFLOAT3& xmf3Vector1, XMFLOAT3& xmf3Vector2)
	{
		return(Angle(XMVector3Normalize(XMLoadFloat3(&xmf3Vector1)), XMVector3Normalize(XMLoadFloat3(&xmf3Vector2))));
	}

	// TransformNormal�� ��� w�� 0���� ������ش� = ���� ��ȯ�� �ַ� ���δ�.
	// ������ ��Ʈ������ ���� ������ 3���� �Ϲ� ���͸� ��ȯ�Ѵ�.
	inline XMFLOAT3 TransformNormal(XMFLOAT3& xmf3Vector, XMMATRIX& xmxm4x4Transform)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMVector3TransformNormal(XMLoadFloat3(&xmf3Vector), xmxm4x4Transform));
		return(xmf3Result);
	}

	inline XMFLOAT3 TransformNormal(XMFLOAT3& xmf3Vector, XMFLOAT4X4& xmmtx4x4Matrix)
	{
		return(TransformNormal(xmf3Vector, XMLoadFloat4x4(&xmmtx4x4Matrix)));
	}

	// TransformCoord�� ��� w�� 1�� ������ش� = ����Ʈ(��ǥ) ��ȯ�� �ַ� ���δ�
	inline XMFLOAT3 TransformCoord(XMFLOAT3& xmf3Vector, XMMATRIX& xmxm4x4Transform)
	{
		XMFLOAT3 xmf3Result;
		XMStoreFloat3(&xmf3Result, XMVector3TransformCoord(XMLoadFloat3(&xmf3Vector), xmxm4x4Transform));
		return(xmf3Result);
	}

	inline XMFLOAT3 TransformCoord(XMFLOAT3& xmf3Vector, XMFLOAT4X4& xmmtx4x4Matrix)
	{
		return(TransformCoord(xmf3Vector, XMLoadFloat4x4(&xmmtx4x4Matrix)));
	}
}

// 4���� ������ ���� 
namespace Vector4
{
	inline XMFLOAT4 Add(XMFLOAT4& xmf4Vector1, XMFLOAT4& xmf4Vector2)
	{
		XMFLOAT4 xmf4Result;
		XMStoreFloat4(&xmf4Result, XMLoadFloat4(&xmf4Vector1) + XMLoadFloat4(&xmf4Vector2));
		return(xmf4Result);
	}


	inline XMFLOAT4 Multiply(float fScalar, XMFLOAT4& xmf4Vector) {

		XMFLOAT4 xmf4Result; XMStoreFloat4(&xmf4Result, fScalar * XMLoadFloat4(&xmf4Vector));

		return(xmf4Result);

	}
}

namespace Matrix4x4
{
	inline XMFLOAT4X4 Identity()
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixIdentity());
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 Translate(float x, float y, float z)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixTranslation(x, y, z));
		return(xmmtx4x4Result);
	}

	/* �� ����� ���ϰ� ����� ��ȯ�Ѵ�. */
	inline XMFLOAT4X4 Multiply(XMFLOAT4X4& xmmtx4x4Matrix1, XMFLOAT4X4& xmmtx4x4Matrix2)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMLoadFloat4x4(&xmmtx4x4Matrix1) * XMLoadFloat4x4(&xmmtx4x4Matrix2));
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 Multiply(XMFLOAT4X4& xmmtx4x4Matrix1, XMMATRIX& xmmtxMatrix2)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMLoadFloat4x4(&xmmtx4x4Matrix1) * xmmtxMatrix2);
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 Multiply(XMMATRIX& xmmtxMatrix1, XMFLOAT4X4& xmmtx4x4Matrix2)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, xmmtxMatrix1 * XMLoadFloat4x4(&xmmtx4x4Matrix2));
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 Multiply(XMMATRIX& xmmtxMatrix1, XMMATRIX& xmmtx4x4Matrix2)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, xmmtxMatrix1 * xmmtx4x4Matrix2);
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 RotationYawPitchRoll(float fPitch, float fYaw, float fRoll)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixRotationRollPitchYaw(XMConvertToRadians(fPitch), XMConvertToRadians(fYaw), XMConvertToRadians(fRoll)));
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 RotationAxis(XMFLOAT3& xmf3Axis, float fAngle)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixRotationAxis(XMLoadFloat3(&xmf3Axis), XMConvertToRadians(fAngle)));
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 Inverse(XMFLOAT4X4& xmmtx4x4Matrix)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixInverse(NULL, XMLoadFloat4x4(&xmmtx4x4Matrix)));
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 Transpose(XMFLOAT4X4& xmmtx4x4Matrix)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixTranspose(XMLoadFloat4x4(&xmmtx4x4Matrix)));
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 PerspectiveFovLH(float fFovAngleY, float fAspectRatio, float fNearZ, float fFarZ)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixPerspectiveFovLH(XMConvertToRadians(fFovAngleY), fAspectRatio, fNearZ, fFarZ));
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 LookAtLH(XMFLOAT3& xmf3EyePosition, XMFLOAT3& xmf3LookAtPosition, XMFLOAT3& xmf3UpDirection)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixLookAtLH(XMLoadFloat3(&xmf3EyePosition), XMLoadFloat3(&xmf3LookAtPosition), XMLoadFloat3(&xmf3UpDirection)));
		return(xmmtx4x4Result);
	}

	inline XMFLOAT4X4 LookToLH(XMFLOAT3& xmf3EyePosition, XMFLOAT3& xmf3LookTo, XMFLOAT3& xmf3UpDirection)
	{
		XMFLOAT4X4 xmmtx4x4Result;
		XMStoreFloat4x4(&xmmtx4x4Result, XMMatrixLookToLH(XMLoadFloat3(&xmf3EyePosition), XMLoadFloat3(&xmf3LookTo), XMLoadFloat3(&xmf3UpDirection)));
		return(xmmtx4x4Result);
	}
}

namespace Triangle
{
	inline bool Intersect(XMFLOAT3& xmf3RayPosition, XMFLOAT3& xmf3RayDirection, XMFLOAT3& v0, XMFLOAT3& v1, XMFLOAT3& v2, float& fHitDistance)
	{
		return(TriangleTests::Intersects(XMLoadFloat3(&xmf3RayPosition), XMLoadFloat3(&xmf3RayDirection), XMLoadFloat3(&v0), XMLoadFloat3(&v1), XMLoadFloat3(&v2), fHitDistance));
	}
}

namespace Plane
{
	inline XMFLOAT4 Normalize(XMFLOAT4& xmf4Plane)
	{
		XMFLOAT4 xmf4Result;
		XMStoreFloat4(&xmf4Result, XMPlaneNormalize(XMLoadFloat4(&xmf4Plane)));
		return(xmf4Result);
	}
}