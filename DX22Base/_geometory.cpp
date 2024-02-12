#include "Geometory.h"

void Geometory::MakeBox()
{
	// ���f�[�^�̍쐬
	Vertex vtx[] =
	{
		// -X��
		{ {-0.5f, 0.5f,  0.5f}, {0.0f, 0.0f} },
		{ {-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f} },
		{ {-0.5f,-0.5f,  0.5f}, {0.0f, 1.0f} },
		{ {-0.5f,-0.5f, -0.5f}, {1.0f, 1.0f} },

		// -Y��
		{ { 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f} },
		{ {-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f} },
		{ { 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} },
		{ {-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f} },

		// -Z��
		{ {-0.5f, 0.5f, -0.5f}, {0.0f, 0.0f} },
		{ { 0.5f, 0.5f, -0.5f}, {1.0f, 0.0f} },
		{ {-0.5f,-0.5f, -0.5f}, {0.0f, 1.0f} },
		{ { 0.5f,-0.5f, -0.5f}, {1.0f, 1.0f} },

		// X��
		{ { 0.5f, 0.5f, -0.5f}, {0.0f, 0.0f} },
		{ { 0.5f, 0.5f,  0.5f}, {1.0f, 0.0f} },
		{ { 0.5f,-0.5f, -0.5f}, {0.0f, 1.0f} },
		{ { 0.5f,-0.5f,  0.5f}, {1.0f, 1.0f} },

		// Y��
		{ {-0.5f, 0.5f,  0.5f}, {0.0f, 0.0f} },
		{ { 0.5f, 0.5f,  0.5f}, {1.0f, 0.0f} },
		{ {-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f} },
		{ { 0.5f, 0.5f, -0.5f}, {1.0f, 1.0f} },

		// Z��
		{ { 0.5f, 0.5f, 0.5f}, {0.0f, 0.0f} },
		{ {-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f} },
		{ { 0.5f,-0.5f, 0.5f}, {0.0f, 1.0f} },
		{ {-0.5f,-0.5f, 0.5f}, {1.0f, 1.0f} },
	};
	int idx[] = {
		 0,  1,  2,  1,  3,  2,	// -X��
		 4,  5,  6,  5,  7,  6,	// -Y��
		 8,  9, 10,  9, 11, 10,	// -Z��
		12, 13, 14, 13, 15, 14,	//  X��
		16, 17, 18, 17, 19, 18,	//  Y��
		20, 21, 22, 21, 23, 22,	//  Z��
	};
	// �o�b�t�@�̍쐬
	MeshBuffer::Description desc = {};
	desc.pVtx	  = vtx;
	desc.vtxCount = _countof(vtx);//sizeof(vtx) / sizeof(vtx[0]); �z��̃T�C�Y��Ԃ� //24;	// ���_�̐�
	desc.vtxSize  = sizeof(Vertex); // 20;	// ���_�������̃f�[�^�T�C�Y
	desc.pIdx	  = idx;
	desc.idxCount = _countof(idx);	// �C���f�b�N�X�̐�
	desc.idxSize  = sizeof(int); //4;	// �C���f�b�N�X�������̃f�[�^�T�C�Y
	desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_pBox = new MeshBuffer(desc);
}

void Geometory::MakeCylinder()
{
	//--- ���_�̍쐬
	// �V�ʁA���

	// ����

	//--- �C���f�b�N�X�̍쐬
	// �V�ʁA���

	// ����


	//--- �o�b�t�@�̍쐬
}

void Geometory::MakeSphere()
{
	//--- ���_�̍쐬

	//--- �C���f�b�N�X�̍쐬

	// �o�b�t�@�̍쐬
}