#include "MultiplayerLobby.h"
#include <iostream>
#include <cstring>

NayderMultiplayerLobby::NayderMultiplayerLobby() {
    active_lobby_clients.clear();
}

int NayderMultiplayerLobby::ProcessClientJoinRequest(const char* name) {
    if (active_lobby_clients.size() >= static_cast<size_t>(max_lobby_capacity)) {
        std::cout << " 🚫 [LOBBY REJECT]: Server full! Session lobby cap reached (" << max_lobby_capacity << " players max)." << std::endl;
        return -1;
    }

    ConnectedPlayerNode new_client;
    new_client.client_network_id = ++client_id_generator;
    std::strncpy(new_client.username, name, 16);
    new_client.tactical_team = TeamTeam::UNASSIGNED;
    new_client.net_state = ConnectionState::IN_LOBBY;
    new_client.respawn_timer = 0.0f;

    active_lobby_clients.push_back(new_client);
    std::cout << " 📡 [SERVER LOBBY]: Incoming handshake check passed! Client '" << name 
              << "' connected successfully. Allocated Network Network ID: #" << new_client.client_network_id << std::endl;
    return new_client.client_network_id;
}

void NayderMultiplayerLobby::AssignPlayerToTacticalTeam(int client_id, TeamTeam team_choice) {
    for (auto& client : active_lobby_clients) {
        if (client.client_network_id == client_id) {
            client.tactical_team = team_choice;
            std::string team_name = (team_choice == TeamTeam::SQUAD_ALPHA) ? "SQUAD_ALPHA (Haitian Special Forces)" : "SQUAD_BRAVO";
            std::cout << " 🛡️  [TEAM REPLICATION]: Player '" << client.username << "' sorted into: [" << team_name << "]" << std::endl;
            return;
        }
    }
}

void NayderMultiplayerLobby::ProcessRespawnTimerTicks(ConnectedPlayerNode& dead_player, float delta_time, float& out_player_x) {
    if (dead_player.net_state != ConnectionState::SPECTATING_DEAD) return;

    dead_player.respawn_timer -= delta_time;
    std::cout << " ⏳ [RESPAWN CLOCK]: Synchronizing revival packet for " << dead_player.username 
              << "... Remaining Cooldown: " << dead_player.respawn_timer << "s" << std::endl;

    if (dead_player.respawn_timer <= 0.0f) {
        dead_player.respawn_timer = 0.0f;
        dead_player.net_state = ConnectionState::IN_MATCH;
        out_player_x = 0.0f; // Reset coordinate tracking vectors back to spawn drop node parameters
        std::cout << " 🎉 [RESPAWN CORE EXECUTION]: Player '" << dead_player.username 
                  << "' materialized completely back at deployment nodes! State synchronized." << std::endl;
    }
}

std::vector<ConnectedPlayerNode>& NayderMultiplayerLobby::GetLobbyClientsPool() {
    return active_lobby_clients;
}
