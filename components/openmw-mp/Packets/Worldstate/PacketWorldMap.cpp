#include <components/openmw-mp/NetworkMessages.hpp>
#include <components/openmw-mp/Log.hpp>
#include "PacketWorldMap.hpp"

using namespace std;
using namespace mwmp;

PacketWorldMap::PacketWorldMap(RakNet::RakPeerInterface *peer) : WorldstatePacket(peer)
{
    packetID = ID_WORLD_MAP;
}

void PacketWorldMap::Packet(RakNet::BitStream *bs, bool send)
{
    WorldstatePacket::Packet(bs, send);

    uint32_t changesCount;

    if (send)
        changesCount = static_cast<uint32_t>(worldstate->mapChanges.mapTiles.size());

    RW(changesCount, send);

    if (!send)
    {
        worldstate->mapChanges.mapTiles.clear();
        worldstate->mapChanges.mapTiles.resize(changesCount);
    }

    for (auto &&mapTile : worldstate->mapChanges.mapTiles)
    {
        RW(mapTile.x, send);
        RW(mapTile.y, send);

        uint32_t imageDataSize;

        if (send)
            imageDataSize = static_cast<uint32_t>(mapTile.imageData.size());

        RW(imageDataSize, send);

        if (imageDataSize > mwmp::maxImageDataSize)
        {
            LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Processed invalid ID_WORLD_MAP packet where tile %i, %i had an imageDataSize of %i",
                mapTile.x, mapTile.y, imageDataSize);
            LOG_APPEND(Log::LOG_ERROR, "- The packet was ignored after that point");
            return;
        }

        if (!send)
        {
            mapTile.imageData.clear();
            mapTile.imageData.resize(imageDataSize);
        }

        for (auto &&imageChar : mapTile.imageData)
        {
            RW(imageChar, send);
        }
    }
}
