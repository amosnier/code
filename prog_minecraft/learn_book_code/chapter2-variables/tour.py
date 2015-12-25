#Connect to Minecraft
from mcpi.minecraft import Minecraft
mc = Minecraft.create()
import time

mc.player.setTilePos(175, 64, 71)
time.sleep(0.5)
mc.player.setTilePos(185, 64, 71)
time.sleep(0.5)
mc.player.setTilePos(185, 64, 81)
time.sleep(0.5)
mc.player.setTilePos(195, 64, 81)
time.sleep(0.5)
mc.player.setTilePos(195, 64, 91)
time.sleep(0.5)
mc.player.setTilePos(205, 64, 91)
