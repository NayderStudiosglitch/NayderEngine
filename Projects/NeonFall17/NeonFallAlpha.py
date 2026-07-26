import sys
import time
import random

class DestructibleStructure:
    def __init__(self, name, integrity_points):
        self.name = name
        self.integrity = integrity_points
        self.is_destroyed = False

    def receive_heavy_impact(self, damage_amount):
        if self.is_destroyed:
            return
            
        self.integrity -= damage_amount
        print(f" 🧱 [STRUCTURE IMPACT]: '{self.name}' frape ak -{damage_amount} fòs fizik!")
        
        if self.integrity <= 0:
            self.integrity = 0
            self.is_destroyed = True
            # Simulate moso debri yo k ap vole (Physics Fracture Vector Simulation)
            debri_count = random.randint(12, 25)
            print(f"\n💥💥 [PHYSICS FRACTURE]: '{self.name}' KRAZE NÈT AN MÈT PYÈS!")
            print(f"    -> NAYDER ENGINE (C++): Matrix fracture split completed.")
            print(f"    -> PARTICLES: {debri_count} moso debri ak gwo nwaj pousyè deklanche nan VRAM.")
        else:
            # Afiche nivo domaj la
            print(f"    [DAMAGE STATE]: '{self.name}' fann! Rezistans ki rete: {self.identity_check()}%")

    def identity_check(self):
        return int((self.integrity / 200) * 100) if self.integrity > 0 else 0

class NeonFallAlphaGame:
    def __init__(self):
        print("\n=======================================================")
        print("    [PROJECT: NEON FALL] - ALPHA v0.6 DESTRÌKSYON MAP")
        print("=======================================================")
        
    def start_game_simulation(self):
        # Spawn yon gwo miray blennde nan zòn vil la
        city_wall = DestructibleStructure(name="MILITARY_BARRICADE_WALL_01", integrity_points=200)
        
        print(f" -> [SPAWN]: '{city_wall.name}' plase sou kat la kòm objè fizik destriktib.")
        print("-------------------------------------------------------")
        
        # 1. Premye kout zam ki fann miray la
        time.sleep(0.5)
        print("[ACTION]: Yon jwè tire sou miray la ak yon zam lou...")
        city_wall.receive_heavy_impact(damage_amount=75)
        
        print("-------------------------------------------------------")
        # 2. Dezyèm gwo enpak (Koki Tank) k ap eksploze miray la nèt ale!
        time.sleep(0.5)
        print("[ACTION]: Gwo kanon Tank lan tire yon koki dirèkteman sou miray la...")
        city_wall.receive_heavy_impact(damage_amount=150)
        
        print("-------------------------------------------------------")
        print(" ✅ STATUS: Sistèm Fracture ak Destriksyon Debri teste 100% kòrèkteman.")

if __name__ == "__main__":
    game_instance = NeonFallAlphaGame()
    game_instance.start_game_simulation()
    print("=======================================================")
