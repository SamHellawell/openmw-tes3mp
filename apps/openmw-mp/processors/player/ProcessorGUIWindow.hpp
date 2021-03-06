//
// Created by koncord on 23.11.17.
//

#pragma once

#include "../PlayerProcessor.hpp"

namespace mwmp
{

    class ProcessorGUIWindow final: public PlayerProcessor
    {
    public:
        ProcessorGUIWindow()
        {
            BPP_INIT(ID_GUI_WINDOW)
        }

        void Do(PlayerPacket &packet, const std::shared_ptr<Player> &player) override
        {
            DEBUG_PRINTF(strPacketID.c_str());

            player->getGUI().onGUIWindowAction();
        }
    };
}

