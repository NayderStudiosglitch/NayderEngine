import math

class PhysicsEngine:
    def __init__(self):
        print("\n=======================================================")
        print("     [NAYDER ENGINE v0.0.4] - PHYSICS & COLLISION CORE")
        print("=======================================================")
        self.gravity = -9.8  # Gravite mond reyèl la (m/s^2)
        
    def calculate_bullet_drop(self, initial_velocity, distance_meters):
        # Simulation fizik Bullet Drop pou Sniper yo
        print(f" -> [PHYSICS]: Kalkile fòs gravite sou bal Sniper...")
        time_of_flight = distance_meters / initial_velocity
        drop_amount = 0.5 * abs(self.gravity) * (time_of_flight ** 2)
        print(f"    [VELOCITY]: {initial_velocity} m/s | DISTANS: {distance_meters}m")
        print(f" ✅ STATUS: Bal la desann de {drop_amount:.2f} mèt akòz gravite.")
        return drop_amount

    def check_aabb_collision(self, obj1_bounds, obj2_bounds):
        # Kòd pwofesyonèl deteksyon kounyè (AABB Collision Detection)
        print(f" -> [COLLISION]: Ap analize bwat kowòdone objè yo (Bounding Boxes)...")
        
        # Bounding box fòma: [x, y, lajè, wotè]
        x1, y1, w1, h1 = obj1_bounds
        x2, y2, w2, h2 = obj2_bounds
        
        if (x1 < x2 + w2 and x1 + w1 > x2 and
            y1 < y2 + h2 and y1 + h1 > y2):
            print(" 💥 COLLISION DETECTED!!! Objè yo frape.")
            print(" -> GRAPHICS ACTION: [SCREEN SHAKE MATRIX ACTIVATED] (~ * ~ * ~)")
            return True
        print(" ⚪ NO COLLISION: Objè yo an sekirite.")
        return False

if __name__ == "__main__":
    # Teste modil fizik la lokalman
    physics_core = PhysicsEngine()
    print("-------------------------------------------------------")
    
    # 1. Tès Bullet Drop pou gwo zam Sniper nan mòn
    physics_core.calculate_bullet_drop(initial_velocity=850, distance_meters=600)
    
    print("-------------------------------------------------------")
    # 2. Tès Collision Matrix (Sòlda vs Zonbi)
    # Simulation lè yo manyen (Collision)
    soldier_rect = [200, 300, 30, 30]
    zombie_rect  = [215, 310, 25, 25]
    physics_core.check_aabb_collision(soldier_rect, zombie_rect)
    print("=======================================================")
