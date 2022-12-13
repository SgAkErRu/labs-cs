[x,y] = meshgrid(-100:1:100, -100:1:100)
z = (x-3).^2 + (y-4).^2

mesh(x, y, z)

xgrid()
