import sys
import time

class PlayerController:
    def __init__(self, name, selected_class):
        self.name = name
        self.player_class = selected_class.upper()
        self.hp = 100
        self.shield = 100
        self.ammo_in_clip = 30
        self.total_reserve_ammo = 150
        
        # Konfigirasyon selon klas la
        if self.player_class == "SNIPER":
            self.ammo_in_clip = 5
            self.total_reserve_ammo = 35
        elif self.player_class == "TANK_DRIVER":
            self.hp = 250
            self.shield = 200

    def fire_weapon(self):
        if self.ammo_in_clip > 0:
            self.ammo_in_clip -= 1
            print(f" 🔫 [NEON FALL ALPHA]: '{self.name}' TIRE YON BAL! (Clip: {self.ammo_in_clip}/{self.total_reserve_ammo})")
            return True
        else:
            print(" 🚫 [WEAPON]: CLIP VID! Peze 'R' pou w Reload zam nan.")
            return False

    def reload_weapon(self):
        if self.total_reserve_ammo > 0:
            needed_ammo = 30 - self.ammo_in_clip if self.player_class != "SNIPER" else 5 - self.ammo_in_clip
            transfer = min(needed_ammo, self.total_reserve_ammo)
            self.ammo_in_clip += transfer
            self.total_reserve_ammo -= transfer
            print(f" 🔄 [WEAPON]: Reloading... Zam nan pare ankò! (Clip: {self.ammo_in_clip}/{self.total_reserve_ammo})")
        else:
            print(" ❌ [WEAPON]: Pa gen bal nan rezèv la ankò!")

class NeonFallAlphaGame:
    def __init__(self):
        print("\n=======================================================")
        print("    [PROJECT: NEON FALL] - ALPHA VERSION v0.1 RUNNING")
        print("=======================================================")
        print(" -> Powered by NAYDER ENGINE Runtime pipeline.")
        print(" -> Map Loaded: 'Desert Ghost City' (Alpha Grid).")
        print("-------------------------------------------------------")
        
    def start_game_simulation(self):
        # 1. Kreye Sòlda a ak klas li
        soldier = PlayerController(name="NAYDER_01", selected_class="Assault")
        print(f" -> [SPAWN]: Jwè '{soldier.name}' parèt sou kat la kòm {soldier.player_class}.")
        print(f"    [STATS]: Sante: {soldier.hp} HP | Pwoteksyon: {soldier.shield} SHIELD")
        print("-------------------------------------------------------")
        
        # 2. Tès simulation konba (Aksyon!)
        soldier.fire_weapon()
        soldier.fire_weapon()
        soldier.fire_weapon()
        
        # Simulation reload
        soldier.reload_weapon()
        print("-------------------------------------------------------")
        print(" ✅ STATUS: Neon Fall Alpha game logic tested successfully on core environment.")

if __name__ == "__main__":
    game_instance = NeonFallAlphaGame()
    game_instance.start_game_simulation()
    print("=======================================================")
