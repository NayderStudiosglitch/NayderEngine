#include "../Renderer/Renderer.cpp"
#include "../Renderer/OBJLoader.cpp"
#include "../Renderer/Texture.cpp"
#include "../Renderer/Material.cpp"
#include "../Renderer/Lighting.cpp"
#include "../Renderer/Shadows.cpp"
#include "../Renderer/Terrain.cpp"
#include "../Renderer/ParticleSystem.cpp"
#include "../Renderer/HUDRenderer.cpp"
#include "../Physics/Collision.cpp"
#include "../Animation/Animation.cpp"
#include "../Audio/Audio.cpp"
#include "../AI/NavMesh.cpp"
#include "../Network/Replication.cpp" // Linked modularly
#include "SaveLoadCore.cpp"
#include "Camera.cpp"
#include <iostream>
#include <cstring>

int main() {
    std::cout << "\n=======================================================" << std::endl;
    std::cout << "     [NAYDER ENGINE v0.0.82] - MULTIPLAYER REPLICATION" << std::endl;
    std::cout << "=======================================================" << std::endl;
    std::cout << " 🏆 NETWORK INTEGRATION LAYER UNLOCKED:" << std::endl;
    std::cout << "  v0.0.80 Animation Graph  -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.81 Navigation Mesh  -> \342\234\205 ONLINE" << std::endl;
    std::cout << "  v0.0.82 Multiplayer Sync -> \342\234\205 ONLINE PA OU" << std::endl;
    std::cout << "  v0.0.83 Editor Tools     -> \342\226\220 NEXT" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    NayderOpenGLRenderer renderer;
    NayderNetworkReplicator server_replicator;

    // 1. Simulate 10-Player Hardcore Clan Server Lobby entries
    server_replicator.RegisterClientNode("CLAN_BRO_02");
    server_replicator.RegisterClientNode("CLAN_MEMBER_03");
    server_replicator.RegisterClientNode("CLAN_TACTICAL_04");

    // 2. Mock a live runtime tracking packet coming straight from host player (NAYDER_01)
    PlayerNetworkPacket host_packet;
    std::strcpy(host_packet.player_id, "NAYDER_01");
    host_packet.pos_x = 14.5f;
    host_packet.pos_z = 2.0f;
    host_packet.current_hp = 85;
    host_packet.active_weapon_clip = 15; // Fired 15 rounds from the M4 clip
    host_packet.sequence_number = 1047;

    // 3. Trigger 60Hz server tick replication graph loop
    server_replicator.BroadcastServerTick(host_packet);
    server_replicator.CompressAndReplicateData();

    std::cout << "\n🎬 [SYSTEM REPLICATION]: Flushing network adapters and swapping frame buffers..." << std::endl;
    renderer.SwapFrameBuffers();

    std::cout << "=======================================================" << std::endl;
    return 0;
}
