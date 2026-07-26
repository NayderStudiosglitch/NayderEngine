import pygame
import sys

class GameObject:
    def __init__(self, name, x, y, color, size):
        self.name = name
        self.x = x
        self.y = y
        self.color = color
        self.size = size

class SceneSystem:
    def __init__(self):
        self.game_objects = {}

    def spawn_object(self, obj):
        self.game_objects[obj.name] = obj
        print(f" -> [SCENE SYSTEM]: '{obj.name}' spawn nan grid la kòrèkteman.")

class NayderEngineRuntime:
    def __init__(self):
        pygame.init()
        pygame.font.init()
        
        self.screen_width = 800
        self.screen_height = 600
        self.window = pygame.display.set_mode((self.screen_width, self.screen_height))
        pygame.display.set_caption("NAYDER ENGINE v0.0.1 - Phase 1 Protocore")
        self.clock = pygame.time.Clock()
        self.is_running = True
        
        self.scene = SceneSystem()
        
        print("\n=======================================================")
        print("    [NAYDER ENGINE v0.0.1] - CORE INITIALIZED WITH GIT")
        print("=======================================================")
        print(" [*] Engine Core      -> ✅ SOU LI")
        print(" [*] Window System    -> ✅ SOU LI (800x600)")
        print(" [*] Input System     -> ✅ SOU LI (Keyboard/Mouse)")
        print(" [*] Renderer Base    -> ✅ SOU LI (Editor Grid)")
        print(" [*] Scene System     -> ✅ SOU LI")
        print(" [*] Entity System    -> ✅ SOU LI")
        print("-------------------------------------------------------")

    def run(self):
        while self.is_running:
            mouse_pos = pygame.mouse.get_pos()
            
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.is_running = False
                if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
                    print(f" -> [INPUT SYSTEM]: Mouse click detekte nan pos: {mouse_pos}")

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
            self.window.blit(font.render("NAYDER ENGINE V0.0.1 - DEVELOPMENT ARCHITECTURE", True, (0, 210, 255)), (20, 20))
            self.window.blit(font.render("[KONTWÒL: W-A-S-D OSWA FLÈCH POU DEPLASE JWÈ A]", True, (120, 125, 135)), (20, 40))

            pygame.display.flip()
            self.clock.tick(107)

        pygame.quit()
        sys.exit()

if __name__ == "__main__":
    runtime = NayderEngineRuntime()
    
    soldaer = GameObject("Player_Soldier", 200, 300, (0, 255, 128), 30)
    runtime.scene.spawn_object(soldaer)
    
    zomb = GameObject("Zombie_Entity", 600, 300, (220, 50, 50), 25)
    runtime.scene.spawn_object(zomb)
    
    runtime.run()
