import pygame
import sys
import os
import math

class AssetLoader:
    def __init__(self):
        self.base_path = "Assets"
        print(" -> [ASSET LOADER]: Sistèm eskanè fichye yo SOU LI.")

    def verify_and_load(self, folder, file_name):
        full_path = os.path.join(self.base_path, folder, file_name)
        if os.path.exists(full_path):
            return True
        return False

class GameObject:
    def __init__(self, name, x, y, color, size, mesh_file, obj_type="ENTITY"):
        self.name = name
        self.x = x
        self.y = y
        self.color = color
        self.size = size
        self.mesh_file = mesh_file
        self.obj_type = obj_type  # "ENTITY" oswa "LOOT"
        self.equipped_weapon = "None"

class SceneSystem:
    def __init__(self):
        self.game_objects = {}
        self.loader = AssetLoader()

    def spawn_object(self, obj, folder):
        if self.loader.verify_and_load(folder, obj.mesh_file) or obj.obj_type == "LOOT":
            self.game_objects[obj.name] = obj
            print(f" ✅ STATUS: '{obj.name}' spawn nan grid la kòrèkteman.")

class NayderEngineRuntime:
    def __init__(self):
        pygame.init()
        pygame.font.init()
        
        self.screen_width = 800
        self.screen_height = 600
        self.window = pygame.display.set_mode((self.screen_width, self.screen_height))
        pygame.display.set_caption("NAYDER ENGINE v0.0.19 - Loot AI Core")
        self.clock = pygame.time.Clock()
        self.is_running = True
        
        self.scene = SceneSystem()
        
        print("\n=======================================================")
        print("    [NAYDER ENGINE v0.0.19] - LOOT WEAPON SYSTEM CORE")
        print("=======================================================")

    def run(self):
        while self.is_running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.is_running = False

            # Koute klavye pou deplasman Sòlda a
            keys = pygame.key.get_pressed()
            player = self.scene.game_objects.get("Player_Soldier")
            if player:
                if keys[pygame.K_LEFT] or keys[pygame.K_a]: player.x -= 5
                if keys[pygame.K_RIGHT] or keys[pygame.K_d]: player.x += 5
                if keys[pygame.K_UP] or keys[pygame.K_w]: player.y -= 5
                if keys[pygame.K_DOWN] or keys[pygame.K_s]: player.y += 5

            # =================================================================
            # LOJIK: LOOT WEAPON DETEKSYON SYSTEM (Collision Input)
            # =================================================================
            loot_item = self.scene.game_objects.get("Neon_SMG_Loot")
            if player and loot_item:
                # Kalkile distans ant Sòlda a ak Zam lan (Matematik AABB kout)
                distans = math.sqrt((player.x - loot_item.x)**2 + (player.y - loot_item.y)**2)
                if distans < 30: # Kontak! Sòlda a mache sou zam lan
                    player.equipped_weapon = "Neon SMG (Low Recoil)"
                    print(f"\n⚡🎴 [LOOT ACQUIRED]: Sòlda a ranmase '{loot_item.name}' ak pwòp men l!")
                    print(f"    -> NAYDER ENGINE: Weapon attached to Player skeletal joint.")
                    # Efase zam lan sou kat la piske l nan men jwè a kounye a
                    del self.scene.game_objects["Neon_SMG_Loot"]

            self.window.fill((12, 12, 16))
            
            # Desine Editè Grid la
            for x in range(0, self.screen_width, 40):
                pygame.draw.line(self.window, (22, 24, 32), (x, 0), (x, self.screen_height), 1)
            for y in range(0, self.screen_height, 40):
                pygame.draw.line(self.window, (22, 24, 32), (0, y), (self.screen_width, y), 1)
                
            # Desine tout objè yo
            for name, obj in list(self.scene.game_objects.items()):
                pygame.draw.rect(self.window, obj.color, (obj.x, obj.y, obj.size, obj.size))
                
            # Afiche enfòmasyon yo an tan reyèl
            font = pygame.font.SysFont("monospace", 12, bold=True)
            self.window.blit(font.render("NAYDER ENGINE V0.0.19 - INTERACTIVE LOOT ACTIVE", True, (0, 210, 255)), (20, 20))
            if player:
                self.window.blit(font.render(f"ZAM NAN MEN W: {player.equipped_weapon}", True, (230, 180, 40)), (20, 40))
                self.window.blit(font.render("[DEPLASE SOU TI KARE CYAN LAN POU W RANMASE ZAM NAN]", True, (130, 135, 145)), (20, 60))

            pygame.display.flip()
            self.clock.tick(107)

        pygame.quit()
        sys.exit()

if __name__ == "__main__":
    runtime = NayderEngineRuntime()
    
    # 1. Spawn Sòlda a
    soldaer = GameObject("Player_Soldier", 200, 300, (0, 255, 128), 30, "haitian_soldier.fbx")
    runtime.scene.spawn_object(soldaer, "Models")
    
    # 2. Spawn Zam lan sou kat la (Ti kare koulè Cyan) k ap tann moun ranmase l
    neon_smg = GameObject("Neon_SMG_Loot", 450, 300, (0, 210, 255), 18, "none", obj_type="LOOT")
    runtime.scene.spawn_object(neon_smg, "Models")
    
    runtime.run()
