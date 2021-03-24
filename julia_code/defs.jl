include("data_types.jl")

Base.println(board :: Board) = print(board :: Board)

function putPiece(board :: Board, piece :: Node, id :: Int64,  x :: Int64, y :: Int64)
    for p in piece.cubes
        posx, posy = x + p[1] - 1, y + p[2] - 1
        board.squares[posx, posy] = id
    end

    return board
end

function buildMatrix(bb :: Board, pool, testing = false)
    q :: Int64 = 0

    x, y = bb.size

    for (n, ppp) in enumerate(pool)
        for i in 1:x, j in 1:y
            for pp in ppp.cubits
                if canFit(bb, pp, i, j)
                    q += 1
                    if !testing
                        w = zeros(Int64, x*y + length(pool))
                        for p in pp.cubes
                            posx, posy = i + p[1] - 1, j + p[2] - 1
                            w[n] = 1
                            w[length(pool) + (posx-1) + (posy-1)*x + 1] = 1
                        end
                        for z in w
                            print("$z ")
                        end
                        println("")
                    end
                end
            end
        end
    end

    return q
end

function Base.print(board :: Board)
    colors = [:red, :green, :blue, :yellow, :cyan, :magenta, :white]
    bx, by = board.size

    for i in 1:bx
        for j in 1:by
            print_with_color(colors[board.squares[i, j]+1], string(board.squares[i, j]))
        end
        println("")
    end
    println("")

end

getRectangleBoard(x :: Int64, y :: Int64) = Board((x, y), zeros(Int64, (x, y)))

function canFit(board :: Board, piece :: Node, x :: Int64, y :: Int64)
    bx, by = board.size
    for p in piece.cubes
        posx, posy = x + p[1] - 1, y + p[2] - 1
        if posx > bx || posy > by || posy < 1 || posx < 1
            return false
        elseif board.squares[posx, posy] != 0
            return false
        end
    end

    return true
end
