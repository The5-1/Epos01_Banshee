#pragma once

#include "BsApplication.h"

#include "CoreThread/BsCoreThread.h"

#include "Resources/BsResources.h"
#include "Resources/BsBuiltinResources.h"

#include "Importer/BsImporter.h"
#include "Importer/BsTextureImportOptions.h"
#include "Importer/BsMeshImportOptions.h"

#include "Material/BsMaterial.h"
#include "Material/BsShader.h"

#include "Input/BsVirtualInput.h"

#include "Components/BsCCamera.h"
#include "Components/BsCRenderable.h"
#include "Components/BsCLight.h"
#include "Components/BsCSkybox.h"

#include "GUI/BsCGUIWidget.h"
#include "GUI/BsGUILayoutX.h"
#include "GUI/BsGUILayoutY.h"
#include "GUI/BsGUIPanel.h"
#include "GUI/BsGUISpace.h"
#include "GUI/BsGUILabel.h"
#include "GUI/BsGUIButton.h"
#include "GUI/BsGUIListBox.h"
#include "GUI/BsProfilerOverlay.h"

#include "Scene/BsSceneObject.h"

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

#include "Mesh/BsMeshData.h"

#include "Math/BsQuaternion.h"

#include "Utility/BsTime.h"
#include "Utility/BsTimer.h"

#include "Renderer/BsRendererUtility.h"

#include "BsEngineConfig.h"
