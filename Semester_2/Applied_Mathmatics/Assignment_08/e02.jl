using Plots
using Plots.PlotMeasures

# QUICK OVERVIEW OF VARIABLE NAMES
# rv = return value
# xi = x on i
# xim = x on i minus 1
# xb = x inbetween

module Quadrature
function right(s::Float64, e::Float64, N::Int, f::Function)::Float64

    h = (e - s) / N

    rv = 0.0

    for i = 1 : N

        xi = s + i * h

        rv += h * f(xi)
    end

    return rv

end

function trapez(s::Float64, e::Float64, N::Int, f::Function)::Float64

    h = (e - s) / N

    rv = 0.0

    for i = 1 : N

        xim = s + (i - 1) * h

        xi = xim + h

        rv += h / 2 * (f(xim) + f(xi))
    end

    return rv

end

function simpson(s::Float64, e::Float64, N::Int, f::Function)::Float64

    h = (e - s) / N

    rv = 0.0

    for i = 1 : N

        xim = s + ( i - 1 ) * h

        xi = xim + h

        xb = (xim + xi) / 2

        rv += h / 6 * (f(xim) + 4 * f(xb) + f(xi))
    end

    return rv
end
end

function f(x::Float64)::Float64
    tanh(x)
end

function F(x::Float64)::Float64
    log(cosh(x))
end

# plot function, its analtyic integral, the numerical approximations, and the local error
function plotFunctionAndErrors(i_start::Float64, i_end::Float64, N::Int, f::Function, F::Function)
    X = i_start:((i_end-i_start)/100):i_end;
    Y = f.(X);

    XI = i_start:((i_end-i_start)/N):i_end

    YI = f.(XI);
    II = F.(XI) .- F(i_start)

    QSum = zeros(N + 1)
    QTra = zeros(N + 1)
    QSim = zeros(N + 1)

    for i = 1 : N
        i_end_2 = i_start + (i_end - i_start) / N * i;

        QSum[i+1] = Quadrature.right(i_start, i_end_2, i, f);
        QTra[i+1] = Quadrature.trapez(i_start, i_end_2, i, f);
        QSim[i+1] = Quadrature.simpson(i_start, i_end_2, i, f);
    end

    println(YI[end], " ", QSum[end], " ", QTra[end], " ", QSim[end])

    plt1 = plot(X, Y, color= :black, xlabel="x", ylabel="f(x)", title="f(x)", legend=false, left_margin=4mm, bottom_margin=3mm)
    plt2 = plot(XI, II, color= :black, label="Analytical", xlabel="x", ylabel="F(x)", title="F(x), N=" * string(N), legend=:top, left_margin=4mm, bottom_margin=3mm)

    plot!(plt2, XI, QSum, color= :grey, label="Sum")
    plot!(plt2, XI, QTra, color= :blue, label="Trapez")
    plot!(plt2, XI, QSim, color= :red, label="Simpson")

    ErrSu = abs.(II .- QSum);
    ErrTr = abs.(II .- QTra);
    ErrSi = abs.(II .- QSim);

    pltErr = plot(XI, ErrSu, color= :grey, label="Sum", xlabel="x", ylabel="error", title="Error to analytical solution, N=" * string(N), legend=:topleft, left_margin=4mm, bottom_margin=3mm)
    plot!(pltErr, XI, ErrTr, color= :blue, label="Trapez")
    plot!(pltErr, XI, ErrSi, color= :red, label="Simpson")

    plot(plt1, plt2, pltErr, layout=(3,1))
end

# plot approximation error for different grid sizes
function plotErrorN(i_start::Float64, i_end::Float64, N::Int, f::Function, F::Function)
    target = F(i_end) - F(i_start)
    ESum = zeros(N-1)
    ETra = zeros(N-1)
    ESim = zeros(N-1)
    X = zeros(N-1)

    for i = 2:N
        X[i-1] = i
        ESum[i-1] = abs(target - Quadrature.right(i_start, i_end, i, f));
        ETra[i-1] = abs(target - Quadrature.trapez(i_start, i_end, i, f));
        ESim[i-1] = abs(target - Quadrature.simpson(i_start, i_end, i, f));
    end

    pltErr = plot(X, log10.(ESum), color= :grey, label="Sum", xlabel="x", ylabel="error (log)", title="Error to analytical solution (log), varying N", left_margin=4mm, bottom_margin=3mm)
    plot!(pltErr, X, log10.(ETra), color= :blue, label="Trapez")
    plot!(pltErr, X, log10.(ESim), color= :red, label="Simpson")
end

p = plot(
    plotFunctionAndErrors(-1.0, 5.0, 3, f, F),
    plotErrorN(-1.0, 5.0, 100, f, F),
    layout=grid(1,2, widths=[0.5, 0.5])
)
plot!(size=(1200, 480))

