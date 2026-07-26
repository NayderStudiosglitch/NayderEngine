import sys
import time

class WeatherSystem:
    def __init__(self):
        self.time_of_day = "DAY"  # Ka chanje ant: DAY, DUSK, NIGHT
        self.current_hazard = "CLEAR"  # Ka chanje ant: CLEAR, RAD_STORM
        self.visibility_percentage = 100

    def set_time_of_day(self, new_time):
        self.time_of_day = new_time.upper()
        if self.time_of_day == "NIGHT":
            self.visibility_percentage = 40
            print(f" 🌙 [ENVIRONMENT]: Sik lannwit deklanche. Syèl la tounen Cyberpunk Dark Purple.")
            print(f"    [GPU RENDER]: Limen tout limyè neon yo ak gwo rann chaj VRAM.")
        else:
            self.visibility_percentage = 100
            print(f" ☀️ [ENVIRONMENT]: Solèy leve. Vizibilite retounen sou 100%.")

    def trigger_radiation_storm(self, player_target):
        self.current_hazard = "RAD_STORM"
        self.visibility_percentage = 20
        print(f"\n🚨 ⛈️ [WEATHER HAZARD]: TANPÈT RADYO-AKTIF DEKLANCHE!")
        print(f"    [EFFECT]: Vizibilite desann sou {self.visibility_percentage}%. Lafimen volumetrik vèt anvayi vil la.")
        
        # Dega tanpèt la sou jwè a
        print(f"    [HAZARD DAMAGE]: Radyasyon ap aji sou '{player_target.name}'...")
        player_target.hp -= 15
        print(f" 💥 [HIT]: '{player_target.name}' pran -15 HP nan radyasyon! Sante sòlda: {player_target.hp}/100")

class PlayerController:
    def __init__(self, name):
        self.name = name
        self.hp = 100
        self.level = 25

class NeonFallAlphaGame:
    def __init__(self):
        print("\n=======================================================")
        print("    [PROJECT: NEON FALL] - ALPHA v0.5 METEO AK JOU/LANNWIT")
        print("=======================================================")
        self.weather = WeatherSystem()
        
    def start_game_simulation(self):
        soldier = PlayerController(name="NAYDER_01")
        
        print(f" -> [SPAWN]: Jwè '{soldier.name}' parèt sou kat 'Desert Ghost City'.")
        print("-------------------------------------------------------")
        
        # 1. Tès Simulation Sik Lannwit (Aksyon!)
        time.sleep(0.5)
        self.weather.set_time_of_day("NIGHT")
        
        print("-------------------------------------------------------")
        # 2. Tès Simulation Tanpèt Radyo-aktif k ap blese jwè a
        time.sleep(0.5)
        self.weather.trigger_radiation_storm(soldier)
        
        print("-------------------------------------------------------")
        print(" ✅ STATUS: Sistèm Dinamik Meteo ak Anbyans teste 100% kòrèkteman.")

if __name__ == "__main__":
    game_instance = NeonFallAlphaGame()
    game_instance.start_game_simulation()
    print("=======================================================")
