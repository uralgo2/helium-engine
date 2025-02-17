//
// Created by uralg on 15.02.2025.
//

#ifndef VOXEL_HPP
#define VOXEL_HPP

#include <He/Core/World/Direction.hpp>
#include <cstddef>
#include <string>
namespace He::Core::World {
	struct VoxelData {
		int BlockId;
		int UserData;
	};
	class Voxel {
	private:
		static std::size_t _lastId;
	public:
		virtual ~Voxel() = default;

		std::string Tag;
		std::string Name;
		std::string Description;
		std::string Textures[6];

		int Id;
		struct {
			bool IsSolid:1;
		} Flags;

		Voxel(const std::string& tag, const std::string textures[6]);
		virtual const std::string& GetTexture(Direction direction, VoxelData voxel) {
			return this->Textures[static_cast<int>(direction)];
		};
	};
}
#endif //VOXEL_HPP
