import sys
import time

class PlayerController:
    def __init__(self, name, selected_class):
        self.name = name
        self.player_class = selected_class.upper()
        self.hp = 100
        self.shield = 100
        self.ammo_in_clip = 30
        
        # Pwofil ak Rekonpans (Estatistik ki soti nan Meni an)
        self.level = 25
        self.xp = 2400
        self.xp_needed_for_next_level = 3000
        self.credits = 53860

    def fire_at_enemy(self, enemy_target):
        if self.ammo_in_clip > 0:
            self.ammo_in_clip -= 1
            print(f" 🔫 [FIRE]: '{self.name}' TIRE sou '{enemy_target.name}'! (Clip: {self.ammo_in_clip}/30)")
            enemy_target.take_damage(damage_amount=25, player_source=self)
            return True
        else:
            print(" 🚫 [WEAPON]: CLIP VID!")
            return False

    def add_xp_and_credits(self, xp_amount, cr_amount):
        self.xp += xp_amount
        self.credits += cr_amount
        print(f" 💵 [REWARD]: +{xp_amount} XP ak +{cr_amount} CR ajoute nan kont ou!")
        
        # Lojik pou Monte Nivo (Level Up Matrix)
        if self.xp >= self.xp_needed_for_next_level:
            self.level += 1
            self.xp = self.xp - self.xp_needed_for_next_level
            print(f"\n⚡🎉=======================================================🎉⚡")
            print(f"       LEVEL UP!!! SÒLDA '{self.name}' MONTE NAN NIVÒ {self.level}!")
            print(f"===========================================================⚡")
        else:
            print(f"    [PROGRESS]: XP Pwofil: {self.xp}/{self.xp_needed_for_next_level} pou pwochen nivo.")

class BasicEnemyAI:
    def __init__(self, name):
        self.name = name
        self.hp = 100
        self.is_alive = True

    def take_damage(self, damage_amount, player_source):
        if self.is_alive:
            self.hp -= damage_amount
            print(f" 💥 [HIT]: '{self.name}' pran -{damage_amount} HP! Sante lènmi: {self.hp}/100")
            if self.hp <= 0:
                self.hp = 0
                self.is_alive = False
                print(f" 💀 [ELIMINATION]: '{self.name}' ELIMINE nèt!")
                # Bay jwè a pwen rekonpans (350 XP ak 500 Credits pou gwo eliminasyon)
                player_source.add_xp_and_credits(xp_amount=750, cr_amount=500)

class NeonFallAlphaGame:
    def __init__(self):
        print("\n=======================================================")
        print("    [PROJECT: NEON FALL] - ALPHA v0.3 REKONPANS AK XP")
        print("=======================================================")
        
    def start_game_simulation(self):
        soldier = PlayerController(name="NAYDER_01", selected_class="Assault")
        zombie_bot = BasicEnemyAI(name="ZONBI_BOT_102")
        
        print(f" -> [PROFILE]: Sòlda: {soldier.name} | Nivo Kòmansman: {soldier.level} | Credits: {soldier.credits}")
        print("-------------------------------------------------------")
        
        # Simulation sekans konba jiskaske lènmi an mouri pou n deklanche LEVEL UP la
        soldier.fire_at_enemy(zombie_bot)
        soldier.fire_at_enemy(zombie_bot)
        soldier.fire_at_enemy(zombie_bot)
        soldier.fire_at_enemy(zombie_bot)
        
        print("-------------------------------------------------------")
        print(f" -> [PROFILE UPDATE]: Nouvo Nivo: {soldier.level} | Total Credits: {soldier.credits} CR")

if __name__ == "__main__":
    game_instance = NeonFallAlphaGame()
    game_instance.start_game_simulation()
    print("=======================================================")
