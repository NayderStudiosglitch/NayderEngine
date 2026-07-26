import pygame
import sys
import os

class AssetLoader:
    def __init__(self):
        self.base_path = "Assets"
        print(" -> [ASSET LOADER]: Sistèm eskanè fichye yo SOU LI.")

    def verify_and_load(self, folder, file_name):
        full_path = os.path.join(self.base_path, folder, file_name)
        if os.path.exists(full_path):
            print(f"    [IO_SUCCESS]: Fichye detekte nan '{full_path}'! Loading nan VRAM...")
            return True
        else:
            print(f"    [IO_ERROR]: Fichye '{full_path}' manke nan katab la!")
            return False

class GameObject:
    def __init__(self, name, x, y, color, size, mesh_file):
        self.name = name
        self.x = x
        self.y = y
        self.color = color
        self.size = size
        self.mesh_file = mesh_file

class SceneSystem:
    def __init__(self):
        self.game_objects = {}
        self.loader = AssetLoader()

    def spawn_object(self, obj, folder):
        print(f"\n -> [SCENE SYSTEM]: Ap eseye spawn '{obj.name}'...")
        # Verifye si vrè fichye a la anvan li spawn
        if self.loader.verify_and_load(folder, obj.mesh_file):
            self.game_objects[obj.name] = obj
            print(f" ✅ STATUS: '{obj.name}' parèt sou kadriyaj la 100% kòrèkteman.")
        else:
            print(f" ❌ STATUS: Blokus! Pa ka spawn '{obj.name}' paske fichye l manke.")

class NayderEngineRuntime:
    def __init__(self):
        pygame.init()
        pygame.font.init()
        
        self.screen_width = 800
        self.screen_height = 600
        self.window = pygame.display.set_mode((self.screen_width, self.screen_height))
        pygame.display.set_caption("NAYDER ENGINE v0.0.18 - File Stream Core")
        self.clock = pygame.time.Clock()
        self.is_running = True
        
        self.scene = SceneSystem()
        
        print("\n=======================================================")
        print("    [NAYDER ENGINE v0.0.18] - HARDWARE FILE STREAM CORE")
        print("=======================================================")

    def run(self):
        while self.is_running:
            mouse_pos = pygame.mouse.get_pos()
            
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.is_running = False

            keys = pygame.key.get_pressed()
            player = self.scene.game_objects.get("Player_Soldier")
            if player:
                if keys[pygame.K_LEFT] or keys[pygame.K_a]: player.x -= 5
                if keys[pygame.K_RIGHT] or keys[pygame.K_d]: player.x += 5
                if keys[pygame.K_UP] or keys[pygame.K_w]: player.y -= 5
                if keys[pygame.K_DOWN] or keys[pygame.K_s]: player.y += 5

            self.window.fill((12, 12, 16))
            
            for x in range(0, self.screen_width, 40):
                pygame.draw.line(self.window, (22, 24, 32), (x, 0), (x, self.screen_height), 1)
            for y in range(0, self.screen_height, 40):
                pygame.draw.line(self.window, (22, 24, 32), (0, y), (self.screen_width, y), 1)
                
            for name, obj in self.scene.game_objects.items():
                pygame.draw.rect(self.window, obj.color, (obj.x, obj.y, obj.size, obj.size))
                
            font = pygame.font.SysFont("monospace", 12, bold=True)
            self.window.blit(font.render("NAYDER ENGINE V0.0.18 - FILE INTERACTION ONLINE", True, (0, 210, 255)), (20, 20))
            pygame.display.flip()
            self.clock.tick(107)

        pygame.quit()
        sys.exit()

if __name__ == "__main__":
    runtime = NayderEngineRuntime()
    
    # Nou ajoute gwo non vrè fichye .fbx yo dirèkteman nan Entity System nan!
    soldaer = GameObject("Player_Soldier", 200, 300, (0, 255, 128), 30, "haitian_soldier.fbx")
    runtime.scene.spawn_object(soldaer, "Models")
    
    zomb = GameObject("Zombie_Entity", 600, 300, (220, 50, 50), 25, "chopper.fbx")
    runtime.scene.spawn_object(zomb, "Models")
    
    runtime.run()
