//
// Created by uralg on 15.02.2025.
//
#include <He/Core/World/Voxel.hpp>
#include <cstring>
namespace He::Core::World {
	std::size_t Voxel::_lastId = 0;
	Voxel::Voxel(const std::string &tag, const std::string textures[6]) {
		this->Tag = tag;
		for (int i = 0; i < 6; i++) {
			this->Textures[i] = textures[i];
		}
		this->Id = Voxel::_lastId++;
	}
}
