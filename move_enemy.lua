math.randomseed(os.time())

positions = {}

for y = 10, 40, 2 do
    for x = 10, 40 do        
        table.insert(positions, x)
        table.insert(positions, y)
    end

    for x = 40, 10, -1 do
        table.insert(positions, x)
        table.insert(positions, y + 1)
    end
end

move_enemy(unpack(positions));
