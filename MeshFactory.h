#pragma once

#include "ForwardDeclarations.h"
#include "include_STL.h"
#include "include_Banshee.h"

namespace The5 {

	/** documentation */
	class MeshFactory
	{
	public:

		///public Fields
		/** name */
		std::string name;
		/** documentation */

		///Constructor / Destructor
		/** Constructor */
		MeshFactory();
		/** Destructor */
		~MeshFactory() = default;

		///Getters / Setters
		/** documentation */

		///Methods
		/** documentation */
		bs::HMesh initCube();

	protected:
		///friend classes
		/** documentation */

		///private Constructor
		/** documentation */

		///private Fields
		/** documentation */
		static bs::HMesh cube;

		///private Methods
		/** documentation */

	};
}