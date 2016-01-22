from mcpi.minecraft import Minecraft

WOOL  = 35

mc = Minecraft.create()

x = 197
y = 63
z = 174
mc.setBlock(x, y, z, WOOL)

y = y + 1
mc.setBlock(x, y, z, WOOL)

x = x + 1
mc.setBlock(x, y, z, WOOL)

y = y + 1
mc.setBlock(x, y, z, WOOL)

x = x + 1
mc.setBlock(x, y, z, WOOL)

y = y + 1
mc.setBlock(x, y, z, WOOL)

x = x + 1
mc.setBlock(x, y, z, WOOL)
