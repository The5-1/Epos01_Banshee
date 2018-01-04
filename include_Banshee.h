#pragma once

#include "BsPrerequisites.h"

#include "BsApplication.h"
#include "CoreThread/BsCoreThread.h"

#include "Resources/BsResources.h"
#include "Resources/BsBuiltinResources.h"
#include "Resources/BsBuiltinResourcesHelper.h"

#include "Debug/BsLog.h"
#include "Debug/BsDebug.h"
#include "Debug/BsDebugDraw.h"
#include "Debug/BsBitmapWriter.h"

#include "Math/BsMath.h"
#include "Math/BsVector3.h"
#include "Math/BsQuaternion.h"

#include "Scene/BsSceneObject.h"
#include "Scene/BsSceneManager.h"
#include "Scene/BsComponent.h"

#include "Renderer/BsRenderer.h"
#include "Renderer/BsRenderSettings.h"
#include "Renderer/BsRendererUtility.h"
#include "Renderer/BsRendererManager.h"
#include "Renderer/BsRendererFactory.h"

#include "RenderAPI/BsRenderAPI.h"
#include "RenderAPI/BsRenderWindow.h"
#include "RenderAPI/BsCommandBuffer.h"
#include "RenderAPI/BsGpuProgram.h"
#include "RenderAPI/BsGpuPipelineState.h"
#include "RenderAPI/BsBlendState.h"
#include "RenderAPI/BsDepthStencilState.h"
#include "RenderAPI/BsGpuParamBlockBuffer.h"
#include "RenderAPI/BsIndexBuffer.h"
#include "RenderAPI/BsVertexDataDesc.h"

#include "Mesh/BsMesh.h"
#include "Mesh/BsMeshBase.h"
#include "Mesh/BsMeshData.h"
#include "Mesh/BsMeshUtility.h"

#include "Importer/BsImporter.h"
#include "Importer/BsTextureImportOptions.h"
#include "Importer/BsMeshImportOptions.h"

#include "Material/BsMaterial.h"
#include "Material/BsShader.h"

#include "Input/BsVirtualInput.h"

#include "Platform/BsCursor.h"

#include "GUI/BsCGUIWidget.h"
#include "GUI/BsGUILayoutX.h"
#include "GUI/BsGUILayoutY.h"
#include "GUI/BsGUIPanel.h"
#include "GUI/BsGUISpace.h"
#include "GUI/BsGUILabel.h"
#include "GUI/BsGUIButton.h"
#include "GUI/BsGUIListBox.h"
#include "GUI/BsProfilerOverlay.h"

#include "Utility/BsTime.h"
#include "Utility/BsTimer.h"
#include "Utility/BsDrawHelper.h"

#include "Animation/BsAnimation.h"
#include "Components/BsCAnimation.h"
#include "Components/BsCBone.h"
#include "Animation/BsSkeleton.h"

#include "Physics/BsPhysicsCommon.h"
#include "Physics/BsRigidbody.h"
#include "Components/BsCRigidbody.h"
#include "Physics/BsCharacterController.h"
#include "Components/BsCCharacterController.h"
#include "Physics/BsCollider.h"
#include "Components/BsCCollider.h"
#include "Physics/BsJoint.h"
#include "Components/BsCJoint.h"
#include "Physics/BsBoxCollider.h"
#include "Components/BsCBoxCollider.h"
#include "Physics/BsPlaneCollider.h"
#include "Components/BsCPlaneCollider.h"
#include "Physics/BsSphereCollider.h"
#include "Components/BsCSphereCollider.h"
#include "Physics/BsCapsuleCollider.h"
#include "Components/BsCCapsuleCollider.h"

#include "Components/BsCCamera.h"
#include "Components/BsCRenderable.h"
#include "Components/BsCLight.h"
#include "Components/BsCSkybox.h"


#include "BsEngineConfig.h"

