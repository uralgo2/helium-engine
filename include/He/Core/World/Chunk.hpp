//
// Created by uralg on 15.02.2025.
//

#ifndef CHUNK_HPP
#define CHUNK_HPP
#include <cstddef>

#include <He/Core/World/Voxel.hpp>
#include <He/Core/World/World.hpp>

namespace He::Core::World {
	class Chunk {
	private:
		VoxelData* _voxels;
		friend class World;
	public:
		const int X, Y, Z;
		struct SizeT  {
			int X, Y, Z;
		} Size;
#define CHUNK_XYZ_TO_LINEAR(X, Y, Z, SX, SY, SZ) ((X * SY + Y) * SZ + Z)
		Chunk(int x, int y, int z, SizeT size);

		VoxelData& Voxel(int x, int y, int z);
		const VoxelData& Voxel(int x, int y, int z) const;
	};
}
#endif //CHUNK_HPP
