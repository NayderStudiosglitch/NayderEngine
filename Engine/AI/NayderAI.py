class ZombieAIController:
    def __init__(self, zombie_id):
        self.zombie_id = zombie_id
        self.state = "PATROL"  # Eta de baz: ap mache chèche moun
        self.speed = 2.0
        print(f" -> [AI SYSTEM]: Sèvo Zonbi_{zombie_id} inisyalize. Eta: '{self.state}'")

    def update_behavior_matrix(self, distance_to_player):
        # Lojik FSM (Finite State Machine) Next-Gen
        print(f"\n -> [AI UPDATE]: Evalye distans ak Sòlda a: {distance_to_player}m...")
        
        # 1. Si sòlda a lwen (Plis pase 50 mèt)
        if distance_to_player > 50:
            self.state = "PATROL"
            self.speed = 2.0
            print(f"    [AI STATE]: Sòlda a twò lwen. Zonbi an retounen nan: '{self.state}' (Vitès: {self.speed})")
            
        # 2. Si sòlda a toupre (Ant 5 ak 50 mèt)
        elif 5 <= distance_to_player <= 50:
            self.state = "CHASE"
            self.speed = 5.5
            print(f" ⚠️  [AI STATE]: Kontak vizyèl detekte! Chanje nan: '{self.state}' (Zonbi a ap KOURI! Vitès: {self.speed})")
            
        # 3. Si l kole nèt sou sòlda a (Mwens pase 5 mèt)
        else:
            self.state = "ATTACK"
            self.speed = 0.0
            print(f" 💥 [AI STATE]: Lènmi an kole nèt! Chanje nan: '{self.state}' (Zonbi a ap GRAPE sòlda a!)")
            
        return self.state

if __name__ == "__main__":
    print("\n=======================================================")
    print("           [NAYDER ENGINE v0.0.6] - AI SYSTEM CORE")
    print("=======================================================")
    
    # Kreye yon robo zonbi tès
    zombie_brain = ZombieAIController(zombie_id=101)
    print("-------------------------------------------------------")
    
    # Tès Simulation 1: Sòlda a lwen nan mòn yo
    zombie_brain.update_behavior_matrix(distance_to_player=120)
    print("-------------------------------------------------------")
    
    # Tès Simulation 2: Sòlda a ap pwoche nan zòn vil Ruins lan
    zombie_brain.update_behavior_matrix(distance_to_player=30)
    print("-------------------------------------------------------")
    
    # Tès Simulation 3: Kontak kò a kò (Collision detekte)
    zombie_brain.update_behavior_matrix(distance_to_player=2)
    print("=======================================================")
