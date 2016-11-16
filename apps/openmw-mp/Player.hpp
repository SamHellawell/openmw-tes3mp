//
// Created by koncord on 05.01.16.
//

#ifndef OPENMW_PLAYER_HPP
#define OPENMW_PLAYER_HPP

#include <map>
#include <string>
#include <chrono>
#include <RakNetTypes.h>

#include <components/esm/npcstats.hpp>
#include <components/esm/cellid.hpp>
#include <components/esm/loadnpc.hpp>
#include <components/esm/loadcell.hpp>

#include <components/openmw-mp/Log.hpp>
#include <components/openmw-mp/Base/BasePlayer.hpp>

struct Player;
typedef std::map<uint64_t, Player*> TPlayers;
typedef std::map<unsigned short, Player*> TSlots;

class Players
{
public:
    static void newPlayer(RakNet::RakNetGUID guid);
    static void deletePlayer(RakNet::RakNetGUID guid);
    static Player *getPlayer(RakNet::RakNetGUID guid);
    static Player *getPlayer(unsigned short id);
    static TPlayers *getPlayers();

private:
    static TPlayers players;
    static TSlots slots;
};

class Player : public mwmp::BasePlayer
{
    unsigned short id;
public:

    enum
    {
        NOTLOADED=0,
        LOADED,
        POSTLOADED
    };
    Player(RakNet::RakNetGUID guid);

    unsigned short getId();
    void setId(unsigned short id);

    bool isHandshaked();
    void setHandshake();

    void setLoadState(int state);
    int getLoadState();

    void setLastAttackerId(unsigned short pid);
    void resetLastAttacker();
    unsigned short getLastAttackerId();

    void setLastAttackerTime(std::chrono::steady_clock::time_point time);
    std::chrono::steady_clock::time_point getLastAttackerTime();

    virtual ~Player();
public:
    mwmp::Inventory inventorySendBuffer;
private:
    bool handshakeState;
    int loadState;
    unsigned short lastAttacker;
    std::chrono::steady_clock::time_point lastAttackerTime;

};

#endif //OPENMW_PLAYER_HPP
