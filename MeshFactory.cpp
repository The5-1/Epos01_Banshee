#include "MeshFactory.h"

using namespace bs;

namespace The5
{
	bs::HMesh MeshFactory::initCube()
	{
		/*
		// desc for the mesh data
		MESH_DESC meshDesc;
		meshDesc.numVertices = 8;
		meshDesc.numIndices = 36;

		// desc for per-vertex data
		SPtr<VertexDataDesc> vertexDesc = VertexDataDesc::create();
		vertexDesc->addVertElem(VET_FLOAT3, VES_POSITION);
		meshDesc.vertexDesc = vertexDesc;

		//create an empty mesh to put data in
		HMesh mesh = Mesh::create(meshDesc);
		SPtr<MeshData> meshData = MeshData::create(meshDesc.numVertices, meshDesc.numIndices, vertexDesc);

		
		Vector3 myVertexPositions[8];
		UINT32 index = 0;
		for (UINT32 x = -1; x <= 1; x+=2)
		{
			for (UINT32 y = -1; y <= 1; y += 2)
			{
				for (UINT32 z = -1; z <= 1; z += 2)
				{
					myVertexPositions[index] = Vector3(x, y, z);
					meshData->setVertexData(VES_POSITION, &myVertexPositions[index], sizeof(myVertexPositions));
					index++;
				}
			}
		}


		auto posIter = meshData->getVec3DataIter(VES_POSITION);
		Vector3 myPosition(0, 0, 0);
		do {
			myPosition.x += 1.0f;
			myPosition.y += 1.0f;
		} while (posIter.addValue(myPosition));

		mesh->writeData(meshData, false);
		*/

	}

}