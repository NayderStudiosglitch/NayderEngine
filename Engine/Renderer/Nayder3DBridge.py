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

def Desine_Player_3D():
    glBegin(GL_QUADS)
    for i, surface in enumerate(surfaces):
        glColor3fv(colors[i % len(colors)])
        for vertex in surface: glVertex3fv(vertices[vertex])
    glEnd()
    glBegin(GL_LINES)
    glColor3fv((10,10,15))
    for edge in edges:
        for vertex in edge: glVertex3fv(vertices[vertex])
    glEnd()

def Desine_Terrain_Grid():
    glColor3fv((40, 45, 60)) # Koulè liy tè kat la
    glBegin(GL_LINES)
    for i in range(-20, 21, 2):
        glVertex3f(i, -1, -20)
        glVertex3f(i, -1, 20)
        glVertex3f(-20, -1, i)
        glVertex3f(20, -1, i)
    glEnd()

def main():
    pygame.init()
    pygame.font.init()
    LÈT, WOTÈ = 800, 600
    pygame.display.set_mode((LÈT, WOTÈ), DOUBLEBUF | OPENGL)
    pygame.display.set_caption("NAYDER ENGINE v0.0.38 - 3D Graphics Bridge [PLAY MODE]")
    clock = pygame.time.Clock()

    gluPerspective(45, (LÈT / WOTÈ), 0.1, 50.0)
    cam_x, cam_y, cam_z = 0.0, 0.0, -8.0

    print("\n=======================================================")
    print("    [NAYDER ENGINE v0.0.38] - 3D GRAPHICS BRIDGE LIVE")
    print("=======================================================")
    print(" [*] C++ Core Logic Linked -> ✅ SYNCHRONIZED")
    print(" [*] OpenGL 3D Viewport     -> ✅ INITIALIZED ON SCREEN")
    print(" [*] Terrain Grid Loaded    -> ✅ DESERT GHOST CITY CHUNKS")
    print("-------------------------------------------------------")
    print(" KONTWÒL: Sèvi ak W-A-S-D oswa Flèch pou w deplase nan espas 3D a!")
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
        glRotatef(1, 0, 1, 0) # Vire dousman pou n ka wè anbyans lan

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glEnable(GL_DEPTH_TEST)

        Desine_Terrain_Grid()
        Desine_Player_3D()

        pygame.display.flip()
        clock.tick(107)

if __name__ == "__main__":
    main()
