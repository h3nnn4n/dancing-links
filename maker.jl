type Node
    cubes      :: Array{(Int64, Int64)}
end

type Piece
    cubits     :: Array{Node}
    rotations  :: Int64
    size       :: Int64
    id         :: Int64
end

type Board
    size       :: (Int64, Int64)
    squares    :: Array{Int64}
end

square   = Piece([Node([(1,1), (1,2), (2,1), (2,2)])], 1, 4, 1)

stick    = Piece([Node([(1,1), (2,1), (3,1), (4,1)]),
                  Node([(1,1), (1,2), (1,3), (1,4)])], 2, 4, 2)

triangle = Piece([Node([(1,1), (2,1), (3,1), (2,2)]),
                  Node([(1,2), (2,2), (3,2), (2,1)]),
                  Node([(1,1), (1,2), (1,3), (2,2)]),
                  Node([(1,2), (2,1), (2,2), (2,3)])], 4, 4, 3)

sssss    = Piece([Node([(1,1), (2,1), (2,2), (3,2)]),
                  Node([(1,2), (2,2), (2,1), (1,3)])], 2, 4, 4)

zzzzz    = Piece([Node([(2,1), (2,2), (1,2), (3,1)]),
                  Node([(1,1), (1,2), (2,2), (2,3)])], 2, 4, 5)

jjjjj    = Piece([Node([(1,1), (1,2), (1,3), (2,1)]),
                  Node([(1,1), (2,1), (3,1), (3,2)]),
                  Node([(1,3), (2,3), (2,2), (2,1)]),
                  Node([(1,1), (1,2), (2,2), (3,2)])], 4, 4, 6)

lllll    = Piece([Node([(1,1), (2,1), (2,2), (2,3)]),
                  Node([(1,2), (2,2), (3,2), (3,1)]),
                  Node([(1,1), (1,2), (1,3), (2,3)]),
                  Node([(1,2), (1,1), (2,1), (3,1)])], 4, 4, 7)

Base.println(board :: Board) = print(board :: Board)

getRectangleBoard(x :: Int64, y :: Int64) = Board((x, y), zeros(Int64, (x, y)))

function canFit(board :: Board, piece :: Node, x :: Int64, y :: Int64)
    bx, by = board.size
    for p in piece.cubes
        posx, posy = x + p[1] - 1, y + p[2] - 1
        if posx > bx || posy > by
            return false
        elseif board.squares[posx, posy] != 0
            return false
        end
    end

    return true
end

function main()
    x, y = 8, 5
    bb = getRectangleBoard(x, y)

    pool  = Piece[]

    push!(pool, triangle)
    push!(pool, triangle)
    push!(pool, square)
    push!(pool, square)
    push!(pool, stick)
    push!(pool, stick)
    push!(pool, sssss)
    push!(pool, zzzzz)
    push!(pool, jjjjj)
    push!(pool, lllll)

    for (n, ppp) in enumerate(pool)
        for i in 1:x, j in 1:y
            for pp in ppp.cubits
                if canFit(bb, pp, i, j)
                    w = zeros(Int64, 5*8 + 10)
                    for p in pp.cubes
                        posx, posy = i + p[1] - 1, j + p[2] - 1
                        w[n] = 1
                        w[10 + (posx-1) + (posy-1)*x + 1] = 1
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

main()