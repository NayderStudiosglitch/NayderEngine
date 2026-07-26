import json
import time

class NetworkPacket:
    @staticmethod
    def serialize_player_data(player_id, x, y, team, status):
        # Transfòme done jwè a an ti pakè JSON ki lejè pou vwayaje sou entènèt la
        packet = {
            "player_id": player_id,
            "team": team,
            "transform": {"x": round(x, 2), "y": round(y, 2)},
            "status": status,
            "timestamp": time.time()
        }
        return json.dumps(packet)

class NayderDedicatedServer:
    def __init__(self):
        print("\n=======================================================")
        print("     [NAYDER ENGINE v0.0.7] - MULTIPLAYER NETWORK CORE")
        print("=======================================================")
        self.tick_rate = 60  # 60Hz Tick Rate pwofesyonèl
        self.connected_players = 0
        self.team_alpha = 0
        self.team_beta = 0

    def broadcast_packet_to_squads(self, json_packet):
        # Simulation voye pakè a bay tout 100 jwè yo
        data = json.loads(json_packet)
        print(f" -> [SERVER BROADCAST - 60Hz]: Sinkwonize Jwè '{data['player_id']}'...")
        print(f"    [DATA]: Ekip: {data['team']} | Pozisyon: ({data['transform']['x']}, {data['transform']['y']}) | Aksyon: {data['status']}")
        return True

    def manage_50vs50_matchmaking(self, player_id, squad_type):
        self.connected_players += 1
        if squad_type == "ALPHA":
            self.team_alpha += 1
        else:
            self.team_beta += 1
            
        print(f" 📡 [MATCHMAKER]: Jwè '{player_id}' konekte nan Sèvè Dedye a.")
        print(f"    [STATUS]: Total Jwè: {self.connected_players}/100 | Squad Alpha: {self.team_alpha}/50 | Squad Beta: {self.team_beta}/50")
        
        if self.connected_players == 100:
            print("\n🚀 SERVER UPDATE: 100/100 PLAYERS CONNECTED! LAG-FREE MULTIPLAYER ACTIVE.")
            print("-------------------------------------------------------")

if __name__ == "__main__":
    # Demare simulation Sèvè Dedye a
    server = NayderDedicatedServer()
    print("-------------------------------------------------------")
    
    # 1. Simulation Matchmaking 50 vs 50 (Antre premye ak dènye sòlda yo)
    server.manage_50vs50_matchmaking("NAYDER_01", "ALPHA")
    server.manage_50vs50_matchmaking("SQUAD_MEMBER_02", "ALPHA")
    
    # Simulate ke 97 lòt jwè antre rapid...
    server.connected_players = 99
    server.team_alpha = 50
    server.team_beta = 49
    
    # 100tyèm jwè a antre pou deklanche lagè a
    server.manage_50vs50_matchmaking("ENEMY_PLAYER_50", "BETA")
    
    # 2. Tès kreyasyon ak voye pakè done sou rezo a
    sample_packet = NetworkPacket.serialize_player_data(
        player_id="NAYDER_01", 
        x=245.50, 
        y=110.25, 
        team="SQUAD_ALPHA", 
        status="FIRING_ZAM_LOW_RECOIL"
    )
    
    server.broadcast_packet_to_squads(sample_packet)
    print("=======================================================")
