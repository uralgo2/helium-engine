//
// Created by uralg on 14.02.2025.
//
#include <He/Graphics/GL/Mesh.hpp>

namespace He::Graphics::GL {
	Mesh::Mesh() : _vertices(0), _normals(0), _uvs(0), _indices(0) {}

	Mesh::Mesh(const Utils::Array<glm::vec3>& vertices, const Utils::Array<glm::vec3>& normals, const Utils::Array<glm::vec2>& uvs,
		const Utils::Array<unsigned int>& indices) : _vertices(vertices),
	_normals(normals),
	_uvs(uvs),
	_indices(indices){
	}

	Mesh::~Mesh() = default;

	Utils::Array<glm::vec3> & Mesh::Vertices() {
		return _vertices;
	}

	Utils::Array<glm::vec3> & Mesh::Normals() {
		return _normals;
	}

	Utils::Array<glm::vec2> & Mesh::UVs() {
		return _uvs;
	}

	Utils::Array<unsigned int> & Mesh::Indices() {
		return _indices;
	}

	void Mesh::SetVertices(const Utils::Array<glm::vec3>& vertices) {
		_vertices = Utils::Array(vertices);
	}

	void Mesh::SetNormals(const Utils::Array<glm::vec3>& normals) {
		_normals = Utils::Array(normals);
	}

	void Mesh::SetUVs(const Utils::Array<glm::vec2>& uvs) {
		_uvs = Utils::Array(uvs);
	}

	void Mesh::SetIndices(const Utils::Array<unsigned int>& indices) {
		_indices = Utils::Array(indices);
	}

	void Mesh::Setup() {
		if (_vertices.size() != _uvs.size() || _vertices.size() != _normals.size()) {
			throw std::runtime_error("Mesh::Setup: Vertices and Normals or UVs have different sizes");
		}

		Utils::Array<Vertex> vertices(_vertices.size());

		for (std::size_t i = 0; i < _vertices.size(); i++) {
			vertices[i].Position = _vertices[i];
			vertices[i].Normal = _normals[i];
			vertices[i].UV = _uvs[i];
		}

		_vbo.SetData(vertices.size() * sizeof(Vertex), vertices.raw_ptr(), GL_DYNAMIC_DRAW);
		_ebo.SetData(_indices.size() * sizeof(unsigned int), _indices.raw_ptr(), GL_DYNAMIC_DRAW);

		_vao.BindVertexBuffer(_vbo, 0, 0, sizeof(Vertex));
		_vao.BindElementBuffer(_ebo);

		_vao.AttribFormat(0, 3, GL_FLOAT, false, offsetof(Vertex, Position));
		_vao.AttribFormat(1, 3, GL_FLOAT, false, offsetof(Vertex, Normal));
		_vao.AttribFormat(2, 2, GL_FLOAT, true, offsetof(Vertex, UV));

		_vao.AttribBinding(0, 0);
		_vao.AttribBinding(1, 0);
		_vao.AttribBinding(2, 0);

		_vao.EnableAttrib(0);
		_vao.EnableAttrib(1);
		_vao.EnableAttrib(2);
	}

	void Mesh::Draw() {
		_vao.Bind();
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_indices.size()), GL_UNSIGNED_INT, nullptr);
	}
}
