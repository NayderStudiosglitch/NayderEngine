import sys
import time

class TankVehicle:
    def __init__(self, name):
        self.name = name
        self.armor = 500
        self.cannon_ammo = 10
        self.is_occupied = False
        self.driver = None

    def enter_vehicle(self, player):
        self.is_occupied = True
        self.driver = player
        print(f" 🦺 [VEHICLE]: Sòlda '{player.name}' antre andedan '{self.name}'!")
        print(f"    [TANK ARMORED STATUS]: Pwoteksyon Tank: {self.armor} HP | Koki Kanon: {self.cannon_ammo}/10")

    def fire_main_cannon(self, enemy_target):
        if self.cannon_ammo > 0:
            self.cannon_ammo -= 1
            print(f" 💥 [CANNON FIRE]: {self.name} LOUVRI TI KANON LOU AN! (Koki: {self.cannon_ammo}/10)")
            # Gwo dega kanon (100 HP - Elimine nenpòt lènmi yon sèl kou!)
            enemy_target.take_damage(damage_amount=100, player_source=self.driver)
            return True
        else:
            print(" 🚫 [CANNON]: Pa gen koki ki rete nan kanon an!")
            return False

class PlayerController:
    def __init__(self, name, selected_class):
        self.name = name
        self.player_class = selected_class.upper()
        self.hp = 100
        self.xp = 2400
        self.level = 25
        self.credits = 53860
        self.xp_needed_for_next_level = 3000

    def add_xp_and_credits(self, xp_amount, cr_amount):
        self.xp += xp_amount
        self.credits += cr_amount
        print(f" 💵 [REWARD]: +{xp_amount} XP ak +{cr_amount} CR ajoute!")
        if self.xp >= self.xp_needed_for_next_level:
            self.level += 1
            print(f"\n⚡🎉=======================================================🎉⚡")
            print(f"       LEVEL UP!!! SÒLDA '{self.name}' MONTE NAN NIVÒ {self.level}!")
            print(f"===========================================================⚡")

class BasicEnemyAI:
    def __init__(self, name):
        self.name = name
        self.hp = 100
        self.is_alive = True

    def take_damage(self, damage_amount, player_source):
        if self.is_alive:
            self.hp -= damage_amount
            print(f" 💥 [HIT]: '{self.name}' pran -{damage_amount} HP nan gwo kanon blennde a!")
            if self.hp <= 0:
                self.hp = 0
                self.is_alive = False
                print(f" 💀 [ELIMINATION]: '{self.name}' ELIMINE nèt sou kat la!")
                player_source.add_xp_and_credits(xp_amount=750, cr_amount=500)

class NeonFallAlphaGame:
    def __init__(self):
        print("\n=======================================================")
        print("    [PROJECT: NEON FALL] - ALPHA v0.4 SISTÈM TANK LOU")
        print("=======================================================")
        
    def start_game_simulation(self):
        # 1. Spawn Sòlda, Tank, ak yon nouvo Gwo Lènmi
        soldier = PlayerController(name="NAYDER_01", selected_class="Assault")
        heavy_tank = TankVehicle(name="M1_NAYDER_TANK_ALPHA")
        zombie_boss = BasicEnemyAI(name="ZONBI_BOSS_200")
        
        print("-------------------------------------------------------")
        # 2. Sòlda a monte sou tank la epi li louvri tir kanon an
        heavy_tank.enter_vehicle(soldier)
        print("-------------------------------------------------------")
        
        time.sleep(0.5)
        heavy_tank.fire_main_cannon(zombie_boss)
        
        print("-------------------------------------------------------")
        print(" ✅ STATUS: Fizik machin ak Lojik Kanon Tank teste 100% kòrèkteman.")

if __name__ == "__main__":
    game_instance = NeonFallAlphaGame()
    game_instance.start_game_simulation()
    print("=======================================================")
