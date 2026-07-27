import pygame
import sys
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLU import *

# Matrix kowòdone Kib Sòlda a an 3D
vertices = ((1,-1,-1), (1,1,-1), (-1,1,-1), (-1,-1,-1), (1,-1,1), (1,1,1), (-1,-1,1), (-1,1,1))
edges = ((0,1), (0,3), (0,4), (2,1), (2,3), (2,7), (6,3), (6,4), (6,7), (5,1), (5,4), (5,7))
colors = ((0,210,255), (220,50,50), (0,255,128), (230,180,40), (150,0,255), (255,0,150))
surfaces = ((0,1,2,3), (3,2,7,6), (6,7,5,4), (4,5,1,0), (1,5,7,2), (4,0,3,6))

# Vektè nòmal pou kalkil limyè sou chak fas kib la (GPU Lighting Normals)
normals = ((0,0,-1), (-1,0,0), (0,0,1), (1,0,0), (0,1,0), (0,-1,0))

def Configured_Neon_Lighting():
    # 1. Aktive nwayo limyè Kat Grafik la (GPU Lighting Setup)
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE)

    # 2. Defini Koulè ak Pozisyon Limyè Neon Cyan an nan espas la
    limye_pozisyon = [0.0, 5.0, 5.0, 1.0] # Plase anlè jwè a
    limye_ambient = [0.2, 0.2, 0.3, 1.0]   # Ti klète fènwa nan background nan (GL_AMBIENT RANJE!)
    limye_diffuse = [0.0, 0.8, 1.0, 1.0]   # Gwo reyon Neon Cyan klere a

    glLightfv(GL_LIGHT0, GL_POSITION, limye_pozisyon)
    glLightfv(GL_LIGHT0, GL_AMBIENT, limye_ambient)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, limye_diffuse)

def Desine_Player_3D():
    glBegin(GL_QUADS)
    for i, surface in enumerate(surfaces):
        glNormal3fv(normals[i % len(normals)]) # Voye vektè nòmal bay GPU a
        glColor3fv(colors[i % len(colors)])
        for vertex in surface: glVertex3fv(vertices[vertex])
    glEnd()

    # Desine liy fil nwa yo sou bòb bwat la
    glDisable(GL_LIGHTING) 
    glBegin(GL_LINES)
    glColor3fv((10,10,15))
    for edge in edges:
        for vertex in edge: glVertex3fv(vertices[vertex])
    glEnd()
    glEnable(GL_LIGHTING)

def Desine_Terrain_Grid():
    glDisable(GL_LIGHTING) 
    glColor3fv((0, 150, 200)) # Koulè liy tè a tounen Neon Blue k ap briye!
    glBegin(GL_LINES)
    for i in range(-20, 21, 2):
        glVertex3f(i, -1, -20)
        glVertex3f(i, -1, 20)
        glVertex3f(-20, -1, i)
        glVertex3f(20, -1, i)
    glEnd()
    glEnable(GL_LIGHTING)

def main():
    pygame.init()
    LÈT, WOTÈ = 800, 600
    pygame.display.set_mode((LÈT, WOTÈ), DOUBLEBUF | OPENGL)
    pygame.display.set_caption("NAYDER ENGINE v0.0.39 - Real-Time Neon Lighting Core")
    clock = pygame.time.Clock()

    gluPerspective(45, (LÈT / WOTÈ), 0.1, 50.0)
    cam_x, cam_y, cam_z = 0.0, 0.0, -8.0

    print("\n=======================================================")
    print("    [NAYDER ENGINE v0.0.39] - NEON LIGHTING ENGINE CORE")
    print("=======================================================")
    print(" [*] Modil 7: Lighting Pipeline -> ✅ HARDWARE GPU LIGHTING ACTIVE")
    print(" [*] Material Color Mapping     -> ✅ NEON GRADIENT GLOW UNLOCKED")
    print("-------------------------------------------------------")
    print(" KONTWÒL: Sèvi ak W-A-S-D oswa Flèch pou w deplase nan anbyans lan!")
    print("=======================================================")

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        keys = pygame.key.get_pressed()
        if keys[pygame.K_w] or keys[pygame.K_UP]:    cam_z += 0.1
        if keys[pygame.K_s] or keys[pygame.K_DOWN]:  cam_z -= 0.1
        if keys[pygame.K_a] or keys[pygame.K_LEFT]:  cam_x += 0.1
        if keys[pygame.K_d] or keys[pygame.K_RIGHT]: cam_x -= 0.1

        glLoadIdentity()
        gluPerspective(45, (LÈT / WOTÈ), 0.1, 50.0)
        glTranslatef(cam_x, cam_y, cam_z)
        glRotatef(1, 0, 1, 0) 

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glEnable(GL_DEPTH_TEST)

        Configured_Neon_Lighting() 
        Desine_Terrain_Grid()
        Desine_Player_3D()

        pygame.display.flip()
        clock.tick(107)

if __name__ == "__main__":
    main()
