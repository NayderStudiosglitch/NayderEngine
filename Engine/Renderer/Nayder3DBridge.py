import pygame
import sys
import math
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *

# Done Jewometri 3D pou Jwè a
vertices = ((1,-1,-1), (1,1,-1), (-1,1,-1), (-1,-1,-1), (1,-1,1), (1,1,1), (-1,-1,1), (-1,1,1))
surfaces = ((0,1,2,3), (3,2,7,6), (6,7,5,4), (4,5,1,0), (1,5,7,2), (4,0,3,6))

# Matris Tè a
terrain_vertices = []
terrain_indices = []

def Generate_3D_Terrain_Mesh(grid_size=30, spacing=1.5):
    global terrain_vertices, terrain_indices
    terrain_vertices = []
    terrain_indices = []
    for z in range(grid_size):
        for x in range(grid_size):
            pos_x = (x - grid_size/2) * spacing
            pos_z = (z - grid_size/2) * spacing
            dist_from_center = math.sqrt(pos_x**2 + pos_z**2)
            if dist_from_center < 10.0:
                pos_y = (math.sin(x * 0.4) * math.cos(z * 0.4) * 2.0) + 1.5
            else:
                pos_y = -0.5
            terrain_vertices.append((pos_x, pos_y, pos_z))

    for z in range(grid_size - 1):
        for x in range(grid_size - 1):
            i0 = z * grid_size + x
            i1 = i0 + 1
            i2 = (z + 1) * grid_size + x
            i3 = i2 + 1
            terrain_indices.extend([i0, i1, i2, i1, i3, i2])

def Desine_Terrain_Mesh_3D():
    glDisable(GL_LIGHTING)
    glColor3fv((0, 255, 180))
    glBegin(GL_LINES)
    for i in range(0, len(terrain_indices), 3):
        glVertex3fv(terrain_vertices[terrain_indices[i]])
        glVertex3fv(terrain_vertices[terrain_indices[i+1]])
        glVertex3fv(terrain_vertices[terrain_indices[i+1]])
        glVertex3fv(terrain_vertices[terrain_indices[i+2]])
        glVertex3fv(terrain_vertices[terrain_indices[i+2]])
        glVertex3fv(terrain_vertices[terrain_indices[i]])
    glEnd()
    glEnable(GL_LIGHTING)

def Desine_Player_3D():
    glBegin(GL_QUADS)
    for surface in surfaces:
        glColor3fv((220, 50, 50))
        for vertex in surface:
            glVertex3fv(vertices[vertex])
    glEnd()

anim_blend_factor = 0.0
current_anim_state = "LOCOMOTION_RUN"

def Process_Animation_Graph_Tick(keys):
    global anim_blend_factor, current_anim_state
    if keys[pygame.K_SPACE]:
        current_anim_state = "COMBAT_IMPACT_STUMBLE"
        if anim_blend_factor < 1.0: anim_blend_factor += 0.05
    else:
        current_anim_state = "LOCOMOTION_RUN"
        if anim_blend_factor > 0.0: anim_blend_factor -= 0.05

def main():
    pygame.init()
    LÈT, WOTÈ = 1366, 768
    pygame.display.set_mode((LÈT, WOTÈ), DOUBLEBUF | OPENGL | RESIZABLE)
    pygame.display.set_caption("NAYDER ENGINE v0.0.80 - Full 360 Desktop Viewport")
    
    pygame.event.set_grab(True)
    pygame.mouse.set_visible(False)
    
    clock = pygame.time.Clock()
    Generate_3D_Terrain_Mesh(35, 1.8)

    cam_x, cam_y, cam_z = 0.0, -4.0, -30.0
    yaw, pitch = -90, 0

    print("\n=======================================================")
    print("    [NAYDER ENGINE v0.0.80] - FULL-SCREEN 360 GRAPHICS")
    print("=======================================================")
    print(" [*] Viewport Mode        -> ✅ WIDE HD COMPUTER SCREEN ACTIVE")
    print(" [*] 360 Mouse Look Core  -> ✅ HARDWARE MOUSE GRAB ACTIVE")
    print(" [*] Animation Graph Loop -> ✅ BLEND TREE ACTIVE (v0.0.80)")
    print(" -> BOUD DEPLASÈ: Sèvi ak W-A-S-D pou mache, deplase sourit la pou w wè 360 degre!")
    print("=======================================================")

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT: pygame.quit(); sys.exit()
            if event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE:
                pygame.quit(); sys.exit()

        mouse_dx, mouse_dy = pygame.mouse.get_rel()
        yaw += mouse_dx * 0.15
        pitch -= mouse_dy * 0.15
        if pitch > 89.0:  pitch = 89.0
        if pitch < -89.0: pitch = -89.0

        keys = pygame.key.get_pressed()
        rad_yaw = math.radians(yaw)
        if keys[pygame.K_w] or keys[pygame.K_UP]:
            cam_x += math.cos(rad_yaw) * 0.3
            cam_z += math.sin(rad_yaw) * 0.3
        if keys[pygame.K_s] or keys[pygame.K_DOWN]:
            cam_x -= math.cos(rad_yaw) * 0.3
            cam_z -= math.sin(rad_yaw) * 0.3

        Process_Animation_Graph_Tick(keys)
        if keys[pygame.K_SPACE]:
            print(f" 🔄 [ANIMATION GRAPH]: Blend factor: {anim_blend_factor:.2f} | State: {current_anim_state}", end="\r")

        glLoadIdentity()
        gluPerspective(45, (LÈT / WOTÈ), 0.1, 150.0)
        
        glRotatef(-pitch, 1, 0, 0)
        glRotatef(-yaw - 90, 0, 1, 0)
        glTranslatef(cam_x, cam_y, cam_z)

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glEnable(GL_DEPTH_TEST)

        glEnable(GL_LIGHTING)
        glEnable(GL_LIGHT0)
        glLightfv(GL_LIGHT0, GL_POSITION, [0.0, 20.0, 10.0, 1.0])

        Desine_Terrain_Mesh_3D()
        
        glPushMatrix()
        glTranslatef(0.0, 1.5, 0.0)
        Desine_Player_3D()
        glPopMatrix()

        pygame.display.flip()
        clock.tick(107)

if __name__ == "__main__":
    main()
