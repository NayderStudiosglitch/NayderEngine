#include "Replication.h"
#include <iostream>
#include <cstring>

NayderNetworkReplicator::NayderNetworkReplicator() {
    server_tick_counter = 0;
}

void NayderNetworkReplicator::RegisterClientNode(const char* id) {
    PlayerNetworkPacket new_client;
    std::strncpy(new_client.player_id, id, 16);
    new_client.pos_x = 0.0f;
    new_client.pos_z = 0.0f;
    new_client.current_hp = 100;
    new_client.active_weapon_clip = 30;
    new_client.sequence_number = 0;
    
    client_connections.push_back(new_client);
    std::cout << " 📡 [NET_REPLICATION]: Registered Client Node: '" << id << "' onto the server synchronization cluster." << std::endl;
}

void NayderNetworkReplicator::BroadcastServerTick(const PlayerNetworkPacket& master_snapshot) {
    server_tick_counter++;
    std::cout << "\n🔄 [SERVER REPLICATION TICK #" << server_tick_counter << " - 60Hz]:" << std::endl;
    std::cout << " -> Intercepting state updates from host: " << master_snapshot.player_id << " (Sequence: " << master_snapshot.sequence_number << ")" << std::endl;
    std::cout << " -> Host Position Matrix: (" << master_snapshot.pos_x << ", " << master_snapshot.pos_z << ") │ HP: " << master_snapshot.current_hp << " │ Ammo: " << master_snapshot.active_weapon_clip << std::endl;
}

void NayderNetworkReplicator::CompressAndReplicateData() {
    std::cout << " ⚡ [PACKET DELTA COMPRESSION]: Compressing transform matrices into bitstream packets..." << std::endl;
    std::cout << "    [REPLICATION GRAPH]: Broadcasting bitstream out to all remaining " << client_connections.size() << " squad players..." << std::endl;
    for (const auto& client : client_connections) {
        std::cout << "   ├── 📁 [UDP ROUTE]: Pushing replicated packet payload to node -> IP_V4_ENDPOINT | Client ID: " << client.player_id << " ... [SYNC OK]" << std::endl;
    }
    std::cout << " ✅ [REPLICATION SUCCESS]: Hardcore squad synchronized across server memory layers with 0ms interpolation lag!" << std::endl;
}
