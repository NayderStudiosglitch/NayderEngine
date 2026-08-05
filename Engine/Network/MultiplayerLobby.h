#pragma once
#include <string>
#include <vector>

enum class TeamTeam { SQUAD_ALPHA, SQUAD_BRAVO, UNASSIGNED };
enum class ConnectionState { CONNECTING, IN_LOBBY, IN_MATCH, SPECTATING_DEAD };

struct ConnectedPlayerNode {
    int client_network_id;
    char username[16];
    TeamTeam tactical_team;
    ConnectionState net_state;
    float respawn_timer;
};

class NayderMultiplayerLobby {
private:
    std::vector<ConnectedPlayerNode> active_lobby_clients;
    int client_id_generator = 100;
    int max_lobby_capacity = 10;

public:
    NayderMultiplayerLobby();
    int ProcessClientJoinRequest(const char* name);
    void AssignPlayerToTacticalTeam(int client_id, TeamTeam team_choice);
    void ProcessRespawnTimerTicks(ConnectedPlayerNode& dead_player, float delta_time, float& out_player_x);
    std::vector<ConnectedPlayerNode>& GetLobbyClientsPool();
};
