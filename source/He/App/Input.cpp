//
// Created by uralg on 16.02.2025.
//
#include <He/App/Input.hpp>

namespace He::App::Input {
	const char * GetKeyName(Keys key) {
		switch (key) {
			case Keys::A: return "A";
			case Keys::S: return "S";
			case Keys::D: return "D";
			case Keys::W: return "W";
			case Keys::C: return "C";
			case Keys::P: return "P";
			case Keys::Space: return "Space";
			case Keys::Unknown: return "Unknown";
			case Keys::LeftShift: return "LeftShift";
			case Keys::Escape: return "Escape";
		}
	}

	Keys GLFW3KeyMap(int key) {
		switch (key) {
			case GLFW_KEY_A: return Keys::A;
			case GLFW_KEY_S: return Keys::S;
			case GLFW_KEY_D: return Keys::D;
			case GLFW_KEY_W: return Keys::W;
			case GLFW_KEY_C: return Keys::C;
			case GLFW_KEY_P: return Keys::P;
			case GLFW_KEY_SPACE: return Keys::Space;
			case GLFW_KEY_LEFT_SHIFT: return Keys::LeftShift;
			case GLFW_KEY_ESCAPE: return Keys::Escape;
			default: return Keys::Unknown;
		}
	}
}
