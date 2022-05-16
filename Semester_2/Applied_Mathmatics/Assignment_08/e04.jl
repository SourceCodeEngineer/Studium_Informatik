using Plots

# original polynomial
function f(x::Float64, y::Float64)::Float64
    12 *x^7 + 2 *x^4 *y^6 + x^3 *y^4 + x^2 *(-3 - 7 *y^4) -2 + 9* y + 2 *y^5
end

# polynomial after applying Horner's scheme
function h(x::Float64, y::Float64)::Float64
    ((2*x*(y^2)+1)*x - 7) * x^2 * y^4 + (12 * (x^5)-3)*x^2 + (2*(y^4)+9)*y - 2
end

function evaluateFunction(N::Int, fun::Function)::Matrix{Float64}
    X = zeros(N, N);
    for i = 1:N
        for j = 1:N
            x = Float64(i)/N - 0.5
            y = Float64(j)/N - 0.5
            X[i,j] = fun(x, y)
        end
    end
    X;
end

function measureTime(runs::Int, N::Int, fun::Function)::Float64
    time = Float64(0.0);
    for i = 1:runs
        time = @elapsed evaluateFunction(N, fun);
    end
    time /= runs;
end

N = 1024
number_runs = 3

avg_runtime_f = measureTime(number_runs, N, f)
println("Original polynomial: Average runtime over ", number_runs, " runs = ", avg_runtime_f)
avg_runtime_h = measureTime(number_runs, N, h)
println("Horner polynomial: Average runtime over ", number_runs, " runs = ", avg_runtime_h)

avg_speedup = avg_runtime_f / avg_runtime_h
println("Average speedup of function transformed with horner scheme = ", avg_speedup)

# execute function, store result in X and store elapsed time
Xf = evaluateFunction( N, f )
Xh = evaluateFunction( N, h )

# create heat map
plt1 = heatmap( Xf, show_axis=true, title="Result original polynomial")
plt2 = heatmap( Xh, show_axis=true, title="Result horner polynomial")

# compute absolute difference
abs_diff = abs.(Xh .- Xf)
abs_max = maximum(abs_diff)
println("Maximum absolute difference between solutions = ", abs_max)

# create absolute difference plot
plt3 = heatmap(abs_diff, title="Difference between solutions")

p = plot(plt1, plt2, plt3, layout=(3, 1))
plot!(size=(1200, 960))
