import pygame
import sys
import math
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *

# Done Jewometri 3D pou Jwè a (Kib)
vertices = ((1,-1,-1), (1,1,-1), (-1,1,-1), (-1,-1,-1), (1,-1,1), (1,1,1), (-1,-1,1), (-1,1,1))
surfaces = ((0,1,2,3), (3,2,7,6), (6,7,5,4), (4,5,1,0), (1,5,7,2), (4,0,3,6))

# =============================================================================
# MODIL GRAPHICS: 3D HEIGHTMAP TERRAIN GENERATOR
# =============================================================================
terrain_vertices = []
terrain_indices = []

def Generate_3D_Terrain_Mesh(grid_size=20, spacing=1.0):
    global terrain_vertices, terrain_indices
    terrain_vertices = []
    terrain_indices = []
    
    # 🏔️ Kalkile altitid mòn ak fon yo ak fonksyon Matematik Math.sin (Heightmap Core)
    for z in range(grid_size):
        for x in range(grid_size):
            pos_x = (x - grid_size/2) * spacing
            pos_z = (z - grid_size/2) * spacing
            
            # Simulate mòn nan mitan kat Desert Ghost City a
            dist_from_center = math.sqrt(pos_x**2 + pos_z**2)
            if dist_from_center < 6.0:
                pos_y = (math.sin(x * 0.5) * math.cos(z * 0.5) * 1.5) + 2.0 # Tèt Mòn
            else:
                pos_y = -0.5 # Plèn lari ki plat
                
            terrain_vertices.append((pos_x, pos_y, pos_z))

    # Bati triyang yo pou kat grafik la ka desine yo (Face Matrix)
    for z in range(grid_size - 1):
        for x in range(grid_size - 1):
            i0 = z * grid_size + x
            i1 = i0 + 1
            i2 = (z + 1) * grid_size + x
            i3 = i2 + 1
            # Triyang 1
            terrain_indices.extend([i0, i1, i2])
            # Triyang 2
            terrain_indices.extend([i1, i3, i2])

def Desine_Terrain_Mesh_3D():
    glDisable(GL_LIGHTING)
    # 🟢 Desine liy kadriyaj mòn yo an bèl koulè Neon Green/Blue k ap briye
    glColor3fv((0, 200, 150))
    glBegin(GL_LINES)
    for i in range(0, len(terrain_indices), 3):
        v0 = terrain_vertices[terrain_indices[i]]
        v1 = terrain_vertices[terrain_indices[i+1]]
        v2 = terrain_vertices[terrain_indices[i+2]]
        
        glVertex3fv(v0); glVertex3fv(v1)
        glVertex3fv(v1); glVertex3fv(v2)
        glVertex3fv(v2); glVertex3fv(v0)
    glEnd()
    glEnable(GL_LIGHTING)

def Configured_Neon_Lighting():
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE)
    glLightfv(GL_LIGHT0, GL_POSITION, [0.0, 10.0, 5.0, 1.0])
    glLightfv(GL_LIGHT0, GL_DIFFUSE, [0.0, 0.8, 1.0, 1.0])

def Desine_Player_3D():
    glBegin(GL_QUADS)
    for surface in surfaces:
        glColor3fv((220, 50, 50)) # Kib Sòlda a an Wouj Neon
        for vertex in surface: glVertex3fv(vertices[vertex])
    glEnd()

def main():
    pygame.init()
    LÈT, WOTÈ = 800, 600
    pygame.display.set_mode((LÈT, WOTÈ), DOUBLEBUF | OPENGL)
    pygame.display.set_caption("NAYDER ENGINE v0.0.79 - 3D Terrain Viewport")
    clock = pygame.time.Clock()

    gluPerspective(45, (LÈT / WOTÈ), 0.1, 100.0)
    cam_x, cam_y, cam_z = 0.0, -3.0, -25.0
    rot_y = 0

    # Lanse kalkilatè mòn lan yon sèl kou
    Generate_3D_Terrain_Mesh(30, 1.5)

    print("\n=======================================================")
    print("    [NAYDER ENGINE v0.0.79] - 3D GRAPHICS TERRAIN LIVE")
    print("=======================================================")
    print(" [*] OpenGL 3D Viewport   -> ✅ INITIALIZED ON SCREEN")
    print(" [*] 3D Terrain Renderer  -> ✅ HEIGHTMAP GRID LOADED")
    print(" -> PEZE W-A-S-D OSOA FLÈCH POU DEPLASE KAT LA!")
    print("=======================================================")

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT: pygame.quit(); sys.exit()

        keys = pygame.key.get_pressed()
        if keys[pygame.K_w] or keys[pygame.K_UP]:    cam_z += 0.2
        if keys[pygame.K_s] or keys[pygame.K_DOWN]:  cam_z -= 0.2
        if keys[pygame.K_a] or keys[pygame.K_LEFT]:  cam_x += 0.2
        if keys[pygame.K_d] or keys[pygame.K_RIGHT]: cam_x -= 0.2

        glLoadIdentity()
        gluPerspective(45, (LÈT / WOTÈ), 0.1, 100.0)
        glTranslatef(cam_x, cam_y, cam_z)
        glRotatef(rot_y, 0, 1, 0)
        rot_y += 0.5 # Kat la ap vire dousman pou n ka byen wè mòn yo!

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glEnable(GL_DEPTH_TEST)

        Configured_Neon_Lighting()
        Desine_Terrain_Mesh_3D() # Desine vrè Terrain 3D a!
        Desine_Player_3D()       # Jwè a nan mitan an

        pygame.display.flip()
        clock.tick(107)

if __name__ == "__main__":
    main()
