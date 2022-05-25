using LinearAlgebra

function stepJacobi!(x_next::Vector, A::Matrix, b::Vector, x::Vector)
    for i in eachindex(x)

        x_next[i] = (b[i] - dot(A[i, :], x) + A[i, i]*x[i]) / A[i, i]
        x[i] = x_next[i]
         
    end
end

#------------------------------ [ Exercise 2 ] ------------------------------
function stepGaußSeidel!(x::Vector, A::Matrix, b::Vector)
    for i in eachindex(x)

        x[i] = (b[i] - dot(A[i, :], x) + A[i, i]*x[i]) / A[i, i]

    end
end


function errorNorm(A::Matrix, b::Vector, x::Vector)
    norm(b - A * x)
end
#------------------------------ [ Exercise 2 ] ------------------------------


# -------------------------- Iterative Solver ------------------------------
mutable struct SolverData{MatType, VecType}
    A::MatType
    b::VecType
    x::VecType
    x_next::VecType
end

function solveIterative!(solver!::Function, data::SolverData, maxiter, epsilon)
    r = zeros(maxiter)

    iter = 2
    r[1] = errorNorm(data.A, data.b, data.x)

    while iter <= maxiter && r[iter-1] > epsilon

        solver!(data.x_next, data.A, data.b, data.x)
        data.x_next, data.x = data.x, data.x_next

        r[iter] = errorNorm(data.A, data.b, data.x)
        iter += 1
    end

    data.x, filter(!iszero, r[1:iter-1])
end

# -------------------------- Solver Definitions --------------------------
function jacobi(A::Matrix, b::Vector, maxiter = 100, epsilon = 1e-8)
    x = zeros(length(b))
    solveIterative!((x_, A, b, x) -> stepJacobi!(x_, A, b, x), SolverData(A, b, x, similar(x)), maxiter, epsilon)
end

function gaußSeidel(A::Matrix, b::Vector, maxiter = 300, epsilon = 1e-8)
    x = zeros(length(b))
    solveIterative!((x_, A, b, x) -> stepGaußSeidel!(x_, A, b), SolverData(A, b, x, similar(x)), maxiter, epsilon)
end

function conjgrad(A::Matrix, b::Vector, maxiter = 5, epsilon = 1e-8)
    x = zeros(length(b))
    er = zeros(maxiter+1)
    iter = 1

    r = b - A * x;
    p = r;
    rsold = r' * r;
    er[1] = rsold
    while iter <= maxiter && sqrt(rsold) > epsilon
        iter = iter + 1
        Ap = A * p;
        alpha = rsold / (p' * Ap);
        x = x + alpha * p;
        r = r - alpha * Ap;
        rsnew = r' * r;
        p = r + (rsnew / rsold) * p;
        rsold = rsnew;
        er[iter] = rsold
    end
    return x, filter(!iszero, er)  
end

# -------------------------- Tests ------------------------------
begin
    A = [ 1.0   3    1    2    5;
            3   13   7    8    17;
            1   7    21   8    15;
            2   8    8    7    16;
            5   17   15   16   40 ]

    b = [ 1.0; 1; 1; 1; 1 ]

    x1 = A\b; 
    @time x2 = jacobi(A, b)[1];
    @time x3 = gaußSeidel(A, b)[1];
    @time x4 = conjgrad(A, b)[1];
    
    
    println("Result of backslash operator is ", round.(x1; digits=2))
    println("Result of Jacobi method is ", round.(x2; digits=2))
    println("Result of Gauß-Seidel method is ", round.(x3; digits=2))
    println("Result of conjugate gradient method is ", round.(x4; digits=2))
end
# -------------------------- Tests ------------------------------
