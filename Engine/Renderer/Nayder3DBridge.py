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
normals = ((0,0,-1), (-1,0,0), (0,0,1), (1,0,0), (0,1,0), (0,-1,0))

def Configured_Neon_Lighting():
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE)
    glLightfv(GL_LIGHT0, GL_POSITION, [0.0, 5.0, 5.0, 1.0])
    glLightfv(GL_LIGHT0, GL_AMBIENT, [0.2, 0.2, 0.3, 1.0])
    glLightfv(GL_LIGHT0, GL_DIFFUSE, [0.0, 0.8, 1.0, 1.0])

def Desine_Player_3D():
    glBegin(GL_QUADS)
    for i, surface in enumerate(surfaces):
        glNormal3fv(normals[i % len(normals)])
        glColor3fv(colors[i % len(colors)])
        for vertex in surface: glVertex3fv(vertices[vertex])
    glEnd()
    glDisable(GL_LIGHTING)
    glBegin(GL_LINES)
    glColor3fv((10,10,15))
    for edge in edges:
        for vertex in edge: glVertex3fv(vertices[vertex])
    glEnd()
    glEnable(GL_LIGHTING)

def Desine_Terrain_Grid():
    glDisable(GL_LIGHTING)
    glColor3fv((0, 150, 200))
    glBegin(GL_LINES)
    for i in range(-20, 21, 2):
        glVertex3f(i, -1, -20); glVertex3f(i, -1, 20)
        glVertex3f(-20, -1, i); glVertex3f(20, -1, i)
    glEnd()
    glEnable(GL_LIGHTING)

# =============================================================================
# VRÈ NWAYO TRANSFÒMASYON TÈKS AN TÈKSTIRE 2D POU GPU A
# =============================================================================
def Krey_Tekstire_Teks(text, font, text_color):
    textSurface = font.render(text, True, text_color)
    textData = pygame.image.tostring(textSurface, "RGBA", True)
    width, height = textSurface.get_size()
    
    tex_id = glGenTextures(1)
    glBindTexture(GL_TEXTURE_2D, tex_id)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textData)
    return tex_id, width, height

def Desine_Plak_HUD(tex_id, x, y, w, h):
    glEnable(GL_TEXTURE_2D)
    glBindTexture(GL_TEXTURE_2D, tex_id)
    glBegin(GL_QUADS)
    glTexCoord2f(0, 0); glVertex2f(x, y)
    glTexCoord2f(1, 0); glVertex2f(x + w, y)
    glTexCoord2f(1, 1); glVertex2f(x + w, y + h)
    glTexCoord2f(0, 1); glVertex2f(x, y + h)
    glEnd()
    glDisable(GL_TEXTURE_2D)

def main():
    pygame.init()
    pygame.font.init()
    LÈT, WOTÈ = 800, 600
    pygame.display.set_mode((LÈT, WOTÈ), DOUBLEBUF | OPENGL)
    pygame.display.set_caption("NAYDER ENGINE v0.0.42 - Real 3D GPU HUD Overlay")
    clock = pygame.time.Clock()

    font = pygame.font.SysFont("monospace", 15, bold=True)
    bold_font = pygame.font.SysFont("monospace", 36, bold=True)

    # Konstwi vrè plak tèkstire yo yon sèl fwa pou VRAM lan
    title_tex, tw, th = Krey_Tekstire_Teks("NEON FALL 17", bold_font, (220, 50, 50))
    sub_tex, sw, sh = Krey_Tekstire_Teks("ONLINE MULTIPLAYER - OPEN WORLD", font, (150, 155, 165))
    prof_tex, pw, ph = Krey_Tekstire_Teks("NAYDER_01 [LVL 25] | 53,860 CR", font, (230, 180, 40))
    btn_tex, bw, bh = Krey_Tekstire_Teks("[1. BUILD WEAPON]   [2. TEST WEAPON]", font, (0, 210, 255))

    gluPerspective(45, (LÈT / WOTÈ), 0.1, 50.0)
    cam_x, cam_y, cam_z = 0.0, 0.0, -8.0

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT: pygame.quit(); sys.exit()

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
        
        # DESINE HUD AN 2D DIRECTEMAN ANLE SCENE LAN (Dynamic Ortho Matrix)
        glMatrixMode(GL_PROJECTION); glPushMatrix(); glLoadIdentity(); gluOrtho2D(0, 800, 0, 600)
        glMatrixMode(GL_MODELVIEW); glPushMatrix(); glLoadIdentity()
        glDisable(GL_LIGHTING); glDisable(GL_DEPTH_TEST)
        glColor3fv((255, 255, 255))

        # Afiche plak tèkstire tèks yo sou ekran an vizyèlman
        Desine_Plak_HUD(title_tex, 30, 530, tw, th)
        Desine_Plak_HUD(sub_tex, 30, 500, sw, sh)
        Desine_Plak_HUD(prof_tex, 480, 535, pw, ph)
        Desine_Plak_HUD(btn_tex, 30, 30, bw, bh)

        glEnable(GL_DEPTH_TEST); glEnable(GL_LIGHTING)
        glMatrixMode(GL_PROJECTION); glPopMatrix(); glMatrixMode(GL_MODELVIEW); glPopMatrix()

        pygame.display.flip()
        clock.tick(107)

if __name__ == "__main__":
    main()
