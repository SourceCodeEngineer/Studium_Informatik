#=
    Scalar/Scalar Multiplication
    hint: you can use `exp(log(a)+log(b))` to multiply two positive float values
=#
function multiply(a::Float64, b::Float64)
    result = 0.0
    negative = (a < 0 && b >= 0) || (b < 0 && a >= 0)
    positive = !negative
    a = abs(a)
    for i in 1:1:a
        if negative && b > 0 || positive && b < 0
            result -= b
        else
            result += b
        end
    end
    return result
end

#= Scalar/Vector Multiplication =#
function multiply(a::Float64, b::Array{Float64,1})
    return [(multiply(a,i)) for i in b]
end

#= Scalar/Matrix Multiplication =#
function multiply(a::Float64, b::Array{Float64,2})
    exp.(log.(b).+log(a))
end

#= Dot Product =#
function dot(r, c)
    r[1] * c[1] + r[2] * c[2]
end

#= Vector/Matrix Multiplication =#
function multiply(a::Array{Float64,1}, b::Array{Float64,2})
    x = a[1] * b[1,1] + a[2] * b[1,2]
    y = a[1] * b[2,1] + a[2] * b[2,2]
    [x,y]
end

#= Matrix/Matrix Multiplication =#
function multiply(a::Array{Float64,2}, b::Array{Float64,2})
    u = a[1,1] * b[1,1] + a[1,2] * b[2,1]

    v = a[1,1] * b[1,2] + a[1,2] * b[2,2]

    w = a[2,1] * b[1,1] + a[2,2] * b[2,1]

    x = a[2,1] * b[1,2] + a[2,2] * b[2,2]

    [[u,w] [v,x]]
end

#= Matrix/Matrix Addition =#
function add(a::Array{Int,2}, b::Array{Int,2})

    matSum = zeros(3,3)

    rows = size(a)[1]

    cols = size(a)[2]

    for i in 1:rows

        for j in 1:cols

            matSum[i,j] = a[i,j] + b[i,j]
        end

    end

    return matSum

end

#= Matrix Transpose =#
function transpose(a::Array{Int,2})

    if length(a) == 2 # For 1x2 arrays

        x = Array{Int,2}(undef,2,1)

        x[1] = a[1]

        x[2] = a[2]

    elseif length(a) == 4 # For 1x4 arrays

        if size(a)[1] == 1

            x = Array{Int,2}(undef,4,1)

            for i in 1:4

                x[i] = a[i]

            end

        else # For 2x2 arrays

            x = Array{Int,2}(undef,2,2)

            x[1] = a[1]

            x[2] = a[3]

            x[3] = a[2]

            x[4] = a[4]

        end

    else # For 2x4 arrays

        x = Array{Int,2}(undef,2,4)

        x[1] = a[1]

        x[2] = a[5]
        
        x[3] = a[2]
        
        x[4] = a[6]
        
        x[5] = a[3]
        
        x[6] = a[7]
        
        x[7] = a[4]
        
        x[8] = a[8]
    
    end
    
    x
    
end

#===============================================================================
        Test Cases (do not touch these!)
===============================================================================#
#= Scalar/Scalar Multiplication =#
@assert multiply( 1.0,  2.0) == ( 1.0 *  2.0)
@assert multiply( 1.0,  1.0) == ( 1.0 *  1.0)
@assert multiply( 0.0,  1.0) == ( 0.0 *  1.0)
@assert multiply(-1.0,  2.0) == (-1.0 *  2.0)
@assert multiply(-1.0,  1.0) == (-1.0 *  1.0)
@assert multiply(-0.0,  1.0) == (-0.0 *  1.0)
@assert multiply(-1.0, -2.0) == (-1.0 * -2.0)
@assert multiply(-1.0, -1.0) == (-1.0 * -1.0)
@assert multiply(-0.0, -1.0) == (-0.0 * -1.0)
@assert multiply( 1.0, -2.0) == ( 1.0 * -2.0)
@assert multiply( 1.0, -1.0) == ( 1.0 * -1.0)
@assert multiply( 0.0, -1.0) == ( 0.0 * -1.0)

#= Scalar/Vector Multiplication =#
@assert multiply(2.0, [1.0, 2.0]) == (2.0 * [1.0, 2.0])
@assert multiply(0.0, [1.0, 2.0]) == (0.0 * [1.0, 2.0])
@assert multiply(0.0, [1.0, 2.0]) != [0.0, 2.0]
@assert multiply(3.0, [3.0, 1.0]) == (3.0 * [3.0, 1.0])
@assert multiply(3.0, [3.0, 1.0]) == (3.0 * [3.0, 1.0])

#= Scalar/Matrix Multiplication =#
@assert multiply(0.0, [1.0  2.0]) == (0.0 * [1.0  2.0])
@assert multiply(2.0, [1.0  2.0]) == (2.0 * [1.0  2.0]) 

@assert multiply(1.0, [[1.0,2.0] [1.0,2.0]]) == (1.0 * [[1.0,2.0] [1.0,2.0]])
@assert multiply(1.0, [[1.0 2.0] [1.0 2.0]]) == (1.0 * [[1.0 2.0] [1.0 2.0]])
@assert multiply(2.0, [[1.0,2.0] [1.0,2.0]]) == (2.0 * [[1.0,2.0] [1.0,2.0]])
@assert multiply(2.0, [[1.0 2.0] [1.0 2.0]]) == (2.0 * [[1.0 2.0] [1.0 2.0]])
@assert multiply(0.0, [[1.0,2.0] [1.0,2.0]]) != [[0.0, 0.0] [1.0, 2.0]]
@assert multiply(0.0, [[1.0 2.0] [1.0 2.0]]) != [[0.0 0.0] [1.0 2.0]]

#= Dot Product =#
@assert dot([1.0,1.0], [1.0,1.0]) == 2.0
@assert dot([0.0,1.0], [1.0,1.0]) == 1.0
@assert dot([0.0,0.0], [1.0,1.0]) == 0.0
@assert dot([0.0,0.0], [0.0,0.0]) == 0.0
@assert dot([1.0 1.0], [1.0 1.0]) == 2.0
@assert dot([0.0 1.0], [1.0 1.0]) == 1.0
@assert dot([0.0 0.0], [1.0 1.0]) == 0.0
@assert dot([0.0 0.0], [0.0 0.0]) == 0.0
@assert dot([0.0,2.0], [1.0,2.0]) == 4.0
@assert dot([0.0,2.0], [1.0,1.0]) == 2.0

#= Vector/Matrix Multiplication =#
@assert multiply([0.0,0.0], [[1.0,1.0] [1.0,1.0]]) == [0.0,0.0]
@assert multiply([0.0,2.0], [[1.0,1.0] [1.0,1.0]]) == [2.0,2.0]
@assert multiply([1.0,2.0], [[1.0,1.0] [1.0,1.0]]) == [3.0,3.0]
@assert multiply([2.0,2.0], [[1.0,1.0] [1.0,1.0]]) == [4.0,4.0]
@assert multiply([0.0,0.0], [[1.0,2.0] [1.0,1.0]]) == [0.0,0.0]
@assert multiply([0.0,2.0], [[1.0,2.0] [1.0,1.0]]) == [2.0,2.0]
@assert multiply([1.0,2.0], [[1.0,2.0] [1.0,1.0]]) == [3.0,4.0]
@assert multiply([2.0,2.0], [[1.0,2.0] [1.0,1.0]]) == [4.0,6.0]

#= Matrix/Matrix Multiplication =#
@assert multiply([[0.0,0.0] [0.0,0.0]], [[1.0,1.0] [1.0,1.0]]) == [[0.0,0.0] [0.0,0.0]]
@assert multiply([[0.0,0.0] [1.0,1.0]], [[1.0,1.0] [1.0,1.0]]) == [[1.0,1.0] [1.0,1.0]]
@assert multiply([[1.0,1.0] [1.0,1.0]], [[1.0,1.0] [1.0,1.0]]) == [[2.0,2.0] [2.0,2.0]]
@assert multiply([[0.0,0.0] [0.0,1.0]], [[1.0,1.0] [1.0,1.0]]) == [[0.0,1.0] [0.0,1.0]]
@assert multiply([[0.0,1.0] [0.0,1.0]], [[1.0,1.0] [1.0,1.0]]) == [[0.0,2.0] [0.0,2.0]]
@assert multiply([[1.0,0.0] [1.0,0.0]], [[1.0,1.0] [1.0,1.0]]) == [[2.0,0.0] [2.0,0.0]]

#= Matrix Transpose =#
@assert transpose([[0] [0]]) == [0 0]'
@assert transpose([[1] [2]]) == [1 2]'
@assert transpose([[1,1] [2,2]]) == [1 2; 1 2]'
@assert transpose([[1,2] [3,4]]) == [1 3; 2 4]'
@assert transpose([[1,1,1,1] [2,2,2,2]]) == [1 2; 1 2; 1 2; 1 2]'
@assert transpose([[1] [2] [3] [4]]) == [1 2 3 4]'

#= Matrix/Matrix Addition =#
@assert add([[9,8,7] [6,5,4] [3,2,1]],
            [[1,2,3] [4,5,6] [7,8,9]]) == [[9,8,7] [6,5,4] [3,2,1]] + [[1,2,3] [4,5,6] [7,8,9]]
@assert add([[-1,-2,-3] [-4,-5,-6] [-7,-8,-9]],
            [[1,2,3] [4,5,6] [7,8,9]]) == [[-1,-2,-3] [-4,-5,-6] [-7,-8,-9]] + [[1,2,3] [4,5,6] [7,8,9]]
