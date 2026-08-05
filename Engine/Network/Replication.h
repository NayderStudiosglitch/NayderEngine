#pragma once
#include <string>
#include <vector>

struct PlayerNetworkPacket {
    char player_id[16]; // Fixed char array instead of dynamic std::string for ultra-fast VRAM/RAM bit blitting
    float pos_x;
    float pos_z;
    int current_hp;
    int active_weapon_clip;
    unsigned int sequence_number; // Packet sequence tracker to handle packet drop/recovery loops
};

class NayderNetworkReplicator {
private:
    std::vector<PlayerNetworkPacket> client_connections;
    unsigned int server_tick_counter = 0;

public:
    NayderNetworkReplicator();
    void RegisterClientNode(const char* id);
    void BroadcastServerTick(const PlayerNetworkPacket& master_snapshot);
    void CompressAndReplicateData();
};
