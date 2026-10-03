#include "CutscenesStarter.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/backend/FiberPool.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/gta/data/CutsceneNames.hpp"
#include "game/gta/Natives.hpp"
#include "core/localization/Translator.hpp"

namespace YimMenu::Submenus
{
    std::shared_ptr<Category> BuildCutscenesStarterMenu()
    {
        auto menu = std::make_shared<Category>(TR("Cutscenes"));
        auto cutsceneGroup = std::make_shared<Group>(TR("All Cutscenes"));

        cutsceneGroup->AddItem(std::make_unique<ImGuiItem>([]
        {
            static char cutSearch[64] = "";
            static std::string cutLower;

            ImGui::InputTextWithHint("##CutsceneSearch", TR("Search cutscenes"), cutSearch, sizeof(cutSearch));

            cutLower = cutSearch;
            std::transform(cutLower.begin(), cutLower.end(), cutLower.begin(), ::tolower);

            ImGui::Separator();
            ImGui::BeginChild("CutsceneList", ImVec2(0, 400), true);

            for (const auto& cs : cutsceneNames)
            {
                if (!cutLower.empty())
                {
                    std::string lower = cs;
                    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

                    if (lower.find(cutLower) == std::string::npos)
                        continue;
                }

                if (ImGui::Selectable(cs))
                {
                    FiberPool::Push([cs]
                    {
                        if (!CUTSCENE::IS_CUTSCENE_ACTIVE())
                        {
                            CUTSCENE::REQUEST_CUTSCENE(cs, 8);

                            while (!CUTSCENE::HAS_CUTSCENE_LOADED())
                                ScriptMgr::Yield();

                            CUTSCENE::START_CUTSCENE(0);
                        }
                    });
                }
            }

            ImGui::EndChild();

            if (ImGui::Button(TR("Stop Cutscene")))
            {
                FiberPool::Push([]()
                {
                    if (CUTSCENE::IS_CUTSCENE_ACTIVE())
                        CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
                });
            }
        }));

        menu->AddItem(std::move(cutsceneGroup));
        return menu;
    }
}
