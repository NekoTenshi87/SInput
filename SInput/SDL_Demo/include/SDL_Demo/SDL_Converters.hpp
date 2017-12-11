#pragma once

#include <SInput/SInput.hpp>

SInput::KEYBOARD::KEY SDL_KeyConverter(int key, int scancode = 0);

SInput::KEYBOARD::ACTION SDL_KeyActionConverter(int action);

int SDL_ModConverter(int mods);

SInput::MOUSE::BUTTON SDL_MouseConverter(int button);

SInput::MOUSE::ACTION SDL_MouseActionConverter(int action);

SInput::GAMEPAD::STATUS SDL_GamePadStatusConverter(int status);

SInput::GAMEPAD::BUTTON SDL_GamePadButtonConverter(int button);

SInput::GAMEPAD::AXIS SDL_GamePadAxisConverter(int axis);

SInput::GAMEPAD::ACTION SDL_GamePadActionConverter(int action);