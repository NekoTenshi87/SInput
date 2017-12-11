#pragma once

#include <SInput/SInput.hpp>

SInput::KEYBOARD::KEY GLFW_KeyConverter(int key, int scancode = 0);

SInput::KEYBOARD::ACTION GLFW_KeyActionConverter(int action);

int GLFW_ModConverter(int mods);

SInput::MOUSE::BUTTON GLFW_MouseConverter(int button);

SInput::MOUSE::ACTION GLFW_MouseActionConverter(int action);

SInput::GAMEPAD::STATUS GLFW_GamePadStatusConverter(int status);

SInput::GAMEPAD::BUTTON GLFW_GamePadButtonConverter(int button);

SInput::GAMEPAD::AXIS GLFW_GamePadAxisConverter(int axis);

SInput::GAMEPAD::ACTION GLFW_GamePadActionConverter(unsigned char action);