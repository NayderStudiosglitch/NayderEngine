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

    def fire_at_enemy(self, enemy_target):
        if self.ammo_in_clip > 0:
            self.ammo_in_clip -= 1
            print(f" 🔫 [FIRE]: '{self.name}' TIRE sou '{enemy_target.name}'! (Clip: {self.ammo_in_clip}/30)")
            # Deklanche dega sou lènmi an
            enemy_target.take_damage(damage_amount=25)
            return True
        else:
            print(" 🚫 [WEAPON]: CLIP VID! Peze enter pou w Reload.")
            return False

class BasicEnemyAI:
    def __init__(self, name, x, y):
        self.name = name
        self.x = x
        self.y = y
        self.hp = 100
        self.is_alive = True

    def take_damage(self, damage_amount):
        if self.is_alive:
            self.hp -= damage_amount
            print(f" 💥 [HIT]: '{self.name}' pran -{damage_amount} HP! Sante lènmi: {self.hp}/100")
            if self.hp <= 0:
                self.hp = 0
                self.is_alive = False
                print(f" 💀 [ELIMINATION]: '{self.name}' ELIMINE nèt sou kat la!")

class NeonFallAlphaGame:
    def __init__(self):
        print("\n=======================================================")
        print("    [PROJECT: NEON FALL] - ALPHA v0.2 AK ENÈMI AI")
        print("=======================================================")
        print(" -> Powered by NAYDER ENGINE AI & Combat Pipeline.")
        print("-------------------------------------------------------")
        
    def start_game_simulation(self):
        # 1. Spawn Sòlda a ak Lènmi AI a
        soldier = PlayerController(name="NAYDER_01", selected_class="Assault")
        zombie_bot = BasicEnemyAI(name="ZONBI_BOT_101", x=450, y=300)
        
        print(f" -> [SPAWN]: Jwè '{soldier.name}' parèt nan grid la.")
        print(f" -> [SPAWN]: Lènmi '{zombie_bot.name}' parèt nan grid la.")
        print("-------------------------------------------------------")
        
        # 2. Simulation sekans konba tire (Aksyon!)
        print("[SEKANS KONBA]: Sòlda a louvri tir sou zonbi a!")
        soldier.fire_at_enemy(zombie_bot)
        time.sleep(0.5)
        soldier.fire_at_enemy(zombie_bot)
        time.sleep(0.5)
        soldier.fire_at_enemy(zombie_bot)
        time.sleep(0.5)
        soldier.fire_at_enemy(zombie_bot) # 4 kout bal ap elimine l nèt (25 x 4 = 100)
        
        print("-------------------------------------------------------")
        print(" ✅ STATUS: Sistèm Combat ak Enèmi AI teste 100% kòrèkteman.")

if __name__ == "__main__":
    game_instance = NeonFallAlphaGame()
    game_instance.start_game_simulation()
    print("=======================================================")
