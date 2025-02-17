//
// Created by uralg on 15.02.2025.
//
#include <stdexcept>
#include <He/Core/World/Chunk.hpp>

namespace He::Core::World {
	Chunk::Chunk(int x, int y, int z, SizeT size): X(x), Y(y), Z(z), Size(size) {
		_voxels = new VoxelData[this->Size.X * this->Size.Y * this->Size.Z];
	}

	VoxelData &Chunk::Voxel(int x, int y, int z) {
		const std::size_t linear = CHUNK_XYZ_TO_LINEAR(x, y, z, Size.X, Size.Y, Size.Z);
#ifdef _DEBUG
		if (linear >= Size.X * Size.Y * Size.Z) {
			throw std::out_of_range("voxel X or Y or Z out of range");
		}
#endif
		return _voxels[linear];
	}
	const VoxelData &Chunk::Voxel(int x, int y, int z) const {
		const std::size_t linear = CHUNK_XYZ_TO_LINEAR(x, y, z, Size.X, Size.Y, Size.Z);
#ifdef _DEBUG
		if (linear >= Size.X * Size.Y * Size.Z) {
			throw std::out_of_range("voxel X or Y or Z out of range");
		}
#endif
		return _voxels[linear];
	}

}
