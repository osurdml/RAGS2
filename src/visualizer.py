import sys, random, math, pygame
import numpy as np
from pygame.locals import *


#constants
XDIM = 640
YDIM = 480
WINSIZE = [XDIM, YDIM]
scale = 15
offset = 1

def main():
        vertices = np.genfromtxt('sector_vertices1.txt', delimiter=',')
        edges = np.genfromtxt('sector_edges1.txt', delimiter=',')
        vertices = (vertices.astype(int)+offset)*scale
        edges = edges.astype(int)
        #initialize and prepare screen
        pygame.init()
        screen = pygame.display.set_mode(WINSIZE)
        white = 255, 240, 200
        black = 20, 20, 40
        screen.fill(white)
        print edges[1,:] 
        for i in range(0,len(edges[:,0])):
            #print vertices[i,:], vertices[edges[i,j],:]
            pygame.draw.line(screen,black,(vertices[edges[i,0],0], vertices[edges[i,0],1]), (vertices[edges[i,1],0], vertices[edges[i,1],1]))
            pygame.display.update()
        raw_input("Press Enter to continue...")


# if python says run, then we should run
if __name__ == '__main__':
        main()


