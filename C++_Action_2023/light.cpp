
//================================================
//=
//= ���C�g�̏���[light.cpp]
//= Author Sakai Minato
//=
//================================================

//=======================================
//=	�C���N���[�h
//=======================================

#include "light.h"

#include "renderer.h"
#include "manager.h"

//-------------------------------------
//-	���C�g�̃R���X�g���N�^
//-------------------------------------
CLight::CLight()
{
	for (int nCount = 0; nCount < LIGHT_MAX; nCount++)
	{
		ZeroMemory(&m_light[nCount], sizeof(D3DLIGHT9));
	}
}

//-------------------------------------
//-	���C�g�̃f�X�g���N�^
//-------------------------------------
CLight::~CLight()
{
}


//-------------------------------------
//-	���C�g�̏���������
//-------------------------------------
HRESULT CLight::Init(void)
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�C�X�̏��擾�̐����𔻒�
	if (pDevice == NULL)
	{// ���s��

		// �����������𔲂���
		return E_FAIL;
	}

	// �ϐ��錾
	D3DXVECTOR3 vecDir[LIGHT_MAX];	// �ݒ�p�����x�N�g��

	for (int nCount = 0; nCount < LIGHT_MAX; nCount++)
	{
		// ���C�g�̎�ނ�ݒ�
		m_light[nCount].Type = D3DLIGHT_DIRECTIONAL;
		
		if (nCount == 0)
		{
			// ���C�g�̊g�U����ݒ�
			m_light[nCount].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// ���C�g�̕�����ݒ�
			vecDir[nCount] = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
		}
		else  if (nCount == 1)
		{
			//���C�g�̊g�U����ݒ�
			m_light[nCount].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);

			// ���C�g�̕�����ݒ�
			vecDir[nCount] = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
		}
		else if (nCount == 2)
		{
			// ���C�g�̊g�U����ݒ�
			m_light[nCount].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

			// ���C�g�̕�����ݒ�
			vecDir[nCount] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
		}

		// �x�N�g���𐳋K������i1.0f�j�ɂ���
		D3DXVec3Normalize(&vecDir[nCount], &vecDir[nCount]);
		m_light[nCount].Direction = vecDir[nCount];

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCount, &m_light[nCount]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCount, TRUE);

	}

	// ������Ԃ�
	return S_OK;
}

//-------------------------------------
//-	���C�g�̏I������
//-------------------------------------
void CLight::Uninit(void)
{
}

//-------------------------------------
//-	���C�g�̍X�V����
//-------------------------------------
void CLight::Update(void)
{

}

