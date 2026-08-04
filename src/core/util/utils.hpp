#pragma once
#include "common.hpp"
#include "types/script/types.hpp"
namespace YimMenu::Utils {
	void ApplyForceToEntity(Entity entity, float x, float y, float z, float offX, float offY, float offZ);
    void SetHeading(float heading);
	void StartScript(const char* script_name, int stack_size);
}
