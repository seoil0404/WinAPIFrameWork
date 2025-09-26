#include "Scene.h"
#include "Main.h"
#include "Vector.h"
#include "Debug.h"

ID3D11Buffer* Scene::GetVertexBuffer()
{
	return vertexBuffer;
}

ID3D11Buffer* Scene::GetIndexBuffer()
{
    return indexBuffer;
}

TriangleScene::TriangleScene()
{
    Debug::Log("TriangleScene Initialized");

    Vector3 vertices[] =
    {
        { 0.0f,  0.5f, 0.0f },   // ��
        { 0.5f, -0.5f, 0.0f },   // ������ �Ʒ�
        {-0.5f, -0.5f, 0.0f }    // ���� �Ʒ�
    };

    unsigned int indices[] =
    {
        0, 1, 2
    };

    // ���ؽ� ����
    D3D11_BUFFER_DESC vbd = {};
    vbd.Usage = D3D11_USAGE_DEFAULT;
    vbd.ByteWidth = sizeof(vertices);
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vinitData = {};
    vinitData.pSysMem = vertices;

    g_device->CreateBuffer(&vbd, &vinitData, &vertexBuffer);

    // �ε��� ����
    D3D11_BUFFER_DESC ibd = {};
    ibd.Usage = D3D11_USAGE_DEFAULT;
    ibd.ByteWidth = sizeof(indices);
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA iinitData = {};
    iinitData.pSysMem = indices;
    
    g_device->CreateBuffer(&ibd, &iinitData, &indexBuffer);

}