from PIL import Image
import numpy as np

width = 8
height = 8

square24 = np.zeros([width, height, 3], dtype=np.uint8)
square24[:] = 255
img24 = Image.fromarray(square24, mode="RGB")
img24.save("bitmap24.bmp")

square32 = np.zeros([width, height, 4], dtype=np.uint8)
square32[:] = 255
img32 = Image.fromarray(square32, mode="RGBA")
img32.save("bitmap32.bmp")

