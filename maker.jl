include("pieces_tetraminoes.jl")
include("pieces_pentaminoes.jl")

include("defs.jl")

include("data_types.jl")


function main()
    x, y = 10, 6
    bb = getRectangleBoard(x, y)

    pool  = Piece[]

    push!(pool, pento_X)
    push!(pool, pento_V)
    push!(pool, pento_U)
    push!(pool, pento_I)
    push!(pool, pento_F)
    push!(pool, pento_N)
    push!(pool, pento_P)
    push!(pool, pento_T)
    push!(pool, pento_W)
    push!(pool, pento_Z)
    push!(pool, pento_Y)
    push!(pool, pento_L)

    w = buildMatrix(deepcopy(bb), pool, true)

    println("$(length(pool) + x*y) $w $(length(pool) + 0)")

    buildMatrix(deepcopy(bb), pool)
end

main()
